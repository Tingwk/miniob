#pragma once
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "storage/trx/trx.h"

class SubQueryPhysicalExpr : public Expression {
 public:
  SubQueryPhysicalExpr() = default;
  virtual ~SubQueryPhysicalExpr() = default;
  SubQueryPhysicalExpr(std::unique_ptr<PhysicalOperator>&& other) : physical_oper_(std::move(other)) {}
  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INVALID_ARGUMENT;}
  AttrType value_type() const override { return AttrType::UNDEFINED; }
  ExprType type() const override { return ExprType::SUB_QUERY_PHYSICAL_EXPR; }
  std::unique_ptr<PhysicalOperator>& physical_operator() { return physical_oper_; }
  Trx* current_trx() { return trx_; }
  size_t reuslt_num() const { return values_.size(); }
  RC do_sub_query(Trx* trx);
  const std::vector<Value>& get_sub_query_results() const { return values_; }
 private:
  std::unique_ptr<PhysicalOperator> physical_oper_;
  std::vector<Value> values_;
  Trx* trx_;
};