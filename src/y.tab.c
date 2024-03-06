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
    AS = 287,                      /* AS  */
    CHAR = 288,                    /* CHAR  */
    INT = 289,                     /* INT  */
    LONG = 290,                    /* LONG  */
    STRING = 291,                  /* STRING  */
    BOOL = 292,                    /* BOOL  */
    FLOAT = 293,                   /* FLOAT  */
    DOUBLE = 294,                  /* DOUBLE  */
    DATE = 295,                    /* DATE  */
    TIMESTAMP = 296,               /* TIMESTAMP  */
    PRIMARY = 297,                 /* PRIMARY  */
    KEY = 298,                     /* KEY  */
    EQ = 299,                      /* EQ  */
    NE = 300,                      /* NE  */
    GT = 301,                      /* GT  */
    GE = 302,                      /* GE  */
    LT = 303,                      /* LT  */
    LE = 304,                      /* LE  */
    IN = 305,                      /* IN  */
    LIKE = 306,                    /* LIKE  */
    AND = 307,                     /* AND  */
    OR = 308,                      /* OR  */
    NOT = 309,                     /* NOT  */
    ASTERISK = 310,                /* ASTERISK  */
    SOLIDUS = 311,                 /* SOLIDUS  */
    PLUS = 312,                    /* PLUS  */
    MINUS = 313,                   /* MINUS  */
    COMMA = 314,                   /* COMMA  */
    SEMICOLON = 315,               /* SEMICOLON  */
    QUOTE = 316,                   /* QUOTE  */
    POINT = 317,                   /* POINT  */
    LEFTPAREN = 318,               /* LEFTPAREN  */
    RIGHTPAREN = 319,              /* RIGHTPAREN  */
    SYSTEM = 320,                  /* SYSTEM  */
    CONFIG = 321,                  /* CONFIG  */
    MEMORY = 322,                  /* MEMORY  */
    IDENTIFIER = 323,              /* IDENTIFIER  */
    INTVALUE = 324,                /* INTVALUE  */
    FLOATVALUE = 325,              /* FLOATVALUE  */
    STRINGVALUE = 326              /* STRINGVALUE  */
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
#define AS 287
#define CHAR 288
#define INT 289
#define LONG 290
#define STRING 291
#define BOOL 292
#define FLOAT 293
#define DOUBLE 294
#define DATE 295
#define TIMESTAMP 296
#define PRIMARY 297
#define KEY 298
#define EQ 299
#define NE 300
#define GT 301
#define GE 302
#define LT 303
#define LE 304
#define IN 305
#define LIKE 306
#define AND 307
#define OR 308
#define NOT 309
#define ASTERISK 310
#define SOLIDUS 311
#define PLUS 312
#define MINUS 313
#define COMMA 314
#define SEMICOLON 315
#define QUOTE 316
#define POINT 317
#define LEFTPAREN 318
#define RIGHTPAREN 319
#define SYSTEM 320
#define CONFIG 321
#define MEMORY 322
#define IDENTIFIER 323
#define INTVALUE 324
#define FLOATVALUE 325
#define STRINGVALUE 326

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
   ColumnNode               *column_node;
   ColumnSetNode            *column_set_node;
   ValueItemNode            *value_item_node;
   ValueItemSetNode         *value_item_set_node;
   SelectionNode            *selection_node;
   ScalarExpNode            *scalar_exp_node;
   ScalarExpSetNode         *scalar_exp_set_node;
   FunctionValueNode        *function_value_node;
   FunctionNode             *function_node;
   CalculateNode            *calculate_node;
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

