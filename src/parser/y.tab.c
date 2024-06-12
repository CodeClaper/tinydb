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
#include "y.tab.h"

int yywrap() {
    return 1;
}
int yylex();

#line 87 "y.tab.c"

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
    SYSTEM = 317,                  /* SYSTEM  */
    CONFIG = 318,                  /* CONFIG  */
    MEMORY = 319,                  /* MEMORY  */
    IDENTIFIER = 320,              /* IDENTIFIER  */
    INTVALUE = 321,                /* INTVALUE  */
    FLOATVALUE = 322,              /* FLOATVALUE  */
    STRINGVALUE = 323              /* STRINGVALUE  */
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
#define SYSTEM 317
#define CONFIG 318
#define MEMORY 319
#define IDENTIFIER 320
#define INTVALUE 321
#define FLOATVALUE 322
#define STRINGVALUE 323

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "sql.y"

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
   ValueItemSetNode             *value_item_set_node;
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
   CreateTableNode              *create_table_node;
   DropTableNode                *drop_table_node;
   SelectNode                   *select_node;
   InsertNode                   *insert_node;
   UpdateNode                   *update_node;
   DeleteNode                   *delete_node;
   DescribeNode                 *describe_node;
   ShowNode                     *show_node;
   Statement                    *statement;
   List                         *list;

#line 326 "y.tab.c"

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
  YYSYMBOL_SYSTEM = 70,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 71,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 72,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 73,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 74,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 75,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 76,               /* STRINGVALUE  */
  YYSYMBOL_77_ = 77,                       /* ','  */
  YYSYMBOL_78_ = 78,                       /* '.'  */
  YYSYMBOL_79_ = 79,                       /* '{'  */
  YYSYMBOL_80_ = 80,                       /* '}'  */
  YYSYMBOL_81_ = 81,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_statements = 83,                /* statements  */
  YYSYMBOL_statement = 84,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 85, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 86, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 87, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 88,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 89,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 90,          /* select_statement  */
  YYSYMBOL_insert_statement = 91,          /* insert_statement  */
  YYSYMBOL_update_statement = 92,          /* update_statement  */
  YYSYMBOL_delete_statement = 93,          /* delete_statement  */
  YYSYMBOL_describe_statement = 94,        /* describe_statement  */
  YYSYMBOL_show_statement = 95,            /* show_statement  */
  YYSYMBOL_selection = 96,                 /* selection  */
  YYSYMBOL_table_exp = 97,                 /* table_exp  */
  YYSYMBOL_from_clause = 98,               /* from_clause  */
  YYSYMBOL_table_ref_commalist = 99,       /* table_ref_commalist  */
  YYSYMBOL_table_ref = 100,                /* table_ref  */
  YYSYMBOL_table = 101,                    /* table  */
  YYSYMBOL_range_variable = 102,           /* range_variable  */
  YYSYMBOL_opt_where_clause = 103,         /* opt_where_clause  */
  YYSYMBOL_where_clause = 104,             /* where_clause  */
  YYSYMBOL_values_or_query_spec = 105,     /* values_or_query_spec  */
  YYSYMBOL_query_spec = 106,               /* query_spec  */
  YYSYMBOL_scalar_exp_commalist = 107,     /* scalar_exp_commalist  */
  YYSYMBOL_scalar_exp = 108,               /* scalar_exp  */
  YYSYMBOL_calculate = 109,                /* calculate  */
  YYSYMBOL_columns = 110,                  /* columns  */
  YYSYMBOL_base_table_element_commalist = 111, /* base_table_element_commalist  */
  YYSYMBOL_base_table_element = 112,       /* base_table_element  */
  YYSYMBOL_column_def = 113,               /* column_def  */
  YYSYMBOL_column_def_name_commalist = 114, /* column_def_name_commalist  */
  YYSYMBOL_column_def_name = 115,          /* column_def_name  */
  YYSYMBOL_data_type = 116,                /* data_type  */
  YYSYMBOL_array_dim_clause = 117,         /* array_dim_clause  */
  YYSYMBOL_column_def_opt_list = 118,      /* column_def_opt_list  */
  YYSYMBOL_column_def_opt = 119,           /* column_def_opt  */
  YYSYMBOL_table_contraint_def = 120,      /* table_contraint_def  */
  YYSYMBOL_column = 121,                   /* column  */
  YYSYMBOL_value_items = 122,              /* value_items  */
  YYSYMBOL_value_item = 123,               /* value_item  */
  YYSYMBOL_atom = 124,                     /* atom  */
  YYSYMBOL_REFERVALUE = 125,               /* REFERVALUE  */
  YYSYMBOL_BOOLVALUE = 126,                /* BOOLVALUE  */
  YYSYMBOL_assignments = 127,              /* assignments  */
  YYSYMBOL_assignment = 128,               /* assignment  */
  YYSYMBOL_condition = 129,                /* condition  */
  YYSYMBOL_predicate = 130,                /* predicate  */
  YYSYMBOL_comparison_predicate = 131,     /* comparison_predicate  */
  YYSYMBOL_like_predicate = 132,           /* like_predicate  */
  YYSYMBOL_in_predicate = 133,             /* in_predicate  */
  YYSYMBOL_compare = 134,                  /* compare  */
  YYSYMBOL_function = 135,                 /* function  */
  YYSYMBOL_function_value = 136,           /* function_value  */
  YYSYMBOL_non_all_function_value = 137,   /* non_all_function_value  */
  YYSYMBOL_end = 138                       /* end  */
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
#define YYFINAL  65
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  281

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
       9,    10,     7,     5,    77,     6,    78,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    81,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    11,     2,    12,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    79,     2,    80,     2,     2,     2,     2,
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
      73,    74,    75,    76
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   160,   160,   165,   172,   178,   184,   190,   197,   204,
     211,   218,   225,   232,   239,   248,   251,   254,   258,   268,
     277,   287,   295,   307,   318,   324,   334,   343,   347,   353,
     360,   368,   378,   381,   389,   395,   402,   408,   415,   424,
     430,   437,   440,   446,   454,   461,   470,   479,   485,   492,
     499,   506,   513,   520,   524,   531,   539,   547,   555,   565,
     571,   578,   584,   591,   598,   620,   631,   637,   644,   652,
     657,   662,   667,   673,   678,   683,   688,   693,   698,   703,
     712,   715,   719,   726,   729,   734,   741,   746,   751,   756,
     762,   767,   773,   779,   787,   793,   799,   806,   814,   821,
     829,   837,   844,   850,   857,   864,   870,   879,   886,   893,
     900,   907,   917,   925,   934,   938,   944,   950,   957,   966,
     974,   982,   986,   995,  1002,  1009,  1018,  1028,  1037,  1066,
    1067,  1068,  1069,  1070,  1071,  1074,  1081,  1088,  1095,  1102,
    1111,  1118,  1125,  1133,  1140,  1149,  1150
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
  "EQ", "NE", "GT", "GE", "LT", "LE", "IN", "LIKE", "NOT", "SYSTEM",
  "CONFIG", "MEMORY", "IDENTIFIER", "INTVALUE", "FLOATVALUE",
  "STRINGVALUE", "','", "'.'", "'{'", "'}'", "';'", "$accept",
  "statements", "statement", "begin_transaction_statement",
  "commit_transaction_statement", "rollback_transaction_statement",
  "create_table_statement", "drop_table_statement", "select_statement",
  "insert_statement", "update_statement", "delete_statement",
  "describe_statement", "show_statement", "selection", "table_exp",
  "from_clause", "table_ref_commalist", "table_ref", "table",
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

