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
    SYSTEM = 321,                  /* SYSTEM  */
    CONFIG = 322,                  /* CONFIG  */
    MEMORY = 323,                  /* MEMORY  */
    IDENTIFIER = 324,              /* IDENTIFIER  */
    INTVALUE = 325,                /* INTVALUE  */
    FLOATVALUE = 326,              /* FLOATVALUE  */
    STRINGVALUE = 327              /* STRINGVALUE  */
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
#define SYSTEM 321
#define CONFIG 322
#define MEMORY 323
#define IDENTIFIER 324
#define INTVALUE 325
#define FLOATVALUE 326
#define STRINGVALUE 327

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
   AddColumnDef                 *add_column_def;
   DropColumnDef                *drop_column_def;
   ChangeColumnDef              *change_column_def;
   AlterTableAction             *alter_table_action;
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

#line 340 "y.tab.c"

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
  YYSYMBOL_SYSTEM = 74,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 75,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 76,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 77,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 78,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 79,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 80,               /* STRINGVALUE  */
  YYSYMBOL_81_ = 81,                       /* ','  */
  YYSYMBOL_82_ = 82,                       /* '.'  */
  YYSYMBOL_83_ = 83,                       /* '{'  */
  YYSYMBOL_84_ = 84,                       /* '}'  */
  YYSYMBOL_85_ = 85,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_statements = 87,                /* statements  */
  YYSYMBOL_statement = 88,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 89, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 90, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 91, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 92,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 93,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 94,          /* select_statement  */
  YYSYMBOL_insert_statement = 95,          /* insert_statement  */
  YYSYMBOL_update_statement = 96,          /* update_statement  */
  YYSYMBOL_delete_statement = 97,          /* delete_statement  */
  YYSYMBOL_describe_statement = 98,        /* describe_statement  */
  YYSYMBOL_show_statement = 99,            /* show_statement  */
  YYSYMBOL_alter_table_statement = 100,    /* alter_table_statement  */
  YYSYMBOL_alter_table_action = 101,       /* alter_table_action  */
  YYSYMBOL_add_column_def = 102,           /* add_column_def  */
  YYSYMBOL_drop_column_def = 103,          /* drop_column_def  */
  YYSYMBOL_change_column_def = 104,        /* change_column_def  */
  YYSYMBOL_selection = 105,                /* selection  */
  YYSYMBOL_table_exp = 106,                /* table_exp  */
  YYSYMBOL_from_clause = 107,              /* from_clause  */
  YYSYMBOL_table_ref_commalist = 108,      /* table_ref_commalist  */
  YYSYMBOL_table_ref = 109,                /* table_ref  */
  YYSYMBOL_table = 110,                    /* table  */
  YYSYMBOL_range_variable = 111,           /* range_variable  */
  YYSYMBOL_opt_where_clause = 112,         /* opt_where_clause  */
  YYSYMBOL_where_clause = 113,             /* where_clause  */
  YYSYMBOL_values_or_query_spec = 114,     /* values_or_query_spec  */
  YYSYMBOL_query_spec = 115,               /* query_spec  */
  YYSYMBOL_scalar_exp_commalist = 116,     /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 117,               /* scalar_exp  */
  YYSYMBOL_calculate = 118,                /* calculate  */
  YYSYMBOL_columns = 119,                  /* columns  */
  YYSYMBOL_base_table_element_commalist = 120, /* base_table_element_commalist  */
  YYSYMBOL_base_table_element = 121,       /* base_table_element  */
  YYSYMBOL_column_def = 122,               /* column_def  */
  YYSYMBOL_column_def_name_commalist = 123, /* column_def_name_commalist  */
  YYSYMBOL_column_def_name = 124,          /* column_def_name  */
  YYSYMBOL_data_type = 125,                /* data_type  */
  YYSYMBOL_array_dim_clause = 126,         /* array_dim_clause  */
  YYSYMBOL_column_def_opt_list = 127,      /* column_def_opt_list  */
  YYSYMBOL_column_def_opt = 128,           /* column_def_opt  */
  YYSYMBOL_table_contraint_def = 129,      /* table_contraint_def  */
  YYSYMBOL_column = 130,                   /* column  */
  YYSYMBOL_value_items = 131,              /* value_items  */
  YYSYMBOL_value_item = 132,               /* value_item  */
  YYSYMBOL_atom = 133,                     /* atom  */
  YYSYMBOL_REFERVALUE = 134,               /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 135,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 136,              /* assignments  */
  YYSYMBOL_assignment = 137,               /* assignment  */
  YYSYMBOL_condition = 138,                /* condition  */
  YYSYMBOL_predicate = 139,                /* predicate  */
  YYSYMBOL_comparison_predicate = 140,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 141,           /* like_predicate  */
  YYSYMBOL_in_predicate = 142,             /* in_predicate  */
  YYSYMBOL_compare = 143,                  /* compare  */
  YYSYMBOL_function = 144,                 /* function  */
  YYSYMBOL_function_value = 145,           /* function_value  */
  YYSYMBOL_non_all_function_value = 146,   /* non_all_function_value  */
  YYSYMBOL_end = 147                       /* end  */
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
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   367

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  299

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
       9,    10,     7,     5,    81,     6,    82,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    85,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    11,     2,    12,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    83,     2,    84,     2,     2,     2,     2,
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
      73,    74,    75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   172,   172,   177,   184,   190,   196,   202,   209,   216,
     223,   230,   237,   244,   251,   258,   267,   270,   273,   277,
     287,   296,   306,   314,   326,   337,   343,   353,   362,   366,
     373,   381,   388,   395,   404,   412,   420,   429,   436,   444,
     454,   457,   465,   471,   478,   484,   491,   500,   506,   513,
     516,   522,   530,   537,   546,   555,   561,   568,   575,   582,
     589,   596,   600,   607,   615,   623,   631,   641,   647,   654,
     660,   667,   674,   696,   707,   713,   720,   728,   733,   738,
     743,   749,   754,   759,   764,   769,   774,   779,   788,   791,
     795,   802,   805,   810,   817,   822,   827,   832,   838,   843,
     849,   855,   863,   869,   875,   882,   890,   897,   905,   913,
     920,   926,   933,   940,   946,   955,   962,   969,   976,   983,
     993,  1001,  1010,  1014,  1020,  1026,  1033,  1042,  1050,  1058,
    1062,  1071,  1078,  1085,  1094,  1104,  1113,  1142,  1143,  1144,
    1145,  1146,  1147,  1150,  1157,  1164,  1171,  1178,  1187,  1194,
    1201,  1209,  1216,  1225,  1226
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
  "COLUMN", "ADD", "CHANGE", "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER",
  "INTVALUE", "FLOATVALUE", "STRINGVALUE", "','", "'.'", "'{'", "'}'",
  "';'", "$accept", "statements", "statement",
  "begin_transaction_statement", "commit_transaction_statement",
  "rollback_transaction_statement", "create_table_statement",
  "drop_table_statement", "select_statement", "insert_statement",
  "update_statement", "delete_statement", "describe_statement",
  "show_statement", "alter_table_statement", "alter_table_action",
  "add_column_def", "drop_column_def", "change_column_def", "selection",
  "table_exp", "from_clause", "table_ref_commalist", "table_ref", "table",
  "range_variable", "opt_where_clause", "where_clause",
  "values_or_query_spec", "query_spec", "scalar_exp_commalist",
  "scalar_exp", "calculate", "columns", "base_table_element_commalist",
  "base_table_element", "column_def", "column_def_name_commalist",
  "column_def_name", "data_type", "array_dim_clause",
  "column_def_opt_list", "column_def_opt", "table_contraint_def", "column",
  "value_items", "value_item", "atom", "REFERVALUE", "BOOLVALUE",
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

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-111)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     231,    17,    17,    17,    33,    53,   143,    95,   -34,     3,
     -34,   -15,    94,   258,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,   118,  -190,
    -190,  -190,   -34,   -34,  -190,    67,   131,   125,   130,   134,
     147,   156,   159,  -190,  -190,  -190,   -14,  -190,  -190,  -190,
     145,    91,   291,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
     -34,  -190,   153,   -34,    17,    17,    17,   -34,  -190,  -190,
    -190,   165,    17,     9,   278,    35,   100,   131,    20,  -190,
      19,    19,    27,    27,    27,     6,    29,   186,   -34,    17,
     167,   186,   186,   186,   186,   186,   121,   185,    29,    10,
    -190,  -190,  -190,    -2,   116,  -190,   123,  -190,  -190,   131,
    -190,   135,  -190,  -190,   198,   204,  -190,  -190,  -190,   207,
     209,   214,    49,   247,   126,  -190,  -190,  -190,  -190,  -190,
     -40,   144,  -190,   -31,  -190,     6,  -190,  -190,   291,    32,
      32,   192,   192,  -190,    29,   143,   226,    17,  -190,   179,
      52,  -190,     6,  -190,   171,   173,    29,    17,  -190,  -190,
    -190,   221,   248,   250,   222,  -190,    38,  -190,  -190,   290,
    -190,    29,  -190,   272,  -190,  -190,  -190,  -190,  -190,   160,
    -190,  -190,  -190,  -190,  -190,  -190,   251,   131,   186,     6,
       6,  -190,  -190,   -34,   229,  -190,  -190,    90,    39,  -190,
     145,   131,  -190,   131,    29,    17,    18,    29,   239,   239,
    -190,   282,   239,     6,   311,    17,   116,  -190,  -190,  -190,
     312,  -190,  -190,  -190,  -190,  -190,  -190,  -190,   313,  -190,
    -190,   131,  -190,   291,   326,  -190,  -190,  -190,    14,    29,
    -190,    41,  -190,  -190,  -190,  -190,  -190,  -190,  -190,   239,
      43,  -190,   315,   239,  -190,  -190,   253,   320,   257,    44,
      17,  -190,  -190,    46,  -190,   239,  -190,    47,   323,  -190,
     322,   301,  -190,   191,   328,   -34,   259,   303,   267,  -190,
    -190,  -190,  -190,  -190,   300,  -190,  -190,  -190,  -190,  -190,
       6,  -190,  -190,  -190,  -190,   -34,   319,  -190,  -190
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   153,     0,    16,
      17,    18,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,   122,   123,   113,   106,   115,   118,   117,
      40,    37,    55,    57,    58,    60,   112,   119,   116,    59,
       0,    47,     0,     0,     0,     0,     0,     0,     1,     3,
     154,     0,     0,   106,     0,     0,    60,     0,     0,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    28,    29,     0,     0,    20,     0,    61,   120,     0,
     114,     0,   151,   152,     0,     0,   150,   148,   149,     0,
       0,     0,     0,     0,     0,   130,   131,   132,   133,   109,
       0,    41,    42,    44,    21,     0,    39,    50,    56,    63,
      64,    65,    66,    62,     0,     0,     0,     0,    53,     0,
      49,   124,     0,    25,     0,     0,     0,     0,    31,    32,
      33,     0,     0,     0,     0,    76,     0,    69,    71,     0,
      72,     0,   111,     0,   143,   144,   145,   146,   147,     0,
     137,   138,   139,   140,   141,   142,     0,     0,     0,     0,
       0,   121,   108,     0,     0,    48,    45,    51,     0,    67,
      40,     0,    22,     0,     0,     0,     0,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,    79,    77,    78,
       0,    81,    82,    83,    84,    86,    85,    87,    88,   107,
     129,     0,   135,   134,   127,   128,    43,    46,     0,     0,
      54,     0,   126,   125,    24,    26,    35,    34,    36,     0,
       0,    74,     0,     0,    19,    70,     0,     0,    91,     0,
       0,    68,    52,     0,   102,     0,   105,     0,     0,    89,
       0,     0,    95,     0,     0,     0,     0,     0,    73,    92,
     136,    23,   103,    75,     0,    80,    90,    96,    98,    97,
       0,   101,    99,    94,    93,     0,     0,   104,   100
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,   339,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,   208,
     154,  -190,  -190,   162,    -8,   163,   206,  -190,   120,  -190,
     273,    -6,  -190,  -190,  -190,   146,   -71,  -189,   -50,  -190,
    -190,  -190,    81,  -190,   -72,   -35,   -30,  -190,  -190,  -190,
    -190,   157,  -115,  -190,  -190,  -190,  -190,  -190,  -190,    76,
     283,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,   157,   158,   159,   160,    50,
      89,    90,   131,   132,   133,   196,   136,   137,   147,   148,
      51,    52,    53,   198,   166,   167,   168,   250,   169,   228,
     258,   278,   279,   170,    54,    75,    55,    56,    57,    58,
     150,   151,   124,   125,   126,   127,   128,   188,    59,   119,
     114,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    78,    64,    30,    31,    76,    79,   179,   113,   113,
     118,   118,   118,   123,   129,   122,   154,    65,   194,   106,
     197,   189,   190,    27,    71,    72,   149,    63,   111,    74,
      27,    27,   110,   145,   116,   152,   111,   206,   111,    94,
      95,    91,   146,    61,   192,   108,   195,    79,   215,   238,
     123,   262,    97,   264,   280,    99,   282,   284,   122,   103,
     263,    66,    32,   123,   267,   100,   101,   102,    86,    87,
     155,   156,   199,   105,   234,   235,    35,   135,    36,   172,
     123,    96,    33,    46,   209,   138,   139,   140,   141,   142,
     134,    86,    87,   189,   190,    28,    46,   112,   252,   229,
     153,   109,    28,    28,    46,   117,    46,    37,    38,    39,
      40,    41,    42,    43,    44,    45,   109,   123,   123,   216,
     239,    60,   109,    67,   265,   109,    73,   265,   265,   189,
     190,    70,   149,   204,    80,   246,   191,   247,   248,    81,
      77,   123,    36,    82,    73,    47,    48,    49,   202,   161,
      34,   162,    35,   163,    36,   164,    83,   232,   210,   120,
     121,   227,   251,   189,   190,    84,   241,   261,    85,    88,
     230,    79,    91,   242,   104,   296,    42,    43,    44,    45,
      98,  -110,   233,    37,    38,    39,    40,    41,    42,    43,
      44,    45,   135,   165,   144,    35,   259,    36,   143,   251,
      77,    79,    36,   251,   145,   171,   244,   245,   174,    47,
      48,    49,   173,   146,   175,   283,   254,   176,   123,   177,
      46,    47,    48,    49,   178,   193,    37,    38,    39,    40,
      41,    42,    43,    44,    45,   201,    42,    43,    44,   288,
     203,    96,   207,   289,   208,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,   211,   214,   212,    68,   213,
     231,   281,    11,    46,    47,    48,    49,   291,   270,    47,
      48,    49,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,   106,    92,    93,    94,    95,   297,   107,    11,
     271,   249,   272,   273,   274,   275,    92,    93,    94,    95,
     271,    12,   272,   273,   274,   275,   195,   276,   180,   181,
     182,   183,   184,   185,   186,   187,   165,   276,   189,   190,
     253,   256,   189,   190,   257,   266,   277,    96,    12,   298,
     190,   268,   269,   285,   286,   287,   277,   290,   295,   292,
      96,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   293,    69,   200,   240,   236,   205,   237,   260,   294,
     130,   243,   255,     0,   115,     0,     0,    61
};

