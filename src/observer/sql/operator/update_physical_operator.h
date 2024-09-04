#pragma once

#include "sql/operator/physical_operator.h"
class UpdateStmt;
class AssignmentUnit;
class SubQueryPhysicalExpr;
class UpdatePhysicalOperator : public PhysicalOperator {
public:
  UpdatePhysicalOperator(Table* t, std::vector<std::unique_ptr<AssignmentUnit>>&&  assignments, std::vector<size_t>&& indices, std::vector<std::unique_ptr<SubQueryPhysicalExpr>>&& queries);

  PhysicalOperatorType type() const override {return PhysicalOperatorType::UPDATE;}
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Table* table() {return table_;}
  Tuple *current_tuple() override { 
    return nullptr; 
  }
private:
  RC initialize_value(size_t index, const Value& new_value);
private:
  RowTuple tuple_;
  Table* table_;
  std::vector<std::unique_ptr<AssignmentUnit>> assignments_;
  std::vector<size_t> indices_;
  std::vector<std::unique_ptr<SubQueryPhysicalExpr>> sub_queries_;
  std::vector<Value> new_values_;
  std::set<std::string> cells_to_update_;
};