#line 322 "y.tab.c"

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
  YYSYMBOL_NL = 3,                         /* NL  */
  YYSYMBOL_BEGINN = 4,                     /* BEGINN  */
  YYSYMBOL_COMMIT = 5,                     /* COMMIT  */
  YYSYMBOL_ROLLBACK = 6,                   /* ROLLBACK  */
  YYSYMBOL_CREATE = 7,                     /* CREATE  */
  YYSYMBOL_DROP = 8,                       /* DROP  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_INSERT = 10,                    /* INSERT  */
  YYSYMBOL_UPDATE = 11,                    /* UPDATE  */
  YYSYMBOL_DELETE = 12,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 13,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 14,                      /* FROM  */
  YYSYMBOL_WHERE = 15,                     /* WHERE  */
  YYSYMBOL_INTO = 16,                      /* INTO  */
  YYSYMBOL_SET = 17,                       /* SET  */
  YYSYMBOL_VALUES = 18,                    /* VALUES  */
  YYSYMBOL_TABLE = 19,                     /* TABLE  */
  YYSYMBOL_LIMIT = 20,                     /* LIMIT  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_TABLES = 22,                    /* TABLES  */
  YYSYMBOL_MAX = 23,                       /* MAX  */
  YYSYMBOL_MIN = 24,                       /* MIN  */
  YYSYMBOL_COUNT = 25,                     /* COUNT  */
  YYSYMBOL_SUM = 26,                       /* SUM  */
  YYSYMBOL_AVG = 27,                       /* AVG  */
  YYSYMBOL_REF = 28,                       /* REF  */
  YYSYMBOL_TRUE = 29,                      /* TRUE  */
  YYSYMBOL_FALSE = 30,                     /* FALSE  */
  YYSYMBOL_NULLX = 31,                     /* NULLX  */
  YYSYMBOL_AS = 32,                        /* AS  */
  YYSYMBOL_CHAR = 33,                      /* CHAR  */
  YYSYMBOL_INT = 34,                       /* INT  */
  YYSYMBOL_LONG = 35,                      /* LONG  */
  YYSYMBOL_STRING = 36,                    /* STRING  */
  YYSYMBOL_BOOL = 37,                      /* BOOL  */
  YYSYMBOL_FLOAT = 38,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 39,                    /* DOUBLE  */
  YYSYMBOL_DATE = 40,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 41,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 42,                   /* PRIMARY  */
  YYSYMBOL_KEY = 43,                       /* KEY  */
  YYSYMBOL_EQ = 44,                        /* EQ  */
  YYSYMBOL_NE = 45,                        /* NE  */
  YYSYMBOL_GT = 46,                        /* GT  */
  YYSYMBOL_GE = 47,                        /* GE  */
  YYSYMBOL_LT = 48,                        /* LT  */
  YYSYMBOL_LE = 49,                        /* LE  */
  YYSYMBOL_IN = 50,                        /* IN  */
  YYSYMBOL_LIKE = 51,                      /* LIKE  */
  YYSYMBOL_AND = 52,                       /* AND  */
  YYSYMBOL_OR = 53,                        /* OR  */
  YYSYMBOL_NOT = 54,                       /* NOT  */
  YYSYMBOL_ASTERISK = 55,                  /* ASTERISK  */
  YYSYMBOL_SOLIDUS = 56,                   /* SOLIDUS  */
  YYSYMBOL_PLUS = 57,                      /* PLUS  */
  YYSYMBOL_MINUS = 58,                     /* MINUS  */
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
  YYSYMBOL_calculate = 90,                 /* calculate  */
  YYSYMBOL_columns = 91,                   /* columns  */
  YYSYMBOL_column_defs = 92,               /* column_defs  */
  YYSYMBOL_column_def = 93,                /* column_def  */
  YYSYMBOL_data_type = 94,                 /* data_type  */
  YYSYMBOL_primary_key_statement = 95,     /* primary_key_statement  */
  YYSYMBOL_column = 96,                    /* column  */
  YYSYMBOL_value_items = 97,               /* value_items  */
  YYSYMBOL_value_item = 98,                /* value_item  */
  YYSYMBOL_REFERVALUE = 99,                /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 100,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 101,              /* assignments  */
  YYSYMBOL_assignment = 102,               /* assignment  */
  YYSYMBOL_condition = 103,                /* condition  */
  YYSYMBOL_predicate = 104,                /* predicate  */
  YYSYMBOL_comparison_predicate = 105,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 106,           /* like_predicate  */
  YYSYMBOL_in_predicate = 107,             /* in_predicate  */
  YYSYMBOL_opt_limit = 108,                /* opt_limit  */
  YYSYMBOL_compare = 109,                  /* compare  */
  YYSYMBOL_function = 110,                 /* function  */
  YYSYMBOL_function_value = 111,           /* function_value  */
  YYSYMBOL_non_all_function_value = 112,   /* non_all_function_value  */
  YYSYMBOL_end = 113                       /* end  */
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
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   242

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   130,   130,   131,   132,   135,   139,   143,   147,   152,
     157,   162,   167,   172,   177,   182,   189,   192,   195,   198,
     205,   215,   223,   232,   242,   250,   261,   268,   278,   284,
     293,   301,   305,   311,   318,   326,   332,   338,   345,   352,
     359,   367,   374,   382,   388,   396,   404,   412,   422,   428,
     435,   441,   448,   458,   469,   480,   489,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   511,   519,   526,   534,
     544,   550,   557,   564,   571,   578,   585,   595,   603,   612,
     616,   622,   628,   635,   644,   652,   660,   664,   673,   680,
     687,   696,   706,   715,   725,   728,   735,   744,   745,   746,
     747,   748,   749,   752,   759,   766,   773,   780,   789,   796,
     803,   811,   818,   827,   828
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
  "\"end of file\"", "error", "\"invalid token\"", "NL", "BEGINN",
  "COMMIT", "ROLLBACK", "CREATE", "DROP", "SELECT", "INSERT", "UPDATE",
  "DELETE", "DESCRIBE", "FROM", "WHERE", "INTO", "SET", "VALUES", "TABLE",
  "LIMIT", "SHOW", "TABLES", "MAX", "MIN", "COUNT", "SUM", "AVG", "REF",
  "TRUE", "FALSE", "NULLX", "AS", "CHAR", "INT", "LONG", "STRING", "BOOL",
  "FLOAT", "DOUBLE", "DATE", "TIMESTAMP", "PRIMARY", "KEY", "EQ", "NE",
  "GT", "GE", "LT", "LE", "IN", "LIKE", "AND", "OR", "NOT", "ASTERISK",
  "SOLIDUS", "PLUS", "MINUS", "COMMA", "SEMICOLON", "QUOTE", "POINT",
  "LEFTPAREN", "RIGHTPAREN", "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER",
  "INTVALUE", "FLOATVALUE", "STRINGVALUE", "$accept", "statements",
  "statement", "begin_transaction_statement",
  "commit_transaction_statement", "rollback_transaction_statement",
  "create_table_statement", "drop_table_statement", "select_statement",
  "insert_statement", "update_statement", "delete_statement",
  "describe_statement", "show_statement", "selection", "table",
  "scalar_exp_commalist", "scalar_exp", "calculate", "columns",
  "column_defs", "column_def", "data_type", "primary_key_statement",
  "column", "value_items", "value_item", "REFERVALUE", "BOOLVALUE",
  "assignments", "assignment", "condition", "predicate",
  "comparison_predicate", "like_predicate", "in_predicate", "opt_limit",
  "compare", "function", "function_value", "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-153)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     188,    13,    13,    13,     2,     9,    63,    22,   -21,    42,
     -21,    -7,   162,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,    51,  -153,  -153,  -153,
     -21,   -21,     4,     7,    19,    28,    39,  -153,    69,    98,
      44,    77,   132,  -153,    73,    78,   -21,  -153,   163,   -21,
      13,    13,    13,  -153,  -153,  -153,   100,    13,   135,   135,
     -35,   -35,   -35,    66,   142,    69,   -21,    69,    69,    69,
      69,    69,   143,   144,    14,   142,     3,  -153,  -153,  -153,
     142,  -153,  -153,  -153,   121,   149,  -153,  -153,  -153,   151,
     152,   153,  -153,  -153,   -19,    49,   132,  -153,  -153,   150,
     150,  -153,  -153,   155,   142,   170,    20,  -153,    40,  -153,
      47,  -153,   110,  -153,  -153,  -153,  -153,  -153,  -153,    40,
     154,    13,    71,    61,  -153,    71,    40,   142,  -153,    40,
     108,    -1,  -153,  -153,  -153,  -153,   -25,    13,  -153,  -153,
    -153,   156,  -153,  -153,  -153,  -153,  -153,  -153,   -15,   -16,
     161,  -153,   159,  -153,  -153,    71,  -153,  -153,  -153,    74,
    -153,  -153,  -153,   142,   206,  -153,    -1,  -153,   -22,  -153,
    -153,  -153,  -153,  -153,  -153,   164,    71,    71,    40,    40,
    -153,   182,  -153,   165,  -153,   157,   185,   199,    13,   166,
      40,   117,    71,    13,  -153,   168,  -153,  -153,    71,  -153,
    -153,  -153,   180,   171,    13,   169,  -153,  -153,  -153,  -153,
      45,  -153,  -153,  -153,    71,   118,   142,  -153,  -153,  -153,
     120,  -153,   172,    13,  -153,  -153
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   113,     0,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,    34,     0,    67,
       0,    33,    36,    38,    39,    41,     0,    35,     0,     0,
       0,     0,     0,     1,     3,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,    32,
       0,    21,   111,   112,     0,     0,   110,   108,   109,     0,
       0,     0,    43,    68,     0,    94,    37,    46,    47,    44,
      45,    40,    42,     0,     0,     0,     0,    81,     0,    28,
       0,    50,     0,   103,   104,   105,   106,   107,    69,     0,
       0,     0,     0,     0,    48,     0,     0,     0,    26,     0,
       0,     0,    87,    88,    89,    90,     0,     0,    59,    57,
      58,    60,    61,    62,    63,    65,    64,    54,    52,    94,
      95,    23,     0,    79,    80,     0,    72,    75,    74,     0,
      70,    76,    73,     0,     0,    83,     0,    82,     0,    97,
      98,    99,   100,   101,   102,     0,     0,     0,     0,     0,
      29,     0,    51,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,    27,    86,     0,    92,
      91,    85,    84,     0,     0,     0,    55,    56,    22,    96,
       0,    77,    71,    24,     0,     0,     0,    20,    53,    78,
       0,    93,     0,     0,    66,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,   225,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,    -5,   173,    46,  -153,  -153,
    -153,   103,  -153,  -153,   -51,  -152,  -111,  -153,  -153,  -153,
     113,  -107,  -153,  -153,  -153,  -153,    92,  -153,  -153,   146,
     183,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    40,    48,    41,    42,    43,   123,
     110,   111,   148,   183,    44,   159,   160,   161,   162,   106,
     107,   131,   132,   133,   134,   135,   121,   177,    45,    89,
      84,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    29,    25,   191,   120,    50,    25,    83,    83,    88,
      88,    88,   149,    93,   165,    51,    25,   181,   108,   166,
      86,    30,   168,    25,   105,    56,    57,   186,    31,   112,
     178,   179,   103,    39,    87,   126,   178,   179,    46,   187,
      67,    74,   197,    39,    76,   118,   215,    47,    77,    78,
      79,   178,   179,   124,    55,    81,    49,   130,    66,    26,
      52,    95,   220,    26,   119,   199,   200,    58,   130,   120,
      59,   201,   202,    26,   109,   130,   105,   104,   130,   127,
      26,   212,    60,   210,    63,   112,    32,    33,    34,    35,
      36,    61,    32,    33,    34,    35,    36,   178,   179,   152,
     153,   154,    62,   129,   128,    72,   136,   147,    39,   219,
      73,   137,   194,    96,    97,    98,    99,   100,    37,   151,
     163,    68,    69,    70,    71,   164,    38,   130,   130,   180,
      92,    39,    38,   192,   155,   184,    67,    39,   193,   130,
     156,   157,   158,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   169,   170,   171,   172,   173,   174,   175,   176,
      64,    65,    53,    80,   196,   222,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,   192,   192,    47,   192,
      75,   211,   221,    11,   223,   113,   208,    68,    69,    70,
      71,   213,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,   217,    39,    82,    68,    69,    90,    91,    11,
      39,   101,   102,   114,   125,   115,   116,   117,   122,   185,
     189,   225,   190,   150,   195,   203,   205,   198,   206,   204,
     207,   214,   178,   218,   216,   209,   224,    54,    94,   182,
     167,   188,    85
};