static const yytype_int16 yycheck[] =
{
       8,    36,    10,     2,     3,    35,    36,   122,    80,    81,
      82,    83,    84,    85,    86,     9,    18,    32,    49,    10,
     135,     3,     4,    13,    32,    33,    98,    24,     9,    35,
      13,    13,    12,    19,     7,    25,     9,   152,     9,     7,
       8,    81,    28,    77,    84,    10,    77,    77,    10,    10,
     122,    10,    60,    10,    10,    63,    10,    10,     9,    67,
     249,    76,    29,   135,   253,    64,    65,    66,    82,    83,
      72,    73,   144,    72,   189,   190,     9,    25,    11,   109,
     152,    49,    29,    77,   156,    91,    92,    93,    94,    95,
      89,    82,    83,     3,     4,    85,    77,    78,   213,   171,
      99,    81,    85,    85,    77,    78,    77,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    81,   189,   190,    81,
      81,    26,    81,    29,    81,    81,    77,    81,    81,     3,
       4,    13,   204,    81,     9,   207,    10,   208,   209,     9,
       9,   213,    11,     9,    77,    78,    79,    80,   147,    33,
       7,    35,     9,    37,    11,    39,     9,   187,   157,    83,
      84,   169,   212,     3,     4,     9,   201,   239,     9,    24,
      10,   201,    81,   203,     9,   290,    45,    46,    47,    48,
      27,    81,   188,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    25,    77,     9,     9,   231,    11,    77,   249,
       9,   231,    11,   253,    19,    82,   205,   206,    10,    78,
      79,    80,    77,    28,    10,   265,   215,    10,   290,    10,
      77,    78,    79,    80,    10,    81,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     9,    45,    46,    47,    48,
      61,    49,    71,   273,    71,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    34,    34,     9,     0,     9,
       9,   260,    31,    77,    78,    79,    80,   275,    11,    78,
      79,    80,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    10,     5,     6,     7,     8,   295,    10,    31,
      33,     9,    35,    36,    37,    38,     5,     6,     7,     8,
      33,    70,    35,    36,    37,    38,    77,    50,    61,    62,
      63,    64,    65,    66,    67,    68,    77,    50,     3,     4,
       9,     9,     3,     4,    11,    10,    69,    49,    70,    10,
       4,    78,    12,    10,    12,    34,    69,     9,    38,    80,
      49,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    48,    13,   145,   200,   193,   150,   194,   238,   278,
      87,   204,   216,    -1,    81,    -1,    -1,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    31,    70,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    13,    85,   147,
     147,   147,    29,    29,     7,     9,    11,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    77,    78,    79,    80,
     105,   116,   117,   118,   130,   132,   133,   134,   135,   144,
      26,    77,   110,    24,   110,    32,    76,    29,     0,    88,
      13,   110,   110,    77,   117,   131,   132,     9,   131,   132,
       9,     9,     9,     9,     9,     9,    82,    83,    24,   106,
     107,    81,     5,     6,     7,     8,    49,   110,    27,   110,
     147,   147,   147,   110,     9,   147,    10,    10,    10,    81,
      12,     9,    78,   130,   146,   146,     7,    78,   130,   145,
     145,   145,     9,   130,   138,   139,   140,   141,   142,   130,
     116,   108,   109,   110,   147,    25,   112,   113,   117,   117,
     117,   117,   117,    77,     9,    19,    28,   114,   115,   130,
     136,   137,    25,   147,    18,    72,    73,   101,   102,   103,
     104,    33,    35,    37,    39,    77,   120,   121,   122,   124,
     129,    82,   132,    77,    10,    10,    10,    10,    10,   138,
      61,    62,    63,    64,    65,    66,    67,    68,   143,     3,
       4,    10,    84,    81,    49,    77,   111,   138,   119,   130,
     105,     9,   147,    61,    81,   112,   138,    71,    71,   130,
     147,    34,     9,     9,    34,    10,    81,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   110,   125,   130,
      10,     9,   132,   117,   138,   138,   109,   111,    10,    81,
     106,   131,   132,   137,   147,   147,   130,   122,   122,     9,
     123,   124,   138,     9,   147,   121,     9,    11,   126,   131,
     114,   130,    10,   123,    10,    81,    10,   123,    78,    12,
      11,    33,    35,    36,    37,    38,    50,    69,   127,   128,
      10,   147,    10,   124,    10,    10,    12,    34,    48,   132,
       9,   110,    80,    48,   128,    38,   138,   110,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    89,    90,    91,    92,
      93,    94,    95,    95,    96,    97,    97,    98,    99,    99,
     100,   101,   101,   101,   102,   103,   104,   105,   105,   106,
     107,   107,   108,   108,   109,   109,   109,   110,   111,   112,
     112,   113,   114,   114,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   118,   118,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   123,   123,   124,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   126,   126,
     126,   127,   127,   127,   128,   128,   128,   128,   128,   128,
     128,   128,   129,   129,   129,   129,   130,   130,   130,   130,
     131,   131,   132,   132,   132,   133,   133,   133,   133,   133,
     134,   134,   135,   135,   136,   136,   137,   138,   138,   138,
     138,   139,   139,   139,   140,   141,   142,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   144,   145,   145,
     145,   146,   146,   147,   147
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     7,
       4,     4,     5,     8,     6,     4,     6,     3,     3,     3,
       5,     1,     1,     1,     3,     3,     3,     1,     1,     2,
       0,     2,     1,     3,     1,     2,     3,     1,     1,     0,
       1,     2,     4,     1,     3,     1,     3,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       3,     1,     1,     4,     1,     3,     1,     1,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1,     0,     2,
       3,     0,     1,     2,     2,     1,     2,     2,     2,     2,
       4,     2,     4,     5,     7,     4,     1,     5,     4,     3,
       1,     3,     1,     1,     3,     1,     1,     1,     1,     1,
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
#line 1707 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 178 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].statement));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 1716 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 185 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1726 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 191 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1736 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 197 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1746 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 203 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1757 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 210 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1768 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 217 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1779 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 224 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1790 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 231 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1801 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 238 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1812 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 245 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1823 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 252 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1834 "y.tab.c"
    break;

  case 15: /* statement: alter_table_statement  */
#line 259 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = ALTER_TABLE_STMT;
            statement->alter_table_node = (yyvsp[0].alter_table_node);
            (yyval.statement) = statement;
        }
