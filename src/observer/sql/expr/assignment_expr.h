#pragma once

#include "sql/expr/expression.h"


class AssignmentExpr : public Expression {
 public:
  virtual ~AssignmentExpr() = default;
  
  virtual RC get_value(const Tuple &tuple, Value &value) const override { return RC::SUCCESS;}

  
  ExprType type() const override { return ExprType::ASSIGNMENT_EXPR; }

  AttrType value_type() const override { return AttrType::UNDEFINED; }

 private:
  
};