static const yytype_uint8 yycheck[] =
{
       2,     3,     3,   155,    20,    10,     3,    58,    59,    60,
      61,    62,   119,    64,   125,    22,     3,    42,    15,   126,
      55,    19,   129,     3,    75,    30,    31,    42,    19,    80,
      52,    53,    18,    68,    69,    15,    52,    53,    16,    54,
      59,    46,    64,    68,    49,    64,   198,    68,    50,    51,
      52,    52,    53,   104,     3,    57,    14,   108,    14,    60,
      67,    66,   214,    60,    15,   176,   177,    63,   119,    20,
      63,   178,   179,    60,    76,   126,   127,    63,   129,    59,
      60,   192,    63,   190,    38,   136,    23,    24,    25,    26,
      27,    63,    23,    24,    25,    26,    27,    52,    53,    28,
      29,    30,    63,    63,   106,    32,    59,   112,    68,    64,
      32,    64,   163,    67,    68,    69,    70,    71,    55,   121,
      59,    55,    56,    57,    58,    64,    63,   178,   179,   131,
      64,    68,    63,    59,    63,   137,    59,    68,    64,   190,
      69,    70,    71,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    44,    45,    46,    47,    48,    49,    50,    51,
      62,    63,     0,    63,   166,   216,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    59,    59,    68,    59,
      17,    64,    64,    21,    64,    64,   188,    55,    56,    57,
      58,   193,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,   204,    68,    69,    55,    56,    61,    62,    21,
      68,    68,    68,    64,    44,    64,    64,    64,    63,    63,
      59,   223,    63,    69,    18,    43,    69,    63,    43,    64,
      31,    63,    52,    64,    63,    69,    64,    12,    65,   136,
     127,   149,    59
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    21,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     3,    60,   113,   113,   113,
      19,    19,    23,    24,    25,    26,    27,    55,    63,    68,
      86,    88,    89,    90,    96,   110,    16,    68,    87,    14,
      87,    22,    67,     0,    74,     3,    87,    87,    63,    63,
      63,    63,    63,    89,    62,    63,    14,    59,    55,    56,
      57,    58,    32,    32,    87,    17,    87,   113,   113,   113,
      63,   113,    69,    96,   112,   112,    55,    69,    96,   111,
     111,   111,    64,    96,    88,    87,    89,    89,    89,    89,
      89,    68,    68,    18,    63,    96,   101,   102,    15,   113,
      92,    93,    96,    64,    64,    64,    64,    64,    64,    15,
      20,   108,    63,    91,    96,    44,    15,    59,   113,    63,
      96,   103,   104,   105,   106,   107,    59,    64,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    87,    94,   103,
      69,   113,    28,    29,    30,    63,    69,    70,    71,    97,
      98,    99,   100,    59,    64,    98,   103,   102,   103,    44,
      45,    46,    47,    48,    49,    50,    51,   109,    52,    53,
     113,    42,    93,    95,   113,    63,    42,    54,   108,    59,
      63,    97,    59,    64,    96,    18,   113,    64,    63,    98,
      98,   103,   103,    43,    64,    69,    43,    31,   113,    69,
     103,    64,    98,   113,    63,    97,    63,   113,    64,    64,
      97,    64,    96,    64,    64,   113
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    76,    77,    78,
      78,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      84,    85,    85,    86,    86,    87,    88,    88,    89,    89,
      89,    89,    89,    89,    90,    90,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    95,    96,    96,    96,
      97,    97,    98,    98,    98,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   103,   103,   103,   103,   104,   104,
     104,   105,   106,   107,   108,   108,   108,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   111,   111,
     111,   112,   112,   113,   113
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     7,
       9,     4,     8,     6,     8,    11,     5,     7,     4,     6,
       3,     3,     3,     1,     1,     1,     1,     3,     1,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       1,     3,     2,     5,     2,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     3,     4,     1,
       1,     1,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     3,     3,     5,     0,     2,     4,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     2
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
#line 136 "sql.y"
        {
            ast_node->statement_type = BEGIN_TRANSACTION_STMT;
        }
#line 1585 "y.tab.c"
    break;

  case 6: /* statement: commit_transaction_statement  */
#line 140 "sql.y"
        {
            ast_node->statement_type = COMMIT_TRANSACTION_STMT;
        }
#line 1593 "y.tab.c"
    break;

  case 7: /* statement: rollback_transaction_statement  */
#line 144 "sql.y"
        {
            ast_node->statement_type = ROLLBACK_TRANSACTION_STMT;
        }
#line 1601 "y.tab.c"
    break;

  case 8: /* statement: create_table_statement  */
#line 148 "sql.y"
        {
            ast_node->statement_type = CREATE_TABLE_STMT;
            ast_node->create_table_node = (yyvsp[0].create_table_node);
        }
#line 1610 "y.tab.c"
    break;

  case 9: /* statement: drop_table_statement  */
#line 153 "sql.y"
        {
            ast_node->statement_type = DROP_TABLE_STMT;
            ast_node->drop_table_node = (yyvsp[0].drop_table_node);
        }
#line 1619 "y.tab.c"
    break;

  case 10: /* statement: select_statement  */
#line 158 "sql.y"
        {
            ast_node->statement_type = SELECT_STMT;
            ast_node->select_node = (yyvsp[0].select_node);
        }
#line 1628 "y.tab.c"
    break;

  case 11: /* statement: insert_statement  */
#line 163 "sql.y"
        {
            ast_node->statement_type = INSERT_STMT;
            ast_node->insert_node = (yyvsp[0].insert_node);
        }
#line 1637 "y.tab.c"
    break;

  case 12: /* statement: update_statement  */
#line 168 "sql.y"
        {
            ast_node->statement_type = UPDATE_STMT;
            ast_node->update_node = (yyvsp[0].update_node);
        }
#line 1646 "y.tab.c"
    break;

  case 13: /* statement: delete_statement  */
#line 173 "sql.y"
        {
            ast_node->statement_type = DELETE_STMT;
            ast_node->delete_node = (yyvsp[0].delete_node);
        }
#line 1655 "y.tab.c"
    break;

  case 14: /* statement: describe_statement  */
#line 178 "sql.y"
        {
            ast_node->statement_type = DESCRIBE_STMT;
            ast_node->describe_node = (yyvsp[0].describe_node);
        }
#line 1664 "y.tab.c"
    break;

  case 15: /* statement: show_statement  */
#line 183 "sql.y"
        {
            ast_node->statement_type = SHOW_STMT;
            ast_node->show_node = (yyvsp[0].show_node);
        }
#line 1673 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs RIGHTPAREN end  */
#line 199 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].s_value);
            create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1684 "y.tab.c"
    break;

  case 20: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs COMMA primary_key_statement RIGHTPAREN end  */
#line 206 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-6].s_value);
            create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
            create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1696 "y.tab.c"
    break;

  case 21: /* drop_table_statement: DROP TABLE table end  */
#line 216 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].s_value);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1706 "y.tab.c"
    break;

  case 22: /* select_statement: SELECT selection FROM table WHERE condition opt_limit end  */
#line 224 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-6].selection_node);
            select_node->table_name = (yyvsp[-4].s_value);
            select_node->condition_node = (yyvsp[-2].condition_node);
            select_node->limit_node = (yyvsp[-1].limit_node);
            (yyval.select_node) = select_node;
        }
