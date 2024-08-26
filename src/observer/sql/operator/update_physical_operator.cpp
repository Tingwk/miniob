#include "sql/operator/update_physical_operator.h"
#include "sql/expr/tuple.h"
#include "storage/index/index.h"
#include "sql/parser/value.h"
#include <string.h>
#include <cstring>

UpdatePhysicalOperator::UpdatePhysicalOperator(Table* t, const Value* values, int value_amount, const FieldMeta* meta) 
: tuple_(),table_(t), values_(), value_amount_(value_amount),meta_(meta) {
  switch (meta_->type()) {
    case AttrType::DATES: 
      int val;
      date_str_to_int(values->get_string(), val);
      values_.set_date(val);
      break;
    case AttrType::CHARS:
      values_.set_string(values->get_string().c_str());
      break;
    case AttrType::INTS:
      values_.set_int(values->get_int());
      break;
    case AttrType::FLOATS:
      values_.set_float(values->get_float());
      break;
    case AttrType::BOOLEANS:
      values_.set_boolean(values->get_boolean());
      break;
    default:
      break;
  }
}

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
      // for (auto index : table_->table_meta().index())12345
      table_->update_indexes(meta_->name(), record, meta_, &values_);
      
      auto field_len = meta_->len();
      // if (meta_->type() == AttrType::CHARS && values_->length() < field_len) {
      //   field_len = values_->length() + 1;
      // }
      std::memcpy((void*)(record.data() + field_meta()->offset()), (void*)values_.data(), field_len);
      // if (index != nullptr) {
      //   index->insert_entry(record.data(), &record.rid());
      // }
    }
  }
  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}