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
    OR = 258,                      /* OR  */
    AND = 259,                     /* AND  */
    NL = 260,                      /* NL  */
    BEGINN = 261,                  /* BEGINN  */
    COMMIT = 262,                  /* COMMIT  */
    ROLLBACK = 263,                /* ROLLBACK  */
    CREATE = 264,                  /* CREATE  */
    DROP = 265,                    /* DROP  */
    SELECT = 266,                  /* SELECT  */
    INSERT = 267,                  /* INSERT  */
    UPDATE = 268,                  /* UPDATE  */
    DELETE = 269,                  /* DELETE  */
    DESCRIBE = 270,                /* DESCRIBE  */
    FROM = 271,                    /* FROM  */
    WHERE = 272,                   /* WHERE  */
    INTO = 273,                    /* INTO  */
    SET = 274,                     /* SET  */
    VALUES = 275,                  /* VALUES  */
    TABLE = 276,                   /* TABLE  */
    LIMIT = 277,                   /* LIMIT  */
    SHOW = 278,                    /* SHOW  */
    TABLES = 279,                  /* TABLES  */
    PRIMARY = 280,                 /* PRIMARY  */
    KEY = 281,                     /* KEY  */
    UNIQUE = 282,                  /* UNIQUE  */
    DEFAULT = 283,                 /* DEFAULT  */
    CHECK = 284,                   /* CHECK  */
    REFERENCES = 285,              /* REFERENCES  */
    FOREIGN = 286,                 /* FOREIGN  */
    MAX = 287,                     /* MAX  */
    MIN = 288,                     /* MIN  */
    COUNT = 289,                   /* COUNT  */
    SUM = 290,                     /* SUM  */
    AVG = 291,                     /* AVG  */
    REF = 292,                     /* REF  */
    TRUE = 293,                    /* TRUE  */
    FALSE = 294,                   /* FALSE  */
    NULLX = 295,                   /* NULLX  */
    AS = 296,                      /* AS  */
    CHAR = 297,                    /* CHAR  */
    INT = 298,                     /* INT  */
    LONG = 299,                    /* LONG  */
    VARCHAR = 300,                 /* VARCHAR  */
    STRING = 301,                  /* STRING  */
    BOOL = 302,                    /* BOOL  */
    FLOAT = 303,                   /* FLOAT  */
    DOUBLE = 304,                  /* DOUBLE  */
    DATE = 305,                    /* DATE  */
    TIMESTAMP = 306,               /* TIMESTAMP  */
    EQ = 307,                      /* EQ  */
    NE = 308,                      /* NE  */
    GT = 309,                      /* GT  */
    GE = 310,                      /* GE  */
    LT = 311,                      /* LT  */
    LE = 312,                      /* LE  */
    IN = 313,                      /* IN  */
    LIKE = 314,                    /* LIKE  */
    NOT = 315,                     /* NOT  */
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
#define OR 258
#define AND 259
#define NL 260
#define BEGINN 261
#define COMMIT 262
#define ROLLBACK 263
#define CREATE 264
#define DROP 265
#define SELECT 266
#define INSERT 267
#define UPDATE 268
#define DELETE 269
#define DESCRIBE 270
#define FROM 271
#define WHERE 272
#define INTO 273
#define SET 274
#define VALUES 275
#define TABLE 276
#define LIMIT 277
#define SHOW 278
#define TABLES 279
#define PRIMARY 280
#define KEY 281
#define UNIQUE 282
#define DEFAULT 283
#define CHECK 284
#define REFERENCES 285
#define FOREIGN 286
#define MAX 287
#define MIN 288
#define COUNT 289
#define SUM 290
#define AVG 291
#define REF 292
#define TRUE 293
#define FALSE 294
#define NULLX 295
#define AS 296
#define CHAR 297
#define INT 298
#define LONG 299
#define VARCHAR 300
#define STRING 301
#define BOOL 302
#define FLOAT 303
#define DOUBLE 304
#define DATE 305
#define TIMESTAMP 306
#define EQ 307
#define NE 308
#define GT 309
#define GE 310
#define LT 311
#define LE 312
#define IN 313
#define LIKE 314
#define NOT 315
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

   char                         *strVal;
   int64_t                      intVal;
   float                        floatVal;
   bool                         boolVal;
   char                         *keyword;
   ReferValue                   *referVal;
   CompareType                  compare_type;
   DataTypeNode                 *data_type_node;
   ColumnDefName                *column_def_name;
   ColumnDefNameCommalist       *column_def_name_commalist;
   ColumnDefNode                *column_def_node;
   ColumnDefSetNode             *column_def_set_node;
   BaseTableElementNode         *base_table_element;
   BaseTableElementCommalist    *base_table_element_commalist;
   ColumnDefOptNode             *column_def_opt;
   ColumnDefOptNodeList         *column_def_opt_list;
   TableContraintDefNode        *table_contraint_def;
   ColumnNode                   *column_node;
   ColumnSetNode                *column_set_node;
   ValueItemNode                *value_item_node;
   ValueItemSetNode             *value_item_set_node;
   SelectionNode                *selection_node;
   ScalarExpNode                *scalar_exp_node;
   ScalarExpSetNode             *scalar_exp_set_node;
   FunctionValueNode            *function_value_node;
   FunctionNode                 *function_node;
   CalculateNode                *calculate_node;
   AssignmentNode               *assignment_node;
   AssignmentSetNode            *assignment_set_node;
   ConditionNode                *condition_node;
   PredicateNode                *predicate_node;
   ComparisonNode               *comparison_node;
   LikeNode                     *like_node;
   InNode                       *in_node;
   LimitNode                    *limit_node;
   TableRefNode                 *table_ref_node;
   TableRefSetNode              *table_ref_set_node;
   QuerySpecNode                *query_spec_node;
   ValuesOrQuerySpecNode        *values_or_query_spec_node;
   FromClauseNode               *from_clause_node;
   WhereClauseNode              *where_clause_node;
   TableExpNode                 *table_exp_node; 
   CreateTableNode              *create_table_node;
   DropTableNode                *drop_table_node;
   SelectNode                   *select_node;
   InsertNode                   *insert_node;
   UpdateNode                   *update_node;
   DeleteNode                   *delete_node;
   DescribeNode                 *describe_node;
   ShowNode                     *show_node;
   Statement                    *statement;
   Statements                   *statements;

