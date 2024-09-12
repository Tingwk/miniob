/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
                                             YYLTYPE *llocp) {
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


#line 123 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_TABLE = 8,                      /* TABLE  */
  YYSYMBOL_TABLES = 9,                     /* TABLES  */
  YYSYMBOL_INDEX = 10,                     /* INDEX  */
  YYSYMBOL_CALC = 11,                      /* CALC  */
  YYSYMBOL_SELECT = 12,                    /* SELECT  */
  YYSYMBOL_DESC = 13,                      /* DESC  */
  YYSYMBOL_SHOW = 14,                      /* SHOW  */
  YYSYMBOL_SYNC = 15,                      /* SYNC  */
  YYSYMBOL_INSERT = 16,                    /* INSERT  */
  YYSYMBOL_DELETE = 17,                    /* DELETE  */
  YYSYMBOL_UPDATE = 18,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 19,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 20,                    /* RBRACE  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 22,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 23,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 24,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 25,                     /* INT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 27,                    /* TEXT_T  */
  YYSYMBOL_INNER = 28,                     /* INNER  */
  YYSYMBOL_JOIN = 29,                      /* JOIN  */
  YYSYMBOL_STRING_T = 30,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 31,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 32,                      /* HELP  */
  YYSYMBOL_EXIT = 33,                      /* EXIT  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_INTO = 35,                      /* INTO  */
  YYSYMBOL_VALUES = 36,                    /* VALUES  */
  YYSYMBOL_FROM = 37,                      /* FROM  */
  YYSYMBOL_WHERE = 38,                     /* WHERE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_SET = 40,                       /* SET  */
  YYSYMBOL_ON = 41,                        /* ON  */
  YYSYMBOL_LOAD = 42,                      /* LOAD  */
  YYSYMBOL_DATA = 43,                      /* DATA  */
  YYSYMBOL_INFILE = 44,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 45,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 46,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 47,                    /* FORMAT  */
  YYSYMBOL_EQ = 48,                        /* EQ  */
  YYSYMBOL_ORDER = 49,                     /* ORDER  */
  YYSYMBOL_ASC = 50,                       /* ASC  */
  YYSYMBOL_AS = 51,                        /* AS  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_GT = 53,                        /* GT  */
  YYSYMBOL_LE = 54,                        /* LE  */
  YYSYMBOL_GE = 55,                        /* GE  */
  YYSYMBOL_NE = 56,                        /* NE  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_LIKE = 58,                      /* LIKE  */
  YYSYMBOL_IN = 59,                        /* IN  */
  YYSYMBOL_EXISTS = 60,                    /* EXISTS  */
  YYSYMBOL_UNIQUE = 61,                    /* UNIQUE  */
  YYSYMBOL_ROUND = 62,                     /* ROUND  */
  YYSYMBOL_LENGTH = 63,                    /* LENGTH  */
  YYSYMBOL_DATE_FORMAT = 64,               /* DATE_FORMAT  */
  YYSYMBOL_null = 65,                      /* null  */
  YYSYMBOL_IS = 66,                        /* IS  */
  YYSYMBOL_HAVING = 67,                    /* HAVING  */
  YYSYMBOL_NUMBER = 68,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 69,                     /* FLOAT  */
  YYSYMBOL_ID = 70,                        /* ID  */
  YYSYMBOL_SSS = 71,                       /* SSS  */
  YYSYMBOL_72_ = 72,                       /* '+'  */
  YYSYMBOL_73_ = 73,                       /* '-'  */
  YYSYMBOL_74_ = 74,                       /* '*'  */
  YYSYMBOL_75_ = 75,                       /* '/'  */
  YYSYMBOL_UMINUS = 76,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_commands = 78,                  /* commands  */
  YYSYMBOL_command_wrapper = 79,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 80,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 81,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 82,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 83,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 84,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 85,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 86,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 87,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 88,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 89,         /* create_index_stmt  */
  YYSYMBOL_id_list = 90,                   /* id_list  */
  YYSYMBOL_drop_index_stmt = 91,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 92,         /* create_table_stmt  */
  YYSYMBOL_create_select_stmt = 93,        /* create_select_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_null_def = 96,                  /* null_def  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_value_with_null_list = 100,     /* value_with_null_list  */
  YYSYMBOL_value_with_null = 101,          /* value_with_null  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_storage_format = 104,           /* storage_format  */
  YYSYMBOL_delete_stmt = 105,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 106,              /* update_stmt  */
  YYSYMBOL_assignment_stmt_list = 107,     /* assignment_stmt_list  */
  YYSYMBOL_assignment_stmt = 108,          /* assignment_stmt  */
  YYSYMBOL_select_stmt = 109,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 110,                /* calc_stmt  */
  YYSYMBOL_expression_list = 111,          /* expression_list  */
  YYSYMBOL_expression = 112,               /* expression  */
  YYSYMBOL_alias_stmt = 113,               /* alias_stmt  */
  YYSYMBOL_rel_attr = 114,                 /* rel_attr  */
  YYSYMBOL_rel_list = 115,                 /* rel_list  */
  YYSYMBOL_on_conditions = 116,            /* on_conditions  */
  YYSYMBOL_new_where = 117,                /* new_where  */
  YYSYMBOL_new_condition_list = 118,       /* new_condition_list  */
  YYSYMBOL_new_condition = 119,            /* new_condition  */
  YYSYMBOL_where = 120,                    /* where  */
  YYSYMBOL_subquery_value_list = 121,      /* subquery_value_list  */
  YYSYMBOL_subquery = 122,                 /* subquery  */
  YYSYMBOL_condition_list = 123,           /* condition_list  */
  YYSYMBOL_condition = 124,                /* condition  */
  YYSYMBOL_comp_op = 125,                  /* comp_op  */
  YYSYMBOL_null_comparator = 126,          /* null_comparator  */
  YYSYMBOL_group_by = 127,                 /* group_by  */
  YYSYMBOL_having_clause = 128,            /* having_clause  */
  YYSYMBOL_order_by = 129,                 /* order_by  */
  YYSYMBOL_order_list = 130,               /* order_list  */
  YYSYMBOL_load_data_stmt = 131,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 132,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 133,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 134             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   530

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  200
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  385

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    74,    72,     2,    73,     2,    75,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    76
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   231,   231,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   263,   269,   274,   280,   286,   292,
     298,   305,   312,   320,   336,   355,   358,   370,   380,   403,
     412,   415,   428,   442,   459,   462,   465,   469,   472,   473,
     474,   475,   478,   494,   497,   507,   510,   518,   521,   532,
     536,   540,   549,   552,   559,   571,   586,   591,   598,   610,
     620,   659,   668,   677,   690,   699,   712,   722,   735,   741,
     752,   755,   758,   761,   764,   768,   771,   776,   781,   787,
     795,   798,   829,   835,   851,   854,   868,   889,   892,   895,
     903,   906,   912,   916,   926,   933,   944,   959,   976,   983,
     992,  1002,  1010,  1020,  1028,  1039,  1047,  1058,  1073,  1090,
    1097,  1106,  1116,  1123,  1133,  1141,  1148,  1157,  1171,  1187,
    1193,  1203,  1212,  1227,  1244,  1251,  1261,  1268,  1282,  1300,
    1303,  1306,  1312,  1315,  1320,  1325,  1332,  1343,  1362,  1377,
    1406,  1409,  1414,  1419,  1426,  1438,  1450,  1462,  1474,  1482,
    1490,  1499,  1507,  1515,  1523,  1531,  1539,  1547,  1555,  1565,
    1566,  1567,  1568,  1569,  1570,  1571,  1572,  1573,  1574,  1575,
    1576,  1580,  1583,  1586,  1593,  1596,  1604,  1608,  1613,  1616,
    1621,  1631,  1641,  1651,  1661,  1672,  1684,  1697,  1705,  1715,
    1716
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT",
  "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T",
  "TEXT_T", "INNER", "JOIN", "STRING_T", "FLOAT_T", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ", "ORDER", "ASC", "AS",
  "LT", "GT", "LE", "GE", "NE", "NOT", "LIKE", "IN", "EXISTS", "UNIQUE",
  "ROUND", "LENGTH", "DATE_FORMAT", "null", "IS", "HAVING", "NUMBER",
  "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "begin_stmt", "commit_stmt", "rollback_stmt", "drop_table_stmt",
  "show_tables_stmt", "desc_table_stmt", "create_index_stmt", "id_list",
  "drop_index_stmt", "create_table_stmt", "create_select_stmt",
  "attr_def_list", "attr_def", "null_def", "number", "type", "insert_stmt",
  "value_with_null_list", "value_with_null", "value_list", "value",
  "storage_format", "delete_stmt", "update_stmt", "assignment_stmt_list",
  "assignment_stmt", "select_stmt", "calc_stmt", "expression_list",
  "expression", "alias_stmt", "rel_attr", "rel_list", "on_conditions",
  "new_where", "new_condition_list", "new_condition", "where",
  "subquery_value_list", "subquery", "condition_list", "condition",
  "comp_op", "null_comparator", "group_by", "having_clause", "order_by",
  "order_list", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-336)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     387,    14,   166,   259,   259,   -42,    22,  -336,    24,     4,
       2,  -336,  -336,  -336,  -336,  -336,    36,    25,   387,   129,
     131,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,    60,    71,   134,    81,    82,   287,  -336,  -336,
      13,  -336,   287,  -336,  -336,  -336,   -39,   119,  -336,  -336,
      92,    93,   138,   140,   147,  -336,  -336,  -336,  -336,     6,
     149,   133,  -336,   158,   170,    45,   112,   137,  -336,   179,
     287,   287,   287,   287,   199,   181,   192,   214,   185,   167,
     187,   195,   225,   197,   240,   205,  -336,   238,   270,   -12,
    -336,  -336,   -19,   -19,  -336,  -336,   259,   107,   272,   215,
    -336,   246,   214,   288,  -336,   258,   117,   290,  -336,   293,
     250,  -336,   300,   301,   238,  -336,   261,   305,   299,   208,
      -2,   410,   302,   425,   440,  -336,   303,  -336,   311,   141,
    -336,   185,   330,  -336,  -336,  -336,  -336,    26,   195,   324,
     281,   321,   259,   259,   332,   107,   284,   127,   352,  -336,
     341,  -336,   342,   344,  -336,  -336,  -336,  -336,  -336,  -336,
      42,  -336,  -336,  -336,   -28,    68,   295,   -27,    99,    28,
     320,   215,   215,   225,  -336,  -336,   308,   313,   317,  -336,
    -336,   290,   327,   366,   325,  -336,  -336,   259,  -336,   353,
      39,   455,   362,   455,   382,   455,  -336,   358,   402,   359,
     208,   392,   167,   393,   470,  -336,  -336,  -336,   349,  -336,
    -336,  -336,  -336,  -336,   350,  -336,  -336,  -336,  -336,   351,
    -336,    -2,  -336,  -336,  -336,  -336,  -336,  -336,  -336,   397,
    -336,  -336,   398,  -336,  -336,   360,  -336,   354,   401,   366,
    -336,   215,   107,    95,   403,   365,  -336,   174,   355,   298,
     361,   146,   227,   306,   363,   127,   259,   427,  -336,   341,
    -336,   342,   470,   373,  -336,  -336,  -336,   342,   413,  -336,
      33,   396,   366,  -336,   426,  -336,  -336,  -336,   429,   455,
    -336,    39,  -336,  -336,   150,  -336,  -336,    39,  -336,   150,
    -336,  -336,  -336,  -336,    39,  -336,   150,    39,  -336,   150,
    -336,  -336,  -336,   378,   373,  -336,  -336,   373,  -336,   430,
    -336,  -336,   377,  -336,  -336,   455,   146,   234,    95,   431,
      95,   432,    95,   433,    95,   439,   162,  -336,     0,  -336,
    -336,  -336,  -336,   146,   245,  -336,  -336,    39,  -336,   150,
     441,  -336,   451,  -336,   452,  -336,   454,  -336,   440,  -336,
     465,   373,   466,  -336,  -336,    39,  -336,   150,    95,   469,
    -336,  -336,  -336,  -336,   278,   373,  -336,   373,   481,   482,
    -336,  -336,  -336,  -336,  -336
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     199,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     8,     9,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    59,    60,
      87,    61,     0,    89,    86,    71,    90,     0,    32,    31,
       0,     0,     0,     0,     0,   197,     1,   200,     2,     0,
       0,     0,    30,     0,    87,     0,     0,     0,    85,     0,
       0,     0,     0,     0,    72,     0,     0,   139,     0,     0,
       0,     0,     0,     0,     0,     0,    84,    90,     0,    90,
      88,    91,    80,    81,    82,    83,     0,    94,     0,   142,
      64,     0,   139,    66,   198,     0,     0,    40,    39,     0,
       0,    37,    74,    78,    90,    73,     0,     0,   100,     0,
       0,     0,    92,     0,     0,   141,   143,   140,   151,     0,
      65,     0,     0,    48,    51,    49,    50,    44,     0,     0,
       0,     0,     0,     0,    76,    94,     0,     0,   184,    56,
      53,    55,    57,     0,   169,   170,   171,   172,   173,   174,
       0,   175,   177,   179,     0,     0,     0,     0,     0,     0,
       0,   142,   142,     0,    68,    67,     0,     0,     0,    45,
      43,    40,    62,    35,     0,    75,    79,     0,    95,    97,
       0,     0,    87,    86,     0,     0,   101,   102,     0,   188,
       0,     0,     0,     0,     0,   176,   178,   180,     0,   166,
     168,   161,   165,    93,     0,   158,   160,   155,   157,     0,
     162,     0,   164,   154,   156,   144,   145,   153,   152,     0,
     196,    47,     0,    46,    41,     0,    38,     0,     0,    35,
      77,   142,    94,    86,     0,   182,   181,     0,     0,   181,
       0,   181,     0,   181,     0,     0,     0,     0,    70,    53,
      52,    57,     0,     0,   167,   159,   163,    57,     0,    69,
      44,     0,    35,    33,     0,    99,    98,    96,     0,     0,
     183,     0,   124,    86,   129,   109,    88,     0,    86,   122,
     112,   119,   123,   114,     0,   130,   136,     0,    86,   113,
     110,   108,   103,   186,     0,    54,    58,     0,   147,     0,
     146,    42,     0,    36,    34,     0,   181,     0,    86,     0,
      86,     0,    86,     0,    86,     0,   150,   185,   190,   189,
     149,   148,    63,   181,     0,   116,   105,     0,   126,   134,
       0,   125,     0,   115,     0,   135,     0,   104,     0,   187,
     194,     0,   192,   118,   107,     0,   128,   138,    86,     0,
     127,   117,   137,   106,     0,     0,   191,     0,     0,     0,
     131,   195,   193,   133,   132
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -336,  -336,   442,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -234,  -336,  -336,  -336,   314,   356,   210,
    -336,  -336,  -336,   206,  -128,  -207,   -86,  -336,  -336,  -336,
     375,  -336,   -78,  -336,     5,    -3,   -70,     9,  -153,  -336,
    -336,   252,  -336,   407,  -175,  -336,  -177,  -336,  -117,  -185,
    -336,  -336,  -336,  -335,  -336,  -336,  -336,  -336
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   248,    31,    32,    33,   149,   117,   190,
     242,   147,    34,   211,   160,   213,    54,   246,    35,    36,
     112,   113,    37,    38,    55,    75,    84,   134,   128,   252,
     158,   206,   207,   110,   135,   136,   137,   138,   175,   257,
     209,   337,   268,   339,    39,    40,    41,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    56,   198,   114,   236,   238,   235,   237,   124,    57,
       4,   184,    79,   360,   118,   284,   178,   180,   260,   262,
     264,   361,    42,   133,    43,    91,   376,   122,    58,   218,
     224,    59,    76,    80,    81,    82,    83,   219,   225,    79,
     381,    61,   382,   161,   162,   187,   288,    77,   323,    78,
     362,     4,   163,   161,   154,    82,    83,    92,    47,    60,
      80,    81,    82,    83,   316,    96,    48,    49,    64,    51,
     319,   203,    62,    99,   286,    44,   285,   102,   103,   104,
     105,    98,   269,   188,   256,   229,   259,   261,   263,   221,
     188,   189,   227,   230,   233,   133,   133,   273,   189,   287,
     215,   216,   217,    56,   327,   239,    63,    48,    49,    74,
      51,   125,    52,    53,   253,   -57,   212,    80,    81,    82,
      83,   350,   254,   352,   161,   354,   271,   356,   126,    66,
      69,    47,    97,   220,    67,   127,    48,    49,   132,    51,
     344,    70,   143,   144,    71,   277,   200,   145,   146,    56,
      56,    72,    73,   278,   204,   317,    85,   195,   196,   359,
     183,   379,    86,    87,   226,   133,   205,    48,    49,   132,
      51,   293,   326,   298,    45,   302,    46,   308,    88,   203,
      48,    49,    50,    51,   222,    52,    53,   228,    89,   234,
      93,    90,   201,   291,    56,    48,    49,   202,    51,    95,
      52,    53,   250,    94,    77,   328,   159,   100,   343,    48,
      49,   330,    51,   329,    48,    49,   132,    51,   332,   331,
     106,   334,    80,    81,    82,    83,   333,   131,   108,   335,
      48,    49,   132,    51,   130,    48,    49,     4,    51,   292,
     345,   374,    48,    49,   202,    51,   304,    52,    53,   101,
     133,   107,   109,   347,   294,   111,   299,   363,   115,   306,
     309,   368,   204,    56,   365,   116,   295,   119,   300,   369,
     303,   313,   310,   159,   205,   121,    48,    49,    47,    51,
     131,   120,   318,    48,    49,   132,    51,   378,   233,    79,
     123,   129,   305,   142,   139,    48,    49,    74,    51,   348,
      52,    53,    48,    49,    74,    51,    47,    52,    53,   141,
     366,   148,   150,    48,    49,    74,    51,   297,    52,    53,
     151,   152,   153,   338,   349,   307,   340,    48,    49,    50,
      51,   155,    52,    53,   156,   346,   176,   157,   186,   231,
     194,   367,   181,   232,   192,   358,    48,    49,   132,    51,
     182,   193,   364,   197,   199,    48,    49,    74,    51,   208,
      52,    53,   210,   212,   214,   223,    48,    49,   202,    51,
     338,    52,    53,   245,    48,    49,   202,    51,   240,    52,
      53,   241,   243,   234,   338,   232,   338,   247,    48,    49,
     132,    51,     1,     2,   251,   249,   258,   265,     3,     4,
       5,     6,     7,     8,     9,    10,   266,   281,   267,    11,
      12,    13,   270,   272,   274,   275,   276,   279,   280,    14,
      15,   283,   290,   289,   282,   296,   301,    16,   311,    17,
     164,   314,    18,   320,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   132,   322,   336,   324,   342,   255,   325,
     341,   351,   353,   355,    80,    81,    82,    83,   164,   357,
      65,   370,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   371,   372,   164,   373,   315,   174,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   375,   377,   164,   380,
     321,   177,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   383,   384,   164,   191,   244,   179,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   185,   312,   164,   140,
       0,   255,   165,   166,   167,   168,   169,   170,   171,   172,
     173
};

