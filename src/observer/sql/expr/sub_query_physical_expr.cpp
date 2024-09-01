#include "sql/expr/sub_query_physical_expr.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/expr/sub_query_physical_expr.h"
#include "sql/expr/tuple.h"

RC SubQueryPhysicalExpr::do_sub_query(Trx* trx) {
  auto proj_phy_oper = static_cast<ProjectPhysicalOperator*>(physical_oper_.get());
  TupleSchema schema;
  proj_phy_oper->tuple_schema(schema);
  proj_phy_oper->open(trx);
  RC rc;
  while ((rc = proj_phy_oper->next()) == RC::SUCCESS) {
    auto cur_tuple = proj_phy_oper->current_tuple();
    Value value;
    rc = cur_tuple->cell_at(0, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get tuple cell value. rc=%s", strrc(rc));
      return rc;
    }
    values_.push_back(value);
  }
  proj_phy_oper->close();
  return RC::SUCCESS;
}