#define YYPACT_NINF (-195)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-103)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     308,    21,    21,    21,   -10,    49,    92,    16,    53,    65,
      53,    40,   280,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -195,    55,  -195,  -195,  -195,
      53,    53,  -195,   132,   183,    85,   102,   118,   119,   122,
     133,  -195,  -195,  -195,    -5,  -195,  -195,  -195,    89,    70,
     206,  -195,  -195,  -195,  -195,  -195,  -195,  -195,    53,  -195,
     124,    53,    21,    21,    21,  -195,  -195,  -195,   140,    21,
      14,   153,    29,    76,   183,    13,  -195,     7,     7,    31,
      31,    31,    34,    52,   178,    53,    21,   131,   178,   178,
     178,   178,   178,    97,   172,    52,    19,  -195,  -195,  -195,
      -4,  -195,   108,  -195,  -195,   183,  -195,   109,  -195,  -195,
     180,   194,  -195,  -195,  -195,   199,   200,   205,    57,   279,
     142,  -195,  -195,  -195,  -195,  -195,   -20,   116,  -195,    47,
    -195,    34,  -195,  -195,   206,    10,    10,   149,   149,  -195,
      52,    92,   207,    21,  -195,   156,    11,  -195,    34,  -195,
     198,   230,   233,   211,  -195,    37,  -195,  -195,   261,  -195,
      52,  -195,   238,  -195,  -195,  -195,  -195,  -195,   234,  -195,
    -195,  -195,  -195,  -195,  -195,   247,   183,   178,    34,    34,
    -195,  -195,    53,   177,  -195,  -195,   113,    38,  -195,    89,
     183,  -195,   183,    52,    21,    17,   256,   193,    34,   266,
      21,    -4,  -195,  -195,  -195,   272,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,   271,  -195,  -195,   183,  -195,   206,   282,
    -195,  -195,  -195,    39,    52,  -195,    41,  -195,  -195,  -195,
    -195,   193,    42,  -195,   237,   193,  -195,  -195,   209,   275,
     235,    44,    21,  -195,  -195,    45,  -195,   193,  -195,    46,
     274,  -195,   276,   255,  -195,   188,   281,    53,   216,   245,
     241,  -195,  -195,  -195,  -195,  -195,   267,  -195,  -195,  -195,
    -195,  -195,    34,  -195,  -195,  -195,  -195,    53,   257,  -195,
    -195
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   145,     0,    15,    16,    17,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   105,    98,   107,   110,   109,    32,    29,
      47,    49,    50,    52,   104,   111,   108,    51,     0,    39,
       0,     0,     0,     0,     0,     1,     3,   146,     0,     0,
      98,     0,     0,    52,     0,     0,   102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    27,    28,
       0,    19,     0,    53,   112,     0,   106,     0,   143,   144,
       0,     0,   142,   140,   141,     0,     0,     0,     0,     0,
       0,   122,   123,   124,   125,   101,     0,    33,    34,    36,
      20,     0,    31,    42,    48,    55,    56,    57,    58,    54,
       0,     0,     0,     0,    45,     0,    41,   116,     0,    24,
       0,     0,     0,     0,    68,     0,    61,    63,     0,    64,
       0,   103,     0,   135,   136,   137,   138,   139,     0,   129,
     130,   131,   132,   133,   134,     0,     0,     0,     0,     0,
     113,   100,     0,     0,    40,    37,    43,     0,    59,    32,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,    69,    70,     0,    73,    74,    75,    76,
      78,    77,    79,    80,    99,   121,     0,   127,   126,   119,
     120,    35,    38,     0,     0,    46,     0,   118,   117,    23,
      25,     0,     0,    66,     0,     0,    18,    62,     0,     0,
      83,     0,     0,    60,    44,     0,    94,     0,    97,     0,
       0,    81,     0,     0,    87,     0,     0,     0,     0,     0,
      65,    84,   128,    22,    95,    67,     0,    72,    82,    88,
      90,    89,     0,    93,    91,    86,    85,     0,     0,    96,
      92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -195,  -195,   294,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,   166,   120,  -195,  -195,   126,    -8,
     150,   186,  -195,   112,  -195,   252,    -6,  -195,  -195,  -195,
     136,  -195,  -194,   -93,  -195,  -195,  -195,    78,  -195,   -69,
     -33,   -28,  -195,  -195,  -195,  -195,   155,  -103,  -195,  -195,
    -195,  -195,  -195,  -195,   104,   273,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    48,    86,    87,   127,   128,   129,
     185,   132,   133,   143,   144,    49,    50,    51,   187,   155,
     156,   157,   232,   233,   213,   240,   260,   261,   159,    52,
      72,    53,    54,    55,    56,   146,   147,   120,   121,   122,
     123,   124,   177,    57,   115,   110,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,    75,    62,    28,    29,    73,    76,   158,   109,   109,
     114,   114,   114,   119,   125,   168,   107,    91,    92,    30,
     178,   179,    68,    69,   102,   106,   145,    71,   186,   150,
      25,   151,    25,   152,    25,   153,   131,   245,   112,   104,
     107,   249,    58,   118,   148,   195,    76,   200,   223,   119,
      94,   244,   246,    96,   262,   264,   266,    88,   141,    93,
     181,   107,   119,    97,    98,    99,   118,   142,    67,   154,
     101,   188,    63,    83,    84,   219,   220,   161,    31,   119,
      44,   108,   134,   135,   136,   137,   138,   130,   193,    61,
     105,   214,    83,    84,    77,   234,   183,   149,    26,    32,
      26,    33,    26,    34,    44,   113,   105,    44,   158,   119,
     119,    78,    64,    85,   201,   224,   178,   179,   105,   247,
     184,   105,   247,   247,   145,    44,    59,    79,    80,   119,
      70,    81,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    33,    82,    34,   191,   178,   179,    88,   217,   100,
     212,    95,   180,  -102,   265,   243,   131,   226,    89,    90,
      91,    92,    76,   103,   227,    44,    45,    46,    47,   278,
     139,   218,    35,    36,    37,    38,    39,    40,    41,    42,
      43,   140,   162,   241,   116,   117,   160,    33,    76,    34,
     163,   141,    74,   182,    34,   229,   230,    74,    93,    34,
     142,   236,    93,   119,   164,    70,    45,    46,    47,   165,
     166,    89,    90,    91,    92,   167,   190,   192,    35,    36,
      37,    38,    39,    40,    41,    42,    43,   271,    40,    41,
      42,    43,   196,    40,    41,    42,   270,   178,   179,   197,
     178,   179,   198,   263,   215,   199,   252,   248,   102,   273,
     184,    44,    45,    46,    47,    93,   216,    45,    46,    47,
     178,   179,    45,    46,    47,   231,   154,   280,   253,   279,
     254,   255,   256,   257,   253,   235,   254,   255,   256,   257,
      65,   238,   239,   250,   267,   258,   179,   251,   268,   269,
     272,   258,   274,   275,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,   259,   277,    66,   189,   221,   225,
     259,    11,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,   194,   222,    59,   242,   126,   237,   276,    11,
     169,   170,   171,   172,   173,   174,   175,   176,   228,     0,
       0,   111
};

