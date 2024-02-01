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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sql.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "intpr.h"
#include "mmu.h"
#include "y.tab.h"

int yywrap() {
    return 1;
}
int yylex();

#line 86 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    NL = 258,                      /* NL  */
    BEGINN = 259,                  /* BEGINN  */
    COMMIT = 260,                  /* COMMIT  */
    ROLLBACK = 261,                /* ROLLBACK  */
    CREATE = 262,                  /* CREATE  */
    DROP = 263,                    /* DROP  */
    SELECT = 264,                  /* SELECT  */
    INSERT = 265,                  /* INSERT  */
    UPDATE = 266,                  /* UPDATE  */
    DELETE = 267,                  /* DELETE  */
    DESCRIBE = 268,                /* DESCRIBE  */
    FROM = 269,                    /* FROM  */
    WHERE = 270,                   /* WHERE  */
    INTO = 271,                    /* INTO  */
    SET = 272,                     /* SET  */
    VALUES = 273,                  /* VALUES  */
    TABLE = 274,                   /* TABLE  */
    LIMIT = 275,                   /* LIMIT  */
    SHOW = 276,                    /* SHOW  */
    TABLES = 277,                  /* TABLES  */
    MAX = 278,                     /* MAX  */
    MIN = 279,                     /* MIN  */
    COUNT = 280,                   /* COUNT  */
    SUM = 281,                     /* SUM  */
    AVG = 282,                     /* AVG  */
    REF = 283,                     /* REF  */
    TRUE = 284,                    /* TRUE  */
    FALSE = 285,                   /* FALSE  */
    NULLX = 286,                   /* NULLX  */
    CHAR = 287,                    /* CHAR  */
    INT = 288,                     /* INT  */
    LONG = 289,                    /* LONG  */
    STRING = 290,                  /* STRING  */
    BOOL = 291,                    /* BOOL  */
    FLOAT = 292,                   /* FLOAT  */
    DOUBLE = 293,                  /* DOUBLE  */
    DATE = 294,                    /* DATE  */
    TIMESTAMP = 295,               /* TIMESTAMP  */
    PRIMARY = 296,                 /* PRIMARY  */
    KEY = 297,                     /* KEY  */
    EQ = 298,                      /* EQ  */
    NE = 299,                      /* NE  */
    GT = 300,                      /* GT  */
    GE = 301,                      /* GE  */
    LT = 302,                      /* LT  */
    LE = 303,                      /* LE  */
    IN = 304,                      /* IN  */
    LIKE = 305,                    /* LIKE  */
    AND = 306,                     /* AND  */
    OR = 307,                      /* OR  */
    NOT = 308,                     /* NOT  */
    ALL = 309,                     /* ALL  */
    COMMA = 310,                   /* COMMA  */
    SEMICOLON = 311,               /* SEMICOLON  */
    QUOTE = 312,                   /* QUOTE  */
    POINT = 313,                   /* POINT  */
    LEFTPAREN = 314,               /* LEFTPAREN  */
    RIGHTPAREN = 315,              /* RIGHTPAREN  */
    SYSTEM = 316,                  /* SYSTEM  */
    CONFIG = 317,                  /* CONFIG  */
    MEMORY = 318,                  /* MEMORY  */
    IDENTIFIER = 319,              /* IDENTIFIER  */
    INTVALUE = 320,                /* INTVALUE  */
    FLOATVALUE = 321,              /* FLOATVALUE  */
    STRINGVALUE = 322              /* STRINGVALUE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NL 258
#define BEGINN 259
#define COMMIT 260
#define ROLLBACK 261
#define CREATE 262
#define DROP 263
#define SELECT 264
#define INSERT 265
#define UPDATE 266
#define DELETE 267
#define DESCRIBE 268
#define FROM 269
#define WHERE 270
#define INTO 271
#define SET 272
#define VALUES 273
#define TABLE 274
#define LIMIT 275
#define SHOW 276
#define TABLES 277
#define MAX 278
#define MIN 279
#define COUNT 280
#define SUM 281
#define AVG 282
#define REF 283
#define TRUE 284
#define FALSE 285
#define NULLX 286
#define CHAR 287
#define INT 288
#define LONG 289
#define STRING 290
#define BOOL 291
#define FLOAT 292
#define DOUBLE 293
#define DATE 294
#define TIMESTAMP 295
#define PRIMARY 296
#define KEY 297
#define EQ 298
#define NE 299
#define GT 300
#define GE 301
#define LT 302
#define LE 303
#define IN 304
#define LIKE 305
#define AND 306
#define OR 307
#define NOT 308
#define ALL 309
#define COMMA 310
#define SEMICOLON 311
#define QUOTE 312
#define POINT 313
#define LEFTPAREN 314
#define RIGHTPAREN 315
#define SYSTEM 316
#define CONFIG 317
#define MEMORY 318
#define IDENTIFIER 319
#define INTVALUE 320
#define FLOATVALUE 321
#define STRINGVALUE 322

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "sql.y"

   char                     *s_value;
   int64_t                  i_value;
   float                    f_value;
   bool                     b_value;
   char                     *keyword;
   ReferValue               *r_value;
   DataType                 data_type;
   CompareType              compare_type;
   ColumnDefNode            *column_def_node;
   ColumnDefSetNode         *column_def_set_node;
   SelectItemsNode          *select_items_node;
   ColumnNode               *column_node;
   ColumnSetNode            *column_set_node;
   ValueItemNode            *value_item_node;
   ValueItemSetNode         *value_item_set_node;
   SelectionNode            *selection_node;
   ScalarExpNode            *scalar_exp_node;
   ScalarExpSetNode         *scalar_exp_set_node;
   FunctionValueNode        *function_value_node;
   FunctionNode             *function_node;
   PrimaryKeyNode           *primary_key_node;
   AssignmentNode           *assignment_node;
   AssignmentSetNode        *assignment_set_node;
   ConditionNode            *condition_node;
   PredicateNode            *predicate_node;
   ComparisonNode           *comparison_node;
   LikeNode                 *like_node;
   InNode                   *in_node;
   LimitNode                *limit_node;
   CreateTableNode          *create_table_node;
   DropTableNode            *drop_table_node;
   SelectNode               *select_node;
   InsertNode               *insert_node;
   UpdateNode               *update_node;
   DeleteNode               *delete_node;
   DescribeNode             *describe_node;
   ShowNode                 *show_node;
   ASTNode                  *ast_node;

#line 314 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (ASTNode *ast_node);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_ = 3,                         /* '+'  */
  YYSYMBOL_4_ = 4,                         /* '-'  */
  YYSYMBOL_5_ = 5,                         /* '*'  */
  YYSYMBOL_6_ = 6,                         /* '/'  */
  YYSYMBOL_NL = 7,                         /* NL  */
  YYSYMBOL_BEGINN = 8,                     /* BEGINN  */
  YYSYMBOL_COMMIT = 9,                     /* COMMIT  */
  YYSYMBOL_ROLLBACK = 10,                  /* ROLLBACK  */
  YYSYMBOL_CREATE = 11,                    /* CREATE  */
  YYSYMBOL_DROP = 12,                      /* DROP  */
  YYSYMBOL_SELECT = 13,                    /* SELECT  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_DELETE = 16,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 17,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 18,                      /* FROM  */
  YYSYMBOL_WHERE = 19,                     /* WHERE  */
  YYSYMBOL_INTO = 20,                      /* INTO  */
  YYSYMBOL_SET = 21,                       /* SET  */
  YYSYMBOL_VALUES = 22,                    /* VALUES  */
  YYSYMBOL_TABLE = 23,                     /* TABLE  */
  YYSYMBOL_LIMIT = 24,                     /* LIMIT  */
  YYSYMBOL_SHOW = 25,                      /* SHOW  */
  YYSYMBOL_TABLES = 26,                    /* TABLES  */
  YYSYMBOL_MAX = 27,                       /* MAX  */
  YYSYMBOL_MIN = 28,                       /* MIN  */
  YYSYMBOL_COUNT = 29,                     /* COUNT  */
  YYSYMBOL_SUM = 30,                       /* SUM  */
  YYSYMBOL_AVG = 31,                       /* AVG  */
  YYSYMBOL_REF = 32,                       /* REF  */
  YYSYMBOL_TRUE = 33,                      /* TRUE  */
  YYSYMBOL_FALSE = 34,                     /* FALSE  */
  YYSYMBOL_NULLX = 35,                     /* NULLX  */
  YYSYMBOL_CHAR = 36,                      /* CHAR  */
  YYSYMBOL_INT = 37,                       /* INT  */
  YYSYMBOL_LONG = 38,                      /* LONG  */
  YYSYMBOL_STRING = 39,                    /* STRING  */
  YYSYMBOL_BOOL = 40,                      /* BOOL  */
  YYSYMBOL_FLOAT = 41,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 42,                    /* DOUBLE  */
  YYSYMBOL_DATE = 43,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 44,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 45,                   /* PRIMARY  */
  YYSYMBOL_KEY = 46,                       /* KEY  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_NE = 48,                        /* NE  */
  YYSYMBOL_GT = 49,                        /* GT  */
  YYSYMBOL_GE = 50,                        /* GE  */
  YYSYMBOL_LT = 51,                        /* LT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_IN = 53,                        /* IN  */
  YYSYMBOL_LIKE = 54,                      /* LIKE  */
  YYSYMBOL_AND = 55,                       /* AND  */
  YYSYMBOL_OR = 56,                        /* OR  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_ALL = 58,                       /* ALL  */
  YYSYMBOL_COMMA = 59,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 60,                 /* SEMICOLON  */
  YYSYMBOL_QUOTE = 61,                     /* QUOTE  */
  YYSYMBOL_POINT = 62,                     /* POINT  */
  YYSYMBOL_LEFTPAREN = 63,                 /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 64,                /* RIGHTPAREN  */
  YYSYMBOL_SYSTEM = 65,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 66,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 67,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 68,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 69,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 70,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 71,               /* STRINGVALUE  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_statements = 73,                /* statements  */
  YYSYMBOL_statement = 74,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 75, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 76, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 77, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 78,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 79,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 80,          /* select_statement  */
  YYSYMBOL_insert_statement = 81,          /* insert_statement  */
  YYSYMBOL_update_statement = 82,          /* update_statement  */
  YYSYMBOL_delete_statement = 83,          /* delete_statement  */
  YYSYMBOL_describe_statement = 84,        /* describe_statement  */
  YYSYMBOL_show_statement = 85,            /* show_statement  */
  YYSYMBOL_selection = 86,                 /* selection  */
  YYSYMBOL_table = 87,                     /* table  */
  YYSYMBOL_scalar_exp_commalist = 88,      /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 89,                /* scalar_exp  */
  YYSYMBOL_columns = 90,                   /* columns  */
  YYSYMBOL_column_defs = 91,               /* column_defs  */
  YYSYMBOL_column_def = 92,                /* column_def  */
  YYSYMBOL_data_type = 93,                 /* data_type  */
  YYSYMBOL_primary_key_statement = 94,     /* primary_key_statement  */
  YYSYMBOL_column = 95,                    /* column  */
  YYSYMBOL_value_items = 96,               /* value_items  */
  YYSYMBOL_value_item = 97,                /* value_item  */
  YYSYMBOL_REFERVALUE = 98,                /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 99,                 /* BOOLVALUE  */
  YYSYMBOL_assignments = 100,              /* assignments  */
  YYSYMBOL_assignment = 101,               /* assignment  */
  YYSYMBOL_condition = 102,                /* condition  */
  YYSYMBOL_predicate = 103,                /* predicate  */
  YYSYMBOL_comparison_predicate = 104,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 105,           /* like_predicate  */
  YYSYMBOL_in_predicate = 106,             /* in_predicate  */
  YYSYMBOL_opt_limit = 107,                /* opt_limit  */
  YYSYMBOL_compare = 108,                  /* compare  */
  YYSYMBOL_function = 109,                 /* function  */
  YYSYMBOL_function_value = 110,           /* function_value  */
  YYSYMBOL_non_all_function_value = 111,   /* non_all_function_value  */
  YYSYMBOL_end = 112                       /* end  */
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
typedef yytype_uint8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
       2,     2,     5,     3,     2,     4,     2,     6,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   129,   129,   130,   131,   134,   138,   142,   146,   151,
     156,   161,   166,   171,   176,   181,   188,   191,   194,   197,
     204,   214,   222,   231,   241,   249,   260,   267,   277,   283,
     292,   300,   304,   332,   339,   347,   353,   359,   366,   373,
     380,   386,   392,   399,   405,   412,   422,   433,   444,   453,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   475,
     483,   490,   500,   506,   513,   520,   527,   534,   541,   551,
     559,   568,   572,   578,   584,   591,   600,   608,   616,   620,
     629,   636,   643,   652,   662,   671,   681,   684,   691,   700,
     701,   702,   703,   704,   705,   708,   715,   722,   729,   736,
     745,   752,   759,   767,   774,   783,   784
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "'+'", "'-'", "'*'",
  "'/'", "NL", "BEGINN", "COMMIT", "ROLLBACK", "CREATE", "DROP", "SELECT",
  "INSERT", "UPDATE", "DELETE", "DESCRIBE", "FROM", "WHERE", "INTO", "SET",
  "VALUES", "TABLE", "LIMIT", "SHOW", "TABLES", "MAX", "MIN", "COUNT",
  "SUM", "AVG", "REF", "TRUE", "FALSE", "NULLX", "CHAR", "INT", "LONG",
  "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE", "TIMESTAMP", "PRIMARY",
  "KEY", "EQ", "NE", "GT", "GE", "LT", "LE", "IN", "LIKE", "AND", "OR",
  "NOT", "ALL", "COMMA", "SEMICOLON", "QUOTE", "POINT", "LEFTPAREN",
  "RIGHTPAREN", "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER", "INTVALUE",
  "FLOATVALUE", "STRINGVALUE", "$accept", "statements", "statement",
  "begin_transaction_statement", "commit_transaction_statement",
  "rollback_transaction_statement", "create_table_statement",
  "drop_table_statement", "select_statement", "insert_statement",
  "update_statement", "delete_statement", "describe_statement",
  "show_statement", "selection", "table", "scalar_exp_commalist",
  "scalar_exp", "columns", "column_defs", "column_def", "data_type",
  "primary_key_statement", "column", "value_items", "value_item",
  "REFERVALUE", "BOOLVALUE", "assignments", "assignment", "condition",
  "predicate", "comparison_predicate", "like_predicate", "in_predicate",
  "opt_limit", "compare", "function", "function_value",
  "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-132)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     152,     9,     9,     9,    -9,    30,    67,    16,   -18,    47,
     -18,   -24,   179,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,    79,  -132,  -132,  -132,
     -18,   -18,    36,    46,    55,    57,    58,  -132,    77,    60,
     106,    69,  -132,  -132,  -132,   -18,  -132,   105,   -18,     9,
       9,     9,  -132,  -132,  -132,    64,     9,   -48,   -48,   -41,
     -41,   -41,    65,    66,   -18,    77,   -17,    73,    -1,  -132,
    -132,  -132,    73,  -132,  -132,  -132,    72,    78,  -132,  -132,
    -132,    80,    82,    83,  -132,  -132,    13,  -132,    70,    73,
      85,    -4,  -132,   -28,  -132,    -7,  -132,   115,  -132,  -132,
    -132,  -132,  -132,   -28,    74,     9,    68,    17,  -132,    68,
     -28,    73,  -132,   -28,   159,    24,  -132,  -132,  -132,  -132,
     -35,     9,  -132,  -132,  -132,    86,  -132,  -132,  -132,  -132,
    -132,  -132,   -34,   -11,   112,  -132,   109,  -132,  -132,    68,
    -132,  -132,  -132,    26,  -132,  -132,  -132,    73,   151,  -132,
      24,  -132,   -26,  -132,  -132,  -132,  -132,  -132,  -132,   111,
      68,    68,   -28,   -28,  -132,   130,  -132,   114,  -132,   113,
     134,   146,     9,   116,   -28,    51,    68,     9,  -132,   121,
    -132,  -132,    68,  -132,  -132,  -132,   142,   135,     9,   136,
    -132,  -132,  -132,  -132,    18,  -132,  -132,  -132,    68,    52,
      73,  -132,  -132,  -132,    53,  -132,   137,     9,  -132,  -132
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   105,     0,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,    34,     0,    60,
       0,    33,    36,    38,    39,     0,    35,     0,     0,     0,
       0,     0,     1,     3,   106,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,     0,    21,   103,   104,     0,     0,   102,   100,
     101,     0,     0,     0,    40,    61,    86,    37,     0,     0,
       0,     0,    73,     0,    28,     0,    43,     0,    95,    96,
      97,    98,    99,     0,     0,     0,     0,     0,    41,     0,
       0,     0,    26,     0,     0,     0,    79,    80,    81,    82,
       0,     0,    52,    50,    51,    53,    54,    55,    56,    58,
      57,    47,    45,    86,    87,    23,     0,    71,    72,     0,
      64,    67,    66,     0,    62,    68,    65,     0,     0,    75,
       0,    74,     0,    89,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,    29,     0,    44,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
      27,    78,     0,    84,    83,    77,    76,     0,     0,     0,
      48,    49,    22,    88,     0,    69,    63,    24,     0,     0,
       0,    20,    46,    70,     0,    85,     0,     0,    59,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,   187,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,    -6,  -132,   -31,  -132,  -132,
      94,  -132,  -132,     3,  -131,   -83,  -132,  -132,  -132,    91,
     -91,  -132,  -132,  -132,  -132,    84,  -132,  -132,    27,   157,
      -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    40,    47,    41,    42,   107,    95,
      96,   132,   167,   114,   143,   144,   145,   146,    91,    92,
     115,   116,   117,   118,   119,   105,   161,    44,    81,    76,
      27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    29,    50,    25,    49,    88,    25,    62,   175,    43,
     165,   170,   133,   104,    30,   110,    25,    78,    93,   150,
      39,    74,   152,   171,    55,    56,   149,    39,    79,   162,
     163,    25,   103,    39,    87,   113,    45,   104,   181,    66,
      39,    43,    68,    51,   162,   163,    89,    69,    70,    71,
      46,   199,   120,    31,    73,   111,    26,   121,    86,    26,
      75,    75,    80,    80,    80,    48,    94,   204,    43,    26,
      90,   185,   186,   162,   163,    97,   147,   183,   184,   162,
     163,   148,   203,   194,    26,   176,    54,    82,    83,   112,
     177,   131,   108,   196,    32,    33,    34,    35,    36,    57,
     136,   137,   138,   135,    32,    33,    34,    35,    36,    58,
     176,   176,   176,   164,    90,   195,   205,   207,    59,   168,
      60,    61,    63,    97,    64,    37,    67,    72,    65,    84,
      38,   139,   109,   106,    85,    39,    98,   140,   141,   142,
      38,    39,    99,   134,   100,    39,   101,   102,   180,   169,
     178,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     192,   173,   174,   179,   182,   197,   187,    11,   188,    52,
     190,   191,   189,    46,   198,   193,   201,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,   162,   200,    53,
     202,   208,   151,   206,    11,   209,   153,   154,   155,   156,
     157,   158,   159,   160,   166,    77,     0,   172
};

