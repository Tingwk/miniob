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
UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount, const FieldMeta* meta, FilterStmt* filter) : table_(table), values_(values), value_amount_(value_amount), field_meta_(meta), filter_(filter)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  // TODO
  auto tb = db->find_table(update.relation_name.c_str());
  if (tb == nullptr) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  auto meta = tb->table_meta().field(update.attribute_name.c_str());
  if (meta == nullptr) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }
  FilterStmt *filter = nullptr;
  std::unordered_map<std::string, Table*> name_to_table{{update.relation_name,tb}};
  auto rc = FilterStmt::create(db, tb, &name_to_table, update.conditions.data(), static_cast<int>(update.conditions.size()), filter);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  auto update_stmt = new UpdateStmt(tb, &(update.value), 1, meta, filter);
  stmt = update_stmt;
  return RC::SUCCESS;
}