#line 1719 "y.tab.c"
    break;

  case 23: /* select_statement: SELECT selection FROM table opt_limit end  */
#line 233 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-4].selection_node);
            select_node->table_name = (yyvsp[-2].s_value);
            select_node->limit_node = (yyvsp[-1].limit_node);
            (yyval.select_node) = select_node;
        }
#line 1731 "y.tab.c"
    break;

  case 24: /* insert_statement: INSERT INTO table VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 243 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-5].s_value);
            node->value_item_set_node = (yyvsp[-2].value_item_set_node);
            (yyval.insert_node) = node;
        }
#line 1743 "y.tab.c"
    break;

  case 25: /* insert_statement: INSERT INTO table LEFTPAREN columns RIGHTPAREN VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 251 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-8].s_value);
            node->columns_set_node = (yyvsp[-6].column_set_node);
            node->value_item_set_node = (yyvsp[-2].value_item_set_node);
            (yyval.insert_node) = node;
        }
#line 1756 "y.tab.c"
    break;

  case 26: /* update_statement: UPDATE table SET assignments end  */
#line 262 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-3].s_value);
            node->assignment_set_node = (yyvsp[-1].assignment_set_node);
            (yyval.update_node) = node;
        }
#line 1767 "y.tab.c"
    break;

  case 27: /* update_statement: UPDATE table SET assignments WHERE condition end  */
