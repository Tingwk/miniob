/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include <common/log/log.h>

#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/group_by_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/create_select_logical_operator.h"

#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/create_select_stmt.h"
#include "sql/expr/expression_iterator.h"
#include "sql/expr/sub_query_logical_expr.h"
#include "sql/expr/sub_query_physical_expr.h"
#include "sql/expr/value_list_expression.h"

using namespace std;
using namespace common;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator) {
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);

      rc = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);

      rc = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);

      rc = create_plan(insert_stmt, logical_operator);
    } break;
    
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt*>(stmt);
      rc = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::ORDER_BY: {
      OrderByStmt *order_stmt = static_cast<OrderByStmt*>(stmt);
      rc = create_plan(order_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);

      rc = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);

      rc = create_plan(explain_stmt, logical_operator);
    } break;

    case StmtType::CREATE_SELECT: {
      auto cs_stmt = static_cast<CreateSelectStmt*>(stmt);
      rc = create_plan(cs_stmt, logical_operator);
    } break;

    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CreateSelectStmt *cs_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  RC rc;
  std::unique_ptr<LogicalOperator> query_oper;
  if (rc = create(cs_stmt->query(), query_oper); rc != RC::SUCCESS) {
    return rc;
  }
  auto cs_logical_oper = new CreateSelectLogicalOperator(cs_stmt->table_name(), std::move(query_oper), cs_stmt->using_infos(), cs_stmt->infos());
  logical_operator.reset(cs_logical_oper);
  return RC::SUCCESS;
} 

