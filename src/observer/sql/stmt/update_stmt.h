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

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/table/table.h"
#include "sql/parser/parse_defs.h"
class FilterStmt;
class Table;

struct AssignmentUnit {
  const FieldMeta* field_meta;
  ValueType new_value_type;
  Value new_value;
  Stmt* sub_query;
};

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, const Value *values, int value_amount, const FieldMeta* meta, FilterStmt* filter);
  UpdateStmt(Table *table, FilterStmt* filter ,std::vector<std::unique_ptr<AssignmentUnit>>&& assignments);
  StmtType type() const override {return StmtType::UPDATE;}
public:
  static RC create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const { return table_; }
  const Value *values() const { return values_; }
  int    value_amount() const { return value_amount_; }
  const FieldMeta * field_meta () const {return field_meta_; }
  FilterStmt * filter() {return filter_;}
  std::vector<std::unique_ptr<AssignmentUnit>>& assignments() { return assignments_; }
private:
  Table *table_        = nullptr;
  const Value *values_       = nullptr;
  int    value_amount_ = 0;
  const FieldMeta *field_meta_;
  FilterStmt *filter_;
  std::vector<std::unique_ptr<AssignmentUnit>> assignments_;
};