#line 269 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-5].s_value);
            node->assignment_set_node = (yyvsp[-3].assignment_set_node);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.update_node) = node;
        }
#line 1779 "y.tab.c"
    break;

  case 28: /* delete_statement: DELETE FROM table end  */
#line 279 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].s_value);
            (yyval.delete_node) = node;
        }
#line 1789 "y.tab.c"
    break;

  case 29: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 285 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].s_value);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1800 "y.tab.c"
    break;

  case 30: /* describe_statement: DESCRIBE table end  */
#line 294 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = db_strdup((yyvsp[-1].s_value));
            (yyval.describe_node) = node;
        }
#line 1810 "y.tab.c"
    break;

  case 31: /* show_statement: SHOW TABLES end  */
#line 302 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1818 "y.tab.c"
    break;

  case 32: /* show_statement: SHOW MEMORY end  */
#line 306 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1826 "y.tab.c"
    break;

  case 33: /* selection: scalar_exp_commalist  */
#line 312 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_set = (yyvsp[0].scalar_exp_set_node);
            (yyval.selection_node) = selection_node;
        }
#line 1837 "y.tab.c"
    break;

  case 34: /* selection: ASTERISK  */
#line 319 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 1847 "y.tab.c"
    break;

  case 35: /* table: IDENTIFIER  */