static const yytype_int16 yycheck[] =
{
       8,    34,    10,     2,     3,    33,    34,   100,    77,    78,
      79,    80,    81,    82,    83,   118,     9,     7,     8,    29,
       3,     4,    30,    31,    10,    12,    95,    33,   131,    33,
      13,    35,    13,    37,    13,    39,    25,   231,     7,    10,
       9,   235,    26,     9,    25,   148,    74,    10,    10,   118,
      58,    10,    10,    61,    10,    10,    10,    77,    19,    49,
      80,     9,   131,    62,    63,    64,     9,    28,    13,    73,
      69,   140,    32,    78,    79,   178,   179,   105,    29,   148,
      73,    74,    88,    89,    90,    91,    92,    86,    77,    24,
      77,   160,    78,    79,     9,   198,    49,    96,    81,     7,
      81,     9,    81,    11,    73,    74,    77,    73,   201,   178,
     179,     9,    72,    24,    77,    77,     3,     4,    77,    77,
      73,    77,    77,    77,   193,    73,    73,     9,     9,   198,
      73,     9,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     9,     9,    11,   143,     3,     4,    77,   176,     9,
     158,    27,    10,    77,   247,   224,    25,   190,     5,     6,
       7,     8,   190,    10,   192,    73,    74,    75,    76,   272,
      73,   177,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     9,    73,   216,    80,    81,    78,     9,   216,    11,
      10,    19,     9,    77,    11,   194,   195,     9,    49,    11,
      28,   200,    49,   272,    10,    73,    74,    75,    76,    10,
      10,     5,     6,     7,     8,    10,     9,    61,    40,    41,
      42,    43,    44,    45,    46,    47,    48,   255,    45,    46,
      47,    48,    34,    45,    46,    47,    48,     3,     4,     9,
       3,     4,     9,   242,    10,    34,    11,    10,    10,   257,
      73,    73,    74,    75,    76,    49,     9,    74,    75,    76,
       3,     4,    74,    75,    76,     9,    73,    10,    33,   277,
      35,    36,    37,    38,    33,     9,    35,    36,    37,    38,
       0,     9,    11,    74,    10,    50,     4,    12,    12,    34,
       9,    50,    76,    48,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    69,    38,    12,   141,   182,   189,
      69,    31,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,   146,   183,    73,   223,    84,   201,   260,    31,
      61,    62,    63,    64,    65,    66,    67,    68,   193,    -1,
      -1,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    31,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    13,    81,   138,   138,   138,
      29,    29,     7,     9,    11,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    73,    74,    75,    76,    96,   107,
     108,   109,   121,   123,   124,   125,   126,   135,    26,    73,
     101,    24,   101,    32,    72,     0,    84,    13,   101,   101,
      73,   108,   122,   123,     9,   122,   123,     9,     9,     9,
       9,     9,     9,    78,    79,    24,    97,    98,    77,     5,
       6,     7,     8,    49,   101,    27,   101,   138,   138,   138,
       9,   138,    10,    10,    10,    77,    12,     9,    74,   121,
     137,   137,     7,    74,   121,   136,   136,   136,     9,   121,
     129,   130,   131,   132,   133,   121,   107,    99,   100,   101,
     138,    25,   103,   104,   108,   108,   108,   108,   108,    73,
       9,    19,    28,   105,   106,   121,   127,   128,    25,   138,
      33,    35,    37,    39,    73,   111,   112,   113,   115,   120,
      78,   123,    73,    10,    10,    10,    10,    10,   129,    61,
      62,    63,    64,    65,    66,    67,    68,   134,     3,     4,
      10,    80,    77,    49,    73,   102,   129,   110,   121,    96,
       9,   138,    61,    77,   103,   129,    34,     9,     9,    34,
      10,    77,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   101,   116,   121,    10,     9,   123,   108,   129,
     129,   100,   102,    10,    77,    97,   122,   123,   128,   138,
     138,     9,   114,   115,   129,     9,   138,   112,     9,    11,
     117,   122,   105,   121,    10,   114,    10,    77,    10,   114,
      74,    12,    11,    33,    35,    36,    37,    38,    50,    69,
     118,   119,    10,   138,    10,   115,    10,    10,    12,    34,
      48,   123,     9,   101,    76,    48,   119,    38,   129,   101,
      10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    83,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    85,    86,    87,    88,    89,
      90,    91,    91,    92,    93,    93,    94,    95,    95,    96,
      96,    97,    98,    98,    99,    99,   100,   100,   100,   101,
     102,   103,   103,   104,   105,   105,   106,   107,   107,   108,
     108,   108,   108,   108,   108,   109,   109,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   114,   114,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   118,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   124,   124,   124,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   129,
     129,   129,   129,   130,   130,   130,   131,   132,   133,   134,
     134,   134,   134,   134,   134,   135,   135,   135,   135,   135,
     136,   136,   136,   137,   137,   138,   138
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
       2,     2,     4,     2,     4,     5,     7,     4,     1,     5,
       4,     3,     1,     3,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     4,     1,     1,     1,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     3,     3,     5,     1,
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
#line 161 "sql.y"
        {
            append_list(states, (yyvsp[0].statement));
            (yyval.list) = states;
        }
#line 1672 "y.tab.c"
    break;

  case 3: /* statements: statements statement  */
#line 166 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].statement));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 1681 "y.tab.c"
    break;

  case 4: /* statement: begin_transaction_statement  */
#line 173 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1691 "y.tab.c"
    break;

  case 5: /* statement: commit_transaction_statement  */
#line 179 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1701 "y.tab.c"
    break;

  case 6: /* statement: rollback_transaction_statement  */
#line 185 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            (yyval.statement) = statement;
        }
