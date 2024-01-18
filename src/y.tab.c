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
    SHOW = 275,                    /* SHOW  */
    TABLES = 276,                  /* TABLES  */
    MAX = 277,                     /* MAX  */
    MIN = 278,                     /* MIN  */
    COUNT = 279,                   /* COUNT  */
    SUM = 280,                     /* SUM  */
    AVG = 281,                     /* AVG  */
    TRUE = 282,                    /* TRUE  */
    FALSE = 283,                   /* FALSE  */
    NOT = 284,                     /* NOT  */
    NULLX = 285,                   /* NULLX  */
    CHAR = 286,                    /* CHAR  */
    INT = 287,                     /* INT  */
    LONG = 288,                    /* LONG  */
    STRING = 289,                  /* STRING  */
    BOOL = 290,                    /* BOOL  */
    FLOAT = 291,                   /* FLOAT  */
    DOUBLE = 292,                  /* DOUBLE  */
    DATE = 293,                    /* DATE  */
    TIMESTAMP = 294,               /* TIMESTAMP  */
    PRIMARY = 295,                 /* PRIMARY  */
    KEY = 296,                     /* KEY  */
    EQ = 297,                      /* EQ  */
    NE = 298,                      /* NE  */
    GT = 299,                      /* GT  */
    GE = 300,                      /* GE  */
    LT = 301,                      /* LT  */
    LE = 302,                      /* LE  */
    IN = 303,                      /* IN  */
    LIKE = 304,                    /* LIKE  */
    AND = 305,                     /* AND  */
    OR = 306,                      /* OR  */
    ALL = 307,                     /* ALL  */
    COMMA = 308,                   /* COMMA  */
    SEMICOLON = 309,               /* SEMICOLON  */
    QUOTE = 310,                   /* QUOTE  */
    POINT = 311,                   /* POINT  */
    LEFTPAREN = 312,               /* LEFTPAREN  */
    RIGHTPAREN = 313,              /* RIGHTPAREN  */
    SYSTEM = 314,                  /* SYSTEM  */
    CONFIG = 315,                  /* CONFIG  */
    MEMORY = 316,                  /* MEMORY  */
    IDENTIFIER = 317,              /* IDENTIFIER  */
    INTVALUE = 318,                /* INTVALUE  */
    FLOATVALUE = 319,              /* FLOATVALUE  */
    STRINGVALUE = 320              /* STRINGVALUE  */
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
#define SHOW 275
#define TABLES 276
#define MAX 277
#define MIN 278
#define COUNT 279
#define SUM 280
#define AVG 281
#define TRUE 282
#define FALSE 283
#define NOT 284
#define NULLX 285
#define CHAR 286
#define INT 287
#define LONG 288
#define STRING 289
#define BOOL 290
#define FLOAT 291
#define DOUBLE 292
#define DATE 293
#define TIMESTAMP 294
#define PRIMARY 295
#define KEY 296
#define EQ 297
#define NE 298
#define GT 299
#define GE 300
#define LT 301
#define LE 302
#define IN 303
#define LIKE 304
#define AND 305
#define OR 306
#define ALL 307
#define COMMA 308
#define SEMICOLON 309
#define QUOTE 310
#define POINT 311
#define LEFTPAREN 312
#define RIGHTPAREN 313
#define SYSTEM 314
#define CONFIG 315
#define MEMORY 316
#define IDENTIFIER 317
#define INTVALUE 318
#define FLOATVALUE 319
#define STRINGVALUE 320

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
   DataType                 data_type;
   OprType                  opr_type;
   ConnType                 conn_type;
   ColumnDefNode            *column_def_node;
   ColumnDefSetNode         *column_def_set_node;
   SelectItemsNode          *select_items_node;
   ColumnNode               *column_node;
   ColumnSetNode            *column_set_node;
   ValueItemNode            *value_item_node;
   ValueItemSetNode         *value_item_set_node;
   FunctionValueNode        *function_value_node;
   FunctionNode             *function_node;
   PrimaryKeyNode           *primary_key_node;
   AssignmentNode           *assignment_node;
   AssignmentSetNode        *assignment_set_node;
   ConditionNode            *cond_node;
   CreateTableNode          *create_table_node;
   DropTableNode            *drop_table_node;
   SelectNode               *select_node;
   InsertNode               *insert_node;
   UpdateNode               *update_node;
   DeleteNode               *delete_node;
   DescribeNode             *describe_node;
   ShowNode                 *show_node;
   ASTNode                  *ast_node;

