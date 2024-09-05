#include "sql/stmt/create_select_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/db/db.h"
RC CreateSelectStmt::create(Db *db, CreateSelectSqlNode& cs, Stmt* &stmt) {
  RC rc;
  Stmt *sub_query_stmt; 
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  auto tb = db->find_table(cs.relation_name.c_str());
  if (tb != nullptr) {
    LOG_WARN("create select, but table %s already exists", cs.relation_name.c_str());
    return RC::INTERNAL;
  }
  if (rc = SelectStmt::create(db, cs.sub_query->selection, sub_query_stmt); rc != RC::SUCCESS) {
    LOG_WARN("cannot create sub query in func: CreateSelectStmt::create(Db *db, CreateSelectSqlNode& cs, Stmt* stmt)");
    return rc;
  }
  auto select_stmt =  static_cast<SelectStmt*>(sub_query_stmt);
  if (select_stmt->tables().size() != 1) {
    LOG_WARN("create select's subquery shall reference only one relation");
    return RC::INTERNAL;
  }
  // std::vector<AttrInfoSqlNode> infos;
  // for
  stmt = new CreateSelectStmt(cs.relation_name, select_stmt->tables()[0], sub_query_stmt);
  return RC::SUCCESS;
}