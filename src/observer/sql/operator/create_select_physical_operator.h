#pragma once

#include "sql/operator/physical_operator.h"

class CreateSelectPhysicalOperator : public PhysicalOperator {
 public:
  RC close() override { return RC::SUCCESS;}
  PhysicalOperatorType type() const override { return PhysicalOperatorType::CREATE_SELECT; }
 private:
  
};