#line 302 "y.tab.c"

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
  YYSYMBOL_SHOW = 20,                      /* SHOW  */
  YYSYMBOL_TABLES = 21,                    /* TABLES  */
  YYSYMBOL_MAX = 22,                       /* MAX  */
  YYSYMBOL_MIN = 23,                       /* MIN  */
  YYSYMBOL_COUNT = 24,                     /* COUNT  */
  YYSYMBOL_SUM = 25,                       /* SUM  */
  YYSYMBOL_AVG = 26,                       /* AVG  */
  YYSYMBOL_TRUE = 27,                      /* TRUE  */
  YYSYMBOL_FALSE = 28,                     /* FALSE  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_NULLX = 30,                     /* NULLX  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_LONG = 33,                      /* LONG  */
  YYSYMBOL_STRING = 34,                    /* STRING  */
  YYSYMBOL_BOOL = 35,                      /* BOOL  */
  YYSYMBOL_FLOAT = 36,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 37,                    /* DOUBLE  */
  YYSYMBOL_DATE = 38,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 39,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 40,                   /* PRIMARY  */
  YYSYMBOL_KEY = 41,                       /* KEY  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_NE = 43,                        /* NE  */
  YYSYMBOL_GT = 44,                        /* GT  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_LT = 46,                        /* LT  */
  YYSYMBOL_LE = 47,                        /* LE  */
  YYSYMBOL_IN = 48,                        /* IN  */
  YYSYMBOL_LIKE = 49,                      /* LIKE  */
  YYSYMBOL_AND = 50,                       /* AND  */
  YYSYMBOL_OR = 51,                        /* OR  */
  YYSYMBOL_ALL = 52,                       /* ALL  */
  YYSYMBOL_COMMA = 53,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 54,                 /* SEMICOLON  */
  YYSYMBOL_QUOTE = 55,                     /* QUOTE  */
  YYSYMBOL_POINT = 56,                     /* POINT  */
  YYSYMBOL_LEFTPAREN = 57,                 /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 58,                /* RIGHTPAREN  */
  YYSYMBOL_SYSTEM = 59,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 60,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 61,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 62,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 63,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 64,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 65,               /* STRINGVALUE  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_statements = 67,                /* statements  */
  YYSYMBOL_statement = 68,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 69, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 70, /* commit_transaction_statement  */
  YYSYMBOL_rollback_transaction_statement = 71, /* rollback_transaction_statement  */
  YYSYMBOL_create_table_statement = 72,    /* create_table_statement  */
  YYSYMBOL_drop_table_statement = 73,      /* drop_table_statement  */
  YYSYMBOL_select_statement = 74,          /* select_statement  */
  YYSYMBOL_insert_statement = 75,          /* insert_statement  */
  YYSYMBOL_update_statement = 76,          /* update_statement  */
  YYSYMBOL_delete_statement = 77,          /* delete_statement  */
  YYSYMBOL_describe_statement = 78,        /* describe_statement  */
  YYSYMBOL_show_statement = 79,            /* show_statement  */
  YYSYMBOL_select_items = 80,              /* select_items  */
  YYSYMBOL_table = 81,                     /* table  */
  YYSYMBOL_columns = 82,                   /* columns  */
  YYSYMBOL_column_defs = 83,               /* column_defs  */
  YYSYMBOL_column_def = 84,                /* column_def  */
  YYSYMBOL_data_type = 85,                 /* data_type  */
  YYSYMBOL_primary_key_statement = 86,     /* primary_key_statement  */
  YYSYMBOL_column = 87,                    /* column  */
  YYSYMBOL_value_items = 88,               /* value_items  */
  YYSYMBOL_value_item = 89,                /* value_item  */
  YYSYMBOL_BOOLVALUE = 90,                 /* BOOLVALUE  */
  YYSYMBOL_assignments = 91,               /* assignments  */
  YYSYMBOL_assignment = 92,                /* assignment  */
  YYSYMBOL_cond = 93,                      /* cond  */
  YYSYMBOL_opr = 94,                       /* opr  */
  YYSYMBOL_conn = 95,                      /* conn  */
  YYSYMBOL_function = 96,                  /* function  */
  YYSYMBOL_function_value = 97,            /* function_value  */
  YYSYMBOL_non_all_function_value = 98,    /* non_all_function_value  */
  YYSYMBOL_end = 99                        /* end  */
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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


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
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   108,   109,   112,   116,   120,   124,   129,
     134,   139,   144,   149,   154,   159,   166,   169,   172,   175,
     182,   192,   200,   208,   217,   225,   236,   243,   253,   259,
     268,   276,   280,   286,   293,   300,   308,   314,   320,   327,
     333,   340,   350,   361,   372,   381,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   403,   411,   418,   428,   434,
     441,   448,   455,   462,   469,   478,   482,   488,   494,   501,
     510,   519,   532,   533,   534,   535,   536,   537,   538,   539,
     542,   543,   546,   553,   560,   567,   574,   583,   590,   597,
     605,   612,   621,   622
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
  "SHOW", "TABLES", "MAX", "MIN", "COUNT", "SUM", "AVG", "TRUE", "FALSE",
  "NOT", "NULLX", "CHAR", "INT", "LONG", "STRING", "BOOL", "FLOAT",
  "DOUBLE", "DATE", "TIMESTAMP", "PRIMARY", "KEY", "EQ", "NE", "GT", "GE",
  "LT", "LE", "IN", "LIKE", "AND", "OR", "ALL", "COMMA", "SEMICOLON",
  "QUOTE", "POINT", "LEFTPAREN", "RIGHTPAREN", "SYSTEM", "CONFIG",
  "MEMORY", "IDENTIFIER", "INTVALUE", "FLOATVALUE", "STRINGVALUE",
  "$accept", "statements", "statement", "begin_transaction_statement",
  "commit_transaction_statement", "rollback_transaction_statement",
  "create_table_statement", "drop_table_statement", "select_statement",
  "insert_statement", "update_statement", "delete_statement",
  "describe_statement", "show_statement", "select_items", "table",
  "columns", "column_defs", "column_def", "data_type",
  "primary_key_statement", "column", "value_items", "value_item",
  "BOOLVALUE", "assignments", "assignment", "cond", "opr", "conn",
  "function", "function_value", "non_all_function_value", "end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-121)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     157,    15,    15,    15,     6,    31,    53,    18,   -21,    39,
     -21,   -12,   129,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,    78,  -121,  -121,  -121,
     -21,   -21,    -1,    25,    26,    27,    42,  -121,    44,    87,
      49,  -121,  -121,   -21,  -121,    86,   -21,    15,    15,    15,
    -121,  -121,  -121,    47,    15,   -50,   -50,   -41,   -41,   -41,
      48,   -21,    50,    13,    50,     1,  -121,  -121,  -121,    50,
    -121,  -121,  -121,    51,    55,  -121,  -121,  -121,    56,    58,
      64,  -121,    11,  -121,    60,    50,    77,    14,  -121,    50,
    -121,   -38,  -121,    59,  -121,  -121,  -121,  -121,  -121,    50,
    -121,    61,   -26,    61,    50,    50,  -121,   136,    15,   -34,
      15,  -121,  -121,  -121,    66,  -121,  -121,  -121,  -121,  -121,
    -121,   -10,    15,  -121,  -121,    61,  -121,  -121,  -121,   -20,
    -121,  -121,   109,  -121,    15,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,    61,  -121,    89,  -121,    70,  -121,
      68,   113,   103,  -121,   -18,    61,    15,    88,  -121,    22,
      90,    15,    92,  -121,  -121,  -121,  -121,  -121,    61,  -121,
    -121,    50,    50,  -121,  -121,   -16,  -121,    93,    15,  -121,
    -121
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     2,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    92,     0,    16,    17,    18,
       0,     0,     0,     0,     0,     0,     0,    35,    56,     0,
      33,    37,    34,     0,    36,     0,     0,     0,     0,     0,
       1,     3,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      21,    90,    91,     0,     0,    89,    87,    88,     0,     0,
       0,    57,     0,    38,     0,     0,     0,     0,    67,     0,
      28,     0,    39,     0,    82,    83,    84,    85,    86,     0,
      23,     0,     0,     0,     0,     0,    26,     0,     0,     0,
       0,    48,    46,    47,    49,    50,    51,    52,    54,    53,
      43,    41,     0,    65,    66,     0,    60,    63,    62,     0,
      58,    61,     0,    69,     0,    68,    72,    73,    74,    75,
      76,    77,    78,    79,     0,    29,     0,    40,     0,    19,
       0,     0,     0,    22,     0,     0,     0,     0,    27,    70,
       0,     0,     0,    45,    44,    64,    59,    24,     0,    80,
      81,     0,     0,    20,    42,     0,    71,     0,     0,    55,
      25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,   134,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,    -7,    63,  -121,    43,  -121,
    -121,     2,  -120,   -93,  -121,  -121,    52,   -97,  -121,  -121,
    -121,   -15,    97,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    39,    45,    40,    91,    92,   121,
     148,   107,   129,   130,   131,    87,    88,   108,   144,   171,
      42,    78,    73,    27
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    29,   122,    47,    25,   154,   146,   134,    41,    48,
     133,    75,    38,    71,    25,   109,    89,    25,    25,   151,
     110,    38,    76,    53,    54,    30,    99,    62,    38,   104,
     152,    84,   132,   155,    43,   155,    63,   155,   156,    65,
     165,    44,   178,    79,    80,    66,    67,    68,   175,    49,
      31,   159,    70,    46,    82,    26,    55,    72,    72,    77,
      77,    77,   166,    90,    83,    26,    86,   105,    26,    26,
      85,    93,   169,   170,   176,    32,    33,    34,    35,    36,
     100,    52,    56,    57,    58,   106,   120,    41,   123,   124,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    59,
      60,    61,    62,    64,    69,    37,   145,    86,   149,    94,
      81,    93,    38,    95,    96,    38,    97,   101,   125,   103,
     153,    44,    98,   150,   126,   127,   128,   157,   161,    50,
     160,   162,   158,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,   163,   164,   168,    51,   172,   102,    11,
     174,   179,   147,    74,   167,     0,     0,   135,     0,   173,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,     0,     0,     0,   177,     0,   180,    11,   136,   137,
     138,   139,   140,   141,   142,   143
};

