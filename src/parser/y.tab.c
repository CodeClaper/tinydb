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
#include "list.h"
#include "intpr.h"
#include "mmu.h"
#include "log.h"
#include "utils.h"
#include "y.tab.h"

int yywrap() {
    return 1;
}
int yylex();

#line 89 "y.tab.c"

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
    OFFSET = 278,                  /* OFFSET  */
    SHOW = 279,                    /* SHOW  */
    TABLES = 280,                  /* TABLES  */
    PRIMARY = 281,                 /* PRIMARY  */
    KEY = 282,                     /* KEY  */
    UNIQUE = 283,                  /* UNIQUE  */
    DEFAULT = 284,                 /* DEFAULT  */
    CHECK = 285,                   /* CHECK  */
    REFERENCES = 286,              /* REFERENCES  */
    FOREIGN = 287,                 /* FOREIGN  */
    MAX = 288,                     /* MAX  */
    MIN = 289,                     /* MIN  */
    COUNT = 290,                   /* COUNT  */
    SUM = 291,                     /* SUM  */
    AVG = 292,                     /* AVG  */
    REF = 293,                     /* REF  */
    TRUE = 294,                    /* TRUE  */
    FALSE = 295,                   /* FALSE  */
    NULLX = 296,                   /* NULLX  */
    AS = 297,                      /* AS  */
    COMMENT = 298,                 /* COMMENT  */
    CHAR = 299,                    /* CHAR  */
    INT = 300,                     /* INT  */
    LONG = 301,                    /* LONG  */
    VARCHAR = 302,                 /* VARCHAR  */
    STRING = 303,                  /* STRING  */
    BOOL = 304,                    /* BOOL  */
    FLOAT = 305,                   /* FLOAT  */
    DOUBLE = 306,                  /* DOUBLE  */
    DATE = 307,                    /* DATE  */
    TIMESTAMP = 308,               /* TIMESTAMP  */
    EQ = 309,                      /* EQ  */
    NE = 310,                      /* NE  */
    GT = 311,                      /* GT  */
    GE = 312,                      /* GE  */
    LT = 313,                      /* LT  */
    LE = 314,                      /* LE  */
    IN = 315,                      /* IN  */
    LIKE = 316,                    /* LIKE  */
    NOT = 317,                     /* NOT  */
    ALTER = 318,                   /* ALTER  */
    COLUMN = 319,                  /* COLUMN  */
    ADD = 320,                     /* ADD  */
    RENAME = 321,                  /* RENAME  */
    BEFORE = 322,                  /* BEFORE  */
    AFTER = 323,                   /* AFTER  */
    SYSTEM = 324,                  /* SYSTEM  */
    CONFIG = 325,                  /* CONFIG  */
    MEMORY = 326,                  /* MEMORY  */
    IDENTIFIER = 327,              /* IDENTIFIER  */
    INTVALUE = 328,                /* INTVALUE  */
    FLOATVALUE = 329,              /* FLOATVALUE  */
    STRINGVALUE = 330              /* STRINGVALUE  */
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
#define OFFSET 278
#define SHOW 279
#define TABLES 280
#define PRIMARY 281
#define KEY 282
#define UNIQUE 283
#define DEFAULT 284
#define CHECK 285
#define REFERENCES 286
#define FOREIGN 287
#define MAX 288
#define MIN 289
#define COUNT 290
#define SUM 291
#define AVG 292
#define REF 293
#define TRUE 294
#define FALSE 295
#define NULLX 296
#define AS 297
#define COMMENT 298
#define CHAR 299
#define INT 300
#define LONG 301
#define VARCHAR 302
#define STRING 303
#define BOOL 304
#define FLOAT 305
#define DOUBLE 306
#define DATE 307
#define TIMESTAMP 308
#define EQ 309
#define NE 310
#define GT 311
#define GE 312
#define LT 313
#define LE 314
#define IN 315
#define LIKE 316
#define NOT 317
#define ALTER 318
#define COLUMN 319
#define ADD 320
#define RENAME 321
#define BEFORE 322
#define AFTER 323
#define SYSTEM 324
#define CONFIG 325
#define MEMORY 326
#define IDENTIFIER 327
#define INTVALUE 328
#define FLOATVALUE 329
#define STRINGVALUE 330

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "sql.y"

   char                         *strVal;
   int64_t                      intVal;
   double                       floatVal;
   bool                         boolVal;
   char                         *keyword;
   ReferValue                   *referVal;
   CompareType                  compare_type;
   DataTypeNode                 *data_type_node;
   ColumnDefName                *column_def_name;
   ColumnDefNode                *column_def_node;
   BaseTableElementNode         *base_table_element;
   ColumnDefOptNode             *column_def_opt;
   TableContraintDefNode        *table_contraint_def;
   ColumnNode                   *column_node;
   AtomNode                     *atom_node;
   ValueItemNode                *value_item_node;
   SelectionNode                *selection_node;
   ScalarExpNode                *scalar_exp_node;
   FunctionValueNode            *function_value_node;
   FunctionNode                 *function_node;
   CalculateNode                *calculate_node;
   AssignmentNode               *assignment_node;
   ConditionNode                *condition_node;
   PredicateNode                *predicate_node;
   ComparisonNode               *comparison_node;
   LikeNode                     *like_node;
   InNode                       *in_node;
   LimitClauseNode              *limit_clause_node;
   TableRefNode                 *table_ref_node;
   QuerySpecNode                *query_spec_node;
   ValuesOrQuerySpecNode        *values_or_query_spec_node;
   FromClauseNode               *from_clause_node;
   WhereClauseNode              *where_clause_node;
   TableExpNode                 *table_exp_node; 
   AddColumnDef                 *add_column_def;
   DropColumnDef                *drop_column_def;
   AlterTableAction             *alter_table_action;
   ColumnPositionDef            *column_position_def;
   CreateTableNode              *create_table_node;
   DropTableNode                *drop_table_node;
   SelectNode                   *select_node;
   InsertNode                   *insert_node;
   UpdateNode                   *update_node;
   DeleteNode                   *delete_node;
   DescribeNode                 *describe_node;
   ShowNode                     *show_node;
   AlterTableNode               *alter_table_node;
   Statement                    *statement;
   List                         *list;