#line 327 "sql.y"
        {
            (yyval.s_value) = (yyvsp[0].s_value);
        }
#line 1855 "y.tab.c"
    break;

  case 36: /* scalar_exp_commalist: scalar_exp  */
#line 333 "sql.y"
        {
            ScalarExpSetNode *scalar_exp_set_node = make_scalar_exp_set_node();
            add_scalar_exp_node(scalar_exp_set_node, (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = scalar_exp_set_node;
        }
#line 1865 "y.tab.c"
    break;

  case 37: /* scalar_exp_commalist: scalar_exp_commalist COMMA scalar_exp  */
#line 339 "sql.y"
        {
            add_scalar_exp_node((yyvsp[-2].scalar_exp_set_node), (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = (yyvsp[-2].scalar_exp_set_node);
        }
#line 1874 "y.tab.c"
    break;

  case 38: /* scalar_exp: calculate  */
#line 346 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 1885 "y.tab.c"
    break;

  case 39: /* scalar_exp: column  */
#line 353 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 1896 "y.tab.c"
    break;

  case 40: /* scalar_exp: column AS IDENTIFIER  */
#line 360 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[-2].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
            (yyval.scalar_exp_node)->alias = db_strdup((yyvsp[0].s_value));
        }
#line 1908 "y.tab.c"
    break;

  case 41: /* scalar_exp: function  */
#line 368 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 1919 "y.tab.c"
    break;

  case 42: /* scalar_exp: function AS IDENTIFIER  */
#line 375 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[-2].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
            (yyval.scalar_exp_node)->alias = db_strdup((yyvsp[0].s_value));
        }
#line 1931 "y.tab.c"
    break;

  case 43: /* scalar_exp: LEFTPAREN scalar_exp RIGHTPAREN  */
#line 383 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 1939 "y.tab.c"
    break;

  case 44: /* calculate: scalar_exp PLUS scalar_exp  */
#line 389 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 1951 "y.tab.c"
    break;

  case 45: /* calculate: scalar_exp MINUS scalar_exp  */
#line 397 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 1963 "y.tab.c"
    break;

  case 46: /* calculate: scalar_exp ASTERISK scalar_exp  */
#line 405 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 1975 "y.tab.c"
    break;

  case 47: /* calculate: scalar_exp SOLIDUS scalar_exp  */
#line 413 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 1987 "y.tab.c"
    break;

  case 48: /* columns: column  */
#line 423 "sql.y"
        {
            ColumnSetNode *column_set_node = make_column_set_node();
            add_column_to_set(column_set_node, (yyvsp[0].column_node));
            (yyval.column_set_node) = column_set_node;
        }
#line 1997 "y.tab.c"
    break;

  case 49: /* columns: columns COMMA column  */
#line 429 "sql.y"
        {
            (yyval.column_set_node) = (yyvsp[-2].column_set_node);
            add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
        }
#line 2006 "y.tab.c"
    break;

  case 50: /* column_defs: column_def  */
#line 436 "sql.y"
        {
            ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
            add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
            (yyval.column_def_set_node) = column_def_set_node;
        }
#line 2016 "y.tab.c"
    break;

  case 51: /* column_defs: column_defs COMMA column_def  */
#line 442 "sql.y"
        {
            (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
            add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
        }
#line 2025 "y.tab.c"
    break;

  case 52: /* column_def: column data_type  */
#line 449 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-1].column_node);
            column_def_node->data_type = (yyvsp[0].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            column_def_node->is_define_len = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2039 "y.tab.c"
    break;

  case 53: /* column_def: column STRING LEFTPAREN INTVALUE RIGHTPAREN  */
#line 459 "sql.y"
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
#line 2054 "y.tab.c"
    break;

  case 54: /* column_def: column table  */
#line 470 "sql.y"
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
#line 2069 "y.tab.c"
    break;

  case 55: /* column_def: column data_type PRIMARY KEY  */
#line 481 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = true;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2082 "y.tab.c"
    break;

  case 56: /* column_def: column data_type NOT NULLX  */
#line 490 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = true;
            (yyval.column_def_node) = column_def_node;
        }
#line 2095 "y.tab.c"
    break;

  case 57: /* data_type: INT  */
#line 500 "sql.y"
                 { (yyval.data_type) = T_INT; }
#line 2101 "y.tab.c"
    break;

  case 58: /* data_type: LONG  */
#line 501 "sql.y"
                 { (yyval.data_type) = T_LONG;  }
#line 2107 "y.tab.c"
    break;

  case 59: /* data_type: CHAR  */
#line 502 "sql.y"
                 { (yyval.data_type) = T_CHAR; }
#line 2113 "y.tab.c"
    break;

  case 60: /* data_type: STRING  */
#line 503 "sql.y"
                 { (yyval.data_type) = T_STRING; }
#line 2119 "y.tab.c"
    break;

  case 61: /* data_type: BOOL  */
#line 504 "sql.y"
                 { (yyval.data_type) = T_BOOL; }
#line 2125 "y.tab.c"
    break;

  case 62: /* data_type: FLOAT  */
#line 505 "sql.y"
                 { (yyval.data_type) = T_FLOAT; }
#line 2131 "y.tab.c"
    break;

  case 63: /* data_type: DOUBLE  */
#line 506 "sql.y"
                 { (yyval.data_type) = T_DOUBLE; }
#line 2137 "y.tab.c"
    break;

  case 64: /* data_type: TIMESTAMP  */
#line 507 "sql.y"
                 { (yyval.data_type) = T_TIMESTAMP; }
#line 2143 "y.tab.c"
    break;

  case 65: /* data_type: DATE  */
#line 508 "sql.y"
                 { (yyval.data_type) = T_DATE; }
#line 2149 "y.tab.c"
    break;

  case 66: /* primary_key_statement: PRIMARY KEY LEFTPAREN column RIGHTPAREN  */
#line 512 "sql.y"
         {
             PrimaryKeyNode *primary_key_node = make_primary_key_node();
             primary_key_node->column = (yyvsp[-1].column_node);
             (yyval.primary_key_node) = primary_key_node;
         }
#line 2159 "y.tab.c"
    break;

  case 67: /* column: IDENTIFIER  */
#line 520 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[0].s_value));
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2170 "y.tab.c"
    break;

  case 68: /* column: IDENTIFIER POINT column  */
#line 527 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-2].s_value));
            column_node->sub_column = (yyvsp[0].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2182 "y.tab.c"
    break;

  case 69: /* column: IDENTIFIER LEFTPAREN scalar_exp_commalist RIGHTPAREN  */
#line 535 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-3].s_value));
            column_node->scalar_exp_set = (yyvsp[-1].scalar_exp_set_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2194 "y.tab.c"
    break;

  case 70: /* value_items: value_item  */
#line 545 "sql.y"
        {
            ValueItemSetNode *node = make_value_item_set_node();
            add_value_item(node, (yyvsp[0].value_item_node));
            (yyval.value_item_set_node) = node;
        }
#line 2204 "y.tab.c"
    break;

  case 71: /* value_items: value_items COMMA value_item  */
#line 551 "sql.y"
        {
            (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
            add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
        }
#line 2213 "y.tab.c"
    break;

  case 72: /* value_item: INTVALUE  */
#line 558 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->i_value = (yyvsp[0].i_value);
            node->data_type = T_INT;
            (yyval.value_item_node) = node;
        }
#line 2224 "y.tab.c"
    break;

  case 73: /* value_item: BOOLVALUE  */
#line 565 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->b_value = (yyvsp[0].b_value);
            node->data_type = T_BOOL;
            (yyval.value_item_node) = node;
        }
#line 2235 "y.tab.c"
    break;

  case 74: /* value_item: STRINGVALUE  */
#line 572 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->s_value = (yyvsp[0].s_value);
            node->data_type = T_STRING;
            (yyval.value_item_node) = node;
        }
#line 2246 "y.tab.c"
    break;

  case 75: /* value_item: FLOATVALUE  */
#line 579 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->f_value = (yyvsp[0].f_value);
            node->data_type = T_FLOAT;
            (yyval.value_item_node) = node;
        }
#line 2257 "y.tab.c"
    break;

  case 76: /* value_item: REFERVALUE  */
#line 586 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->r_value = (yyvsp[0].r_value);
            node->data_type = T_REFERENCE;
            (yyval.value_item_node) = node;
        }
#line 2268 "y.tab.c"
    break;

  case 77: /* REFERVALUE: LEFTPAREN value_items RIGHTPAREN  */
#line 596 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_item_set = (yyvsp[-1].value_item_set_node);
            (yyval.r_value) = refer;
        }