#line 328 "y.tab.c"

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
  YYSYMBOL_OR = 3,                         /* OR  */
  YYSYMBOL_AND = 4,                        /* AND  */
  YYSYMBOL_5_ = 5,                         /* '+'  */
  YYSYMBOL_6_ = 6,                         /* '-'  */
  YYSYMBOL_7_ = 7,                         /* '*'  */
  YYSYMBOL_8_ = 8,                         /* '/'  */
  YYSYMBOL_9_ = 9,                         /* '('  */
  YYSYMBOL_10_ = 10,                       /* ')'  */
  YYSYMBOL_NL = 11,                        /* NL  */
  YYSYMBOL_BEGINN = 12,                    /* BEGINN  */
  YYSYMBOL_COMMIT = 13,                    /* COMMIT  */
  YYSYMBOL_ROLLBACK = 14,                  /* ROLLBACK  */
  YYSYMBOL_CREATE = 15,                    /* CREATE  */
  YYSYMBOL_DROP = 16,                      /* DROP  */
  YYSYMBOL_SELECT = 17,                    /* SELECT  */
  YYSYMBOL_INSERT = 18,                    /* INSERT  */
  YYSYMBOL_UPDATE = 19,                    /* UPDATE  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 21,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 22,                      /* FROM  */
  YYSYMBOL_WHERE = 23,                     /* WHERE  */
  YYSYMBOL_INTO = 24,                      /* INTO  */
  YYSYMBOL_SET = 25,                       /* SET  */
  YYSYMBOL_VALUES = 26,                    /* VALUES  */
  YYSYMBOL_TABLE = 27,                     /* TABLE  */
  YYSYMBOL_LIMIT = 28,                     /* LIMIT  */
  YYSYMBOL_SHOW = 29,                      /* SHOW  */
  YYSYMBOL_TABLES = 30,                    /* TABLES  */
  YYSYMBOL_PRIMARY = 31,                   /* PRIMARY  */
  YYSYMBOL_KEY = 32,                       /* KEY  */
  YYSYMBOL_UNIQUE = 33,                    /* UNIQUE  */
  YYSYMBOL_DEFAULT = 34,                   /* DEFAULT  */
  YYSYMBOL_CHECK = 35,                     /* CHECK  */
  YYSYMBOL_REFERENCES = 36,                /* REFERENCES  */
  YYSYMBOL_FOREIGN = 37,                   /* FOREIGN  */
  YYSYMBOL_MAX = 38,                       /* MAX  */
  YYSYMBOL_MIN = 39,                       /* MIN  */
  YYSYMBOL_COUNT = 40,                     /* COUNT  */
  YYSYMBOL_SUM = 41,                       /* SUM  */
  YYSYMBOL_AVG = 42,                       /* AVG  */
  YYSYMBOL_REF = 43,                       /* REF  */
  YYSYMBOL_TRUE = 44,                      /* TRUE  */
  YYSYMBOL_FALSE = 45,                     /* FALSE  */
  YYSYMBOL_NULLX = 46,                     /* NULLX  */
  YYSYMBOL_AS = 47,                        /* AS  */
  YYSYMBOL_CHAR = 48,                      /* CHAR  */
  YYSYMBOL_INT = 49,                       /* INT  */
  YYSYMBOL_LONG = 50,                      /* LONG  */
  YYSYMBOL_VARCHAR = 51,                   /* VARCHAR  */
  YYSYMBOL_STRING = 52,                    /* STRING  */
  YYSYMBOL_BOOL = 53,                      /* BOOL  */
  YYSYMBOL_FLOAT = 54,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 55,                    /* DOUBLE  */
  YYSYMBOL_DATE = 56,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 57,                 /* TIMESTAMP  */
  YYSYMBOL_EQ = 58,                        /* EQ  */
  YYSYMBOL_NE = 59,                        /* NE  */
  YYSYMBOL_GT = 60,                        /* GT  */
  YYSYMBOL_GE = 61,                        /* GE  */
  YYSYMBOL_LT = 62,                        /* LT  */
  YYSYMBOL_LE = 63,                        /* LE  */
  YYSYMBOL_IN = 64,                        /* IN  */
  YYSYMBOL_LIKE = 65,                      /* LIKE  */
  YYSYMBOL_NOT = 66,                       /* NOT  */
  YYSYMBOL_SYSTEM = 67,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 68,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 69,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 70,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 71,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 72,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 73,               /* STRINGVALUE  */
  YYSYMBOL_74_ = 74,                       /* ','  */
  YYSYMBOL_75_ = 75,                       /* '['  */
  YYSYMBOL_76_ = 76,                       /* ']'  */
  YYSYMBOL_77_ = 77,                       /* '{'  */
  YYSYMBOL_78_ = 78,                       /* '}'  */
  YYSYMBOL_79_ = 79,                       /* '.'  */
  YYSYMBOL_80_ = 80,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_statements = 82,                /* statements  */
  YYSYMBOL_statement = 83,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 84, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 85, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 86, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 87,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 88,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 89,          /* select_statement  */
  YYSYMBOL_insert_statement = 90,          /* insert_statement  */
  YYSYMBOL_update_statement = 91,          /* update_statement  */
  YYSYMBOL_delete_statement = 92,          /* delete_statement  */
  YYSYMBOL_describe_statement = 93,        /* describe_statement  */
  YYSYMBOL_show_statement = 94,            /* show_statement  */
  YYSYMBOL_selection = 95,                 /* selection  */
  YYSYMBOL_table_exp = 96,                 /* table_exp  */
  YYSYMBOL_from_clause = 97,               /* from_clause  */
  YYSYMBOL_table_ref_commalist = 98,       /* table_ref_commalist  */
  YYSYMBOL_table_ref = 99,                 /* table_ref  */
  YYSYMBOL_table = 100,                    /* table  */
  YYSYMBOL_range_variable = 101,           /* range_variable  */
  YYSYMBOL_opt_where_clause = 102,         /* opt_where_clause  */
  YYSYMBOL_where_clause = 103,             /* where_clause  */
  YYSYMBOL_values_or_query_spec = 104,     /* values_or_query_spec  */
  YYSYMBOL_query_spec = 105,               /* query_spec  */
  YYSYMBOL_scalar_exp_commalist = 106,     /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 107,               /* scalar_exp  */
  YYSYMBOL_calculate = 108,                /* calculate  */
  YYSYMBOL_columns = 109,                  /* columns  */
  YYSYMBOL_base_table_element_commalist = 110, /* base_table_element_commalist  */
  YYSYMBOL_base_table_element = 111,       /* base_table_element  */
  YYSYMBOL_column_def = 112,               /* column_def  */
  YYSYMBOL_column_def_name_commalist = 113, /* column_def_name_commalist  */
  YYSYMBOL_column_def_name = 114,          /* column_def_name  */
  YYSYMBOL_data_type = 115,                /* data_type  */
  YYSYMBOL_array_dim_clause = 116,         /* array_dim_clause  */
  YYSYMBOL_column_def_opt_list = 117,      /* column_def_opt_list  */
  YYSYMBOL_column_def_opt = 118,           /* column_def_opt  */
  YYSYMBOL_table_contraint_def = 119,      /* table_contraint_def  */
  YYSYMBOL_column = 120,                   /* column  */
  YYSYMBOL_value_items = 121,              /* value_items  */
  YYSYMBOL_value_item = 122,               /* value_item  */
  YYSYMBOL_REFERVALUE = 123,               /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 124,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 125,              /* assignments  */
  YYSYMBOL_assignment = 126,               /* assignment  */
  YYSYMBOL_condition = 127,                /* condition  */
  YYSYMBOL_predicate = 128,                /* predicate  */
  YYSYMBOL_comparison_predicate = 129,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 130,           /* like_predicate  */
  YYSYMBOL_in_predicate = 131,             /* in_predicate  */
  YYSYMBOL_compare = 132,                  /* compare  */
  YYSYMBOL_function = 133,                 /* function  */
  YYSYMBOL_function_value = 134,           /* function_value  */
  YYSYMBOL_non_all_function_value = 135,   /* non_all_function_value  */
  YYSYMBOL_end = 136                       /* end  */
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
#define YYLAST   311

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

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
       9,    10,     7,     5,    74,     6,    79,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    80,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    75,     2,    76,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    77,     2,    78,     2,     2,     2,     2,
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
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   166,   173,   179,   185,   191,   198,   205,
     212,   219,   226,   233,   240,   249,   252,   255,   259,   269,
     278,   288,   296,   308,   319,   325,   335,   344,   348,   354,
     361,   369,   379,   382,   390,   396,   403,   409,   416,   425,
     431,   438,   441,   447,   455,   462,   471,   480,   486,   493,
     500,   507,   514,   521,   525,   532,   540,   548,   556,   566,
     572,   579,   585,   592,   599,   621,   632,   638,   645,   653,
     658,   663,   668,   674,   679,   684,   689,   694,   699,   704,
     713,   716,   720,   727,   730,   735,   742,   747,   752,   757,
     763,   768,   774,   782,   788,   794,   801,   809,   816,   824,
     832,   839,   845,   852,   859,   866,   873,   880,   890,   898,
     907,   911,   917,   923,   930,   939,   947,   955,   959,   968,
     975,   982,   991,  1001,  1010,  1039,  1040,  1041,  1042,  1043,
    1044,  1047,  1054,  1061,  1068,  1075,  1084,  1091,  1098,  1106,
    1113,  1122,  1123
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
  "\"end of file\"", "error", "\"invalid token\"", "OR", "AND", "'+'",
  "'-'", "'*'", "'/'", "'('", "')'", "NL", "BEGINN", "COMMIT", "ROLLBACK",
  "CREATE", "DROP", "SELECT", "INSERT", "UPDATE", "DELETE", "DESCRIBE",
  "FROM", "WHERE", "INTO", "SET", "VALUES", "TABLE", "LIMIT", "SHOW",
  "TABLES", "PRIMARY", "KEY", "UNIQUE", "DEFAULT", "CHECK", "REFERENCES",
  "FOREIGN", "MAX", "MIN", "COUNT", "SUM", "AVG", "REF", "TRUE", "FALSE",
  "NULLX", "AS", "CHAR", "INT", "LONG", "VARCHAR", "STRING", "BOOL",
  "FLOAT", "DOUBLE", "DATE", "TIMESTAMP", "EQ", "NE", "GT", "GE", "LT",
  "LE", "IN", "LIKE", "NOT", "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER",
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
  "base_table_element_commalist", "base_table_element", "column_def",
  "column_def_name_commalist", "column_def_name", "data_type",
  "array_dim_clause", "column_def_opt_list", "column_def_opt",
  "table_contraint_def", "column", "value_items", "value_item",
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

