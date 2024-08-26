#pragma once

#include "sql/operator/physical_operator.h"
class OrderByUnit;
class Tuple;
class OrderByPhysicalOperator : public PhysicalOperator {
 public:
  OrderByPhysicalOperator(std::vector<std::unique_ptr<OrderByUnit>>&& units ): units_(std::move(units)), index_in_tuples_(-1) {}
  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
 private:
  std::vector<int> offsets_;
  std::vector<std::unique_ptr<OrderByUnit>> units_;
  std::vector<Tuple*> tuples_;
  size_t index_in_tuples_;
};