#line 344 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (List *states);


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
  YYSYMBOL_11_ = 11,                       /* '['  */
  YYSYMBOL_12_ = 12,                       /* ']'  */
  YYSYMBOL_NL = 13,                        /* NL  */
  YYSYMBOL_BEGINN = 14,                    /* BEGINN  */
  YYSYMBOL_COMMIT = 15,                    /* COMMIT  */
  YYSYMBOL_ROLLBACK = 16,                  /* ROLLBACK  */
  YYSYMBOL_CREATE = 17,                    /* CREATE  */
  YYSYMBOL_DROP = 18,                      /* DROP  */
  YYSYMBOL_SELECT = 19,                    /* SELECT  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_DELETE = 22,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 23,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 24,                      /* FROM  */
  YYSYMBOL_WHERE = 25,                     /* WHERE  */
  YYSYMBOL_INTO = 26,                      /* INTO  */
  YYSYMBOL_SET = 27,                       /* SET  */
  YYSYMBOL_VALUES = 28,                    /* VALUES  */
  YYSYMBOL_TABLE = 29,                     /* TABLE  */
  YYSYMBOL_LIMIT = 30,                     /* LIMIT  */
  YYSYMBOL_OFFSET = 31,                    /* OFFSET  */
  YYSYMBOL_SHOW = 32,                      /* SHOW  */
  YYSYMBOL_TABLES = 33,                    /* TABLES  */
  YYSYMBOL_PRIMARY = 34,                   /* PRIMARY  */
  YYSYMBOL_KEY = 35,                       /* KEY  */
  YYSYMBOL_UNIQUE = 36,                    /* UNIQUE  */
  YYSYMBOL_DEFAULT = 37,                   /* DEFAULT  */
  YYSYMBOL_CHECK = 38,                     /* CHECK  */
  YYSYMBOL_REFERENCES = 39,                /* REFERENCES  */
  YYSYMBOL_FOREIGN = 40,                   /* FOREIGN  */
  YYSYMBOL_MAX = 41,                       /* MAX  */
  YYSYMBOL_MIN = 42,                       /* MIN  */
  YYSYMBOL_COUNT = 43,                     /* COUNT  */
  YYSYMBOL_SUM = 44,                       /* SUM  */
  YYSYMBOL_AVG = 45,                       /* AVG  */
  YYSYMBOL_REF = 46,                       /* REF  */
  YYSYMBOL_TRUE = 47,                      /* TRUE  */
  YYSYMBOL_FALSE = 48,                     /* FALSE  */
  YYSYMBOL_NULLX = 49,                     /* NULLX  */
  YYSYMBOL_AS = 50,                        /* AS  */
  YYSYMBOL_COMMENT = 51,                   /* COMMENT  */
  YYSYMBOL_CHAR = 52,                      /* CHAR  */
  YYSYMBOL_INT = 53,                       /* INT  */
  YYSYMBOL_LONG = 54,                      /* LONG  */
  YYSYMBOL_VARCHAR = 55,                   /* VARCHAR  */
  YYSYMBOL_STRING = 56,                    /* STRING  */
  YYSYMBOL_BOOL = 57,                      /* BOOL  */
  YYSYMBOL_FLOAT = 58,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 59,                    /* DOUBLE  */
  YYSYMBOL_DATE = 60,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 61,                 /* TIMESTAMP  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_NE = 63,                        /* NE  */
  YYSYMBOL_GT = 64,                        /* GT  */
  YYSYMBOL_GE = 65,                        /* GE  */
  YYSYMBOL_LT = 66,                        /* LT  */
  YYSYMBOL_LE = 67,                        /* LE  */
  YYSYMBOL_IN = 68,                        /* IN  */
  YYSYMBOL_LIKE = 69,                      /* LIKE  */
  YYSYMBOL_NOT = 70,                       /* NOT  */
  YYSYMBOL_ALTER = 71,                     /* ALTER  */
  YYSYMBOL_COLUMN = 72,                    /* COLUMN  */
  YYSYMBOL_ADD = 73,                       /* ADD  */
  YYSYMBOL_RENAME = 74,                    /* RENAME  */
  YYSYMBOL_BEFORE = 75,                    /* BEFORE  */
  YYSYMBOL_AFTER = 76,                     /* AFTER  */
  YYSYMBOL_SYSTEM = 77,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 78,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 79,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 80,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 81,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 82,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 83,               /* STRINGVALUE  */
  YYSYMBOL_84_ = 84,                       /* ','  */
  YYSYMBOL_85_ = 85,                       /* '.'  */
  YYSYMBOL_86_ = 86,                       /* '{'  */
  YYSYMBOL_87_ = 87,                       /* '}'  */
  YYSYMBOL_88_ = 88,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_statements = 90,                /* statements  */
  YYSYMBOL_statement = 91,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 92, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 93, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 94, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 95,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 96,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 97,          /* select_statement  */
  YYSYMBOL_insert_statement = 98,          /* insert_statement  */
  YYSYMBOL_update_statement = 99,          /* update_statement  */
  YYSYMBOL_delete_statement = 100,         /* delete_statement  */
  YYSYMBOL_describe_statement = 101,       /* describe_statement  */
  YYSYMBOL_show_statement = 102,           /* show_statement  */
  YYSYMBOL_alter_table_statement = 103,    /* alter_table_statement  */
  YYSYMBOL_alter_table_action = 104,       /* alter_table_action  */
  YYSYMBOL_add_column_def = 105,           /* add_column_def  */
  YYSYMBOL_drop_column_def = 106,          /* drop_column_def  */
  YYSYMBOL_column_position_def = 107,      /* column_position_def  */
  YYSYMBOL_selection = 108,                /* selection  */
  YYSYMBOL_table_exp = 109,                /* table_exp  */
  YYSYMBOL_from_clause = 110,              /* from_clause  */
  YYSYMBOL_table_ref_commalist = 111,      /* table_ref_commalist  */
  YYSYMBOL_table_ref = 112,                /* table_ref  */
  YYSYMBOL_table = 113,                    /* table  */
  YYSYMBOL_range_variable = 114,           /* range_variable  */
  YYSYMBOL_opt_where_clause = 115,         /* opt_where_clause  */
  YYSYMBOL_where_clause = 116,             /* where_clause  */
  YYSYMBOL_values_or_query_spec = 117,     /* values_or_query_spec  */
  YYSYMBOL_opt_values = 118,               /* opt_values  */
  YYSYMBOL_query_spec = 119,               /* query_spec  */
  YYSYMBOL_scalar_exp_commalist = 120,     /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 121,               /* scalar_exp  */
  YYSYMBOL_calculate = 122,                /* calculate  */
  YYSYMBOL_columns = 123,                  /* columns  */
  YYSYMBOL_base_table_element_commalist = 124, /* base_table_element_commalist  */
  YYSYMBOL_base_table_element = 125,       /* base_table_element  */
  YYSYMBOL_column_def = 126,               /* column_def  */
  YYSYMBOL_column_def_name_commalist = 127, /* column_def_name_commalist  */
  YYSYMBOL_column_def_name = 128,          /* column_def_name  */
  YYSYMBOL_data_type = 129,                /* data_type  */
  YYSYMBOL_array_dim_clause = 130,         /* array_dim_clause  */
  YYSYMBOL_column_def_opt_list = 131,      /* column_def_opt_list  */
  YYSYMBOL_column_def_opt = 132,           /* column_def_opt  */
  YYSYMBOL_table_contraint_def = 133,      /* table_contraint_def  */
  YYSYMBOL_column = 134,                   /* column  */
  YYSYMBOL_value_items = 135,              /* value_items  */
  YYSYMBOL_value_item = 136,               /* value_item  */
  YYSYMBOL_atom = 137,                     /* atom  */
  YYSYMBOL_REFERVALUE = 138,               /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 139,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 140,              /* assignments  */
  YYSYMBOL_assignment = 141,               /* assignment  */
  YYSYMBOL_condition = 142,                /* condition  */
  YYSYMBOL_predicate = 143,                /* predicate  */
  YYSYMBOL_comparison_predicate = 144,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 145,           /* like_predicate  */
  YYSYMBOL_in_predicate = 146,             /* in_predicate  */
  YYSYMBOL_limit_clause = 147,             /* limit_clause  */
  YYSYMBOL_compare = 148,                  /* compare  */
  YYSYMBOL_function = 149,                 /* function  */
  YYSYMBOL_function_value = 150,           /* function_value  */
  YYSYMBOL_non_all_function_value = 151,   /* non_all_function_value  */
  YYSYMBOL_end = 152                       /* end  */
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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   374

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  311

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
       9,    10,     7,     5,    84,     6,    85,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    88,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    11,     2,    12,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,     2,    87,     2,     2,     2,     2,
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
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   172,   172,   177,   184,   190,   196,   202,   209,   216,
     223,   230,   237,   244,   251,   258,   267,   270,   273,   277,
     287,   296,   306,   314,   326,   337,   343,   353,   362,   368,
     377,   385,   392,   401,   410,   419,   422,   429,   438,   445,
     453,   464,   467,   475,   481,   488,   494,   501,   510,   516,
     523,   526,   532,   540,   547,   556,   561,   568,   577,   583,
     590,   597,   604,   611,   618,   622,   629,   637,   645,   653,
     663,   669,   676,   682,   689,   697,   720,   731,   737,   744,
     752,   758,   764,   770,   777,   783,   789,   795,   801,   807,
     813,   823,   826,   830,   837,   840,   845,   852,   858,   864,
     870,   877,   883,   890,   897,   906,   913,   920,   928,   937,
     944,   952,   960,   967,   973,   980,   987,   993,  1002,  1009,
    1016,  1023,  1030,  1040,  1048,  1057,  1061,  1067,  1073,  1080,
    1089,  1097,  1105,  1109,  1118,  1125,  1132,  1141,  1151,  1160,
    1170,  1173,  1180,  1187,  1196,  1197,  1198,  1199,  1200,  1201,
    1204,  1211,  1218,  1225,  1232,  1241,  1248,  1255,  1263,  1270,
    1279,  1280
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
  "'-'", "'*'", "'/'", "'('", "')'", "'['", "']'", "NL", "BEGINN",
  "COMMIT", "ROLLBACK", "CREATE", "DROP", "SELECT", "INSERT", "UPDATE",
  "DELETE", "DESCRIBE", "FROM", "WHERE", "INTO", "SET", "VALUES", "TABLE",
  "LIMIT", "OFFSET", "SHOW", "TABLES", "PRIMARY", "KEY", "UNIQUE",
  "DEFAULT", "CHECK", "REFERENCES", "FOREIGN", "MAX", "MIN", "COUNT",
  "SUM", "AVG", "REF", "TRUE", "FALSE", "NULLX", "AS", "COMMENT", "CHAR",
  "INT", "LONG", "VARCHAR", "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE",
  "TIMESTAMP", "EQ", "NE", "GT", "GE", "LT", "LE", "IN", "LIKE", "NOT",
  "ALTER", "COLUMN", "ADD", "RENAME", "BEFORE", "AFTER", "SYSTEM",
  "CONFIG", "MEMORY", "IDENTIFIER", "INTVALUE", "FLOATVALUE",
  "STRINGVALUE", "','", "'.'", "'{'", "'}'", "';'", "$accept",
  "statements", "statement", "begin_transaction_statement",
  "commit_transaction_statement", "rollback_transaction_statement",
  "create_table_statement", "drop_table_statement", "select_statement",
  "insert_statement", "update_statement", "delete_statement",
  "describe_statement", "show_statement", "alter_table_statement",
  "alter_table_action", "add_column_def", "drop_column_def",
  "column_position_def", "selection", "table_exp", "from_clause",
  "table_ref_commalist", "table_ref", "table", "range_variable",
  "opt_where_clause", "where_clause", "values_or_query_spec", "opt_values",
  "query_spec", "scalar_exp_commalist", "scalar_exp", "calculate",
  "columns", "base_table_element_commalist", "base_table_element",
  "column_def", "column_def_name_commalist", "column_def_name",
  "data_type", "array_dim_clause", "column_def_opt_list", "column_def_opt",
  "table_contraint_def", "column", "value_items", "value_item", "atom",
  "REFERVALUE", "BOOLVALUE", "assignments", "assignment", "condition",
  "predicate", "comparison_predicate", "like_predicate", "in_predicate",
  "limit_clause", "compare", "function", "function_value",
  "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-194)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-114)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     286,   -68,   -68,   -68,     3,    58,    62,    31,   -19,   137,
     -19,   124,   143,   260,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,   162,  -194,  -194,
    -194,   -19,   -19,  -194,    87,    67,   170,   182,   184,   186,
     203,   205,  -194,  -194,  -194,   -45,  -194,  -194,  -194,   187,
     142,   246,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   -19,
    -194,   213,   -19,   -68,   -68,   -68,   -19,  -194,  -194,  -194,
     232,   -68,    -3,   238,     2,   165,    67,    13,  -194,    71,
      71,    37,    37,    37,    61,    79,   175,   -19,   -68,   234,
     175,   175,   175,   175,   175,   192,    34,    79,    -4,  -194,
    -194,  -194,     8,   154,  -194,   199,  -194,  -194,    67,  -194,
     206,  -194,  -194,   252,   275,  -194,  -194,  -194,   277,   279,
     281,   130,   202,    32,  -194,  -194,  -194,  -194,  -194,   -54,
     209,  -194,   -21,  -194,    61,   264,  -194,   246,   197,   197,
     240,   240,  -194,    79,    62,   288,   -68,  -194,   233,   -17,
    -194,    61,  -194,   226,   239,   -68,  -194,  -194,   282,   307,
     310,   285,  -194,    17,  -194,  -194,   280,  -194,    79,  -194,
     311,  -194,  -194,  -194,  -194,  -194,   173,  -194,  -194,  -194,
    -194,  -194,  -194,   313,    67,   175,    61,    61,  -194,  -194,
     -19,   243,  -194,  -194,   150,   244,  -194,    28,  -194,   187,
      67,   242,  -194,    67,    79,   -68,     7,   248,   249,  -194,
     315,   249,    61,   321,   -68,   154,  -194,  -194,  -194,   333,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,   332,  -194,  -194,
      67,  -194,   246,   340,  -194,  -194,  -194,   129,     9,    79,
    -194,    35,   336,  -194,  -194,  -194,  -194,  -194,   133,   249,
      38,  -194,   177,   249,  -194,  -194,   266,   337,   191,    39,
     267,   269,   -68,  -194,  -194,    67,   271,   272,  -194,    40,
    -194,   249,  -194,    42,   343,  -194,   342,   320,  -194,   116,
     347,   -19,   278,   309,   276,  -194,  -194,  -194,  -194,  -194,
      53,  -194,  -194,  -194,  -194,   323,  -194,  -194,  -194,  -194,
    -194,    61,  -194,  -194,  -194,  -194,  -194,   -19,   229,  -194,
    -194
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   160,    16,    17,
      18,     0,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   126,   116,   109,   118,   121,   120,    41,
      38,    58,    60,    61,    63,   115,   122,   119,    62,     0,
      48,     0,     0,     0,     0,     0,     0,     1,     3,   161,
       0,     0,   109,     0,     0,    63,     0,     0,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      28,    29,     0,     0,    20,     0,    64,   123,     0,   117,
       0,   158,   159,     0,     0,   157,   155,   156,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   112,     0,
      42,    43,    45,    21,     0,   140,    51,    59,    66,    67,
      68,    69,    65,     0,     0,     0,     0,    54,     0,    50,
     127,     0,    25,     0,     0,     0,    31,    32,     0,     0,
       0,     0,    79,     0,    72,    74,     0,    75,     0,   114,
       0,   150,   151,   152,   153,   154,     0,   144,   145,   146,
     147,   148,   149,     0,     0,     0,     0,     0,   124,   111,
       0,     0,    49,    46,    52,     0,    40,     0,    70,    41,
       0,    53,    22,     0,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,    82,    80,    81,     0,
      84,    85,    86,    87,    89,    88,    90,    91,   110,   132,
       0,   138,   137,   130,   131,    44,    47,   141,     0,     0,
      57,     0,     0,   129,   128,    24,    26,    34,    35,     0,
       0,    77,     0,     0,    19,    73,     0,     0,    94,     0,
       0,     0,     0,    71,    55,     0,     0,     0,    33,     0,
     105,     0,   108,     0,     0,    92,     0,     0,    98,     0,
       0,     0,     0,     0,    76,    95,   139,   143,   142,    23,
       0,    36,    37,   106,    78,     0,    83,    93,    99,   101,
     100,     0,   104,   102,    97,    96,    56,     0,     0,   107,
     103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,   346,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,   219,
     166,  -194,  -194,   174,    -8,   176,   217,  -194,   131,  -194,
    -194,   284,     0,  -194,  -194,  -194,   153,   163,  -193,   -71,
    -194,  -194,  -194,    88,  -194,   -66,   -34,   -29,  -194,  -194,
    -194,  -194,   169,  -112,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,   155,   294,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   155,   156,   157,   268,    49,
      88,    89,   130,   131,   132,   193,   135,   136,   146,   201,
     147,    50,    51,    52,   197,   163,   164,   165,   250,   166,
     227,   258,   284,   285,   167,    53,    74,    54,    55,    56,
      57,   149,   150,   123,   124,   125,   126,   127,   196,   185,
      58,   118,   113,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    77,    63,    29,    30,    75,    78,   105,   134,   176,
     186,   187,   107,   112,   112,   117,   117,   117,   122,   128,
      27,   151,   194,    70,    71,   109,   153,   214,   144,   191,
      90,   148,    31,   189,    73,   186,   187,   145,   238,   206,
      85,    86,   188,   143,   115,   264,   110,    78,   270,   286,
     293,    96,   295,   144,    98,   122,   269,    59,   102,   192,
     273,    60,   145,   306,    99,   100,   101,   204,   122,    33,
     121,    34,   104,    35,   233,   234,    76,   198,    35,   169,
     110,   154,    85,    86,    27,   122,   108,    32,   110,   133,
     137,   138,   139,   140,   141,    27,    34,   108,    35,   152,
     252,   215,   228,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   239,    41,    42,    43,    44,    45,   116,   108,
     122,   122,   271,   108,   271,    76,   271,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,   108,   148,   121,
     251,    45,    45,    46,    47,    48,   122,   202,    46,    47,
      48,    45,   111,   186,   187,   231,   209,    64,   226,    45,
     260,    62,    41,    42,    43,   299,   241,    72,    46,    47,
      48,    78,    66,   263,   243,    69,   186,   187,   251,    79,
     186,   187,   251,   229,    34,   232,    35,   272,   158,   308,
     159,    80,   160,    81,   161,    82,   259,    46,    47,    48,
     294,    78,   276,    65,    93,    94,   245,   246,   266,   267,
      72,    87,    83,   261,    84,   254,    36,    37,    38,    39,
      40,    41,    42,    43,    44,   277,    90,   278,   279,   280,
     281,   290,   186,   187,   162,   122,    78,   119,   120,   310,
      97,   103,   282,    91,    92,    93,    94,    95,   106,  -113,
     300,    91,    92,    93,    94,    45,    46,    47,    48,   134,
      67,   283,   171,   289,   177,   178,   179,   180,   181,   182,
     183,   184,   142,   302,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,   168,   172,   170,   173,    95,   174,
      95,   175,    11,   190,   195,   203,    95,   200,   207,   309,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     277,   208,   278,   279,   280,   281,   211,   210,    11,   212,
     213,   105,   230,   192,   249,   237,   242,   282,   247,   162,
     253,    12,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   256,   257,   187,   265,   283,   274,   287,   275,
     288,   291,   292,   296,   297,   298,   301,    12,   304,    68,
      60,   303,   307,   199,   235,   240,   205,   236,   255,   262,
     129,   248,   305,   244,   114
};

