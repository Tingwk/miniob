#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"
#include "sql/parser/parse_defs.h"
RC DropTableStmt::create(Db* db, DropTableSqlNode& node, Stmt*& stmt) {
  if (db->find_table(node.relation_name.c_str()) == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), node.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  stmt = new DropTableStmt(node.relation_name);
  return RC::SUCCESS;
}