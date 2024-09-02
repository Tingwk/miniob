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

string token_name(const char *sql_string, YYLTYPE *llocp)
{
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


#line 125 "yacc_sql.cpp"

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
  YYSYMBOL_INNER = 27,                     /* INNER  */
  YYSYMBOL_JOIN = 28,                      /* JOIN  */
  YYSYMBOL_STRING_T = 29,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 30,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 31,                      /* HELP  */
  YYSYMBOL_EXIT = 32,                      /* EXIT  */
  YYSYMBOL_DOT = 33,                       /* DOT  */
  YYSYMBOL_INTO = 34,                      /* INTO  */
  YYSYMBOL_VALUES = 35,                    /* VALUES  */
  YYSYMBOL_FROM = 36,                      /* FROM  */
  YYSYMBOL_WHERE = 37,                     /* WHERE  */
  YYSYMBOL_AND = 38,                       /* AND  */
  YYSYMBOL_SET = 39,                       /* SET  */
  YYSYMBOL_ON = 40,                        /* ON  */
  YYSYMBOL_LOAD = 41,                      /* LOAD  */
  YYSYMBOL_DATA = 42,                      /* DATA  */
  YYSYMBOL_INFILE = 43,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 44,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 45,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 46,                    /* FORMAT  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_ORDER = 48,                     /* ORDER  */
  YYSYMBOL_ASC = 49,                       /* ASC  */
  YYSYMBOL_LT = 50,                        /* LT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_NOT = 55,                       /* NOT  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_EXISTS = 58,                    /* EXISTS  */
  YYSYMBOL_UNIQUE = 59,                    /* UNIQUE  */
  YYSYMBOL_ROUND = 60,                     /* ROUND  */
  YYSYMBOL_LENGTH = 61,                    /* LENGTH  */
  YYSYMBOL_DATA_FORMAT = 62,               /* DATA_FORMAT  */
  YYSYMBOL_null = 63,                      /* null  */
  YYSYMBOL_IS = 64,                        /* IS  */
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '/'  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command_wrapper = 76,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 77,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 78,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 79,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 80,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 81,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 82,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 83,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 84,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 85,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 86,         /* create_index_stmt  */
  YYSYMBOL_id_list = 87,                   /* id_list  */
  YYSYMBOL_drop_index_stmt = 88,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 89,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_null_def = 92,                  /* null_def  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_insert_stmt = 95,               /* insert_stmt  */
  YYSYMBOL_value_with_null_list = 96,      /* value_with_null_list  */
  YYSYMBOL_value_with_null = 97,           /* value_with_null  */
  YYSYMBOL_value_list = 98,                /* value_list  */
  YYSYMBOL_value = 99,                     /* value  */
  YYSYMBOL_storage_format = 100,           /* storage_format  */
  YYSYMBOL_delete_stmt = 101,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 102,              /* update_stmt  */
  YYSYMBOL_select_stmt = 103,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 104,                /* calc_stmt  */
  YYSYMBOL_expression_list = 105,          /* expression_list  */
  YYSYMBOL_expression = 106,               /* expression  */
  YYSYMBOL_rel_attr = 107,                 /* rel_attr  */
  YYSYMBOL_rel_list = 108,                 /* rel_list  */
  YYSYMBOL_where = 109,                    /* where  */
  YYSYMBOL_condition_list = 110,           /* condition_list  */
  YYSYMBOL_condition = 111,                /* condition  */
  YYSYMBOL_comp_op = 112,                  /* comp_op  */
  YYSYMBOL_group_by = 113,                 /* group_by  */
  YYSYMBOL_order_by = 114,                 /* order_by  */
  YYSYMBOL_order_list = 115,               /* order_list  */
  YYSYMBOL_load_data_stmt = 116,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 117,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 118,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 119             /* opt_semicolon  */
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
#define YYFINAL  65
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  266

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


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
       2,     2,    71,    69,     2,    70,     2,    72,     2,     2,
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
      65,    66,    67,    68,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   213,   213,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   244,   250,   255,   261,   267,   273,   279,
     286,   292,   300,   316,   335,   338,   350,   360,   384,   387,
     400,   414,   431,   434,   437,   441,   444,   445,   446,   447,
     450,   466,   469,   479,   482,   490,   493,   504,   508,   512,
     521,   524,   531,   543,   558,   593,   602,   607,   616,   622,
     632,   638,   647,   653,   663,   666,   669,   672,   675,   679,
     682,   687,   692,   698,   706,   712,   728,   731,   745,   758,
     779,   782,   785,   799,   819,   836,   880,   883,   888,   895,
     907,   919,   931,   943,   951,   959,   968,   976,   984,   992,
    1000,  1012,  1013,  1014,  1015,  1016,  1017,  1018,  1019,  1020,
    1021,  1022,  1023,  1029,  1032,  1039,  1042,  1047,  1057,  1067,
    1077,  1087,  1098,  1110,  1123,  1131,  1141,  1142
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
  "INNER", "JOIN", "STRING_T", "FLOAT_T", "HELP", "EXIT", "DOT", "INTO",
  "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "STORAGE", "FORMAT", "EQ", "ORDER", "ASC", "LT", "GT", "LE",
  "GE", "NE", "NOT", "LIKE", "IN", "EXISTS", "UNIQUE", "ROUND", "LENGTH",
  "DATA_FORMAT", "null", "IS", "NUMBER", "FLOAT", "ID", "SSS", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "id_list", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "null_def", "number",
  "type", "insert_stmt", "value_with_null_list", "value_with_null",
  "value_list", "value", "storage_format", "delete_stmt", "update_stmt",
  "select_stmt", "calc_stmt", "expression_list", "expression", "rel_attr",
  "rel_list", "where", "condition_list", "condition", "comp_op",
  "group_by", "order_by", "order_list", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-208)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     157,    10,    69,    53,    53,   -55,     7,  -208,    12,    -6,
     -20,  -208,  -208,  -208,  -208,  -208,    16,    31,   157,    84,
      87,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,    32,    34,    95,    55,    65,    78,  -208,  -208,    -9,
    -208,    78,  -208,  -208,  -208,    24,    98,  -208,  -208,    74,
      90,   111,   104,   133,  -208,  -208,  -208,  -208,   159,   144,
     119,  -208,   151,   164,    38,    21,   132,  -208,    53,    78,
      78,    78,    78,   140,   173,   172,   147,   163,   148,   160,
     175,   203,   177,  -208,   225,   237,    83,  -208,  -208,   -33,
     -33,  -208,  -208,     6,   239,   -11,  -208,   212,  -208,   226,
     110,   240,   243,   196,  -208,    53,   244,   245,   197,   241,
     172,   -15,    -5,   198,   234,   168,   183,  -208,   230,   163,
     262,  -208,  -208,  -208,  -208,    13,   160,   251,   205,   254,
    -208,    53,    53,     6,   207,   268,  -208,   255,  -208,   256,
     258,  -208,  -208,  -208,  -208,  -208,  -208,    57,  -208,  -208,
    -208,    99,   213,   -38,    62,   -32,    93,   127,   172,   214,
     217,   216,  -208,  -208,   240,   238,   263,   218,  -208,  -208,
    -208,   -12,   282,   242,   -15,   267,   163,   269,   198,  -208,
    -208,  -208,  -208,  -208,  -208,   228,  -208,  -208,  -208,  -208,
     229,  -208,    -5,  -208,  -208,  -208,   183,  -208,  -208,  -208,
    -208,   273,  -208,  -208,   248,  -208,   221,   275,   263,   127,
    -208,    53,   292,  -208,   255,  -208,   256,   198,   231,  -208,
    -208,   256,   277,   137,   -29,   252,   263,  -208,   280,     6,
    -208,   231,  -208,  -208,   231,  -208,   281,  -208,  -208,   235,
    -208,  -208,  -208,     0,  -208,  -208,  -208,  -208,   283,   231,
     284,   231,  -208,   231,  -208,  -208
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     136,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,    57,    58,    81,
      59,     0,    83,    80,    65,    66,     0,    31,    30,     0,
       0,     0,     0,     0,   134,     1,   137,     2,     0,     0,
       0,    29,     0,    81,     0,     0,     0,    79,     0,     0,
       0,     0,     0,     0,     0,    90,     0,     0,     0,     0,
       0,     0,     0,    78,    68,     0,     0,    82,    67,    74,
      75,    76,    77,    86,     0,    96,    62,     0,   135,     0,
       0,    38,     0,     0,    36,     0,    72,    70,     0,     0,
      90,     0,     0,     0,    84,     0,     0,    91,    97,     0,
       0,    46,    49,    47,    48,    42,     0,     0,     0,     0,
      69,     0,     0,    86,     0,   123,    54,    51,    53,    55,
       0,   111,   112,   113,   114,   115,   116,     0,   117,   119,
     121,     0,     0,     0,     0,     0,     0,    96,    90,     0,
       0,     0,    43,    41,    38,    60,    34,     0,    73,    71,
      87,    86,     0,   125,     0,     0,     0,     0,     0,   118,
     120,   122,   106,   110,    85,     0,   103,   105,   100,   102,
       0,   107,     0,   109,    99,   101,     0,    98,    63,   133,
      45,     0,    44,    39,     0,    37,     0,     0,    34,    96,
      88,     0,     0,    64,    51,    50,    55,     0,     0,   104,
     108,    55,     0,     0,    42,     0,    34,    32,     0,    86,
     124,     0,    52,    56,     0,    93,     0,    92,    40,     0,
      35,    33,    89,   127,   126,    95,    94,    61,   131,     0,
     129,     0,   128,     0,   132,   130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,   285,  -208,  -208,  -208,  -208,  -208,  -208,  -208,
    -208,  -208,  -208,  -207,  -208,  -208,   134,   170,    73,  -208,
    -208,  -208,    85,   126,  -189,   -86,  -208,  -208,  -208,  -120,
    -208,    -4,   131,  -102,  -137,   -98,  -153,  -208,  -121,  -208,
    -208,   -76,  -208,  -208,  -208,  -208
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   217,    31,    32,   137,   111,   173,   211,
     135,    33,   185,   147,   187,    53,   215,    34,    35,    36,
      37,    54,    55,   253,   120,   106,   127,   128,   161,   183,
     223,   254,    38,    39,    40,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,   108,   150,   126,   164,   166,   180,     4,   122,   118,
      75,   238,    57,   258,   207,   119,    58,   195,    41,   125,
      42,   259,   145,   200,    76,   196,   171,   118,   219,   250,
      60,   201,   170,   119,   172,   148,   149,   243,    81,    82,
      46,    94,   246,   168,   220,    78,    59,    61,   146,   260,
      47,    48,   123,    50,    47,    48,   124,    50,    93,   193,
      47,    48,   199,    50,   205,   206,   239,   228,   171,    43,
     208,    95,    46,    63,    98,   192,   172,    44,   198,    45,
     204,   125,   232,    62,    65,   233,    47,    48,    49,    50,
      66,    51,    52,    79,    80,    81,    82,    46,   148,    68,
     226,    69,   252,   117,    78,    70,   244,    79,    80,    81,
      82,   140,   202,   189,   190,   191,   231,   206,    47,    48,
      49,    50,    71,    51,    52,   197,   245,    47,    48,   124,
      50,   205,    72,   125,    83,   131,   132,   178,   179,   133,
     134,    84,   255,    47,    48,    73,    50,   204,    51,    52,
      86,    87,    79,    80,    81,    82,   203,    85,    47,    48,
     124,    50,     1,     2,    47,    48,   124,    50,     3,     4,
       5,     6,     7,     8,     9,    10,    88,    74,    89,    11,
      12,    13,    77,   262,    90,   264,    91,   265,    14,    15,
     123,    92,    47,    48,   124,    50,    16,    76,    17,    97,
     203,    18,    47,    48,   124,    50,    96,   103,   104,   105,
      99,   100,   101,   102,   107,   151,   109,   240,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   110,    47,    48,
     151,    50,   163,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   112,   113,   114,   151,   115,   165,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   116,   121,   129,
     130,   136,   138,   139,   143,   141,   142,   162,   167,   144,
     169,   175,   176,   177,   181,   182,   184,   186,   188,   212,
     194,   209,   210,   214,   216,   218,   221,   225,   236,   227,
     222,   229,   230,   234,   235,   237,   241,   247,   124,   249,
     251,   256,   257,    64,   261,   263,   174,   248,   213,   242,
     224
};

