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
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/join_physical_operator.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/table_scan_physical_operator.h"

NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator() {}

RC NestedLoopJoinPhysicalOperator::open(Trx *trx) {
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc         = RC::SUCCESS;
  left_         = children_[0].get();
  right_        = children_[1].get();
  right_closed_ = true;
  round_done_   = true;

  rc   = left_->open(trx);
  trx_ = trx;
  return rc;
}

RC NestedLoopJoinPhysicalOperator::next() {
  if (finished) {
    return RC::RECORD_EOF;
  }
  RC rc;
  while (true) {

    if (left_tuple_ == nullptr) {
      rc = left_next();
      if (rc != RC::SUCCESS) {
        // left is empty
        finished = true;
        return rc;
      }
      rc = right_next();
      if (rc != RC::SUCCESS) {
        // right table is empty.
        finished = true;
        return RC::RECORD_EOF;
      }
    } else {
      rc = right_next();
      if (rc != RC::SUCCESS) {
        rc = left_next();
        if (rc != RC::SUCCESS) {
          finished = true;
          return RC::RECORD_EOF;
        }
        if (RC::SUCCESS != right_next()) {
          finished = true;
          return RC::RECORD_EOF;
        }
      }
    }
    bool loop  = false;
    for (auto &pred : predicates_) {
      ASSERT(pred->type() == ExprType::COMPARISON, "the condition that pred is comparsion expression must be held.");
      ComparisonExpr* cmp_pred = static_cast<ComparisonExpr*>(pred.get());
      std::unique_ptr<Expression>& left = cmp_pred->left();
      std::unique_ptr<Expression>& right = cmp_pred->right();
      bool result = false;
      Value left_val, right_val;
      if (left->type() == ExprType::FIELD && right->type() == ExprType::FIELD) {
        auto left_field = static_cast<FieldExpr*>(left.get());
        auto right_field = static_cast<FieldExpr*>(right.get());
        
        TupleCellSpec t1(left_field->field().table_name(), left_field->field().field_name());
        TupleCellSpec t2(right_field->field().table_name(), right_field->field().field_name());
        int left_index = 0, right_index = 0;
        auto left_schema = left_->schema();
        auto right_schema = right_->schema();
        if (!find_position(left_schema, t1, left_index)) {
          find_position(right_schema, t1, left_index);
          find_position(left_schema, t2, right_index);
          joined_tuple_.left_tuple()->cell_at(right_index, right_val);
          joined_tuple_.right_tuple()->cell_at(left_index, left_val);
        } else {
          joined_tuple_.left_tuple()->cell_at(left_index, left_val);
          joined_tuple_.right_tuple()->find_cell(t2, right_val);
        }
        // now we can make a comparison.
      } else if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
        int index;
        auto left_field = static_cast<FieldExpr*>(left.get());
        TupleCellSpec spec(left_field->field().table_name(), left_field->field().field_name());
        TupleSchema * schema = left_->schema();
        if (!find_position(schema, spec, index)) {
          schema = right_->schema();
          find_position(schema, spec, index);
          joined_tuple_.right_tuple()->cell_at(index, left_val);
        } else {
          joined_tuple_.left_tuple()->cell_at(index, left_val);
        }
        static_cast<ValueExpr*>(right.get())->get_value(right_val);
      } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
        int index;
        auto field = static_cast<FieldExpr*>(right.get());
        TupleCellSpec spec(field->field().table_name(), field->field().field_name());
        TupleSchema * schema = left_->schema();
        if (!find_position(schema, spec, index)) {
          schema = right_->schema();
          find_position(schema, spec, index);
          joined_tuple_.right_tuple()->cell_at(index, left_val);
        } else {
          joined_tuple_.left_tuple()->cell_at(index, left_val);
        }
        static_cast<ValueExpr*>(left.get())->get_value(right_val);
      } else {
        auto left_val_expr = static_cast<ValueExpr*>(left.get());
        auto right_val_expr = static_cast<ValueExpr*>(right.get());
        left_val_expr->get_value(left_val);
        right_val_expr->get_value(right_val);
      }
      cmp_pred->compare_value(left_val, right_val, result);
      if (!result) {
        loop = true;
        break;
      }
    }
    if (!loop) {
      return RC::SUCCESS;
    }
    // otherwise the conditions don't hold.
  }
}

RC NestedLoopJoinPhysicalOperator::close() {
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  if (!right_closed_) {
    rc = right_->close();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to close right oper. rc=%s", strrc(rc));
    } else {
      right_closed_ = true;
    }
  }
  return rc;
}

Tuple *NestedLoopJoinPhysicalOperator::current_tuple() { return &joined_tuple_; }

RC NestedLoopJoinPhysicalOperator::left_next() {
  RC rc = RC::SUCCESS;
  rc    = left_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  left_tuple_ = left_->current_tuple();
  joined_tuple_.set_left(left_tuple_);
  return rc;
}

RC NestedLoopJoinPhysicalOperator::right_next()
{
  RC rc = RC::SUCCESS;
  if (round_done_) {
    if (!right_closed_) {
      rc = right_->close();
      right_closed_ = true;
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }

    rc = right_->open(trx_);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    right_closed_ = false;

    round_done_ = false;
  }

  rc = right_->next();
  if (rc != RC::SUCCESS) {
    if (rc == RC::RECORD_EOF) {
      round_done_ = true;
    }
    return rc;
  }

  right_tuple_ = right_->current_tuple();
  joined_tuple_.set_right(right_tuple_);
  return rc;
}

void NestedLoopJoinPhysicalOperator::set_schema(const TupleSchema* t1) {
  for (int j = 0; j < t1->cell_num(); j++) { 
    schemas_.append_cell(t1->cell_at(j));
  }
}

bool NestedLoopJoinPhysicalOperator::find_position(TupleSchema* schemas, TupleCellSpec& spec, int& index) {
  for (int i = 0; i < schemas->cell_num(); i++) {
    if (spec == schemas->cell_at(i)) {
      index = i;
      return true;
    }
  }
  return false;
}