#define YYPACT_NINF (-183)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-102)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     258,    -4,    -4,    -4,   -18,    13,    44,    46,     9,    75,
       9,     2,   229,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,   111,  -183,  -183,  -183,
       9,     9,  -183,   119,   104,   115,   125,   140,   156,   169,
    -183,  -183,    62,  -183,  -183,  -183,   133,    98,   178,  -183,
    -183,  -183,  -183,  -183,  -183,     9,  -183,   172,     9,    -4,
      -4,    -4,  -183,  -183,  -183,   186,    -4,   161,    18,   137,
      73,    73,    23,    23,    23,    -1,   129,   119,   129,     9,
      -4,   184,   119,   119,   119,   119,   119,   143,    95,   129,
      10,  -183,  -183,  -183,   163,  -183,  -183,  -183,    30,  -183,
    -183,   205,   209,  -183,  -183,  -183,   210,   216,   217,    -1,
     230,   123,  -183,  -183,  -183,  -183,   152,   -40,  -183,   157,
    -183,    48,  -183,    -1,  -183,  -183,   178,    17,    17,   183,
     183,  -183,   129,    44,   223,    -4,  -183,   176,    45,  -183,
      -1,  -183,   207,   228,   242,   220,  -183,    25,  -183,  -183,
     212,  -183,    30,  -183,  -183,  -183,  -183,  -183,  -183,   128,
    -183,  -183,  -183,  -183,  -183,  -183,   244,    30,   119,    -1,
      -1,  -183,  -183,  -183,     9,   168,  -183,  -183,   150,    26,
    -183,   133,    30,  -183,    30,   129,    -4,    16,   245,   185,
      -1,   247,    -4,   163,  -183,  -183,  -183,   248,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,   208,  -183,  -183,    30,  -183,
     178,   276,  -183,  -183,  -183,    20,   129,  -183,    32,  -183,
    -183,  -183,  -183,   185,    33,  -183,   206,   185,  -183,  -183,
     213,   221,   146,    34,    -4,  -183,  -183,    49,  -183,   185,
    -183,    55,   271,  -183,   253,  -183,   102,   277,     9,   250,
     222,   170,  -183,  -183,  -183,  -183,  -183,   263,  -183,  -183,
    -183,  -183,    -1,  -183,  -183,  -183,  -183,     9,   214,  -183,
    -183
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   141,     0,    15,    16,    17,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
     110,   111,    97,   103,   106,   105,    32,    29,    47,    49,
      50,    52,   107,   104,    51,     0,    39,     0,     0,     0,
       0,     0,     1,     3,   142,     0,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    27,    28,     0,    19,    53,   108,     0,   139,
     140,     0,     0,   138,   136,   137,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,     0,     0,   100,    33,
      34,    36,    20,     0,    31,    42,    48,    55,    56,    57,
      58,    54,     0,     0,     0,     0,    45,     0,    41,   112,
       0,    24,     0,     0,     0,     0,    68,     0,    61,    63,
       0,    64,     0,   102,   131,   132,   133,   134,   135,     0,
     125,   126,   127,   128,   129,   130,     0,     0,     0,     0,
       0,   109,    98,    99,     0,     0,    40,    37,    43,     0,
      59,    32,     0,    21,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,    69,    70,     0,    73,    74,
      75,    76,    78,    77,    79,    80,   101,   117,     0,   123,
     122,   115,   116,    35,    38,     0,     0,    46,     0,   114,
     113,    23,    25,     0,     0,    66,     0,     0,    18,    62,
       0,     0,    83,     0,     0,    60,    44,     0,    93,     0,
      96,     0,     0,    81,     0,    87,     0,     0,     0,     0,
       0,    65,    84,   124,    22,    94,    67,     0,    72,    88,
      90,    89,     0,    92,    86,    82,    85,     0,     0,    95,
      91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,   288,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,   171,   120,  -183,  -183,   131,    -8,
     127,   165,  -183,    91,  -183,   231,   -28,  -183,  -183,  -183,
     114,  -183,  -182,   -88,  -183,  -183,  -183,    58,  -183,   -60,
    -156,   -32,  -183,  -183,  -183,   126,   -92,  -183,  -183,  -183,
    -183,  -183,  -183,   149,   239,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    46,    80,    81,   119,   120,   121,
     177,   124,   125,   135,   136,    47,    48,    49,   179,   147,
     148,   149,   224,   225,   205,   232,   251,   252,   151,    50,
      68,    51,    52,    53,   138,   139,   111,   112,   113,   114,
     115,   168,    54,   106,   101,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    69,    59,    28,    29,    67,   150,    25,   109,    30,
     100,   100,   105,   105,   105,   110,   116,   159,   118,   169,
     170,    25,    65,    66,    85,    86,   218,    25,    97,   137,
     103,   178,    60,   140,    82,   192,   215,   133,   173,   152,
      31,   237,   236,   238,   253,   241,   134,    88,   187,   110,
      90,    32,   233,    33,   126,   127,   128,   129,   130,   255,
      91,    92,    93,   110,    87,   257,   153,    95,   123,    42,
      55,    61,   180,    39,    40,    41,    26,   211,   212,    56,
     110,   122,    34,    35,    36,    37,    38,    39,    40,    41,
      26,   141,    98,    42,   104,   175,    26,    58,   226,   193,
     216,    43,    44,    45,   132,   150,    98,   239,    98,   110,
     110,   152,   133,    70,    42,    43,    44,    45,   176,   185,
     206,   134,    64,   239,    71,   137,   169,   170,    33,   239,
     110,   169,   170,   171,    72,   209,   183,    76,   207,    77,
     210,    78,   204,    42,    99,    39,    40,    41,   260,    73,
     206,   256,   219,   169,   170,    79,   235,    34,    35,    36,
      37,    38,    39,    40,    41,    74,    83,    84,    85,    86,
     268,    96,    82,    43,    44,    45,   206,   244,    75,   245,
     246,   247,   248,    83,    84,    85,    86,   221,   222,    42,
      43,    44,    45,   228,   142,    94,   143,    89,   144,    42,
     145,   244,   110,   245,   246,   247,   248,   123,    87,   169,
     170,  -101,   249,   131,   261,   154,   240,   169,   170,   155,
     156,   250,   107,   108,   270,    87,   157,   158,   172,    62,
      87,   174,   182,   146,   184,   254,   249,   189,   176,   188,
     263,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,   190,   191,   208,   223,   146,   227,   230,    11,   269,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     170,   258,    56,   231,   242,   259,   262,    11,   160,   161,
     162,   163,   164,   165,   166,   167,   264,   243,   265,   267,
      63,   217,   214,   186,   181,   213,   234,   229,   117,   266,
     102,   220
};

