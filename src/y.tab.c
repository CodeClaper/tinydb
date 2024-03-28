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
   TableRefNode             *table_ref_node;
   TableRefSetNode          *table_ref_set_node;
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

#line 308 "y.tab.c"

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
  YYSYMBOL_scalar_exp_commalist = 98,      /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 99,                /* scalar_exp  */
  YYSYMBOL_calculate = 100,                /* calculate  */
  YYSYMBOL_columns = 101,                  /* columns  */
  YYSYMBOL_column_defs = 102,              /* column_defs  */
  YYSYMBOL_column_def = 103,               /* column_def  */
  YYSYMBOL_data_type = 104,                /* data_type  */
  YYSYMBOL_primary_key_statement = 105,    /* primary_key_statement  */
  YYSYMBOL_column = 106,                   /* column  */
  YYSYMBOL_value_items = 107,              /* value_items  */
  YYSYMBOL_value_item = 108,               /* value_item  */
  YYSYMBOL_REFERVALUE = 109,               /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 110,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 111,              /* assignments  */
  YYSYMBOL_assignment = 112,               /* assignment  */
  YYSYMBOL_condition = 113,                /* condition  */
  YYSYMBOL_predicate = 114,                /* predicate  */
  YYSYMBOL_comparison_predicate = 115,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 116,           /* like_predicate  */
  YYSYMBOL_in_predicate = 117,             /* in_predicate  */
  YYSYMBOL_compare = 118,                  /* compare  */
  YYSYMBOL_function = 119,                 /* function  */
  YYSYMBOL_function_value = 120,           /* function_value  */
  YYSYMBOL_non_all_function_value = 121,   /* non_all_function_value  */
  YYSYMBOL_end = 122                       /* end  */
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
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
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
       0,   143,   143,   148,   155,   161,   167,   173,   180,   187,
     194,   201,   208,   215,   222,   231,   234,   237,   240,   247,
     257,   265,   274,   282,   293,   300,   310,   316,   325,   333,
     337,   343,   350,   358,   367,   375,   381,   388,   394,   401,
     410,   416,   423,   426,   432,   440,   446,   453,   460,   467,
     474,   481,   485,   492,   500,   508,   516,   526,   532,   539,
     545,   552,   562,   573,   584,   593,   604,   605,   606,   607,
     608,   609,   610,   611,   612,   615,   623,   630,   638,   646,
     653,   659,   666,   673,   680,   687,   694,   704,   712,   721,
     725,   731,   737,   744,   753,   761,   769,   773,   782,   789,
     796,   805,   815,   824,   853,   854,   855,   856,   857,   858,
     861,   868,   875,   882,   889,   898,   905,   912,   920,   927,
     936,   937
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
  "opt_where_clause", "where_clause", "scalar_exp_commalist", "scalar_exp",
  "calculate", "columns", "column_defs", "column_def", "data_type",
  "primary_key_statement", "column", "value_items", "value_item",
  "REFERVALUE", "BOOLVALUE", "assignments", "assignment", "condition",
  "predicate", "comparison_predicate", "like_predicate", "in_predicate",
  "compare", "function", "function_value", "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-151)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-81)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     241,    13,    13,    13,     4,     9,   113,    41,   -24,    52,
     -24,   -12,   223,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,    61,  -151,  -151,  -151,
     -24,   -24,  -151,   155,    70,    78,    91,   108,   109,   112,
    -151,  -151,   125,  -151,  -151,  -151,   107,    60,   154,  -151,
    -151,  -151,  -151,  -151,  -151,   -24,  -151,   114,   -24,    13,
      13,    13,  -151,  -151,  -151,   128,    13,   126,    23,    82,
     -18,   -18,    31,    31,    31,    11,    74,   155,    74,   -24,
      13,   130,   155,   155,   155,   155,   155,    92,     0,    74,
      -1,  -151,  -151,  -151,    74,  -151,  -151,  -151,    87,  -151,
    -151,   168,   173,  -151,  -151,  -151,   174,   175,   187,    11,
     116,    -4,  -151,  -151,  -151,  -151,    93,    42,  -151,   129,
    -151,   -32,  -151,    11,  -151,  -151,   154,    55,    55,   161,
     161,  -151,    74,   193,   162,    18,  -151,    11,  -151,    29,
    -151,   163,    87,  -151,  -151,  -151,  -151,  -151,  -151,    48,
    -151,  -151,  -151,  -151,  -151,  -151,   204,    87,   155,  -151,
      11,    11,  -151,  -151,   -24,   149,  -151,  -151,    50,    33,
    -151,    87,    87,    11,    74,  -151,    10,    13,     1,  -151,
    -151,  -151,   208,  -151,  -151,  -151,  -151,  -151,  -151,   -25,
    -151,  -151,    87,  -151,   154,  -151,   158,  -151,  -151,   194,
      74,    35,  -151,    10,  -151,  -151,  -151,   176,  -151,   216,
     165,   177,   191,    36,   224,  -151,    13,  -151,   225,    13,
     235,  -151,  -151,  -151,    87,  -151,    74,  -151,  -151,    37,
     236,    13,  -151,  -151
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   120,     0,    15,    16,    17,
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
      89,    90,    76,    82,    85,    84,     0,    31,    45,    47,
      48,    50,    86,    83,    49,     0,    40,     0,     0,     0,
       0,     0,     1,     3,   121,     0,     0,     0,     0,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    30,     0,    20,    51,    87,     0,   118,
     119,     0,     0,   117,   115,   116,     0,     0,     0,     0,
       0,     0,    97,    98,    99,   100,     0,     0,    79,    34,
      35,    37,    21,     0,    33,    43,    46,    53,    54,    55,
      56,    52,     0,     0,     0,     0,    91,     0,    26,     0,
      59,     0,     0,    81,   110,   111,   112,   113,   114,     0,
     104,   105,   106,   107,   108,   109,     0,     0,     0,    88,
       0,     0,    77,    78,     0,     0,    41,    38,    44,     0,
      57,     0,     0,     0,     0,    24,     0,     0,     0,    68,
      66,    67,    69,    70,    71,    72,    74,    73,    63,    61,
      80,    96,     0,   102,   101,    95,    94,    36,    39,     0,
       0,     0,    93,     0,    92,    27,    18,     0,    60,     0,
       0,     0,     0,     0,     0,    58,     0,    25,     0,     0,
       0,    64,    65,   103,     0,    22,     0,    19,    62,     0,
       0,     0,    75,    23
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,   233,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,    83,    -5,
      81,  -151,  -151,   171,    -3,  -151,  -151,  -151,    71,  -151,
    -151,   -61,  -150,   -31,  -151,  -151,  -151,    88,   -71,  -151,
    -151,  -151,  -151,  -151,  -151,    51,   190,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    46,    80,    81,   119,   120,   121,
     167,   124,   125,    47,    48,    49,   169,   139,   140,   189,
     209,    50,    68,    51,    52,    53,   135,   136,   111,   112,
     113,   114,   115,   158,    54,   106,   101,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    29,    69,    57,   159,    59,   165,   132,    25,   100,
     100,   105,   105,   105,   110,   116,    60,   118,   109,    25,
     137,   201,    25,   211,   133,    65,    66,    25,   134,    30,
      67,    97,   166,   141,    31,   212,   103,   177,   149,   173,
      56,   199,   213,   216,   223,   231,    42,    99,   110,   207,
      88,    61,   168,    90,   160,   161,   191,    91,    92,    93,
      85,    86,   110,    55,    95,    42,   176,   143,   160,   161,
      64,   170,    58,    26,   229,    42,   110,    70,   122,   126,
     127,   128,   129,   130,    26,    71,   174,    26,   138,   195,
     196,    98,    26,    87,   142,    42,   104,   178,    72,   110,
     110,   200,   203,    98,    98,    98,   160,   161,   160,   161,
      82,   190,   110,   134,   163,    73,    74,   141,    32,    75,
      33,    39,    40,    41,   107,   108,   193,    79,    82,    83,
      84,    85,    86,   175,    96,    94,   188,    89,    42,   215,
     190,   202,    34,    35,    36,    37,    38,    39,    40,    41,
     -80,   123,    43,    44,    45,   194,   131,    83,    84,    85,
      86,   190,    33,   162,    87,   230,   150,   151,   152,   153,
     154,   155,   156,   157,   205,   206,   144,    42,    43,    44,
      45,   145,   146,   147,    34,    35,    36,    37,    38,    39,
      40,    41,    87,   190,    76,   148,    77,   164,    78,    87,
     171,   217,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   192,   172,   166,   225,   210,   160,   227,   214,    42,
      43,    44,    45,    62,   219,   218,   221,    56,   222,   233,
     220,   224,   226,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,   228,   232,    63,   198,   197,   117,   208,
      11,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   102,   204,     0,     0,     0,     0,     0,    11
};

