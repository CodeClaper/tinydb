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
    COMMENT = 297,                 /* COMMENT  */
    CHAR = 298,                    /* CHAR  */
    INT = 299,                     /* INT  */
    LONG = 300,                    /* LONG  */
    VARCHAR = 301,                 /* VARCHAR  */
    STRING = 302,                  /* STRING  */
    BOOL = 303,                    /* BOOL  */
    FLOAT = 304,                   /* FLOAT  */
    DOUBLE = 305,                  /* DOUBLE  */
    DATE = 306,                    /* DATE  */
    TIMESTAMP = 307,               /* TIMESTAMP  */
    EQ = 308,                      /* EQ  */
    NE = 309,                      /* NE  */
    GT = 310,                      /* GT  */
    GE = 311,                      /* GE  */
    LT = 312,                      /* LT  */
    LE = 313,                      /* LE  */
    IN = 314,                      /* IN  */
    LIKE = 315,                    /* LIKE  */
    NOT = 316,                     /* NOT  */
    ALTER = 317,                   /* ALTER  */
    COLUMN = 318,                  /* COLUMN  */
    ADD = 319,                     /* ADD  */
    CHANGE = 320,                  /* CHANGE  */
    BEFORE = 321,                  /* BEFORE  */
    AFTER = 322,                   /* AFTER  */
    SYSTEM = 323,                  /* SYSTEM  */
    CONFIG = 324,                  /* CONFIG  */
    MEMORY = 325,                  /* MEMORY  */
    IDENTIFIER = 326,              /* IDENTIFIER  */
    INTVALUE = 327,                /* INTVALUE  */
    FLOATVALUE = 328,              /* FLOATVALUE  */
    STRINGVALUE = 329              /* STRINGVALUE  */
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
#define COMMENT 297
#define CHAR 298
#define INT 299
#define LONG 300
#define VARCHAR 301
#define STRING 302
#define BOOL 303
#define FLOAT 304
#define DOUBLE 305
#define DATE 306
#define TIMESTAMP 307
#define EQ 308
#define NE 309
#define GT 310
#define GE 311
#define LT 312
#define LE 313
#define IN 314
#define LIKE 315
#define NOT 316
#define ALTER 317
#define COLUMN 318
#define ADD 319
#define CHANGE 320
#define BEFORE 321
#define AFTER 322
#define SYSTEM 323
#define CONFIG 324
#define MEMORY 325
#define IDENTIFIER 326
#define INTVALUE 327
#define FLOATVALUE 328
#define STRINGVALUE 329

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
   LimitNode                    *limit_node;
   TableRefNode                 *table_ref_node;
   QuerySpecNode                *query_spec_node;
   ValuesOrQuerySpecNode        *values_or_query_spec_node;
   FromClauseNode               *from_clause_node;
   WhereClauseNode              *where_clause_node;
   TableExpNode                 *table_exp_node; 
   AddColumnDef                 *add_column_def;
   DropColumnDef                *drop_column_def;
   ChangeColumnDef              *change_column_def;
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

