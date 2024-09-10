#include "sql/operator/create_select_physical_operator.h"
#include "storage/trx/trx.h"
#include "sql/executor/create_table_executor.h"
#include "sql/operator/project_physical_operator.h"
#include "session/session.h"
#include "storage/db/db.h"
RC CreateSelectPhysicalOperator::open(Trx* trx) {
  RC rc;
  if (!children_.empty()) {
    auto child = children_[0].get();
    rc = child->open(trx);
    if (OB_FAIL(rc)) {
      LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
      return rc;
    }
  }
  // create table.
  
  auto proj_phy_oper = static_cast<ProjectPhysicalOperator*>(children_[0].get());
  proj_phy_oper->tuple_schema(schema_);
  auto &expressions = proj_phy_oper->expressions();
  std::vector<AttrInfoSqlNode> infos;
  for (size_t k = 0; k < expressions.size();++k) {
    auto expre = expressions[k].get();
    AttrInfoSqlNode attr;
    if (expre->type() == ExprType::FIELD) {
      auto field_expr = static_cast<FieldExpr*>(expre);
      auto field = field_expr->field().meta();
      attr.length = field->len();
      attr.name = field->name();
      attr.nullable = field->nullable();
      attr.type = field->type();
    } else if (expre->type() == ExprType::AGGREGATION) {
      auto aggre_expr = static_cast<AggregateExpr*>(expre);
      // attr.length = ;
      if ((aggre_expr->aggregate_type() == AggregateExpr::Type::MAX || aggre_expr->aggregate_type() == AggregateExpr::Type::MIN) && aggre_expr->value_type() == AttrType::CHARS) {
        attr.length = aggre_expr->value_length();
      } else  {
        attr.length = 4;
      }
      attr.type = aggre_expr->value_type();
      if (aggre_expr->aggregate_type() == AggregateExpr::Type::COUNT) {
        attr.type = AttrType::INTS;
      } else if (aggre_expr->aggregate_type() == AggregateExpr::Type::AVG) {
        attr.type = AttrType::FLOATS;
      }
      // attr.type = aggre_expr->value_type();
      attr.nullable = true;
      attr.name = aggre_expr->name();
    } else {
      // ...
    }
    infos.emplace_back(attr);
  }
  session_->get_current_db()->create_table(new_table_name_.c_str(), infos, StorageFormat::ROW_FORMAT);
  return RC::SUCCESS;
}

RC CreateSelectPhysicalOperator::next() {
  RC rc;
  auto table = session_->get_current_db()->find_table(new_table_name_.c_str());
  if (table == nullptr) {
    return RC::INTERNAL;
  }
  auto value_num = static_cast<size_t>(schema_.cell_num());
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    // insert tuples;
    std::vector<Value> values(value_num);
    auto tuple = children_[0]->current_tuple();
    for(size_t k = 0; k < value_num; ++k) {
      tuple->cell_at(k, values[k]);
    }
    Record record;
    table->make_record(value_num, values.data(), record);
    table->insert_record(record);
  }
  return RC::RECORD_EOF;
}

RC CreateSelectPhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}