static const yytype_int16 yycheck[] =
{
       2,     3,    26,     7,    10,    22,     7,    38,   139,     6,
      45,    45,   103,    24,    23,    19,     7,    58,    19,   110,
      68,    69,   113,    57,    30,    31,   109,    68,    69,    55,
      56,     7,    19,    68,    65,    63,    20,    24,    64,    45,
      68,    38,    48,    67,    55,    56,    63,    49,    50,    51,
      68,   182,    59,    23,    56,    59,    60,    64,    64,    60,
      57,    58,    59,    60,    61,    18,    68,   198,    65,    60,
      67,   162,   163,    55,    56,    72,    59,   160,   161,    55,
      56,    64,    64,   174,    60,    59,     7,    60,    61,    91,
      64,    97,    89,   176,    27,    28,    29,    30,    31,    63,
      32,    33,    34,   105,    27,    28,    29,    30,    31,    63,
      59,    59,    59,   115,   111,    64,    64,    64,    63,   121,
      63,    63,    62,   120,    18,    58,    21,    63,    59,    64,
      63,    63,    47,    63,    68,    68,    64,    69,    70,    71,
      63,    68,    64,    69,    64,    68,    64,    64,   150,    63,
     147,    36,    37,    38,    39,    40,    41,    42,    43,    44,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
     172,    59,    63,    22,    63,   177,    46,    25,    64,     0,
      46,    35,    69,    68,    63,    69,   188,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    55,    63,    12,
      64,    64,   111,   200,    25,   207,    47,    48,    49,    50,
      51,    52,    53,    54,   120,    58,    -1,   133
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    25,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     7,    60,   112,   112,   112,
      23,    23,    27,    28,    29,    30,    31,    58,    63,    68,
      86,    88,    89,    95,   109,    20,    68,    87,    18,    87,
      26,    67,     0,    74,     7,    87,    87,    63,    63,    63,
      63,    63,    89,    62,    18,    59,    87,    21,    87,   112,
     112,   112,    63,   112,    69,    95,   111,   111,    58,    69,
      95,   110,   110,   110,    64,    68,    87,    89,    22,    63,
      95,   100,   101,    19,   112,    91,    92,    95,    64,    64,
      64,    64,    64,    19,    24,   107,    63,    90,    95,    47,
      19,    59,   112,    63,    95,   102,   103,   104,   105,   106,
      59,    64,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    87,    93,   102,    69,   112,    32,    33,    34,    63,
      69,    70,    71,    96,    97,    98,    99,    59,    64,    97,
     102,   101,   102,    47,    48,    49,    50,    51,    52,    53,
      54,   108,    55,    56,   112,    45,    92,    94,   112,    63,
      45,    57,   107,    59,    63,    96,    59,    64,    95,    22,
     112,    64,    63,    97,    97,   102,   102,    46,    64,    69,
      46,    35,   112,    69,   102,    64,    97,   112,    63,    96,
      63,   112,    64,    64,    96,    64,    95,    64,    64,   112
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    76,    77,    78,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      84,    85,    85,    86,    86,    87,    88,    88,    89,    89,
      89,    90,    90,    91,    91,    92,    92,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    98,
      98,    99,    99,   100,   100,   101,   102,   102,   102,   102,
     103,   103,   103,   104,   105,   106,   107,   107,   107,   108,
     108,   108,   108,   108,   108,   109,   109,   109,   109,   109,
     110,   110,   110,   111,   111,   112,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     7,
       9,     4,     8,     6,     8,    11,     5,     7,     4,     6,
       3,     3,     3,     1,     1,     1,     1,     3,     1,     1,
       3,     1,     3,     1,     3,     2,     5,     2,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     3,
       4,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     3,     3,     5,     0,     2,     4,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     2
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
        yyerror (ast_node, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, ast_node); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, ASTNode *ast_node)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (ast_node);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, ASTNode *ast_node)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, ast_node);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, ASTNode *ast_node)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], ast_node);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ast_node); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, ASTNode *ast_node)
{
  YY_USE (yyvaluep);
  YY_USE (ast_node);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (ASTNode *ast_node)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 5: /* statement: begin_transaction_statement  */
#line 135 "sql.y"
        {
            ast_node->statement_type = BEGIN_TRANSACTION_STMT;
        }
#line 1561 "y.tab.c"
    break;

  case 6: /* statement: commit_transaction_statement  */
#line 139 "sql.y"
        {
            ast_node->statement_type = COMMIT_TRANSACTION_STMT;
        }
#line 1569 "y.tab.c"
    break;

  case 7: /* statement: rollback_transaction_statement  */
#line 143 "sql.y"
        {
            ast_node->statement_type = ROLLBACK_TRANSACTION_STMT;
        }
#line 1577 "y.tab.c"
    break;

  case 8: /* statement: create_table_statement  */
#line 147 "sql.y"
        {
            ast_node->statement_type = CREATE_TABLE_STMT;
            ast_node->create_table_node = (yyvsp[0].create_table_node);
        }
#line 1586 "y.tab.c"
    break;

  case 9: /* statement: drop_table_statement  */
#line 152 "sql.y"
        {
            ast_node->statement_type = DROP_TABLE_STMT;
            ast_node->drop_table_node = (yyvsp[0].drop_table_node);
        }
#line 1595 "y.tab.c"
    break;

  case 10: /* statement: select_statement  */
#line 157 "sql.y"
        {
            ast_node->statement_type = SELECT_STMT;
            ast_node->select_node = (yyvsp[0].select_node);
        }
#line 1604 "y.tab.c"
    break;

  case 11: /* statement: insert_statement  */
#line 162 "sql.y"
        {
            ast_node->statement_type = INSERT_STMT;
            ast_node->insert_node = (yyvsp[0].insert_node);
        }
#line 1613 "y.tab.c"
    break;

  case 12: /* statement: update_statement  */
#line 167 "sql.y"
        {
            ast_node->statement_type = UPDATE_STMT;
            ast_node->update_node = (yyvsp[0].update_node);
        }
#line 1622 "y.tab.c"
    break;

  case 13: /* statement: delete_statement  */
#line 172 "sql.y"
        {
            ast_node->statement_type = DELETE_STMT;
            ast_node->delete_node = (yyvsp[0].delete_node);
        }
#line 1631 "y.tab.c"
    break;

  case 14: /* statement: describe_statement  */
#line 177 "sql.y"
        {
            ast_node->statement_type = DESCRIBE_STMT;
            ast_node->describe_node = (yyvsp[0].describe_node);
        }
#line 1640 "y.tab.c"
    break;

  case 15: /* statement: show_statement  */
#line 182 "sql.y"
        {
            ast_node->statement_type = SHOW_STMT;
            ast_node->show_node = (yyvsp[0].show_node);
        }
#line 1649 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs RIGHTPAREN end  */
#line 198 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].s_value);
            create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1660 "y.tab.c"
    break;

  case 20: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs COMMA primary_key_statement RIGHTPAREN end  */
#line 205 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-6].s_value);
            create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
            create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1672 "y.tab.c"
    break;

  case 21: /* drop_table_statement: DROP TABLE table end  */
#line 215 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].s_value);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1682 "y.tab.c"
    break;

  case 22: /* select_statement: SELECT selection FROM table WHERE condition opt_limit end  */
#line 223 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-6].selection_node);
            select_node->table_name = (yyvsp[-4].s_value);
            select_node->condition_node = (yyvsp[-2].condition_node);
            select_node->limit_node = (yyvsp[-1].limit_node);
            (yyval.select_node) = select_node;
        }
