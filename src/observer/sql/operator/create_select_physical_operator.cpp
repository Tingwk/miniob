#include "sql/operator/create_select_physical_operator.h"
#include "storage/trx/trx.h"
#include "sql/executor/create_table_executor.h"
#include "storage/db/db.h"
RC CreateSelectPhysicalOperator::open(Trx* trx) {
  RC rc;
  if (!children_.empty()) {
    auto child = children_[0].get();
    rc = child->open(trx);
    if (OB_FAIL(rc)) {
      LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
      return rc;
    }
  }
  // create table.
  auto table_meta = suq_query_table_->table_meta();
  TupleSchema *schema = children_[0]->schema();
  std::vector<AttrInfoSqlNode> infos(table_meta.field_num());
  auto field_metas = *(table_meta.field_metas());
  for (size_t k = 0; k < field_metas.size(); ++k) {
    infos[k].length = field_metas[k].len();
    infos[k].name = string(field_metas[k].name());
    infos[k].nullable = field_metas[k].nullable();
    infos[k].type = field_metas[k].type();
  }
  auto db = suq_query_table_->db();
  rc = db->create_table(new_table_name_.c_str(), infos, table_meta.storage_format());
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot create new table");
    return rc;
  }
  return RC::SUCCESS;
}

RC CreateSelectPhysicalOperator::next() {
  RC rc;
  auto table = suq_query_table_->db()->find_table(new_table_name_.c_str());
  if (table == nullptr) {
    return RC::INTERNAL;
  }
  auto schema = children_[0]->schema();
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    
  }
  return RC::SUCCESS;
}

RC CreateSelectPhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}