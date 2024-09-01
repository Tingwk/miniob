/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2022/6/27.
//

#include "sql/operator/predicate_physical_operator.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"
#include "storage/record/record.h"
#include "sql/expr/sub_query_physical_expr.h"
#include "sql/expr/expression.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(std::unique_ptr<Expression> expr) : expression_(std::move(expr))
{
  ASSERT(expression_->value_type() == AttrType::BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  auto rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  auto expressions = static_cast<ConjunctionExpr*>(expression_.get());
  for (auto &expr : expressions->children()) {
    if (expr->type() == ExprType::COMPARISON && static_cast<ComparisonExpr*>(expr.get())->right()->type() == ExprType::SUB_QUERY_PHYSICAL_EXPR) {
      auto cmp_expr = static_cast<ComparisonExpr*>(expr.get());
      auto sub_query_expr = static_cast<SubQueryPhysicalExpr*>(cmp_expr->right().get());
      sub_query_expr->do_sub_query(trx);
      bool flag = cmp_expr->comp() != CompOp::EXISTS_ && cmp_expr->comp() != CompOp::NOT_EXISTS_ && cmp_expr->comp() != CompOp::IN_ && cmp_expr->comp() != CompOp::NOT_IN_;
      if (flag && sub_query_expr->reuslt_num() > 1) {
        return RC::INTERNAL;
      }
    }
  }
  return RC::SUCCESS;
}

RC PredicatePhysicalOperator::next()
{
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    Value value;
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (value.get_boolean()) {
      return rc;
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }

RC PredicatePhysicalOperator::tuple_schema(TupleSchema &schema) const
{
  return children_[0]->tuple_schema(schema);
}