static const yytype_int16 yycheck[] =
{
       8,    35,    10,     2,     3,    34,    35,    10,    25,   121,
       3,     4,    10,    79,    80,    81,    82,    83,    84,    85,
      88,    25,   134,    31,    32,    12,    18,    10,    19,    50,
      84,    97,    29,    87,    34,     3,     4,    28,    10,   151,
      85,    86,    10,     9,     7,    10,     9,    76,    10,    10,
      10,    59,    10,    19,    62,   121,   249,    26,    66,    80,
     253,    80,    28,    10,    63,    64,    65,    84,   134,     7,
       9,     9,    71,    11,   186,   187,     9,   143,    11,   108,
       9,    73,    85,    86,    88,   151,    84,    29,     9,    88,
      90,    91,    92,    93,    94,    88,     9,    84,    11,    98,
     212,    84,   168,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    84,    46,    47,    48,    49,    80,    81,    84,
     186,   187,    84,    84,    84,     9,    84,    11,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    84,   204,     9,
     211,    80,    80,    81,    82,    83,   212,   146,    81,    82,
      83,    80,    81,     3,     4,   184,   155,    33,   166,    80,
      31,    24,    46,    47,    48,    49,   200,    80,    81,    82,
      83,   200,    29,   239,   203,    13,     3,     4,   249,     9,
       3,     4,   253,    10,     9,   185,    11,    10,    34,   301,
      36,     9,    38,     9,    40,     9,   230,    81,    82,    83,
     271,   230,    11,    79,     7,     8,   205,   206,    75,    76,
      80,    24,     9,    84,     9,   214,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    34,    84,    36,    37,    38,
      39,   265,     3,     4,    80,   301,   265,    82,    83,    10,
      27,     9,    51,     5,     6,     7,     8,    50,    10,    84,
     279,     5,     6,     7,     8,    80,    81,    82,    83,    25,
       0,    70,    10,   262,    62,    63,    64,    65,    66,    67,
      68,    69,    80,   281,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    85,    10,    80,    10,    50,    10,
      50,    10,    32,    84,    30,    62,    50,     9,    72,   307,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      34,    72,    36,    37,    38,    39,     9,    35,    32,     9,
      35,    10,     9,    80,     9,    81,    84,    51,    80,    80,
       9,    71,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,     9,    11,     4,     9,    70,    81,    81,    12,
      81,    80,    80,    10,    12,    35,     9,    71,    49,    13,
      80,    83,    39,   144,   190,   199,   149,   191,   215,   238,
      86,   208,   284,   204,    80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    32,    71,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    88,   152,   152,
     152,    29,    29,     7,     9,    11,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    80,    81,    82,    83,   108,
     120,   121,   122,   134,   136,   137,   138,   139,   149,    26,
      80,   113,    24,   113,    33,    79,    29,     0,    91,    13,
     113,   113,    80,   121,   135,   136,     9,   135,   136,     9,
       9,     9,     9,     9,     9,    85,    86,    24,   109,   110,
      84,     5,     6,     7,     8,    50,   113,    27,   113,   152,
     152,   152,   113,     9,   152,    10,    10,    10,    84,    12,
       9,    81,   134,   151,   151,     7,    81,   134,   150,   150,
     150,     9,   134,   142,   143,   144,   145,   146,   134,   120,
     111,   112,   113,   152,    25,   115,   116,   121,   121,   121,
     121,   121,    80,     9,    19,    28,   117,   119,   134,   140,
     141,    25,   152,    18,    73,   104,   105,   106,    34,    36,
      38,    40,    80,   124,   125,   126,   128,   133,    85,   136,
      80,    10,    10,    10,    10,    10,   142,    62,    63,    64,
      65,    66,    67,    68,    69,   148,     3,     4,    10,    87,
      84,    50,    80,   114,   142,    30,   147,   123,   134,   108,
       9,   118,   152,    62,    84,   115,   142,    72,    72,   152,
      35,     9,     9,    35,    10,    84,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,   113,   129,   134,    10,
       9,   136,   121,   142,   142,   112,   114,    81,    10,    84,
     109,   135,    84,   136,   141,   152,   152,    80,   126,     9,
     127,   128,   142,     9,   152,   125,     9,    11,   130,   135,
      31,    84,   117,   134,    10,     9,    75,    76,   107,   127,
      10,    84,    10,   127,    81,    12,    11,    34,    36,    37,
      38,    39,    51,    70,   131,   132,    10,    81,    81,   152,
     135,    80,    80,    10,   128,    10,    10,    12,    35,    49,
     136,     9,   113,    83,    49,   132,    10,    39,   142,   113,
      10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    93,    94,    95,
      96,    97,    98,    98,    99,   100,   100,   101,   102,   102,
     103,   104,   104,   105,   106,   107,   107,   107,   108,   108,
     109,   110,   110,   111,   111,   112,   112,   112,   113,   114,
     115,   115,   116,   117,   117,   118,   118,   119,   120,   120,
     121,   121,   121,   121,   121,   121,   122,   122,   122,   122,
     123,   123,   124,   124,   125,   125,   126,   127,   127,   128,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   130,   130,   130,   131,   131,   131,   132,   132,   132,
     132,   132,   132,   132,   132,   133,   133,   133,   133,   134,
     134,   134,   134,   135,   135,   136,   136,   136,   137,   137,
     137,   137,   137,   138,   138,   139,   139,   140,   140,   141,
     142,   142,   142,   142,   143,   143,   143,   144,   145,   146,
     147,   147,   147,   147,   148,   148,   148,   148,   148,   148,
     149,   149,   149,   149,   149,   150,   150,   150,   151,   151,
     152,   152
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     7,
       4,     4,     5,     8,     6,     4,     6,     3,     3,     3,
       5,     1,     1,     4,     3,     0,     2,     2,     1,     1,
       3,     0,     2,     1,     3,     1,     2,     3,     1,     1,
       0,     1,     2,     2,     1,     3,     5,     3,     1,     3,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     1,     4,     1,     3,     1,
       1,     1,     1,     4,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     3,     0,     1,     2,     2,     1,     2,
       2,     2,     2,     4,     2,     4,     5,     7,     4,     1,
       5,     4,     3,     1,     3,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     4,     1,     1,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     3,     3,     5,
       0,     2,     4,     4,     1,     1,     1,     1,     1,     1,
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
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, List *states)
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, List *states)
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
                 int yyrule, List *states)
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, List *states)
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
yyparse (List *states)
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
#line 173 "sql.y"
        {
            append_list(states, (yyvsp[0].statement));
            (yyval.list) = states;
        }