#line 1695 "y.tab.c"
    break;

  case 23: /* select_statement: SELECT selection FROM table opt_limit end  */
#line 232 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-4].selection_node);
            select_node->table_name = (yyvsp[-2].s_value);
            select_node->limit_node = (yyvsp[-1].limit_node);
            (yyval.select_node) = select_node;
        }
#line 1707 "y.tab.c"
    break;

  case 24: /* insert_statement: INSERT INTO table VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 242 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-5].s_value);
            node->value_item_set_node = (yyvsp[-2].value_item_set_node);
            (yyval.insert_node) = node;
        }
#line 1719 "y.tab.c"
    break;

  case 25: /* insert_statement: INSERT INTO table LEFTPAREN columns RIGHTPAREN VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 250 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-8].s_value);
            node->columns_set_node = (yyvsp[-6].column_set_node);
            node->value_item_set_node = (yyvsp[-2].value_item_set_node);
            (yyval.insert_node) = node;
        }
#line 1732 "y.tab.c"
    break;

  case 26: /* update_statement: UPDATE table SET assignments end  */
#line 261 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-3].s_value);
            node->assignment_set_node = (yyvsp[-1].assignment_set_node);
            (yyval.update_node) = node;
        }
#line 1743 "y.tab.c"
    break;

  case 27: /* update_statement: UPDATE table SET assignments WHERE condition end  */
