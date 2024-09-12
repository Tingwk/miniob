#pragma once

#include "sql/operator/logical_operator.h"

class CreateSelectLogicalOperator : public LogicalOperator {
 public:
  // CreateSelectLogicalOperator(const std::string&name, Table *table, std::unique_ptr<LogicalOperator>&& other): tb_name_(name), suq_query_table_(table), logical_oper_(std::move(other)) {}
  CreateSelectLogicalOperator(const std::string&name, std::unique_ptr<LogicalOperator>&& other, bool using_infos, std::vector<AttrInfoSqlNode>& infos): tb_name_(name), logical_oper_(std::move(other)),using_infos_(using_infos), infos_(infos) {}
  virtual ~CreateSelectLogicalOperator() = default;
  LogicalOperatorType type() const override { return LogicalOperatorType::CREATE_SELECT; }
  const std::string& table_name() const  { return tb_name_; }
  std::unique_ptr<LogicalOperator>& query() { return logical_oper_; }
  
  bool using_infos() {return using_infos_;}
  std::vector<AttrInfoSqlNode>& infos() { return infos_; };
 private:
  std::string tb_name_;
  std::unique_ptr<LogicalOperator> logical_oper_;
  bool using_infos_;
  std::vector<AttrInfoSqlNode> infos_;
};