#line 1711 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 191 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = (yyvsp[0].create_table_node);
            (yyval.statement) = statement;
        }
#line 1722 "y.tab.c"
    break;

  case 8: /* statement: drop_table_statement  */
#line 198 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = (yyvsp[0].drop_table_node);
            (yyval.statement) = statement;
        }
#line 1733 "y.tab.c"
    break;

  case 9: /* statement: select_statement  */
#line 205 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SELECT_STMT;
            statement->select_node = (yyvsp[0].select_node);
            (yyval.statement) = statement;
        }
#line 1744 "y.tab.c"
    break;

  case 10: /* statement: insert_statement  */
#line 212 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = INSERT_STMT;
            statement->insert_node = (yyvsp[0].insert_node);
            (yyval.statement) = statement;
        }
#line 1755 "y.tab.c"
    break;

  case 11: /* statement: update_statement  */
#line 219 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = UPDATE_STMT;
            statement->update_node = (yyvsp[0].update_node);
            (yyval.statement) = statement;
        }
#line 1766 "y.tab.c"
    break;

  case 12: /* statement: delete_statement  */
#line 226 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DELETE_STMT;
            statement->delete_node = (yyvsp[0].delete_node);
            (yyval.statement) = statement;
        }
#line 1777 "y.tab.c"
    break;

  case 13: /* statement: describe_statement  */
#line 233 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = (yyvsp[0].describe_node);
            (yyval.statement) = statement;
        }
#line 1788 "y.tab.c"
    break;

  case 14: /* statement: show_statement  */
#line 240 "sql.y"
        {
            Statement *statement = make_statement();
            statement->statement_type = SHOW_STMT;
            statement->show_node = (yyvsp[0].show_node);
            (yyval.statement) = statement;
        }
#line 1799 "y.tab.c"
    break;

  case 18: /* create_table_statement: CREATE TABLE table '(' base_table_element_commalist ')' end  */
#line 259 "sql.y"
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = (yyvsp[-4].strVal);
            create_table_node->base_table_element_commalist = (yyvsp[-2].list);
            (yyval.create_table_node) = create_table_node;
        }
#line 1810 "y.tab.c"
    break;

  case 19: /* drop_table_statement: DROP TABLE table end  */
#line 269 "sql.y"
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = (yyvsp[-1].strVal);
            (yyval.drop_table_node) = drop_table_node;
        }
#line 1820 "y.tab.c"
    break;

  case 20: /* select_statement: SELECT selection table_exp end  */
#line 278 "sql.y"
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = (yyvsp[-2].selection_node);
            select_node->table_exp = (yyvsp[-1].table_exp_node);
            (yyval.select_node) = select_node;
        }
#line 1831 "y.tab.c"
    break;

  case 21: /* insert_statement: INSERT INTO table values_or_query_spec end  */
#line 288 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = (yyvsp[-2].strVal);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1843 "y.tab.c"
    break;

  case 22: /* insert_statement: INSERT INTO table '(' columns ')' values_or_query_spec end  */
#line 296 "sql.y"
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = (yyvsp[-5].strVal);
            node->column_list = (yyvsp[-3].list);
            node->values_or_query_spec = (yyvsp[-1].values_or_query_spec_node);
            (yyval.insert_node) = node;
        }
#line 1856 "y.tab.c"
    break;

  case 23: /* update_statement: UPDATE table SET assignments opt_where_clause end  */
#line 308 "sql.y"
        {
            UpdateNode *node = make_update_node();
            node->table_name = (yyvsp[-4].strVal);
            node->assignment_set_node = (yyvsp[-2].assignment_set_node);
            node->where_clause = (yyvsp[-1].where_clause_node);
            (yyval.update_node) = node;
        }
#line 1868 "y.tab.c"
    break;

  case 24: /* delete_statement: DELETE FROM table end  */
#line 319 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.delete_node) = node;
        }
#line 1878 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table WHERE condition end  */
#line 325 "sql.y"
        {
            DeleteNode *node = make_delete_node();
            node->table_name = (yyvsp[-3].strVal);
            node->condition_node = (yyvsp[-1].condition_node);
            (yyval.delete_node) = node;
        }
#line 1889 "y.tab.c"
    break;

  case 26: /* describe_statement: DESCRIBE table end  */
#line 335 "sql.y"
        {
            DescribeNode *node = make_describe_node();
            node->table_name = (yyvsp[-1].strVal);
            (yyval.describe_node) = node;
        }
#line 1899 "y.tab.c"
    break;

  case 27: /* show_statement: SHOW TABLES end  */
#line 344 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_TABLES);
        }
#line 1907 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW MEMORY end  */
#line 348 "sql.y"
        {
            (yyval.show_node) = make_show_node(SHOW_MEMORY);
        }
#line 1915 "y.tab.c"
    break;

  case 29: /* selection: scalar_exp_commalist  */
#line 354 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_list = (yyvsp[0].list);
            (yyval.selection_node) = selection_node;
        }
#line 1926 "y.tab.c"
    break;

  case 30: /* selection: '*'  */
#line 361 "sql.y"
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            (yyval.selection_node) = selection_node;
        }
#line 1936 "y.tab.c"
    break;

  case 31: /* table_exp: from_clause opt_where_clause  */
#line 369 "sql.y"
        {
            TableExpNode *table_exp = make_table_exp_node();
            table_exp->from_clause = (yyvsp[-1].from_clause_node);
            table_exp->where_clause = (yyvsp[0].where_clause_node);
            (yyval.table_exp_node) = table_exp;
        }
#line 1947 "y.tab.c"
    break;

  case 32: /* from_clause: %empty  */
