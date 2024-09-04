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

#include "sql/stmt/update_stmt.h"
#include "storage/db/db.h"
#include "sql/parser/parse.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount, const FieldMeta* meta, FilterStmt* filter) : table_(table), values_(values), value_amount_(value_amount), field_meta_(meta), filter_(filter)
{}

UpdateStmt::UpdateStmt(Table *table, FilterStmt* filter, std::vector<std::unique_ptr<AssignmentUnit>>&& assignments) 
: table_(table), filter_(filter),assignments_(std::move(assignments)) {}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt) {
  // TODO
  auto tb = db->find_table(update.relation_name.c_str());
  if (tb == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::unordered_map<std::string, Table*> name_to_table;
  std::vector<std::unique_ptr<AssignmentUnit>> assignments;
  for (size_t k = 0; k < update.assignments.size();++k) {
    auto &assign = update.assignments[k];
    auto meta = tb->table_meta().field(assign.attribute_name.c_str());
    if (meta == nullptr) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    
    name_to_table.insert({assign.attribute_name ,tb});
    if (!meta->nullable() && assign.value.attr_type() == AttrType::NULLS) {
      return RC::INTERNAL;
    } 
    std::unique_ptr<AssignmentUnit> unit (new AssignmentUnit);
    unit->field_meta = meta;
    if (assign.type == ValueType::SUB_QUERY) {
      Stmt* stmt;
      if (SelectStmt::create(db, assign.sub_query->selection, stmt) != RC::SUCCESS) {
        return RC::INTERNAL;
      }
      unit->new_value_type = ValueType::SUB_QUERY;
      unit->sub_query = stmt;
    } else {
      unit->new_value = assign.value;
      unit->new_value_type = assign.type;
    }
    assignments.emplace_back(std::move(unit));
  }
  FilterStmt *filter = nullptr;
  auto rc = FilterStmt::create(db, tb, &name_to_table, update.conditions.data(), static_cast<int>(update.conditions.size()), filter);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // auto update_stmt = new UpdateStmt(tb, &update.value, 1, meta, filter);
  // stmt = update_stmt;
  auto update_stmt = new UpdateStmt(tb,filter , std::move(assignments));
  stmt = update_stmt;
  return RC::SUCCESS;
}