#line 1845 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table '(' base_table_element_commalist ')' end  */
#line 278 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].strVal);
            create_table_node->base_table_element_commalist = (yyvsp[-2].list);
            (yyval.create_table_node) = create_table_node;
        }
#line 1856 "y.tab.c"
    break;

  case 20: /* drop_table_statement: DROP TABLE table end  */
#line 288 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].strVal);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1866 "y.tab.c"
    break;

  case 21: /* select_statement: SELECT selection table_exp end  */
#line 297 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1877 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table values_or_query_spec end  */
#line 307 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-2].strVal);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1889 "y.tab.c"
    break;

  case 23: /* insert_statement: INSERT INTO table '(' columns ')' values_or_query_spec end  */
#line 315 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-5].strVal);
            node->column_list = (yyvsp[-3].list);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1902 "y.tab.c"
    break;

  case 24: /* update_statement: UPDATE table SET assignments opt_where_clause end  */
#line 327 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-4].strVal);
            node->assignment_set_node = (yyvsp[-2].assignment_set_node);
            node->where_clause = (yyvsp[-1].where_clause_node);
            (yyval.update_node) = node;
        }
#line 1914 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table end  */
#line 338 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.delete_node) = node;
        }
#line 1924 "y.tab.c"
    break;

  case 26: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 344 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].strVal);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1935 "y.tab.c"
    break;

  case 27: /* describe_statement: DESCRIBE table end  */