static const yytype_int16 yycheck[] =
{
       2,     3,    99,    10,     3,   125,    40,   104,     6,    21,
     103,    52,    62,    63,     3,    53,    15,     3,     3,    29,
      58,    62,    63,    30,    31,    19,    15,    53,    62,    15,
      40,    18,    58,    53,    16,    53,    43,    53,    58,    46,
      58,    62,    58,    58,    59,    47,    48,    49,   168,    61,
      19,   144,    54,    14,    61,    54,    57,    55,    56,    57,
      58,    59,   155,    65,    62,    54,    64,    53,    54,    54,
      57,    69,    50,    51,   171,    22,    23,    24,    25,    26,
      82,     3,    57,    57,    57,    87,    93,    85,    27,    28,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    57,
      56,    14,    53,    17,    57,    52,   108,   105,   110,    58,
      62,   109,    62,    58,    58,    62,    58,    57,    57,    42,
     122,    62,    58,    57,    63,    64,    65,    18,    58,     0,
      41,    63,   134,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    30,    41,    57,    12,    57,    85,    20,
      58,    58,   109,    56,   156,    -1,    -1,   105,    -1,   161,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,   172,    -1,   178,    20,    42,    43,
      44,    45,    46,    47,    48,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    20,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     3,    54,    99,    99,    99,
      19,    19,    22,    23,    24,    25,    26,    52,    62,    80,
      82,    87,    96,    16,    62,    81,    14,    81,    21,    61,
       0,    68,     3,    81,    81,    57,    57,    57,    57,    57,
      56,    14,    53,    81,    17,    81,    99,    99,    99,    57,
      99,    63,    87,    98,    98,    52,    63,    87,    97,    97,
      97,    62,    81,    87,    18,    57,    87,    91,    92,    15,
      99,    83,    84,    87,    58,    58,    58,    58,    58,    15,
      99,    57,    82,    42,    15,    53,    99,    87,    93,    53,
      58,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      81,    85,    93,    27,    28,    57,    63,    64,    65,    88,
      89,    90,    58,    89,    93,    92,    42,    43,    44,    45,
      46,    47,    48,    49,    94,    99,    40,    84,    86,    99,
      57,    29,    40,    99,    88,    53,    58,    18,    99,    89,
      41,    58,    63,    30,    41,    58,    89,    99,    57,    50,
      51,    95,    57,    99,    58,    88,    93,    87,    58,    58,
      99
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    67,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    69,    70,    71,    72,
      72,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    79,    79,    80,    80,    80,    81,    82,    82,    83,
      83,    84,    84,    84,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    86,    87,    87,    88,    88,
      89,    89,    89,    89,    89,    90,    90,    91,    91,    92,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      95,    95,    96,    96,    96,    96,    96,    97,    97,    97,
      98,    98,    99,    99
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     7,
       9,     4,     7,     5,     8,    11,     5,     7,     4,     6,
       3,     3,     3,     1,     1,     1,     1,     1,     3,     1,
       3,     2,     5,     2,     4,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     1,     3,     1,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     3,     3,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     1,     1,     1,
       1,     1,     1,     2
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
#line 113 "sql.y"
                {
                    ast_node->statement_type = BEGIN_TRANSACTION_STMT;
                }
#line 1516 "y.tab.c"
    break;

  case 6: /* statement: commit_transaction_statement  */
#line 117 "sql.y"
                {
                    ast_node->statement_type = COMMIT_TRANSACTION_STMT;
                }
#line 1524 "y.tab.c"
    break;

  case 7: /* statement: rollback_transaction_statement  */
#line 121 "sql.y"
                {
                    ast_node->statement_type = ROLLBACK_TRANSACTION_STMT;
                }
#line 1532 "y.tab.c"
    break;

  case 8: /* statement: create_table_statement  */
#line 125 "sql.y"
                {
                    ast_node->statement_type = CREATE_TABLE_STMT;
                    ast_node->create_table_node = (yyvsp[0].create_table_node);
                }
#line 1541 "y.tab.c"
    break;

  case 9: /* statement: drop_table_statement  */
#line 130 "sql.y"
                {
                    ast_node->statement_type = DROP_TABLE_STMT;
                    ast_node->drop_table_node = (yyvsp[0].drop_table_node);
                }
#line 1550 "y.tab.c"
    break;

  case 10: /* statement: select_statement  */
#line 135 "sql.y"
                {
                    ast_node->statement_type = SELECT_STMT;
                    ast_node->select_node = (yyvsp[0].select_node);
                }
#line 1559 "y.tab.c"
    break;

  case 11: /* statement: insert_statement  */
#line 140 "sql.y"
                {
                    ast_node->statement_type = INSERT_STMT;
                    ast_node->insert_node = (yyvsp[0].insert_node);
                }
#line 1568 "y.tab.c"
    break;

  case 12: /* statement: update_statement  */
#line 145 "sql.y"
                {
                    ast_node->statement_type = UPDATE_STMT;
                    ast_node->update_node = (yyvsp[0].update_node);
                }
#line 1577 "y.tab.c"
    break;

  case 13: /* statement: delete_statement  */
#line 150 "sql.y"
                {
                    ast_node->statement_type = DELETE_STMT;
                    ast_node->delete_node = (yyvsp[0].delete_node);
                }
#line 1586 "y.tab.c"
    break;

  case 14: /* statement: describe_statement  */
#line 155 "sql.y"
                {
                    ast_node->statement_type = DESCRIBE_STMT;
                    ast_node->describe_node = (yyvsp[0].describe_node);
                }
#line 1595 "y.tab.c"
    break;

  case 15: /* statement: show_statement  */
#line 160 "sql.y"
                {
                    ast_node->statement_type = SHOW_STMT;
                    ast_node->show_node = (yyvsp[0].show_node);
                }
#line 1604 "y.tab.c"
    break;

  case 19: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs RIGHTPAREN end  */
#line 176 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = (yyvsp[-4].s_value);
                    create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1615 "y.tab.c"
    break;

  case 20: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs COMMA primary_key_statement RIGHTPAREN end  */
#line 183 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = (yyvsp[-6].s_value);
                    create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
                    create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1627 "y.tab.c"
    break;

  case 21: /* drop_table_statement: DROP TABLE table end  */
#line 193 "sql.y"
                {
                    DropTableNode *drop_table_node = make_drop_table_node();
                    drop_table_node->table_name = (yyvsp[-1].s_value);
                    (yyval.drop_table_node) = drop_table_node;
                }
#line 1637 "y.tab.c"
    break;

  case 22: /* select_statement: SELECT select_items FROM table WHERE cond end  */
#line 201 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-5].select_items_node);
                    select_node->table_name = (yyvsp[-3].s_value);
                    select_node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.select_node) = select_node;
                }
