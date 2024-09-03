
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp) {
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        DATE_T
        INNER 
        JOIN
        STRING_T
        FLOAT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        EQ
        ORDER
        ASC
        LT
        GT
        LE
        GE
        NE
        NOT
        LIKE
        IN
        EXISTS
        UNIQUE
        ROUND
        LENGTH
        DATA_FORMAT
        null
        IS

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  ConditionSqlNode *                         condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<OrderBySqlNode>*               order_by_list;
  std::vector<Value> *                       value_list;
  std::vector<ConditionSqlNode> *            condition_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string>*                  id_list_type;
//  std::vector<std::string> *                 relation_list;
  RelListSqlNode*                            relation_list;
  char *                                     string;
  int                                        number;
  int *                                      number_ptr;
  float                                      floats;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <condition>           subquery
%type <value>               value
%type <value>               value_with_null
%type <id_list_type>        id_list
%type <number>              number
// %type <string>              relation
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <number_ptr>          null_def
%type <value_list>          value_list
%type <value_list>          value_with_null_list
%type <condition_list>      where
%type <order_by_list>       order_by
%type <order_by_list>       order_list
%type <condition_list>      condition_list
%type <condition_list>      subquery_value_list
%type <string>              storage_format
%type <relation_list>       rel_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.unique = false;
      if ($8 != nullptr) {
        create_index.attribute_names.swap(*$8);
        delete $8;
      }
      create_index.attribute_names.emplace(create_index.attribute_names.begin(), $7);
      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;
      create_index.unique = true;
      if ($9 != nullptr) {
        create_index.attribute_names.swap(*$9);
        delete $9;
      }
      create_index.attribute_names.emplace(create_index.attribute_names.begin(), $8);
      free($4);
      free($6);
      free($8);
    }
    ;
id_list:
  /* empty */
  {
    $$ = nullptr;
  }
  | COMMA ID id_list {
    if ($3 != nullptr) {
      $$ = $3;
    } else {
      $$ = new std::vector<std::string>();
    }
    $$->emplace($$->begin(), $2);
    free($2);
  }
  ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      if ($6 != nullptr) {
        $$->nullable = (*$6 == 0);
        delete $6;
      } else {
        $$->nullable = false;
      }
      free($1);
    }
    | ID type null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      if ($3 != nullptr) {
        $$->nullable = (*$3 == 0);
        delete $3;
      } else {
        $$->nullable = false;
      }
      free($1);
    }
    ;
null_def:
    /* empty */
    {
      $$ = nullptr;
    }
    | null {
      $$ = new int(0);
    }
    | NOT null {
      $$ = new int(1);
    }
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | DATE_T { $$ = static_cast<int>(AttrType::DATES); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value_with_null value_with_null_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;
value_with_null_list:
  /* empty */
  {
    $$ = nullptr;
  }
  | COMMA value_with_null value_with_null_list  { 
    if ($3 != nullptr) {
      $$ = $3;
    } else {
      $$ = new std::vector<Value>;
    }
    $$->emplace_back(*$2);
    delete $2;
  };
value_with_null:
  value  {
    $$ = $1;
  }
  | null {
    $$ = new Value();
    $$->set_null();
  }
  ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    ;
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value_with_null where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_name = $4;
      $$->update.value = *$6;
      if ($7 != nullptr) {
        $$->update.conditions.swap(*$7);
        delete $7;
      }
      free($2);
      free($4);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM ID rel_list where group_by order_by
    {
      std::cout << "select_stmt\n";
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.expressions.swap(*$2);
        delete $2;
      }

      if ($5 != nullptr) {
        $$->selection.relations.swap((*$5).relations);
        $$->selection.joins.swap((*$5).joins);
        delete $5;
      }
      $$->selection.relations.emplace($$->selection.relations.begin(), $4);
      free($4);
      
      if ($6 != nullptr) {
        //cout << (*$6)[0].right_sub_queries << '\n';
        $$->selection.conditions.swap(*$6);
        delete $6;
        //cout << ($$->selection.conditions)[0].right_sub_queries << '\n';
      }

      if ($7 != nullptr) {
        $$->selection.group_by.swap(*$7);
        delete $7;
      }
      if ($8 != nullptr) {
        $$->selection.order_by.swap(*$8);
        delete $8;
      }
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      $$->emplace($$->begin(), $1);
    }
    | ID LBRACE RBRACE {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      Expression *expr = new ErrorExpr();
      $$->emplace_back(expr);
      free($1);
    }
    | ID LBRACE RBRACE COMMA expression_list {
      if ($5) {
        delete $5;
      }
      $$ = new std::vector<std::unique_ptr<Expression>>;
      Expression *expr = new ErrorExpr();
      $$->emplace_back(expr);
      free($1);
    }

    | ID LBRACE expression RBRACE {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      auto expr = create_aggregate_expression($1, $3, sql_string, &@$);
      $$->emplace_back(expr);
      free($1);
    }
    | ID LBRACE expression RBRACE COMMA expression_list  {
      $$ = $6;
      int start = @1.first_column;
      int end = @4.last_column;
      auto expr = create_aggregate_expression($1, $3, sql_string, &@$);
      expr->set_name(std::string(sql_string+ start, end- start + 1));
      free($1);
      $$->emplace($$->begin(), expr);
    }
    | ID LBRACE expression_list RBRACE {
      delete $3;
      $$ = new std::vector<std::unique_ptr<Expression>>;
      Expression* expr = new ErrorExpr;
      $$->emplace_back(expr);
    }
    | ID LBRACE expression_list RBRACE COMMA expression_list {
      delete $3;
      delete $6;
      $$ = new std::vector<std::unique_ptr<Expression>>;
      Expression* expr = new ErrorExpr;
      $$->emplace_back(expr);
    }
    
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | ID {
      $$ = new UnboundFieldExpr("", $1);
      $$->set_name(token_name(sql_string, &@$));
      free($1);
    }
    | ID DOT ID {
      $$ = new UnboundFieldExpr($1, $3);
      $$->set_name(token_name(sql_string,&@$));
      free($1);
      free($3);
    }
    | '*' {
      $$ = new StarExpr();
    }
    // your code here
    
    ;