RC LogicalPlanGenerator::create_plan(OrderByStmt *order_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  if (order_stmt != nullptr) {
    LogicalOperator *oper = new OrderByLogicalOperator(std::move(order_stmt->units()));
    logical_operator.reset(oper);
  }
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  unique_ptr<LogicalOperator> *last_oper = nullptr;

  unique_ptr<LogicalOperator> table_oper(nullptr);
  last_oper = &table_oper;

  const std::vector<Table *> &tables = select_stmt->tables();
  int k{0};
  for (Table *table : tables) {

    unique_ptr<TableGetLogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_ONLY));
    auto filter_units = select_stmt->filter_stmt()->filter_units();
    std::vector<std::unique_ptr<Expression>> predicates;
    for (size_t i = 0; i < filter_units.size(); i++) {
      auto unit = filter_units[i];
      if (unit->left().value_type == ValueType::ATTRIBUTE && unit->left().field.table() == table && unit->right().value_type == ValueType::CONSTANT) {
        std::unique_ptr<FieldExpr> left(new FieldExpr(unit->left().field));
        std::unique_ptr<ValueExpr> right(new ValueExpr(unit->right().value));
        std::unique_ptr<ComparisonExpr> cmp_expr (new ComparisonExpr(unit->comp(), std::move(left), std::move(right)));
        predicates.emplace_back(std::move(cmp_expr));
        select_stmt->filter_stmt()->set_flag(i, false);
      } else if (unit->right().value_type == ValueType::ATTRIBUTE && unit->right().field.table() == table && unit->left().value_type == ValueType::CONSTANT) {
        std::unique_ptr<ValueExpr> left (new ValueExpr(unit->left().value));
        std::unique_ptr<FieldExpr> right(new FieldExpr(unit->right().field));
        std::unique_ptr<ComparisonExpr> cmp_expr (new ComparisonExpr(unit->comp(), std::move(left), std::move(right)));
        predicates.emplace_back(std::move(cmp_expr));
        select_stmt->filter_stmt()->set_flag(i, false);
      } else  if (unit->left().value_type == ValueType::ATTRIBUTE && unit->left().field.table() == table && unit->right().value_type == ValueType::SUB_QUERY) {
        std::unique_ptr<FieldExpr> left(new FieldExpr(unit->left().field));
        std::unique_ptr<LogicalOperator> sub_query_logical_oper;
        [[maybe_unused]]auto sub_selete_stmt = static_cast<SelectStmt*>(unit->right().sub_query);
        auto rc = create_plan(sub_selete_stmt, sub_query_logical_oper);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannont create sub query");
          return rc;
        }
        std::unique_ptr<SubQueryLogicalExpr> right(new SubQueryLogicalExpr(std::move(sub_query_logical_oper)));
        right->set_with_table_name(sub_selete_stmt->tables().size() > 1);
        std::unique_ptr<ComparisonExpr> cmp_expr (new ComparisonExpr(unit->comp(), std::move(left), std::move(right)));
        predicates.emplace_back(std::move(cmp_expr));
        select_stmt->filter_stmt()->set_flag(i, false);
      } else if (unit->left().value_type == ValueType::ATTRIBUTE && unit->left().field.table() == table && unit->right().value_type == ValueType::VALUE_LIST) {
        std::unique_ptr<FieldExpr> left(new FieldExpr(unit->left().field));
        std::unique_ptr<ValueListExpr> right(new ValueListExpr(unit->right().values));
        std::unique_ptr<ComparisonExpr> cmp_expr(new ComparisonExpr(unit->comp(), std::move(left), std::move(right)));
        predicates.emplace_back(std::move(cmp_expr));
        select_stmt->filter_stmt()->set_flag(i, false);
      }
    }
    if (!predicates.empty()) {
      // check whether cmp_expr is empty or not,
      table_get_oper->set_predicates(std::move(predicates));
    }
    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      FilterStmt* filter = nullptr;
      filter = select_stmt->on_conditions_at(k);
      ++k;
      std::vector<std::unique_ptr<Expression>> cmp_exprs;
      filter->filter_expression(cmp_exprs);
      join_oper->set_predicates(std::move(cmp_exprs));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(*last_oper));
    }

    last_oper = &predicate_oper;
  }

  unique_ptr<LogicalOperator> group_by_oper;
  rc = create_group_by_plan(select_stmt, group_by_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
    return rc;
  }

  if (group_by_oper) {
    if (*last_oper) {
      group_by_oper->add_child(std::move(*last_oper));
    }

    last_oper = &group_by_oper;
  }
  unique_ptr<LogicalOperator> order_by_oper;
  if (select_stmt->order_stmt() != nullptr) {
    rc = create(select_stmt->order_stmt(), order_by_oper);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to create group by logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }
  if (order_by_oper) {
    if (*last_oper) {
      order_by_oper->add_child(std::move(*last_oper));
    }
    last_oper = &order_by_oper;
  }
  auto project_oper = make_unique<ProjectLogicalOperator>(std::move(select_stmt->query_expressions()));
  if (*last_oper) {
    project_oper->add_child(std::move(*last_oper));
  }

  logical_operator = std::move(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator) {
  std::vector<unique_ptr<Expression>> cmp_exprs;
  std::vector<FilterUnit*> sub_queries;
  std::vector<FilterUnit*> value_list;
  filter_stmt->filter_sub_queries(sub_queries);
  filter_stmt->filter_expression(cmp_exprs);
  filter_stmt->filter_value_list(value_list);
  for(auto unit : sub_queries) {
    std::unique_ptr<LogicalOperator> sub_query;
    auto select_stmt = static_cast<SelectStmt*>(unit->right().sub_query);
    auto rc = create_plan(select_stmt, sub_query);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot create sub_query");
      return rc;
    }
    std::unique_ptr<FieldExpr> left(new FieldExpr(unit->left().field));
    std::unique_ptr<SubQueryLogicalExpr> right(new SubQueryLogicalExpr(std::move(sub_query)));
    right->set_with_table_name(select_stmt->tables().size() > 1);
    auto cmp_expr = new ComparisonExpr(unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }
  for (auto unit : value_list) {
    std::unique_ptr<FieldExpr> left(new FieldExpr(unit->left().field));
    std::unique_ptr<ValueListExpr> right(new ValueListExpr(unit->right().values));
    auto cmp_expr = new ComparisonExpr(unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }
  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt* update_stmt, std::unique_ptr<LogicalOperator> &logical_operator) {
  std::unique_ptr<LogicalOperator> *last_oper;
  std::unique_ptr<LogicalOperator> table_oper;
  std::unique_ptr<LogicalOperator> predicate_oper;
  last_oper = &table_oper;
  table_oper.reset(new TableGetLogicalOperator(update_stmt->table(), ReadWriteMode::READ_WRITE));
  auto rc = create_plan(update_stmt->filter(), predicate_oper);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }
  if (predicate_oper) {
    if (*last_oper) {
      predicate_oper->add_child(std::move(table_oper));
    }
    last_oper = &predicate_oper;
  }
  std::vector<std::unique_ptr<LogicalOperator>> sub_queries;
  std::vector<std::unique_ptr<SubQueryLogicalExpr>> sub_query_logical_exprs; 
  std::vector<size_t> indices;
  size_t k = 0;
  for (auto & unit : update_stmt->assignments()) {
    if (unit->new_value_type == ValueType::SUB_QUERY) {
      std::unique_ptr<LogicalOperator> query;
      [[maybe_unused]]auto sub_selete_stmt = static_cast<SelectStmt*>(unit->sub_query);
      create_plan(sub_selete_stmt, query);
      indices.emplace_back(k);
      std::unique_ptr<SubQueryLogicalExpr> logical_expr (new SubQueryLogicalExpr(std::move(query)));
      logical_expr->set_with_table_name(sub_selete_stmt->tables().size() > 1);
      sub_query_logical_exprs.emplace_back(std::move(logical_expr));
    }
    ++k;
  }
  
  UpdateLogicalOperator *update_oper = new UpdateLogicalOperator(update_stmt->table(), std::move(update_stmt->assignments()), std::move(indices), std::move(sub_query_logical_exprs), update_stmt->field_meta());
  update_oper->add_child(std::move(*last_oper));
  logical_operator.reset(update_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                      *table       = delete_stmt->table();
  FilterStmt                 *filter_stmt = delete_stmt->filter_stmt();
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, ReadWriteMode::READ_WRITE));

  unique_ptr<LogicalOperator> predicate_oper;

  RC rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> child_oper;

  Stmt *child_stmt = explain_stmt->child();

  RC rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}

