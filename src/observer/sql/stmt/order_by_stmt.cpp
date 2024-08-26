
#include "sql/stmt/order_by_stmt.h"
#include "storage/table/table.h"
#include "storage/table/table_meta.h"



RC OrderByStmt::create(std::unordered_map<string,Table*>& name_to_tables , std::vector<OrderBySqlNode>& order_by_specs, OrderByStmt *&stmt) {
  std::vector<std::unique_ptr<OrderByUnit>> units;
  for (auto & order_by : order_by_specs) {
    auto iter = name_to_tables.find(order_by.table_name);
    if (iter == name_to_tables.end()) {
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    auto meta = iter->second->table_meta().field(order_by.attribute_name.c_str());
    if (meta == nullptr) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    auto  unit = std::make_unique<OrderByUnit>(iter->second, meta, order_by.asc);
    units.emplace_back(std::move(unit));
  }
  stmt =  new OrderByStmt(std::move(units));
  return RC::SUCCESS;
}