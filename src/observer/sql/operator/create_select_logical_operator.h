#pragma once

#include "sql/operator/logical_operator.h"

class CreateSelectLogicalOperator : public LogicalOperator {
 public:
  CreateSelectLogicalOperator(const std::string&name, Table *table, std::unique_ptr<LogicalOperator>&& other): tb_name_(name), suq_query_table_(table), logical_oper_(std::move(other)) {}
  virtual ~CreateSelectLogicalOperator() = default;
  LogicalOperatorType type() const override { return LogicalOperatorType::CREATE_SELECT; }
  const std::string& table_name() const  { return tb_name_; }
  std::unique_ptr<LogicalOperator>& query() { return logical_oper_; }
  Table* sub_query_table() { return suq_query_table_; }
 private:
  std::string tb_name_;
  Table *suq_query_table_;
  std::unique_ptr<LogicalOperator> logical_oper_;
};