static const yytype_int16 yycheck[] =
{
       8,    33,    10,     2,     3,    33,    94,    11,     9,    27,
      70,    71,    72,    73,    74,    75,    76,   109,    78,     3,
       4,    11,    30,    31,     7,     8,   182,    11,    10,    89,
       7,   123,    30,    23,    74,    10,    10,    17,    78,     9,
      27,   223,    10,    10,    10,   227,    26,    55,   140,   109,
      58,     7,   208,     9,    82,    83,    84,    85,    86,    10,
      59,    60,    61,   123,    47,    10,    98,    66,    23,    70,
      24,    69,   132,    43,    44,    45,    80,   169,   170,    70,
     140,    80,    38,    39,    40,    41,    42,    43,    44,    45,
      80,    90,    74,    70,    71,    47,    80,    22,   190,    74,
      74,    71,    72,    73,     9,   193,    74,    74,    74,   169,
     170,     9,    17,     9,    70,    71,    72,    73,    70,    74,
     152,    26,    11,    74,     9,   185,     3,     4,     9,    74,
     190,     3,     4,    10,     9,   167,   135,    75,    10,    77,
     168,    79,   150,    70,    71,    43,    44,    45,    46,     9,
     182,   239,   184,     3,     4,    22,   216,    38,    39,    40,
      41,    42,    43,    44,    45,     9,     5,     6,     7,     8,
     262,    10,    74,    71,    72,    73,   208,    31,     9,    33,
      34,    35,    36,     5,     6,     7,     8,   186,   187,    70,
      71,    72,    73,   192,    31,     9,    33,    25,    35,    70,
      37,    31,   262,    33,    34,    35,    36,    23,    47,     3,
       4,    74,    66,    70,   246,    10,    10,     3,     4,    10,
      10,    75,    73,    74,    10,    47,    10,    10,    76,     0,
      47,    74,     9,    70,    58,   234,    66,     9,    70,    32,
     248,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     9,    32,     9,     9,    70,     9,     9,    29,   267,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       4,    10,    70,    75,    71,    32,     9,    29,    58,    59,
      60,    61,    62,    63,    64,    65,    46,    76,    76,    36,
      12,   181,   175,   138,   133,   174,   215,   193,    77,   251,
      71,   185
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    29,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    11,    80,   136,   136,   136,
      27,    27,     7,     9,    38,    39,    40,    41,    42,    43,
      44,    45,    70,    71,    72,    73,    95,   106,   107,   108,
     120,   122,   123,   124,   133,    24,    70,   100,    22,   100,
      30,    69,     0,    83,    11,   100,   100,   107,   121,   122,
       9,     9,     9,     9,     9,     9,    75,    77,    79,    22,
      96,    97,    74,     5,     6,     7,     8,    47,   100,    25,
     100,   136,   136,   136,     9,   136,    10,    10,    74,    71,
     120,   135,   135,     7,    71,   120,   134,   134,   134,     9,
     120,   127,   128,   129,   130,   131,   120,   106,   120,    98,
      99,   100,   136,    23,   102,   103,   107,   107,   107,   107,
     107,    70,     9,    17,    26,   104,   105,   120,   125,   126,
      23,   136,    31,    33,    35,    37,    70,   110,   111,   112,
     114,   119,     9,   122,    10,    10,    10,    10,    10,   127,
      58,    59,    60,    61,    62,    63,    64,    65,   132,     3,
       4,    10,    76,    78,    74,    47,    70,   101,   127,   109,
     120,    95,     9,   136,    58,    74,   102,   127,    32,     9,
       9,    32,    10,    74,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,   100,   115,   122,    10,     9,   122,
     107,   127,   127,    99,   101,    10,    74,    96,   121,   122,
     126,   136,   136,     9,   113,   114,   127,     9,   136,   111,
       9,    75,   116,   121,   104,   120,    10,   113,    10,    74,
      10,   113,    71,    76,    31,    33,    34,    35,    36,    66,
      75,   117,   118,    10,   136,    10,   114,    10,    10,    32,
      46,   122,     9,   100,    46,    76,   118,    36,   127,   100,
      10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    88,
      89,    90,    90,    91,    92,    92,    93,    94,    94,    95,
      95,    96,    97,    97,    98,    98,    99,    99,    99,   100,
     101,   102,   102,   103,   104,   104,   105,   106,   106,   107,
     107,   107,   107,   107,   107,   108,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   113,   113,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   117,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   120,   120,   120,
     120,   121,   121,   122,   122,   122,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   127,   127,   127,   127,   128,
     128,   128,   129,   130,   131,   132,   132,   132,   132,   132,
     132,   133,   133,   133,   133,   133,   134,   134,   134,   135,
     135,   136,   136
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     7,     4,
       4,     5,     8,     6,     4,     6,     3,     3,     3,     1,
       1,     2,     0,     2,     1,     3,     1,     2,     3,     1,
       1,     0,     1,     2,     4,     1,     3,     1,     3,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     3,     1,     1,     4,     1,     3,     1,     1,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     3,     0,     1,     2,     2,     1,     2,     2,
       2,     4,     2,     4,     5,     7,     4,     1,     4,     4,
       3,     1,     3,     1,     1,     1,     1,     1,     3,     4,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     3,     3,     5,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     1,     2
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
#line 162 "sql.y"
        {
            add_statement(states, (yyvsp[0].statement));
            (yyval.statements) = states;
        }
#line 1660 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 167 "sql.y"
        {
            add_statement((yyvsp[-1].statements), (yyvsp[0].statement));
            (yyval.statements) = (yyvsp[-1].statements);
        }
#line 1669 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 174 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1679 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 180 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1689 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 186 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1699 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 192 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1710 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 199 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1721 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 206 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1732 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 213 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1743 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 220 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1754 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 227 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1765 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 234 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1776 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 241 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1787 "y.tab.c"
    break;

  case 18: /* create_table_statement: CREATE TABLE table '(' base_table_element_commalist ')' end  */
#line 260 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].strVal);
            create_table_node->base_table_element_commalist = (yyvsp[-2].base_table_element_commalist);
            (yyval.create_table_node) = create_table_node;
        }