#line 343 "y.tab.c"

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
  YYSYMBOL_SHOW = 31,                      /* SHOW  */
  YYSYMBOL_TABLES = 32,                    /* TABLES  */
  YYSYMBOL_PRIMARY = 33,                   /* PRIMARY  */
  YYSYMBOL_KEY = 34,                       /* KEY  */
  YYSYMBOL_UNIQUE = 35,                    /* UNIQUE  */
  YYSYMBOL_DEFAULT = 36,                   /* DEFAULT  */
  YYSYMBOL_CHECK = 37,                     /* CHECK  */
  YYSYMBOL_REFERENCES = 38,                /* REFERENCES  */
  YYSYMBOL_FOREIGN = 39,                   /* FOREIGN  */
  YYSYMBOL_MAX = 40,                       /* MAX  */
  YYSYMBOL_MIN = 41,                       /* MIN  */
  YYSYMBOL_COUNT = 42,                     /* COUNT  */
  YYSYMBOL_SUM = 43,                       /* SUM  */
  YYSYMBOL_AVG = 44,                       /* AVG  */
  YYSYMBOL_REF = 45,                       /* REF  */
  YYSYMBOL_TRUE = 46,                      /* TRUE  */
  YYSYMBOL_FALSE = 47,                     /* FALSE  */
  YYSYMBOL_NULLX = 48,                     /* NULLX  */
  YYSYMBOL_AS = 49,                        /* AS  */
  YYSYMBOL_COMMENT = 50,                   /* COMMENT  */
  YYSYMBOL_CHAR = 51,                      /* CHAR  */
  YYSYMBOL_INT = 52,                       /* INT  */
  YYSYMBOL_LONG = 53,                      /* LONG  */
  YYSYMBOL_VARCHAR = 54,                   /* VARCHAR  */
  YYSYMBOL_STRING = 55,                    /* STRING  */
  YYSYMBOL_BOOL = 56,                      /* BOOL  */
  YYSYMBOL_FLOAT = 57,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 58,                    /* DOUBLE  */
  YYSYMBOL_DATE = 59,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 60,                 /* TIMESTAMP  */
  YYSYMBOL_EQ = 61,                        /* EQ  */
  YYSYMBOL_NE = 62,                        /* NE  */
  YYSYMBOL_GT = 63,                        /* GT  */
  YYSYMBOL_GE = 64,                        /* GE  */
  YYSYMBOL_LT = 65,                        /* LT  */
  YYSYMBOL_LE = 66,                        /* LE  */
  YYSYMBOL_IN = 67,                        /* IN  */
  YYSYMBOL_LIKE = 68,                      /* LIKE  */
  YYSYMBOL_NOT = 69,                       /* NOT  */
  YYSYMBOL_ALTER = 70,                     /* ALTER  */
  YYSYMBOL_COLUMN = 71,                    /* COLUMN  */
  YYSYMBOL_ADD = 72,                       /* ADD  */
  YYSYMBOL_CHANGE = 73,                    /* CHANGE  */
  YYSYMBOL_BEFORE = 74,                    /* BEFORE  */
  YYSYMBOL_AFTER = 75,                     /* AFTER  */
  YYSYMBOL_SYSTEM = 76,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 77,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 78,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 79,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 80,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 81,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 82,               /* STRINGVALUE  */
  YYSYMBOL_83_ = 83,                       /* ','  */
  YYSYMBOL_84_ = 84,                       /* '.'  */
  YYSYMBOL_85_ = 85,                       /* '{'  */
  YYSYMBOL_86_ = 86,                       /* '}'  */
  YYSYMBOL_87_ = 87,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_statements = 89,                /* statements  */
  YYSYMBOL_statement = 90,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 91, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 92, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 93, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 94,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 95,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 96,          /* select_statement  */
  YYSYMBOL_insert_statement = 97,          /* insert_statement  */
  YYSYMBOL_update_statement = 98,          /* update_statement  */
  YYSYMBOL_delete_statement = 99,          /* delete_statement  */
  YYSYMBOL_describe_statement = 100,       /* describe_statement  */
  YYSYMBOL_show_statement = 101,           /* show_statement  */
  YYSYMBOL_alter_table_statement = 102,    /* alter_table_statement  */
  YYSYMBOL_alter_table_action = 103,       /* alter_table_action  */
  YYSYMBOL_add_column_def = 104,           /* add_column_def  */
  YYSYMBOL_drop_column_def = 105,          /* drop_column_def  */
  YYSYMBOL_change_column_def = 106,        /* change_column_def  */
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
  YYSYMBOL_compare = 147,                  /* compare  */
  YYSYMBOL_function = 148,                 /* function  */
  YYSYMBOL_function_value = 149,           /* function_value  */
  YYSYMBOL_non_all_function_value = 150,   /* non_all_function_value  */
  YYSYMBOL_end = 151                       /* end  */
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
#define YYLAST   371

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


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
       9,    10,     7,     5,    83,     6,    84,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    87,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    11,     2,    12,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,    86,     2,     2,     2,     2,
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
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   174,   174,   179,   186,   192,   198,   204,   211,   218,
     225,   232,   239,   246,   253,   260,   269,   272,   275,   279,
     289,   298,   308,   316,   328,   339,   345,   355,   364,   370,
     379,   387,   394,   401,   410,   419,   427,   437,   440,   447,
     456,   463,   471,   481,   484,   492,   498,   505,   511,   518,
     527,   533,   540,   543,   549,   557,   564,   573,   578,   585,
     594,   600,   607,   614,   621,   628,   635,   639,   646,   654,
     662,   670,   680,   686,   693,   699,   706,   714,   737,   748,
     754,   761,   769,   775,   781,   787,   794,   800,   806,   812,
     818,   824,   830,   840,   843,   847,   854,   857,   862,   869,
     875,   881,   887,   894,   900,   907,   914,   923,   930,   937,
     945,   954,   961,   969,   977,   984,   990,   997,  1004,  1010,
    1019,  1026,  1033,  1040,  1047,  1057,  1065,  1074,  1078,  1084,
    1090,  1097,  1106,  1114,  1122,  1126,  1135,  1142,  1149,  1158,
    1168,  1177,  1206,  1207,  1208,  1209,  1210,  1211,  1214,  1221,
    1228,  1235,  1242,  1251,  1258,  1265,  1273,  1280,  1289,  1290
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
  "LIMIT", "SHOW", "TABLES", "PRIMARY", "KEY", "UNIQUE", "DEFAULT",
  "CHECK", "REFERENCES", "FOREIGN", "MAX", "MIN", "COUNT", "SUM", "AVG",
  "REF", "TRUE", "FALSE", "NULLX", "AS", "COMMENT", "CHAR", "INT", "LONG",
  "VARCHAR", "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE", "TIMESTAMP",
  "EQ", "NE", "GT", "GE", "LT", "LE", "IN", "LIKE", "NOT", "ALTER",
  "COLUMN", "ADD", "CHANGE", "BEFORE", "AFTER", "SYSTEM", "CONFIG",
  "MEMORY", "IDENTIFIER", "INTVALUE", "FLOATVALUE", "STRINGVALUE", "','",
  "'.'", "'{'", "'}'", "';'", "$accept", "statements", "statement",
  "begin_transaction_statement", "commit_transaction_statement",
  "rollback_transaction_statement", "create_table_statement",
  "drop_table_statement", "select_statement", "insert_statement",
  "update_statement", "delete_statement", "describe_statement",
  "show_statement", "alter_table_statement", "alter_table_action",
  "add_column_def", "drop_column_def", "change_column_def",
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
  "compare", "function", "function_value", "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-116)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     268,   -52,   -52,   -52,    17,    24,   177,    36,   -24,    55,
     -24,   -21,    45,   292,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,    81,  -114,  -114,
    -114,   -24,   -24,  -114,   199,    50,   125,   131,   143,   145,
     150,   155,  -114,  -114,  -114,    92,  -114,  -114,  -114,   147,
      90,   121,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   -24,
    -114,   160,   -24,   -52,   -52,   -52,   -24,  -114,  -114,  -114,
     193,   -52,     3,   186,    20,   126,    50,    38,  -114,    40,
      40,    22,    22,    22,    13,    25,   223,   -24,   -52,   179,
     223,   223,   223,   223,   223,   132,   137,    25,   -20,  -114,
    -114,  -114,    18,   116,  -114,   128,  -114,  -114,    50,  -114,
     134,  -114,  -114,   204,   205,  -114,  -114,  -114,   216,   217,
     218,    43,   263,   158,  -114,  -114,  -114,  -114,  -114,   -23,
     146,  -114,    -2,  -114,    13,  -114,  -114,   121,    19,    19,
     182,   182,  -114,    25,   177,   228,   -52,  -114,   190,   -13,
    -114,    13,  -114,   167,   181,   194,   -52,  -114,  -114,  -114,
     227,   265,   266,   242,  -114,    23,  -114,  -114,   288,  -114,
      25,  -114,   267,  -114,  -114,  -114,  -114,  -114,   195,  -114,
    -114,  -114,  -114,  -114,  -114,   284,    50,   223,    13,    13,
    -114,  -114,   -24,   215,  -114,  -114,   176,    29,  -114,   147,
      50,   212,  -114,    50,    25,   -52,     6,   219,   221,   221,
    -114,   308,   221,    13,   313,   -52,   116,  -114,  -114,  -114,
     323,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   286,  -114,
    -114,    50,  -114,   121,   297,  -114,  -114,  -114,     9,    25,
    -114,    30,   325,  -114,  -114,  -114,  -114,  -114,   107,  -114,
     221,    31,  -114,   245,   221,  -114,  -114,   255,   324,   100,
      32,   -52,  -114,  -114,    50,   258,   270,  -114,    33,  -114,
     221,  -114,    34,   340,  -114,   339,   319,  -114,    62,   345,
     -24,   273,   309,   283,  -114,  -114,  -114,    35,  -114,  -114,
    -114,  -114,   318,  -114,  -114,  -114,  -114,  -114,    13,  -114,
    -114,  -114,  -114,  -114,   -24,   250,  -114,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   158,    16,    17,
      18,     0,     0,    41,     0,     0,     0,     0,     0,     0,
       0,     0,   127,   128,   118,   111,   120,   123,   122,    43,
      40,    60,    62,    63,    65,   117,   124,   121,    64,     0,
      50,     0,     0,     0,     0,     0,     0,     1,     3,   159,
       0,     0,   111,     0,     0,    65,     0,     0,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      28,    29,     0,     0,    20,     0,    66,   125,     0,   119,
       0,   156,   157,     0,     0,   155,   153,   154,     0,     0,
       0,     0,     0,     0,   135,   136,   137,   138,   114,     0,
      44,    45,    47,    21,     0,    42,    53,    61,    68,    69,
      70,    71,    67,     0,     0,     0,     0,    56,     0,    52,
     129,     0,    25,     0,     0,     0,     0,    31,    32,    33,
       0,     0,     0,     0,    81,     0,    74,    76,     0,    77,
       0,   116,     0,   148,   149,   150,   151,   152,     0,   142,
     143,   144,   145,   146,   147,     0,     0,     0,     0,     0,
     126,   113,     0,     0,    51,    48,    54,     0,    72,    43,
       0,    55,    22,     0,     0,     0,     0,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,    84,    82,    83,
       0,    86,    87,    88,    89,    91,    90,    92,    93,   112,
     134,     0,   140,   139,   132,   133,    46,    49,     0,     0,
      59,     0,     0,   131,   130,    24,    26,    35,    37,    36,
       0,     0,    79,     0,     0,    19,    75,     0,     0,    96,
       0,     0,    73,    57,     0,     0,     0,    34,     0,   107,
       0,   110,     0,     0,    94,     0,     0,   100,     0,     0,
       0,     0,     0,    78,    97,   141,    23,     0,    38,    39,
     108,    80,     0,    85,    95,   101,   103,   102,     0,   106,
     104,    99,    98,    58,     0,     0,   109,   105
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,   346,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
     214,   161,  -114,  -114,   169,    -8,   170,   220,  -114,   127,
    -114,  -114,   278,    -9,  -114,  -114,  -114,   152,   -19,  -109,
     -87,  -114,  -114,  -114,    83,  -114,   -65,   -34,   -28,  -114,
    -114,  -114,  -114,   166,  -113,  -114,  -114,  -114,  -114,  -114,
    -114,   118,   291,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   156,   157,   158,   159,   267,
      49,    88,    89,   130,   131,   132,   195,   135,   136,   146,
     201,   147,    50,    51,    52,   197,   165,   166,   167,   251,
     168,   228,   259,   283,   284,   169,    53,    74,    54,    55,
      56,    57,   149,   150,   123,   124,   125,   126,   127,   187,
      58,   118,   113,    28
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    77,    63,    29,    30,   151,    75,    78,   178,   188,
     189,    64,   134,   105,   112,   112,   117,   117,   117,   122,
     128,   196,   121,    70,    71,    73,    93,    94,   144,   115,
     107,   110,   148,   215,   110,    27,   153,   145,   206,   238,
     263,   269,   285,   290,   292,   303,    31,   193,    78,   110,
     109,    96,   121,    32,    98,    60,   122,    65,   102,    76,
      90,    35,    59,   191,    99,   100,   101,    27,    95,   122,
     204,    76,   104,    35,    66,   234,   235,   194,   198,    62,
     171,   137,   138,   139,   140,   141,   122,    85,    86,   133,
     154,   155,    45,    27,    69,    41,    42,    43,    44,   152,
     253,    45,   116,   108,    45,   229,   216,    41,    42,    43,
     296,   275,   239,   108,   270,   108,   270,   270,   108,    45,
     111,   108,    72,   122,   122,   252,    91,    92,    93,    94,
      46,    47,    48,   276,    79,   277,   278,   279,   280,   148,
      80,   268,    46,    47,    48,   272,   143,   202,   122,   160,
     281,   161,    81,   162,    82,   163,   144,   210,   232,    83,
     227,   188,   189,   252,    84,   145,   241,   252,   190,   282,
      95,    87,    78,    90,   262,   243,    85,    86,   233,   188,
     189,   265,   266,   291,    33,   305,    34,    97,    35,   248,
     249,    91,    92,    93,    94,   164,   106,   260,   188,   189,
     119,   120,   103,    78,   134,   230,   245,   246,    34,  -115,
      35,   142,   170,   172,   173,   174,   255,    36,    37,    38,
      39,    40,    41,    42,    43,    44,   175,   176,   177,   192,
     287,    95,    34,   122,    35,    95,    78,   200,   207,    36,
      37,    38,    39,    40,    41,    42,    43,    44,   188,   189,
     297,   203,   208,   188,   189,   271,    45,    46,    47,    48,
     307,   211,   286,    36,    37,    38,    39,    40,    41,    42,
      43,    44,   299,   209,   212,   213,   214,   105,    72,    46,
      47,    48,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    67,   231,   194,   242,   306,   258,   247,    11,
     164,   189,    45,    46,    47,    48,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,   276,   250,   277,   278,
     279,   280,   254,    11,   179,   180,   181,   182,   183,   184,
     185,   186,   257,   281,   264,   273,   274,   288,    12,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   289,
     293,   294,   282,   295,   298,   300,   304,   301,   199,    68,
     240,   236,    12,   237,   129,   261,   302,    60,   256,   205,
     244,   114
};