#line 1649 "y.tab.c"
    break;

  case 23: /* select_statement: SELECT select_items FROM table end  */
#line 209 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-3].select_items_node);
                    select_node->table_name = (yyvsp[-1].s_value);
                    (yyval.select_node) = select_node;
                }
#line 1660 "y.tab.c"
    break;

  case 24: /* insert_statement: INSERT INTO table VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 218 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = true;
                    node->table_name = (yyvsp[-5].s_value);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1672 "y.tab.c"
    break;

  case 25: /* insert_statement: INSERT INTO table LEFTPAREN columns RIGHTPAREN VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 226 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = false;
                    node->table_name = (yyvsp[-8].s_value);
                    node->columns_set_node = (yyvsp[-6].column_set_node);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1685 "y.tab.c"
    break;

  case 26: /* update_statement: UPDATE table SET assignments end  */
#line 237 "sql.y"
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = (yyvsp[-3].s_value);
                    node->assignment_set_node = (yyvsp[-1].assignment_set_node);
                    (yyval.update_node) = node;
                }
#line 1696 "y.tab.c"
    break;

  case 27: /* update_statement: UPDATE table SET assignments WHERE cond end  */
#line 244 "sql.y"
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = (yyvsp[-5].s_value);
                    node->assignment_set_node = (yyvsp[-3].assignment_set_node);
                    node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.update_node) = node;
                }