#line 1798 "y.tab.c"
    break;

  case 19: /* drop_table_statement: DROP TABLE table end  */
#line 270 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].strVal);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1808 "y.tab.c"
    break;

  case 20: /* select_statement: SELECT selection table_exp end  */
#line 279 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1819 "y.tab.c"
    break;

  case 21: /* insert_statement: INSERT INTO table values_or_query_spec end  */
#line 289 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-2].strVal);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1831 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table '(' columns ')' values_or_query_spec end  */
#line 297 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-5].strVal);
            node->columns_set_node = (yyvsp[-3].column_set_node);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1844 "y.tab.c"
    break;

  case 23: /* update_statement: UPDATE table SET assignments opt_where_clause end  */
#line 309 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-4].strVal);
            node->assignment_set_node = (yyvsp[-2].assignment_set_node);
            node->where_clause = (yyvsp[-1].where_clause_node);
            (yyval.update_node) = node;
        }
#line 1856 "y.tab.c"
    break;

  case 24: /* delete_statement: DELETE FROM table end  */
#line 320 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.delete_node) = node;
        }
#line 1866 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 326 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].strVal);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1877 "y.tab.c"
    break;

  case 26: /* describe_statement: DESCRIBE table end  */
#line 336 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.describe_node) = node;
        }
#line 1887 "y.tab.c"
    break;

  case 27: /* show_statement: SHOW TABLES end  */
#line 345 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1895 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW MEMORY end  */
#line 349 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1903 "y.tab.c"
    break;

  case 29: /* selection: scalar_exp_commalist  */
#line 355 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_set = (yyvsp[0].scalar_exp_set_node);
            (yyval.selection_node) = selection_node;
        }
#line 1914 "y.tab.c"
    break;

  case 30: /* selection: '*'  */
#line 362 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 1924 "y.tab.c"
    break;

  case 31: /* table_exp: from_clause opt_where_clause  */