static const yytype_int16 yycheck[] =
{
       8,    35,    10,     2,     3,    25,    34,    35,   121,     3,
       4,    32,    25,    10,    79,    80,    81,    82,    83,    84,
      85,   134,     9,    31,    32,    34,     7,     8,    19,     7,
      10,     9,    97,    10,     9,    87,    18,    28,   151,    10,
      10,    10,    10,    10,    10,    10,    29,    49,    76,     9,
      12,    59,     9,    29,    62,    79,   121,    78,    66,     9,
      83,    11,    26,    86,    63,    64,    65,    87,    49,   134,
      83,     9,    71,    11,    29,   188,   189,    79,   143,    24,
     108,    90,    91,    92,    93,    94,   151,    84,    85,    88,
      72,    73,    79,    87,    13,    45,    46,    47,    48,    98,
     213,    79,    80,    83,    79,   170,    83,    45,    46,    47,
      48,    11,    83,    83,    83,    83,    83,    83,    83,    79,
      80,    83,    79,   188,   189,   212,     5,     6,     7,     8,
      80,    81,    82,    33,     9,    35,    36,    37,    38,   204,
       9,   250,    80,    81,    82,   254,     9,   146,   213,    33,
      50,    35,     9,    37,     9,    39,    19,   156,   186,     9,
     168,     3,     4,   250,     9,    28,   200,   254,    10,    69,
      49,    24,   200,    83,   239,   203,    84,    85,   187,     3,
       4,    74,    75,   270,     7,   298,     9,    27,    11,   208,
     209,     5,     6,     7,     8,    79,    10,   231,     3,     4,
      82,    83,     9,   231,    25,    10,   205,   206,     9,    83,
      11,    79,    84,    79,    10,    10,   215,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    10,    10,    10,    83,
     264,    49,     9,   298,    11,    49,   264,     9,    71,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     3,     4,
     278,    61,    71,     3,     4,    10,    79,    80,    81,    82,
      10,    34,   261,    40,    41,    42,    43,    44,    45,    46,
      47,    48,   280,    79,     9,     9,    34,    10,    79,    80,
      81,    82,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,     9,    79,    83,   304,    11,    79,    31,
      79,     4,    79,    80,    81,    82,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    33,     9,    35,    36,
      37,    38,     9,    31,    61,    62,    63,    64,    65,    66,
      67,    68,     9,    50,     9,    80,    12,    79,    70,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    79,
      10,    12,    69,    34,     9,    82,    38,    48,   144,    13,
     199,   192,    70,   193,    86,   238,   283,    79,   216,   149,
     204,    80
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    31,    70,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    87,   151,   151,
     151,    29,    29,     7,     9,    11,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    79,    80,    81,    82,   108,
     120,   121,   122,   134,   136,   137,   138,   139,   148,    26,
      79,   113,    24,   113,    32,    78,    29,     0,    90,    13,
     113,   113,    79,   121,   135,   136,     9,   135,   136,     9,
       9,     9,     9,     9,     9,    84,    85,    24,   109,   110,
      83,     5,     6,     7,     8,    49,   113,    27,   113,   151,
     151,   151,   113,     9,   151,    10,    10,    10,    83,    12,
       9,    80,   134,   150,   150,     7,    80,   134,   149,   149,
     149,     9,   134,   142,   143,   144,   145,   146,   134,   120,
     111,   112,   113,   151,    25,   115,   116,   121,   121,   121,
     121,   121,    79,     9,    19,    28,   117,   119,   134,   140,
     141,    25,   151,    18,    72,    73,   103,   104,   105,   106,
      33,    35,    37,    39,    79,   124,   125,   126,   128,   133,
      84,   136,    79,    10,    10,    10,    10,    10,   142,    61,
      62,    63,    64,    65,    66,    67,    68,   147,     3,     4,
      10,    86,    83,    49,    79,   114,   142,   123,   134,   108,
       9,   118,   151,    61,    83,   115,   142,    71,    71,    79,
     151,    34,     9,     9,    34,    10,    83,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   113,   129,   134,
      10,     9,   136,   121,   142,   142,   112,   114,    10,    83,
     109,   135,    83,   136,   141,   151,   151,    79,   126,   126,
       9,   127,   128,   142,     9,   151,   125,     9,    11,   130,
     135,   117,   134,    10,     9,    74,    75,   107,   127,    10,
      83,    10,   127,    80,    12,    11,    33,    35,    36,    37,
      38,    50,    69,   131,   132,    10,   151,   135,    79,    79,
      10,   128,    10,    10,    12,    34,    48,   136,     9,   113,
      82,    48,   132,    10,    38,   142,   113,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    92,    93,    94,
      95,    96,    97,    97,    98,    99,    99,   100,   101,   101,
     102,   103,   103,   103,   104,   105,   106,   107,   107,   107,
     108,   108,   109,   110,   110,   111,   111,   112,   112,   112,
     113,   114,   115,   115,   116,   117,   117,   118,   118,   119,
     120,   120,   121,   121,   121,   121,   121,   121,   122,   122,
     122,   122,   123,   123,   124,   124,   125,   125,   126,   127,
     127,   128,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   130,   130,   130,   131,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   133,
     133,   134,   134,   134,   134,   135,   135,   136,   136,   136,
     137,   137,   137,   137,   137,   138,   138,   139,   139,   140,
     140,   141,   142,   142,   142,   142,   143,   143,   143,   144,
     145,   146,   147,   147,   147,   147,   147,   147,   148,   148,
     148,   148,   148,   149,   149,   149,   150,   150,   151,   151
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     7,
       4,     4,     5,     8,     6,     4,     6,     3,     3,     3,
       5,     1,     1,     1,     4,     3,     3,     0,     2,     2,
       1,     1,     2,     0,     2,     1,     3,     1,     2,     3,
       1,     1,     0,     1,     2,     2,     1,     3,     5,     3,
       1,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     1,     3,     1,     1,     4,     1,
       3,     1,     1,     1,     1,     4,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     3,     0,     1,     2,     2,
       1,     2,     2,     2,     2,     4,     2,     4,     5,     7,
       4,     1,     5,     4,     3,     1,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     4,     1,     1,     1,
       3,     3,     3,     3,     3,     1,     1,     1,     1,     3,
       3,     5,     1,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     2
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
#line 175 "sql.y"
        {
            append_list(states, (yyvsp[0].statement));
            (yyval.list) = states;
        }
#line 1719 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 180 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].statement));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 1728 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 187 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1738 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 193 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1748 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 199 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1758 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 205 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1769 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 212 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1780 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 219 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1791 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 226 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1802 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 233 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1813 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 240 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1824 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 247 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1835 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 254 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1846 "y.tab.c"
    break;

  case 15: /* statement: alter_table_statement  */
#line 261 "sql.y"
        {
            Statement *statement = instance(Statement);
            statement->statement_type = ALTER_TABLE_STMT;
            statement->alter_table_node = (yyvsp[0].alter_table_node);
            (yyval.statement) = statement;
        }
#line 1857 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table '(' base_table_element_commalist ')' end  */
#line 280 "sql.y"
        {
            CreateTableNode *create_table_node = instance(CreateTableNode);
            create_table_node->table_name = (yyvsp[-4].strVal);
            create_table_node->base_table_element_commalist = (yyvsp[-2].list);
            (yyval.create_table_node) = create_table_node;
        }
#line 1868 "y.tab.c"
    break;

  case 20: /* drop_table_statement: DROP TABLE table end  */
#line 290 "sql.y"
        {
            DropTableNode *drop_table_node = instance(DropTableNode);
            drop_table_node->table_name = (yyvsp[-1].strVal);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1878 "y.tab.c"
    break;

  case 21: /* select_statement: SELECT selection table_exp end  */
#line 299 "sql.y"
        {
            SelectNode *select_node = instance(SelectNode);
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1889 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table values_or_query_spec end  */
#line 309 "sql.y"
        {
            InsertNode *node = instance(InsertNode);
            node->all_column = true;
            node->table_name = (yyvsp[-2].strVal);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1901 "y.tab.c"
    break;

  case 23: /* insert_statement: INSERT INTO table '(' columns ')' values_or_query_spec end  */
#line 317 "sql.y"
        {
            InsertNode *node = instance(InsertNode);
            node->all_column = false;
            node->table_name = (yyvsp[-5].strVal);
            node->column_list = (yyvsp[-3].list);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1914 "y.tab.c"
    break;

  case 24: /* update_statement: UPDATE table SET assignments opt_where_clause end  */
#line 329 "sql.y"
        {
            UpdateNode *node = instance(UpdateNode);
            node->table_name = (yyvsp[-4].strVal);
            node->assignment_list = (yyvsp[-2].list);
            node->where_clause = (yyvsp[-1].where_clause_node);
            (yyval.update_node) = node;
        }
#line 1926 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table end  */
#line 340 "sql.y"
        {
            DeleteNode *node = instance(DeleteNode);
            node->table_name = (yyvsp[-1].strVal);
            (yyval.delete_node) = node;
        }
#line 1936 "y.tab.c"
    break;

  case 26: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 346 "sql.y"
        {
            DeleteNode *node = instance(DeleteNode);
            node->table_name = (yyvsp[-3].strVal);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1947 "y.tab.c"
    break;

  case 27: /* describe_statement: DESCRIBE table end  */
#line 356 "sql.y"
        {
            DescribeNode *node = instance(DescribeNode);
            node->table_name = (yyvsp[-1].strVal);
            (yyval.describe_node) = node;
        }
#line 1957 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW TABLES end  */
#line 365 "sql.y"
        {
            ShowNode *node = instance(ShowNode);   
            node->type = SHOW_TABLES;
            (yyval.show_node) = node;
        }
#line 1967 "y.tab.c"
    break;

  case 29: /* show_statement: SHOW MEMORY end  */
#line 371 "sql.y"
        {
            ShowNode *node = instance(ShowNode);   
            node->type = SHOW_MEMORY;
            (yyval.show_node) = node;
        }
#line 1977 "y.tab.c"
    break;

  case 30: /* alter_table_statement: ALTER TABLE table alter_table_action end  */
#line 380 "sql.y"
        {
            (yyval.alter_table_node) = instance(AlterTableNode);
            (yyval.alter_table_node)->table_name = (yyvsp[-2].strVal);
            (yyval.alter_table_node)->action = (yyvsp[-1].alter_table_action);
        }
#line 1987 "y.tab.c"
    break;

  case 31: /* alter_table_action: add_column_def  */
#line 388 "sql.y"
        {
            AlterTableAction *action = instance(AlterTableAction);
            action->type = ALTER_TO_ADD_COLUMN;
            action->action.add_column = (yyvsp[0].add_column_def);
            (yyval.alter_table_action) = action;
        }
#line 1998 "y.tab.c"
    break;

  case 32: /* alter_table_action: drop_column_def  */
#line 395 "sql.y"
        {
            AlterTableAction *action = instance(AlterTableAction);
            action->type = ALTER_TO_DROP_COLUMN;
            action->action.drop_column = (yyvsp[0].drop_column_def);
            (yyval.alter_table_action) = action;
        }
#line 2009 "y.tab.c"
    break;

  case 33: /* alter_table_action: change_column_def  */
#line 402 "sql.y"
        {
            AlterTableAction *action = instance(AlterTableAction);
            action->type = ALTER_TO_CHANGE_COLUMN;
            action->action.change_column = (yyvsp[0].change_column_def);
            (yyval.alter_table_action) = action;
        }
#line 2020 "y.tab.c"
    break;

  case 34: /* add_column_def: ADD COLUMN column_def column_position_def  */
#line 411 "sql.y"
        {
            AddColumnDef *node = instance(AddColumnDef);
            node->column_def = (yyvsp[-1].column_def_node);
            node->position_def = (yyvsp[0].column_position_def);
            (yyval.add_column_def) = node;
        }
#line 2031 "y.tab.c"
    break;

  case 35: /* drop_column_def: DROP COLUMN IDENTIFIER  */
#line 420 "sql.y"
        {
            DropColumnDef *node = instance(DropColumnDef);
            node->column_name = (yyvsp[0].strVal);
            (yyval.drop_column_def) = node;
        }
#line 2041 "y.tab.c"
    break;

  case 36: /* change_column_def: CHANGE IDENTIFIER column_def  */
#line 428 "sql.y"
        {
            ChangeColumnDef *node = instance(ChangeColumnDef);
            node->old_column_name = (yyvsp[-1].strVal);
            node->new_column_def = (yyvsp[0].column_def_node);
            (yyval.change_column_def) = node;
        }
#line 2052 "y.tab.c"
    break;

  case 37: /* column_position_def: %empty  */
#line 437 "sql.y"
    {
        (yyval.column_position_def) = NULL;
    }
#line 2060 "y.tab.c"
    break;

  case 38: /* column_position_def: BEFORE IDENTIFIER  */
#line 441 "sql.y"
        {
            ColumnPositionDef *pos = instance(ColumnPositionDef);
            pos->type = POS_BEFORE;
            pos->column = (yyvsp[0].strVal);
            (yyval.column_position_def) = pos;
        }
#line 2071 "y.tab.c"
    break;

  case 39: /* column_position_def: AFTER IDENTIFIER  */
#line 448 "sql.y"
        {
            ColumnPositionDef *pos = instance(ColumnPositionDef);
            pos->type = POS_AFTER;
            pos->column = (yyvsp[0].strVal);
            (yyval.column_position_def) = pos;
        }
#line 2082 "y.tab.c"
    break;

  case 40: /* selection: scalar_exp_commalist  */
#line 457 "sql.y"
        {
            SelectionNode *selection_node = instance(SelectionNode);
            selection_node->all_column = false;
            selection_node->scalar_exp_list = (yyvsp[0].list);
            (yyval.selection_node) = selection_node;
        }
#line 2093 "y.tab.c"
    break;

  case 41: /* selection: '*'  */
#line 464 "sql.y"
        {
            SelectionNode *selection_node = instance(SelectionNode);
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 2103 "y.tab.c"
    break;

  case 42: /* table_exp: from_clause opt_where_clause  */
#line 472 "sql.y"
        {
            TableExpNode *table_exp = instance(TableExpNode);
            table_exp->from_clause = (yyvsp[-1].from_clause_node);
            table_exp->where_clause = (yyvsp[0].where_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 2114 "y.tab.c"
    break;

  case 43: /* from_clause: %empty  */
#line 481 "sql.y"
        {
            (yyval.from_clause_node) = NULL;
        }
#line 2122 "y.tab.c"
    break;

  case 44: /* from_clause: FROM table_ref_commalist  */
#line 485 "sql.y"
        {
            FromClauseNode *from_clause = instance(FromClauseNode);
            from_clause->from = (yyvsp[0].list);
            (yyval.from_clause_node) = from_clause;
        }
#line 2132 "y.tab.c"
    break;

  case 45: /* table_ref_commalist: table_ref  */
#line 493 "sql.y"
        {
            List *list = create_list(NODE_TABLE_REFER);
            append_list(list, (yyvsp[0].table_ref_node));
            (yyval.list) = list;
        }
#line 2142 "y.tab.c"
    break;

  case 46: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 499 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].table_ref_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2151 "y.tab.c"
    break;

  case 47: /* table_ref: table  */
#line 506 "sql.y"
        {
            TableRefNode *table_ref = instance(TableRefNode);
            table_ref->table = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2161 "y.tab.c"
    break;

  case 48: /* table_ref: table range_variable  */
#line 512 "sql.y"
        {
            TableRefNode *table_ref = instance(TableRefNode);
            table_ref->table = (yyvsp[-1].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2172 "y.tab.c"
    break;

  case 49: /* table_ref: table AS range_variable  */
#line 519 "sql.y"
        {
            TableRefNode *table_ref = instance(TableRefNode);
            table_ref->table = (yyvsp[-2].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2183 "y.tab.c"
    break;

  case 50: /* table: IDENTIFIER  */
#line 528 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2191 "y.tab.c"
    break;

  case 51: /* range_variable: IDENTIFIER  */
#line 534 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2199 "y.tab.c"
    break;

  case 52: /* opt_where_clause: %empty  */
#line 540 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 2207 "y.tab.c"
    break;

  case 53: /* opt_where_clause: where_clause  */
#line 544 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 2215 "y.tab.c"
    break;

  case 54: /* where_clause: WHERE condition  */
#line 550 "sql.y"
        {
            WhereClauseNode *where_clause_node = instance(WhereClauseNode);
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 2225 "y.tab.c"
    break;

  case 55: /* values_or_query_spec: VALUES opt_values  */
#line 558 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = instance(ValuesOrQuerySpecNode);
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = (yyvsp[0].list);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2236 "y.tab.c"
    break;

  case 56: /* values_or_query_spec: query_spec  */
#line 565 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = instance(ValuesOrQuerySpecNode);
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = (yyvsp[0].query_spec_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2247 "y.tab.c"
    break;

  case 57: /* opt_values: '(' value_items ')'  */
#line 574 "sql.y"
        {
            (yyval.list) = create_list(NODE_LIST);
            append_list((yyval.list), (yyvsp[-1].list));
        }
#line 2256 "y.tab.c"
    break;

  case 58: /* opt_values: opt_values ',' '(' value_items ')'  */
#line 579 "sql.y"
        {
            (yyval.list) = (yyvsp[-4].list);
            append_list((yyval.list), (yyvsp[-1].list));
        }
#line 2265 "y.tab.c"
    break;

  case 59: /* query_spec: SELECT selection table_exp  */
#line 586 "sql.y"
        {
            QuerySpecNode *query_spec = instance(QuerySpecNode);
            query_spec->selection = (yyvsp[-1].selection_node);
            query_spec->table_exp = (yyvsp[0].table_exp_node);
            (yyval.query_spec_node) = query_spec;
        }
#line 2276 "y.tab.c"
    break;

  case 60: /* scalar_exp_commalist: scalar_exp  */
#line 595 "sql.y"
        {
            List *scalar_exp_list = create_list(NODE_SCALAR_EXP);
            append_list(scalar_exp_list, (yyvsp[0].scalar_exp_node));
            (yyval.list) = scalar_exp_list;
        }
#line 2286 "y.tab.c"
    break;

  case 61: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 601 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].scalar_exp_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2295 "y.tab.c"
    break;

  case 62: /* scalar_exp: calculate  */
#line 608 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2306 "y.tab.c"
    break;

  case 63: /* scalar_exp: column  */
#line 615 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2317 "y.tab.c"
    break;

  case 64: /* scalar_exp: function  */
#line 622 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2328 "y.tab.c"
    break;

  case 65: /* scalar_exp: value_item  */
#line 629 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = instance(ScalarExpNode);
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2339 "y.tab.c"
    break;

  case 66: /* scalar_exp: '(' scalar_exp ')'  */
#line 636 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2347 "y.tab.c"
    break;

  case 67: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 640 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].strVal);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2356 "y.tab.c"
    break;

  case 68: /* calculate: scalar_exp '+' scalar_exp  */
#line 647 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2368 "y.tab.c"
    break;

  case 69: /* calculate: scalar_exp '-' scalar_exp  */
#line 655 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2380 "y.tab.c"
    break;

  case 70: /* calculate: scalar_exp '*' scalar_exp  */
#line 663 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2392 "y.tab.c"
    break;

  case 71: /* calculate: scalar_exp '/' scalar_exp  */
#line 671 "sql.y"
        {
            CalculateNode *calculate_node = instance(CalculateNode);
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2404 "y.tab.c"
    break;

  case 72: /* columns: column  */
#line 681 "sql.y"
        {
            List *column_set_node = create_list(NODE_COLUMN);
            append_list(column_set_node, (yyvsp[0].column_node));
            (yyval.list) = column_set_node;
        }
#line 2414 "y.tab.c"
    break;

  case 73: /* columns: columns ',' column  */
#line 687 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].column_node));
        }
#line 2423 "y.tab.c"
    break;

  case 74: /* base_table_element_commalist: base_table_element  */
#line 694 "sql.y"
        {
            List *base_table_element_commalist = create_list(NODE_BASE_TABLE_ELEMENT);
            append_list(base_table_element_commalist, (yyvsp[0].base_table_element));
            (yyval.list) = base_table_element_commalist;
        }
#line 2433 "y.tab.c"
    break;

  case 75: /* base_table_element_commalist: base_table_element_commalist ',' base_table_element  */
#line 700 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].base_table_element));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2442 "y.tab.c"
    break;

  case 76: /* base_table_element: column_def  */
#line 707 "sql.y"
        {
            BaseTableElementNode *node = instance(BaseTableElementNode);
            node->column_def = (yyvsp[0].column_def_node);
            node->table_contraint_def = NULL;
            node->type = TELE_COLUMN_DEF;
            (yyval.base_table_element) = node;
        }
#line 2454 "y.tab.c"
    break;

  case 77: /* base_table_element: table_contraint_def  */
#line 715 "sql.y"
        {
            BaseTableElementNode *node = instance(BaseTableElementNode);
            node->column_def = NULL;
            node->table_contraint_def = (yyvsp[0].table_contraint_def);
            node->type = TELE_TABLE_CONTRAINT_DEF;
            (yyval.base_table_element) = node;
        }
#line 2466 "y.tab.c"
    break;

  case 78: /* column_def: column_def_name data_type array_dim_clause column_def_opt_list  */
#line 738 "sql.y"
        {
            ColumnDefNode *column_def = instance(ColumnDefNode);
            column_def->column = (yyvsp[-3].column_def_name);
            column_def->data_type = (yyvsp[-2].data_type_node);
            column_def->array_dim = (yyvsp[-1].intVal);
            column_def->column_def_opt_list = (yyvsp[0].list);
            (yyval.column_def_node) = column_def;
        }
#line 2479 "y.tab.c"
    break;

  case 79: /* column_def_name_commalist: column_def_name  */
#line 749 "sql.y"
        {
            List *list = create_list(NODE_COLUMN_DEF_NAME);
            append_list(list, (yyvsp[0].column_def_name));
            (yyval.list) = list;
        }
#line 2489 "y.tab.c"
    break;

  case 80: /* column_def_name_commalist: column_def_name_commalist ',' column_def_name  */
#line 755 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].column_def_name));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2498 "y.tab.c"
    break;

  case 81: /* column_def_name: IDENTIFIER  */
#line 762 "sql.y"
        {
            ColumnDefName *column_def_name = instance(ColumnDefName);
            column_def_name->column = (yyvsp[0].strVal);
            (yyval.column_def_name) = column_def_name;
        }
#line 2508 "y.tab.c"
    break;

  case 82: /* data_type: INT  */
#line 770 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_INT; 
            (yyval.data_type_node) = node;
        }
#line 2518 "y.tab.c"
    break;

  case 83: /* data_type: LONG  */
#line 776 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_LONG;  
            (yyval.data_type_node) = node;
        }
#line 2528 "y.tab.c"
    break;

  case 84: /* data_type: CHAR  */
#line 782 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_CHAR; 
            (yyval.data_type_node) = node;
        }
#line 2538 "y.tab.c"
    break;

  case 85: /* data_type: VARCHAR '(' INTVALUE ')'  */
#line 788 "sql.y"
        {
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_VARCHAR; 
            node->len = (yyvsp[-1].intVal);
            (yyval.data_type_node) = node;
        }
#line 2549 "y.tab.c"
    break;

  case 86: /* data_type: STRING  */
#line 795 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_STRING; 
            (yyval.data_type_node) = node;
        }
#line 2559 "y.tab.c"
    break;

  case 87: /* data_type: BOOL  */
#line 801 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_BOOL; 
            (yyval.data_type_node) = node;
        }
#line 2569 "y.tab.c"
    break;

  case 88: /* data_type: FLOAT  */
#line 807 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_FLOAT; 
            (yyval.data_type_node) = node;
        }
#line 2579 "y.tab.c"
    break;

  case 89: /* data_type: DOUBLE  */
#line 813 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_DOUBLE; 
            (yyval.data_type_node) = node;
        }
#line 2589 "y.tab.c"
    break;

  case 90: /* data_type: TIMESTAMP  */
#line 819 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_TIMESTAMP; 
            (yyval.data_type_node) = node;
        }
#line 2599 "y.tab.c"
    break;

  case 91: /* data_type: DATE  */
#line 825 "sql.y"
        { 
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_DATE; 
            (yyval.data_type_node) = node;
        }
#line 2609 "y.tab.c"
    break;

  case 92: /* data_type: table  */
#line 831 "sql.y"
        {
            DataTypeNode *node = instance(DataTypeNode);                
            node->type = T_REFERENCE;
            node->table_name = (yyvsp[0].strVal);
            (yyval.data_type_node) = node;
        }
#line 2620 "y.tab.c"
    break;

  case 93: /* array_dim_clause: %empty  */
#line 840 "sql.y"
        {
            (yyval.intVal) = 0;
        }
#line 2628 "y.tab.c"
    break;

  case 94: /* array_dim_clause: '[' ']'  */
#line 844 "sql.y"
        {
            (yyval.intVal) = 1;
        }
#line 2636 "y.tab.c"
    break;

  case 95: /* array_dim_clause: array_dim_clause '[' ']'  */
#line 848 "sql.y"
        {
            (yyval.intVal)++;
        }
#line 2644 "y.tab.c"
    break;

  case 96: /* column_def_opt_list: %empty  */
#line 854 "sql.y"
        {
            (yyval.list) = NULL;
        }
#line 2652 "y.tab.c"
    break;

  case 97: /* column_def_opt_list: column_def_opt  */
#line 858 "sql.y"
        {
            (yyval.list) = create_list(NODE_COLUMN_DEF_OPT);
            append_list((yyval.list), (yyvsp[0].column_def_opt));
        }
#line 2661 "y.tab.c"
    break;

  case 98: /* column_def_opt_list: column_def_opt_list column_def_opt  */
#line 863 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].column_def_opt));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 2670 "y.tab.c"
    break;

  case 99: /* column_def_opt: NOT NULLX  */
#line 870 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_NOT_NULL; 
            (yyval.column_def_opt) = node;
        }
#line 2680 "y.tab.c"
    break;

  case 100: /* column_def_opt: UNIQUE  */
#line 876 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_UNIQUE; 
            (yyval.column_def_opt) = node;
        }
#line 2690 "y.tab.c"
    break;

  case 101: /* column_def_opt: PRIMARY KEY  */
#line 882 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_PRIMARY_KEY; 
            (yyval.column_def_opt) = node;
        }
#line 2700 "y.tab.c"
    break;

  case 102: /* column_def_opt: DEFAULT value_item  */
#line 888 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_DEFAULT_VALUE;
            node->value = (yyvsp[0].value_item_node);
            (yyval.column_def_opt) = node;
        }
