#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
class LogicalOperator;


class SubQueryLogicalExpr : public Expression {
 public:
  SubQueryLogicalExpr() = default;
//  SubQueryLogicalExpr(const SubQueryLogicalExpr& other): sub_query_(expression_factory(other.sub_query_.get())) {}
  SubQueryLogicalExpr(std::unique_ptr<LogicalOperator>&& oper) : sub_query_(std::move(oper)) {}
  virtual ~SubQueryLogicalExpr() = default;
  RC get_value(const Tuple &tuple, Value &value) const override { return RC::INVALID_ARGUMENT;}
  AttrType value_type() const override { return AttrType::UNDEFINED; }
  ExprType type() const override { return ExprType::SUB_QUERY_LOGICAL_EXPR; }
  bool with_table_name() const {return with_table_name_;}
  void set_with_table_name(bool f) {with_table_name_ = f;}
  std::unique_ptr<LogicalOperator>& sub_query()  { return sub_query_;}
 private:
  std::unique_ptr<LogicalOperator> sub_query_;
  bool with_table_name_ = false;
};