#line 354 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.describe_node) = node;
        }
#line 1945 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW TABLES end  */
#line 363 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1953 "y.tab.c"
    break;

  case 29: /* show_statement: SHOW MEMORY end  */
#line 367 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1961 "y.tab.c"
    break;

  case 30: /* alter_table_statement: ALTER TABLE table alter_table_action end  */
#line 374 "sql.y"
        {
            (yyval.alter_table_node) = make_alter_table_node();
            (yyval.alter_table_node)->table_name = (yyvsp[-2].strVal);
            (yyval.alter_table_node)->action = (yyvsp[-1].alter_table_action);
        }
#line 1971 "y.tab.c"
    break;

  case 31: /* alter_table_action: add_column_def  */
#line 382 "sql.y"
        {
            AlterTableAction *action = make_alter_table_action();
            action->type = ALTER_TO_ADD_COLUMN;
            action->action.add_column = (yyvsp[0].add_column_def);
            (yyval.alter_table_action) = action;
        }
#line 1982 "y.tab.c"
    break;

  case 32: /* alter_table_action: drop_column_def  */
#line 389 "sql.y"
        {
            AlterTableAction *action = make_alter_table_action();
            action->type = ALTER_TO_DROP_COLUMN;
            action->action.drop_column = (yyvsp[0].drop_column_def);
            (yyval.alter_table_action) = action;
        }
