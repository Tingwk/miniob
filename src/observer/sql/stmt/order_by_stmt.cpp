
#include "sql/stmt/order_by_stmt.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"



RC OrderByStmt::create(std::unordered_map<string,Table*>& name_to_tables , std::vector<OrderBySqlNode>& order_by_specs, OrderByStmt *&stmt) {
  if (order_by_specs.empty()) {
    return RC::SUCCESS;
  }
  std::vector<std::unique_ptr<OrderByUnit>> units;
  for (auto & order_by : order_by_specs) {
    Table * table = nullptr;
    if (name_to_tables.size() > 1) {
      auto iter = name_to_tables.find(order_by.table_name);
      if (iter == name_to_tables.end()) {
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }
    } else {
      table = name_to_tables.begin()->second;
    }
    auto meta = table->table_meta().field(order_by.attribute_name.c_str());
    if (meta == nullptr) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    auto  unit = std::make_unique<OrderByUnit>(table, meta, order_by.asc);
    units.emplace_back(std::move(unit));
  }
  stmt =  new OrderByStmt(std::move(units));
  return RC::SUCCESS;
}