static const yytype_int16 yycheck[] =
{
       2,     3,    33,     8,     8,    10,    38,     7,     9,    70,
      71,    72,    73,    74,    75,    76,    28,    78,     7,     9,
      21,   171,     9,    48,    24,    30,    31,     9,    89,    25,
      33,     8,    64,    94,    25,    60,     5,     8,   109,    21,
      64,     8,   192,     8,     8,     8,    64,    65,   109,    48,
      55,    63,   123,    58,    58,    59,     8,    59,    60,    61,
       5,     6,   123,    22,    66,    64,   137,    98,    58,    59,
       9,   132,    20,    74,   224,    64,   137,     7,    80,    82,
      83,    84,    85,    86,    74,     7,    68,    74,    90,   160,
     161,    68,    74,    38,     7,    64,    65,    68,     7,   160,
     161,    68,   173,    68,    68,    68,    58,    59,    58,    59,
      68,   142,   173,   174,    72,     7,     7,   178,     5,     7,
       7,    34,    35,    36,    73,    74,   157,    20,    68,     3,
       4,     5,     6,   135,     8,     7,   141,    23,    64,   200,
     171,   172,    29,    30,    31,    32,    33,    34,    35,    36,
      68,    21,    65,    66,    67,   158,    64,     3,     4,     5,
       6,   192,     7,    70,    38,   226,    50,    51,    52,    53,
      54,    55,    56,    57,   176,   177,     8,    64,    65,    66,
      67,     8,     8,     8,    29,    30,    31,    32,    33,    34,
      35,    36,    38,   224,    69,     8,    71,    68,    73,    38,
       7,   203,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     7,    50,    64,   216,     7,    58,   219,    24,    64,
      65,    66,    67,     0,     8,    49,    49,    64,    37,   231,
      65,     7,     7,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     8,     8,    12,   165,   164,    77,   178,
      27,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    71,   174,    -1,    -1,    -1,    -1,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    27,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,     9,    74,   122,   122,   122,
      25,    25,     5,     7,    29,    30,    31,    32,    33,    34,
      35,    36,    64,    65,    66,    67,    89,    98,    99,   100,
     106,   108,   109,   110,   119,    22,    64,    94,    20,    94,
      28,    63,     0,    77,     9,    94,    94,    99,   107,   108,
       7,     7,     7,     7,     7,     7,    69,    71,    73,    20,
      90,    91,    68,     3,     4,     5,     6,    38,    94,    23,
      94,   122,   122,   122,     7,   122,     8,     8,    68,    65,
     106,   121,   121,     5,    65,   106,   120,   120,   120,     7,
     106,   113,   114,   115,   116,   117,   106,    98,   106,    92,
      93,    94,   122,    21,    96,    97,    99,    99,    99,    99,
      99,    64,     7,    24,   106,   111,   112,    21,   122,   102,
     103,   106,     7,   108,     8,     8,     8,     8,     8,   113,
      50,    51,    52,    53,    54,    55,    56,    57,   118,     8,
      58,    59,    70,    72,    68,    38,    64,    95,   113,   101,
     106,     7,    50,    21,    68,   122,   113,     8,    68,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    94,   104,
     108,     8,     7,   108,    99,   113,   113,    93,    95,     8,
      68,   107,   108,   113,   112,   122,   122,    48,   103,   105,
       7,    48,    60,   107,    24,   106,     8,   122,    49,     8,
      65,    49,    37,     8,     7,   122,     7,   122,     8,   107,
     106,     8,     8,   122
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    78,    79,    80,    81,    81,
      82,    83,    84,    84,    85,    85,    86,    86,    87,    88,
      88,    89,    89,    90,    91,    92,    92,    93,    93,    93,
      94,    95,    96,    96,    97,    98,    98,    99,    99,    99,
      99,    99,    99,   100,   100,   100,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   108,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   113,   113,   113,   113,   114,   114,
     114,   115,   116,   117,   118,   118,   118,   118,   118,   118,
     119,   119,   119,   119,   119,   120,   120,   120,   121,   121,
     122,   122
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     7,     9,
       4,     4,     8,    11,     5,     7,     4,     6,     3,     3,
       3,     1,     1,     2,     2,     1,     3,     1,     2,     3,
       1,     1,     0,     1,     2,     1,     3,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       3,     2,     5,     2,     4,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     1,     4,     4,     3,
       1,     3,     1,     1,     1,     1,     1,     3,     4,     1,
       1,     1,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     3,     3,     5,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     4,     4,     1,     1,     1,     1,     1,
       1,     2
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
#line 144 "sql.y"
        {
            add_statement(states, (yyvsp[0].statement));
            (yyval.statements) = states;
        }
#line 1591 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 149 "sql.y"
        {
            add_statement((yyvsp[-1].statements), (yyvsp[0].statement));
            (yyval.statements) = (yyvsp[-1].statements);
        }
#line 1600 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 156 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1610 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 162 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1620 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 168 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1630 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 174 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1641 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 181 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1652 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 188 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1663 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 195 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1674 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 202 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1685 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 209 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1696 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 216 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1707 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 223 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1718 "y.tab.c"
    break;

  case 18: /* create_table_statement: CREATE TABLE table '(' column_defs ')' end  */
#line 241 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].s_value);
            create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1729 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table '(' column_defs ',' primary_key_statement ')' end  */
#line 248 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-6].s_value);
            create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
            create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
            (yyval.create_table_node) = create_table_node;
        }
