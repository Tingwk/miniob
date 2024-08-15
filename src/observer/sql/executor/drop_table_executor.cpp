
#include "sql/executor/drop_table_executor.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"
RC DropTableExecutor::execute(SQLStageEvent *sql_event) {
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_TABLE,
      "create table executor can not run this command: %d",
      static_cast<int>(stmt->type()));
  auto dt_stmt = static_cast<DropTableStmt*>(stmt);
  auto tb_name = dt_stmt->table_name().c_str();
  auto rc = session->get_current_db()->drop_table(tb_name);
  return rc;
}