#line 1993 "y.tab.c"
    break;

  case 33: /* alter_table_action: change_column_def  */
#line 396 "sql.y"
        {
            AlterTableAction *action = make_alter_table_action();
            action->type = ALTER_TO_CHANGE_COLUMN;
            action->action.change_column = (yyvsp[0].change_column_def);
            (yyval.alter_table_action) = action;
        }
#line 2004 "y.tab.c"
    break;

  case 34: /* add_column_def: ADD COLUMN column_def  */
#line 405 "sql.y"
        {
            AddColumnDef *node = make_add_column_def();
            node->column_def = (yyvsp[0].column_def_node);
            (yyval.add_column_def) = node;
        }
#line 2014 "y.tab.c"
    break;

  case 35: /* drop_column_def: DROP COLUMN column  */
#line 413 "sql.y"
        {
            DropColumnDef *node = make_drop_column_def();
            node->column_name = (yyvsp[0].column_node);
            (yyval.drop_column_def) = node;
        }
#line 2024 "y.tab.c"
    break;

  case 36: /* change_column_def: CHANGE column column_def  */
#line 421 "sql.y"
        {
            ChangeColumnDef *node = make_change_column_def();
            node->old_column_name = (yyvsp[-1].column_node);
            node->new_column_def = (yyvsp[0].column_def_node);
            (yyval.change_column_def) = node;
        }
#line 2035 "y.tab.c"
    break;

  case 37: /* selection: scalar_exp_commalist  */
#line 430 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_list = (yyvsp[0].list);
            (yyval.selection_node) = selection_node;
        }
#line 2046 "y.tab.c"
    break;

  case 38: /* selection: '*'  */
#line 437 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 2056 "y.tab.c"
    break;

  case 39: /* table_exp: from_clause opt_where_clause  */