#line 268 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-5].s_value);
            node->assignment_set_node = (yyvsp[-3].assignment_set_node);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.update_node) = node;
        }
#line 1755 "y.tab.c"
    break;

  case 28: /* delete_statement: DELETE FROM table end  */
#line 278 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].s_value);
            (yyval.delete_node) = node;
        }
#line 1765 "y.tab.c"
    break;

  case 29: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 284 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].s_value);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1776 "y.tab.c"
    break;

  case 30: /* describe_statement: DESCRIBE table end  */
#line 293 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = db_strdup((yyvsp[-1].s_value));
            (yyval.describe_node) = node;
        }
#line 1786 "y.tab.c"
    break;

  case 31: /* show_statement: SHOW TABLES end  */
#line 301 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1794 "y.tab.c"
    break;

  case 32: /* show_statement: SHOW MEMORY end  */
#line 305 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1802 "y.tab.c"
    break;

  case 33: /* selection: scalar_exp_commalist  */
#line 333 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_set = (yyvsp[0].scalar_exp_set_node);
            (yyval.selection_node) = selection_node;
        }
#line 1813 "y.tab.c"
    break;

  case 34: /* selection: ALL  */
#line 340 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 1823 "y.tab.c"
    break;

  case 35: /* table: IDENTIFIER  */
