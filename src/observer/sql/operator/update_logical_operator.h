
#pragma once

#include "sql/operator/logical_operator.h"
#include <vector>
class AssignmentUnit;
class SubQueryLogicalExpr;

class UpdateLogicalOperator : public LogicalOperator{
 public:
  UpdateLogicalOperator(Table*, const Value*,int ,const FieldMeta*);
  UpdateLogicalOperator(Table*, std::vector<std::unique_ptr<AssignmentUnit>>&&  assignments, std::vector<size_t>&& indices, std::vector<std::unique_ptr<SubQueryLogicalExpr>>&& queries ,const FieldMeta*);
  virtual ~UpdateLogicalOperator() = default;
  LogicalOperatorType type() const override {return LogicalOperatorType::UPDATE;}
  Table* table() {return table_;}
  const Value* value() {return values_;}
  int value_count() {return value_amount_;}
  const FieldMeta * field_meta() {return field_meta_;}
  std::vector<std::unique_ptr<SubQueryLogicalExpr>>& sub_queries() { return sub_queries_; }
  std::vector<size_t>& indices() { return sub_query_indices_; }
  std::vector<std::unique_ptr<AssignmentUnit>>& assignments() { return assignments_; }
 private:
  Table *table_        = nullptr;
  const Value *values_       = nullptr;
  int    value_amount_ = 0;
  std::vector<std::unique_ptr<AssignmentUnit>> assignments_;
  std::vector<size_t> sub_query_indices_;
  std::vector<std::unique_ptr<SubQueryLogicalExpr>> sub_queries_;
  const FieldMeta *field_meta_;
  
};