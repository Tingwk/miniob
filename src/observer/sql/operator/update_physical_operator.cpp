#include "sql/operator/update_physical_operator.h"
#include "sql/expr/tuple.h"
#include <cstring>
UpdatePhysicalOperator::UpdatePhysicalOperator(Table* t, const Value* values, int value_amount, const FieldMeta* meta) 
: tuple_(),table_(t), values_(values), value_amount_(value_amount),meta_(meta) {}

RC UpdatePhysicalOperator::open(Trx *trx) {
  if (children_.empty()) {
    return RC::SUCCESS;
  }
  auto child = children_[0].get();
  auto rc = child->open(trx);
  if (OB_FAIL(rc)) {
    LOG_ERROR("failed to open update phy operator's child operator:%s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next() {
  RC rc = RC::SUCCESS;
  while ((rc = children_[0]->next()) == RC::SUCCESS) {
    if (OB_SUCC(rc)) {
      auto tuple = static_cast<RowTuple*>(children_[0]->current_tuple());
      auto record = tuple->record();
      memcpy((void*)(record.data() + field_meta()->offset()), (void*)values_->data(), field_meta()->len());
    }
  }
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}