#line 348 "sql.y"
        {
            (yyval.s_value) = (yyvsp[0].s_value);
        }
#line 1831 "y.tab.c"
    break;

  case 36: /* scalar_exp_commalist: scalar_exp  */
#line 354 "sql.y"
        {
            ScalarExpSetNode *scalar_exp_set_node = make_scalar_exp_set_node();
            add_scalar_exp_node(scalar_exp_set_node, (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = scalar_exp_set_node;
        }
#line 1841 "y.tab.c"
    break;

  case 37: /* scalar_exp_commalist: scalar_exp_commalist COMMA scalar_exp  */
#line 360 "sql.y"
        {
            add_scalar_exp_node((yyvsp[-2].scalar_exp_set_node), (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = (yyvsp[-2].scalar_exp_set_node);
        }
#line 1850 "y.tab.c"
    break;

  case 38: /* scalar_exp: column  */
#line 367 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 1861 "y.tab.c"
    break;

  case 39: /* scalar_exp: function  */
#line 374 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 1872 "y.tab.c"
    break;

  case 40: /* scalar_exp: LEFTPAREN scalar_exp RIGHTPAREN  */
#line 381 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-2].keyword);
        }
#line 1880 "y.tab.c"
    break;

  case 41: /* columns: column  */
#line 387 "sql.y"
        {
            ColumnSetNode *column_set_node = make_column_set_node();
            add_column_to_set(column_set_node, (yyvsp[0].column_node));
            (yyval.column_set_node) = column_set_node;
        }
#line 1890 "y.tab.c"
    break;

  case 42: /* columns: columns COMMA column  */
#line 393 "sql.y"
        {
            (yyval.column_set_node) = (yyvsp[-2].column_set_node);
            add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
        }
#line 1899 "y.tab.c"
    break;

  case 43: /* column_defs: column_def  */
#line 400 "sql.y"
        {
            ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
            add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
            (yyval.column_def_set_node) = column_def_set_node;
        }
#line 1909 "y.tab.c"
    break;

  case 44: /* column_defs: column_defs COMMA column_def  */
#line 406 "sql.y"
        {
            (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
            add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
        }
#line 1918 "y.tab.c"
    break;

  case 45: /* column_def: column data_type  */
#line 413 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-1].column_node);
            column_def_node->data_type = (yyvsp[0].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            column_def_node->is_define_len = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 1932 "y.tab.c"
    break;

  case 46: /* column_def: column STRING LEFTPAREN INTVALUE RIGHTPAREN  */
#line 423 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-4].column_node);
            column_def_node->data_type = T_STRING;
            column_def_node->data_len = (yyvsp[-1].i_value);
            column_def_node->is_define_len = true;
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 1947 "y.tab.c"
    break;

  case 47: /* column_def: column table  */
#line 434 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-1].column_node);
            column_def_node->data_type = T_REFERENCE;
            column_def_node->table_name = (yyvsp[0].s_value);
            column_def_node->is_define_len = false;
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 1962 "y.tab.c"
    break;

  case 48: /* column_def: column data_type PRIMARY KEY  */
#line 445 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = true;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 1975 "y.tab.c"
    break;

  case 49: /* column_def: column data_type NOT NULLX  */
#line 454 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = true;
            (yyval.column_def_node) = column_def_node;
        }
#line 1988 "y.tab.c"
    break;

  case 50: /* data_type: INT  */
#line 464 "sql.y"
                 { (yyval.data_type) = T_INT; }
#line 1994 "y.tab.c"
    break;

  case 51: /* data_type: LONG  */
#line 465 "sql.y"
                 { (yyval.data_type) = T_LONG;  }
#line 2000 "y.tab.c"
    break;

  case 52: /* data_type: CHAR  */
#line 466 "sql.y"
                 { (yyval.data_type) = T_CHAR; }
#line 2006 "y.tab.c"
    break;

  case 53: /* data_type: STRING  */
#line 467 "sql.y"
                 { (yyval.data_type) = T_STRING; }
#line 2012 "y.tab.c"
    break;

  case 54: /* data_type: BOOL  */
#line 468 "sql.y"
                 { (yyval.data_type) = T_BOOL; }
#line 2018 "y.tab.c"
    break;

  case 55: /* data_type: FLOAT  */
#line 469 "sql.y"
                 { (yyval.data_type) = T_FLOAT; }
#line 2024 "y.tab.c"
    break;

  case 56: /* data_type: DOUBLE  */
#line 470 "sql.y"
                 { (yyval.data_type) = T_DOUBLE; }
#line 2030 "y.tab.c"
    break;

  case 57: /* data_type: TIMESTAMP  */
#line 471 "sql.y"
                 { (yyval.data_type) = T_TIMESTAMP; }
#line 2036 "y.tab.c"
    break;

  case 58: /* data_type: DATE  */
#line 472 "sql.y"
                 { (yyval.data_type) = T_DATE; }
#line 2042 "y.tab.c"
    break;

  case 59: /* primary_key_statement: PRIMARY KEY LEFTPAREN column RIGHTPAREN  */
#line 476 "sql.y"
         {
             PrimaryKeyNode *primary_key_node = make_primary_key_node();
             primary_key_node->column = (yyvsp[-1].column_node);
             (yyval.primary_key_node) = primary_key_node;
         }
#line 2052 "y.tab.c"
    break;

  case 60: /* column: IDENTIFIER  */
#line 484 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[0].s_value));
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2063 "y.tab.c"
    break;

  case 61: /* column: IDENTIFIER POINT IDENTIFIER  */
#line 491 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-2].s_value));
            column_node->sub_column_name = db_strdup((yyvsp[0].s_value));
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2075 "y.tab.c"
    break;

  case 62: /* value_items: value_item  */
#line 501 "sql.y"
        {
            ValueItemSetNode *node = make_value_item_set_node();
            add_value_item(node, (yyvsp[0].value_item_node));
            (yyval.value_item_set_node) = node;
        }
#line 2085 "y.tab.c"
    break;

  case 63: /* value_items: value_items COMMA value_item  */
#line 507 "sql.y"
        {
            (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
            add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
        }
#line 2094 "y.tab.c"
    break;

  case 64: /* value_item: INTVALUE  */
#line 514 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->i_value = (yyvsp[0].i_value);
            node->data_type = T_INT;
            (yyval.value_item_node) = node;
        }
#line 2105 "y.tab.c"
    break;

  case 65: /* value_item: BOOLVALUE  */
#line 521 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->b_value = (yyvsp[0].b_value);
            node->data_type = T_BOOL;
            (yyval.value_item_node) = node;
        }
#line 2116 "y.tab.c"
    break;

  case 66: /* value_item: STRINGVALUE  */
#line 528 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->s_value = (yyvsp[0].s_value);
            node->data_type = T_STRING;
            (yyval.value_item_node) = node;
        }
#line 2127 "y.tab.c"
    break;

  case 67: /* value_item: FLOATVALUE  */
#line 535 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->f_value = (yyvsp[0].f_value);
            node->data_type = T_FLOAT;
            (yyval.value_item_node) = node;
        }
#line 2138 "y.tab.c"
    break;

  case 68: /* value_item: REFERVALUE  */
#line 542 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->r_value = (yyvsp[0].r_value);
            node->data_type = T_REFERENCE;
            (yyval.value_item_node) = node;
        }