#line 445 "sql.y"
        {
            TableExpNode *table_exp = make_table_exp_node();
            table_exp->from_clause = (yyvsp[-1].from_clause_node);
            table_exp->where_clause = (yyvsp[0].where_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 2067 "y.tab.c"
    break;

  case 40: /* from_clause: %empty  */
#line 454 "sql.y"
        {
            (yyval.from_clause_node) = NULL;
        }
#line 2075 "y.tab.c"
    break;

  case 41: /* from_clause: FROM table_ref_commalist  */
#line 458 "sql.y"
        {
            FromClauseNode *from_clause = make_from_clause_node();
            from_clause->from = (yyvsp[0].table_ref_set_node);
            (yyval.from_clause_node) = from_clause;
        }
#line 2085 "y.tab.c"
    break;

  case 42: /* table_ref_commalist: table_ref  */
#line 466 "sql.y"
        {
            TableRefSetNode *table_ref_set = make_table_ref_set_node();
            add_table_ref_to_set(table_ref_set, (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = table_ref_set;
        }
#line 2095 "y.tab.c"
    break;

  case 43: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 472 "sql.y"
        {
            add_table_ref_to_set((yyvsp[-2].table_ref_set_node), (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = (yyvsp[-2].table_ref_set_node);
        }
#line 2104 "y.tab.c"
    break;

  case 44: /* table_ref: table  */
#line 479 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2114 "y.tab.c"
    break;

  case 45: /* table_ref: table range_variable  */
#line 485 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-1].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2125 "y.tab.c"
    break;

  case 46: /* table_ref: table AS range_variable  */
#line 492 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-2].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2136 "y.tab.c"
    break;

  case 47: /* table: IDENTIFIER  */
#line 501 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2144 "y.tab.c"
    break;

  case 48: /* range_variable: IDENTIFIER  */
#line 507 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2152 "y.tab.c"
    break;

  case 49: /* opt_where_clause: %empty  */
#line 513 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 2160 "y.tab.c"
    break;

  case 50: /* opt_where_clause: where_clause  */
#line 517 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 2168 "y.tab.c"
    break;

  case 51: /* where_clause: WHERE condition  */
#line 523 "sql.y"
        {
            WhereClauseNode *where_clause_node = make_where_clause_node();
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 2178 "y.tab.c"
    break;

  case 52: /* values_or_query_spec: VALUES '(' value_items ')'  */
#line 531 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = (yyvsp[-1].list);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2189 "y.tab.c"
    break;

  case 53: /* values_or_query_spec: query_spec  */
#line 538 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = (yyvsp[0].query_spec_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2200 "y.tab.c"
    break;

  case 54: /* query_spec: SELECT selection table_exp  */
#line 547 "sql.y"
        {
            QuerySpecNode *query_spec = make_query_spec_node();
            query_spec->selection = (yyvsp[-1].selection_node);
            query_spec->table_exp = (yyvsp[0].table_exp_node);
            (yyval.query_spec_node) = query_spec;
        }
#line 2211 "y.tab.c"
    break;

  case 55: /* scalar_exp_commalist: scalar_exp  */
#line 556 "sql.y"
        {
            List *scalar_exp_list = create_list(NODE_SCALAR_EXP);
            append_list(scalar_exp_list, (yyvsp[0].scalar_exp_node));
            (yyval.list) = scalar_exp_list;
        }
#line 2221 "y.tab.c"
    break;

  case 56: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 562 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].scalar_exp_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2230 "y.tab.c"
    break;

  case 57: /* scalar_exp: calculate  */
#line 569 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2241 "y.tab.c"
    break;

  case 58: /* scalar_exp: column  */
#line 576 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2252 "y.tab.c"
    break;

  case 59: /* scalar_exp: function  */
#line 583 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2263 "y.tab.c"
    break;

  case 60: /* scalar_exp: value_item  */
#line 590 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2274 "y.tab.c"
    break;

  case 61: /* scalar_exp: '(' scalar_exp ')'  */
#line 597 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2282 "y.tab.c"
    break;

  case 62: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 601 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].strVal);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2291 "y.tab.c"
    break;

  case 63: /* calculate: scalar_exp '+' scalar_exp  */
#line 608 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2303 "y.tab.c"
    break;

  case 64: /* calculate: scalar_exp '-' scalar_exp  */
#line 616 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2315 "y.tab.c"
    break;

  case 65: /* calculate: scalar_exp '*' scalar_exp  */
#line 624 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2327 "y.tab.c"
    break;

  case 66: /* calculate: scalar_exp '/' scalar_exp  */
#line 632 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2339 "y.tab.c"
    break;

  case 67: /* columns: column  */
#line 642 "sql.y"
        {
            List *column_set_node = create_list(NODE_COLUMN);
            append_list(column_set_node, (yyvsp[0].column_node));
            (yyval.list) = column_set_node;
        }
#line 2349 "y.tab.c"
    break;

  case 68: /* columns: columns ',' column  */
#line 648 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].column_node));
        }
#line 2358 "y.tab.c"
    break;

  case 69: /* base_table_element_commalist: base_table_element  */
#line 655 "sql.y"
        {
            List *base_table_element_commalist = create_list(NODE_BASE_TABLE_ELEMENT);
            append_list(base_table_element_commalist, (yyvsp[0].base_table_element));
            (yyval.list) = base_table_element_commalist;
        }
#line 2368 "y.tab.c"
    break;

  case 70: /* base_table_element_commalist: base_table_element_commalist ',' base_table_element  */
#line 661 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].base_table_element));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2377 "y.tab.c"
    break;

  case 71: /* base_table_element: column_def  */
#line 668 "sql.y"
        {
            (yyval.base_table_element) = make_base_table_element_node();
            (yyval.base_table_element)->column_def = (yyvsp[0].column_def_node);
            (yyval.base_table_element)->table_contraint_def = NULL;
            (yyval.base_table_element)->type = TELE_COLUMN_DEF;
        }
#line 2388 "y.tab.c"
    break;

  case 72: /* base_table_element: table_contraint_def  */
#line 675 "sql.y"
        {
            (yyval.base_table_element) = make_base_table_element_node();
            (yyval.base_table_element)->column_def = NULL;
            (yyval.base_table_element)->table_contraint_def = (yyvsp[0].table_contraint_def);
            (yyval.base_table_element)->type = TELE_TABLE_CONTRAINT_DEF;
        }
#line 2399 "y.tab.c"
    break;

  case 73: /* column_def: column_def_name data_type array_dim_clause column_def_opt_list  */
#line 697 "sql.y"
        {
            ColumnDefNode *column_def = make_column_def_node();
            column_def->column = (yyvsp[-3].column_def_name);
            column_def->data_type = (yyvsp[-2].data_type_node);
            column_def->array_dim = (yyvsp[-1].intVal);
            column_def->column_def_opt_list = (yyvsp[0].list);
            (yyval.column_def_node) = column_def;
        }
#line 2412 "y.tab.c"
    break;

  case 74: /* column_def_name_commalist: column_def_name  */
#line 708 "sql.y"
        {
            List *list = create_list(NODE_COLUMN_DEF_NAME);
            append_list(list, (yyvsp[0].column_def_name));
            (yyval.list) = list;
        }
#line 2422 "y.tab.c"
    break;

  case 75: /* column_def_name_commalist: column_def_name_commalist ',' column_def_name  */
#line 714 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].column_def_name));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2431 "y.tab.c"
    break;

  case 76: /* column_def_name: IDENTIFIER  */
#line 721 "sql.y"
        {
            ColumnDefName *column_def_name = make_column_def_name();
            column_def_name->column = (yyvsp[0].strVal);
            (yyval.column_def_name) = column_def_name;
        }
#line 2441 "y.tab.c"
    break;

  case 77: /* data_type: INT  */
#line 729 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_INT; 
        }
#line 2450 "y.tab.c"
    break;

  case 78: /* data_type: LONG  */
#line 734 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_LONG;  
        }
#line 2459 "y.tab.c"
    break;

  case 79: /* data_type: CHAR  */
#line 739 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_CHAR; 
        }
#line 2468 "y.tab.c"
    break;

  case 80: /* data_type: VARCHAR '(' INTVALUE ')'  */
#line 744 "sql.y"
        {
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_VARCHAR; 
            (yyval.data_type_node)->len = (yyvsp[-1].intVal);
        }
#line 2478 "y.tab.c"
    break;

  case 81: /* data_type: STRING  */
#line 750 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_STRING; 
        }
#line 2487 "y.tab.c"
    break;

  case 82: /* data_type: BOOL  */