static const yytype_int16 yycheck[] =
{
       4,    87,   122,   105,   125,   126,   143,    12,    19,    21,
      19,   218,    67,    13,   167,    27,     9,    55,     8,   105,
      10,    21,   120,    55,    33,    63,    55,    21,    40,   236,
      36,    63,    19,    27,    63,   121,   122,   226,    71,    72,
      19,    20,   231,   129,   181,    21,    34,    67,    63,    49,
      65,    66,    63,    68,    65,    66,    67,    68,    20,   161,
      65,    66,   164,    68,   166,   167,   219,   188,    55,    59,
     168,    75,    19,    42,    78,   161,    63,     8,   164,    10,
     166,   167,   202,    67,     0,   206,    65,    66,    67,    68,
       3,    70,    71,    69,    70,    71,    72,    19,   184,    67,
     186,    67,   239,    20,    21,    10,   227,    69,    70,    71,
      72,   115,    19,    56,    57,    58,   202,   219,    65,    66,
      67,    68,    67,    70,    71,    63,   228,    65,    66,    67,
      68,   233,    67,   219,    36,    25,    26,   141,   142,    29,
      30,    67,   244,    65,    66,    67,    68,   233,    70,    71,
      39,    47,    69,    70,    71,    72,    63,    67,    65,    66,
      67,    68,     5,     6,    65,    66,    67,    68,    11,    12,
      13,    14,    15,    16,    17,    18,    43,    46,    19,    22,
      23,    24,    51,   259,    40,   261,    67,   263,    31,    32,
      63,    40,    65,    66,    67,    68,    39,    33,    41,    67,
      63,    44,    65,    66,    67,    68,    75,    67,    35,    37,
      79,    80,    81,    82,    67,    47,    68,   221,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    67,    65,    66,
      47,    68,    64,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    67,    40,    67,    47,    21,    64,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    20,    19,    47,
      34,    21,    19,    67,    67,    21,    21,    33,    38,    28,
       8,    20,    67,    19,    67,     7,    21,    21,    20,    63,
      67,    67,    65,    45,    21,    67,     4,    20,    67,    20,
      48,    63,    63,    20,    46,    20,     4,    20,    67,    47,
      20,    20,    67,    18,    21,    21,   136,   234,   174,   224,
     184
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,     6,    11,    12,    13,    14,    15,    16,    17,
      18,    22,    23,    24,    31,    32,    39,    41,    44,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    88,    89,    95,   101,   102,   103,   104,   116,   117,
     118,     8,    10,    59,     8,    10,    19,    65,    66,    67,
      68,    70,    71,    99,   105,   106,   105,    67,     9,    34,
      36,    67,    67,    42,    76,     0,     3,   119,    67,    67,
      10,    67,    67,    67,   106,    19,    33,   106,    21,    69,
      70,    71,    72,    36,    67,    67,    39,    47,    43,    19,
      40,    67,    40,    20,    20,   105,   106,    67,   105,   106,
     106,   106,   106,    67,    35,    37,   109,    67,    99,    68,
      67,    91,    67,    40,    67,    21,    20,    20,    21,    27,
     108,    19,    19,    63,    67,    99,   107,   110,   111,    47,
      34,    25,    26,    29,    30,    94,    21,    90,    19,    67,
     105,    21,    21,    67,    28,   109,    63,    97,    99,    99,
     103,    47,    50,    51,    52,    53,    54,    55,    56,    57,
      58,   112,    33,    64,   112,    64,   112,    38,    99,     8,
      19,    55,    63,    92,    91,    20,    67,    19,   105,   105,
     108,    67,     7,   113,    21,    96,    21,    98,    20,    56,
      57,    58,    99,   107,    67,    55,    63,    63,    99,   107,
      55,    63,    19,    63,    99,   107,   107,   110,   109,    67,
      65,    93,    63,    90,    45,   100,    21,    87,    67,    40,
     108,     4,    48,   114,    97,    20,    99,    20,   112,    63,
      63,    99,   103,   112,    20,    46,    67,    20,    87,   110,
     105,     4,    96,    98,   112,   107,    98,    20,    92,    47,
      87,    20,   108,   107,   115,   107,    20,    67,    13,    21,
      49,    21,   115,    21,   115,   115
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    86,    87,    87,    88,    89,    90,    90,
      91,    91,    92,    92,    92,    93,    94,    94,    94,    94,
      95,    96,    96,    97,    97,    98,    98,    99,    99,    99,
     100,   100,   101,   102,   103,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   107,   107,   108,   108,   108,   108,
     109,   109,   109,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   113,   113,   114,   114,   115,   115,   115,
     115,   115,   115,   116,   117,   118,   119,   119
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     8,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     1,     0,     3,     1,     1,     1,
       0,     4,     4,     7,     8,     2,     1,     3,     3,     5,
       4,     6,     4,     6,     3,     3,     3,     3,     3,     2,
       1,     1,     3,     1,     1,     3,     0,     3,     4,     6,
       0,     2,     6,     6,     7,     7,     0,     1,     3,     3,
       3,     3,     3,     3,     4,     3,     3,     3,     4,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     0,     3,     0,     3,     1,     3,     2,
       4,     2,     4,     7,     2,     4,     0,     1
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
#line 214 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1833 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 244 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1842 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 250 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1850 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 255 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1858 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 261 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1866 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 267 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1874 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 273 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1882 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 279 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1892 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 286 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1900 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 292 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1910 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 301 "yacc_sql.y"
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
#line 1930 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID id_list RBRACE  */
#line 317 "yacc_sql.y"
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
#line 1950 "yacc_sql.cpp"
    break;

  case 34: /* id_list: %empty  */
#line 335 "yacc_sql.y"
  {
    (yyval.id_list_type) = nullptr;
  }
#line 1958 "yacc_sql.cpp"
    break;

  case 35: /* id_list: COMMA ID id_list  */
#line 338 "yacc_sql.y"
                     {
    if ((yyvsp[0].id_list_type) != nullptr) {
      (yyval.id_list_type) = (yyvsp[0].id_list_type);
    } else {
      (yyval.id_list_type) = new std::vector<std::string>();
    }
    (yyval.id_list_type)->emplace((yyval.id_list_type)->begin(), (yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 1972 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 351 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1984 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 361 "yacc_sql.y"
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
#line 2009 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 384 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2017 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 388 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2031 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 401 "yacc_sql.y"
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
#line 2049 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type null_def  */
#line 415 "yacc_sql.y"
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
#line 2067 "yacc_sql.cpp"
    break;

  case 42: /* null_def: %empty  */
#line 431 "yacc_sql.y"
    {
      (yyval.number_ptr) = nullptr;
    }
#line 2075 "yacc_sql.cpp"
    break;

  case 43: /* null_def: null  */
#line 434 "yacc_sql.y"
           {
      (yyval.number_ptr) = new int(0);
    }
#line 2083 "yacc_sql.cpp"
    break;

  case 44: /* null_def: NOT null  */
#line 437 "yacc_sql.y"
               {
      (yyval.number_ptr) = new int(1);
    }
#line 2091 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 441 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2097 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 444 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2103 "yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 445 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2109 "yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 446 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2115 "yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 447 "yacc_sql.y"
             { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2121 "yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES LBRACE value_with_null value_with_null_list RBRACE  */
#line 451 "yacc_sql.y"
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
#line 2138 "yacc_sql.cpp"
    break;

  case 51: /* value_with_null_list: %empty  */
#line 466 "yacc_sql.y"
  {
    (yyval.value_list) = nullptr;
  }
#line 2146 "yacc_sql.cpp"
    break;

  case 52: /* value_with_null_list: COMMA value_with_null value_with_null_list  */
#line 469 "yacc_sql.y"
                                                { 
    if ((yyvsp[0].value_list) != nullptr) {
      (yyval.value_list) = (yyvsp[0].value_list);
    } else {
      (yyval.value_list) = new std::vector<Value>;
    }
    (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
    delete (yyvsp[-1].value);
  }
#line 2160 "yacc_sql.cpp"
    break;

  case 53: /* value_with_null: value  */
#line 479 "yacc_sql.y"
         {
    (yyval.value) = (yyvsp[0].value);
  }
#line 2168 "yacc_sql.cpp"
    break;

  case 54: /* value_with_null: null  */
#line 482 "yacc_sql.y"
         {
    (yyval.value) = new Value();
    (yyval.value)->set_null();
  }
#line 2177 "yacc_sql.cpp"
    break;

  case 55: /* value_list: %empty  */
#line 490 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2185 "yacc_sql.cpp"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 493 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 57: /* value: NUMBER  */
#line 504 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2208 "yacc_sql.cpp"
    break;

  case 58: /* value: FLOAT  */
#line 508 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2217 "yacc_sql.cpp"
    break;

  case 59: /* value: SSS  */
#line 512 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2228 "yacc_sql.cpp"
    break;

  case 60: /* storage_format: %empty  */
#line 521 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2236 "yacc_sql.cpp"
    break;

  case 61: /* storage_format: STORAGE FORMAT EQ ID  */
#line 525 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2244 "yacc_sql.cpp"
    break;

  case 62: /* delete_stmt: DELETE FROM ID where  */
#line 532 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2258 "yacc_sql.cpp"
    break;

  case 63: /* update_stmt: UPDATE ID SET ID EQ value where  */
#line 544 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->update.attribute_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.value = *(yyvsp[-1].value);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2275 "yacc_sql.cpp"
    break;

  case 64: /* select_stmt: SELECT expression_list FROM ID rel_list where group_by order_by  */
#line 559 "yacc_sql.y"
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
      
      if ((yyvsp[-2].condition_list) != nullptr) {
        //cout << (*$6)[0].right_sub_queries << '\n';
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-2].condition_list));
        delete (yyvsp[-2].condition_list);
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
#line 2312 "yacc_sql.cpp"
    break;

  case 65: /* calc_stmt: CALC expression_list  */
#line 594 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2322 "yacc_sql.cpp"
    break;

  case 66: /* expression_list: expression  */
#line 603 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2331 "yacc_sql.cpp"
    break;

  case 67: /* expression_list: expression COMMA expression_list  */
#line 608 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-2].expression));
    }
#line 2344 "yacc_sql.cpp"
    break;

  case 68: /* expression_list: ID LBRACE RBRACE  */
#line 616 "yacc_sql.y"
                       {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression *expr = new ErrorExpr();
      (yyval.expression_list)->emplace_back(expr);
      free((yyvsp[-2].string));
    }
#line 2355 "yacc_sql.cpp"
    break;

  case 69: /* expression_list: ID LBRACE RBRACE COMMA expression_list  */
#line 622 "yacc_sql.y"
                                             {
      if ((yyvsp[0].expression_list)) {
        delete (yyvsp[0].expression_list);
      }
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression *expr = new ErrorExpr();
      (yyval.expression_list)->emplace_back(expr);
      free((yyvsp[-4].string));
    }
#line 2369 "yacc_sql.cpp"
    break;

  case 70: /* expression_list: ID LBRACE expression RBRACE  */
#line 632 "yacc_sql.y"
                                  {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      auto expr = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
      (yyval.expression_list)->emplace_back(expr);
      free((yyvsp[-3].string));
    }
#line 2380 "yacc_sql.cpp"
    break;

  case 71: /* expression_list: ID LBRACE expression RBRACE COMMA expression_list  */
#line 638 "yacc_sql.y"
                                                         {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      int start = (yylsp[-5]).first_column;
      int end = (yylsp[-2]).last_column;
      auto expr = create_aggregate_expression((yyvsp[-5].string), (yyvsp[-3].expression), sql_string, &(yyloc));
      expr->set_name(std::string(sql_string+ start, end- start + 1));
      free((yyvsp[-5].string));
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), expr);
    }
#line 2394 "yacc_sql.cpp"
    break;

  case 72: /* expression_list: ID LBRACE expression_list RBRACE  */
#line 647 "yacc_sql.y"
                                       {
      delete (yyvsp[-1].expression_list);
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression* expr = new ErrorExpr;
      (yyval.expression_list)->emplace_back(expr);
    }
#line 2405 "yacc_sql.cpp"
    break;

  case 73: /* expression_list: ID LBRACE expression_list RBRACE COMMA expression_list  */
#line 653 "yacc_sql.y"
                                                             {
      delete (yyvsp[-3].expression_list);
      delete (yyvsp[0].expression_list);
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      Expression* expr = new ErrorExpr;
      (yyval.expression_list)->emplace_back(expr);
    }
#line 2417 "yacc_sql.cpp"
    break;

  case 74: /* expression: expression '+' expression  */
#line 663 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2425 "yacc_sql.cpp"
    break;

  case 75: /* expression: expression '-' expression  */
#line 666 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2433 "yacc_sql.cpp"
    break;

  case 76: /* expression: expression '*' expression  */
#line 669 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2441 "yacc_sql.cpp"
    break;

  case 77: /* expression: expression '/' expression  */
#line 672 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2449 "yacc_sql.cpp"
    break;

  case 78: /* expression: LBRACE expression RBRACE  */
#line 675 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 79: /* expression: '-' expression  */
#line 679 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 80: /* expression: value  */
#line 682 "yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2476 "yacc_sql.cpp"
    break;

  case 81: /* expression: ID  */
#line 687 "yacc_sql.y"
         {
      (yyval.expression) = new UnboundFieldExpr("", (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      free((yyvsp[0].string));
    }
#line 2486 "yacc_sql.cpp"
    break;

  case 82: /* expression: ID DOT ID  */
#line 692 "yacc_sql.y"
                {
      (yyval.expression) = new UnboundFieldExpr((yyvsp[-2].string), (yyvsp[0].string));
      (yyval.expression)->set_name(token_name(sql_string,&(yyloc)));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2497 "yacc_sql.cpp"
    break;

  case 83: /* expression: '*'  */
#line 698 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2505 "yacc_sql.cpp"
    break;

  case 84: /* rel_attr: ID  */
#line 706 "yacc_sql.y"
       {
      std::cout << (yyvsp[0].string)<<'\n';
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2516 "yacc_sql.cpp"
    break;

  case 85: /* rel_attr: ID DOT ID  */
#line 712 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2528 "yacc_sql.cpp"
    break;

  case 86: /* rel_list: %empty  */
#line 728 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2536 "yacc_sql.cpp"
    break;

  case 87: /* rel_list: COMMA ID rel_list  */
#line 731 "yacc_sql.y"
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
#line 2555 "yacc_sql.cpp"
    break;

  case 88: /* rel_list: INNER JOIN ID rel_list  */
#line 745 "yacc_sql.y"
                             {
      (yyval.relation_list) = new RelListSqlNode();
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list)->relations.swap(((yyvsp[0].relation_list))->relations);
        (yyval.relation_list)->joins.swap(((yyvsp[0].relation_list))->joins);
        delete (yyvsp[0].relation_list);
      }
      JoinSqlNode join;
      join.type = JoinType::INNER_JOIN;
      (yyval.relation_list)->joins.emplace((yyval.relation_list)->joins.begin(), join);
      (yyval.relation_list)->relations.emplace((yyval.relation_list)->relations.begin(), (yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
#line 2573 "yacc_sql.cpp"
    break;

  case 89: /* rel_list: INNER JOIN ID ON condition_list rel_list  */
#line 758 "yacc_sql.y"
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
      (yyval.relation_list)->relations.emplace((yyval.relation_list)->relations.begin(), (yyvsp[-3].string));
      free((yyvsp[-3].string));
    }
#line 2595 "yacc_sql.cpp"
    break;

  case 90: /* where: %empty  */
#line 779 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2603 "yacc_sql.cpp"
    break;

  case 91: /* where: WHERE condition_list  */
#line 782 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2611 "yacc_sql.cpp"
    break;

  case 92: /* where: WHERE rel_attr comp_op LBRACE select_stmt RBRACE  */
#line 785 "yacc_sql.y"
                                                       {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      ConditionSqlNode q;
      q.left_value_type = ValueType::ATTRIBUTE;
      q.left_attr = *(yyvsp[-4].rel_attr);
      q.comp = (yyvsp[-3].comp);
      q.right_value_type = ValueType::SUB_QUERY;
      /*std::cout << "709 address:" << $5 << '\n';
      cout << $5->selection.relations[0] << '\n'; */
      q.right_sub_queries = (yyvsp[-1].sql_node);
      delete (yyvsp[-4].rel_attr);
      (yyval.condition_list)->emplace_back(q);
      // cout << (*$$)[0].right_sub_queries << '\n';
    }
#line 2630 "yacc_sql.cpp"
    break;

  case 93: /* where: WHERE LBRACE select_stmt RBRACE comp_op rel_attr  */
#line 799 "yacc_sql.y"
                                                       {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      ConditionSqlNode q;
      q.left_value_type = ValueType::ATTRIBUTE;
      q.left_attr = *(yyvsp[0].rel_attr);
      q.comp = (yyvsp[-1].comp);
      if (q.comp == CompOp::LESS_THAN) {
        q.comp = CompOp::GREAT_THAN;
      } else if (q.comp == CompOp::LESS_EQUAL) {
        q.comp = CompOp::GREAT_EQUAL;
      } else if (q.comp == CompOp::GREAT_THAN) {
        q.comp = CompOp::LESS_THAN;
      } else if (q.comp == CompOp::GREAT_EQUAL) {
        q.comp = CompOp::LESS_EQUAL;
      } 
      q.right_value_type = ValueType::SUB_QUERY;
      q.right_sub_queries = (yyvsp[-3].sql_node);
      delete (yyvsp[0].rel_attr);
      (yyval.condition_list)->emplace_back(q);
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 94: /* where: WHERE rel_attr comp_op LBRACE value value_list RBRACE  */
#line 819 "yacc_sql.y"
                                                            {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      ConditionSqlNode q;
      q.left_value_type = ValueType::ATTRIBUTE;
      q.left_attr = *(yyvsp[-5].rel_attr);
      q.comp = (yyvsp[-4].comp);
      q.right_value_type = ValueType::VALUE_LIST;
      delete (yyvsp[-5].rel_attr);
      if ((yyvsp[-1].value_list) != nullptr) {
        q.value_list = (yyvsp[-1].value_list);
      } else {
        q.value_list = new std::vector<Value>();
      }
      q.value_list->emplace(q.value_list->begin(), *(yyvsp[-2].value));
      delete (yyvsp[-2].value);
      (yyval.condition_list)->emplace_back(q);
    }
#line 2677 "yacc_sql.cpp"
    break;

  case 95: /* where: WHERE LBRACE value value_list RBRACE comp_op rel_attr  */
#line 836 "yacc_sql.y"
                                                            {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      ConditionSqlNode q;
      q.left_value_type = ValueType::ATTRIBUTE;
      q.left_attr = *(yyvsp[0].rel_attr);
      q.comp = (yyvsp[-1].comp);
      if (q.comp == CompOp::LESS_THAN) {
        q.comp = CompOp::GREAT_THAN;
      } else if (q.comp == CompOp::LESS_EQUAL) {
        q.comp = CompOp::GREAT_EQUAL;
      } else if (q.comp == CompOp::GREAT_THAN) {
        q.comp = CompOp::LESS_THAN;
      } else if (q.comp == CompOp::GREAT_EQUAL) {
        q.comp = CompOp::LESS_EQUAL;
      } 
      q.right_value_type = ValueType::VALUE_LIST;
      if ((yyvsp[-3].value_list) != nullptr) {
        q.value_list = (yyvsp[-3].value_list);
      } else {
        q.value_list = new vector<Value>();
      }
      q.value_list->emplace(q.value_list->begin(), *(yyvsp[-4].value));
      delete (yyvsp[-4].value);
      delete (yyvsp[0].rel_attr);
      (yyval.condition_list)->emplace_back(q);
    }
#line 2708 "yacc_sql.cpp"
    break;

  case 96: /* condition_list: %empty  */
#line 880 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2716 "yacc_sql.cpp"
    break;

  case 97: /* condition_list: condition  */
#line 883 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 98: /* condition_list: condition AND condition_list  */
#line 888 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2736 "yacc_sql.cpp"
    break;

  case 99: /* condition: rel_attr comp_op value  */
#line 896 "yacc_sql.y"
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
#line 2752 "yacc_sql.cpp"
    break;

  case 100: /* condition: value comp_op value  */
#line 908 "yacc_sql.y"
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
#line 2768 "yacc_sql.cpp"
    break;

  case 101: /* condition: rel_attr comp_op rel_attr  */
#line 920 "yacc_sql.y"
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
#line 2784 "yacc_sql.cpp"
    break;

  case 102: /* condition: value comp_op rel_attr  */
#line 932 "yacc_sql.y"
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
#line 2800 "yacc_sql.cpp"
    break;

  case 103: /* condition: value IS null  */
#line 943 "yacc_sql.y"
                    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NULL_;
      delete (yyvsp[-2].value);
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 104: /* condition: value IS NOT null  */
#line 951 "yacc_sql.y"
                        {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-3].value);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NOT_NULL_;
      delete (yyvsp[-3].value);
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 105: /* condition: value comp_op null  */
#line 959 "yacc_sql.y"
                         {
      cout << "hello\n";
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[-2].value);
    }
#line 2840 "yacc_sql.cpp"
    break;

  case 106: /* condition: null comp_op value  */
#line 968 "yacc_sql.y"
                         {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->left_value = *(yyvsp[0].value);
      (yyval.condition)->left_value_type = ValueType::CONSTANT;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].value);
    }
#line 2853 "yacc_sql.cpp"
    break;

  case 107: /* condition: rel_attr IS null  */
#line 976 "yacc_sql.y"
                       {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NULL_;
      delete (yyvsp[-2].rel_attr);
    }
#line 2866 "yacc_sql.cpp"
    break;

  case 108: /* condition: rel_attr IS NOT null  */
#line 984 "yacc_sql.y"
                           {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-3].rel_attr);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = IS_NOT_NULL_;
      delete (yyvsp[-3].rel_attr);
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 109: /* condition: rel_attr comp_op null  */
#line 992 "yacc_sql.y"
                            {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[-2].rel_attr);
    }