rel_attr:
    ID {
      std::cout << $1<<'\n';
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;
/*
relation:
    ID {
      $$ = $1;
    }
    ;*/
rel_list:
     /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID rel_list {
       // Cartesian Product
      $$ = new RelListSqlNode();
      if ($3 != nullptr) {
        $$->relations.swap(($3)->relations);
        $$->joins.swap(($3)->joins);
        delete $3;
      }
      $$->relations.emplace($$->relations.begin(), $2);
      JoinSqlNode join;
      join.type = JoinType::INNER_JOIN;
      $$->joins.emplace($$->joins.begin(), join);
      free($2);
    }
    | INNER JOIN ID rel_list {
      $$ = new RelListSqlNode();
      if ($4 != nullptr) {
        $$->relations.swap(($4)->relations);
        $$->joins.swap(($4)->joins);
        delete $4;
      }
      JoinSqlNode join;
      join.type = JoinType::INNER_JOIN;
      $$->joins.emplace($$->joins.begin(), join);
      $$->relations.emplace($$->relations.begin(), $3);
      free($3);
    }
    | INNER JOIN ID ON condition_list rel_list {
      $$ = new RelListSqlNode();
      if ($6 != nullptr) {
        $$->relations.swap(($6)->relations);
        $$->joins.swap(($6)->joins);
        delete $6;
      }
      JoinSqlNode join;
      join.type = JoinType::INNER_JOIN;
      if ($5 != nullptr) {
        join.conditions.swap(*$5);
        delete $5;
      }
      $$->joins.emplace($$->joins.begin() ,join);
      $$->relations.emplace($$->relations.begin(), $3);
      free($3);
    }
    ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    | WHERE subquery_value_list {
      $$ = $2;
    }

subquery_value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | subquery {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    } 
    | subquery AND subquery_value_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    } 
    | subquery AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
subquery:
    rel_attr comp_op LBRACE select_stmt RBRACE {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->comp = $2;
      $$->right_value_type = ValueType::SUB_QUERY;
      /*std::cout << "709 address:" << $5 << '\n';
      cout << $5->selection.relations[0] << '\n'; */
      $$->right_sub_queries = $4;
      delete $1;
      // cout << (*$$)[0].right_sub_queries << '\n';
    } 
    | LBRACE select_stmt RBRACE comp_op rel_attr {
      $$ = new ConditionSqlNode;
      
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$5;
      $$->comp = $4;
      if ($$->comp == CompOp::LESS_THAN) {
        $$->comp = CompOp::GREAT_THAN;
      } else if ($$->comp == CompOp::LESS_EQUAL) {
        $$->comp = CompOp::GREAT_EQUAL;
      } else if ($$->comp == CompOp::GREAT_THAN) {
        $$->comp = CompOp::LESS_THAN;
      } else if ($$->comp == CompOp::GREAT_EQUAL) {
        $$->comp = CompOp::LESS_EQUAL;
      } 
      $$->right_value_type = ValueType::SUB_QUERY;
      $$->right_sub_queries = $2;
      delete $5;
    }
    | rel_attr comp_op LBRACE value value_list RBRACE {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->comp = $2;
      $$->right_value_type = ValueType::VALUE_LIST;
      delete $1;
      if ($5 != nullptr) {
        $$->value_list = $5;
      } else {
        $$->value_list = new std::vector<Value>();
      }
      $$->value_list->emplace($$->value_list->begin(), *$4);
      delete $4;
    }
    | LBRACE value value_list RBRACE comp_op rel_attr {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$6;
      $$->comp = $5;
      if ($$->comp == CompOp::LESS_THAN) {
        $$->comp = CompOp::GREAT_THAN;
      } else if ($$->comp == CompOp::LESS_EQUAL) {
        $$->comp = CompOp::GREAT_EQUAL;
      } else if ($$->comp == CompOp::GREAT_THAN) {
        $$->comp = CompOp::LESS_THAN;
      } else if ($$->comp == CompOp::GREAT_EQUAL) {
        $$->comp = CompOp::LESS_EQUAL;
      } 
      $$->right_value_type = ValueType::VALUE_LIST;
      if ($3 != nullptr) {
        $$->value_list = $3;
      } else {
        $$->value_list = new vector<Value>();
      }
      $$->value_list->emplace($$->value_list->begin(), *$2);
      delete $2;
      delete $6;
    }
    ;

condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND subquery_value_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->right_value_type = ValueType::CONSTANT;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value 
    {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value = *$1;
      $$->right_value_type = ValueType::CONSTANT;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->right_value_type = ValueType::ATTRIBUTE;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value = *$1;
      $$->right_value_type = ValueType::ATTRIBUTE;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value IS null {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value = *$1;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->comp = IS_NULL_;
      delete $1;
    }
    | value IS NOT null {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value = *$1;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->comp = IS_NOT_NULL_;
      delete $1;
    }
    | value comp_op null {
      cout << "hello\n";
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value = *$1;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->comp = $2;
      delete $1;
    }
    | null comp_op value {
      $$ = new ConditionSqlNode;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->left_value = *$3;
      $$->left_value_type = ValueType::CONSTANT;
      $$->comp = $2;
      delete $3;
    }
    | rel_attr IS null {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->comp = IS_NULL_;
      delete $1;
    }
    | rel_attr IS NOT null {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->comp = IS_NOT_NULL_;
      delete $1;
    }
    | rel_attr comp_op null {
      $$ = new ConditionSqlNode;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$1;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->comp = $2;
      delete $1;
    }
    | null comp_op rel_attr {
      $$ = new ConditionSqlNode;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->left_value_type = ValueType::ATTRIBUTE;
      $$->left_attr = *$3;
      $$->comp = $2;
      delete $3;
    }
    | null IS null {
      $$ = new ConditionSqlNode;
      $$->right_value_type = ValueType::CONSTANT;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value.set_int(0);
      $$->right_value.set_int(0);
      $$->comp = EQUAL_TO;
    }
    | null IS NOT null {
      $$ = new ConditionSqlNode;
      $$->right_value_type = ValueType::CONSTANT;
      $$->left_value_type = ValueType::CONSTANT;
      $$->left_value.set_int(0);
      $$->right_value.set_int(1);
      $$->comp = EQUAL_TO;
    }
    | null comp_op null {
      $$ = new ConditionSqlNode;
      $$->right_value_type = ValueType::NULL_TYPE;
      $$->left_value_type = ValueType::NULL_TYPE;
      $$->comp = $2;
    }
   
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LK; }
    | NOT LIKE {$$ = NOT_LK; }
    | IN { $$ = IN_; }
    | NOT IN { $$ = NOT_IN_; }
    | EXISTS { $$ = EXISTS_; }
    | NOT EXISTS { $$ = NOT_EXISTS_; }
    ;

// your code here
group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY expression_list {
      $$ = $3;
      /*delete $3;*/
    }
    ;
order_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_list {
      $$ = $3;
    }
    ;
order_list:
  rel_attr {
    //std::cout << "[1]\n";
    $$ = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = $1->relation_name;
    node.attribute_name = $1->attribute_name;
    node.asc = true;
    delete $1;
    $$->emplace_back(std::move(node));
  }
  | rel_attr COMMA order_list {
    //std::cout << "[2]\n";
    $$ = $3;
    OrderBySqlNode node; 
    node.table_name = $1->relation_name;
    node.attribute_name = $1->attribute_name;
    node.asc = true;
    delete $1;
    $$->emplace($$->begin(), std::move(node));
  }
  | rel_attr ASC {
    //std::cout << "[3]\n";
    $$ = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = $1->relation_name;
    node.attribute_name = $1->attribute_name;
    node.asc = true;
    delete $1;
    $$->emplace_back(std::move(node));
  } 
  | rel_attr ASC COMMA order_list {
    //std::cout << "[4]\n";
    $$ = $4;
    OrderBySqlNode node; 
    node.table_name = $1->relation_name;
    node.attribute_name = $1->attribute_name;
    node.asc = true;
    delete $1;
    $$->emplace($$->begin(), std::move(node));
  } 
  | rel_attr DESC {
    //std::cout << "[5]\n";
    $$ = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = $1->relation_name;
    node.attribute_name = $1->attribute_name;
    node.asc = false;
    delete $1;
    $$->emplace_back(std::move(node));
    std::cout << (*$$)[0].attribute_name << '\n';
  } 
  | rel_attr DESC COMMA order_list {
    //std::cout << "[6]\n";
    $$ = $4;
    OrderBySqlNode node; 
    node.table_name = $1->relation_name;
    node.attribute_name = $1->attribute_name;
    node.asc = false;
    delete $1;
    $$->emplace($$->begin(), std::move(node));
  } 

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