#line 2149 "y.tab.c"
    break;

  case 69: /* REFERVALUE: LEFTPAREN value_items RIGHTPAREN  */
#line 552 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_item_set = (yyvsp[-1].value_item_set_node);
            (yyval.r_value) = refer;
        }
#line 2160 "y.tab.c"
    break;

  case 70: /* REFERVALUE: REF LEFTPAREN condition RIGHTPAREN  */
#line 560 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.r_value) = refer;
        }
#line 2171 "y.tab.c"
    break;

  case 71: /* BOOLVALUE: TRUE  */
#line 569 "sql.y"
        {
            (yyval.b_value) = true;
        }
#line 2179 "y.tab.c"
    break;

  case 72: /* BOOLVALUE: FALSE  */
#line 573 "sql.y"
        {
            (yyval.b_value) = false;
        }
#line 2187 "y.tab.c"
    break;

  case 73: /* assignments: assignment  */
#line 579 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2197 "y.tab.c"
    break;

  case 74: /* assignments: assignments COMMA assignment  */
#line 585 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2206 "y.tab.c"
    break;

  case 75: /* assignment: column EQ value_item  */
#line 592 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2217 "y.tab.c"
    break;

  case 76: /* condition: condition OR condition  */
#line 601 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2229 "y.tab.c"
    break;

  case 77: /* condition: condition AND condition  */