#line 370 "sql.y"
        {
            TableExpNode *table_exp = make_table_exp_node();
            table_exp->from_clause = (yyvsp[-1].from_clause_node);
            table_exp->where_clause = (yyvsp[0].where_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 1935 "y.tab.c"
    break;

  case 32: /* from_clause: %empty  */
#line 379 "sql.y"
        {
            (yyval.from_clause_node) = NULL;
        }
#line 1943 "y.tab.c"
    break;

  case 33: /* from_clause: FROM table_ref_commalist  */
#line 383 "sql.y"
        {
            FromClauseNode *from_clause = make_from_clause_node();
            from_clause->from = (yyvsp[0].table_ref_set_node);
            (yyval.from_clause_node) = from_clause;
        }
#line 1953 "y.tab.c"
    break;

  case 34: /* table_ref_commalist: table_ref  */
#line 391 "sql.y"
        {
            TableRefSetNode *table_ref_set = make_table_ref_set_node();
            add_table_ref_to_set(table_ref_set, (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = table_ref_set;
        }
#line 1963 "y.tab.c"
    break;

  case 35: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 397 "sql.y"
        {
            add_table_ref_to_set((yyvsp[-2].table_ref_set_node), (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = (yyvsp[-2].table_ref_set_node);
        }
#line 1972 "y.tab.c"
    break;

  case 36: /* table_ref: table  */
#line 404 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 1982 "y.tab.c"
    break;

  case 37: /* table_ref: table range_variable  */
#line 410 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-1].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 1993 "y.tab.c"
    break;

  case 38: /* table_ref: table AS range_variable  */
#line 417 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-2].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2004 "y.tab.c"
    break;

  case 39: /* table: IDENTIFIER  */
#line 426 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2012 "y.tab.c"
    break;

  case 40: /* range_variable: IDENTIFIER  */
#line 432 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2020 "y.tab.c"
    break;

  case 41: /* opt_where_clause: %empty  */
#line 438 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 2028 "y.tab.c"
    break;

  case 42: /* opt_where_clause: where_clause  */
#line 442 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 2036 "y.tab.c"
    break;

  case 43: /* where_clause: WHERE condition  */
#line 448 "sql.y"
        {
            WhereClauseNode *where_clause_node = make_where_clause_node();
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 2046 "y.tab.c"
    break;

  case 44: /* values_or_query_spec: VALUES '(' value_items ')'  */
#line 456 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = (yyvsp[-1].value_item_set_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2057 "y.tab.c"
    break;

  case 45: /* values_or_query_spec: query_spec  */
#line 463 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = (yyvsp[0].query_spec_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2068 "y.tab.c"
    break;

  case 46: /* query_spec: SELECT selection table_exp  */
#line 472 "sql.y"
        {
            QuerySpecNode *query_spec = make_query_spec_node();
            query_spec->selection = (yyvsp[-1].selection_node);
            query_spec->table_exp = (yyvsp[0].table_exp_node);
            (yyval.query_spec_node) = query_spec;
        }
#line 2079 "y.tab.c"
    break;

  case 47: /* scalar_exp_commalist: scalar_exp  */
#line 481 "sql.y"
        {
            ScalarExpSetNode *scalar_exp_set_node = make_scalar_exp_set_node();
            add_scalar_exp_node(scalar_exp_set_node, (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = scalar_exp_set_node;
        }
#line 2089 "y.tab.c"
    break;

  case 48: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 487 "sql.y"
        {
            add_scalar_exp_node((yyvsp[-2].scalar_exp_set_node), (yyvsp[0].scalar_exp_node));
            (yyval.scalar_exp_set_node) = (yyvsp[-2].scalar_exp_set_node);
        }
#line 2098 "y.tab.c"
    break;

  case 49: /* scalar_exp: calculate  */
#line 494 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2109 "y.tab.c"
    break;

  case 50: /* scalar_exp: column  */
#line 501 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2120 "y.tab.c"
    break;

  case 51: /* scalar_exp: function  */
#line 508 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2131 "y.tab.c"
    break;

  case 52: /* scalar_exp: value_item  */
#line 515 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2142 "y.tab.c"
    break;

  case 53: /* scalar_exp: '(' scalar_exp ')'  */
#line 522 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2150 "y.tab.c"
    break;

  case 54: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 526 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].strVal);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2159 "y.tab.c"
    break;

  case 55: /* calculate: scalar_exp '+' scalar_exp  */
#line 533 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2171 "y.tab.c"
    break;

  case 56: /* calculate: scalar_exp '-' scalar_exp  */
#line 541 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2183 "y.tab.c"
    break;

  case 57: /* calculate: scalar_exp '*' scalar_exp  */
#line 549 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2195 "y.tab.c"
    break;

  case 58: /* calculate: scalar_exp '/' scalar_exp  */
#line 557 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2207 "y.tab.c"
    break;

  case 59: /* columns: column  */
#line 567 "sql.y"
        {
            ColumnSetNode *column_set_node = make_column_set_node();
            add_column_to_set(column_set_node, (yyvsp[0].column_node));
            (yyval.column_set_node) = column_set_node;
        }
#line 2217 "y.tab.c"
    break;

  case 60: /* columns: columns ',' column  */
#line 573 "sql.y"
        {
            (yyval.column_set_node) = (yyvsp[-2].column_set_node);
            add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
        }
#line 2226 "y.tab.c"
    break;

  case 61: /* base_table_element_commalist: base_table_element  */
#line 580 "sql.y"
        {
            BaseTableElementCommalist *base_table_element_commalist = make_base_table_element_commalist();
            add_base_table_element_to_set(base_table_element_commalist, (yyvsp[0].base_table_element));
            (yyval.base_table_element_commalist) = base_table_element_commalist;
        }
#line 2236 "y.tab.c"
    break;

  case 62: /* base_table_element_commalist: base_table_element_commalist ',' base_table_element  */
#line 586 "sql.y"
        {
            add_base_table_element_to_set((yyvsp[-2].base_table_element_commalist), (yyvsp[0].base_table_element));
            (yyval.base_table_element_commalist) = (yyvsp[-2].base_table_element_commalist);
        }
#line 2245 "y.tab.c"
    break;

  case 63: /* base_table_element: column_def  */
#line 593 "sql.y"
        {
            (yyval.base_table_element) = make_base_table_element_node();
            (yyval.base_table_element)->column_def = (yyvsp[0].column_def_node);
            (yyval.base_table_element)->table_contraint_def = NULL;
            (yyval.base_table_element)->type = TELE_COLUMN_DEF;
        }
#line 2256 "y.tab.c"
    break;

  case 64: /* base_table_element: table_contraint_def  */
#line 600 "sql.y"
        {
            (yyval.base_table_element) = make_base_table_element_node();
            (yyval.base_table_element)->column_def = NULL;
            (yyval.base_table_element)->table_contraint_def = (yyvsp[0].table_contraint_def);
            (yyval.base_table_element)->type = TELE_TABLE_CONTRAINT_DEF;
        }
#line 2267 "y.tab.c"
    break;

  case 65: /* column_def: column_def_name data_type array_dim_clause column_def_opt_list  */
#line 622 "sql.y"
        {
            ColumnDefNode *column_def = make_column_def_node();
            column_def->column = (yyvsp[-3].column_def_name);
            column_def->data_type = (yyvsp[-2].data_type_node);
            column_def->array_dim = (yyvsp[-1].intVal);
            column_def->column_def_opt_list = (yyvsp[0].column_def_opt_list);
            (yyval.column_def_node) = column_def;
        }
#line 2280 "y.tab.c"
    break;

  case 66: /* column_def_name_commalist: column_def_name  */
#line 633 "sql.y"
        {
            ColumnDefNameCommalist *list = make_column_def_name_list();
            add_column_def_name_to_set(list, (yyvsp[0].column_def_name));
            (yyval.column_def_name_commalist) = list;
        }
#line 2290 "y.tab.c"
    break;

  case 67: /* column_def_name_commalist: column_def_name_commalist ',' column_def_name  */
#line 639 "sql.y"
        {
            add_column_def_name_to_set((yyvsp[-2].column_def_name_commalist), (yyvsp[0].column_def_name));
            (yyval.column_def_name_commalist) = (yyvsp[-2].column_def_name_commalist);
        }
#line 2299 "y.tab.c"
    break;

  case 68: /* column_def_name: IDENTIFIER  */
#line 646 "sql.y"
        {
            ColumnDefName *column_def_name = make_column_def_name();
            column_def_name->column = (yyvsp[0].strVal);
            (yyval.column_def_name) = column_def_name;
        }
#line 2309 "y.tab.c"
    break;

  case 69: /* data_type: INT  */
#line 654 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_INT; 
        }
#line 2318 "y.tab.c"
    break;

  case 70: /* data_type: LONG  */
#line 659 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_LONG;  
        }
#line 2327 "y.tab.c"
    break;

  case 71: /* data_type: CHAR  */
#line 664 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_CHAR; 
        }
#line 2336 "y.tab.c"
    break;

  case 72: /* data_type: VARCHAR '(' INTVALUE ')'  */
#line 669 "sql.y"
        {
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_VARCHAR; 
            (yyval.data_type_node)->len = (yyvsp[-1].intVal); 
        }
#line 2346 "y.tab.c"
    break;

  case 73: /* data_type: STRING  */
#line 675 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_STRING; 
        }
#line 2355 "y.tab.c"
    break;

  case 74: /* data_type: BOOL  */
#line 680 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_BOOL; 
        }
#line 2364 "y.tab.c"
    break;

  case 75: /* data_type: FLOAT  */
#line 685 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_FLOAT; 
        }
#line 2373 "y.tab.c"
    break;

  case 76: /* data_type: DOUBLE  */
#line 690 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_DOUBLE; 
        }