#line 1729 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 178 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].statement));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 1738 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 185 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1748 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 191 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1758 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 197 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1768 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 203 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1779 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 210 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1790 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 217 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1801 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 224 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1812 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 231 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1823 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 238 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1834 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 245 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1845 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 252 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1856 "y.tab.c"
    break;

  case 15: /* statement: alter_table_statement  */
#line 259 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = ALTER_TABLE_STMT;
            statement->alter_table_node = (yyvsp[0].alter_table_node);
            (yyval.statement) = statement;
        }
#line 1867 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table '(' base_table_element_commalist ')' end  */
#line 278 "sql.y"
        {
            CreateTableNode *create_table_node = instance(CreateTableNode);
            create_table_node->table_name = (yyvsp[-4].strVal);
            create_table_node->base_table_element_commalist = (yyvsp[-2].list);
            (yyval.create_table_node) = create_table_node;
        }
#line 1878 "y.tab.c"
    break;

  case 20: /* drop_table_statement: DROP TABLE table end  */
#line 288 "sql.y"
        {
            DropTableNode *drop_table_node = instance(DropTableNode);
            drop_table_node->table_name = (yyvsp[-1].strVal);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1888 "y.tab.c"
    break;

  case 21: /* select_statement: SELECT selection table_exp end  */
#line 297 "sql.y"
        {
            SelectNode *select_node = instance(SelectNode);
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1899 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table values_or_query_spec end  */
#line 307 "sql.y"
        {
            InsertNode *node = instance(InsertNode);
            node->all_column = true;
            node->table_name = (yyvsp[-2].strVal);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1911 "y.tab.c"
    break;

  case 23: /* insert_statement: INSERT INTO table '(' columns ')' values_or_query_spec end  */
#line 315 "sql.y"
        {
            InsertNode *node = instance(InsertNode);
            node->all_column = false;
            node->table_name = (yyvsp[-5].strVal);
            node->column_list = (yyvsp[-3].list);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1924 "y.tab.c"
    break;

  case 24: /* update_statement: UPDATE table SET assignments opt_where_clause end  */
#line 327 "sql.y"
        {
            UpdateNode *node = instance(UpdateNode);
            node->table_name = (yyvsp[-4].strVal);
            node->assignment_list = (yyvsp[-2].list);
            node->where_clause = (yyvsp[-1].where_clause_node);
            (yyval.update_node) = node;
        }
#line 1936 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table end  */
#line 338 "sql.y"
        {
            DeleteNode *node = instance(DeleteNode);
            node->table_name = (yyvsp[-1].strVal);
            (yyval.delete_node) = node;
        }
#line 1946 "y.tab.c"
    break;

  case 26: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 344 "sql.y"
        {
            DeleteNode *node = instance(DeleteNode);
            node->table_name = (yyvsp[-3].strVal);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1957 "y.tab.c"
    break;

  case 27: /* describe_statement: DESCRIBE table end  */
#line 354 "sql.y"
        {
            DescribeNode *node = instance(DescribeNode);
            node->table_name = (yyvsp[-1].strVal);
            (yyval.describe_node) = node;
        }
#line 1967 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW TABLES end  */
#line 363 "sql.y"
        {
            ShowNode *node = instance(ShowNode);   
            node->type = SHOW_TABLES;
            (yyval.show_node) = node;
        }
#line 1977 "y.tab.c"
    break;

  case 29: /* show_statement: SHOW MEMORY end  */
#line 369 "sql.y"
        {
            ShowNode *node = instance(ShowNode);   
            node->type = SHOW_MEMORY;
            (yyval.show_node) = node;
        }
#line 1987 "y.tab.c"
    break;

  case 30: /* alter_table_statement: ALTER TABLE table alter_table_action end  */
#line 378 "sql.y"
        {
            (yyval.alter_table_node) = instance(AlterTableNode);
            (yyval.alter_table_node)->table_name = (yyvsp[-2].strVal);
            (yyval.alter_table_node)->action = (yyvsp[-1].alter_table_action);
        }
#line 1997 "y.tab.c"
    break;

  case 31: /* alter_table_action: add_column_def  */
#line 386 "sql.y"
        {
            AlterTableAction *action = instance(AlterTableAction);
            action->type = ALTER_TO_ADD_COLUMN;
            action->action.add_column = (yyvsp[0].add_column_def);
            (yyval.alter_table_action) = action;
        }
#line 2008 "y.tab.c"
    break;

  case 32: /* alter_table_action: drop_column_def  */
#line 393 "sql.y"
        {
            AlterTableAction *action = instance(AlterTableAction);
            action->type = ALTER_TO_DROP_COLUMN;
            action->action.drop_column = (yyvsp[0].drop_column_def);
            (yyval.alter_table_action) = action;
        }
#line 2019 "y.tab.c"
    break;

  case 33: /* add_column_def: ADD COLUMN column_def column_position_def  */
#line 402 "sql.y"
        {
            AddColumnDef *node = instance(AddColumnDef);
            node->column_def = (yyvsp[-1].column_def_node);
            node->position_def = (yyvsp[0].column_position_def);
            (yyval.add_column_def) = node;
        }
#line 2030 "y.tab.c"
    break;

  case 34: /* drop_column_def: DROP COLUMN IDENTIFIER  */
#line 411 "sql.y"
        {
            DropColumnDef *node = instance(DropColumnDef);
            node->column_name = (yyvsp[0].strVal);
            (yyval.drop_column_def) = node;
        }
#line 2040 "y.tab.c"
    break;

  case 35: /* column_position_def: %empty  */
#line 419 "sql.y"
    {
        (yyval.column_position_def) = NULL;
    }
#line 2048 "y.tab.c"
    break;

  case 36: /* column_position_def: BEFORE IDENTIFIER  */
#line 423 "sql.y"
        {
            ColumnPositionDef *pos = instance(ColumnPositionDef);
            pos->type = POS_BEFORE;
            pos->column = (yyvsp[0].strVal);
            (yyval.column_position_def) = pos;
        }
#line 2059 "y.tab.c"
    break;

  case 37: /* column_position_def: AFTER IDENTIFIER  */
#line 430 "sql.y"
        {
            ColumnPositionDef *pos = instance(ColumnPositionDef);
            pos->type = POS_AFTER;
            pos->column = (yyvsp[0].strVal);
            (yyval.column_position_def) = pos;
        }
#line 2070 "y.tab.c"
    break;

  case 38: /* selection: scalar_exp_commalist  */
#line 439 "sql.y"
        {
            SelectionNode *selection_node = instance(SelectionNode);
            selection_node->all_column = false;
            selection_node->scalar_exp_list = (yyvsp[0].list);
            (yyval.selection_node) = selection_node;
        }
#line 2081 "y.tab.c"
    break;

  case 39: /* selection: '*'  */
#line 446 "sql.y"
        {
            SelectionNode *selection_node = instance(SelectionNode);
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 2091 "y.tab.c"
    break;

  case 40: /* table_exp: from_clause opt_where_clause limit_clause  */
#line 454 "sql.y"
        {
            TableExpNode *table_exp = instance(TableExpNode);
            table_exp->from_clause = (yyvsp[-2].from_clause_node);
            table_exp->where_clause = (yyvsp[-1].where_clause_node);
            table_exp->limit_clause = (yyvsp[0].limit_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 2103 "y.tab.c"
    break;

  case 41: /* from_clause: %empty  */
#line 464 "sql.y"
        {
            (yyval.from_clause_node) = NULL;
        }
#line 2111 "y.tab.c"
    break;

  case 42: /* from_clause: FROM table_ref_commalist  */
#line 468 "sql.y"
        {
            FromClauseNode *from_clause = instance(FromClauseNode);
            from_clause->from = (yyvsp[0].list);
            (yyval.from_clause_node) = from_clause;
        }
#line 2121 "y.tab.c"
    break;

  case 43: /* table_ref_commalist: table_ref  */
#line 476 "sql.y"
        {
            List *list = create_list(NODE_TABLE_REFER);
            append_list(list, (yyvsp[0].table_ref_node));
            (yyval.list) = list;
        }
#line 2131 "y.tab.c"
    break;

  case 44: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 482 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].table_ref_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2140 "y.tab.c"
    break;

  case 45: /* table_ref: table  */
#line 489 "sql.y"
        {
            TableRefNode *table_ref = instance(TableRefNode);
            table_ref->table = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2150 "y.tab.c"
    break;

  case 46: /* table_ref: table range_variable  */
#line 495 "sql.y"
        {
            TableRefNode *table_ref = instance(TableRefNode);
            table_ref->table = (yyvsp[-1].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2161 "y.tab.c"
    break;

  case 47: /* table_ref: table AS range_variable  */
#line 502 "sql.y"
        {
            TableRefNode *table_ref = instance(TableRefNode);
            table_ref->table = (yyvsp[-2].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2172 "y.tab.c"
    break;

  case 48: /* table: IDENTIFIER  */
#line 511 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2180 "y.tab.c"
    break;

  case 49: /* range_variable: IDENTIFIER  */
#line 517 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2188 "y.tab.c"
    break;

  case 50: /* opt_where_clause: %empty  */
#line 523 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 2196 "y.tab.c"
    break;

  case 51: /* opt_where_clause: where_clause  */
#line 527 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 2204 "y.tab.c"
    break;

  case 52: /* where_clause: WHERE condition  */
#line 533 "sql.y"
        {
            WhereClauseNode *where_clause_node = instance(WhereClauseNode);
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 2214 "y.tab.c"
    break;

  case 53: /* values_or_query_spec: VALUES opt_values  */
#line 541 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = instance(ValuesOrQuerySpecNode);
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = (yyvsp[0].list);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2225 "y.tab.c"
    break;

  case 54: /* values_or_query_spec: query_spec  */
#line 548 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = instance(ValuesOrQuerySpecNode);
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = (yyvsp[0].query_spec_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2236 "y.tab.c"
    break;

  case 55: /* opt_values: '(' value_items ')'  */
#line 557 "sql.y"
        {
            (yyval.list) = create_list(NODE_LIST);
            append_list((yyval.list), (yyvsp[-1].list));
        }
#line 2245 "y.tab.c"
    break;

  case 56: /* opt_values: opt_values ',' '(' value_items ')'  */
#line 562 "sql.y"
        {
            (yyval.list) = (yyvsp[-4].list);
            append_list((yyval.list), (yyvsp[-1].list));
        }
#line 2254 "y.tab.c"
    break;

  case 57: /* query_spec: SELECT selection table_exp  */
#line 569 "sql.y"
        {
            QuerySpecNode *query_spec = instance(QuerySpecNode);
            query_spec->selection = (yyvsp[-1].selection_node);
            query_spec->table_exp = (yyvsp[0].table_exp_node);
            (yyval.query_spec_node) = query_spec;
        }
#line 2265 "y.tab.c"
    break;

  case 58: /* scalar_exp_commalist: scalar_exp  */
#line 578 "sql.y"
        {
            List *scalar_exp_list = create_list(NODE_SCALAR_EXP);
            append_list(scalar_exp_list, (yyvsp[0].scalar_exp_node));
            (yyval.list) = scalar_exp_list;
        }
#line 2275 "y.tab.c"
    break;

  case 59: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 584 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].scalar_exp_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2284 "y.tab.c"
    break;

  case 60: /* scalar_exp: calculate  */
#line 591 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2295 "y.tab.c"
    break;

  case 61: /* scalar_exp: column  */
#line 598 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2306 "y.tab.c"
    break;

  case 62: /* scalar_exp: function  */
#line 605 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2317 "y.tab.c"
    break;

  case 63: /* scalar_exp: value_item  */
#line 612 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2328 "y.tab.c"
    break;

  case 64: /* scalar_exp: '(' scalar_exp ')'  */
#line 619 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2336 "y.tab.c"
    break;

  case 65: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 623 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].strVal);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2345 "y.tab.c"
    break;

  case 66: /* calculate: scalar_exp '+' scalar_exp  */
#line 630 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2357 "y.tab.c"
    break;

  case 67: /* calculate: scalar_exp '-' scalar_exp  */
#line 638 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2369 "y.tab.c"
    break;

  case 68: /* calculate: scalar_exp '*' scalar_exp  */
#line 646 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2381 "y.tab.c"
    break;

  case 69: /* calculate: scalar_exp '/' scalar_exp  */
#line 654 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2393 "y.tab.c"
    break;

  case 70: /* columns: column  */
#line 664 "sql.y"
        {
            List *column_set_node = create_list(NODE_COLUMN);
            append_list(column_set_node, (yyvsp[0].column_node));
            (yyval.list) = column_set_node;
        }
#line 2403 "y.tab.c"
    break;

  case 71: /* columns: columns ',' column  */
#line 670 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].column_node));
        }
#line 2412 "y.tab.c"
    break;

  case 72: /* base_table_element_commalist: base_table_element  */
#line 677 "sql.y"
        {
            List *base_table_element_commalist = create_list(NODE_BASE_TABLE_ELEMENT);
            append_list(base_table_element_commalist, (yyvsp[0].base_table_element));
            (yyval.list) = base_table_element_commalist;
        }
#line 2422 "y.tab.c"
    break;

  case 73: /* base_table_element_commalist: base_table_element_commalist ',' base_table_element  */
#line 683 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].base_table_element));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2431 "y.tab.c"
    break;

  case 74: /* base_table_element: column_def  */
#line 690 "sql.y"
        {
            BaseTableElementNode *node = instance(BaseTableElementNode);
            node->column_def = (yyvsp[0].column_def_node);
            node->table_contraint_def = NULL;
            node->type = TELE_COLUMN_DEF;
            (yyval.base_table_element) = node;
        }
#line 2443 "y.tab.c"
    break;

  case 75: /* base_table_element: table_contraint_def  */
#line 698 "sql.y"
        {
            BaseTableElementNode *node = instance(BaseTableElementNode);
            node->column_def = NULL;
            node->table_contraint_def = (yyvsp[0].table_contraint_def);
            node->type = TELE_TABLE_CONTRAINT_DEF;
            (yyval.base_table_element) = node;
        }
#line 2455 "y.tab.c"
    break;

  case 76: /* column_def: column_def_name data_type array_dim_clause column_def_opt_list  */
#line 721 "sql.y"
        {
            ColumnDefNode *column_def = instance(ColumnDefNode);
            column_def->column = (yyvsp[-3].column_def_name);
            column_def->data_type = (yyvsp[-2].data_type_node);
            column_def->array_dim = (yyvsp[-1].intVal);
            column_def->column_def_opt_list = (yyvsp[0].list);
            (yyval.column_def_node) = column_def;
        }
#line 2468 "y.tab.c"
    break;

  case 77: /* column_def_name_commalist: column_def_name  */
#line 732 "sql.y"
        {
            List *list = create_list(NODE_COLUMN_DEF_NAME);
            append_list(list, (yyvsp[0].column_def_name));
            (yyval.list) = list;
        }
#line 2478 "y.tab.c"
    break;

  case 78: /* column_def_name_commalist: column_def_name_commalist ',' column_def_name  */
#line 738 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].column_def_name));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2487 "y.tab.c"
    break;

  case 79: /* column_def_name: IDENTIFIER  */
#line 745 "sql.y"
        {
            ColumnDefName *column_def_name = instance(ColumnDefName);
            column_def_name->column = (yyvsp[0].strVal);
            (yyval.column_def_name) = column_def_name;
        }
#line 2497 "y.tab.c"
    break;

  case 80: /* data_type: INT  */
#line 753 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_INT; 
            (yyval.data_type_node) = node;
        }
#line 2507 "y.tab.c"
    break;

  case 81: /* data_type: LONG  */
#line 759 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_LONG;  
            (yyval.data_type_node) = node;
        }
#line 2517 "y.tab.c"
    break;

  case 82: /* data_type: CHAR  */
#line 765 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_CHAR; 
            (yyval.data_type_node) = node;
        }
#line 2527 "y.tab.c"
    break;

  case 83: /* data_type: VARCHAR '(' INTVALUE ')'  */
#line 771 "sql.y"
        {
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_VARCHAR; 
            node->len = (yyvsp[-1].intVal);
            (yyval.data_type_node) = node;
        }
#line 2538 "y.tab.c"
    break;

  case 84: /* data_type: STRING  */
#line 778 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_STRING; 
            (yyval.data_type_node) = node;
        }
#line 2548 "y.tab.c"
    break;

  case 85: /* data_type: BOOL  */
#line 784 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_BOOL; 
            (yyval.data_type_node) = node;
        }
#line 2558 "y.tab.c"
    break;

  case 86: /* data_type: FLOAT  */
#line 790 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_FLOAT; 
            (yyval.data_type_node) = node;
        }
#line 2568 "y.tab.c"
    break;

  case 87: /* data_type: DOUBLE  */
#line 796 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_DOUBLE; 
            (yyval.data_type_node) = node;
        }
#line 2578 "y.tab.c"
    break;

  case 88: /* data_type: TIMESTAMP  */
#line 802 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_TIMESTAMP; 
            (yyval.data_type_node) = node;
        }
#line 2588 "y.tab.c"
    break;

  case 89: /* data_type: DATE  */
#line 808 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_DATE; 
            (yyval.data_type_node) = node;
        }
#line 2598 "y.tab.c"
    break;

  case 90: /* data_type: table  */
#line 814 "sql.y"
        {
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_REFERENCE;
            node->table_name = (yyvsp[0].strVal);
            (yyval.data_type_node) = node;
        }
#line 2609 "y.tab.c"
    break;

  case 91: /* array_dim_clause: %empty  */
#line 823 "sql.y"
        {
            (yyval.intVal) = 0;
        }
#line 2617 "y.tab.c"
    break;

  case 92: /* array_dim_clause: '[' ']'  */
#line 827 "sql.y"
        {
            (yyval.intVal) = 1;
        }
#line 2625 "y.tab.c"
    break;

  case 93: /* array_dim_clause: array_dim_clause '[' ']'  */
#line 831 "sql.y"
        {
            (yyval.intVal)++;
        }
#line 2633 "y.tab.c"
    break;

  case 94: /* column_def_opt_list: %empty  */
#line 837 "sql.y"
        {
            (yyval.list) = NULL;
        }
#line 2641 "y.tab.c"
    break;

  case 95: /* column_def_opt_list: column_def_opt  */
#line 841 "sql.y"
        {
            (yyval.list) = create_list(NODE_COLUMN_DEF_OPT);
            append_list((yyval.list), (yyvsp[0].column_def_opt));
        }
#line 2650 "y.tab.c"
    break;

  case 96: /* column_def_opt_list: column_def_opt_list column_def_opt  */
#line 846 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].column_def_opt));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 2659 "y.tab.c"
    break;

  case 97: /* column_def_opt: NOT NULLX  */
#line 853 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_NOT_NULL; 
            (yyval.column_def_opt) = node;
        }