#line 609 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2241 "y.tab.c"
    break;

  case 78: /* condition: LEFTPAREN condition RIGHTPAREN  */
#line 617 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2249 "y.tab.c"
    break;

  case 79: /* condition: predicate  */
#line 621 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2260 "y.tab.c"
    break;

  case 80: /* predicate: comparison_predicate  */
#line 630 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2271 "y.tab.c"
    break;

  case 81: /* predicate: like_predicate  */
#line 637 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2282 "y.tab.c"
    break;

  case 82: /* predicate: in_predicate  */
#line 644 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 2293 "y.tab.c"
    break;

  case 83: /* comparison_predicate: column compare value_item  */
#line 653 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].value_item_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 2305 "y.tab.c"
    break;

  case 84: /* like_predicate: column LIKE value_item  */
#line 663 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 2316 "y.tab.c"
    break;

  case 85: /* in_predicate: column IN LEFTPAREN value_items RIGHTPAREN  */
#line 672 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_set = (yyvsp[-1].value_item_set_node);
            (yyval.in_node) = in_node;
        }
#line 2327 "y.tab.c"
    break;

  case 86: /* opt_limit: %empty  */
#line 681 "sql.y"
        {
            (yyval.limit_node) = NULL;
        }
#line 2335 "y.tab.c"
    break;

  case 87: /* opt_limit: LIMIT INTVALUE  */