#line 1708 "y.tab.c"
    break;

  case 28: /* delete_statement: DELETE FROM table end  */
#line 254 "sql.y"
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = (yyvsp[-1].s_value);
                    (yyval.delete_node) = node;
                }
#line 1718 "y.tab.c"
    break;

  case 29: /* delete_statement: DELETE FROM table WHERE cond end  */
#line 260 "sql.y"
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = (yyvsp[-3].s_value);
                    node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.delete_node) = node;
                }
#line 1729 "y.tab.c"
    break;

  case 30: /* describe_statement: DESCRIBE table end  */
#line 269 "sql.y"
                {
                    DescribeNode *node = make_describe_node();
                    node->table_name = db_strdup((yyvsp[-1].s_value));
                    (yyval.describe_node) = node;
                }
#line 1739 "y.tab.c"
    break;

  case 31: /* show_statement: SHOW TABLES end  */
#line 277 "sql.y"
                {
                    (yyval.show_node) = make_show_node(SHOW_TABLES);
                }
#line 1747 "y.tab.c"
    break;

  case 32: /* show_statement: SHOW MEMORY end  */
#line 281 "sql.y"
                {
                    (yyval.show_node) = make_show_node(SHOW_MEMORY);
                }
#line 1755 "y.tab.c"
    break;

  case 33: /* select_items: columns  */