#line 755 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_BOOL; 
        }
#line 2496 "y.tab.c"
    break;

  case 83: /* data_type: FLOAT  */
#line 760 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_FLOAT; 
        }
#line 2505 "y.tab.c"
    break;

  case 84: /* data_type: DOUBLE  */
#line 765 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_DOUBLE; 
        }
#line 2514 "y.tab.c"
    break;

  case 85: /* data_type: TIMESTAMP  */
#line 770 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_TIMESTAMP; 
        }
#line 2523 "y.tab.c"
    break;

  case 86: /* data_type: DATE  */
#line 775 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_DATE; 
        }
#line 2532 "y.tab.c"
    break;

  case 87: /* data_type: table  */
#line 780 "sql.y"
        {
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_REFERENCE;
            (yyval.data_type_node)->table_name = (yyvsp[0].strVal);
        }
#line 2542 "y.tab.c"
    break;

  case 88: /* array_dim_clause: %empty  */
#line 788 "sql.y"
        {
            (yyval.intVal) = 0;
        }
#line 2550 "y.tab.c"
    break;

  case 89: /* array_dim_clause: '[' ']'  */
#line 792 "sql.y"
        {
            (yyval.intVal) = 1;
        }
#line 2558 "y.tab.c"
    break;

  case 90: /* array_dim_clause: array_dim_clause '[' ']'  */
#line 796 "sql.y"
        {
            (yyval.intVal)++;
        }
#line 2566 "y.tab.c"
    break;

  case 91: /* column_def_opt_list: %empty  */
#line 802 "sql.y"
        {
            (yyval.list) = NULL;
        }
#line 2574 "y.tab.c"
    break;

  case 92: /* column_def_opt_list: column_def_opt  */
#line 806 "sql.y"
        {
            (yyval.list) = create_list(NODE_COLUMN_DEF_OPT);
            append_list((yyval.list), (yyvsp[0].column_def_opt));
        }
#line 2583 "y.tab.c"
    break;

  case 93: /* column_def_opt_list: column_def_opt_list column_def_opt  */
#line 811 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].column_def_opt));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 2592 "y.tab.c"
    break;

  case 94: /* column_def_opt: NOT NULLX  */
#line 818 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_NOT_NULL; 
        }
#line 2601 "y.tab.c"
    break;

  case 95: /* column_def_opt: UNIQUE  */
#line 823 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_UNIQUE; 
        }
#line 2610 "y.tab.c"
    break;

  case 96: /* column_def_opt: PRIMARY KEY  */
#line 828 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_PRIMARY_KEY; 
        }
#line 2619 "y.tab.c"
    break;

  case 97: /* column_def_opt: DEFAULT value_item  */
#line 833 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_DEFAULT_VALUE;
            (yyval.column_def_opt)->value = (yyvsp[0].value_item_node);
        }
#line 2629 "y.tab.c"
    break;

  case 98: /* column_def_opt: DEFAULT NULLX  */
#line 839 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_DEFAULT_NULL;
        }
#line 2638 "y.tab.c"
    break;

  case 99: /* column_def_opt: COMMENT STRINGVALUE  */
#line 844 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_COMMENT;
            (yyval.column_def_opt)->comment = (yyvsp[0].strVal);
        }
#line 2648 "y.tab.c"
    break;

  case 100: /* column_def_opt: CHECK '(' condition ')'  */
#line 850 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_CHECK_CONDITION;
            (yyval.column_def_opt)->condition = (yyvsp[-1].condition_node);
        }
#line 2658 "y.tab.c"
    break;

  case 101: /* column_def_opt: REFERENCES table  */
#line 856 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_REFERENECS;
            (yyval.column_def_opt)->refer_table = (yyvsp[0].strVal);
        }
#line 2668 "y.tab.c"
    break;

  case 102: /* table_contraint_def: UNIQUE '(' column_def_name_commalist ')'  */
#line 864 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_UNIQUE;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-1].list);
        }
#line 2678 "y.tab.c"
    break;

  case 103: /* table_contraint_def: PRIMARY KEY '(' column_def_name_commalist ')'  */
#line 870 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_PRIMARY_KEY;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-1].list);
        }
#line 2688 "y.tab.c"
    break;

  case 104: /* table_contraint_def: FOREIGN KEY '(' column_def_name_commalist ')' REFERENCES table  */
#line 876 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_FOREIGN_KEY;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-3].list);
            (yyval.table_contraint_def)->table = (yyvsp[0].strVal);
        }
#line 2699 "y.tab.c"
    break;

  case 105: /* table_contraint_def: CHECK '(' condition ')'  */
#line 883 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_CHECK;
            (yyval.table_contraint_def)->condition = (yyvsp[-1].condition_node);
        }
#line 2709 "y.tab.c"
    break;

  case 106: /* column: IDENTIFIER  */
#line 891 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[0].strVal);
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2720 "y.tab.c"
    break;

  case 107: /* column: '(' IDENTIFIER ')' '.' column  */
#line 898 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->sub_column = (yyvsp[0].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2732 "y.tab.c"
    break;

  case 108: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 906 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->scalar_exp_list = (yyvsp[-1].list);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2744 "y.tab.c"
    break;

  case 109: /* column: IDENTIFIER '.' column  */
#line 914 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = (yyvsp[-2].strVal);
        }
#line 2753 "y.tab.c"
    break;

  case 110: /* value_items: value_item  */
#line 921 "sql.y"
        {
            List *value_list = create_list(NODE_VALUE_ITEM);
            append_list(value_list, (yyvsp[0].value_item_node));
            (yyval.list) = value_list;
        }
#line 2763 "y.tab.c"
    break;

  case 111: /* value_items: value_items ',' value_item  */
#line 927 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].value_item_node));
        }
#line 2772 "y.tab.c"
    break;

  case 112: /* value_item: atom  */
