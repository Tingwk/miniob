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

struct FilterObj
{
  ValueType  value_type;
  Field field;
  Value value;
  Stmt * sub_query;
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
};

class FilterUnit
{
public:
  FilterUnit() = default;
  ~FilterUnit() {}

  void set_comp(CompOp comp) { comp_ = comp; }

  CompOp comp() const { return comp_; }

  void set_left(const FilterObj &obj) { left_ = obj; }
  void set_right(const FilterObj &obj) { right_ = obj; }

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

  static RC create_filter_unit(Db *db, Table *default_table, const std::unordered_map<std::string, Table *> *tables,
       ConditionSqlNode &condition, FilterUnit *&filter_unit);
  void set_flag(int index, bool flag) {
    if (index < 0 || index >= static_cast<int>(filter_flags_.size())) 
      return;
    filter_flags_[index] = flag;
  }
  RC filter_expression(std::vector<std::unique_ptr<Expression>>& cmp_exprs);
  RC filter_sub_queries(std::vector<FilterUnit*>& vec_querys);
private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
  // used to mark whether a filter has been pushed down.
  std::vector<bool> filter_flags_;       
};