#line 378 "sql.y"
        {
            (yyval.from_clause_node) = NULL;
        }
#line 1955 "y.tab.c"
    break;

  case 33: /* from_clause: FROM table_ref_commalist  */
#line 382 "sql.y"
        {
            FromClauseNode *from_clause = make_from_clause_node();
            from_clause->from = (yyvsp[0].table_ref_set_node);
            (yyval.from_clause_node) = from_clause;
        }
#line 1965 "y.tab.c"
    break;

  case 34: /* table_ref_commalist: table_ref  */
#line 390 "sql.y"
        {
            TableRefSetNode *table_ref_set = make_table_ref_set_node();
            add_table_ref_to_set(table_ref_set, (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = table_ref_set;
        }
#line 1975 "y.tab.c"
    break;

  case 35: /* table_ref_commalist: table_ref_commalist ',' table_ref  */
#line 396 "sql.y"
        {
            add_table_ref_to_set((yyvsp[-2].table_ref_set_node), (yyvsp[0].table_ref_node));
            (yyval.table_ref_set_node) = (yyvsp[-2].table_ref_set_node);
        }
#line 1984 "y.tab.c"
    break;

  case 36: /* table_ref: table  */
#line 403 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 1994 "y.tab.c"
    break;

  case 37: /* table_ref: table range_variable  */
#line 409 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-1].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2005 "y.tab.c"
    break;

  case 38: /* table_ref: table AS range_variable  */
#line 416 "sql.y"
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = (yyvsp[-2].strVal);
            table_ref->range_variable = (yyvsp[0].strVal);
            (yyval.table_ref_node) = table_ref;
        }
#line 2016 "y.tab.c"
    break;

  case 39: /* table: IDENTIFIER  */
#line 425 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2024 "y.tab.c"
    break;

  case 40: /* range_variable: IDENTIFIER  */
#line 431 "sql.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2032 "y.tab.c"
    break;

  case 41: /* opt_where_clause: %empty  */
#line 437 "sql.y"
        {
            (yyval.where_clause_node) = NULL;
        }
#line 2040 "y.tab.c"
    break;

  case 42: /* opt_where_clause: where_clause  */
#line 441 "sql.y"
        {
            (yyval.where_clause_node) = (yyvsp[0].where_clause_node);
        }
#line 2048 "y.tab.c"
    break;

  case 43: /* where_clause: WHERE condition  */
#line 447 "sql.y"
        {
            WhereClauseNode *where_clause_node = make_where_clause_node();
            where_clause_node->condition = (yyvsp[0].condition_node);
            (yyval.where_clause_node) = where_clause_node;
        }
#line 2058 "y.tab.c"
    break;

  case 44: /* values_or_query_spec: VALUES '(' value_items ')'  */
#line 455 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = (yyvsp[-1].value_item_set_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2069 "y.tab.c"
    break;

  case 45: /* values_or_query_spec: query_spec  */
#line 462 "sql.y"
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = (yyvsp[0].query_spec_node);
            (yyval.values_or_query_spec_node) = values_or_query_spec;
        }
#line 2080 "y.tab.c"
    break;

  case 46: /* query_spec: SELECT selection table_exp  */
#line 471 "sql.y"
        {
            QuerySpecNode *query_spec = make_query_spec_node();
            query_spec->selection = (yyvsp[-1].selection_node);
            query_spec->table_exp = (yyvsp[0].table_exp_node);
            (yyval.query_spec_node) = query_spec;
        }
#line 2091 "y.tab.c"
    break;

  case 47: /* scalar_exp_commalist: scalar_exp  */
#line 480 "sql.y"
        {
            List *scalar_exp_list = create_list(NODE_SCALAR_EXP);
            append_list(scalar_exp_list, (yyvsp[0].scalar_exp_node));
            (yyval.list) = scalar_exp_list;
        }
#line 2101 "y.tab.c"
    break;

  case 48: /* scalar_exp_commalist: scalar_exp_commalist ',' scalar_exp  */
#line 486 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].scalar_exp_node));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2110 "y.tab.c"
    break;

  case 49: /* scalar_exp: calculate  */
#line 493 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = (yyvsp[0].calculate_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2121 "y.tab.c"
    break;

  case 50: /* scalar_exp: column  */
#line 500 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = (yyvsp[0].column_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2132 "y.tab.c"
    break;

  case 51: /* scalar_exp: function  */
#line 507 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = (yyvsp[0].function_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2143 "y.tab.c"
    break;

  case 52: /* scalar_exp: value_item  */
#line 514 "sql.y"
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = (yyvsp[0].value_item_node);
            (yyval.scalar_exp_node) = scalar_exp_node;
        }
#line 2154 "y.tab.c"
    break;

  case 53: /* scalar_exp: '(' scalar_exp ')'  */
#line 521 "sql.y"
        {
            (yyval.scalar_exp_node) = (yyvsp[-1].scalar_exp_node);
        }
#line 2162 "y.tab.c"
    break;

  case 54: /* scalar_exp: scalar_exp AS IDENTIFIER  */
#line 525 "sql.y"
        {
            (yyvsp[-2].scalar_exp_node)->alias = (yyvsp[0].strVal);
            (yyval.scalar_exp_node) = (yyvsp[-2].scalar_exp_node);
        }
#line 2171 "y.tab.c"
    break;

  case 55: /* calculate: scalar_exp '+' scalar_exp  */
#line 532 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2183 "y.tab.c"
    break;

  case 56: /* calculate: scalar_exp '-' scalar_exp  */
#line 540 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2195 "y.tab.c"
    break;

  case 57: /* calculate: scalar_exp '*' scalar_exp  */
#line 548 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2207 "y.tab.c"
    break;

  case 58: /* calculate: scalar_exp '/' scalar_exp  */
#line 556 "sql.y"
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = (yyvsp[-2].scalar_exp_node);
            calculate_node->right = (yyvsp[0].scalar_exp_node);
            (yyval.calculate_node) = calculate_node;
        }
#line 2219 "y.tab.c"
    break;

  case 59: /* columns: column  */
#line 566 "sql.y"
        {
            List *column_set_node = create_list(NODE_COLUMN);
            append_list(column_set_node, (yyvsp[0].column_node));
            (yyval.list) = column_set_node;
        }
#line 2229 "y.tab.c"
    break;

  case 60: /* columns: columns ',' column  */
#line 572 "sql.y"
        {
            (yyval.list) = (yyvsp[-2].list);
            append_list((yyval.list), (yyvsp[0].column_node));
        }
