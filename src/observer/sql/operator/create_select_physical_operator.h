#pragma once

#include "sql/operator/physical_operator.h"
class Table;
class CreateSelectPhysicalOperator : public PhysicalOperator {
 public:
  CreateSelectPhysicalOperator(Table* table, const std::string& name) :suq_query_table_(table),new_table_name_(name) {}
  // RC close() override { return RC::SUCCESS;}
  PhysicalOperatorType type() const override { return PhysicalOperatorType::CREATE_SELECT; }
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
 private:
  Table *suq_query_table_;
  std::string new_table_name_;
  // std::unique_ptr<PhysicalOperator> sub_query_;
};