#line 2669 "y.tab.c"
    break;

  case 98: /* column_def_opt: UNIQUE  */
#line 859 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_UNIQUE; 
            (yyval.column_def_opt) = node;
        }
#line 2679 "y.tab.c"
    break;

  case 99: /* column_def_opt: PRIMARY KEY  */
#line 865 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_PRIMARY_KEY; 
            (yyval.column_def_opt) = node;
        }
#line 2689 "y.tab.c"
    break;

  case 100: /* column_def_opt: DEFAULT value_item  */
#line 871 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_DEFAULT_VALUE;
            node->value = (yyvsp[0].value_item_node);
            (yyval.column_def_opt) = node;
        }
#line 2700 "y.tab.c"
    break;

  case 101: /* column_def_opt: DEFAULT NULLX  */
#line 878 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_DEFAULT_NULL;
            (yyval.column_def_opt) = node;
        }
#line 2710 "y.tab.c"
    break;

  case 102: /* column_def_opt: COMMENT STRINGVALUE  */
#line 884 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_COMMENT;
            node->comment = (yyvsp[0].strVal);
            (yyval.column_def_opt) = node;
        }
#line 2721 "y.tab.c"
    break;

  case 103: /* column_def_opt: CHECK '(' condition ')'  */
#line 891 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_CHECK_CONDITION;
            node->condition = (yyvsp[-1].condition_node);
            (yyval.column_def_opt) = node;
        }