#line 934 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_ATOM;
            node->value.atom = (yyvsp[0].atom_node);
            (yyval.value_item_node) = node;
        }
#line 2783 "y.tab.c"
    break;

  case 113: /* value_item: NULLX  */
#line 941 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_NULL;
            (yyval.value_item_node) = node;
        }
#line 2793 "y.tab.c"
    break;

  case 114: /* value_item: '[' value_items ']'  */
#line 947 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_ARRAY;
            node->value.value_list = (yyvsp[-1].list);
            (yyval.value_item_node) = node;
        }
#line 2804 "y.tab.c"
    break;

  case 115: /* atom: INTVALUE  */
#line 956 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.intval = (yyvsp[0].intVal);
            node->type = A_INT;
            (yyval.atom_node) = node;
        }
#line 2815 "y.tab.c"
    break;

  case 116: /* atom: BOOLVALUE  */
#line 963 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.boolval = (yyvsp[0].boolVal);
            node->type = A_BOOL;
            (yyval.atom_node) = node;
        }
#line 2826 "y.tab.c"
    break;

  case 117: /* atom: STRINGVALUE  */
#line 970 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.strval = (yyvsp[0].strVal);
            node->type = A_STRING;
            (yyval.atom_node) = node;
        }
#line 2837 "y.tab.c"
    break;

  case 118: /* atom: FLOATVALUE  */
#line 977 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.floatval = (yyvsp[0].floatVal);
            node->type = A_FLOAT;
            (yyval.atom_node) = node;
        }
#line 2848 "y.tab.c"
    break;

  case 119: /* atom: REFERVALUE  */
#line 984 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.referval = (yyvsp[0].referVal);
            node->type = A_REFERENCE;
            (yyval.atom_node) = node;
        }
#line 2859 "y.tab.c"
    break;

  case 120: /* REFERVALUE: '(' value_items ')'  */
#line 994 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_list = (yyvsp[-1].list);
            (yyval.referVal) = refer;
        }
#line 2870 "y.tab.c"
    break;

  case 121: /* REFERVALUE: REF '(' condition ')'  */
#line 1002 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.referVal) = refer;
        }
#line 2881 "y.tab.c"
    break;

  case 122: /* BOOLVALUE: TRUE  */
#line 1011 "sql.y"
        {
            (yyval.boolVal) = true;
        }
#line 2889 "y.tab.c"
    break;

  case 123: /* BOOLVALUE: FALSE  */
#line 1015 "sql.y"
        {
            (yyval.boolVal) = false;
        }
#line 2897 "y.tab.c"
    break;

  case 124: /* assignments: assignment  */
#line 1021 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2907 "y.tab.c"
    break;

  case 125: /* assignments: assignments ',' assignment  */
#line 1027 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2916 "y.tab.c"
    break;

  case 126: /* assignment: column EQ value_item  */
#line 1034 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2927 "y.tab.c"
    break;

  case 127: /* condition: condition OR condition  */
#line 1043 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2939 "y.tab.c"
    break;

  case 128: /* condition: condition AND condition  */
#line 1051 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2951 "y.tab.c"
    break;

  case 129: /* condition: '(' condition ')'  */
#line 1059 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2959 "y.tab.c"
    break;

  case 130: /* condition: predicate  */
#line 1063 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2970 "y.tab.c"
    break;

  case 131: /* predicate: comparison_predicate  */
#line 1072 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2981 "y.tab.c"
    break;

  case 132: /* predicate: like_predicate  */
#line 1079 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2992 "y.tab.c"
    break;

  case 133: /* predicate: in_predicate  */
#line 1086 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 3003 "y.tab.c"
    break;

  case 134: /* comparison_predicate: column compare scalar_exp  */
#line 1095 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 3015 "y.tab.c"
    break;

  case 135: /* like_predicate: column LIKE value_item  */
#line 1105 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 3026 "y.tab.c"
    break;

  case 136: /* in_predicate: column IN '(' value_items ')'  */
#line 1114 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_list = (yyvsp[-1].list);
            (yyval.in_node) = in_node;
        }
#line 3037 "y.tab.c"
    break;

  case 137: /* compare: EQ  */
#line 1142 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 3043 "y.tab.c"
    break;

  case 138: /* compare: NE  */
#line 1143 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 3049 "y.tab.c"
    break;

  case 139: /* compare: GT  */
#line 1144 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 3055 "y.tab.c"
    break;

  case 140: /* compare: GE  */
#line 1145 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 3061 "y.tab.c"
    break;

  case 141: /* compare: LT  */
#line 1146 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 3067 "y.tab.c"
    break;

  case 142: /* compare: LE  */
#line 1147 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 3073 "y.tab.c"
    break;

  case 143: /* function: MAX '(' non_all_function_value ')'  */
#line 1151 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3084 "y.tab.c"
    break;

  case 144: /* function: MIN '(' non_all_function_value ')'  */
#line 1158 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3095 "y.tab.c"
    break;

  case 145: /* function: COUNT '(' function_value ')'  */
#line 1165 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3106 "y.tab.c"
    break;

  case 146: /* function: SUM '(' function_value ')'  */
#line 1172 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3117 "y.tab.c"
    break;

  case 147: /* function: AVG '(' function_value ')'  */
#line 1179 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3128 "y.tab.c"
    break;

  case 148: /* function_value: INTVALUE  */
#line 1188 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3139 "y.tab.c"
    break;

  case 149: /* function_value: column  */
#line 1195 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3150 "y.tab.c"
    break;

  case 150: /* function_value: '*'  */
#line 1202 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 3160 "y.tab.c"
    break;

  case 151: /* non_all_function_value: INTVALUE  */
#line 1210 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3171 "y.tab.c"
    break;

  case 152: /* non_all_function_value: column  */
#line 1217 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3182 "y.tab.c"
    break;


#line 3186 "y.tab.c"

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

#line 1228 "sql.y"