RC LogicalPlanGenerator::create_group_by_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  vector<unique_ptr<Expression>> &group_by_expressions = select_stmt->group_by();
  vector<Expression *> aggregate_expressions;
  vector<unique_ptr<Expression>> &query_expressions = select_stmt->query_expressions();
  function<RC(std::unique_ptr<Expression>&)> collector = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      expr->set_pos(aggregate_expressions.size() + group_by_expressions.size());
      aggregate_expressions.push_back(expr.get());
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, collector);
    return rc;
  };

  function<RC(std::unique_ptr<Expression>&)> bind_group_by_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    for (size_t i = 0; i < group_by_expressions.size(); i++) {
      auto &group_by = group_by_expressions[i];
      if (expr->type() == ExprType::AGGREGATION) {
        break;
      } else if (expr->equal(*group_by)) {
        expr->set_pos(i);
        continue;
      } else {
        rc = ExpressionIterator::iterate_child_expr(*expr, bind_group_by_expr);
      }
    }
    return rc;
  };

 bool found_unbound_column = false;
  function<RC(std::unique_ptr<Expression>&)> find_unbound_column = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      // do nothing
    } else if (expr->pos() != -1) {
      // do nothing
    } else if (expr->type() == ExprType::FIELD) {
      found_unbound_column = true;
    }else {
      rc = ExpressionIterator::iterate_child_expr(*expr, find_unbound_column);
    }
    return rc;
  };
  

  for (unique_ptr<Expression> &expression : query_expressions) {
    bind_group_by_expr(expression);
  }

  for (unique_ptr<Expression> &expression : query_expressions) {
    find_unbound_column(expression);
  }

  // collect all aggregate expressions
  for (unique_ptr<Expression> &expression : query_expressions) {
    collector(expression);
  }

  if (group_by_expressions.empty() && aggregate_expressions.empty()) {
    // 既没有group by也没有聚合函数，不需要group by
    return RC::SUCCESS;
  }

  if (found_unbound_column) {
    LOG_WARN("column must appear in the GROUP BY clause or must be part of an aggregate function");
    return RC::INVALID_ARGUMENT;
  }

  // 如果只需要聚合，但是没有group by 语句，需要生成一个空的group by 语句

  auto group_by_oper = make_unique<GroupByLogicalOperator>(std::move(group_by_expressions),
                                                           std::move(aggregate_expressions));
  logical_operator = std::move(group_by_oper);
  return RC::SUCCESS;
}