#line 2732 "y.tab.c"
    break;

  case 104: /* column_def_opt: REFERENCES table  */
#line 898 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_REFERENECS;
            node->refer_table = (yyvsp[0].strVal);
            (yyval.column_def_opt) = node;
        }
#line 2743 "y.tab.c"
    break;

  case 105: /* table_contraint_def: UNIQUE '(' column_def_name_commalist ')'  */
#line 907 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_UNIQUE;
            node->column_commalist = (yyvsp[-1].list);
            (yyval.table_contraint_def) = node;
        }
#line 2754 "y.tab.c"
    break;

  case 106: /* table_contraint_def: PRIMARY KEY '(' column_def_name_commalist ')'  */
#line 914 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_PRIMARY_KEY;
            node->column_commalist = (yyvsp[-1].list);
            (yyval.table_contraint_def) = node;
        }
#line 2765 "y.tab.c"
    break;

  case 107: /* table_contraint_def: FOREIGN KEY '(' column_def_name_commalist ')' REFERENCES table  */
#line 921 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_FOREIGN_KEY;
            node->column_commalist = (yyvsp[-3].list);
            node->table = (yyvsp[0].strVal);
            (yyval.table_contraint_def) = node;
        }
#line 2777 "y.tab.c"
    break;

  case 108: /* table_contraint_def: CHECK '(' condition ')'  */
