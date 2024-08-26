#pragma once

#include <unordered_map>
#include "sql/stmt/stmt.h"
class Table;
class FieldMeta;

class Db;
class OrderByUnit {
 public:
  OrderByUnit(Table* table, const FieldMeta* field, bool asc) : table_(table), field_(field), asc_(asc)  {}
 public:
  Table *table_;
  const FieldMeta *field_;
  bool asc_;
};
class OrderByStmt : public Stmt {

 public:
  friend class OrderByLogicalOperator;
 public:
  OrderByStmt() = default;
  StmtType type() const override { return StmtType::ORDER_BY; }
  OrderByStmt(std::vector<std::unique_ptr<OrderByUnit>>&& units) : units_(std::move(units)) {}
  static RC create(std::unordered_map<std::string,Table*>& name_to_tables , std::vector<OrderBySqlNode>& order_by_specs, OrderByStmt *&stmt);
  std::vector<std::unique_ptr<OrderByUnit>>& units() { return units_; }
  
 private:
  std::vector<std::unique_ptr<OrderByUnit>> units_;
};