#line 2892 "yacc_sql.cpp"
    break;

  case 110: /* condition: null comp_op rel_attr  */
#line 1000 "yacc_sql.y"
                            {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->right_value_type = ValueType::NULL_TYPE;
      (yyval.condition)->left_value_type = ValueType::ATTRIBUTE;
      (yyval.condition)->left_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);
      delete (yyvsp[0].rel_attr);
    }
#line 2905 "yacc_sql.cpp"
    break;

  case 111: /* comp_op: EQ  */
#line 1012 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2911 "yacc_sql.cpp"
    break;

  case 112: /* comp_op: LT  */
#line 1013 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2917 "yacc_sql.cpp"
    break;

  case 113: /* comp_op: GT  */
#line 1014 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2923 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: LE  */
#line 1015 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2929 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: GE  */
#line 1016 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2935 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: NE  */
#line 1017 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2941 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: LIKE  */
#line 1018 "yacc_sql.y"
           { (yyval.comp) = LK; }
#line 2947 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: NOT LIKE  */
#line 1019 "yacc_sql.y"
               {(yyval.comp) = NOT_LK; }
#line 2953 "yacc_sql.cpp"
    break;

  case 119: /* comp_op: IN  */
#line 1020 "yacc_sql.y"
         { (yyval.comp) = IN_; }