#line 929 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_CHECK;
            node->condition = (yyvsp[-1].condition_node);
            (yyval.table_contraint_def) = node;
        }
#line 2788 "y.tab.c"
    break;

  case 109: /* column: IDENTIFIER  */
#line 938 "sql.y"
        {
            ColumnNode *column_node = instance(ColumnNode);
            column_node->column_name = (yyvsp[0].strVal);
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2799 "y.tab.c"
    break;

  case 110: /* column: '(' IDENTIFIER ')' '.' column  */
#line 945 "sql.y"
        {
            ColumnNode *column_node = instance(ColumnNode);
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->sub_column = (yyvsp[0].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2811 "y.tab.c"
    break;

  case 111: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 953 "sql.y"
        {
            ColumnNode *column_node = instance(ColumnNode);
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->scalar_exp_list = (yyvsp[-1].list);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2823 "y.tab.c"
    break;

  case 112: /* column: IDENTIFIER '.' column  */
#line 961 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = (yyvsp[-2].strVal);
        }
#line 2832 "y.tab.c"
    break;

  case 113: /* value_items: value_item  */
#line 968 "sql.y"
        {
            List *value_list = create_list(NODE_VALUE_ITEM);
            append_list(value_list, (yyvsp[0].value_item_node));
            (yyval.list) = value_list;
        }
#line 2842 "y.tab.c"
    break;

  case 114: /* value_items: value_items ',' value_item  */
#line 974 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].value_item_node));
        }
#line 2851 "y.tab.c"
    break;

  case 115: /* value_item: atom  */
#line 981 "sql.y"
        {
            ValueItemNode *node = instance(ValueItemNode);
            node->type = V_ATOM;
            node->value.atom = (yyvsp[0].atom_node);
            (yyval.value_item_node) = node;
        }
#line 2862 "y.tab.c"
    break;

  case 116: /* value_item: NULLX  */
#line 988 "sql.y"
        {
            ValueItemNode *node = instance(ValueItemNode);
            node->type = V_NULL;
            (yyval.value_item_node) = node;
        }
#line 2872 "y.tab.c"
    break;

  case 117: /* value_item: '[' value_items ']'  */
#line 994 "sql.y"
        {
            ValueItemNode *node = instance(ValueItemNode);
            node->type = V_ARRAY;
            node->value.value_list = (yyvsp[-1].list);
            (yyval.value_item_node) = node;
        }
#line 2883 "y.tab.c"
    break;

  case 118: /* atom: INTVALUE  */
#line 1003 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.intval = (yyvsp[0].intVal);
            node->type = A_INT;
            (yyval.atom_node) = node;
        }
#line 2894 "y.tab.c"
    break;

  case 119: /* atom: BOOLVALUE  */
#line 1010 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.boolval = (yyvsp[0].boolVal);
            node->type = A_BOOL;
            (yyval.atom_node) = node;
        }