#line 685 "sql.y"
        {
            LimitNode *limit_node = make_limit_node();
            limit_node->start = 0;
            limit_node->end = (yyvsp[0].i_value);
            (yyval.limit_node) = limit_node;
        }
#line 2346 "y.tab.c"
    break;

  case 88: /* opt_limit: LIMIT INTVALUE COMMA INTVALUE  */
#line 692 "sql.y"
        {
            LimitNode *limit_node = make_limit_node();
            limit_node->start = (yyvsp[-2].i_value);
            limit_node->end = (yyvsp[0].i_value);
            (yyval.limit_node) = limit_node;
        }
#line 2357 "y.tab.c"
    break;

  case 89: /* compare: EQ  */
#line 700 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 2363 "y.tab.c"
    break;

  case 90: /* compare: NE  */
#line 701 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 2369 "y.tab.c"
    break;

  case 91: /* compare: GT  */
#line 702 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 2375 "y.tab.c"
    break;

  case 92: /* compare: GE  */
#line 703 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 2381 "y.tab.c"
    break;

  case 93: /* compare: LT  */
#line 704 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 2387 "y.tab.c"
    break;

  case 94: /* compare: LE  */
#line 705 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 2393 "y.tab.c"
    break;

  case 95: /* function: MAX LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 709 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2404 "y.tab.c"
    break;

  case 96: /* function: MIN LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 716 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2415 "y.tab.c"
    break;

  case 97: /* function: COUNT LEFTPAREN function_value RIGHTPAREN  */
#line 723 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2426 "y.tab.c"
    break;

  case 98: /* function: SUM LEFTPAREN function_value RIGHTPAREN  */
#line 730 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2437 "y.tab.c"
    break;

  case 99: /* function: AVG LEFTPAREN function_value RIGHTPAREN  */
#line 737 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2448 "y.tab.c"
    break;

  case 100: /* function_value: INTVALUE  */
#line 746 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].i_value);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2459 "y.tab.c"
    break;

  case 101: /* function_value: column  */
#line 753 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2470 "y.tab.c"
    break;

  case 102: /* function_value: ALL  */
#line 760 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 2480 "y.tab.c"
    break;

  case 103: /* non_all_function_value: INTVALUE  */
#line 768 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].i_value);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2491 "y.tab.c"
    break;

  case 104: /* non_all_function_value: column  */
#line 775 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2502 "y.tab.c"
    break;


#line 2506 "y.tab.c"

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
      yyerror (ast_node, YY_("syntax error"));
    }

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
                      yytoken, &yylval, ast_node);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, ast_node);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (ast_node, YY_("memory exhausted"));
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
                  yytoken, &yylval, ast_node);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, ast_node);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 786 "sql.y"

