#include "sql/operator/order_by_physical_operator.h"
#include "storage/trx/trx.h"
#include "sql/stmt/order_by_stmt.h"
#include "common/rc.h"
#include "common/lang/comparator.h"
#include "sql/expr/tuple.h"

#include <algorithm>


RC OrderByPhysicalOperator::open(Trx* trx) {
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }
  RC rc;
  
  if (rc = children_[0]->open(trx); rc != RC::SUCCESS) {
    LOG_WARN("order_by physical operator cannot open its child");
    return rc;
  }
  // 设置好每一个要排序的field的offset
  auto child_oper = children_.front().get();
  auto schema = child_oper->schema();
  for (size_t j = 0; j < units_.size(); j++) {  
    for (int i = 0; i < schema->cell_num(); i++) {
      auto spec = schema->cell_at(i);
      if (strcmp(spec.table_name(), units_[j]->table_->name()) == 0 && strcmp(spec.field_name(), units_[j]->field_->name()) == 0) {
        offsets_.emplace_back(i);
        break;
      }
    }
  }
  // sizes of two vectors shall be identical.
  assert(units_.size() == offsets_.size());
  while ((rc = child_oper->next()) == RC::SUCCESS) {
    Tuple *t = child_oper->current_tuple();
    if (t->type() == TupleType::ROW_TUPLE) {
      auto row_tuple = static_cast<RowTuple*>(t);
      std::unique_ptr<Tuple> t_ptr(new RowTuple(*row_tuple));
      std::cout << t_ptr.get() << '\n';
      tuples_.emplace_back(std::move(t_ptr));
    } else if (t->type() == TupleType::JOINED_TUPLE) {
      auto joined_tuple = static_cast<JoinedTuple*>(t);
      JoinedTuple *tuple = new JoinedTuple;
      tuple->set_left(tuple_cre_factory(joined_tuple->left_tuple()), true);
      tuple->set_right(tuple_cre_factory(joined_tuple->right_tuple()), true);
      std::unique_ptr<Tuple> joined_tuple_ptr(tuple);
      tuples_.emplace_back(std::move(joined_tuple_ptr));
    }
  }

  // currently order by only supports sorting JoinedTuple and RowTuple
  auto comparator = [this] (const std::unique_ptr<Tuple>& t1, const std::unique_ptr<Tuple>& t2) -> bool {
    for(size_t k = 0; k < this->offsets_.size(); ++k) {
      int index = this->offsets_[k];
      int result;
      Value v1,v2;
      t1->cell_at(index, v1);
      t2->cell_at(index,v2);
      auto unit = this->units_[k].get();
      if (v2.attr_type() == AttrType::NULLS) {
        if (v1.attr_type() == v2.attr_type()) {
          continue;
        }
        return unit->asc_ ? false : true;
      }
      switch (v1.attr_type()) {
      case AttrType::INTS :
        result = common::compare_int((void*)(v1.data()), (void*)v2.data()); 
        break;
      case AttrType::FLOATS:
        result = common::compare_float((void*)v1.data(), (void*)v2.data());
        break;
      case AttrType::DATES: 
        result = common::compare_int((void*)(v1.data()), (void*)v2.data()); 
        break;
      case AttrType::CHARS:
        result = common::compare_string((void*)(v1.data()), unit->field_->len() , (void*)v2.data(), unit->field_->len());
        break;
      case AttrType::NULLS: 
        if (v2.attr_type() == v1.attr_type()) {
          result = 0;
        } else {
          return unit->asc_ ? true : false;
        }
        break;
      default:
        // UNREACHABLE.
        assert(false);
        result = 0;
        break;
      }
      if (result != 0) {
        return unit->asc_ ? (result > 0 ? false : true) : (result > 0 ? true: false);
      }
    }
    return 0;
  };
  std::sort(tuples_.begin(), tuples_.end(), comparator);
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next() {
  ++index_in_tuples_;
  if (static_cast<size_t>(index_in_tuples_) == tuples_.size()) {
    return RC::RECORD_EOF;
  }
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close()  {
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple() {
  return tuples_[index_in_tuples_].get();
}
