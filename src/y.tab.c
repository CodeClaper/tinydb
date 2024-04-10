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
    SYSTEM = 310,                  /* SYSTEM  */
    CONFIG = 311,                  /* CONFIG  */
    MEMORY = 312,                  /* MEMORY  */
    IDENTIFIER = 313,              /* IDENTIFIER  */
    INTVALUE = 314,                /* INTVALUE  */
    FLOATVALUE = 315,              /* FLOATVALUE  */
    STRINGVALUE = 316              /* STRINGVALUE  */
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
#define SYSTEM 310
#define CONFIG 311
#define MEMORY 312
#define IDENTIFIER 313
#define INTVALUE 314
#define FLOATVALUE 315
#define STRINGVALUE 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "sql.y"

   char                     *strVal;
   int64_t                  intVal;
   float                    floatVal;
   bool                     boolVal;
   char                     *keyword;
   ReferValue               *referVal;
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
   TableRefNode             *table_ref_node;
   TableRefSetNode          *table_ref_set_node;
   QuerySpecNode            *query_spec_node;
   ValuesOrQuerySpecNode    *values_or_query_spec_node;
   FromClauseNode           *from_clause_node;
   WhereClauseNode          *where_clause_node;
   TableExpNode             *table_exp_node; 
   CreateTableNode          *create_table_node;
   DropTableNode            *drop_table_node;
   SelectNode               *select_node;
   InsertNode               *insert_node;
   UpdateNode               *update_node;
   DeleteNode               *delete_node;
   DescribeNode             *describe_node;
   ShowNode                 *show_node;
   Statement                *statement;
   Statements               *statements;