static const yytype_int16 yycheck[] =
{
       3,     4,   155,    89,   181,   182,   181,   182,    20,     4,
      12,   139,    51,    13,    92,   249,   133,   134,   203,   204,
     205,    21,     8,   109,    10,    19,   361,    97,    70,    57,
      57,     9,    19,    72,    73,    74,    75,    65,    65,    51,
     375,    37,   377,   129,   130,    19,   253,    34,   282,    52,
      50,    12,   130,   139,   124,    74,    75,    51,    19,    35,
      72,    73,    74,    75,   271,    20,    68,    69,    43,    71,
     277,   157,    70,    76,   251,    61,   251,    80,    81,    82,
      83,    76,   210,    57,   201,    57,   203,   204,   205,   175,
      57,    65,   178,    65,   180,   181,   182,   214,    65,   252,
      58,    59,    60,   106,   289,   183,    70,    68,    69,    70,
      71,   106,    73,    74,   200,    20,    21,    72,    73,    74,
      75,   328,   200,   330,   210,   332,   212,   334,    21,     0,
      70,    19,    20,    65,     3,    28,    68,    69,    70,    71,
     325,    70,    25,    26,    10,   231,    19,    30,    31,   152,
     153,    70,    70,   231,   157,   272,    37,   152,   153,   336,
      19,   368,    70,    70,    65,   251,   157,    68,    69,    70,
      71,   257,   289,   259,     8,   261,    10,   263,    40,   265,
      68,    69,    70,    71,   175,    73,    74,   178,    48,   180,
      41,    44,    65,    19,   197,    68,    69,    70,    71,    41,
      73,    74,   197,    70,    34,   291,    65,    70,   325,    68,
      69,   297,    71,   291,    68,    69,    70,    71,   304,   297,
      21,   307,    72,    73,    74,    75,   304,    65,    36,   307,
      68,    69,    70,    71,    19,    68,    69,    12,    71,    65,
     326,   358,    68,    69,    70,    71,    19,    73,    74,    70,
     336,    70,    38,    19,   257,    70,   259,   343,    71,   262,
     263,   347,   265,   266,    19,    70,   257,    70,   259,   347,
     261,   266,   263,    65,   265,    70,    68,    69,    19,    71,
      65,    41,   273,    68,    69,    70,    71,   365,   374,    51,
      20,    19,    65,    35,    48,    68,    69,    70,    71,    65,
      73,    74,    68,    69,    70,    71,    19,    73,    74,    21,
      65,    21,    19,    68,    69,    70,    71,    19,    73,    74,
      70,    21,    21,   314,   327,    19,   317,    68,    69,    70,
      71,    70,    73,    74,    29,   326,    34,    38,     8,    19,
      19,   344,    39,    65,    20,   336,    68,    69,    70,    71,
      39,    70,   343,    21,    70,    68,    69,    70,    71,     7,
      73,    74,    21,    21,    20,    70,    68,    69,    70,    71,
     361,    73,    74,    46,    68,    69,    70,    71,    70,    73,
      74,    68,    65,   374,   375,    65,   377,    21,    68,    69,
      70,    71,     5,     6,    41,    70,    34,    39,    11,    12,
      13,    14,    15,    16,    17,    18,     4,    47,    49,    22,
      23,    24,    20,    20,    65,    65,    65,    20,    20,    32,
      33,    20,    57,    20,    70,    70,    65,    40,    65,    42,
      48,     4,    45,    20,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    70,    48,    67,    20,    70,    66,    20,
      20,    20,    20,    20,    72,    73,    74,    75,    48,    20,
      18,    20,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    20,    20,    48,    20,   269,    66,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    21,    21,    48,    20,
     280,    66,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    20,    20,    48,   148,   191,    66,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   141,   265,    48,   112,
      -1,    66,    52,    53,    54,    55,    56,    57,    58,    59,
      60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    11,    12,    13,    14,    15,    16,    17,
      18,    22,    23,    24,    32,    33,    40,    42,    45,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    91,    92,    93,    99,   105,   106,   109,   110,   131,
     132,   133,     8,    10,    61,     8,    10,    19,    68,    69,
      70,    71,    73,    74,   103,   111,   112,   111,    70,     9,
      35,    37,    70,    70,    43,    79,     0,     3,   134,    70,
      70,    10,    70,    70,    70,   112,    19,    34,   112,    51,
      72,    73,    74,    75,   113,    37,    70,    70,    40,    48,
      44,    19,    51,    41,    70,    41,    20,    20,   111,   112,
      70,    70,   112,   112,   112,   112,    21,    70,    36,    38,
     120,    70,   107,   108,   103,    71,    70,    95,   109,    70,
      41,    70,   113,    20,    20,   111,    21,    28,   115,    19,
      19,    65,    70,   103,   114,   121,   122,   123,   124,    48,
     120,    21,    35,    25,    26,    30,    31,    98,    21,    94,
      19,    70,    21,    21,   113,    70,    29,    38,   117,    65,
     101,   103,   103,   109,    48,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    66,   125,    34,    66,   125,    66,
     125,    39,    39,    19,   101,   107,     8,    19,    57,    65,
      96,    95,    20,    70,    19,   111,   111,    21,   115,    70,
      19,    65,    70,   103,   112,   114,   118,   119,     7,   127,
      21,   100,    21,   102,    20,    58,    59,    60,    57,    65,
      65,   103,   114,    70,    57,    65,    65,   103,   114,    57,
      65,    19,    65,   103,   114,   121,   123,   121,   123,   109,
      70,    68,    97,    65,    94,    46,   104,    21,    90,    70,
     111,    41,   116,   103,   109,    66,   125,   126,    34,   125,
     126,   125,   126,   125,   126,    39,     4,    49,   129,   101,
      20,   103,    20,   125,    65,    65,    65,   103,   109,    20,
      20,    47,    70,    20,    90,   121,   123,   115,   102,    20,
      57,    19,    65,   103,   112,   114,    70,    19,   103,   112,
     114,    65,   103,   114,    19,    65,   112,    19,   103,   112,
     114,    65,   118,   111,     4,   100,   102,   125,   114,   102,
      20,    96,    48,    90,    20,    20,   125,   126,   103,   109,
     103,   109,   103,   109,   103,   109,    67,   128,   114,   130,
     114,    20,    70,   125,   126,   103,   114,    19,    65,   112,
     102,    20,   102,    20,   102,    20,   102,    20,   114,   123,
      13,    21,    50,   103,   114,    19,    65,   112,   103,   109,
      20,    20,    20,    20,   125,    21,   130,    21,   109,   102,
      20,   130,   130,    20,    20
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    89,    90,    90,    91,    92,    93,
      94,    94,    95,    95,    96,    96,    96,    97,    98,    98,
      98,    98,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   103,   104,   104,   105,   106,   107,   107,   108,   108,
     109,   110,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   113,   114,   114,   115,   115,   115,   116,   116,   116,
     117,   117,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   120,
     120,   120,   121,   121,   121,   121,   122,   122,   122,   122,
     123,   123,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   130,   130,   130,   130,   131,   132,   133,   134,
     134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     0,     3,     5,     8,     5,
       0,     3,     6,     3,     0,     1,     2,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     1,     0,     3,     1,
       1,     1,     0,     4,     4,     5,     1,     3,     3,     5,
       8,     2,     2,     4,     4,     6,     5,     7,     4,     6,
       3,     3,     3,     3,     3,     2,     1,     1,     3,     1,
       0,     2,     1,     3,     0,     3,     5,     0,     2,     2,
       0,     2,     1,     3,     5,     5,     6,     6,     3,     3,
       3,     3,     3,     3,     3,     5,     5,     6,     6,     3,
       3,     3,     3,     3,     3,     5,     5,     6,     6,     3,
       3,     7,     8,     8,     5,     5,     3,     6,     6,     0,
       2,     2,     0,     1,     3,     3,     5,     5,     6,     6,
       0,     1,     3,     3,     3,     3,     3,     3,     3,     4,
       3,     3,     3,     4,     3,     3,     3,     4,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       2,     1,     1,     2,     0,     4,     0,     2,     0,     3,
       1,     3,     2,     4,     2,     4,     7,     2,     4,     0,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 232 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1953 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 263 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 269 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 274 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1978 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 280 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1986 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 286 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 292 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2002 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 298 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2012 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 305 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2020 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 312 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 321 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.unique = false;
      if ((yyvsp[-1].id_list_type) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].id_list_type));
        delete (yyvsp[-1].id_list_type);
      }
      create_index.attribute_names.emplace(create_index.attribute_names.begin(), (yyvsp[-2].string));
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2050 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 337 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.unique = true;
      if ((yyvsp[-1].id_list_type) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].id_list_type));
        delete (yyvsp[-1].id_list_type);
      }
      create_index.attribute_names.emplace(create_index.attribute_names.begin(), (yyvsp[-2].string));
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2070 "yacc_sql.cpp"
    break;

  case 35: /* id_list: %empty  */
