#pragma once

#include "sql/operator/logical_operator.h"

class OrderByUnit;
class OrderByLogicalOperator : public LogicalOperator {
 public:
  OrderByLogicalOperator(std::vector<std::unique_ptr<OrderByUnit>>&& units); 
  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }
  const std::vector<std::unique_ptr<OrderByUnit>>& units() const { return units_; }
 private:
  std::vector<std::unique_ptr<OrderByUnit>> units_;
};