#line 310 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (Statements *states);


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
  YYSYMBOL_7_ = 7,                         /* '('  */
  YYSYMBOL_8_ = 8,                         /* ')'  */
  YYSYMBOL_NL = 9,                         /* NL  */
  YYSYMBOL_BEGINN = 10,                    /* BEGINN  */
  YYSYMBOL_COMMIT = 11,                    /* COMMIT  */
  YYSYMBOL_ROLLBACK = 12,                  /* ROLLBACK  */
  YYSYMBOL_CREATE = 13,                    /* CREATE  */
  YYSYMBOL_DROP = 14,                      /* DROP  */
  YYSYMBOL_SELECT = 15,                    /* SELECT  */
  YYSYMBOL_INSERT = 16,                    /* INSERT  */
  YYSYMBOL_UPDATE = 17,                    /* UPDATE  */
  YYSYMBOL_DELETE = 18,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 19,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 20,                      /* FROM  */
  YYSYMBOL_WHERE = 21,                     /* WHERE  */
  YYSYMBOL_INTO = 22,                      /* INTO  */
  YYSYMBOL_SET = 23,                       /* SET  */
  YYSYMBOL_VALUES = 24,                    /* VALUES  */
  YYSYMBOL_TABLE = 25,                     /* TABLE  */
  YYSYMBOL_LIMIT = 26,                     /* LIMIT  */
  YYSYMBOL_SHOW = 27,                      /* SHOW  */
  YYSYMBOL_TABLES = 28,                    /* TABLES  */
  YYSYMBOL_MAX = 29,                       /* MAX  */
  YYSYMBOL_MIN = 30,                       /* MIN  */
  YYSYMBOL_COUNT = 31,                     /* COUNT  */
  YYSYMBOL_SUM = 32,                       /* SUM  */
  YYSYMBOL_AVG = 33,                       /* AVG  */
  YYSYMBOL_REF = 34,                       /* REF  */
  YYSYMBOL_TRUE = 35,                      /* TRUE  */
  YYSYMBOL_FALSE = 36,                     /* FALSE  */
  YYSYMBOL_NULLX = 37,                     /* NULLX  */
  YYSYMBOL_AS = 38,                        /* AS  */
  YYSYMBOL_CHAR = 39,                      /* CHAR  */
  YYSYMBOL_INT = 40,                       /* INT  */
  YYSYMBOL_LONG = 41,                      /* LONG  */
  YYSYMBOL_STRING = 42,                    /* STRING  */
  YYSYMBOL_BOOL = 43,                      /* BOOL  */
  YYSYMBOL_FLOAT = 44,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 45,                    /* DOUBLE  */
  YYSYMBOL_DATE = 46,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 47,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 48,                   /* PRIMARY  */
  YYSYMBOL_KEY = 49,                       /* KEY  */
  YYSYMBOL_EQ = 50,                        /* EQ  */
  YYSYMBOL_NE = 51,                        /* NE  */
  YYSYMBOL_GT = 52,                        /* GT  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_LT = 54,                        /* LT  */
  YYSYMBOL_LE = 55,                        /* LE  */
  YYSYMBOL_IN = 56,                        /* IN  */
  YYSYMBOL_LIKE = 57,                      /* LIKE  */
  YYSYMBOL_AND = 58,                       /* AND  */
  YYSYMBOL_OR = 59,                        /* OR  */
  YYSYMBOL_NOT = 60,                       /* NOT  */
  YYSYMBOL_SYSTEM = 61,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 62,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 63,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 64,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 65,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 66,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 67,               /* STRINGVALUE  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '['  */
  YYSYMBOL_70_ = 70,                       /* ']'  */
  YYSYMBOL_71_ = 71,                       /* '{'  */
  YYSYMBOL_72_ = 72,                       /* '}'  */
  YYSYMBOL_73_ = 73,                       /* '.'  */
  YYSYMBOL_74_ = 74,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_statements = 76,                /* statements  */
  YYSYMBOL_statement = 77,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 78, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 79, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 80, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 81,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 82,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 83,          /* select_statement  */
  YYSYMBOL_insert_statement = 84,          /* insert_statement  */
  YYSYMBOL_update_statement = 85,          /* update_statement  */
  YYSYMBOL_delete_statement = 86,          /* delete_statement  */
  YYSYMBOL_describe_statement = 87,        /* describe_statement  */
  YYSYMBOL_show_statement = 88,            /* show_statement  */
  YYSYMBOL_selection = 89,                 /* selection  */
  YYSYMBOL_table_exp = 90,                 /* table_exp  */
  YYSYMBOL_from_clause = 91,               /* from_clause  */
  YYSYMBOL_table_ref_commalist = 92,       /* table_ref_commalist  */
  YYSYMBOL_table_ref = 93,                 /* table_ref  */
  YYSYMBOL_table = 94,                     /* table  */
  YYSYMBOL_range_variable = 95,            /* range_variable  */
  YYSYMBOL_opt_where_clause = 96,          /* opt_where_clause  */
  YYSYMBOL_where_clause = 97,              /* where_clause  */
  YYSYMBOL_values_or_query_spec = 98,      /* values_or_query_spec  */
  YYSYMBOL_query_spec = 99,                /* query_spec  */
  YYSYMBOL_scalar_exp_commalist = 100,     /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 101,               /* scalar_exp  */
  YYSYMBOL_calculate = 102,                /* calculate  */
  YYSYMBOL_columns = 103,                  /* columns  */
  YYSYMBOL_column_defs = 104,              /* column_defs  */
  YYSYMBOL_column_def = 105,               /* column_def  */
  YYSYMBOL_data_type = 106,                /* data_type  */
  YYSYMBOL_primary_key_statement = 107,    /* primary_key_statement  */
  YYSYMBOL_column = 108,                   /* column  */
  YYSYMBOL_value_items = 109,              /* value_items  */
  YYSYMBOL_value_item = 110,               /* value_item  */
  YYSYMBOL_REFERVALUE = 111,               /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 112,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 113,              /* assignments  */
  YYSYMBOL_assignment = 114,               /* assignment  */
  YYSYMBOL_condition = 115,                /* condition  */
  YYSYMBOL_predicate = 116,                /* predicate  */
  YYSYMBOL_comparison_predicate = 117,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 118,           /* like_predicate  */
  YYSYMBOL_in_predicate = 119,             /* in_predicate  */
  YYSYMBOL_compare = 120,                  /* compare  */
  YYSYMBOL_function = 121,                 /* function  */
  YYSYMBOL_function_value = 122,           /* function_value  */
  YYSYMBOL_non_all_function_value = 123,   /* non_all_function_value  */
  YYSYMBOL_end = 124                       /* end  */
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
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  234

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


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
       7,     8,     5,     3,    68,     4,    73,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    74,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,     2,    72,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   147,   147,   152,   159,   165,   171,   177,   184,   191,
     198,   205,   212,   219,   226,   235,   238,   241,   245,   252,
     263,   272,   282,   290,   302,   313,   319,   329,   338,   342,
     348,   355,   363,   373,   376,   384,   390,   397,   403,   410,
     419,   425,   432,   435,   441,   449,   456,   465,   474,   480,
     487,   494,   501,   508,   515,   519,   526,   534,   542,   550,
     560,   566,   573,   579,   586,   596,   607,   618,   627,   638,
     639,   640,   641,   642,   643,   644,   645,   646,   649,   657,
     664,   672,   680,   687,   693,   700,   707,   714,   721,   728,
     738,   746,   755,   759,   765,   771,   778,   787,   795,   803,
     807,   816,   823,   830,   839,   849,   858,   887,   888,   889,
     890,   891,   892,   895,   902,   909,   916,   923,   932,   939,
     946,   954,   961,   970,   971
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
  "'/'", "'('", "')'", "NL", "BEGINN", "COMMIT", "ROLLBACK", "CREATE",
  "DROP", "SELECT", "INSERT", "UPDATE", "DELETE", "DESCRIBE", "FROM",
  "WHERE", "INTO", "SET", "VALUES", "TABLE", "LIMIT", "SHOW", "TABLES",
  "MAX", "MIN", "COUNT", "SUM", "AVG", "REF", "TRUE", "FALSE", "NULLX",
  "AS", "CHAR", "INT", "LONG", "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE",
  "TIMESTAMP", "PRIMARY", "KEY", "EQ", "NE", "GT", "GE", "LT", "LE", "IN",
  "LIKE", "AND", "OR", "NOT", "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER",
  "INTVALUE", "FLOATVALUE", "STRINGVALUE", "','", "'['", "']'", "'{'",
  "'}'", "'.'", "';'", "$accept", "statements", "statement",
  "begin_transaction_statement", "commit_transaction_statement",
  "rollback_transaction_statement", "create_table_statement",
  "drop_table_statement", "select_statement", "insert_statement",
  "update_statement", "delete_statement", "describe_statement",
  "show_statement", "selection", "table_exp", "from_clause",
  "table_ref_commalist", "table_ref", "table", "range_variable",
  "opt_where_clause", "where_clause", "values_or_query_spec", "query_spec",
  "scalar_exp_commalist", "scalar_exp", "calculate", "columns",
  "column_defs", "column_def", "data_type", "primary_key_statement",
  "column", "value_items", "value_item", "REFERVALUE", "BOOLVALUE",
  "assignments", "assignment", "condition", "predicate",
  "comparison_predicate", "like_predicate", "in_predicate", "compare",
  "function", "function_value", "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-158)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-84)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     221,     1,     1,     1,    -1,     9,    18,     4,   -23,    26,
     -23,    38,   176,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,    35,  -158,  -158,  -158,
     -23,   -23,  -158,    87,    48,    79,   105,   118,   123,   135,
    -158,  -158,   127,  -158,  -158,  -158,   125,    32,   169,  -158,
    -158,  -158,  -158,  -158,  -158,   -23,  -158,   120,   -23,     1,
       1,     1,  -158,  -158,  -158,   141,     1,   163,     6,    82,
      42,    42,    15,    15,    15,    31,    91,    87,    91,   -23,
       1,   142,    87,    87,    87,    87,    87,    92,   117,    91,
       7,  -158,  -158,  -158,    91,  -158,  -158,  -158,    69,  -158,
    -158,   156,   162,  -158,  -158,  -158,   174,   175,   177,    31,
     158,   100,  -158,  -158,  -158,  -158,   114,    41,  -158,   129,
    -158,   -21,  -158,    31,  -158,  -158,   169,    93,    93,   161,
     161,  -158,    91,    18,   195,     1,  -158,   154,    19,  -158,
      31,  -158,    21,  -158,   183,    69,  -158,  -158,  -158,  -158,
    -158,  -158,   102,  -158,  -158,  -158,  -158,  -158,  -158,   198,
      69,    87,  -158,    31,    31,  -158,  -158,   -23,   152,  -158,
    -158,    80,    22,  -158,   125,    69,  -158,    69,    91,     1,
       3,     1,   -27,  -158,  -158,  -158,   199,  -158,  -158,  -158,
    -158,  -158,  -158,   -15,  -158,  -158,    69,  -158,   169,  -158,
     160,  -158,  -158,    78,    91,  -158,    23,  -158,  -158,  -158,
    -158,  -158,   170,  -158,   212,   178,   192,   205,    24,     1,
    -158,  -158,   237,     1,   238,  -158,  -158,  -158,  -158,    91,
    -158,  -158,   241,  -158
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   123,     0,    15,    16,    17,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
      92,    93,    79,    85,    88,    87,    33,    30,    48,    50,
      51,    53,    89,    86,    52,     0,    40,     0,     0,     0,
       0,     0,     1,     3,   124,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,    28,    29,     0,    20,    54,    90,     0,   121,
     122,     0,     0,   120,   118,   119,     0,     0,     0,     0,
       0,     0,   100,   101,   102,   103,     0,     0,    82,    34,
      35,    37,    21,     0,    32,    43,    49,    56,    57,    58,
      59,    55,     0,     0,     0,     0,    46,     0,    42,    94,
       0,    25,     0,    62,     0,     0,    84,   113,   114,   115,
     116,   117,     0,   107,   108,   109,   110,   111,   112,     0,
       0,     0,    91,     0,     0,    80,    81,     0,     0,    41,
      38,    44,     0,    60,    33,     0,    22,     0,     0,     0,
       0,     0,     0,    71,    69,    70,    72,    73,    74,    75,
      77,    76,    66,    64,    83,    99,     0,   105,   104,    98,
      97,    36,    39,     0,     0,    47,     0,    96,    95,    24,
      26,    18,     0,    63,     0,     0,     0,     0,     0,     0,
      61,    45,     0,     0,     0,    67,    68,   106,    23,     0,
      19,    65,     0,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -158,  -158,   233,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,   119,    76,  -158,  -158,    84,     5,
      85,   116,  -158,    52,  -158,   179,   -14,  -158,  -158,  -158,
      75,  -158,  -158,   -67,  -157,   -31,  -158,  -158,  -158,    81,
      17,  -158,  -158,  -158,  -158,  -158,  -158,    54,   187,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    46,    80,    81,   119,   120,   121,
     170,   124,   125,   135,   136,    47,    48,    49,   172,   142,
     143,   193,   214,    50,    68,    51,    52,    53,   138,   139,
     111,   112,   113,   114,   115,   161,    54,   106,   101,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    29,    69,   100,   100,   105,   105,   105,   110,   116,
      25,   118,    25,    57,    97,    59,    25,   168,   206,    67,
     103,   212,   137,    32,    30,    33,    55,   144,   140,   181,
     203,   221,   227,   216,    31,    65,    66,    42,   109,   218,
     123,    56,   110,   169,    64,   217,    58,    34,    35,    36,
      37,    38,    39,    40,    41,    70,   110,    91,    92,    93,
      88,   163,   164,    90,    95,   173,    60,   146,   126,   127,
     128,   129,   130,   110,    98,    26,   145,    26,   122,    42,
     104,    26,    42,    43,    44,    45,    71,   178,   141,   182,
     204,    98,    98,   133,    33,    42,   110,   110,    85,    86,
      82,    61,   134,    39,    40,    41,    42,    99,   162,    82,
     195,   137,    72,   166,   194,   144,    34,    35,    36,    37,
      38,    39,    40,    41,   132,    73,   152,   107,   108,   197,
      74,    87,   133,   176,    43,    44,    45,   220,   163,   164,
     171,   134,    75,    89,   194,    79,   207,   198,    94,   192,
     -83,    42,    43,    44,    45,    42,   131,   180,   163,   164,
     163,   164,   232,   123,   147,   194,    83,    84,    85,    86,
     148,    96,    83,    84,    85,    86,    62,   209,   210,   211,
     199,   200,   149,   150,   165,   151,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    76,   167,    77,    87,
      78,    87,   175,    11,   177,   196,   215,    87,   153,   154,
     155,   156,   157,   158,   159,   160,   169,   228,   163,   222,
     223,   230,   183,   184,   185,   186,   187,   188,   189,   190,
     191,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   225,   226,   224,   229,    63,   231,    56,    11,   233,
     205,   201,   174,   202,   179,   219,   117,   213,   102,   208
};

