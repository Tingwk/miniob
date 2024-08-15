#pragma once
#include <string>
#include "sql/stmt/stmt.h"
class Db;
class Table;
class DropTableStmt : public Stmt {
 public:
  DropTableStmt() = default;
  DropTableStmt(std::string & name) : table_name_(std::move(name)) {}
  ~DropTableStmt() = default;
  StmtType type() const override {return StmtType::DROP_TABLE; }
 public:
  std::string& table_name() {return table_name_;}
  static RC create(Db* db, DropTableSqlNode& node, Stmt* &stmt) ;
 private:
  std::string table_name_;
};