#line 2711 "y.tab.c"
    break;

  case 103: /* column_def_opt: DEFAULT NULLX  */
#line 895 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_DEFAULT_NULL;
            (yyval.column_def_opt) = node;
        }
#line 2721 "y.tab.c"
    break;

  case 104: /* column_def_opt: COMMENT STRINGVALUE  */
#line 901 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_COMMENT;
            node->comment = (yyvsp[0].strVal);
            (yyval.column_def_opt) = node;
        }
#line 2732 "y.tab.c"
    break;

  case 105: /* column_def_opt: CHECK '(' condition ')'  */
#line 908 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_CHECK_CONDITION;
            node->condition = (yyvsp[-1].condition_node);
            (yyval.column_def_opt) = node;
        }
#line 2743 "y.tab.c"
    break;

  case 106: /* column_def_opt: REFERENCES table  */
#line 915 "sql.y"
        {
            ColumnDefOptNode *node = instance(ColumnDefOptNode);
            node->opt_type = OPT_REFERENECS;
            node->refer_table = (yyvsp[0].strVal);
            (yyval.column_def_opt) = node;
        }
#line 2754 "y.tab.c"
    break;

  case 107: /* table_contraint_def: UNIQUE '(' column_def_name_commalist ')'  */
#line 924 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_UNIQUE;
            node->column_commalist = (yyvsp[-1].list);
            (yyval.table_contraint_def) = node;
        }