#line 2238 "y.tab.c"
    break;

  case 61: /* base_table_element_commalist: base_table_element  */
#line 579 "sql.y"
        {
            List *base_table_element_commalist = create_list(NODE_BASE_TABLE_ELEMENT);
            append_list(base_table_element_commalist, (yyvsp[0].base_table_element));
            (yyval.list) = base_table_element_commalist;
        }
#line 2248 "y.tab.c"
    break;

  case 62: /* base_table_element_commalist: base_table_element_commalist ',' base_table_element  */
#line 585 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].base_table_element));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2257 "y.tab.c"
    break;

  case 63: /* base_table_element: column_def  */
#line 592 "sql.y"
        {
            (yyval.base_table_element) = make_base_table_element_node();
            (yyval.base_table_element)->column_def = (yyvsp[0].column_def_node);
            (yyval.base_table_element)->table_contraint_def = NULL;
            (yyval.base_table_element)->type = TELE_COLUMN_DEF;
        }
#line 2268 "y.tab.c"
    break;

  case 64: /* base_table_element: table_contraint_def  */
#line 599 "sql.y"
        {
            (yyval.base_table_element) = make_base_table_element_node();
            (yyval.base_table_element)->column_def = NULL;
            (yyval.base_table_element)->table_contraint_def = (yyvsp[0].table_contraint_def);
            (yyval.base_table_element)->type = TELE_TABLE_CONTRAINT_DEF;
        }
#line 2279 "y.tab.c"
    break;

  case 65: /* column_def: column_def_name data_type array_dim_clause column_def_opt_list  */
#line 621 "sql.y"
        {
            ColumnDefNode *column_def = make_column_def_node();
            column_def->column = (yyvsp[-3].column_def_name);
            column_def->data_type = (yyvsp[-2].data_type_node);
            column_def->array_dim = (yyvsp[-1].intVal);
            column_def->column_def_opt_list = (yyvsp[0].list);
            (yyval.column_def_node) = column_def;
        }
#line 2292 "y.tab.c"
    break;

  case 66: /* column_def_name_commalist: column_def_name  */
#line 632 "sql.y"
        {
            List *list = create_list(NODE_COLUMN_DEF_NAME);
            append_list(list, (yyvsp[0].column_def_name));
            (yyval.list) = list;
        }
#line 2302 "y.tab.c"
    break;

  case 67: /* column_def_name_commalist: column_def_name_commalist ',' column_def_name  */
#line 638 "sql.y"
        {
            append_list((yyvsp[-2].list), (yyvsp[0].column_def_name));
            (yyval.list) = (yyvsp[-2].list);
        }
#line 2311 "y.tab.c"
    break;

  case 68: /* column_def_name: IDENTIFIER  */
#line 645 "sql.y"
        {
            ColumnDefName *column_def_name = make_column_def_name();
            column_def_name->column = (yyvsp[0].strVal);
            (yyval.column_def_name) = column_def_name;
        }
#line 2321 "y.tab.c"
    break;

  case 69: /* data_type: INT  */
#line 653 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_INT; 
        }
#line 2330 "y.tab.c"
    break;

  case 70: /* data_type: LONG  */
#line 658 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_LONG;  
        }
#line 2339 "y.tab.c"
    break;

  case 71: /* data_type: CHAR  */
#line 663 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_CHAR; 
        }
#line 2348 "y.tab.c"
    break;

  case 72: /* data_type: VARCHAR '(' INTVALUE ')'  */
#line 668 "sql.y"
        {
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_VARCHAR; 
            (yyval.data_type_node)->len = (yyvsp[-1].intVal); 
        }
#line 2358 "y.tab.c"
    break;

  case 73: /* data_type: STRING  */
#line 674 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_STRING; 
        }
#line 2367 "y.tab.c"
    break;

  case 74: /* data_type: BOOL  */
#line 679 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_BOOL; 
        }
#line 2376 "y.tab.c"
    break;

  case 75: /* data_type: FLOAT  */
#line 684 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_FLOAT; 
        }
#line 2385 "y.tab.c"
    break;

  case 76: /* data_type: DOUBLE  */
#line 689 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_DOUBLE; 
        }
#line 2394 "y.tab.c"
    break;

  case 77: /* data_type: TIMESTAMP  */
#line 694 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_TIMESTAMP; 
        }
#line 2403 "y.tab.c"
    break;

  case 78: /* data_type: DATE  */
#line 699 "sql.y"
        { 
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_DATE; 
        }
#line 2412 "y.tab.c"
    break;

  case 79: /* data_type: table  */
#line 704 "sql.y"
        {
            (yyval.data_type_node) = make_data_type_node();
            (yyval.data_type_node)->type = T_REFERENCE;
            (yyval.data_type_node)->table_name = (yyvsp[0].strVal);
        }
#line 2422 "y.tab.c"
    break;

  case 80: /* array_dim_clause: %empty  */
#line 712 "sql.y"
        {
            (yyval.intVal) = 0;
        }
#line 2430 "y.tab.c"
    break;

  case 81: /* array_dim_clause: '[' ']'  */
#line 716 "sql.y"
        {
            (yyval.intVal) = 1;
        }
#line 2438 "y.tab.c"
    break;

  case 82: /* array_dim_clause: array_dim_clause '[' ']'  */
#line 720 "sql.y"
        {
            (yyval.intVal)++;
        }
#line 2446 "y.tab.c"
    break;

  case 83: /* column_def_opt_list: %empty  */
#line 726 "sql.y"
        {
            (yyval.list) = NULL;
        }
#line 2454 "y.tab.c"
    break;

  case 84: /* column_def_opt_list: column_def_opt  */
#line 730 "sql.y"
        {
            (yyval.list) = create_list(NODE_COLUMN_DEF_OPT);
            append_list((yyval.list), (yyvsp[0].column_def_opt));
        }
#line 2463 "y.tab.c"
    break;

  case 85: /* column_def_opt_list: column_def_opt_list column_def_opt  */
#line 735 "sql.y"
        {
            append_list((yyvsp[-1].list), (yyvsp[0].column_def_opt));
            (yyval.list) = (yyvsp[-1].list);
        }
#line 2472 "y.tab.c"
    break;

  case 86: /* column_def_opt: NOT NULLX  */
#line 742 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_NOT_NULL; 
        }
#line 2481 "y.tab.c"
    break;

  case 87: /* column_def_opt: UNIQUE  */
#line 747 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_UNIQUE; 
        }
#line 2490 "y.tab.c"
    break;

  case 88: /* column_def_opt: PRIMARY KEY  */
