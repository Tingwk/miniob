
#pragma once

#include "sql/operator/logical_operator.h"

class UpdateLogicalOperator : public LogicalOperator{
 public:
  UpdateLogicalOperator(Table*, const Value*,int ,const FieldMeta*);
  virtual ~UpdateLogicalOperator() = default;
  LogicalOperatorType type() const override {return LogicalOperatorType::UPDATE;}
  Table* table() {return table_;}
  const Value* value() {return values_;}
  int value_count() {return value_amount_;}
  const FieldMeta * field_meta() {return field_meta_;}
 private:
  Table *table_        = nullptr;
  const Value *values_       = nullptr;
  int    value_amount_ = 0;
  const FieldMeta *field_meta_;
  
};