#line 2765 "y.tab.c"
    break;

  case 108: /* table_contraint_def: PRIMARY KEY '(' column_def_name_commalist ')'  */
#line 931 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_PRIMARY_KEY;
            node->column_commalist = (yyvsp[-1].list);
            (yyval.table_contraint_def) = node;
        }
#line 2776 "y.tab.c"
    break;

  case 109: /* table_contraint_def: FOREIGN KEY '(' column_def_name_commalist ')' REFERENCES table  */
#line 938 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_FOREIGN_KEY;
            node->column_commalist = (yyvsp[-3].list);
            node->table = (yyvsp[0].strVal);
            (yyval.table_contraint_def) = node;
        }
#line 2788 "y.tab.c"
    break;

  case 110: /* table_contraint_def: CHECK '(' condition ')'  */
#line 946 "sql.y"
        {
            TableContraintDefNode *node = instance(TableContraintDefNode);
            node->type = TCONTRAINT_CHECK;
            node->condition = (yyvsp[-1].condition_node);
            (yyval.table_contraint_def) = node;
        }
#line 2799 "y.tab.c"
    break;

  case 111: /* column: IDENTIFIER  */
#line 955 "sql.y"
        {
            ColumnNode *column_node = instance(ColumnNode);
            column_node->column_name = (yyvsp[0].strVal);
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2810 "y.tab.c"
    break;

  case 112: /* column: '(' IDENTIFIER ')' '.' column  */
#line 962 "sql.y"
        {
            ColumnNode *column_node = instance(ColumnNode);
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->sub_column = (yyvsp[0].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2822 "y.tab.c"
    break;

  case 113: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 970 "sql.y"
        {
            ColumnNode *column_node = instance(ColumnNode);
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->scalar_exp_list = (yyvsp[-1].list);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2834 "y.tab.c"
    break;

  case 114: /* column: IDENTIFIER '.' column  */
#line 978 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = (yyvsp[-2].strVal);
        }
#line 2843 "y.tab.c"
    break;

  case 115: /* value_items: value_item  */
#line 985 "sql.y"
        {
            List *value_list = create_list(NODE_VALUE_ITEM);
            append_list(value_list, (yyvsp[0].value_item_node));
            (yyval.list) = value_list;
        }
#line 2853 "y.tab.c"
    break;

  case 116: /* value_items: value_items ',' value_item  */
#line 991 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].value_item_node));
        }
#line 2862 "y.tab.c"
    break;

  case 117: /* value_item: atom  */
#line 998 "sql.y"
        {
            ValueItemNode *node = instance(ValueItemNode);
            node->type = V_ATOM;
            node->value.atom = (yyvsp[0].atom_node);
            (yyval.value_item_node) = node;
        }
#line 2873 "y.tab.c"
    break;

  case 118: /* value_item: NULLX  */
#line 1005 "sql.y"
        {
            ValueItemNode *node = instance(ValueItemNode);
            node->type = V_NULL;
            (yyval.value_item_node) = node;
        }
#line 2883 "y.tab.c"
    break;

  case 119: /* value_item: '[' value_items ']'  */
#line 1011 "sql.y"
        {
            ValueItemNode *node = instance(ValueItemNode);
            node->type = V_ARRAY;
            node->value.value_list = (yyvsp[-1].list);
            (yyval.value_item_node) = node;
        }
#line 2894 "y.tab.c"
    break;

  case 120: /* atom: INTVALUE  */
#line 1020 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.intval = (yyvsp[0].intVal);
            node->type = A_INT;
            (yyval.atom_node) = node;
        }
#line 2905 "y.tab.c"
    break;

  case 121: /* atom: BOOLVALUE  */
#line 1027 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.boolval = (yyvsp[0].boolVal);
            node->type = A_BOOL;
            (yyval.atom_node) = node;
        }