#line 2382 "y.tab.c"
    break;

  case 77: /* data_type: TIMESTAMP  */
#line 695 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_TIMESTAMP; 
        }
#line 2391 "y.tab.c"
    break;

  case 78: /* data_type: DATE  */
#line 700 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_DATE; 
        }
#line 2400 "y.tab.c"
    break;

  case 79: /* data_type: table  */
#line 705 "sql.y"
        {
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_REFERENCE;
            (yyval.data_type_node)->table_name = (yyvsp[0].strVal);
        }
#line 2410 "y.tab.c"
    break;

  case 80: /* array_dim_clause: %empty  */
#line 713 "sql.y"
        {
            (yyval.intVal) = 0;
        }
#line 2418 "y.tab.c"
    break;

  case 81: /* array_dim_clause: '[' ']'  */
#line 717 "sql.y"
        {
            (yyval.intVal) = 1;
        }
#line 2426 "y.tab.c"
    break;

  case 82: /* array_dim_clause: array_dim_clause '[' ']'  */
#line 721 "sql.y"
        {
            (yyval.intVal)++;
        }
#line 2434 "y.tab.c"
    break;

  case 83: /* column_def_opt_list: %empty  */
#line 727 "sql.y"
        {
            (yyval.column_def_opt_list) = NULL;
        }
#line 2442 "y.tab.c"
    break;

  case 84: /* column_def_opt_list: column_def_opt  */
#line 731 "sql.y"
        {
            (yyval.column_def_opt_list) = make_column_def_opt_list();
            add_column_def_opt_to_set((yyval.column_def_opt_list), (yyvsp[0].column_def_opt));
        }
#line 2451 "y.tab.c"
    break;

  case 85: /* column_def_opt_list: column_def_opt_list column_def_opt  */
#line 736 "sql.y"
        {
            add_column_def_opt_to_set((yyvsp[-1].column_def_opt_list), (yyvsp[0].column_def_opt));
            (yyval.column_def_opt_list) = (yyvsp[-1].column_def_opt_list);
        }
#line 2460 "y.tab.c"
    break;

  case 86: /* column_def_opt: NOT NULLX  */
#line 743 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_NOT_NULL; 
        }
#line 2469 "y.tab.c"
    break;

  case 87: /* column_def_opt: UNIQUE  */
#line 748 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_UNIQUE; 
        }
#line 2478 "y.tab.c"
    break;

  case 88: /* column_def_opt: PRIMARY KEY  */
#line 753 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_PRIMARY_KEY; 
        }
#line 2487 "y.tab.c"
    break;

  case 89: /* column_def_opt: DEFAULT value_item  */
#line 758 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_DEFAULT_VALUE;
            (yyval.column_def_opt)->value = (yyvsp[0].value_item_node);
        }
#line 2497 "y.tab.c"
    break;

  case 90: /* column_def_opt: DEFAULT NULLX  */
#line 764 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_DEFAULT_NULL;
        }
#line 2506 "y.tab.c"
    break;

  case 91: /* column_def_opt: CHECK '(' condition ')'  */
#line 769 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_CHECK_CONDITION;
            (yyval.column_def_opt)->condition = (yyvsp[-1].condition_node);
        }
#line 2516 "y.tab.c"
    break;

  case 92: /* column_def_opt: REFERENCES table  */
#line 775 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_REFERENECS;
            (yyval.column_def_opt)->refer_table = (yyvsp[0].strVal);
        }
#line 2526 "y.tab.c"
    break;

  case 93: /* table_contraint_def: UNIQUE '(' column_def_name_commalist ')'  */
#line 783 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_UNIQUE;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-1].column_def_name_commalist);
        }
#line 2536 "y.tab.c"
    break;

  case 94: /* table_contraint_def: PRIMARY KEY '(' column_def_name_commalist ')'  */
#line 789 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_PRIMARY_KEY;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-1].column_def_name_commalist);
        }
#line 2546 "y.tab.c"
    break;

  case 95: /* table_contraint_def: FOREIGN KEY '(' column_def_name_commalist ')' REFERENCES table  */
#line 795 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_FOREIGN_KEY;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-3].column_def_name_commalist);
            (yyval.table_contraint_def)->table = (yyvsp[0].strVal);
        }
#line 2557 "y.tab.c"
    break;

  case 96: /* table_contraint_def: CHECK '(' condition ')'  */
