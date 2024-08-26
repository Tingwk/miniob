#pragma once

#include "sql/operator/physical_operator.h"
class UpdateStmt;

class UpdatePhysicalOperator : public PhysicalOperator {
public:
  UpdatePhysicalOperator(Table* t, const Value* values, int value_amount, const FieldMeta* meta);

  PhysicalOperatorType type() const override {return PhysicalOperatorType::UPDATE;}
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Table* table() {return table_;}
  const Value* values() const {
    return &values_;
  }
  int value_amount() {return value_amount_;}
  const FieldMeta* field_meta() {return meta_;}
  Tuple *current_tuple() override { 
    return nullptr; 
  }
private:
  RowTuple tuple_;
  Table* table_;
  Value values_;
  int value_amount_;
  const FieldMeta* meta_;
};