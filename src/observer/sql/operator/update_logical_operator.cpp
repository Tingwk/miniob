
#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table*t, const Value* v,int count,const FieldMeta* meta)
:table_(t), values_(v), value_amount_(count), field_meta_(meta) {}