#line 2905 "y.tab.c"
    break;

  case 120: /* atom: STRINGVALUE  */
#line 1017 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.strval = (yyvsp[0].strVal);
            node->type = A_STRING;
            (yyval.atom_node) = node;
        }
#line 2916 "y.tab.c"
    break;

  case 121: /* atom: FLOATVALUE  */
#line 1024 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.floatval = (yyvsp[0].floatVal);
            node->type = A_FLOAT;
            (yyval.atom_node) = node;
        }
#line 2927 "y.tab.c"
    break;

  case 122: /* atom: REFERVALUE  */
#line 1031 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.referval = (yyvsp[0].referVal);
            node->type = A_REFERENCE;
            (yyval.atom_node) = node;
        }
#line 2938 "y.tab.c"
    break;

  case 123: /* REFERVALUE: '(' value_items ')'  */
#line 1041 "sql.y"
        {
            ReferValue *refer = instance(ReferValue);
            refer->type = DIRECTLY;
            refer->nest_value_list = (yyvsp[-1].list);
            (yyval.referVal) = refer;
        }
#line 2949 "y.tab.c"
    break;

  case 124: /* REFERVALUE: REF '(' condition ')'  */
#line 1049 "sql.y"
        {
            ReferValue *refer = instance(ReferValue);
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.referVal) = refer;
        }
#line 2960 "y.tab.c"
    break;

  case 125: /* BOOLVALUE: TRUE  */
#line 1058 "sql.y"
        {
            (yyval.boolVal) = true;
        }
#line 2968 "y.tab.c"
    break;

  case 126: /* BOOLVALUE: FALSE  */
#line 1062 "sql.y"
        {
            (yyval.boolVal) = false;
        }
#line 2976 "y.tab.c"
    break;

  case 127: /* assignments: assignment  */
#line 1068 "sql.y"
        {
            List *list = create_list(NODE_ASSIGNMENT);
            append_list(list, (yyvsp[0].assignment_node));
            (yyval.list) = list;
        }
#line 2986 "y.tab.c"
    break;

  case 128: /* assignments: assignments ',' assignment  */
#line 1074 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].assignment_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2995 "y.tab.c"
    break;

  case 129: /* assignment: column EQ value_item  */
#line 1081 "sql.y"
        {
            AssignmentNode *node = instance(AssignmentNode);
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 3006 "y.tab.c"
    break;

  case 130: /* condition: condition OR condition  */
#line 1090 "sql.y"
        {
            ConditionNode *condition = instance(ConditionNode);
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 3018 "y.tab.c"
    break;

  case 131: /* condition: condition AND condition  */
#line 1098 "sql.y"
        {
            ConditionNode *condition = instance(ConditionNode);
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 3030 "y.tab.c"
    break;

  case 132: /* condition: '(' condition ')'  */
#line 1106 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 3038 "y.tab.c"
    break;

  case 133: /* condition: predicate  */
#line 1110 "sql.y"
        {
            ConditionNode *condition = instance(ConditionNode);
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 3049 "y.tab.c"
    break;

  case 134: /* predicate: comparison_predicate  */
#line 1119 "sql.y"
        {
            PredicateNode *predicate = instance(PredicateNode);
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 3060 "y.tab.c"
    break;

  case 135: /* predicate: like_predicate  */
#line 1126 "sql.y"
        {
            PredicateNode *predicate = instance(PredicateNode);
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 3071 "y.tab.c"
    break;

  case 136: /* predicate: in_predicate  */
#line 1133 "sql.y"
        {
            PredicateNode *predicate = instance(PredicateNode);
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 3082 "y.tab.c"
    break;

  case 137: /* comparison_predicate: column compare scalar_exp  */
#line 1142 "sql.y"
        {
            ComparisonNode *comparison_node = instance(ComparisonNode);
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 3094 "y.tab.c"
    break;

  case 138: /* like_predicate: column LIKE value_item  */
#line 1152 "sql.y"
        {
            LikeNode *like_node = instance(LikeNode);
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 3105 "y.tab.c"
    break;

  case 139: /* in_predicate: column IN '(' value_items ')'  */
#line 1161 "sql.y"
        {
            InNode *in_node = instance(InNode);
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_list = (yyvsp[-1].list);
            (yyval.in_node) = in_node;
        }
#line 3116 "y.tab.c"
    break;

  case 140: /* limit_clause: %empty  */
#line 1170 "sql.y"
        {
            (yyval.limit_clause_node) = NULL;
        }
#line 3124 "y.tab.c"
    break;

  case 141: /* limit_clause: LIMIT INTVALUE  */
#line 1174 "sql.y"
        {
            LimitClauseNode *node = instance(LimitClauseNode);
            node->offset = 0;
            node->rows = (yyvsp[0].intVal);
            (yyval.limit_clause_node) = node;
        }
#line 3135 "y.tab.c"
    break;

  case 142: /* limit_clause: LIMIT INTVALUE ',' INTVALUE  */
#line 1181 "sql.y"
        {
            LimitClauseNode *node = instance(LimitClauseNode);
            node->offset = (yyvsp[-2].intVal);
            node->rows = (yyvsp[0].intVal);
            (yyval.limit_clause_node) = node;
        }
#line 3146 "y.tab.c"
    break;

  case 143: /* limit_clause: LIMIT INTVALUE OFFSET INTVALUE  */
#line 1188 "sql.y"
        {
            LimitClauseNode *node = instance(LimitClauseNode);
            node->rows = (yyvsp[-2].intVal);
            node->offset = (yyvsp[0].intVal);
            (yyval.limit_clause_node) = node;
        }
#line 3157 "y.tab.c"
    break;

  case 144: /* compare: EQ  */
#line 1196 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 3163 "y.tab.c"
    break;

  case 145: /* compare: NE  */
#line 1197 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 3169 "y.tab.c"
    break;

  case 146: /* compare: GT  */
#line 1198 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 3175 "y.tab.c"
    break;

  case 147: /* compare: GE  */
#line 1199 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 3181 "y.tab.c"
    break;

  case 148: /* compare: LT  */
#line 1200 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 3187 "y.tab.c"
    break;

  case 149: /* compare: LE  */
#line 1201 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 3193 "y.tab.c"
    break;

  case 150: /* function: MAX '(' non_all_function_value ')'  */
#line 1205 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3204 "y.tab.c"
    break;

  case 151: /* function: MIN '(' non_all_function_value ')'  */
#line 1212 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3215 "y.tab.c"
    break;

  case 152: /* function: COUNT '(' function_value ')'  */
#line 1219 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3226 "y.tab.c"
    break;

  case 153: /* function: SUM '(' function_value ')'  */
#line 1226 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3237 "y.tab.c"
    break;

  case 154: /* function: AVG '(' function_value ')'  */
#line 1233 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3248 "y.tab.c"
    break;

  case 155: /* function_value: INTVALUE  */
#line 1242 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3259 "y.tab.c"
    break;

  case 156: /* function_value: column  */
#line 1249 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3270 "y.tab.c"
    break;

  case 157: /* function_value: '*'  */
#line 1256 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 3280 "y.tab.c"
    break;

  case 158: /* non_all_function_value: INTVALUE  */
#line 1264 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3291 "y.tab.c"
    break;

  case 159: /* non_all_function_value: column  */
#line 1271 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3302 "y.tab.c"
    break;


#line 3306 "y.tab.c"

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

#line 1282 "sql.y"