static const yytype_uint8 yycheck[] =
{
       2,     3,    33,    70,    71,    72,    73,    74,    75,    76,
       9,    78,     9,     8,     8,    10,     9,    38,   175,    33,
       5,    48,    89,     5,    25,     7,    22,    94,    21,     8,
       8,     8,     8,    48,    25,    30,    31,    64,     7,   196,
      21,    64,   109,    64,     9,    60,    20,    29,    30,    31,
      32,    33,    34,    35,    36,     7,   123,    59,    60,    61,
      55,    58,    59,    58,    66,   132,    28,    98,    82,    83,
      84,    85,    86,   140,    68,    74,     7,    74,    80,    64,
      65,    74,    64,    65,    66,    67,     7,    68,    90,    68,
      68,    68,    68,    15,     7,    64,   163,   164,     5,     6,
      68,    63,    24,    34,    35,    36,    64,    65,     8,    68,
       8,   178,     7,    72,   145,   182,    29,    30,    31,    32,
      33,    34,    35,    36,     7,     7,   109,    73,    74,   160,
       7,    38,    15,   135,    65,    66,    67,   204,    58,    59,
     123,    24,     7,    23,   175,    20,   177,   161,     7,   144,
      68,    64,    65,    66,    67,    64,    64,   140,    58,    59,
      58,    59,   229,    21,     8,   196,     3,     4,     5,     6,
       8,     8,     3,     4,     5,     6,     0,   179,   180,   181,
     163,   164,     8,     8,    70,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    69,    68,    71,    38,
      73,    38,     7,    27,    50,     7,     7,    38,    50,    51,
      52,    53,    54,    55,    56,    57,    64,   219,    58,    49,
       8,   223,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    49,    37,    65,     7,    12,     8,    64,    27,     8,
     174,   167,   133,   168,   138,   203,    77,   182,    71,   178
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    27,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,     9,    74,   124,   124,   124,
      25,    25,     5,     7,    29,    30,    31,    32,    33,    34,
      35,    36,    64,    65,    66,    67,    89,   100,   101,   102,
     108,   110,   111,   112,   121,    22,    64,    94,    20,    94,
      28,    63,     0,    77,     9,    94,    94,   101,   109,   110,
       7,     7,     7,     7,     7,     7,    69,    71,    73,    20,
      90,    91,    68,     3,     4,     5,     6,    38,    94,    23,
      94,   124,   124,   124,     7,   124,     8,     8,    68,    65,
     108,   123,   123,     5,    65,   108,   122,   122,   122,     7,
     108,   115,   116,   117,   118,   119,   108,   100,   108,    92,
      93,    94,   124,    21,    96,    97,   101,   101,   101,   101,
     101,    64,     7,    15,    24,    98,    99,   108,   113,   114,
      21,   124,   104,   105,   108,     7,   110,     8,     8,     8,
       8,     8,   115,    50,    51,    52,    53,    54,    55,    56,
      57,   120,     8,    58,    59,    70,    72,    68,    38,    64,
      95,   115,   103,   108,    89,     7,   124,    50,    68,    96,
     115,     8,    68,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    94,   106,   110,     8,     7,   110,   101,   115,
     115,    93,    95,     8,    68,    90,   109,   110,   114,   124,
     124,   124,    48,   105,   107,     7,    48,    60,   109,    98,
     108,     8,    49,     8,    65,    49,    37,     8,   124,     7,
     124,     8,   108,     8
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    78,    79,    80,    81,    81,
      82,    83,    84,    84,    85,    86,    86,    87,    88,    88,
      89,    89,    90,    91,    91,    92,    92,    93,    93,    93,
      94,    95,    96,    96,    97,    98,    98,    99,   100,   100,
     101,   101,   101,   101,   101,   101,   102,   102,   102,   102,
     103,   103,   104,   104,   105,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   107,   108,
     108,   108,   108,   109,   109,   110,   110,   110,   110,   110,
     111,   111,   112,   112,   113,   113,   114,   115,   115,   115,
     115,   116,   116,   116,   117,   118,   119,   120,   120,   120,
     120,   120,   120,   121,   121,   121,   121,   121,   122,   122,
     122,   123,   123,   124,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     7,     9,
       4,     4,     5,     8,     6,     4,     6,     3,     3,     3,
       1,     1,     2,     0,     2,     1,     3,     1,     2,     3,
       1,     1,     0,     1,     2,     4,     1,     3,     1,     3,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     2,     5,     2,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     1,
       4,     4,     3,     1,     3,     1,     1,     1,     1,     1,
       3,     4,     1,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     3,     5,     1,     1,     1,
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
        yyerror (states, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, states); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, Statements *states)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (states);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, Statements *states)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, states);
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
                 int yyrule, Statements *states)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], states);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, states); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, Statements *states)
{
  YY_USE (yyvaluep);
  YY_USE (states);
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
yyparse (Statements *states)
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
  case 2: /* statements: statement  */
#line 148 "sql.y"
        {
            add_statement(states, (yyvsp[0].statement));
            (yyval.statements) = states;
        }
#line 1594 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 153 "sql.y"
        {
            add_statement((yyvsp[-1].statements), (yyvsp[0].statement));
            (yyval.statements) = (yyvsp[-1].statements);
        }
#line 1603 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 160 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1613 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 166 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1623 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 172 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1633 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 178 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1644 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 185 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1655 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 192 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1666 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 199 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1677 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 206 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1688 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 213 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1699 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 220 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1710 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 227 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1721 "y.tab.c"
    break;

  case 18: /* create_table_statement: CREATE TABLE table '(' column_defs ')' end  */
#line 246 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].strVal);
            create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1732 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table '(' column_defs ',' primary_key_statement ')' end  */
#line 253 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-6].strVal);
            create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
            create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1744 "y.tab.c"
    break;

  case 20: /* drop_table_statement: DROP TABLE table end  */
#line 264 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].strVal);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1754 "y.tab.c"
    break;

  case 21: /* select_statement: SELECT selection table_exp end  */
#line 273 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1765 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table values_or_query_spec end  */
#line 283 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-2].strVal);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1777 "y.tab.c"
    break;

  case 23: /* insert_statement: INSERT INTO table '(' columns ')' values_or_query_spec end  */
#line 291 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-5].strVal);
            node->columns_set_node = (yyvsp[-3].column_set_node);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1790 "y.tab.c"
    break;

  case 24: /* update_statement: UPDATE table SET assignments opt_where_clause end  */
#line 303 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-4].strVal);
            node->assignment_set_node = (yyvsp[-2].assignment_set_node);
            node->where_clause = (yyvsp[-1].where_clause_node);
            (yyval.update_node) = node;
        }