#line 2916 "y.tab.c"
    break;

  case 122: /* atom: STRINGVALUE  */
#line 1034 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.strval = (yyvsp[0].strVal);
            node->type = A_STRING;
            (yyval.atom_node) = node;
        }
#line 2927 "y.tab.c"
    break;

  case 123: /* atom: FLOATVALUE  */
#line 1041 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.floatval = (yyvsp[0].floatVal);
            node->type = A_FLOAT;
            (yyval.atom_node) = node;
        }
#line 2938 "y.tab.c"
    break;

  case 124: /* atom: REFERVALUE  */
#line 1048 "sql.y"
        {
            AtomNode *node = instance(AtomNode);
            node->value.referval = (yyvsp[0].referVal);
            node->type = A_REFERENCE;
            (yyval.atom_node) = node;
        }
#line 2949 "y.tab.c"
    break;

  case 125: /* REFERVALUE: '(' value_items ')'  */
#line 1058 "sql.y"
        {
            ReferValue *refer = instance(ReferValue);
            refer->type = DIRECTLY;
            refer->nest_value_list = (yyvsp[-1].list);
            (yyval.referVal) = refer;
        }
#line 2960 "y.tab.c"
    break;

  case 126: /* REFERVALUE: REF '(' condition ')'  */
#line 1066 "sql.y"
        {
            ReferValue *refer = instance(ReferValue);
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.referVal) = refer;
        }
