
#include "sql/operator/order_by_logical_operator.h"
#include "sql/stmt/order_by_stmt.h"

OrderByLogicalOperator::OrderByLogicalOperator(std::vector<std::unique_ptr<OrderByUnit>>&& units): units_(std::move(units)) {}