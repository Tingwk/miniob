/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"
#include "sql/expr/expression.h"
#include <set>
using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
  if (nullptr != order_stmt_) {
    delete order_stmt_;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;
  bool has_aggregation {false};
  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
  }

  // collect query fields in `select` statement
  vector<std::unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context);
  int i = 0;
  std::vector<int> aggregation_indices;
  for (auto &expression : select_sql.expressions) {
    if (expression->type() == ExprType::ERROR_EXPR) {
      return RC::INTERNAL;
    }
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    if (bound_expressions[i]->type() == ExprType::AGGREGATION) {
      has_aggregation = true;
      aggregation_indices.push_back(i);
    }
    ++i;
  }

  vector<std::unique_ptr<Expression>> group_by_expressions;
  set<std::string> gropy_columns;
  i = 0;
  for (std::unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
    if (group_by_expressions[i]->type() == ExprType::FIELD) {
      gropy_columns.insert(static_cast<FieldExpr*>(group_by_expressions[i].get())->field_name());
    } 
  }

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }
  size_t valid_count{0};
  if (has_aggregation) {
    for (std::unique_ptr<Expression>& expr: bound_expressions) {
      if (expr->type() == ExprType::FIELD) {
        if (group_by_expressions.empty()) {
          // i.e. select id,count(id) from table;
          return RC::INTERNAL;
        }
        auto field_expr = static_cast<FieldExpr*>(expr.get());
        if (gropy_columns.find(field_expr->field_name()) == gropy_columns.end()) {
          // field_name doesn't appear in group by clause.
          return RC::INTERNAL;
        }
        ++valid_count;
      }
    }
  }
  if (valid_count != gropy_columns.size()) {
    // The result of query `select id1, count(*) from table group by a,b` means nothing;
    return RC::INTERNAL;
  }
  std::vector<FilterStmt*> filters;
  filters.resize(select_sql.joins.size());
  RC rc;
  std::unordered_map<std::string, Table*> name_to_table;
  for (size_t k = 0; k < select_sql.joins.size(); k++) {
    std::vector<ConditionSqlNode> useful_conditions;
    for (auto &cond : select_sql.joins[k].conditions) {
      if (cond.left_value_type == ValueType::ATTRIBUTE && cond.right_value_type == ValueType::ATTRIBUTE) {
        if (rc = field_validation_check(db, cond.left_attr); rc != RC::SUCCESS) {
          return rc;
        }
        if (rc = field_validation_check(db, cond.right_attr); rc != RC::SUCCESS) {
          return rc;
        }
        name_to_table.insert({cond.left_attr.relation_name, db->find_table(cond.left_attr.relation_name.c_str())});
        name_to_table.insert({cond.right_attr.relation_name, db->find_table(cond.right_attr.relation_name.c_str())});
        useful_conditions.push_back(cond);
      } else if ((cond.left_value_type == ValueType::ATTRIBUTE && cond.right_value_type  == ValueType::CONSTANT) || (cond.right_value_type  == ValueType::ATTRIBUTE && cond.left_value_type  == ValueType::CONSTANT)) {
        select_sql.conditions.push_back(cond);
      } else if ((cond.left_value_type == ValueType::CONSTANT && cond.right_value_type  == ValueType::CONSTANT) || (cond.right_value_type  == ValueType::CONSTANT && cond.left_value_type  == ValueType::CONSTANT)) {
        useful_conditions.push_back(cond);
      }
    }
    FilterStmt *filter_stmt = nullptr;
    rc = FilterStmt::create(db, default_table, &name_to_table, useful_conditions.data(), static_cast<int>(useful_conditions.size()), filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
    filters[k] = filter_stmt;
  }
  
  
  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // order by
  OrderByStmt *order_stmt = nullptr;
  if (rc = OrderByStmt::create(table_map, select_sql.order_by, order_stmt); rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->on_conditions_.swap(filters);
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_stmt_ = order_stmt;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}

RC SelectStmt::field_validation_check(Db* db, const RelAttrSqlNode& cond) {
  auto tb = db->find_table(cond.relation_name.c_str());
  if (tb == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), cond.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  auto field_meta = tb->table_meta().field(cond.attribute_name.c_str());
  if (field_meta == nullptr) {
    LOG_WARN("no such field. field=%s.%s.%s", db->name(), tb->name(), cond.attribute_name.c_str());
    return RC::SCHEMA_FIELD_MISSING;
  }
  return RC::SUCCESS;
}

FilterStmt* SelectStmt::on_conditions_at(int index) {
  if (index < 0 || index > static_cast<int>(on_conditions_.size())) {
    return nullptr;
  }
  return on_conditions_[index];
}