#line 752 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_PRIMARY_KEY; 
        }
#line 2499 "y.tab.c"
    break;

  case 89: /* column_def_opt: DEFAULT value_item  */
#line 757 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_DEFAULT_VALUE;
            (yyval.column_def_opt)->value = (yyvsp[0].value_item_node);
        }
#line 2509 "y.tab.c"
    break;

  case 90: /* column_def_opt: DEFAULT NULLX  */
#line 763 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_DEFAULT_NULL;
        }
#line 2518 "y.tab.c"
    break;

  case 91: /* column_def_opt: COMMENT STRINGVALUE  */
#line 768 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_COMMENT;
            (yyval.column_def_opt)->comment = (yyvsp[0].strVal);
        }
#line 2528 "y.tab.c"
    break;

  case 92: /* column_def_opt: CHECK '(' condition ')'  */
#line 774 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_CHECK_CONDITION;
            (yyval.column_def_opt)->condition = (yyvsp[-1].condition_node);
        }
#line 2538 "y.tab.c"
    break;

  case 93: /* column_def_opt: REFERENCES table  */
#line 780 "sql.y"
        {
            (yyval.column_def_opt) = make_column_def_opt_node();
            (yyval.column_def_opt)->opt_type = OPT_REFERENECS;
            (yyval.column_def_opt)->refer_table = (yyvsp[0].strVal);
        }
#line 2548 "y.tab.c"
    break;

  case 94: /* table_contraint_def: UNIQUE '(' column_def_name_commalist ')'  */
#line 788 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_UNIQUE;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-1].list);
        }
#line 2558 "y.tab.c"
    break;

  case 95: /* table_contraint_def: PRIMARY KEY '(' column_def_name_commalist ')'  */
#line 794 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_PRIMARY_KEY;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-1].list);
        }
#line 2568 "y.tab.c"
    break;

  case 96: /* table_contraint_def: FOREIGN KEY '(' column_def_name_commalist ')' REFERENCES table  */
#line 800 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_FOREIGN_KEY;
            (yyval.table_contraint_def)->column_commalist = (yyvsp[-3].list);
            (yyval.table_contraint_def)->table = (yyvsp[0].strVal);
        }
#line 2579 "y.tab.c"
    break;

  case 97: /* table_contraint_def: CHECK '(' condition ')'  */
#line 807 "sql.y"
        {
            (yyval.table_contraint_def) = make_table_contraint_def_node();
            (yyval.table_contraint_def)->type = TCONTRAINT_CHECK;
            (yyval.table_contraint_def)->condition = (yyvsp[-1].condition_node);
        }
#line 2589 "y.tab.c"
    break;

  case 98: /* column: IDENTIFIER  */
#line 815 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[0].strVal);
            column_node->has_sub_column = false;
            (yyval.column_node) = column_node;
        }
#line 2600 "y.tab.c"
    break;

  case 99: /* column: '(' IDENTIFIER ')' '.' column  */
#line 822 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->sub_column = (yyvsp[0].column_node);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2612 "y.tab.c"
    break;

  case 100: /* column: IDENTIFIER '{' scalar_exp_commalist '}'  */
#line 830 "sql.y"
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = (yyvsp[-3].strVal);
            column_node->scalar_exp_list = (yyvsp[-1].list);
            column_node->has_sub_column = true;
            (yyval.column_node) = column_node;
        }
#line 2624 "y.tab.c"
    break;

  case 101: /* column: IDENTIFIER '.' column  */
#line 838 "sql.y"
        {
            (yyval.column_node) = (yyvsp[0].column_node);
            (yyval.column_node)->range_variable = (yyvsp[-2].strVal);
        }
#line 2633 "y.tab.c"
    break;

  case 102: /* value_items: value_item  */
#line 845 "sql.y"
        {
            ValueItemSetNode *node = make_value_item_set_node();
            add_value_item(node, (yyvsp[0].value_item_node));
            (yyval.value_item_set_node) = node;
        }
#line 2643 "y.tab.c"
    break;

  case 103: /* value_items: value_items ',' value_item  */
#line 851 "sql.y"
        {
            (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
            add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
        }
#line 2652 "y.tab.c"
    break;

  case 104: /* value_item: atom  */
#line 858 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_ATOM;
            node->value.atom = (yyvsp[0].atom_node);
            (yyval.value_item_node) = node;
        }
#line 2663 "y.tab.c"
    break;

  case 105: /* value_item: NULLX  */
#line 865 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_NULL;
            (yyval.value_item_node) = node;
        }
#line 2673 "y.tab.c"
    break;

  case 106: /* value_item: '[' value_items ']'  */
#line 871 "sql.y"
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_ARRAY;
            node->value.value_set = (yyvsp[-1].value_item_set_node);
            (yyval.value_item_node) = node;
        }
#line 2684 "y.tab.c"
    break;

  case 107: /* atom: INTVALUE  */
#line 880 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.intval = (yyvsp[0].intVal);
            node->type = A_INT;
            (yyval.atom_node) = node;
        }
#line 2695 "y.tab.c"
    break;

  case 108: /* atom: BOOLVALUE  */
#line 887 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.boolval = (yyvsp[0].boolVal);
            node->type = A_BOOL;
            (yyval.atom_node) = node;
        }
#line 2706 "y.tab.c"
    break;

  case 109: /* atom: STRINGVALUE  */
#line 894 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.strval = (yyvsp[0].strVal);
            node->type = A_STRING;
            (yyval.atom_node) = node;
        }
#line 2717 "y.tab.c"
    break;

  case 110: /* atom: FLOATVALUE  */
#line 901 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.floatval = (yyvsp[0].floatVal);
            node->type = A_FLOAT;
            (yyval.atom_node) = node;
        }
#line 2728 "y.tab.c"
    break;

  case 111: /* atom: REFERVALUE  */
#line 908 "sql.y"
        {
            AtomNode *node = make_atom_node();
            node->value.referval = (yyvsp[0].referVal);
            node->type = A_REFERENCE;
            (yyval.atom_node) = node;
        }
#line 2739 "y.tab.c"
    break;

  case 112: /* REFERVALUE: '(' value_items ')'  */
#line 918 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_item_set = (yyvsp[-1].value_item_set_node);
            (yyval.referVal) = refer;
        }
#line 2750 "y.tab.c"
    break;

  case 113: /* REFERVALUE: REF '(' condition ')'  */
#line 926 "sql.y"
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = (yyvsp[-1].condition_node);
            (yyval.referVal) = refer;
        }