#line 1741 "y.tab.c"
    break;

  case 20: /* drop_table_statement: DROP TABLE table end  */
#line 258 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].s_value);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1751 "y.tab.c"
    break;

  case 21: /* select_statement: SELECT selection table_exp end  */
#line 266 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1762 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table VALUES '(' value_items ')' end  */
#line 275 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-5].s_value);
            node->value_item_set_node = (yyvsp[-2].value_item_set_node);
            (yyval.insert_node) = node;
        }
#line 1774 "y.tab.c"
    break;

  case 23: /* insert_statement: INSERT INTO table '(' columns ')' VALUES '(' value_items ')' end  */
#line 283 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-8].s_value);
            node->columns_set_node = (yyvsp[-6].column_set_node);
            node->value_item_set_node = (yyvsp[-2].value_item_set_node);
            (yyval.insert_node) = node;
        }
#line 1787 "y.tab.c"
    break;

  case 24: /* update_statement: UPDATE table SET assignments end  */
#line 294 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-3].s_value);
            node->assignment_set_node = (yyvsp[-1].assignment_set_node);
            (yyval.update_node) = node;
        }
#line 1798 "y.tab.c"
    break;

  case 25: /* update_statement: UPDATE table SET assignments WHERE condition end  */
#line 301 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-5].s_value);
            node->assignment_set_node = (yyvsp[-3].assignment_set_node);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.update_node) = node;
        }
