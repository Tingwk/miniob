#include "sql/operator/update_physical_operator.h"
#include "sql/expr/tuple.h"
#include "storage/index/index.h"
#include "sql/parser/value.h"
#include "sql/stmt/update_stmt.h"
#include "sql/expr/sub_query_physical_expr.h"
#include <string.h>
#include <cstring>



UpdatePhysicalOperator::UpdatePhysicalOperator(Table* t, std::vector<std::unique_ptr<AssignmentUnit>>&& assignments, std::vector<size_t>&& indices, std::vector<std::unique_ptr<SubQueryPhysicalExpr>>&& queries)
:table_(t), assignments_(std::move(assignments)), indices_(std::move(indices)),sub_queries_(std::move(queries)) {

}

RC UpdatePhysicalOperator::open(Trx *trx) {
  RC rc;
  if (!children_.empty()) {
    auto child = children_[0].get();
    rc = child->open(trx);
    if (OB_FAIL(rc)) {
      LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
      return rc;
    }
  }
  size_t k = 0 ;
  new_values_.resize(assignments_.size());
  std::set<size_t> indices_map;
  for(auto & query : sub_queries_) {
    query->do_sub_query(trx);
    if (OB_FAIL(rc)) {
      LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
      return rc;
    }
    Value result;
    if (query->reuslt_num() > 1) {
      // sub query returns multiple rows.
      return RC::INTERNAL;
    } else if (query->reuslt_num() == 1) {
      result = query->get_sub_query_results()[0];
    } else {
      if (!assignments_[indices_[k]]->field_meta->nullable()) {
        // field is non-nullable while subquery return 0 row.
        return RC::INTERNAL;
      }
      result.set_null();
    }
    initialize_value(indices_[k], result);
    indices_map.insert(indices_[k]);
    ++k;
  }
  for (size_t i = 0; i < assignments_.size(); i++) {
    auto assignment = assignments_[i].get();
    cells_to_update_.insert(string(assignment->field_meta->name()));
    if (indices_map.find(i) != indices_map.end()) {
      continue;
    }
    initialize_value(i, assignment->new_value);
  }
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() {
  RC rc = RC::SUCCESS;
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    if (OB_SUCC(rc)) {
      auto tuple = static_cast<RowTuple*>(children_[0]->current_tuple());
      auto record = tuple->record();
      table_->delete_entry_of_indexes(record.data(), record.rid(), cells_to_update_);
      for (size_t k = 0; k < assignments_.size(); ++k) {
        auto assign = assignments_[k].get();
        auto meta = assign->field_meta;
        auto offset = meta->offset();
        auto len = meta->len();
        if (new_values_[k].attr_type() == AttrType::NULLS) {
          std::memset((void *)(record.data() + offset), 0, len);
          // mark cell is null
          *(static_cast<char*>(record.data() + offset + len) ) = 1; 
        } else {
          auto value_len = new_values_[k].length();
          std::memcpy((void*)(record.data() + offset), (void*)new_values_[k].data(), value_len);
          if (value_len < len) {
            std::memset((void*)(record.data() + offset + value_len), 0, len - value_len);
          }
          if (meta->nullable()) {
            *(static_cast<char*>(record.data() + offset + len)) = 0; 
          }
        }
      }
      table_->insert_entry_of_indexes(record.data(), record.rid(), cells_to_update_);
    }
  }
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::initialize_value(size_t index, const Value& new_value) {
  if (index < 0 || index >= assignments_.size()) {
    return RC::INTERNAL;
  }
  const FieldMeta* meta = assignments_[index]->field_meta;
  if (new_value.attr_type() == AttrType::NULLS) {
    new_values_[index].set_null();
  } else {
    switch (meta->type()) {
      case AttrType::DATES: 
        int val;
        date_str_to_int(new_value.get_string(), val);
        new_values_[index].set_date(val);
        break;
      case AttrType::CHARS:
        new_values_[index].set_string(new_value.get_string().c_str());
        break;
      case AttrType::INTS:
        new_values_[index].set_int(new_value.get_int());
        break;
      case AttrType::FLOATS:
        new_values_[index].set_float(new_value.get_float());
        break;
      case AttrType::BOOLEANS:
        new_values_[index].set_boolean(new_value.get_boolean());
        break;
      default:
        break;
    }
  }
  return RC::SUCCESS;
}