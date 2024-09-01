#pragma once

#include "sql/expr/expression.h"

class ValueListExpr : public Expression {
 public:
  ValueListExpr() = default;
  virtual ~ValueListExpr() = default;
  ValueListExpr(std::vector<Value>* values) : values_(values) {}
  

  RC get_value(const Tuple &tuple, Value &value) const override {
    return RC::SUCCESS;
  }
  AttrType value_type() const override {
    return AttrType::UNDEFINED;
  }
  std::vector<Value>& values_list() { return *values_; }
  RC try_get_value(Value &value) const override { return RC::SUCCESS;}
  ExprType type() const override { return ExprType::VALUE_LIST_EXPR; }
 private:
  std::vector<Value> *values_;
};