#line 287 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_COLUMNS;
                    select_items_node->column_set_node= (yyvsp[0].column_set_node);
                    (yyval.select_items_node) = select_items_node;
                }
#line 1766 "y.tab.c"
    break;

  case 34: /* select_items: function  */
#line 294 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_FUNCTION;
                    select_items_node->function_node = (yyvsp[0].function_node);
                    (yyval.select_items_node) = select_items_node;
                }
#line 1777 "y.tab.c"
    break;

  case 35: /* select_items: ALL  */
#line 301 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_ALL;
                    (yyval.select_items_node) = select_items_node;
                }
#line 1787 "y.tab.c"
    break;

  case 36: /* table: IDENTIFIER  */
#line 309 "sql.y"
                {
                    (yyval.s_value) = (yyvsp[0].s_value);
                }
#line 1795 "y.tab.c"
    break;

  case 37: /* columns: column  */
#line 315 "sql.y"
                {
                    ColumnSetNode *column_set_node = make_column_set_node();
                    add_column_to_set(column_set_node, (yyvsp[0].column_node));
                    (yyval.column_set_node) = column_set_node;
                }
#line 1805 "y.tab.c"
    break;

  case 38: /* columns: columns COMMA column  */
#line 321 "sql.y"
                {
                    (yyval.column_set_node) = (yyvsp[-2].column_set_node);
                    add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
                }
#line 1814 "y.tab.c"
    break;

  case 39: /* column_defs: column_def  */
#line 328 "sql.y"
                {
                    ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
                    add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
                    (yyval.column_def_set_node) = column_def_set_node;
                }
#line 1824 "y.tab.c"
    break;

  case 40: /* column_defs: column_defs COMMA column_def  */
#line 334 "sql.y"
                {
                    (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
                    add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
                }
#line 1833 "y.tab.c"
    break;

  case 41: /* column_def: column data_type  */
#line 341 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-1].column_node);
                    column_def_node->data_type = (yyvsp[0].data_type);
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = false;
                    column_def_node->is_define_len = false;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1847 "y.tab.c"
    break;

  case 42: /* column_def: column STRING LEFTPAREN INTVALUE RIGHTPAREN  */
#line 351 "sql.y"
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
#line 1862 "y.tab.c"
    break;

  case 43: /* column_def: column table  */
#line 362 "sql.y"
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
#line 1877 "y.tab.c"
    break;

  case 44: /* column_def: column data_type PRIMARY KEY  */
#line 373 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-3].column_node);
                    column_def_node->data_type = (yyvsp[-2].data_type);
                    column_def_node->is_primary = true;
                    column_def_node->allow_null = false;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1890 "y.tab.c"
    break;

  case 45: /* column_def: column data_type NOT NULLX  */
#line 382 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-3].column_node);
                    column_def_node->data_type = (yyvsp[-2].data_type);
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = true;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1903 "y.tab.c"
    break;

  case 46: /* data_type: INT  */
#line 392 "sql.y"
                        { (yyval.data_type) = T_INT; }
#line 1909 "y.tab.c"
    break;

  case 47: /* data_type: LONG  */
#line 393 "sql.y"
                        { (yyval.data_type) = T_LONG;  }
#line 1915 "y.tab.c"
    break;

  case 48: /* data_type: CHAR  */
#line 394 "sql.y"
                        { (yyval.data_type) = T_CHAR; }
#line 1921 "y.tab.c"
    break;

  case 49: /* data_type: STRING  */
#line 395 "sql.y"
                        { (yyval.data_type) = T_STRING; }
#line 1927 "y.tab.c"
    break;

  case 50: /* data_type: BOOL  */
#line 396 "sql.y"
                        { (yyval.data_type) = T_BOOL; }
#line 1933 "y.tab.c"
    break;

  case 51: /* data_type: FLOAT  */
#line 397 "sql.y"
                        { (yyval.data_type) = T_FLOAT; }
#line 1939 "y.tab.c"
    break;

  case 52: /* data_type: DOUBLE  */
#line 398 "sql.y"
                        { (yyval.data_type) = T_DOUBLE; }
#line 1945 "y.tab.c"
    break;

  case 53: /* data_type: TIMESTAMP  */
#line 399 "sql.y"
                        { (yyval.data_type) = T_TIMESTAMP; }
#line 1951 "y.tab.c"
    break;

  case 54: /* data_type: DATE  */
#line 400 "sql.y"
                        { (yyval.data_type) = T_DATE; }
#line 1957 "y.tab.c"
    break;

  case 55: /* primary_key_statement: PRIMARY KEY LEFTPAREN column RIGHTPAREN  */
#line 404 "sql.y"
                {
                    PrimaryKeyNode *primary_key_node = make_primary_key_node();
                    primary_key_node->column = (yyvsp[-1].column_node);
                    (yyval.primary_key_node) = primary_key_node;
                }
#line 1967 "y.tab.c"
    break;

  case 56: /* column: IDENTIFIER  */
#line 412 "sql.y"
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = db_strdup((yyvsp[0].s_value));
                    column_node->has_sub_column = false;
                    (yyval.column_node) = column_node;
                }
