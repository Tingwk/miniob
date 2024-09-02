/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    TABLE = 263,                   /* TABLE  */
    TABLES = 264,                  /* TABLES  */
    INDEX = 265,                   /* INDEX  */
    CALC = 266,                    /* CALC  */
    SELECT = 267,                  /* SELECT  */
    DESC = 268,                    /* DESC  */
    SHOW = 269,                    /* SHOW  */
    SYNC = 270,                    /* SYNC  */
    INSERT = 271,                  /* INSERT  */
    DELETE = 272,                  /* DELETE  */
    UPDATE = 273,                  /* UPDATE  */
    LBRACE = 274,                  /* LBRACE  */
    RBRACE = 275,                  /* RBRACE  */
    COMMA = 276,                   /* COMMA  */
    TRX_BEGIN = 277,               /* TRX_BEGIN  */
    TRX_COMMIT = 278,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 279,            /* TRX_ROLLBACK  */
    INT_T = 280,                   /* INT_T  */
    DATE_T = 281,                  /* DATE_T  */
    INNER = 282,                   /* INNER  */
    JOIN = 283,                    /* JOIN  */
    STRING_T = 284,                /* STRING_T  */
    FLOAT_T = 285,                 /* FLOAT_T  */
    HELP = 286,                    /* HELP  */
    EXIT = 287,                    /* EXIT  */
    DOT = 288,                     /* DOT  */
    INTO = 289,                    /* INTO  */
    VALUES = 290,                  /* VALUES  */
    FROM = 291,                    /* FROM  */
    WHERE = 292,                   /* WHERE  */
    AND = 293,                     /* AND  */
    SET = 294,                     /* SET  */
    ON = 295,                      /* ON  */
    LOAD = 296,                    /* LOAD  */
    DATA = 297,                    /* DATA  */
    INFILE = 298,                  /* INFILE  */
    EXPLAIN = 299,                 /* EXPLAIN  */
    STORAGE = 300,                 /* STORAGE  */
    FORMAT = 301,                  /* FORMAT  */
    EQ = 302,                      /* EQ  */
    ORDER = 303,                   /* ORDER  */
    ASC = 304,                     /* ASC  */
    LT = 305,                      /* LT  */
    GT = 306,                      /* GT  */
    LE = 307,                      /* LE  */
    GE = 308,                      /* GE  */
    NE = 309,                      /* NE  */
    NOT = 310,                     /* NOT  */
    LIKE = 311,                    /* LIKE  */
    IN = 312,                      /* IN  */
    EXISTS = 313,                  /* EXISTS  */
    UNIQUE = 314,                  /* UNIQUE  */
    ROUND = 315,                   /* ROUND  */
    LENGTH = 316,                  /* LENGTH  */
    DATA_FORMAT = 317,             /* DATA_FORMAT  */
    null = 318,                    /* null  */
    IS = 319,                      /* IS  */
    NUMBER = 320,                  /* NUMBER  */
    FLOAT = 321,                   /* FLOAT  */
    ID = 322,                      /* ID  */
    SSS = 323,                     /* SSS  */
    UMINUS = 324                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 131 "yacc_sql.y"

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

#line 156 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
