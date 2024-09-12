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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;

struct FilterObj {
  ValueType  value_type;
  Field field;                  // attr
  Value value;                  // value & null
  Stmt * sub_query;             // sub_query
  std::vector<Value> *values;   // value_list
  std::unique_ptr<Expression>   expression;

  void init_attr(const Field &field) {
    value_type     = ValueType::ATTRIBUTE;
    this->field = field;
  }

  void init_value(const Value &value) {
    value_type     = ValueType::CONSTANT;
    this->value = value;
  }

  void init_sub_query(Stmt * query) {
    this->sub_query = query;
    value_type = ValueType::SUB_QUERY;
  }
  
  void init_value_list(std::unique_ptr<Expression>& other) {
    expression.reset(other.release());
    values = static_cast<ValueListExpr*>(expression.get())->values_list();
    value_type = ValueType::VALUE_LIST;
  }
  void init_null(const Value v) {
    this->value = v;
    value_type = ValueType::NULL_TYPE;
  }
  void init_null() {
    value_type = ValueType::NULL_TYPE;
    value_type = ValueType::NULL_TYPE;
  }

  void init_expression(std::unique_ptr<Expression>& other) {
    value_type = ValueType::EXPRESSION_TYPE;
    expression.reset(other.release());
  }

  RC convert_to_expression(std::unique_ptr<Expression>& expr) {
    switch (value_type) {
    case ValueType::ATTRIBUTE:{
      expr.reset(new FieldExpr(field));
    } break;
    case ValueType::CONSTANT: {
      expr.reset(new ValueExpr(value));
    }break;
    case ValueType::NULL_TYPE : {
      expr.reset(new NullExpr);
    }break;
    case ValueType::SUB_QUERY : {

    }break;
    case ValueType::VALUE_LIST: {
      expr.reset(expression.release());
    }break;
    case ValueType::EXPRESSION_TYPE: {
      expr.reset(expression.release());
    }break;
    default:
      break;
    }
    return RC::SUCCESS;
  }
};

class FilterUnit {
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  FilterObj &left() { return left_; }
  FilterObj &right() { return right_; }

  const FilterObj &left() const { return left_; }
  const FilterObj &right() const { return right_; }

private:
  CompOp    comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt {
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const { return filter_units_; }

public:
  static RC create(Db *db, Table *default_table, const std::unordered_map<std::string, Table *> *tables,
       ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt);
  static RC create(Db *db, Table *default_table, const std::unordered_map<std::string, Table *> *tables,
    std::vector<std::unique_ptr<Expression>>& conditions, FilterStmt *&stmt);
  static RC create_filter_unit(Db *db, Table *default_table, const std::unordered_map<std::string, Table *> *tables,
       ConditionSqlNode &condition, FilterUnit *&filter_unit);
  static RC create_filter_unit(Db *db, Table *default_table, const std::unordered_map<std::string, Table *> *tables,
       std::unique_ptr<Expression>& expr, FilterUnit *&filter_unit);

  void set_flag(int index, bool flag) {
    if (index < 0 || index >= static_cast<int>(filter_flags_.size())) 
      return;
    filter_flags_[index] = flag;
  }
  bool flag(size_t k) const { return filter_flags_[k];}
  RC filter_expression(std::vector<std::unique_ptr<Expression>>& cmp_exprs);
  RC filter_sub_queries(std::vector<FilterUnit*>& vec_querys);
  RC filter_value_list(std::vector<FilterUnit*>& value_list);
private:
  static RC create_filter_obj(Db* db, FilterUnit* unit, std::unique_ptr<Expression>& expr, bool left);
private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
  // used to mark whether a filter has been pushed down.
  std::vector<bool> filter_flags_;       
};