#line 355 "yacc_sql.y"
  {
    (yyval.id_list_type) = nullptr;
  }
#line 2078 "yacc_sql.cpp"
    break;

  case 36: /* id_list: COMMA ID id_list  */
#line 358 "yacc_sql.y"
                     {
    if ((yyvsp[0].id_list_type) != nullptr) {
      (yyval.id_list_type) = (yyvsp[0].id_list_type);
    } else {
      (yyval.id_list_type) = new std::vector<std::string>();
    }
    (yyval.id_list_type)->emplace((yyval.id_list_type)->begin(), (yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 2092 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 371 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2104 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 381 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2129 "yacc_sql.cpp"
    break;

  case 39: /* create_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 403 "yacc_sql.y"
                                 {
    cout << "hello\n";
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_SELECT);
    (yyval.sql_node)->create_select.relation_name = (yyvsp[-2].string);
    free((yyvsp[-2].string));
    (yyval.sql_node)->create_select.sub_query = (yyvsp[0].sql_node);
  }
#line 2141 "yacc_sql.cpp"
    break;

  case 40: /* attr_def_list: %empty  */
#line 412 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2149 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 416 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 42: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 429 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      if ((yyvsp[0].number_ptr) != nullptr) {
        (yyval.attr_info)->nullable = (*(yyvsp[0].number_ptr) == 0);
        delete (yyvsp[0].number_ptr);
      } else {
        (yyval.attr_info)->nullable = false;
      }
      free((yyvsp[-5].string));
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type null_def  */
#line 443 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      if ((yyvsp[0].number_ptr) != nullptr) {
        (yyval.attr_info)->nullable = (*(yyvsp[0].number_ptr) == 0);
        delete (yyvsp[0].number_ptr);
      } else {
        (yyval.attr_info)->nullable = false;
      }
      free((yyvsp[-2].string));
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 44: /* null_def: %empty  */
#line 459 "yacc_sql.y"
    {
      (yyval.number_ptr) = nullptr;
    }
#line 2207 "yacc_sql.cpp"
    break;

  case 45: /* null_def: null  */
#line 462 "yacc_sql.y"
           {
      (yyval.number_ptr) = new int(0);
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 46: /* null_def: NOT null  */
#line 465 "yacc_sql.y"
               {
      (yyval.number_ptr) = new int(1);
    }
#line 2223 "yacc_sql.cpp"
    break;

  case 47: /* number: NUMBER  */
#line 469 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2229 "yacc_sql.cpp"
    break;

  case 48: /* type: INT_T  */
#line 472 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2235 "yacc_sql.cpp"
    break;

  case 49: /* type: STRING_T  */
#line 473 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2241 "yacc_sql.cpp"
    break;

  case 50: /* type: FLOAT_T  */
#line 474 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2247 "yacc_sql.cpp"
    break;

  case 51: /* type: DATE_T  */
#line 475 "yacc_sql.y"
             { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2253 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value_with_null value_with_null_list RBRACE  */
#line 479 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
        delete (yyvsp[-1].value_list);
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2270 "yacc_sql.cpp"
    break;

  case 53: /* value_with_null_list: %empty  */
#line 494 "yacc_sql.y"
  {
    (yyval.value_list) = nullptr;
  }
#line 2278 "yacc_sql.cpp"
    break;

  case 54: /* value_with_null_list: COMMA value_with_null value_with_null_list  */
#line 497 "yacc_sql.y"
                                                { 
    if ((yyvsp[0].value_list) != nullptr) {
      (yyval.value_list) = (yyvsp[0].value_list);
    } else {
      (yyval.value_list) = new std::vector<Value>;
    }
    (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
    delete (yyvsp[-1].value);
  }
#line 2292 "yacc_sql.cpp"
    break;

  case 55: /* value_with_null: value  */
#line 507 "yacc_sql.y"
         {
    (yyval.value) = (yyvsp[0].value);
  }
#line 2300 "yacc_sql.cpp"
    break;

  case 56: /* value_with_null: null  */
#line 510 "yacc_sql.y"
         {
    (yyval.value) = new Value();
    (yyval.value)->set_null();
  }
#line 2309 "yacc_sql.cpp"
    break;

  case 57: /* value_list: %empty  */
#line 518 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2317 "yacc_sql.cpp"
    break;

  case 58: /* value_list: COMMA value value_list  */
#line 521 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2331 "yacc_sql.cpp"
    break;

  case 59: /* value: NUMBER  */
#line 532 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2340 "yacc_sql.cpp"
    break;

  case 60: /* value: FLOAT  */
#line 536 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2349 "yacc_sql.cpp"
    break;

  case 61: /* value: SSS  */
#line 540 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2360 "yacc_sql.cpp"
    break;

  case 62: /* storage_format: %empty  */
#line 549 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2368 "yacc_sql.cpp"
    break;

  case 63: /* storage_format: STORAGE FORMAT EQ ID  */
#line 553 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2376 "yacc_sql.cpp"
    break;

  case 64: /* delete_stmt: DELETE FROM ID where  */
#line 560 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2390 "yacc_sql.cpp"
    break;

  case 65: /* update_stmt: UPDATE ID SET assignment_stmt_list where  */
#line 572 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.assignments.swap(*(yyvsp[-1].assignment_list_type));
      
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      delete (yyvsp[-1].assignment_list_type);
      free((yyvsp[-3].string));
    }
#line 2407 "yacc_sql.cpp"
    break;

  case 66: /* assignment_stmt_list: assignment_stmt  */
#line 586 "yacc_sql.y"
                  {
    (yyval.assignment_list_type) = new std::vector<Assignment>;
    (yyval.assignment_list_type)->emplace_back(*(yyvsp[0].assignment_type));
    delete (yyvsp[0].assignment_type);
  }
#line 2417 "yacc_sql.cpp"
    break;

  case 67: /* assignment_stmt_list: assignment_stmt COMMA assignment_stmt_list  */
#line 591 "yacc_sql.y"
                                               {
    (yyval.assignment_list_type) = (yyvsp[0].assignment_list_type);
    (yyval.assignment_list_type)->emplace((yyval.assignment_list_type)->begin(), *(yyvsp[-2].assignment_type));
    delete (yyvsp[-2].assignment_type);
  }
#line 2427 "yacc_sql.cpp"
    break;

  case 68: /* assignment_stmt: ID EQ value_with_null  */
#line 598 "yacc_sql.y"
                        {
    (yyval.assignment_type) = new Assignment;
    (yyval.assignment_type)->value = *(yyvsp[0].value);
    delete (yyvsp[0].value);
    if ((yyval.assignment_type)->value.attr_type() == AttrType::NULLS) {
      (yyval.assignment_type)->type = ValueType::NULL_TYPE;
    } else {
      (yyval.assignment_type)->type = ValueType::CONSTANT;
    }
    (yyval.assignment_type)->attribute_name = (yyvsp[-2].string);
    free((yyvsp[-2].string));
  }
#line 2444 "yacc_sql.cpp"
    break;

  case 69: /* assignment_stmt: ID EQ LBRACE select_stmt RBRACE  */
#line 610 "yacc_sql.y"
                                    {
    (yyval.assignment_type) = new Assignment;
    (yyval.assignment_type)->sub_query = (yyvsp[-1].sql_node);
    (yyval.assignment_type)->type = ValueType::SUB_QUERY;
    (yyval.assignment_type)->attribute_name = (yyvsp[-4].string);
    free((yyvsp[-4].string));
  }
#line 2456 "yacc_sql.cpp"
    break;

  case 70: /* select_stmt: SELECT expression_list FROM ID rel_list new_where group_by order_by  */
#line 621 "yacc_sql.y"
    {
      std::cout << "select_stmt\n";
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-6].expression_list) != nullptr) {
        (yyval.sql_node)->selection.expressions.swap(*(yyvsp[-6].expression_list));
        delete (yyvsp[-6].expression_list);
      }

      if ((yyvsp[-3].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap((*(yyvsp[-3].relation_list)).relations);
        (yyval.sql_node)->selection.joins.swap((*(yyvsp[-3].relation_list)).joins);
        delete (yyvsp[-3].relation_list);
      }
      (yyval.sql_node)->selection.relations.emplace((yyval.sql_node)->selection.relations.begin(), (yyvsp[-4].string));
      free((yyvsp[-4].string));
      
      if ((yyvsp[-2].new_condition_list) != nullptr) {
        //cout << (*$6)[0].right_sub_queries << '\n';
        // $$->selection.conditions.swap(*$6);
        for (auto expr : *(yyvsp[-2].new_condition_list)) {
          std::unique_ptr<Expression> uni_expr(expr);
          (yyval.sql_node)->selection.conditions.emplace_back(std::move(uni_expr));
        }
        delete (yyvsp[-2].new_condition_list);
        //cout << ($$->selection.conditions)[0].right_sub_queries << '\n';
      }

      if ((yyvsp[-1].expression_list) != nullptr) {
        (yyval.sql_node)->selection.group_by.swap(*(yyvsp[-1].expression_list));
        delete (yyvsp[-1].expression_list);
      }
      if ((yyvsp[0].order_by_list) != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*(yyvsp[0].order_by_list));
        delete (yyvsp[0].order_by_list);
      }
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 71: /* calc_stmt: CALC expression_list  */
#line 660 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2507 "yacc_sql.cpp"
    break;

  case 72: /* expression_list: expression alias_stmt  */
#line 669 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if ((yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 73: /* expression_list: expression alias_stmt COMMA expression_list  */
#line 678 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if ((yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_alias((yyvsp[-2].string));
        free((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 74: /* expression_list: ID LBRACE RBRACE alias_stmt  */
#line 690 "yacc_sql.y"
                                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression *expr = new ErrorExpr();
      (yyval.expression_list)->emplace_back(expr);
      if ((yyvsp[0].string)) {
        free((yyvsp[0].string));
      }
      free((yyvsp[-3].string));
    }
#line 2551 "yacc_sql.cpp"
    break;

  case 75: /* expression_list: ID LBRACE RBRACE alias_stmt COMMA expression_list  */
#line 699 "yacc_sql.y"
                                                        {
      if ((yyvsp[0].expression_list)) {
        delete (yyvsp[0].expression_list);
      }
      if ((yyvsp[-2].string)) {
        free((yyvsp[-2].string));
      }
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression *expr = new ErrorExpr();
      (yyval.expression_list)->emplace_back(expr);
      free((yyvsp[-5].string));
    }
#line 2568 "yacc_sql.cpp"
    break;

  case 76: /* expression_list: ID LBRACE expression RBRACE alias_stmt  */
#line 712 "yacc_sql.y"
                                             {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      auto expr = create_aggregate_expression((yyvsp[-4].string), (yyvsp[-2].expression), sql_string, &(yyloc));
      if ((yyvsp[0].string)) {
        expr->set_alias((yyvsp[0].string));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back(expr);
      free((yyvsp[-4].string));
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 77: /* expression_list: ID LBRACE expression RBRACE alias_stmt COMMA expression_list  */
#line 722 "yacc_sql.y"
                                                                    {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      int start = (yylsp[-6]).first_column;
      int end = (yylsp[-3]).last_column;
      auto expr = create_aggregate_expression((yyvsp[-6].string), (yyvsp[-4].expression), sql_string, &(yyloc));
      expr->set_name(std::string(sql_string+ start, end- start + 1));
      if ((yyvsp[-2].string)) {
        expr->set_alias((yyvsp[-2].string));
        free((yyvsp[-2].string));
      }
      free((yyvsp[-6].string));
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), expr);
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 78: /* expression_list: ID LBRACE expression_list RBRACE  */
#line 735 "yacc_sql.y"
                                       {
      delete (yyvsp[-1].expression_list);
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression* expr = new ErrorExpr;
      (yyval.expression_list)->emplace_back(expr);
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 79: /* expression_list: ID LBRACE expression_list RBRACE COMMA expression_list  */
#line 741 "yacc_sql.y"
                                                             {
      delete (yyvsp[-3].expression_list);
      delete (yyvsp[0].expression_list);
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression* expr = new ErrorExpr;
      (yyval.expression_list)->emplace_back(expr);
    }
#line 2624 "yacc_sql.cpp"
    break;

  case 80: /* expression: expression '+' expression  */
#line 752 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2632 "yacc_sql.cpp"
    break;

  case 81: /* expression: expression '-' expression  */
#line 755 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2640 "yacc_sql.cpp"
    break;

  case 82: /* expression: expression '*' expression  */
#line 758 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 83: /* expression: expression '/' expression  */
#line 761 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2656 "yacc_sql.cpp"
    break;

  case 84: /* expression: LBRACE expression RBRACE  */
#line 764 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2665 "yacc_sql.cpp"
    break;

  case 85: /* expression: '-' expression  */
#line 768 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 86: /* expression: value  */
#line 771 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2683 "yacc_sql.cpp"
    break;

  case 87: /* expression: ID  */
#line 776 "yacc_sql.y"
         {
      (yyval.expression) = new UnboundFieldExpr("", (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 2693 "yacc_sql.cpp"
    break;

  case 88: /* expression: ID DOT ID  */
#line 781 "yacc_sql.y"
                {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string,&(yyloc)));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 89: /* expression: '*'  */
#line 787 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 90: /* alias_stmt: %empty  */
#line 795 "yacc_sql.y"
  {
    (yyval.string) = nullptr;
  }
#line 2720 "yacc_sql.cpp"
    break;

  case 91: /* alias_stmt: AS ID  */
#line 798 "yacc_sql.y"
          {
    (yyval.string) = (yyvsp[0].string);
  }
#line 2728 "yacc_sql.cpp"
    break;

  case 92: /* rel_attr: ID  */
#line 829 "yacc_sql.y"
       {
      std::cout << (yyvsp[0].string)<<'\n';
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2739 "yacc_sql.cpp"
    break;

  case 93: /* rel_attr: ID DOT ID  */
#line 835 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2751 "yacc_sql.cpp"
    break;

  case 94: /* rel_list: %empty  */
#line 851 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2759 "yacc_sql.cpp"
    break;

  case 95: /* rel_list: COMMA ID rel_list  */
#line 854 "yacc_sql.y"
                        {
       // Cartesian Product
      (yyval.relation_list) = new RelListSqlNode();
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list)->relations.swap(((yyvsp[0].relation_list))->relations);
        (yyval.relation_list)->joins.swap(((yyvsp[0].relation_list))->joins);
        delete (yyvsp[0].relation_list);
      }
      (yyval.relation_list)->relations.emplace((yyval.relation_list)->relations.begin(), (yyvsp[-1].string));
      JoinSqlNode join;
      join.type = JoinType::INNER_JOIN;
      (yyval.relation_list)->joins.emplace((yyval.relation_list)->joins.begin(), join);
      free((yyvsp[-1].string));
    }
#line 2778 "yacc_sql.cpp"
    break;

  case 96: /* rel_list: INNER JOIN ID on_conditions rel_list  */
#line 868 "yacc_sql.y"
                                           {
      (yyval.relation_list) = new RelListSqlNode();
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list)->relations.swap(((yyvsp[0].relation_list))->relations);
        (yyval.relation_list)->joins.swap(((yyvsp[0].relation_list))->joins);
        delete (yyvsp[0].relation_list);
      }
      JoinSqlNode join;
      join.type = JoinType::INNER_JOIN;
      if ((yyvsp[-1].condition_list) != nullptr) {
        join.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      (yyval.relation_list)->joins.emplace((yyval.relation_list)->joins.begin() ,join);
      (yyval.relation_list)->relations.emplace((yyval.relation_list)->relations.begin(), (yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
#line 2800 "yacc_sql.cpp"
    break;

  case 97: /* on_conditions: %empty  */
#line 889 "yacc_sql.y"
  {
    (yyval.condition_list) = nullptr;
  }
#line 2808 "yacc_sql.cpp"
    break;

  case 98: /* on_conditions: ON condition_list  */
#line 892 "yacc_sql.y"
                      {
    (yyval.condition_list) = (yyvsp[0].condition_list);
  }
#line 2816 "yacc_sql.cpp"
    break;

  case 99: /* on_conditions: ON subquery_value_list  */
#line 895 "yacc_sql.y"
                           {
    (yyval.condition_list) = (yyvsp[0].condition_list);
  }
#line 2824 "yacc_sql.cpp"
    break;

  case 100: /* new_where: %empty  */
#line 903 "yacc_sql.y"
  {
    (yyval.new_condition_list) = nullptr;
  }
#line 2832 "yacc_sql.cpp"
    break;

  case 101: /* new_where: WHERE new_condition_list  */
#line 906 "yacc_sql.y"
                             {
    (yyval.new_condition_list) = (yyvsp[0].new_condition_list);
  }
#line 2840 "yacc_sql.cpp"
    break;

  case 102: /* new_condition_list: new_condition  */
#line 912 "yacc_sql.y"
                {
    (yyval.new_condition_list) = new std::vector<Expression*>();
    (yyval.new_condition_list)->emplace_back((yyvsp[0].new_condition));
  }
#line 2849 "yacc_sql.cpp"
    break;

  case 103: /* new_condition_list: new_condition AND new_condition_list  */
#line 916 "yacc_sql.y"
                                         {
    (yyval.new_condition_list) = (yyvsp[0].new_condition_list);
    (yyval.new_condition_list)->emplace((yyval.new_condition_list)->begin(), (yyvsp[-2].new_condition));
  }
#line 2858 "yacc_sql.cpp"
    break;

  case 104: /* new_condition: rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 926 "yacc_sql.y"
                                               {
      std::unique_ptr<UnboundFieldExpr> left(new UnboundFieldExpr((yyvsp[-4].rel_attr)->relation_name,(yyvsp[-4].rel_attr)->attribute_name));
      std::unique_ptr<ParsedSqlNode> query((yyvsp[-1].sql_node));
      std::unique_ptr<SubQueryExpr> right(new SubQueryExpr(std::move(query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
      delete (yyvsp[-4].rel_attr);
    }
#line 2870 "yacc_sql.cpp"
    break;

  case 105: /* new_condition: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 933 "yacc_sql.y"
                                                 {
      std::unique_ptr<Expression> right(new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name));
      std::unique_ptr<ParsedSqlNode> query((yyvsp[-3].sql_node));
      
      std::unique_ptr<SubQueryExpr> left(new SubQueryExpr(std::move(query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      
      delete (yyvsp[0].rel_attr);
    }
#line 2884 "yacc_sql.cpp"
    break;

  case 106: /* new_condition: rel_attr comp_op LBRACE value value_list RBRACE  */
#line 944 "yacc_sql.y"
                                                      {
      std::unique_ptr<UnboundFieldExpr> left(new UnboundFieldExpr((yyvsp[-5].rel_attr)->relation_name,(yyvsp[-5].rel_attr)->attribute_name));
      delete (yyvsp[-5].rel_attr);
      std::vector<Value> *val_list;
      if ((yyvsp[-1].value_list) != nullptr) {
        val_list = (yyvsp[-1].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      std::unique_ptr<ValueListExpr> right(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-4].comp), std::move(left), std::move(right));
      
    }
#line 2904 "yacc_sql.cpp"
    break;

  case 107: /* new_condition: LBRACE value value_list RBRACE comp_op rel_attr  */
#line 959 "yacc_sql.y"
                                                       {
    //1      2      3          4      5      6
      std::unique_ptr<UnboundFieldExpr> right(new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name));
      delete (yyvsp[0].rel_attr);
      std::vector<Value> *val_list;
      if ((yyvsp[-3].value_list) != nullptr) {
        val_list = (yyvsp[-3].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-4].value));
      delete (yyvsp[-4].value);
      std::unique_ptr<ValueListExpr> left(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2924 "yacc_sql.cpp"
    break;

  case 108: /* new_condition: rel_attr null_comparator null  */
#line 976 "yacc_sql.y"
                                    {
      std::unique_ptr<UnboundFieldExpr> left(new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name));
      delete (yyvsp[-2].rel_attr);
      std::unique_ptr<NullExpr> right(new NullExpr);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 109: /* new_condition: null null_comparator rel_attr  */
#line 983 "yacc_sql.y"
                                    {
      std::unique_ptr<UnboundFieldExpr> right(new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name));
      delete (yyvsp[0].rel_attr);
      std::unique_ptr<Expression> left(new NullExpr());
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 2948 "yacc_sql.cpp"
    break;

  case 110: /* new_condition: rel_attr comp_op rel_attr  */
#line 992 "yacc_sql.y"
                                {
      std::unique_ptr<UnboundFieldExpr> left(new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name));
      std::unique_ptr<UnboundFieldExpr> right(new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name));
      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      
    }
#line 2961 "yacc_sql.cpp"
    break;

  case 111: /* new_condition: rel_attr comp_op value  */
#line 1002 "yacc_sql.y"
                             {
      std::unique_ptr<UnboundFieldExpr> left(new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name));
      std::unique_ptr<ValueExpr> right(new ValueExpr(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
      delete (yyvsp[-2].rel_attr);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 2974 "yacc_sql.cpp"
    break;

  case 112: /* new_condition: value comp_op rel_attr  */
#line 1010 "yacc_sql.y"
                             {
      std::unique_ptr<UnboundFieldExpr> right(new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name));
      std::unique_ptr<ValueExpr> left(new ValueExpr(*(yyvsp[-2].value)));
      delete (yyvsp[0].rel_attr);
      delete (yyvsp[-2].value);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 2987 "yacc_sql.cpp"
    break;

  case 113: /* new_condition: rel_attr comp_op expression  */
#line 1020 "yacc_sql.y"
                                  {
      std::unique_ptr<UnboundFieldExpr> left(new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name));
      std::unique_ptr<Expression> right ((yyvsp[0].expression));
      cout << "rel_attr&expression:"  << '\n';
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
      delete (yyvsp[-2].rel_attr);
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 114: /* new_condition: expression comp_op rel_attr  */
#line 1028 "yacc_sql.y"
                                  {
      std::unique_ptr<UnboundFieldExpr> right(new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name));
      std::unique_ptr<Expression> left ((yyvsp[-2].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
      delete (yyvsp[0].rel_attr);
    }
#line 3012 "yacc_sql.cpp"
    break;

  case 115: /* new_condition: value comp_op LBRACE select_stmt RBRACE  */
#line 1039 "yacc_sql.y"
                                              {
      std::unique_ptr<ValueExpr> left(new ValueExpr(*(yyvsp[-4].value)));
      delete (yyvsp[-4].value);
      std::unique_ptr<ParsedSqlNode> query((yyvsp[-1].sql_node));
      std::unique_ptr<SubQueryExpr> right(new SubQueryExpr(std::move(query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3025 "yacc_sql.cpp"
    break;

  case 116: /* new_condition: LBRACE select_stmt RBRACE comp_op value  */
#line 1047 "yacc_sql.y"
                                              {
      std::unique_ptr<ValueExpr> right(new ValueExpr(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
      std::unique_ptr<ParsedSqlNode> query;
      query.reset((yyvsp[-3].sql_node));
      std::unique_ptr<SubQueryExpr> left(new SubQueryExpr(std::move(query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 117: /* new_condition: value comp_op LBRACE value value_list RBRACE  */
#line 1058 "yacc_sql.y"
                                                   {
      std::unique_ptr<ValueExpr> left(new ValueExpr(*(yyvsp[-5].value)));
      delete (yyvsp[-5].value);
      std::vector<Value> *val_list;
      if ((yyvsp[-1].value_list) != nullptr) {
        val_list = (yyvsp[-1].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      std::unique_ptr<ValueListExpr> right(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-4].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 118: /* new_condition: LBRACE value value_list RBRACE comp_op value  */
#line 1073 "yacc_sql.y"
                                                    {
      std::unique_ptr<ValueExpr> right(new ValueExpr(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
      std::vector<Value> *val_list;
      if ((yyvsp[-3].value_list) != nullptr) {
        val_list = (yyvsp[-3].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-4].value));
      delete (yyvsp[-4].value);
      std::unique_ptr<ValueListExpr> left(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 119: /* new_condition: value null_comparator null  */
#line 1090 "yacc_sql.y"
                                 {
      std::unique_ptr<ValueExpr> left(new ValueExpr(*(yyvsp[-2].value)));
      delete (yyvsp[-2].value);
      std::unique_ptr<NullExpr> right(new NullExpr);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 120: /* new_condition: null null_comparator value  */
#line 1097 "yacc_sql.y"
                                 {
      std::unique_ptr<ValueExpr> right(new ValueExpr(*(yyvsp[0].value)));
      delete (yyvsp[0].value);
      std::unique_ptr<NullExpr> left(new NullExpr);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3103 "yacc_sql.cpp"
    break;

  case 121: /* new_condition: value comp_op value  */
#line 1106 "yacc_sql.y"
                          {
      std::unique_ptr<ValueExpr> left(new ValueExpr(*(yyvsp[-2].value)));
      std::unique_ptr<ValueExpr> right(new ValueExpr(*(yyvsp[0].value)));
      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3116 "yacc_sql.cpp"
    break;

  case 122: /* new_condition: value comp_op expression  */
#line 1116 "yacc_sql.y"
                               {
      std::unique_ptr<ValueExpr> left(new ValueExpr(*(yyvsp[-2].value)));
      std::unique_ptr<Expression> right ((yyvsp[0].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
      delete (yyvsp[-2].value);
    }
#line 3128 "yacc_sql.cpp"
    break;

  case 123: /* new_condition: expression comp_op value  */
#line 1123 "yacc_sql.y"
                               {
      std::unique_ptr<ValueExpr> right(new ValueExpr(*(yyvsp[0].value)));
      std::unique_ptr<Expression> left ((yyvsp[-2].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
      delete (yyvsp[0].value);
    }
#line 3140 "yacc_sql.cpp"
    break;

  case 124: /* new_condition: null null_comparator null  */
#line 1133 "yacc_sql.y"
                                {
      std::unique_ptr<NullExpr> left(new NullExpr);
      std::unique_ptr<NullExpr> right(new NullExpr);
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3151 "yacc_sql.cpp"
    break;

  case 125: /* new_condition: null null_comparator LBRACE select_stmt RBRACE  */
#line 1141 "yacc_sql.y"
                                                     {
      std::unique_ptr<NullExpr> left(new NullExpr);
      std::unique_ptr<ParsedSqlNode> query((yyvsp[-1].sql_node));
      std::unique_ptr<SubQueryExpr> right(new SubQueryExpr(std::move(query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3163 "yacc_sql.cpp"
    break;

  case 126: /* new_condition: LBRACE select_stmt RBRACE null_comparator null  */
#line 1148 "yacc_sql.y"
                                                    {
      std::unique_ptr<NullExpr> right(new NullExpr);
      std::unique_ptr<ParsedSqlNode> query((yyvsp[-3].sql_node));
      std::unique_ptr<SubQueryExpr> left(new SubQueryExpr(std::move(query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3175 "yacc_sql.cpp"
    break;

  case 127: /* new_condition: null null_comparator LBRACE value value_list RBRACE  */
#line 1157 "yacc_sql.y"
                                                          {
      std::unique_ptr<NullExpr> left(new NullExpr);
      std::vector<Value> *val_list;
      if ((yyvsp[-1].value_list) != nullptr) {
        val_list = (yyvsp[-1].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      std::unique_ptr<ValueListExpr> right(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-4].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3194 "yacc_sql.cpp"
    break;

  case 128: /* new_condition: LBRACE value value_list RBRACE null_comparator null  */
#line 1171 "yacc_sql.y"
                                                           {
      std::unique_ptr<NullExpr> right(new NullExpr);
      std::vector<Value> *val_list;
      if ((yyvsp[-3].value_list) != nullptr) {
        val_list = (yyvsp[-3].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-4].value));
      delete (yyvsp[-4].value);
      std::unique_ptr<ValueListExpr> left(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3213 "yacc_sql.cpp"
    break;

  case 129: /* new_condition: null null_comparator expression  */
#line 1187 "yacc_sql.y"
                                      {
      std::unique_ptr<NullExpr> left(new NullExpr);
      std::unique_ptr<Expression> right ((yyvsp[0].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3224 "yacc_sql.cpp"
    break;

  case 130: /* new_condition: expression null_comparator null  */
#line 1193 "yacc_sql.y"
                                      {
      std::unique_ptr<NullExpr> right(new NullExpr);
      std::unique_ptr<Expression> left ((yyvsp[-2].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3235 "yacc_sql.cpp"
    break;

  case 131: /* new_condition: LBRACE select_stmt RBRACE null_comparator LBRACE select_stmt RBRACE  */
#line 1203 "yacc_sql.y"
                                                                          {
      std::unique_ptr<ParsedSqlNode> left_query((yyvsp[-5].sql_node));
      std::unique_ptr<SubQueryExpr> left(new SubQueryExpr(std::move(left_query)));
      std::unique_ptr<ParsedSqlNode> right_query((yyvsp[-1].sql_node));
      std::unique_ptr<SubQueryExpr> right(new SubQueryExpr(std::move(right_query)));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 3247 "yacc_sql.cpp"
    break;

  case 132: /* new_condition: LBRACE select_stmt RBRACE null_comparator LBRACE value value_list RBRACE  */
#line 1212 "yacc_sql.y"
                                                                               {
      std::unique_ptr<ParsedSqlNode> left_query((yyvsp[-6].sql_node));
      std::unique_ptr<SubQueryExpr> left(new SubQueryExpr(std::move(left_query)));
      std::vector<Value> *val_list;
      if ((yyvsp[-1].value_list) != nullptr) {
        val_list = (yyvsp[-1].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      std::unique_ptr<ValueListExpr> right(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-4].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3267 "yacc_sql.cpp"
    break;

  case 133: /* new_condition: LBRACE value value_list RBRACE null_comparator LBRACE select_stmt RBRACE  */
#line 1227 "yacc_sql.y"
                                                                               {
      std::unique_ptr<ParsedSqlNode> right_query((yyvsp[-1].sql_node));
      std::unique_ptr<SubQueryExpr> right(new SubQueryExpr(std::move(right_query)));
      std::vector<Value> *val_list;
      if ((yyvsp[-5].value_list) != nullptr) {
        val_list = (yyvsp[-5].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-6].value));
      delete (yyvsp[-6].value);
      std::unique_ptr<ValueListExpr> left(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3287 "yacc_sql.cpp"
    break;

  case 134: /* new_condition: LBRACE select_stmt RBRACE null_comparator expression  */
#line 1244 "yacc_sql.y"
                                                           {
      std::unique_ptr<ParsedSqlNode> left_query((yyvsp[-3].sql_node));
      std::unique_ptr<SubQueryExpr> left(new SubQueryExpr(std::move(left_query)));
      std::unique_ptr<Expression> right ((yyvsp[0].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3299 "yacc_sql.cpp"
    break;

  case 135: /* new_condition: expression null_comparator LBRACE select_stmt RBRACE  */
#line 1251 "yacc_sql.y"
                                                           {
      std::unique_ptr<ParsedSqlNode> right_query((yyvsp[-1].sql_node));
      std::unique_ptr<SubQueryExpr> right(new SubQueryExpr(std::move(right_query)));
      std::unique_ptr<Expression> left ((yyvsp[-4].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3311 "yacc_sql.cpp"
    break;

  case 136: /* new_condition: expression null_comparator expression  */
#line 1261 "yacc_sql.y"
                                            {
      std::unique_ptr<Expression> left ((yyvsp[-2].expression));
      std::unique_ptr<Expression> right ((yyvsp[0].expression));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3322 "yacc_sql.cpp"
    break;

  case 137: /* new_condition: expression null_comparator LBRACE value value_list RBRACE  */
#line 1268 "yacc_sql.y"
                                                                {
      std::unique_ptr<Expression> left ((yyvsp[-5].expression));
      std::vector<Value> *val_list;
      if ((yyvsp[-1].value_list) != nullptr) {
        val_list = (yyvsp[-1].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      std::unique_ptr<ValueListExpr> right(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-4].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3341 "yacc_sql.cpp"
    break;

  case 138: /* new_condition: LBRACE value value_list RBRACE null_comparator expression  */
#line 1282 "yacc_sql.y"
                                                                {
      std::unique_ptr<Expression> right ((yyvsp[0].expression));
      std::vector<Value> *val_list;
      if ((yyvsp[-3].value_list) != nullptr) {
        val_list = (yyvsp[-3].value_list);
      } else {
        val_list = new std::vector<Value>();
      }
      val_list->emplace(val_list->begin(), *(yyvsp[-4].value));
      delete (yyvsp[-4].value);
      std::unique_ptr<ValueListExpr> left(new ValueListExpr(val_list));
      (yyval.new_condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
      // $$.reset(expr);
    }
#line 3360 "yacc_sql.cpp"
    break;

  case 139: /* where: %empty  */
#line 1300 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3368 "yacc_sql.cpp"
    break;

  case 140: /* where: WHERE condition_list  */
#line 1303 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3376 "yacc_sql.cpp"
    break;

  case 141: /* where: WHERE subquery_value_list  */
#line 1306 "yacc_sql.y"
                                {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3384 "yacc_sql.cpp"
    break;

  case 142: /* subquery_value_list: %empty  */
#line 1312 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3392 "yacc_sql.cpp"
    break;

  case 143: /* subquery_value_list: subquery  */
#line 1315 "yacc_sql.y"
               {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3402 "yacc_sql.cpp"
    break;

  case 144: /* subquery_value_list: subquery AND subquery_value_list  */
#line 1320 "yacc_sql.y"
                                       {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3412 "yacc_sql.cpp"
    break;

  case 145: /* subquery_value_list: subquery AND condition_list  */
#line 1325 "yacc_sql.y"
                                  {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3422 "yacc_sql.cpp"
    break;

  case 146: /* subquery: rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 1332 "yacc_sql.y"
                                               {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
      (yyval.condition)->comp = (yyvsp[-3].comp);
      (yyval.condition)->right_value_type = ValueType::SUB_QUERY;
      
      (yyval.condition)->right_sub_queries = (yyvsp[-1].sql_node);
      delete (yyvsp[-4].rel_attr);
      
    }
#line 3438 "yacc_sql.cpp"
    break;

  case 147: /* subquery: LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 1343 "yacc_sql.y"
                                                 {
      (yyval.condition) = new ConditionSqlNode;
      
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      if ((yyval.condition)->comp == CompOp::LESS_THAN) {
        (yyval.condition)->comp = CompOp::GREAT_THAN;
      } else if ((yyval.condition)->comp == CompOp::LESS_EQUAL) {
        (yyval.condition)->comp = CompOp::GREAT_EQUAL;
      } else if ((yyval.condition)->comp == CompOp::GREAT_THAN) {
        (yyval.condition)->comp = CompOp::LESS_THAN;
      } else if ((yyval.condition)->comp == CompOp::GREAT_EQUAL) {
        (yyval.condition)->comp = CompOp::LESS_EQUAL;
      } 
      (yyval.condition)->right_value_type = ValueType::SUB_QUERY;
      (yyval.condition)->right_sub_queries = (yyvsp[-3].sql_node);
      delete (yyvsp[0].rel_attr);
    }
#line 3462 "yacc_sql.cpp"
    break;

  case 148: /* subquery: rel_attr comp_op LBRACE value value_list RBRACE  */
#line 1362 "yacc_sql.y"
                                                      {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->comp = (yyvsp[-4].comp);
      (yyval.condition)->right_value_type = ValueType::VALUE_LIST;
      delete (yyvsp[-5].rel_attr);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->value_list = (yyvsp[-1].value_list);
      } else {
        (yyval.condition)->value_list = new std::vector<Value>();
      }
      (yyval.condition)->value_list->emplace((yyval.condition)->value_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
    }
#line 3482 "yacc_sql.cpp"
    break;

  case 149: /* subquery: LBRACE value value_list RBRACE comp_op rel_attr  */
#line 1377 "yacc_sql.y"
                                                      {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      if ((yyval.condition)->comp == CompOp::LESS_THAN) {
        (yyval.condition)->comp = CompOp::GREAT_THAN;
      } else if ((yyval.condition)->comp == CompOp::LESS_EQUAL) {
        (yyval.condition)->comp = CompOp::GREAT_EQUAL;
      } else if ((yyval.condition)->comp == CompOp::GREAT_THAN) {
        (yyval.condition)->comp = CompOp::LESS_THAN;
      } else if ((yyval.condition)->comp == CompOp::GREAT_EQUAL) {
        (yyval.condition)->comp = CompOp::LESS_EQUAL;
      } 
      (yyval.condition)->right_value_type = ValueType::VALUE_LIST;
      if ((yyvsp[-3].value_list) != nullptr) {
        (yyval.condition)->value_list = (yyvsp[-3].value_list);
      } else {
        (yyval.condition)->value_list = new vector<Value>();
      }
      (yyval.condition)->value_list->emplace((yyval.condition)->value_list->begin(), *(yyvsp[-4].value));
      delete (yyvsp[-4].value);
      delete (yyvsp[0].rel_attr);
    }
#line 3511 "yacc_sql.cpp"
    break;

  case 150: /* condition_list: %empty  */
#line 1406 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3519 "yacc_sql.cpp"
    break;

  case 151: /* condition_list: condition  */
#line 1409 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 3529 "yacc_sql.cpp"
    break;

  case 152: /* condition_list: condition AND condition_list  */
#line 1414 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3539 "yacc_sql.cpp"
    break;

  case 153: /* condition_list: condition AND subquery_value_list  */
#line 1419 "yacc_sql.y"
                                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 3549 "yacc_sql.cpp"
    break;

  case 154: /* condition: rel_attr comp_op value  */
#line 1427 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_value_type = ValueType::CONSTANT;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 3565 "yacc_sql.cpp"
    break;

  case 155: /* condition: value comp_op value  */
#line 1439 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_value_type = ValueType::CONSTANT;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 3581 "yacc_sql.cpp"
    break;

  case 156: /* condition: rel_attr comp_op rel_attr  */
#line 1451 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 3597 "yacc_sql.cpp"
    break;

  case 157: /* condition: value comp_op rel_attr  */
#line 1463 "yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 3613 "yacc_sql.cpp"
    break;

  case 158: /* condition: value IS null  */
#line 1474 "yacc_sql.y"
                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NULL_;
      delete (yyvsp[-2].value);
    }
#line 3626 "yacc_sql.cpp"
    break;

  case 159: /* condition: value IS NOT null  */
#line 1482 "yacc_sql.y"
                        {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-3].value);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NOT_NULL_;
      delete (yyvsp[-3].value);
    }
#line 3639 "yacc_sql.cpp"
    break;

  case 160: /* condition: value comp_op null  */
#line 1490 "yacc_sql.y"
                         {
      cout << "hello\n";
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[-2].value);
    }
#line 3653 "yacc_sql.cpp"
    break;

  case 161: /* condition: null comp_op value  */
#line 1499 "yacc_sql.y"
                         {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->left_value = *(yyvsp[0].value);
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].value);
    }
#line 3666 "yacc_sql.cpp"
    break;

  case 162: /* condition: rel_attr IS null  */
#line 1507 "yacc_sql.y"
                       {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NULL_;
      delete (yyvsp[-2].rel_attr);
    }
#line 3679 "yacc_sql.cpp"
    break;

  case 163: /* condition: rel_attr IS NOT null  */
#line 1515 "yacc_sql.y"
                           {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-3].rel_attr);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NOT_NULL_;
      delete (yyvsp[-3].rel_attr);
    }
#line 3692 "yacc_sql.cpp"
    break;

  case 164: /* condition: rel_attr comp_op null  */
#line 1523 "yacc_sql.y"
                            {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[-2].rel_attr);
    }
#line 3705 "yacc_sql.cpp"
    break;

  case 165: /* condition: null comp_op rel_attr  */
#line 1531 "yacc_sql.y"
                            {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].rel_attr);
    }
#line 3718 "yacc_sql.cpp"
    break;

  case 166: /* condition: null IS null  */
#line 1539 "yacc_sql.y"
                   {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value.set_int(0);
      (yyval.condition)->right_value.set_int(0);
      (yyval.condition)->comp = EQUAL_TO;
    }
#line 3731 "yacc_sql.cpp"
    break;

  case 167: /* condition: null IS NOT null  */
#line 1547 "yacc_sql.y"
                       {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value.set_int(0);
      (yyval.condition)->right_value.set_int(1);
      (yyval.condition)->comp = EQUAL_TO;
    }
#line 3744 "yacc_sql.cpp"
    break;

  case 168: /* condition: null comp_op null  */
#line 1555 "yacc_sql.y"
                        {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->left_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = (yyvsp[-1].comp);
    }
#line 3755 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: EQ  */
#line 1565 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3761 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: LT  */
#line 1566 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3767 "yacc_sql.cpp"
    break;

  case 171: /* comp_op: GT  */
#line 1567 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3773 "yacc_sql.cpp"
    break;

  case 172: /* comp_op: LE  */
#line 1568 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3779 "yacc_sql.cpp"
    break;

  case 173: /* comp_op: GE  */
#line 1569 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3785 "yacc_sql.cpp"
    break;

  case 174: /* comp_op: NE  */
#line 1570 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3791 "yacc_sql.cpp"
    break;

  case 175: /* comp_op: LIKE  */
#line 1571 "yacc_sql.y"
           { (yyval.comp) = LK; }
#line 3797 "yacc_sql.cpp"
    break;

  case 176: /* comp_op: NOT LIKE  */
#line 1572 "yacc_sql.y"
               {(yyval.comp) = NOT_LK; }
#line 3803 "yacc_sql.cpp"
    break;

  case 177: /* comp_op: IN  */
#line 1573 "yacc_sql.y"
         { (yyval.comp) = IN_; }
#line 3809 "yacc_sql.cpp"
    break;

  case 178: /* comp_op: NOT IN  */
#line 1574 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_; }
#line 3815 "yacc_sql.cpp"
    break;

  case 179: /* comp_op: EXISTS  */
#line 1575 "yacc_sql.y"
             { (yyval.comp) = EXISTS_; }
#line 3821 "yacc_sql.cpp"
    break;

  case 180: /* comp_op: NOT EXISTS  */
#line 1576 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_; }
#line 3827 "yacc_sql.cpp"
    break;

  case 181: /* null_comparator: comp_op  */
#line 1580 "yacc_sql.y"
          {
    (yyval.comp) = (yyvsp[0].comp);
  }
#line 3835 "yacc_sql.cpp"
    break;

  case 182: /* null_comparator: IS  */
#line 1583 "yacc_sql.y"
       {
    (yyval.comp) = IS_NULL_;
  }
#line 3843 "yacc_sql.cpp"
    break;

  case 183: /* null_comparator: IS NOT  */
#line 1586 "yacc_sql.y"
           {
    (yyval.comp) = IS_NOT_NULL_;
  }
#line 3851 "yacc_sql.cpp"
    break;

  case 184: /* group_by: %empty  */
#line 1593 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3859 "yacc_sql.cpp"
    break;

  case 185: /* group_by: GROUP BY expression_list having_clause  */
#line 1596 "yacc_sql.y"
                                             {
      (yyval.expression_list) = (yyvsp[-1].expression_list);
      
      /*delete $3;*/
    }
#line 3869 "yacc_sql.cpp"
    break;

  case 186: /* having_clause: %empty  */
#line 1604 "yacc_sql.y"
    {
      // no having clause
      (yyval.condition_list) = nullptr;
    }
#line 3878 "yacc_sql.cpp"
    break;

  case 187: /* having_clause: HAVING condition_list  */
#line 1608 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3886 "yacc_sql.cpp"
    break;

  case 188: /* order_by: %empty  */
#line 1613 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3894 "yacc_sql.cpp"
    break;

  case 189: /* order_by: ORDER BY order_list  */
#line 1616 "yacc_sql.y"
                          {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3902 "yacc_sql.cpp"
    break;

  case 190: /* order_list: rel_attr  */
#line 1621 "yacc_sql.y"
           {
    //std::cout << "[1]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[0].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[0].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[0].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3917 "yacc_sql.cpp"
    break;

  case 191: /* order_list: rel_attr COMMA order_list  */
#line 1631 "yacc_sql.y"
                              {
    //std::cout << "[2]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-2].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-2].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-2].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3932 "yacc_sql.cpp"
    break;

  case 192: /* order_list: rel_attr ASC  */
#line 1641 "yacc_sql.y"
                 {
    //std::cout << "[3]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3947 "yacc_sql.cpp"
    break;

  case 193: /* order_list: rel_attr ASC COMMA order_list  */
#line 1651 "yacc_sql.y"
                                  {
    //std::cout << "[4]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-3].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3962 "yacc_sql.cpp"
    break;

  case 194: /* order_list: rel_attr DESC  */
#line 1661 "yacc_sql.y"
                  {
    //std::cout << "[5]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = false;
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
    std::cout << (*(yyval.order_by_list))[0].attribute_name << '\n';
  }
#line 3978 "yacc_sql.cpp"
    break;

  case 195: /* order_list: rel_attr DESC COMMA order_list  */
#line 1672 "yacc_sql.y"
                                   {
    //std::cout << "[6]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = false;
    delete (yyvsp[-3].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3993 "yacc_sql.cpp"
    break;

  case 196: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1685 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 4007 "yacc_sql.cpp"
    break;

  case 197: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1698 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 4016 "yacc_sql.cpp"
    break;

  case 198: /* set_variable_stmt: SET ID EQ value  */
#line 1706 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 4028 "yacc_sql.cpp"
    break;


#line 4032 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1718 "yacc_sql.y"

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