#line 2761 "y.tab.c"
    break;

  case 114: /* BOOLVALUE: TRUE  */
#line 935 "sql.y"
        {
            (yyval.boolVal) = true;
        }
#line 2769 "y.tab.c"
    break;

  case 115: /* BOOLVALUE: FALSE  */
#line 939 "sql.y"
        {
            (yyval.boolVal) = false;
        }
#line 2777 "y.tab.c"
    break;

  case 116: /* assignments: assignment  */
#line 945 "sql.y"
        {
            AssignmentSetNode *node = make_assignment_set_node();
            add_assignment_to_set(node, (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = node;
        }
#line 2787 "y.tab.c"
    break;

  case 117: /* assignments: assignments ',' assignment  */
#line 951 "sql.y"
        {
            add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
            (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
        }
#line 2796 "y.tab.c"
    break;

  case 118: /* assignment: column EQ value_item  */
#line 958 "sql.y"
        {
            AssignmentNode *node = make_assignment_node();
            node->column = (yyvsp[-2].column_node);
            node->value = (yyvsp[0].value_item_node);
            (yyval.assignment_node) = node;
        }
#line 2807 "y.tab.c"
    break;

  case 119: /* condition: condition OR condition  */
#line 967 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2819 "y.tab.c"
    break;

  case 120: /* condition: condition AND condition  */
#line 975 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = (yyvsp[-2].condition_node);
            condition->right = (yyvsp[0].condition_node);
            (yyval.condition_node) = condition;
        }
#line 2831 "y.tab.c"
    break;

  case 121: /* condition: '(' condition ')'  */
#line 983 "sql.y"
        {
            (yyval.condition_node) = (yyvsp[-1].condition_node);
        }
#line 2839 "y.tab.c"
    break;

  case 122: /* condition: predicate  */
#line 987 "sql.y"
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = (yyvsp[0].predicate_node);
            (yyval.condition_node) = condition;
        }
#line 2850 "y.tab.c"
    break;

  case 123: /* predicate: comparison_predicate  */
#line 996 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = (yyvsp[0].comparison_node);
            (yyval.predicate_node) = predicate;
        }
#line 2861 "y.tab.c"
    break;

  case 124: /* predicate: like_predicate  */
#line 1003 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = (yyvsp[0].like_node);
            (yyval.predicate_node) = predicate;
        }
#line 2872 "y.tab.c"
    break;

  case 125: /* predicate: in_predicate  */
#line 1010 "sql.y"
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = (yyvsp[0].in_node);
            (yyval.predicate_node) = predicate;
        }
#line 2883 "y.tab.c"
    break;

  case 126: /* comparison_predicate: column compare scalar_exp  */
#line 1019 "sql.y"
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = (yyvsp[-2].column_node);
            comparison_node->type = (yyvsp[-1].compare_type);
            comparison_node->value = (yyvsp[0].scalar_exp_node);
            (yyval.comparison_node) = comparison_node;
        }
#line 2895 "y.tab.c"
    break;

  case 127: /* like_predicate: column LIKE value_item  */
#line 1029 "sql.y"
        {
            LikeNode *like_node = make_like_node();
            like_node->column = (yyvsp[-2].column_node);
            like_node->value = (yyvsp[0].value_item_node);
            (yyval.like_node) = like_node;
        }
#line 2906 "y.tab.c"
    break;

  case 128: /* in_predicate: column IN '(' value_items ')'  */
#line 1038 "sql.y"
        {
            InNode *in_node = make_in_node();
            in_node->column = (yyvsp[-4].column_node);
            in_node->value_set = (yyvsp[-1].value_item_set_node);
            (yyval.in_node) = in_node;
        }
#line 2917 "y.tab.c"
    break;

  case 129: /* compare: EQ  */
#line 1066 "sql.y"
            { (yyval.compare_type) = O_EQ; }
#line 2923 "y.tab.c"
    break;

  case 130: /* compare: NE  */
#line 1067 "sql.y"
            { (yyval.compare_type) = O_NE; }
#line 2929 "y.tab.c"
    break;

  case 131: /* compare: GT  */
#line 1068 "sql.y"
            { (yyval.compare_type) = O_GT; }
#line 2935 "y.tab.c"
    break;

  case 132: /* compare: GE  */
#line 1069 "sql.y"
            { (yyval.compare_type) = O_GE; }
#line 2941 "y.tab.c"
    break;

  case 133: /* compare: LT  */
#line 1070 "sql.y"
            { (yyval.compare_type) = O_LT; }
#line 2947 "y.tab.c"
    break;

  case 134: /* compare: LE  */
#line 1071 "sql.y"
            { (yyval.compare_type) = O_LE; }
#line 2953 "y.tab.c"
    break;

  case 135: /* function: MAX '(' non_all_function_value ')'  */
#line 1075 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2964 "y.tab.c"
    break;

  case 136: /* function: MIN '(' non_all_function_value ')'  */
#line 1082 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2975 "y.tab.c"
    break;

  case 137: /* function: COUNT '(' function_value ')'  */
#line 1089 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2986 "y.tab.c"
    break;

  case 138: /* function: SUM '(' function_value ')'  */
#line 1096 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 2997 "y.tab.c"
    break;

  case 139: /* function: AVG '(' function_value ')'  */
#line 1103 "sql.y"
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
            function_node->value = (yyvsp[-1].function_value_node);
            (yyval.function_node) = function_node;
        }
#line 3008 "y.tab.c"
    break;

  case 140: /* function_value: INTVALUE  */
#line 1112 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3019 "y.tab.c"
    break;

  case 141: /* function_value: column  */
#line 1119 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3030 "y.tab.c"
    break;

  case 142: /* function_value: '*'  */
#line 1126 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->value_type = V_ALL;
            (yyval.function_value_node) = node;
        }
#line 3040 "y.tab.c"
    break;

  case 143: /* non_all_function_value: INTVALUE  */
#line 1134 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->i_value = (yyvsp[0].intVal);
            node->value_type = V_INT;
            (yyval.function_value_node) = node;
        }
#line 3051 "y.tab.c"
    break;

  case 144: /* non_all_function_value: column  */
#line 1141 "sql.y"
        {
            FunctionValueNode *node = make_function_value_node();
            node->column = (yyvsp[0].column_node);
            node->value_type = V_COLUMN;
            (yyval.function_value_node) = node;
        }
#line 3062 "y.tab.c"
    break;


#line 3066 "y.tab.c"

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

#line 1152 "sql.y"