#line 802 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_CHECK;
            (yyval.table_contraint_def)->condition = (yyvsp[-1].condition_node);
        }
#line 2567 "y.tab.c"
    break;

  case 97: /* column: IDENTIFIER  */
#line 810 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[0].strVal);
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2578 "y.tab.c"
    break;

  case 98: /* column: IDENTIFIER '[' column ']'  */
#line 817 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->sub_column = (yyvsp[-1].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2590 "y.tab.c"
    break;

  case 99: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 825 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->scalar_exp_set = (yyvsp[-1].scalar_exp_set_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2602 "y.tab.c"
    break;

  case 100: /* column: IDENTIFIER '.' column  */
#line 833 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = (yyvsp[-2].strVal);
        }
#line 2611 "y.tab.c"
    break;

  case 101: /* value_items: value_item  */
#line 840 "sql.y"
        {
            ValueItemSetNode *node = make_value_item_set_node();
            add_value_item(node, (yyvsp[0].value_item_node));
            (yyval.value_item_set_node) = node;
        }
#line 2621 "y.tab.c"
    break;

  case 102: /* value_items: value_items ',' value_item  */
#line 846 "sql.y"
        {
            (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
            add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
        }
#line 2630 "y.tab.c"
    break;

  case 103: /* value_item: INTVALUE  */
#line 853 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.i_value = (yyvsp[0].intVal);
            node->data_type = T_INT;
            (yyval.value_item_node) = node;
        }
#line 2641 "y.tab.c"
    break;

  case 104: /* value_item: BOOLVALUE  */
#line 860 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.b_value = (yyvsp[0].boolVal);
            node->data_type = T_BOOL;
            (yyval.value_item_node) = node;
        }
#line 2652 "y.tab.c"
    break;

  case 105: /* value_item: STRINGVALUE  */
#line 867 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.s_value = (yyvsp[0].strVal);
            node->data_type = T_STRING;
            (yyval.value_item_node) = node;
        }
#line 2663 "y.tab.c"
    break;

  case 106: /* value_item: FLOATVALUE  */
#line 874 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.f_value = (yyvsp[0].floatVal);
            node->data_type = T_FLOAT;
            (yyval.value_item_node) = node;
        }
#line 2674 "y.tab.c"
    break;

  case 107: /* value_item: REFERVALUE  */
#line 881 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->value.r_value = (yyvsp[0].referVal);
            node->data_type = T_REFERENCE;
            (yyval.value_item_node) = node;
        }
#line 2685 "y.tab.c"
    break;

  case 108: /* REFERVALUE: '(' value_items ')'  */
#line 891 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_item_set = (yyvsp[-1].value_item_set_node);
            (yyval.referVal) = refer;
        }
#line 2696 "y.tab.c"
    break;

  case 109: /* REFERVALUE: REF '(' condition ')'  */
#line 899 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.referVal) = refer;
        }
#line 2707 "y.tab.c"
    break;

  case 110: /* BOOLVALUE: TRUE  */
#line 908 "sql.y"
        {
            (yyval.boolVal) = true;
        }
#line 2715 "y.tab.c"
    break;

  case 111: /* BOOLVALUE: FALSE  */
#line 912 "sql.y"
        {
            (yyval.boolVal) = false;
        }
#line 2723 "y.tab.c"
    break;

  case 112: /* assignments: assignment  */
#line 918 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2733 "y.tab.c"
    break;

  case 113: /* assignments: assignments ',' assignment  */
#line 924 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2742 "y.tab.c"
    break;

  case 114: /* assignment: column EQ value_item  */
#line 931 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2753 "y.tab.c"
    break;

  case 115: /* condition: condition OR condition  */
#line 940 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2765 "y.tab.c"
    break;

  case 116: /* condition: condition AND condition  */
#line 948 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2777 "y.tab.c"
    break;

  case 117: /* condition: '(' condition ')'  */
#line 956 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2785 "y.tab.c"
    break;

  case 118: /* condition: predicate  */
#line 960 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2796 "y.tab.c"
    break;

  case 119: /* predicate: comparison_predicate  */
#line 969 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2807 "y.tab.c"
    break;

  case 120: /* predicate: like_predicate  */
#line 976 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2818 "y.tab.c"
    break;

  case 121: /* predicate: in_predicate  */
#line 983 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 2829 "y.tab.c"
    break;

  case 122: /* comparison_predicate: column compare scalar_exp  */
#line 992 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 2841 "y.tab.c"
    break;

  case 123: /* like_predicate: column LIKE value_item  */
#line 1002 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 2852 "y.tab.c"
    break;

  case 124: /* in_predicate: column IN '(' value_items ')'  */
#line 1011 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_set = (yyvsp[-1].value_item_set_node);
            (yyval.in_node) = in_node;
        }
#line 2863 "y.tab.c"
    break;

  case 125: /* compare: EQ  */
#line 1039 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 2869 "y.tab.c"
    break;

  case 126: /* compare: NE  */
#line 1040 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 2875 "y.tab.c"
    break;

  case 127: /* compare: GT  */
#line 1041 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 2881 "y.tab.c"
    break;

  case 128: /* compare: GE  */
#line 1042 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 2887 "y.tab.c"
    break;

  case 129: /* compare: LT  */
#line 1043 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 2893 "y.tab.c"
    break;

  case 130: /* compare: LE  */
#line 1044 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 2899 "y.tab.c"
    break;

  case 131: /* function: MAX '(' non_all_function_value ')'  */
#line 1048 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2910 "y.tab.c"
    break;

  case 132: /* function: MIN '(' non_all_function_value ')'  */
#line 1055 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2921 "y.tab.c"
    break;

  case 133: /* function: COUNT '(' function_value ')'  */
#line 1062 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2932 "y.tab.c"
    break;

  case 134: /* function: SUM '(' function_value ')'  */
#line 1069 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2943 "y.tab.c"
    break;

  case 135: /* function: AVG '(' function_value ')'  */
#line 1076 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2954 "y.tab.c"
    break;

  case 136: /* function_value: INTVALUE  */
#line 1085 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2965 "y.tab.c"
    break;

  case 137: /* function_value: column  */
#line 1092 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 2976 "y.tab.c"
    break;

  case 138: /* function_value: '*'  */
#line 1099 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 2986 "y.tab.c"
    break;

  case 139: /* non_all_function_value: INTVALUE  */
#line 1107 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 2997 "y.tab.c"
    break;

  case 140: /* non_all_function_value: column  */
#line 1114 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3008 "y.tab.c"
    break;


#line 3012 "y.tab.c"

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

#line 1125 "sql.y"