#line 1810 "y.tab.c"
    break;

  case 26: /* delete_statement: DELETE FROM table end  */
#line 311 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].s_value);
            (yyval.delete_node) = node;
        }
#line 1820 "y.tab.c"
    break;

  case 27: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 317 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].s_value);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1831 "y.tab.c"
    break;

  case 28: /* describe_statement: DESCRIBE table end  */
#line 326 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = db_strdup((yyvsp[-1].s_value));
            (yyval.describe_node) = node;
        }
#line 1841 "y.tab.c"
    break;

  case 29: /* show_statement: SHOW TABLES end  */
#line 334 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1849 "y.tab.c"
    break;

  case 30: /* show_statement: SHOW MEMORY end  */
#line 338 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1857 "y.tab.c"
    break;

  case 31: /* selection: scalar_exp_commalist  */
#line 344 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_set = (yyvsp[0].scalar_exp_set_node);
            (yyval.selection_node) = selection_node;
        }
#line 1868 "y.tab.c"
    break;

  case 32: /* selection: '*'  */
#line 351 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 1878 "y.tab.c"
    break;

  case 33: /* table_exp: from_clause opt_where_clause  */
#line 359 "sql.y"
        {
            TableExpNode *table_exp = make_table_exp_node();
            table_exp->from_clause = (yyvsp[-1].from_clause_node);
            table_exp->where_clause = (yyvsp[0].where_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 1889 "y.tab.c"
    break;

  case 34: /* from_clause: FROM table_ref_commalist  */
#line 368 "sql.y"
        {
            FromClauseNode *from_clause = make_from_clause_node();
            from_clause->from = (yyvsp[0].table_ref_set_node);
            (yyval.from_clause_node) = from_clause;
        }
#line 1899 "y.tab.c"
    break;

  case 35: /* table_ref_commalist: table_ref  */
#line 376 "sql.y"
        {
            TableRefSetNode *table_ref_set = make_table_ref_set_node();
            add_table_ref_to_set(table_ref_set, (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = table_ref_set;
        }
#line 1909 "y.tab.c"
    break;

  case 36: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 382 "sql.y"
        {
            add_table_ref_to_set((yyvsp[-2].table_ref_set_node), (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = (yyvsp[-2].table_ref_set_node);
        }
#line 1918 "y.tab.c"
    break;

  case 37: /* table_ref: table  */
#line 389 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[0].s_value);
            (yyval.table_ref_node) = table_ref;
        }
#line 1928 "y.tab.c"
    break;

  case 38: /* table_ref: table range_variable  */
#line 395 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-1].s_value);
            table_ref->range_variable = (yyvsp[0].s_value);
            (yyval.table_ref_node) = table_ref;
        }
#line 1939 "y.tab.c"
    break;

  case 39: /* table_ref: table AS range_variable  */
#line 402 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-2].s_value);
            table_ref->range_variable = (yyvsp[0].s_value);
            (yyval.table_ref_node) = table_ref;
        }
#line 1950 "y.tab.c"
    break;

  case 40: /* table: IDENTIFIER  */
#line 411 "sql.y"
        {
            (yyval.s_value) = (yyvsp[0].s_value);
        }
#line 1958 "y.tab.c"
    break;

  case 41: /* range_variable: IDENTIFIER  */
#line 417 "sql.y"
        {
            (yyval.s_value) = (yyvsp[0].s_value);
        }
#line 1966 "y.tab.c"
    break;

  case 42: /* opt_where_clause: %empty  */
#line 423 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 1974 "y.tab.c"
    break;

  case 43: /* opt_where_clause: where_clause  */
#line 427 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 1982 "y.tab.c"
    break;

  case 44: /* where_clause: WHERE condition  */
#line 433 "sql.y"
        {
            WhereClauseNode *where_clause_node = make_where_clause_node();
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 1992 "y.tab.c"
    break;

  case 45: /* scalar_exp_commalist: scalar_exp  */
#line 441 "sql.y"
        {
            ScalarExpSetNode *scalar_exp_set_node = make_scalar_exp_set_node();
            add_scalar_exp_node(scalar_exp_set_node, (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = scalar_exp_set_node;
        }
#line 2002 "y.tab.c"
    break;

  case 46: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 447 "sql.y"
        {
            add_scalar_exp_node((yyvsp[-2].scalar_exp_set_node), (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = (yyvsp[-2].scalar_exp_set_node);
        }
#line 2011 "y.tab.c"
    break;

  case 47: /* scalar_exp: calculate  */
#line 454 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2022 "y.tab.c"
    break;

  case 48: /* scalar_exp: column  */
#line 461 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2033 "y.tab.c"
    break;

  case 49: /* scalar_exp: function  */
#line 468 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2044 "y.tab.c"
    break;

  case 50: /* scalar_exp: value_item  */
#line 475 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2055 "y.tab.c"
    break;

  case 51: /* scalar_exp: '(' scalar_exp ')'  */
#line 482 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2063 "y.tab.c"
    break;

  case 52: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 486 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].s_value);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2072 "y.tab.c"
    break;

  case 53: /* calculate: scalar_exp '+' scalar_exp  */
#line 493 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2084 "y.tab.c"
    break;

  case 54: /* calculate: scalar_exp '-' scalar_exp  */
#line 501 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2096 "y.tab.c"
    break;

  case 55: /* calculate: scalar_exp '*' scalar_exp  */
#line 509 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2108 "y.tab.c"
    break;

  case 56: /* calculate: scalar_exp '/' scalar_exp  */
#line 517 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2120 "y.tab.c"
    break;

  case 57: /* columns: column  */
#line 527 "sql.y"
        {
            ColumnSetNode *column_set_node = make_column_set_node();
            add_column_to_set(column_set_node, (yyvsp[0].column_node));
            (yyval.column_set_node) = column_set_node;
        }
#line 2130 "y.tab.c"
    break;

  case 58: /* columns: columns ',' column  */
#line 533 "sql.y"
        {
            (yyval.column_set_node) = (yyvsp[-2].column_set_node);
            add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
        }
#line 2139 "y.tab.c"
    break;

  case 59: /* column_defs: column_def  */
#line 540 "sql.y"
        {
            ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
            add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
            (yyval.column_def_set_node) = column_def_set_node;
        }
#line 2149 "y.tab.c"
    break;

  case 60: /* column_defs: column_defs ',' column_def  */
#line 546 "sql.y"
        {
            (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
            add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
        }
#line 2158 "y.tab.c"
    break;

  case 61: /* column_def: column data_type  */
#line 553 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-1].column_node);
            column_def_node->data_type = (yyvsp[0].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = false;
            column_def_node->is_define_len = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2172 "y.tab.c"
    break;

  case 62: /* column_def: column STRING '(' INTVALUE ')'  */
#line 563 "sql.y"
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
#line 2187 "y.tab.c"
    break;

  case 63: /* column_def: column table  */
#line 574 "sql.y"
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
#line 2202 "y.tab.c"
    break;

  case 64: /* column_def: column data_type PRIMARY KEY  */
#line 585 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = true;
            column_def_node->allow_null = false;
            (yyval.column_def_node) = column_def_node;
        }
#line 2215 "y.tab.c"
    break;

  case 65: /* column_def: column data_type NOT NULLX  */
#line 594 "sql.y"
        {
            ColumnDefNode *column_def_node = make_column_def_node();
            column_def_node->column = (yyvsp[-3].column_node);
            column_def_node->data_type = (yyvsp[-2].data_type);
            column_def_node->is_primary = false;
            column_def_node->allow_null = true;
            (yyval.column_def_node) = column_def_node;
        }
#line 2228 "y.tab.c"
    break;

  case 66: /* data_type: INT  */
#line 604 "sql.y"
                 { (yyval.data_type) = T_INT; }
#line 2234 "y.tab.c"
    break;

  case 67: /* data_type: LONG  */
#line 605 "sql.y"
                 { (yyval.data_type) = T_LONG;  }
#line 2240 "y.tab.c"
    break;

  case 68: /* data_type: CHAR  */
#line 606 "sql.y"
                 { (yyval.data_type) = T_CHAR; }
#line 2246 "y.tab.c"
    break;

  case 69: /* data_type: STRING  */
#line 607 "sql.y"
                 { (yyval.data_type) = T_STRING; }
#line 2252 "y.tab.c"
    break;

  case 70: /* data_type: BOOL  */
#line 608 "sql.y"
                 { (yyval.data_type) = T_BOOL; }
#line 2258 "y.tab.c"
    break;

  case 71: /* data_type: FLOAT  */
#line 609 "sql.y"
                 { (yyval.data_type) = T_FLOAT; }
#line 2264 "y.tab.c"
    break;

  case 72: /* data_type: DOUBLE  */
#line 610 "sql.y"
                 { (yyval.data_type) = T_DOUBLE; }
#line 2270 "y.tab.c"
    break;

  case 73: /* data_type: TIMESTAMP  */
#line 611 "sql.y"
                 { (yyval.data_type) = T_TIMESTAMP; }
#line 2276 "y.tab.c"
    break;

  case 74: /* data_type: DATE  */
#line 612 "sql.y"
                 { (yyval.data_type) = T_DATE; }
#line 2282 "y.tab.c"
    break;

  case 75: /* primary_key_statement: PRIMARY KEY '(' column ')'  */
#line 616 "sql.y"
         {
             PrimaryKeyNode *primary_key_node = make_primary_key_node();
             primary_key_node->column = (yyvsp[-1].column_node);
             (yyval.primary_key_node) = primary_key_node;
         }
#line 2292 "y.tab.c"
    break;

  case 76: /* column: IDENTIFIER  */
#line 624 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[0].s_value));
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2303 "y.tab.c"
    break;

  case 77: /* column: IDENTIFIER '[' column ']'  */
#line 631 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-3].s_value));
            column_node->sub_column = (yyvsp[-1].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2315 "y.tab.c"
    break;

  case 78: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 639 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = db_strdup((yyvsp[-3].s_value));
            column_node->scalar_exp_set = (yyvsp[-1].scalar_exp_set_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2327 "y.tab.c"
    break;

  case 79: /* column: IDENTIFIER '.' column  */
#line 647 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = db_strdup((yyvsp[-2].s_value));
        }
#line 2336 "y.tab.c"
    break;

  case 80: /* value_items: value_item  */
#line 654 "sql.y"
        {
            ValueItemSetNode *node = make_value_item_set_node();
            add_value_item(node, (yyvsp[0].value_item_node));
            (yyval.value_item_set_node) = node;
        }
#line 2346 "y.tab.c"
    break;

  case 81: /* value_items: value_items ',' value_item  */
#line 660 "sql.y"
        {
            (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
            add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
        }
#line 2355 "y.tab.c"
    break;

  case 82: /* value_item: INTVALUE  */
#line 667 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.i_value = (yyvsp[0].i_value);
            node->data_type = T_INT;
            (yyval.value_item_node) = node;
        }
#line 2366 "y.tab.c"
    break;

  case 83: /* value_item: BOOLVALUE  */
#line 674 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.b_value = (yyvsp[0].b_value);
            node->data_type = T_BOOL;
            (yyval.value_item_node) = node;
        }
#line 2377 "y.tab.c"
    break;

  case 84: /* value_item: STRINGVALUE  */
#line 681 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.s_value = (yyvsp[0].s_value);
            node->data_type = T_STRING;
            (yyval.value_item_node) = node;
        }
#line 2388 "y.tab.c"
    break;

  case 85: /* value_item: FLOATVALUE  */
#line 688 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.f_value = (yyvsp[0].f_value);
            node->data_type = T_FLOAT;
            (yyval.value_item_node) = node;
        }
#line 2399 "y.tab.c"
    break;

  case 86: /* value_item: REFERVALUE  */
#line 695 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.r_value = (yyvsp[0].r_value);
            node->data_type = T_REFERENCE;
            (yyval.value_item_node) = node;
        }
#line 2410 "y.tab.c"
    break;

  case 87: /* REFERVALUE: '(' value_items ')'  */
#line 705 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_item_set = (yyvsp[-1].value_item_set_node);
            (yyval.r_value) = refer;
        }
#line 2421 "y.tab.c"
    break;

  case 88: /* REFERVALUE: REF '(' condition ')'  */
#line 713 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.r_value) = refer;
        }
#line 2432 "y.tab.c"
    break;

  case 89: /* BOOLVALUE: TRUE  */
#line 722 "sql.y"
        {
            (yyval.b_value) = true;
        }
#line 2440 "y.tab.c"
    break;

  case 90: /* BOOLVALUE: FALSE  */
#line 726 "sql.y"
        {
            (yyval.b_value) = false;
        }
#line 2448 "y.tab.c"
    break;

  case 91: /* assignments: assignment  */
#line 732 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2458 "y.tab.c"
    break;

  case 92: /* assignments: assignments ',' assignment  */
#line 738 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2467 "y.tab.c"
    break;

  case 93: /* assignment: column EQ value_item  */
#line 745 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2478 "y.tab.c"
    break;

  case 94: /* condition: condition OR condition  */
#line 754 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2490 "y.tab.c"
    break;

  case 95: /* condition: condition AND condition  */
#line 762 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2502 "y.tab.c"
    break;

  case 96: /* condition: '(' condition ')'  */
#line 770 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2510 "y.tab.c"
    break;

  case 97: /* condition: predicate  */
#line 774 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2521 "y.tab.c"
    break;

  case 98: /* predicate: comparison_predicate  */
#line 783 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2532 "y.tab.c"
    break;

  case 99: /* predicate: like_predicate  */
#line 790 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2543 "y.tab.c"
    break;

  case 100: /* predicate: in_predicate  */
#line 797 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 2554 "y.tab.c"
    break;

  case 101: /* comparison_predicate: column compare scalar_exp  */
#line 806 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 2566 "y.tab.c"
    break;

  case 102: /* like_predicate: column LIKE value_item  */
#line 816 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 2577 "y.tab.c"
    break;

  case 103: /* in_predicate: column IN '(' value_items ')'  */
#line 825 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_set = (yyvsp[-1].value_item_set_node);
            (yyval.in_node) = in_node;
        }
#line 2588 "y.tab.c"
    break;

  case 104: /* compare: EQ  */
#line 853 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 2594 "y.tab.c"
    break;

  case 105: /* compare: NE  */
#line 854 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 2600 "y.tab.c"
    break;

  case 106: /* compare: GT  */
#line 855 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 2606 "y.tab.c"
    break;

  case 107: /* compare: GE  */
#line 856 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 2612 "y.tab.c"
    break;

  case 108: /* compare: LT  */
#line 857 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 2618 "y.tab.c"
    break;

  case 109: /* compare: LE  */
#line 858 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 2624 "y.tab.c"
    break;

  case 110: /* function: MAX '(' non_all_function_value ')'  */
#line 862 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2635 "y.tab.c"
    break;

  case 111: /* function: MIN '(' non_all_function_value ')'  */
#line 869 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2646 "y.tab.c"
    break;

  case 112: /* function: COUNT '(' function_value ')'  */
#line 876 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2657 "y.tab.c"
    break;

  case 113: /* function: SUM '(' function_value ')'  */
#line 883 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2668 "y.tab.c"
    break;

  case 114: /* function: AVG '(' function_value ')'  */
#line 890 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2679 "y.tab.c"
    break;

  case 115: /* function_value: INTVALUE  */
#line 899 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].i_value);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2690 "y.tab.c"
    break;

  case 116: /* function_value: column  */
#line 906 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2701 "y.tab.c"
    break;

  case 117: /* function_value: '*'  */
#line 913 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 2711 "y.tab.c"
    break;

  case 118: /* non_all_function_value: INTVALUE  */
#line 921 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].i_value);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2722 "y.tab.c"
    break;

  case 119: /* non_all_function_value: column  */
#line 928 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2733 "y.tab.c"
    break;


#line 2737 "y.tab.c"

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

#line 939 "sql.y"