#line 1802 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table end  */
#line 314 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.delete_node) = node;
        }
#line 1812 "y.tab.c"
    break;

  case 26: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 320 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].strVal);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1823 "y.tab.c"
    break;

  case 27: /* describe_statement: DESCRIBE table end  */
#line 330 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = db_strdup((yyvsp[-1].strVal));
            (yyval.describe_node) = node;
        }
#line 1833 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW TABLES end  */
#line 339 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1841 "y.tab.c"
    break;

  case 29: /* show_statement: SHOW MEMORY end  */
#line 343 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1849 "y.tab.c"
    break;

  case 30: /* selection: scalar_exp_commalist  */
#line 349 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_set = (yyvsp[0].scalar_exp_set_node);
            (yyval.selection_node) = selection_node;
        }
#line 1860 "y.tab.c"
    break;

  case 31: /* selection: '*'  */
#line 356 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 1870 "y.tab.c"
    break;

  case 32: /* table_exp: from_clause opt_where_clause  */
#line 364 "sql.y"
        {
            TableExpNode *table_exp = make_table_exp_node();
            table_exp->from_clause = (yyvsp[-1].from_clause_node);
            table_exp->where_clause = (yyvsp[0].where_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 1881 "y.tab.c"
    break;

  case 33: /* from_clause: %empty  */
#line 373 "sql.y"
        {
            (yyval.from_clause_node) = NULL;
        }
#line 1889 "y.tab.c"
    break;

  case 34: /* from_clause: FROM table_ref_commalist  */
#line 377 "sql.y"
        {
            FromClauseNode *from_clause = make_from_clause_node();
            from_clause->from = (yyvsp[0].table_ref_set_node);
            (yyval.from_clause_node) = from_clause;
        }
#line 1899 "y.tab.c"
    break;

  case 35: /* table_ref_commalist: table_ref  */
#line 385 "sql.y"
        {
            TableRefSetNode *table_ref_set = make_table_ref_set_node();
            add_table_ref_to_set(table_ref_set, (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = table_ref_set;
        }
#line 1909 "y.tab.c"
    break;

  case 36: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 391 "sql.y"
        {
            add_table_ref_to_set((yyvsp[-2].table_ref_set_node), (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = (yyvsp[-2].table_ref_set_node);
        }
#line 1918 "y.tab.c"
    break;

  case 37: /* table_ref: table  */
#line 398 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 1928 "y.tab.c"
    break;

  case 38: /* table_ref: table range_variable  */
#line 404 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-1].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 1939 "y.tab.c"
    break;

  case 39: /* table_ref: table AS range_variable  */
#line 411 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-2].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 1950 "y.tab.c"
    break;

  case 40: /* table: IDENTIFIER  */
#line 420 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 1958 "y.tab.c"
    break;

  case 41: /* range_variable: IDENTIFIER  */
#line 426 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 1966 "y.tab.c"
    break;

  case 42: /* opt_where_clause: %empty  */
#line 432 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 1974 "y.tab.c"
    break;

  case 43: /* opt_where_clause: where_clause  */
#line 436 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 1982 "y.tab.c"
    break;

  case 44: /* where_clause: WHERE condition  */
#line 442 "sql.y"
        {
            WhereClauseNode *where_clause_node = make_where_clause_node();
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 1992 "y.tab.c"
    break;

  case 45: /* values_or_query_spec: VALUES '(' value_items ')'  */
#line 450 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = (yyvsp[-1].value_item_set_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2003 "y.tab.c"
    break;

  case 46: /* values_or_query_spec: query_spec  */
#line 457 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = (yyvsp[0].query_spec_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2014 "y.tab.c"
    break;

  case 47: /* query_spec: SELECT selection table_exp  */
#line 466 "sql.y"
        {
            QuerySpecNode *query_spec = make_query_spec_node();
            query_spec->selection = (yyvsp[-1].selection_node);
            query_spec->table_exp = (yyvsp[0].table_exp_node);
            (yyval.query_spec_node) = query_spec;
        }
#line 2025 "y.tab.c"
    break;

  case 48: /* scalar_exp_commalist: scalar_exp  */
#line 475 "sql.y"
        {
            ScalarExpSetNode *scalar_exp_set_node = make_scalar_exp_set_node();
            add_scalar_exp_node(scalar_exp_set_node, (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = scalar_exp_set_node;
        }
#line 2035 "y.tab.c"
    break;

  case 49: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 481 "sql.y"
        {
            add_scalar_exp_node((yyvsp[-2].scalar_exp_set_node), (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = (yyvsp[-2].scalar_exp_set_node);
        }
#line 2044 "y.tab.c"
    break;

  case 50: /* scalar_exp: calculate  */
#line 488 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2055 "y.tab.c"
    break;

  case 51: /* scalar_exp: column  */
#line 495 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2066 "y.tab.c"
    break;

  case 52: /* scalar_exp: function  */
#line 502 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2077 "y.tab.c"
    break;

  case 53: /* scalar_exp: value_item  */
#line 509 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2088 "y.tab.c"
    break;

  case 54: /* scalar_exp: '(' scalar_exp ')'  */
#line 516 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2096 "y.tab.c"
    break;

  case 55: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 520 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].strVal);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2105 "y.tab.c"
    break;

  case 56: /* calculate: scalar_exp '+' scalar_exp  */
#line 527 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2117 "y.tab.c"
    break;

  case 57: /* calculate: scalar_exp '-' scalar_exp  */
#line 535 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2129 "y.tab.c"
    break;

  case 58: /* calculate: scalar_exp '*' scalar_exp  */
#line 543 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2141 "y.tab.c"
    break;

  case 59: /* calculate: scalar_exp '/' scalar_exp  */
#line 551 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2153 "y.tab.c"
    break;

  case 60: /* columns: column  */
#line 561 "sql.y"
        {
            ColumnSetNode *column_set_node = make_column_set_node();
            add_column_to_set(column_set_node, (yyvsp[0].column_node));
            (yyval.column_set_node) = column_set_node;
        }
#line 2163 "y.tab.c"
    break;

  case 61: /* columns: columns ',' column  */
#line 567 "sql.y"
        {
            (yyval.column_set_node) = (yyvsp[-2].column_set_node);
            add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
        }
#line 2172 "y.tab.c"
    break;

  case 62: /* column_defs: column_def  */
#line 574 "sql.y"
        {
            ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
            add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
            (yyval.column_def_set_node) = column_def_set_node;
        }
#line 2182 "y.tab.c"
    break;

  case 63: /* column_defs: column_defs ',' column_def  */
#line 580 "sql.y"
        {
            (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
            add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
        }
#line 2191 "y.tab.c"
    break;

  case 64: /* column_def: column data_type  */
#line 587 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-1].column_node);
            column_def_node->data_type = (yyvsp[0].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            column_def_node->is_define_len = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2205 "y.tab.c"
    break;

  case 65: /* column_def: column STRING '(' INTVALUE ')'  */
#line 597 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-4].column_node);
            column_def_node->data_type = T_STRING;
            column_def_node->data_len = (yyvsp[-1].intVal);
            column_def_node->is_define_len = true;
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2220 "y.tab.c"
    break;

  case 66: /* column_def: column table  */
#line 608 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-1].column_node);
            column_def_node->data_type = T_REFERENCE;
            column_def_node->table_name = (yyvsp[0].strVal);
            column_def_node->is_define_len = false;
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2235 "y.tab.c"
    break;

  case 67: /* column_def: column data_type PRIMARY KEY  */
#line 619 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = true;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2248 "y.tab.c"
    break;

  case 68: /* column_def: column data_type NOT NULLX  */
#line 628 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = true;
            (yyval.column_def_node) = column_def_node;
        }
#line 2261 "y.tab.c"
    break;

  case 69: /* data_type: INT  */
#line 638 "sql.y"
                 { (yyval.data_type) = T_INT; }
#line 2267 "y.tab.c"
    break;

  case 70: /* data_type: LONG  */
#line 639 "sql.y"
                 { (yyval.data_type) = T_LONG;  }
#line 2273 "y.tab.c"
    break;

  case 71: /* data_type: CHAR  */
#line 640 "sql.y"
                 { (yyval.data_type) = T_CHAR; }
#line 2279 "y.tab.c"
    break;

  case 72: /* data_type: STRING  */
#line 641 "sql.y"
                 { (yyval.data_type) = T_STRING; }
#line 2285 "y.tab.c"
    break;

  case 73: /* data_type: BOOL  */
#line 642 "sql.y"
                 { (yyval.data_type) = T_BOOL; }
#line 2291 "y.tab.c"
    break;

  case 74: /* data_type: FLOAT  */
#line 643 "sql.y"
                 { (yyval.data_type) = T_FLOAT; }
#line 2297 "y.tab.c"
    break;

  case 75: /* data_type: DOUBLE  */
#line 644 "sql.y"
                 { (yyval.data_type) = T_DOUBLE; }
#line 2303 "y.tab.c"
    break;

  case 76: /* data_type: TIMESTAMP  */
#line 645 "sql.y"
                 { (yyval.data_type) = T_TIMESTAMP; }
#line 2309 "y.tab.c"
    break;

  case 77: /* data_type: DATE  */
#line 646 "sql.y"
                 { (yyval.data_type) = T_DATE; }
#line 2315 "y.tab.c"
    break;

  case 78: /* primary_key_statement: PRIMARY KEY '(' column ')'  */
#line 650 "sql.y"
         {
             PrimaryKeyNode *primary_key_node = make_primary_key_node();
             primary_key_node->column = (yyvsp[-1].column_node);
             (yyval.primary_key_node) = primary_key_node;
         }
#line 2325 "y.tab.c"
    break;

  case 79: /* column: IDENTIFIER  */
#line 658 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[0].strVal));
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2336 "y.tab.c"
    break;

  case 80: /* column: IDENTIFIER '[' column ']'  */
#line 665 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-3].strVal));
            column_node->sub_column = (yyvsp[-1].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2348 "y.tab.c"
    break;

  case 81: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 673 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-3].strVal));
            column_node->scalar_exp_set = (yyvsp[-1].scalar_exp_set_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2360 "y.tab.c"
    break;

  case 82: /* column: IDENTIFIER '.' column  */
#line 681 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = db_strdup((yyvsp[-2].strVal));
        }
#line 2369 "y.tab.c"
    break;

  case 83: /* value_items: value_item  */
#line 688 "sql.y"
        {
            ValueItemSetNode *node = make_value_item_set_node();
            add_value_item(node, (yyvsp[0].value_item_node));
            (yyval.value_item_set_node) = node;
        }
#line 2379 "y.tab.c"
    break;

  case 84: /* value_items: value_items ',' value_item  */
#line 694 "sql.y"
        {
            (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
            add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
        }
#line 2388 "y.tab.c"
    break;

  case 85: /* value_item: INTVALUE  */
#line 701 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.i_value = (yyvsp[0].intVal);
            node->data_type = T_INT;
            (yyval.value_item_node) = node;
        }
#line 2399 "y.tab.c"
    break;

  case 86: /* value_item: BOOLVALUE  */
#line 708 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.b_value = (yyvsp[0].boolVal);
            node->data_type = T_BOOL;
            (yyval.value_item_node) = node;
        }
#line 2410 "y.tab.c"
    break;

  case 87: /* value_item: STRINGVALUE  */
#line 715 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.s_value = (yyvsp[0].strVal);
            node->data_type = T_STRING;
            (yyval.value_item_node) = node;
        }
#line 2421 "y.tab.c"
    break;

  case 88: /* value_item: FLOATVALUE  */
#line 722 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.f_value = (yyvsp[0].floatVal);
            node->data_type = T_FLOAT;
            (yyval.value_item_node) = node;
        }
#line 2432 "y.tab.c"
    break;

  case 89: /* value_item: REFERVALUE  */
#line 729 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.r_value = (yyvsp[0].referVal);
            node->data_type = T_REFERENCE;
            (yyval.value_item_node) = node;
        }
#line 2443 "y.tab.c"
    break;

  case 90: /* REFERVALUE: '(' value_items ')'  */
#line 739 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_item_set = (yyvsp[-1].value_item_set_node);
            (yyval.referVal) = refer;
        }
#line 2454 "y.tab.c"
    break;

  case 91: /* REFERVALUE: REF '(' condition ')'  */
#line 747 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.referVal) = refer;
        }
#line 2465 "y.tab.c"
    break;

  case 92: /* BOOLVALUE: TRUE  */
#line 756 "sql.y"
        {
            (yyval.boolVal) = true;
        }
#line 2473 "y.tab.c"
    break;

  case 93: /* BOOLVALUE: FALSE  */
#line 760 "sql.y"
        {
            (yyval.boolVal) = false;
        }
#line 2481 "y.tab.c"
    break;

  case 94: /* assignments: assignment  */
#line 766 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2491 "y.tab.c"
    break;

  case 95: /* assignments: assignments ',' assignment  */
#line 772 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2500 "y.tab.c"
    break;

  case 96: /* assignment: column EQ value_item  */
#line 779 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2511 "y.tab.c"
    break;

  case 97: /* condition: condition OR condition  */
#line 788 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2523 "y.tab.c"
    break;

  case 98: /* condition: condition AND condition  */
#line 796 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2535 "y.tab.c"
    break;

  case 99: /* condition: '(' condition ')'  */
#line 804 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2543 "y.tab.c"
    break;

  case 100: /* condition: predicate  */
#line 808 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2554 "y.tab.c"
    break;

  case 101: /* predicate: comparison_predicate  */
#line 817 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2565 "y.tab.c"
    break;

  case 102: /* predicate: like_predicate  */
#line 824 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2576 "y.tab.c"
    break;

  case 103: /* predicate: in_predicate  */
#line 831 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 2587 "y.tab.c"
    break;

  case 104: /* comparison_predicate: column compare scalar_exp  */
#line 840 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 2599 "y.tab.c"
    break;

  case 105: /* like_predicate: column LIKE value_item  */
#line 850 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 2610 "y.tab.c"
    break;

  case 106: /* in_predicate: column IN '(' value_items ')'  */
#line 859 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_set = (yyvsp[-1].value_item_set_node);
            (yyval.in_node) = in_node;
        }
#line 2621 "y.tab.c"
    break;

  case 107: /* compare: EQ  */
#line 887 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 2627 "y.tab.c"
    break;

  case 108: /* compare: NE  */
#line 888 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 2633 "y.tab.c"
    break;

  case 109: /* compare: GT  */
#line 889 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 2639 "y.tab.c"
    break;

  case 110: /* compare: GE  */
#line 890 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 2645 "y.tab.c"
    break;

  case 111: /* compare: LT  */
#line 891 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 2651 "y.tab.c"
    break;

  case 112: /* compare: LE  */
#line 892 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 2657 "y.tab.c"
    break;

  case 113: /* function: MAX '(' non_all_function_value ')'  */
#line 896 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2668 "y.tab.c"
    break;

  case 114: /* function: MIN '(' non_all_function_value ')'  */
#line 903 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2679 "y.tab.c"
    break;

  case 115: /* function: COUNT '(' function_value ')'  */
#line 910 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2690 "y.tab.c"
    break;

  case 116: /* function: SUM '(' function_value ')'  */
#line 917 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2701 "y.tab.c"
    break;

  case 117: /* function: AVG '(' function_value ')'  */
#line 924 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2712 "y.tab.c"
    break;

  case 118: /* function_value: INTVALUE  */
#line 933 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2723 "y.tab.c"
    break;

  case 119: /* function_value: column  */
#line 940 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2734 "y.tab.c"
    break;

  case 120: /* function_value: '*'  */
#line 947 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 2744 "y.tab.c"
    break;

  case 121: /* non_all_function_value: INTVALUE  */
#line 955 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2755 "y.tab.c"
    break;

  case 122: /* non_all_function_value: column  */
#line 962 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2766 "y.tab.c"
    break;


#line 2770 "y.tab.c"

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
      yyerror (states, YY_("syntax error"));
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
                      yytoken, &yylval, states);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, states);
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
  yyerror (states, YY_("memory exhausted"));
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
                  yytoken, &yylval, states);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, states);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 973 "sql.y"