#line 2279 "y.tab.c"
    break;

  case 78: /* REFERVALUE: REF LEFTPAREN condition RIGHTPAREN  */
#line 604 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.r_value) = refer;
        }
#line 2290 "y.tab.c"
    break;

  case 79: /* BOOLVALUE: TRUE  */
#line 613 "sql.y"
        {
            (yyval.b_value) = true;
        }
#line 2298 "y.tab.c"
    break;

  case 80: /* BOOLVALUE: FALSE  */
#line 617 "sql.y"
        {
            (yyval.b_value) = false;
        }
#line 2306 "y.tab.c"
    break;

  case 81: /* assignments: assignment  */
#line 623 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2316 "y.tab.c"
    break;

  case 82: /* assignments: assignments COMMA assignment  */
#line 629 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2325 "y.tab.c"
    break;

  case 83: /* assignment: column EQ value_item  */
#line 636 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2336 "y.tab.c"
    break;

  case 84: /* condition: condition OR condition  */
#line 645 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2348 "y.tab.c"
    break;

  case 85: /* condition: condition AND condition  */
#line 653 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2360 "y.tab.c"
    break;

  case 86: /* condition: LEFTPAREN condition RIGHTPAREN  */
#line 661 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2368 "y.tab.c"
    break;

  case 87: /* condition: predicate  */
