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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/value.h"
FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::filter_expression(std::vector<std::unique_ptr<Expression>>& cmp_exprs) {
  for (size_t k = 0; k < filter_units_.size(); k++) {
    if (!filter_flags_[k]) {
      continue;
    }
    auto unit = filter_units_[k];
    const FilterObj& left_obj = unit->left();
    const FilterObj& right_obj = unit->right();
    std::unique_ptr<Expression> left(left_obj.is_attr ? static_cast<Expression*>(new FieldExpr(left_obj.field)) : static_cast<Expression*>(new ValueExpr(left_obj.value)));
    std::unique_ptr<Expression> right(right_obj.is_attr ? static_cast<Expression*>(new FieldExpr(right_obj.field)) : static_cast<Expression*>(new ValueExpr(right_obj.value)));
    auto cmp_expr = new ComparisonExpr(unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }
  return RC::SUCCESS;
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  tmp_stmt->filter_flags_.resize(condition_num);
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
    tmp_stmt->filter_flags_[i] = true;
  }
  
  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  if (condition.left_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  }

  if (condition.right_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
  } else {
    FilterObj filter_obj;
    if (condition.left_is_attr && filter_unit->left().field.attr_type() == AttrType::DATES) {
      ASSERT(condition.right_value.attr_type() == AttrType::CHARS, "value type must be chars");
      auto date_str = condition.right_value.get_string();
      int date_val;
      if (rc = date_str_to_int(date_str.c_str(), date_val); rc != RC::SUCCESS) {
        return rc;
      }
      Value v;
      v.set_date(date_val);
      filter_obj.init_value(v);
    } else {
      filter_obj.init_value(condition.right_value);
    }
    filter_unit->set_right(filter_obj);
  }

  if (!condition.left_is_attr) {
    FilterObj filter_obj;
    if (condition.right_is_attr && filter_unit->right().field.attr_type() == AttrType::DATES) {
      ASSERT(condition.left_value.attr_type() == AttrType::CHARS, "value type must be chars");
      auto date_str = condition.left_value.get_string();
      int date_val;
      if (rc = date_str_to_int(date_str.c_str(), date_val);RC::SUCCESS != rc) {
        return rc;
      }
      Value v;
      v.set_date(date_val);
      filter_obj.init_value(v);
    } else {
      filter_obj.init_value(condition.left_value);
    }
    filter_unit->set_left(filter_obj);
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}