#line 2959 "yacc_sql.cpp"
    break;

  case 120: /* comp_op: NOT IN  */
#line 1021 "yacc_sql.y"
             { (yyval.comp) = NOT_IN_; }
#line 2965 "yacc_sql.cpp"
    break;

  case 121: /* comp_op: EXISTS  */
#line 1022 "yacc_sql.y"
             { (yyval.comp) = EXISTS_; }
#line 2971 "yacc_sql.cpp"
    break;

  case 122: /* comp_op: NOT EXISTS  */
#line 1023 "yacc_sql.y"
                 { (yyval.comp) = NOT_EXISTS_; }
#line 2977 "yacc_sql.cpp"
    break;

  case 123: /* group_by: %empty  */
#line 1029 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2985 "yacc_sql.cpp"
    break;

  case 124: /* group_by: GROUP BY expression_list  */
#line 1032 "yacc_sql.y"
                               {
      (yyval.expression_list) = (yyvsp[0].expression_list);
      /*delete $3;*/
    }
#line 2994 "yacc_sql.cpp"
    break;

  case 125: /* order_by: %empty  */
#line 1039 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 126: /* order_by: ORDER BY order_list  */
#line 1042 "yacc_sql.y"
                          {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3010 "yacc_sql.cpp"
    break;

  case 127: /* order_list: rel_attr  */
#line 1047 "yacc_sql.y"
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
#line 3025 "yacc_sql.cpp"
    break;

  case 128: /* order_list: rel_attr COMMA order_list  */
#line 1057 "yacc_sql.y"
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
#line 3040 "yacc_sql.cpp"
    break;

  case 129: /* order_list: rel_attr ASC  */
#line 1067 "yacc_sql.y"
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
#line 3055 "yacc_sql.cpp"
    break;

  case 130: /* order_list: rel_attr ASC COMMA order_list  */
#line 1077 "yacc_sql.y"
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
#line 3070 "yacc_sql.cpp"
    break;

  case 131: /* order_list: rel_attr DESC  */
#line 1087 "yacc_sql.y"
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
#line 3086 "yacc_sql.cpp"
    break;

  case 132: /* order_list: rel_attr DESC COMMA order_list  */
#line 1098 "yacc_sql.y"
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
#line 3101 "yacc_sql.cpp"
    break;

  case 133: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1111 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3115 "yacc_sql.cpp"
    break;

  case 134: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1124 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3124 "yacc_sql.cpp"
    break;

  case 135: /* set_variable_stmt: SET ID EQ value  */
#line 1132 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3136 "yacc_sql.cpp"
    break;


#line 3140 "yacc_sql.cpp"

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

#line 1144 "yacc_sql.y"

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