#line 1978 "y.tab.c"
    break;

  case 57: /* column: IDENTIFIER POINT IDENTIFIER  */
#line 419 "sql.y"
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = db_strdup((yyvsp[-2].s_value));
                    column_node->sub_column_name = db_strdup((yyvsp[0].s_value));
                    column_node->has_sub_column = true;
                    (yyval.column_node) = column_node;
                }
#line 1990 "y.tab.c"
    break;

  case 58: /* value_items: value_item  */
#line 429 "sql.y"
                {
                    ValueItemSetNode *node = make_value_item_set_node();
                    add_value_item(node, (yyvsp[0].value_item_node));
                    (yyval.value_item_set_node) = node;
                }
#line 2000 "y.tab.c"
    break;

  case 59: /* value_items: value_items COMMA value_item  */
#line 435 "sql.y"
                {
                    (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
                    add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
                }
#line 2009 "y.tab.c"
    break;

  case 60: /* value_item: INTVALUE  */
#line 442 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->data_type = T_INT;
                    (yyval.value_item_node) = node;
                }
#line 2020 "y.tab.c"
    break;

  case 61: /* value_item: BOOLVALUE  */
#line 449 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->b_value = (yyvsp[0].b_value);
                    node->data_type = T_BOOL;
                    (yyval.value_item_node) = node;
                }
#line 2031 "y.tab.c"
    break;

  case 62: /* value_item: STRINGVALUE  */
#line 456 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->s_value = (yyvsp[0].s_value);
                    node->data_type = T_STRING;
                    (yyval.value_item_node) = node;
                }
#line 2042 "y.tab.c"
    break;

  case 63: /* value_item: FLOATVALUE  */
#line 463 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->f_value = (yyvsp[0].f_value);
                    node->data_type = T_FLOAT;
                    (yyval.value_item_node) = node;
                }
#line 2053 "y.tab.c"
    break;

  case 64: /* value_item: LEFTPAREN value_items RIGHTPAREN  */
#line 470 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->nest_value_item_set = (yyvsp[-1].value_item_set_node);
                    node->data_type = T_REFERENCE;
                    (yyval.value_item_node) = node;
                }
#line 2064 "y.tab.c"
    break;

  case 65: /* BOOLVALUE: TRUE  */
#line 479 "sql.y"
                {
                    (yyval.b_value) = true;
                }
#line 2072 "y.tab.c"
    break;

  case 66: /* BOOLVALUE: FALSE  */
#line 483 "sql.y"
                {
                    (yyval.b_value) = false;
                }
#line 2080 "y.tab.c"
    break;

  case 67: /* assignments: assignment  */
#line 489 "sql.y"
                {
                    AssignmentSetNode *node = make_assignment_set_node();
                    add_assignment_to_set(node, (yyvsp[0].assignment_node));
                    (yyval.assignment_set_node) = node;
                }
#line 2090 "y.tab.c"
    break;

  case 68: /* assignments: assignments COMMA assignment  */
