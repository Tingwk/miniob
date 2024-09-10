#pragma once

#include "sql/operator/physical_operator.h"
class Table;
class Session;
class CreateSelectPhysicalOperator : public PhysicalOperator {
 public:
  // CreateSelectPhysicalOperator(const std::string& name, std::unique_ptr<PhysicalOperator>&& phy_oper) :new_table_name_(name), sub_query_(std::move(phy_oper)) {}
  CreateSelectPhysicalOperator(Session* session, const std::string& name) :session_(session), new_table_name_(name) {}
  // RC close() override { return RC::SUCCESS;}
  PhysicalOperatorType type() const override { return PhysicalOperatorType::CREATE_SELECT; }
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
 private:
  // Table *suq_query_table_;
  Session *session_;
  std::string new_table_name_;
  TupleSchema schema_;
  // std::unique_ptr<PhysicalOperator> sub_query_;
};