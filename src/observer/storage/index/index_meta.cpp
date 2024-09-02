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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString UNIQUE_INDEX("unique");

RC IndexMeta::init(const char *name, std::vector<const FieldMeta *>& metas, bool unique) {
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }
  unique_ = unique_;
  name_  = name;
  for (auto meta : metas) {
   fields_.emplace_back(meta->name()); 
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME]       = name_;
  json_value[UNIQUE_INDEX] = unique_ ? "true" : "false";
  Json::Value val;
  for(auto field : fields_) {
    Json::Value v(field);
    val.append(v);
  }
  json_value[FIELD_FIELD_NAME] = std::move(val);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value  = json_value[FIELD_NAME];
  const Json::Value &fields_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique = json_value[UNIQUE_INDEX];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!unique.isString()) {
    LOG_ERROR("unique index is not a string. json value=%s", unique.toStyledString().c_str());
    return RC::INTERNAL;
  }
  if (!fields_value.isArray() || fields_value.size() <= 0) {
    LOG_ERROR("Invalid table meta. fields is not array, json value=%s", fields_value.toStyledString().c_str());
    return RC::INDEX_FIELD_ERROR;
  }

  std::vector<const FieldMeta *> fields;
  for(size_t i = 0; i < fields_value.size();++i) {
    Json::Value default_val;
    auto name = fields_value.get(i, default_val).asString();
    auto field = table.field(name.c_str());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(field);
  }
  bool unique_index = (0 == strcmp(unique.asCString(), "true")); 
  return index.init(name_value.asCString(), fields, unique_index);
}

const char *IndexMeta::name() const { return name_.c_str(); }

const std::vector<string>& IndexMeta::field() const { return fields_; }

void IndexMeta::desc(ostream &os) const { os << "index name=" << name_ << ", field";
  os << (fields_.size() > 0 ? "s=" : "=");
  for (size_t i = 0; i < fields_.size(); i++) {
    if (i > 0)
      os << ",";
    os << fields_[i];
  } 
}