#line 495 "sql.y"
                {
                    add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
                    (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
                }
#line 2099 "y.tab.c"
    break;

  case 69: /* assignment: column EQ value_item  */
#line 502 "sql.y"
                {
                    AssignmentNode *node = make_assignment_node();
                    node->column = (yyvsp[-2].column_node);
                    node->value = (yyvsp[0].value_item_node);
                    (yyval.assignment_node) = node;
                }
#line 2110 "y.tab.c"
    break;

  case 70: /* cond: column opr value_item  */
#line 511 "sql.y"
                {
                    ConditionNode *cond_node = make_cond_node();
                    cond_node->column = (yyvsp[-2].column_node);
                    cond_node->opr_type = (yyvsp[-1].opr_type);
                    cond_node->value = (yyvsp[0].value_item_node);
                    cond_node->type = EXEC_CONDITION;
                    (yyval.cond_node) = cond_node;
                }
#line 2123 "y.tab.c"
    break;

  case 71: /* cond: column opr value_item conn cond  */
#line 520 "sql.y"
                {
                    ConditionNode *cond_node = make_cond_node();
                    cond_node->column = (yyvsp[-4].column_node);
                    cond_node->opr_type = (yyvsp[-3].opr_type);
                    cond_node->value = (yyvsp[-2].value_item_node);
                    cond_node->conn_type = (yyvsp[-1].conn_type);
                    cond_node->next = (yyvsp[0].cond_node);
                    cond_node->type = EXEC_CONDITION;
                    (yyval.cond_node) = cond_node;
                }
#line 2138 "y.tab.c"
    break;

  case 72: /* opr: EQ  */
#line 532 "sql.y"
                    { (yyval.opr_type) = O_EQ; }
#line 2144 "y.tab.c"
    break;

  case 73: /* opr: NE  */
#line 533 "sql.y"
                    { (yyval.opr_type) = O_NE; }
#line 2150 "y.tab.c"
    break;

  case 74: /* opr: GT  */
#line 534 "sql.y"
                    { (yyval.opr_type) = O_GT; }
#line 2156 "y.tab.c"
    break;

  case 75: /* opr: GE  */
#line 535 "sql.y"
                    { (yyval.opr_type) = O_GE; }
#line 2162 "y.tab.c"
    break;

  case 76: /* opr: LT  */
#line 536 "sql.y"
                    { (yyval.opr_type) = O_LT; }
#line 2168 "y.tab.c"
    break;

  case 77: /* opr: LE  */
#line 537 "sql.y"
                    { (yyval.opr_type) = O_LE; }
#line 2174 "y.tab.c"
    break;

  case 78: /* opr: IN  */
#line 538 "sql.y"
                    { (yyval.opr_type) = O_IN; }
#line 2180 "y.tab.c"
    break;

  case 79: /* opr: LIKE  */
#line 539 "sql.y"
                    { (yyval.opr_type) = O_LIKE; }
#line 2186 "y.tab.c"
    break;

  case 80: /* conn: AND  */
#line 542 "sql.y"
                    { (yyval.conn_type) = C_AND; }
#line 2192 "y.tab.c"
    break;

  case 81: /* conn: OR  */
#line 543 "sql.y"
                    { (yyval.conn_type) = C_OR; }
#line 2198 "y.tab.c"
    break;

  case 82: /* function: MAX LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 547 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MAX;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2209 "y.tab.c"
    break;

  case 83: /* function: MIN LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 554 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MIN;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2220 "y.tab.c"
    break;

  case 84: /* function: COUNT LEFTPAREN function_value RIGHTPAREN  */
#line 561 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_COUNT;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2231 "y.tab.c"
    break;

  case 85: /* function: SUM LEFTPAREN function_value RIGHTPAREN  */
#line 568 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_SUM;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2242 "y.tab.c"
    break;

  case 86: /* function: AVG LEFTPAREN function_value RIGHTPAREN  */
#line 575 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_AVG;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2253 "y.tab.c"
    break;

  case 87: /* function_value: INTVALUE  */
#line 584 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 2264 "y.tab.c"
    break;

  case 88: /* function_value: column  */
#line 591 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = (yyvsp[0].column_node);
                    node->value_type = V_COLUMN;
                    (yyval.function_value_node) = node;
                }
#line 2275 "y.tab.c"
    break;

  case 89: /* function_value: ALL  */
#line 598 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->value_type = V_ALL;
                    (yyval.function_value_node) = node;
                }
#line 2285 "y.tab.c"
    break;

  case 90: /* non_all_function_value: INTVALUE  */
#line 606 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 2296 "y.tab.c"
    break;

  case 91: /* non_all_function_value: column  */
#line 613 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = (yyvsp[0].column_node);
                    node->value_type = V_COLUMN;
                    (yyval.function_value_node) = node;
                }
#line 2307 "y.tab.c"
    break;


#line 2311 "y.tab.c"

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

#line 624 "sql.y"