#line 2971 "y.tab.c"
    break;

  case 127: /* BOOLVALUE: TRUE  */
#line 1075 "sql.y"
        {
            (yyval.boolVal) = true;
        }
#line 2979 "y.tab.c"
    break;

  case 128: /* BOOLVALUE: FALSE  */
#line 1079 "sql.y"
        {
            (yyval.boolVal) = false;
        }
#line 2987 "y.tab.c"
    break;

  case 129: /* assignments: assignment  */
#line 1085 "sql.y"
        {
            List *list = create_list(NODE_ASSIGNMENT);
            append_list(list, (yyvsp[0].assignment_node));
            (yyval.list) = list;
        }
#line 2997 "y.tab.c"
    break;

  case 130: /* assignments: assignments ',' assignment  */
#line 1091 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].assignment_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 3006 "y.tab.c"
    break;

  case 131: /* assignment: column EQ value_item  */
#line 1098 "sql.y"
        {
            AssignmentNode *node = instance(AssignmentNode);
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 3017 "y.tab.c"
    break;

  case 132: /* condition: condition OR condition  */
#line 1107 "sql.y"
        {
            ConditionNode *condition = instance(ConditionNode);
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 3029 "y.tab.c"
    break;

  case 133: /* condition: condition AND condition  */
#line 1115 "sql.y"
        {
            ConditionNode *condition = instance(ConditionNode);
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 3041 "y.tab.c"
    break;

  case 134: /* condition: '(' condition ')'  */
#line 1123 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 3049 "y.tab.c"
    break;

  case 135: /* condition: predicate  */
#line 1127 "sql.y"
        {
            ConditionNode *condition = instance(ConditionNode);
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 3060 "y.tab.c"
    break;

  case 136: /* predicate: comparison_predicate  */
#line 1136 "sql.y"
        {
            PredicateNode *predicate = instance(PredicateNode);
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 3071 "y.tab.c"
    break;

  case 137: /* predicate: like_predicate  */
#line 1143 "sql.y"
        {
            PredicateNode *predicate = instance(PredicateNode);
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 3082 "y.tab.c"
    break;

  case 138: /* predicate: in_predicate  */
#line 1150 "sql.y"
        {
            PredicateNode *predicate = instance(PredicateNode);
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 3093 "y.tab.c"
    break;

  case 139: /* comparison_predicate: column compare scalar_exp  */
#line 1159 "sql.y"
        {
            ComparisonNode *comparison_node = instance(ComparisonNode);
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 3105 "y.tab.c"
    break;

  case 140: /* like_predicate: column LIKE value_item  */
#line 1169 "sql.y"
        {
            LikeNode *like_node = instance(LikeNode);
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 3116 "y.tab.c"
    break;

  case 141: /* in_predicate: column IN '(' value_items ')'  */
#line 1178 "sql.y"
        {
            InNode *in_node = instance(InNode);
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_list = (yyvsp[-1].list);
            (yyval.in_node) = in_node;
        }
#line 3127 "y.tab.c"
    break;

  case 142: /* compare: EQ  */
#line 1206 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 3133 "y.tab.c"
    break;

  case 143: /* compare: NE  */
#line 1207 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 3139 "y.tab.c"
    break;

  case 144: /* compare: GT  */
#line 1208 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 3145 "y.tab.c"
    break;

  case 145: /* compare: GE  */
#line 1209 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 3151 "y.tab.c"
    break;

  case 146: /* compare: LT  */
#line 1210 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 3157 "y.tab.c"
    break;

  case 147: /* compare: LE  */
#line 1211 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 3163 "y.tab.c"
    break;

  case 148: /* function: MAX '(' non_all_function_value ')'  */
#line 1215 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3174 "y.tab.c"
    break;

  case 149: /* function: MIN '(' non_all_function_value ')'  */
#line 1222 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3185 "y.tab.c"
    break;

  case 150: /* function: COUNT '(' function_value ')'  */
#line 1229 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3196 "y.tab.c"
    break;

  case 151: /* function: SUM '(' function_value ')'  */
#line 1236 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3207 "y.tab.c"
    break;

  case 152: /* function: AVG '(' function_value ')'  */
#line 1243 "sql.y"
        {
            FunctionNode *function_node = instance(FunctionNode);        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3218 "y.tab.c"
    break;

  case 153: /* function_value: INTVALUE  */
#line 1252 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3229 "y.tab.c"
    break;

  case 154: /* function_value: column  */
#line 1259 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3240 "y.tab.c"
    break;

  case 155: /* function_value: '*'  */
#line 1266 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 3250 "y.tab.c"
    break;

  case 156: /* non_all_function_value: INTVALUE  */
#line 1274 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3261 "y.tab.c"
    break;

  case 157: /* non_all_function_value: column  */
#line 1281 "sql.y"
        {
            FunctionValueNode *node = instance(FunctionValueNode);
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3272 "y.tab.c"
    break;


#line 3276 "y.tab.c"

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

#line 1292 "sql.y"