#line 665 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2379 "y.tab.c"
    break;

  case 88: /* predicate: comparison_predicate  */
#line 674 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2390 "y.tab.c"
    break;

  case 89: /* predicate: like_predicate  */
#line 681 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2401 "y.tab.c"
    break;

  case 90: /* predicate: in_predicate  */
#line 688 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 2412 "y.tab.c"
    break;

  case 91: /* comparison_predicate: column compare value_item  */
#line 697 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].value_item_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 2424 "y.tab.c"
    break;

  case 92: /* like_predicate: column LIKE value_item  */
#line 707 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 2435 "y.tab.c"
    break;

  case 93: /* in_predicate: column IN LEFTPAREN value_items RIGHTPAREN  */
#line 716 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_set = (yyvsp[-1].value_item_set_node);
            (yyval.in_node) = in_node;
        }
#line 2446 "y.tab.c"
    break;

  case 94: /* opt_limit: %empty  */
#line 725 "sql.y"
        {
            (yyval.limit_node) = NULL;
        }
#line 2454 "y.tab.c"
    break;

  case 95: /* opt_limit: LIMIT INTVALUE  */
#line 729 "sql.y"
        {
            LimitNode *limit_node = make_limit_node();
            limit_node->start = 0;
            limit_node->end = (yyvsp[0].i_value);
            (yyval.limit_node) = limit_node;
        }
#line 2465 "y.tab.c"
    break;

  case 96: /* opt_limit: LIMIT INTVALUE COMMA INTVALUE  */
#line 736 "sql.y"
        {
            LimitNode *limit_node = make_limit_node();
            limit_node->start = (yyvsp[-2].i_value);
            limit_node->end = (yyvsp[0].i_value);
            (yyval.limit_node) = limit_node;
        }
#line 2476 "y.tab.c"
    break;

  case 97: /* compare: EQ  */
#line 744 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 2482 "y.tab.c"
    break;

  case 98: /* compare: NE  */
#line 745 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 2488 "y.tab.c"
    break;

  case 99: /* compare: GT  */
#line 746 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 2494 "y.tab.c"
    break;

  case 100: /* compare: GE  */
#line 747 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 2500 "y.tab.c"
    break;

  case 101: /* compare: LT  */
#line 748 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 2506 "y.tab.c"
    break;

  case 102: /* compare: LE  */
#line 749 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 2512 "y.tab.c"
    break;

  case 103: /* function: MAX LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 753 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2523 "y.tab.c"
    break;

  case 104: /* function: MIN LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 760 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2534 "y.tab.c"
    break;

  case 105: /* function: COUNT LEFTPAREN function_value RIGHTPAREN  */
#line 767 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2545 "y.tab.c"
    break;

  case 106: /* function: SUM LEFTPAREN function_value RIGHTPAREN  */
#line 774 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2556 "y.tab.c"
    break;

  case 107: /* function: AVG LEFTPAREN function_value RIGHTPAREN  */
#line 781 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2567 "y.tab.c"
    break;

  case 108: /* function_value: INTVALUE  */
#line 790 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].i_value);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2578 "y.tab.c"
    break;

  case 109: /* function_value: column  */
#line 797 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2589 "y.tab.c"
    break;

  case 110: /* function_value: ASTERISK  */
#line 804 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 2599 "y.tab.c"
    break;

  case 111: /* non_all_function_value: INTVALUE  */
#line 812 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].i_value);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2610 "y.tab.c"
    break;

  case 112: /* non_all_function_value: column  */
#line 819 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2621 "y.tab.c"
    break;


#line 2625 "y.tab.c"

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

#line 830 "sql.y"

