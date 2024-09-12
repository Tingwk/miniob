#pragma once
#include "sql/stmt/stmt.h"
class SelectStmt;
class Table;
class CreateSelectStmt : public Stmt {
 public:
  // CreateSelectStmt(const std::string&name,Table* tb, Stmt* query):tb_name_(name), sub_query_table_(tb), query_(query) {}
  CreateSelectStmt(const std::string&name, Stmt* query, bool using_infos, std::vector<AttrInfoSqlNode>&& infos):tb_name_(name), query_(query), using_infos_(using_infos), infos_(std::move(infos)) {}
  StmtType type() const override { return StmtType::CREATE_SELECT; }
  static RC create(Db *db, CreateSelectSqlNode& cs, Stmt* &stmt);
  const std::string& table_name() const { return tb_name_; }
  Stmt* query() {return query_;}
  bool using_infos() { return using_infos_;}
  std::vector<AttrInfoSqlNode>& infos() { return infos_;}
  // Table* sub_query_table() { return sub_query_table_; }
 private:
  std::string tb_name_;
  Stmt * query_;
  bool using_infos_;
  std::vector<AttrInfoSqlNode> infos_;
};