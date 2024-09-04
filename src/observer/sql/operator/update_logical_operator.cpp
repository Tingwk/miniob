
#include "sql/operator/update_logical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "sql/expr/sub_query_logical_expr.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table*t, const Value* v,int count,const FieldMeta* meta)
:table_(t), values_(v), value_amount_(count), field_meta_(meta) {}

UpdateLogicalOperator::UpdateLogicalOperator(Table*t, std::vector<std::unique_ptr<AssignmentUnit>>&&  assignments, std::vector<size_t>&& indices, std::vector<std::unique_ptr<SubQueryLogicalExpr>>&& queries ,const FieldMeta*) 
: table_(t), assignments_(std::move(assignments)), sub_query_indices_(std::move(indices)),sub_queries_(std::move(queries)), field_meta_(field_meta())
{}