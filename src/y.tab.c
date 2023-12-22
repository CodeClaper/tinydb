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
#include "y.tab.h"

int yywrap() {
    return 1;
}
int yylex();

#line 85 "y.tab.c"

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
    CREATE = 261,                  /* CREATE  */
    SELECT = 262,                  /* SELECT  */
    INSERT = 263,                  /* INSERT  */
    UPDATE = 264,                  /* UPDATE  */
    DELETE = 265,                  /* DELETE  */
    DESCRIBE = 266,                /* DESCRIBE  */
    FROM = 267,                    /* FROM  */
    WHERE = 268,                   /* WHERE  */
    INTO = 269,                    /* INTO  */
    SET = 270,                     /* SET  */
    VALUES = 271,                  /* VALUES  */
    TABLE = 272,                   /* TABLE  */
    SHOW = 273,                    /* SHOW  */
    TABLES = 274,                  /* TABLES  */
    MAX = 275,                     /* MAX  */
    MIN = 276,                     /* MIN  */
    COUNT = 277,                   /* COUNT  */
    SUM = 278,                     /* SUM  */
    AVG = 279,                     /* AVG  */
    TRUE = 280,                    /* TRUE  */
    FALSE = 281,                   /* FALSE  */
    NOT = 282,                     /* NOT  */
    NULLX = 283,                   /* NULLX  */
    INT = 284,                     /* INT  */
    CHAR = 285,                    /* CHAR  */
    STRING = 286,                  /* STRING  */
    BOOL = 287,                    /* BOOL  */
    FLOAT = 288,                   /* FLOAT  */
    DOUBLE = 289,                  /* DOUBLE  */
    DATE = 290,                    /* DATE  */
    TIMESTAMP = 291,               /* TIMESTAMP  */
    PRIMARY = 292,                 /* PRIMARY  */
    KEY = 293,                     /* KEY  */
    EQ = 294,                      /* EQ  */
    NE = 295,                      /* NE  */
    GT = 296,                      /* GT  */
    GE = 297,                      /* GE  */
    LT = 298,                      /* LT  */
    LE = 299,                      /* LE  */
    IN = 300,                      /* IN  */
    LIKE = 301,                    /* LIKE  */
    AND = 302,                     /* AND  */
    OR = 303,                      /* OR  */
    ALL = 304,                     /* ALL  */
    COMMA = 305,                   /* COMMA  */
    SEMICOLON = 306,               /* SEMICOLON  */
    QUOTE = 307,                   /* QUOTE  */
    POINT = 308,                   /* POINT  */
    LEFTPAREN = 309,               /* LEFTPAREN  */
    RIGHTPAREN = 310,              /* RIGHTPAREN  */
    SYSTEM = 311,                  /* SYSTEM  */
    CONFIG = 312,                  /* CONFIG  */
    MEMORY = 313,                  /* MEMORY  */
    IDENTIFIER = 314,              /* IDENTIFIER  */
    INTVALUE = 315,                /* INTVALUE  */
    FLOATVALUE = 316,              /* FLOATVALUE  */
    STRINGVALUE = 317              /* STRINGVALUE  */
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
#define CREATE 261
#define SELECT 262
#define INSERT 263
#define UPDATE 264
#define DELETE 265
#define DESCRIBE 266
#define FROM 267
#define WHERE 268
#define INTO 269
#define SET 270
#define VALUES 271
#define TABLE 272
#define SHOW 273
#define TABLES 274
#define MAX 275
#define MIN 276
#define COUNT 277
#define SUM 278
#define AVG 279
#define TRUE 280
#define FALSE 281
#define NOT 282
#define NULLX 283
#define INT 284
#define CHAR 285
#define STRING 286
#define BOOL 287
#define FLOAT 288
#define DOUBLE 289
#define DATE 290
#define TIMESTAMP 291
#define PRIMARY 292
#define KEY 293
#define EQ 294
#define NE 295
#define GT 296
#define GE 297
#define LT 298
#define LE 299
#define IN 300
#define LIKE 301
#define AND 302
#define OR 303
#define ALL 304
#define COMMA 305
#define SEMICOLON 306
#define QUOTE 307
#define POINT 308
#define LEFTPAREN 309
#define RIGHTPAREN 310
#define SYSTEM 311
#define CONFIG 312
#define MEMORY 313
#define IDENTIFIER 314
#define INTVALUE 315
#define FLOATVALUE 316
#define STRINGVALUE 317

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "sql.y"

   char                     *s_value;
   int                      i_value;
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
   SelectNode               *select_node;
   InsertNode               *insert_node;
   UpdateNode               *update_node;
   DeleteNode               *delete_node;
   DescribeNode             *describe_node;
   ShowNode                 *show_node;
   ASTNode                  *ast_node;

#line 294 "y.tab.c"

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
  YYSYMBOL_CREATE = 6,                     /* CREATE  */
  YYSYMBOL_SELECT = 7,                     /* SELECT  */
  YYSYMBOL_INSERT = 8,                     /* INSERT  */
  YYSYMBOL_UPDATE = 9,                     /* UPDATE  */
  YYSYMBOL_DELETE = 10,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 11,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 12,                      /* FROM  */
  YYSYMBOL_WHERE = 13,                     /* WHERE  */
  YYSYMBOL_INTO = 14,                      /* INTO  */
  YYSYMBOL_SET = 15,                       /* SET  */
  YYSYMBOL_VALUES = 16,                    /* VALUES  */
  YYSYMBOL_TABLE = 17,                     /* TABLE  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_TABLES = 19,                    /* TABLES  */
  YYSYMBOL_MAX = 20,                       /* MAX  */
  YYSYMBOL_MIN = 21,                       /* MIN  */
  YYSYMBOL_COUNT = 22,                     /* COUNT  */
  YYSYMBOL_SUM = 23,                       /* SUM  */
  YYSYMBOL_AVG = 24,                       /* AVG  */
  YYSYMBOL_TRUE = 25,                      /* TRUE  */
  YYSYMBOL_FALSE = 26,                     /* FALSE  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_NULLX = 28,                     /* NULLX  */
  YYSYMBOL_INT = 29,                       /* INT  */
  YYSYMBOL_CHAR = 30,                      /* CHAR  */
  YYSYMBOL_STRING = 31,                    /* STRING  */
  YYSYMBOL_BOOL = 32,                      /* BOOL  */
  YYSYMBOL_FLOAT = 33,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 34,                    /* DOUBLE  */
  YYSYMBOL_DATE = 35,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 36,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 37,                   /* PRIMARY  */
  YYSYMBOL_KEY = 38,                       /* KEY  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_NE = 40,                        /* NE  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_GE = 42,                        /* GE  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_IN = 45,                        /* IN  */
  YYSYMBOL_LIKE = 46,                      /* LIKE  */
  YYSYMBOL_AND = 47,                       /* AND  */
  YYSYMBOL_OR = 48,                        /* OR  */
  YYSYMBOL_ALL = 49,                       /* ALL  */
  YYSYMBOL_COMMA = 50,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 51,                 /* SEMICOLON  */
  YYSYMBOL_QUOTE = 52,                     /* QUOTE  */
  YYSYMBOL_POINT = 53,                     /* POINT  */
  YYSYMBOL_LEFTPAREN = 54,                 /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 55,                /* RIGHTPAREN  */
  YYSYMBOL_SYSTEM = 56,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 57,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 58,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 59,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 60,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 61,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 62,               /* STRINGVALUE  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_statements = 64,                /* statements  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_begin_transaction_statement = 66, /* begin_transaction_statement  */
  YYSYMBOL_commit_transaction_statement = 67, /* commit_transaction_statement  */
  YYSYMBOL_create_table_statement = 68,    /* create_table_statement  */
  YYSYMBOL_select_statement = 69,          /* select_statement  */
  YYSYMBOL_insert_statement = 70,          /* insert_statement  */
  YYSYMBOL_update_statement = 71,          /* update_statement  */
  YYSYMBOL_delete_statement = 72,          /* delete_statement  */
  YYSYMBOL_describe_statement = 73,        /* describe_statement  */
  YYSYMBOL_show_statement = 74,            /* show_statement  */
  YYSYMBOL_select_items = 75,              /* select_items  */
  YYSYMBOL_table = 76,                     /* table  */
  YYSYMBOL_columns = 77,                   /* columns  */
  YYSYMBOL_column_defs = 78,               /* column_defs  */
  YYSYMBOL_column_def = 79,                /* column_def  */
  YYSYMBOL_data_type = 80,                 /* data_type  */
  YYSYMBOL_primary_key_statement = 81,     /* primary_key_statement  */
  YYSYMBOL_column = 82,                    /* column  */
  YYSYMBOL_value_items = 83,               /* value_items  */
  YYSYMBOL_value_item = 84,                /* value_item  */
  YYSYMBOL_BOOLVALUE = 85,                 /* BOOLVALUE  */
  YYSYMBOL_assignments = 86,               /* assignments  */
  YYSYMBOL_assignment = 87,                /* assignment  */
  YYSYMBOL_cond = 88,                      /* cond  */
  YYSYMBOL_opr = 89,                       /* opr  */
  YYSYMBOL_conn = 90,                      /* conn  */
  YYSYMBOL_function = 91,                  /* function  */
  YYSYMBOL_function_value = 92,            /* function_value  */
  YYSYMBOL_non_all_function_value = 93,    /* non_all_function_value  */
  YYSYMBOL_end = 94                        /* end  */
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
#define YYFINAL  44
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   173

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   104,   104,   105,   106,   109,   113,   117,   122,   127,
     132,   137,   142,   147,   154,   157,   160,   167,   177,   185,
     194,   202,   213,   220,   230,   236,   245,   253,   257,   263,
     270,   277,   285,   291,   297,   304,   310,   317,   327,   338,
     349,   360,   361,   362,   363,   364,   365,   366,   367,   370,
     378,   385,   395,   401,   408,   415,   422,   429,   436,   445,
     449,   455,   461,   468,   477,   486,   499,   500,   501,   502,
     503,   504,   505,   506,   509,   510,   513,   520,   527,   534,
     541,   550,   557,   564,   572,   579,   588,   589
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
  "COMMIT", "CREATE", "SELECT", "INSERT", "UPDATE", "DELETE", "DESCRIBE",
  "FROM", "WHERE", "INTO", "SET", "VALUES", "TABLE", "SHOW", "TABLES",
  "MAX", "MIN", "COUNT", "SUM", "AVG", "TRUE", "FALSE", "NOT", "NULLX",
  "INT", "CHAR", "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE", "TIMESTAMP",
  "PRIMARY", "KEY", "EQ", "NE", "GT", "GE", "LT", "LE", "IN", "LIKE",
  "AND", "OR", "ALL", "COMMA", "SEMICOLON", "QUOTE", "POINT", "LEFTPAREN",
  "RIGHTPAREN", "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER", "INTVALUE",
  "FLOATVALUE", "STRINGVALUE", "$accept", "statements", "statement",
  "begin_transaction_statement", "commit_transaction_statement",
  "create_table_statement", "select_statement", "insert_statement",
  "update_statement", "delete_statement", "describe_statement",
  "show_statement", "select_items", "table", "columns", "column_defs",
  "column_def", "data_type", "primary_key_statement", "column",
  "value_items", "value_item", "BOOLVALUE", "assignments", "assignment",
  "cond", "opr", "conn", "function", "function_value",
  "non_all_function_value", "end", YY_NULLPTR
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

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     146,    12,    12,    -5,    45,     5,   -31,    36,   -31,   -15,
     120,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,    35,  -114,  -114,   -31,    37,    38,    39,    41,
      42,  -114,    -4,    68,    40,  -114,  -114,   -31,  -114,    82,
     -31,    12,    12,    12,  -114,  -114,  -114,    47,   -43,   -43,
     -38,   -38,   -38,    46,   -31,    54,    -8,    54,     7,  -114,
    -114,  -114,    54,  -114,  -114,    51,    52,  -114,  -114,  -114,
      59,    60,    61,  -114,    11,  -114,    63,    54,    79,    10,
    -114,    54,  -114,   -23,  -114,    53,  -114,  -114,  -114,  -114,
    -114,    54,  -114,    48,   -21,    48,    54,    54,  -114,   127,
      12,   -28,    12,  -114,  -114,    65,  -114,  -114,  -114,  -114,
    -114,  -114,    94,    12,  -114,  -114,    48,  -114,  -114,  -114,
     -13,  -114,  -114,   106,  -114,    12,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,    48,  -114,    95,  -114,    77,
    -114,    74,   107,  -114,    20,    48,    12,    83,  -114,   -22,
      85,    12,    81,  -114,  -114,  -114,  -114,    48,  -114,  -114,
      54,    54,  -114,  -114,    26,  -114,    86,    12,  -114,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    86,     0,    14,    15,     0,     0,     0,     0,     0,
       0,    31,    50,     0,    29,    33,    30,     0,    32,     0,
       0,     0,     0,     0,     1,     3,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      27,    28,     0,    84,    85,     0,     0,    83,    81,    82,
       0,     0,     0,    51,     0,    34,     0,     0,     0,     0,
      61,     0,    24,     0,    35,     0,    76,    77,    78,    79,
      80,     0,    19,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,    41,    42,    43,    44,    45,    46,    48,
      47,    39,    37,     0,    59,    60,     0,    54,    57,    56,
       0,    52,    55,     0,    63,     0,    62,    66,    67,    68,
      69,    70,    71,    72,    73,     0,    25,     0,    36,     0,
      16,     0,     0,    18,     0,     0,     0,     0,    23,    64,
       0,     0,     0,    40,    58,    53,    20,     0,    74,    75,
       0,     0,    17,    38,     0,    65,     0,     0,    49,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,   130,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,    -7,    66,  -114,    44,  -114,  -114,     2,
    -113,   -90,  -114,  -114,    49,   -89,  -114,  -114,  -114,   -16,
      93,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    33,    39,    34,    83,    84,   112,   139,    99,
     120,   121,   122,    79,    80,   100,   135,   160,    36,    70,
      65,    23
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      24,    41,   113,   144,    42,   124,    35,   125,    76,   137,
      21,    67,    25,    21,    21,    21,    32,    63,    47,    37,
      81,    32,    68,    96,    91,   158,   159,   101,    38,    55,
      56,    32,   102,    58,   123,    71,    72,   145,    46,    59,
      60,    61,   146,    43,   164,   149,    77,    74,    40,    53,
      64,    64,    69,    69,    69,   155,    82,    75,    22,    78,
      97,    22,    22,    22,    85,    26,    27,    28,    29,    30,
     145,   165,    92,   114,   115,   154,   145,    98,   111,    35,
      54,   167,   103,   104,   105,   106,   107,   108,   109,   110,
      55,    48,    49,    50,    31,    51,    52,    57,   136,    78,
     140,    62,   116,    85,    32,    73,    86,    87,   117,   118,
     119,   143,    38,    32,    88,    89,    90,    93,    95,   141,
      44,   142,   147,   148,     1,     2,     3,     4,     5,     6,
       7,     8,   151,   150,   152,   153,   163,   157,     9,   161,
      45,   168,    66,    94,   156,   138,   126,     0,     0,   162,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     0,
       0,     0,     0,   166,     9,   169,   127,   128,   129,   130,
     131,   132,   133,   134
};

static const yytype_int16 yycheck[] =
{
       2,     8,    91,   116,    19,    95,     4,    96,    16,    37,
       3,    49,    17,     3,     3,     3,    59,    60,    25,    14,
      13,    59,    60,    13,    13,    47,    48,    50,    59,    50,
      37,    59,    55,    40,    55,    51,    52,    50,     3,    41,
      42,    43,    55,    58,   157,   135,    54,    54,    12,    53,
      48,    49,    50,    51,    52,   145,    58,    55,    51,    57,
      50,    51,    51,    51,    62,    20,    21,    22,    23,    24,
      50,   160,    74,    25,    26,    55,    50,    79,    85,    77,
      12,    55,    29,    30,    31,    32,    33,    34,    35,    36,
      50,    54,    54,    54,    49,    54,    54,    15,   100,    97,
     102,    54,    54,   101,    59,    59,    55,    55,    60,    61,
      62,   113,    59,    59,    55,    55,    55,    54,    39,    54,
       0,    27,    16,   125,     4,     5,     6,     7,     8,     9,
      10,    11,    55,    38,    60,    28,    55,    54,    18,    54,
      10,    55,    49,    77,   146,   101,    97,    -1,    -1,   151,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,   161,    18,   167,    39,    40,    41,    42,
      43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    18,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     3,    51,    94,    94,    17,    20,    21,    22,    23,
      24,    49,    59,    75,    77,    82,    91,    14,    59,    76,
      12,    76,    19,    58,     0,    65,     3,    76,    54,    54,
      54,    54,    54,    53,    12,    50,    76,    15,    76,    94,
      94,    94,    54,    60,    82,    93,    93,    49,    60,    82,
      92,    92,    92,    59,    76,    82,    16,    54,    82,    86,
      87,    13,    94,    78,    79,    82,    55,    55,    55,    55,
      55,    13,    94,    54,    77,    39,    13,    50,    94,    82,
      88,    50,    55,    29,    30,    31,    32,    33,    34,    35,
      36,    76,    80,    88,    25,    26,    54,    60,    61,    62,
      83,    84,    85,    55,    84,    88,    87,    39,    40,    41,
      42,    43,    44,    45,    46,    89,    94,    37,    79,    81,
      94,    54,    27,    94,    83,    50,    55,    16,    94,    84,
      38,    55,    60,    28,    55,    84,    94,    54,    47,    48,
      90,    54,    94,    55,    83,    88,    82,    55,    55,    94
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    67,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    74,    74,    75,
      75,    75,    76,    77,    77,    78,    78,    79,    79,    79,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      82,    82,    83,    83,    84,    84,    84,    84,    84,    85,
      85,    86,    86,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    90,    90,    91,    91,    91,    91,
      91,    92,    92,    92,    93,    93,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     7,     9,     7,     5,
       8,    11,     5,     7,     4,     6,     3,     3,     3,     1,
       1,     1,     1,     1,     3,     1,     3,     2,     5,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     3,     3,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     4,     4,
       4,     1,     1,     1,     1,     1,     1,     2
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
#line 110 "sql.y"
                {
                    ast_node->statement_type = BEGIN_TRANSACTION_STMT;
                }
#line 1490 "y.tab.c"
    break;

  case 6: /* statement: commit_transaction_statement  */
#line 114 "sql.y"
                {
                    ast_node->statement_type = COMMIT_TRANSACTION_STMT;
                }
#line 1498 "y.tab.c"
    break;

  case 7: /* statement: create_table_statement  */
#line 118 "sql.y"
                {
                    ast_node->statement_type = CREATE_TABLE_STMT;
                    ast_node->create_table_node = (yyvsp[0].create_table_node);
                }
#line 1507 "y.tab.c"
    break;

  case 8: /* statement: select_statement  */
#line 123 "sql.y"
                {
                    ast_node->statement_type = SELECT_STMT;
                    ast_node->select_node = (yyvsp[0].select_node);
                }
#line 1516 "y.tab.c"
    break;

  case 9: /* statement: insert_statement  */
#line 128 "sql.y"
                {
                    ast_node->statement_type = INSERT_STMT;
                    ast_node->insert_node = (yyvsp[0].insert_node);
                }
#line 1525 "y.tab.c"
    break;

  case 10: /* statement: update_statement  */
#line 133 "sql.y"
                {
                    ast_node->statement_type = UPDATE_STMT;
                    ast_node->update_node = (yyvsp[0].update_node);
                }
#line 1534 "y.tab.c"
    break;

  case 11: /* statement: delete_statement  */
#line 138 "sql.y"
                {
                    ast_node->statement_type = DELETE_STMT;
                    ast_node->delete_node = (yyvsp[0].delete_node);
                }
#line 1543 "y.tab.c"
    break;

  case 12: /* statement: describe_statement  */
#line 143 "sql.y"
                {
                    ast_node->statement_type = DESCRIBE_STMT;
                    ast_node->describe_node = (yyvsp[0].describe_node);
                }
#line 1552 "y.tab.c"
    break;

  case 13: /* statement: show_statement  */
#line 148 "sql.y"
                {
                    ast_node->statement_type = SHOW_STMT;
                    ast_node->show_node = (yyvsp[0].show_node);
                }
#line 1561 "y.tab.c"
    break;

  case 16: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs RIGHTPAREN end  */
#line 161 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = (yyvsp[-4].s_value);
                    create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1572 "y.tab.c"
    break;

  case 17: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs COMMA primary_key_statement RIGHTPAREN end  */
#line 168 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = (yyvsp[-6].s_value);
                    create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
                    create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1584 "y.tab.c"
    break;

  case 18: /* select_statement: SELECT select_items FROM table WHERE cond end  */
#line 178 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-5].select_items_node);
                    select_node->table_name = (yyvsp[-3].s_value);
                    select_node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.select_node) = select_node;
                }
#line 1596 "y.tab.c"
    break;

  case 19: /* select_statement: SELECT select_items FROM table end  */
#line 186 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-3].select_items_node);
                    select_node->table_name = (yyvsp[-1].s_value);
                    (yyval.select_node) = select_node;
                }
#line 1607 "y.tab.c"
    break;

  case 20: /* insert_statement: INSERT INTO table VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 195 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = true;
                    node->table_name = (yyvsp[-5].s_value);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1619 "y.tab.c"
    break;

  case 21: /* insert_statement: INSERT INTO table LEFTPAREN columns RIGHTPAREN VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 203 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = false;
                    node->table_name = (yyvsp[-8].s_value);
                    node->columns_set_node = (yyvsp[-6].column_set_node);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1632 "y.tab.c"
    break;

  case 22: /* update_statement: UPDATE table SET assignments end  */
#line 214 "sql.y"
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = (yyvsp[-3].s_value);
                    node->assignment_set_node = (yyvsp[-1].assignment_set_node);
                    (yyval.update_node) = node;
                }
#line 1643 "y.tab.c"
    break;

  case 23: /* update_statement: UPDATE table SET assignments WHERE cond end  */
#line 221 "sql.y"
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = (yyvsp[-5].s_value);
                    node->assignment_set_node = (yyvsp[-3].assignment_set_node);
                    node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.update_node) = node;
                }
#line 1655 "y.tab.c"
    break;

  case 24: /* delete_statement: DELETE FROM table end  */
#line 231 "sql.y"
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = (yyvsp[-1].s_value);
                    (yyval.delete_node) = node;
                }
#line 1665 "y.tab.c"
    break;

  case 25: /* delete_statement: DELETE FROM table WHERE cond end  */
#line 237 "sql.y"
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = (yyvsp[-3].s_value);
                    node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.delete_node) = node;
                }
#line 1676 "y.tab.c"
    break;

  case 26: /* describe_statement: DESCRIBE table end  */
#line 246 "sql.y"
                {
                    DescribeNode *node = make_describe_node();
                    node->table_name = strdup((yyvsp[-1].s_value));
                    (yyval.describe_node) = node;
                }
#line 1686 "y.tab.c"
    break;

  case 27: /* show_statement: SHOW TABLES end  */
#line 254 "sql.y"
                {
                    (yyval.show_node) = make_show_node(SHOW_TABLES);
                }
#line 1694 "y.tab.c"
    break;

  case 28: /* show_statement: SHOW MEMORY end  */
#line 258 "sql.y"
                {
                    (yyval.show_node) = make_show_node(SHOW_MEMORY);
                }
#line 1702 "y.tab.c"
    break;

  case 29: /* select_items: columns  */
#line 264 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_COLUMNS;
                    select_items_node->column_set_node= (yyvsp[0].column_set_node);
                    (yyval.select_items_node) = select_items_node;
                }
#line 1713 "y.tab.c"
    break;

  case 30: /* select_items: function  */
#line 271 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_FUNCTION;
                    select_items_node->function_node = (yyvsp[0].function_node);
                    (yyval.select_items_node) = select_items_node;
                }
#line 1724 "y.tab.c"
    break;

  case 31: /* select_items: ALL  */
#line 278 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_ALL;
                    (yyval.select_items_node) = select_items_node;
                }
#line 1734 "y.tab.c"
    break;

  case 32: /* table: IDENTIFIER  */
#line 286 "sql.y"
                {
                    (yyval.s_value) = (yyvsp[0].s_value);
                }
#line 1742 "y.tab.c"
    break;

  case 33: /* columns: column  */
#line 292 "sql.y"
                {
                    ColumnSetNode *column_set_node = make_column_set_node();
                    add_column_to_set(column_set_node, (yyvsp[0].column_node));
                    (yyval.column_set_node) = column_set_node;
                }
#line 1752 "y.tab.c"
    break;

  case 34: /* columns: columns COMMA column  */
#line 298 "sql.y"
                {
                    (yyval.column_set_node) = (yyvsp[-2].column_set_node);
                    add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
                }
#line 1761 "y.tab.c"
    break;

  case 35: /* column_defs: column_def  */
#line 305 "sql.y"
                {
                    ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
                    add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
                    (yyval.column_def_set_node) = column_def_set_node;
                }
#line 1771 "y.tab.c"
    break;

  case 36: /* column_defs: column_defs COMMA column_def  */
#line 311 "sql.y"
                {
                    (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
                    add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
                }
#line 1780 "y.tab.c"
    break;

  case 37: /* column_def: column data_type  */
#line 318 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-1].column_node);
                    column_def_node->data_type = (yyvsp[0].data_type);
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = false;
                    column_def_node->is_define_len = false;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1794 "y.tab.c"
    break;

  case 38: /* column_def: column STRING LEFTPAREN INTVALUE RIGHTPAREN  */
#line 328 "sql.y"
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
#line 1809 "y.tab.c"
    break;

  case 39: /* column_def: column table  */
#line 339 "sql.y"
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
#line 1824 "y.tab.c"
    break;

  case 40: /* column_def: column data_type NOT NULLX  */
#line 350 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-3].column_node);
                    column_def_node->data_type = (yyvsp[-2].data_type);
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = true;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1837 "y.tab.c"
    break;

  case 41: /* data_type: INT  */
#line 360 "sql.y"
                        { (yyval.data_type) = T_INT; }
#line 1843 "y.tab.c"
    break;

  case 42: /* data_type: CHAR  */
#line 361 "sql.y"
                        { (yyval.data_type) = T_CHAR; }
#line 1849 "y.tab.c"
    break;

  case 43: /* data_type: STRING  */
#line 362 "sql.y"
                        { (yyval.data_type) = T_STRING; }
#line 1855 "y.tab.c"
    break;

  case 44: /* data_type: BOOL  */
#line 363 "sql.y"
                        { (yyval.data_type) = T_BOOL; }
#line 1861 "y.tab.c"
    break;

  case 45: /* data_type: FLOAT  */
#line 364 "sql.y"
                        { (yyval.data_type) = T_FLOAT; }
#line 1867 "y.tab.c"
    break;

  case 46: /* data_type: DOUBLE  */
#line 365 "sql.y"
                        { (yyval.data_type) = T_DOUBLE; }
#line 1873 "y.tab.c"
    break;

  case 47: /* data_type: TIMESTAMP  */
#line 366 "sql.y"
                        { (yyval.data_type) = T_TIMESTAMP; }
#line 1879 "y.tab.c"
    break;

  case 48: /* data_type: DATE  */
#line 367 "sql.y"
                        { (yyval.data_type) = T_DATE; }
#line 1885 "y.tab.c"
    break;

  case 49: /* primary_key_statement: PRIMARY KEY LEFTPAREN column RIGHTPAREN  */
#line 371 "sql.y"
                {
                    PrimaryKeyNode *primary_key_node = make_primary_key_node();
                    primary_key_node->column = (yyvsp[-1].column_node);
                    (yyval.primary_key_node) = primary_key_node;
                }
#line 1895 "y.tab.c"
    break;

  case 50: /* column: IDENTIFIER  */
#line 379 "sql.y"
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = strdup((yyvsp[0].s_value));
                    column_node->has_sub_column = false;
                    (yyval.column_node) = column_node;
                }
#line 1906 "y.tab.c"
    break;

  case 51: /* column: IDENTIFIER POINT IDENTIFIER  */
#line 386 "sql.y"
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = strdup((yyvsp[-2].s_value));
                    column_node->sub_column_name = strdup((yyvsp[0].s_value));
                    column_node->has_sub_column = true;
                    (yyval.column_node) = column_node;
                }
#line 1918 "y.tab.c"
    break;

  case 52: /* value_items: value_item  */
#line 396 "sql.y"
                {
                    ValueItemSetNode *node = make_value_item_set_node();
                    add_value_item(node, (yyvsp[0].value_item_node));
                    (yyval.value_item_set_node) = node;
                }
#line 1928 "y.tab.c"
    break;

  case 53: /* value_items: value_items COMMA value_item  */
#line 402 "sql.y"
                {
                    (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
                    add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
                }
#line 1937 "y.tab.c"
    break;

  case 54: /* value_item: INTVALUE  */
#line 409 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->data_type = T_INT;
                    (yyval.value_item_node) = node;
                }
#line 1948 "y.tab.c"
    break;

  case 55: /* value_item: BOOLVALUE  */
#line 416 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->b_value = (yyvsp[0].b_value);
                    node->data_type = T_BOOL;
                    (yyval.value_item_node) = node;
                }
#line 1959 "y.tab.c"
    break;

  case 56: /* value_item: STRINGVALUE  */
#line 423 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->s_value = (yyvsp[0].s_value);
                    node->data_type = T_STRING;
                    (yyval.value_item_node) = node;
                }
#line 1970 "y.tab.c"
    break;

  case 57: /* value_item: FLOATVALUE  */
#line 430 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->f_value = (yyvsp[0].f_value);
                    node->data_type = T_FLOAT;
                    (yyval.value_item_node) = node;
                }
#line 1981 "y.tab.c"
    break;

  case 58: /* value_item: LEFTPAREN value_items RIGHTPAREN  */
#line 437 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->nest_value_item_set = (yyvsp[-1].value_item_set_node);
                    node->data_type = T_REFERENCE;
                    (yyval.value_item_node) = node;
                }
#line 1992 "y.tab.c"
    break;

  case 59: /* BOOLVALUE: TRUE  */
#line 446 "sql.y"
                {
                    (yyval.b_value) = true;
                }
#line 2000 "y.tab.c"
    break;

  case 60: /* BOOLVALUE: FALSE  */
#line 450 "sql.y"
                {
                    (yyval.b_value) = false;
                }
#line 2008 "y.tab.c"
    break;

  case 61: /* assignments: assignment  */
#line 456 "sql.y"
                {
                    AssignmentSetNode *node = make_assignment_set_node();
                    add_assignment_to_set(node, (yyvsp[0].assignment_node));
                    (yyval.assignment_set_node) = node;
                }
#line 2018 "y.tab.c"
    break;

  case 62: /* assignments: assignments COMMA assignment  */
#line 462 "sql.y"
                {
                    add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
                    (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
                }
#line 2027 "y.tab.c"
    break;

  case 63: /* assignment: column EQ value_item  */
#line 469 "sql.y"
                {
                    AssignmentNode *node = make_assignment_node();
                    node->column = (yyvsp[-2].column_node);
                    node->value = (yyvsp[0].value_item_node);
                    (yyval.assignment_node) = node;
                }
#line 2038 "y.tab.c"
    break;

  case 64: /* cond: column opr value_item  */
#line 478 "sql.y"
                {
                    ConditionNode *cond_node = make_cond_node();
                    cond_node->column = (yyvsp[-2].column_node);
                    cond_node->opr_type = (yyvsp[-1].opr_type);
                    cond_node->value = (yyvsp[0].value_item_node);
                    cond_node->type = EXEC_CONDITION;
                    (yyval.cond_node) = cond_node;
                }
#line 2051 "y.tab.c"
    break;

  case 65: /* cond: column opr value_item conn cond  */
#line 487 "sql.y"
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
#line 2066 "y.tab.c"
    break;

  case 66: /* opr: EQ  */
#line 499 "sql.y"
                    { (yyval.opr_type) = O_EQ; }
#line 2072 "y.tab.c"
    break;

  case 67: /* opr: NE  */
#line 500 "sql.y"
                    { (yyval.opr_type) = O_NE; }
#line 2078 "y.tab.c"
    break;

  case 68: /* opr: GT  */
#line 501 "sql.y"
                    { (yyval.opr_type) = O_GT; }
#line 2084 "y.tab.c"
    break;

  case 69: /* opr: GE  */
#line 502 "sql.y"
                    { (yyval.opr_type) = O_GE; }
#line 2090 "y.tab.c"
    break;

  case 70: /* opr: LT  */
#line 503 "sql.y"
                    { (yyval.opr_type) = O_LT; }
#line 2096 "y.tab.c"
    break;

  case 71: /* opr: LE  */
#line 504 "sql.y"
                    { (yyval.opr_type) = O_LE; }
#line 2102 "y.tab.c"
    break;

  case 72: /* opr: IN  */
#line 505 "sql.y"
                    { (yyval.opr_type) = O_IN; }
#line 2108 "y.tab.c"
    break;

  case 73: /* opr: LIKE  */
#line 506 "sql.y"
                    { (yyval.opr_type) = O_LIKE; }
#line 2114 "y.tab.c"
    break;

  case 74: /* conn: AND  */
#line 509 "sql.y"
                    { (yyval.conn_type) = C_AND; }
#line 2120 "y.tab.c"
    break;

  case 75: /* conn: OR  */
#line 510 "sql.y"
                    { (yyval.conn_type) = C_OR; }
#line 2126 "y.tab.c"
    break;

  case 76: /* function: MAX LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 514 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MAX;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2137 "y.tab.c"
    break;

  case 77: /* function: MIN LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 521 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MIN;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2148 "y.tab.c"
    break;

  case 78: /* function: COUNT LEFTPAREN function_value RIGHTPAREN  */
#line 528 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_COUNT;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2159 "y.tab.c"
    break;

  case 79: /* function: SUM LEFTPAREN function_value RIGHTPAREN  */
#line 535 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_SUM;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2170 "y.tab.c"
    break;

  case 80: /* function: AVG LEFTPAREN function_value RIGHTPAREN  */
#line 542 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_AVG;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2181 "y.tab.c"
    break;

  case 81: /* function_value: INTVALUE  */
#line 551 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 2192 "y.tab.c"
    break;

  case 82: /* function_value: column  */
#line 558 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = (yyvsp[0].column_node);
                    node->value_type = V_COLUMN;
                    (yyval.function_value_node) = node;
                }
#line 2203 "y.tab.c"
    break;

  case 83: /* function_value: ALL  */
#line 565 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->value_type = V_ALL;
                    (yyval.function_value_node) = node;
                }
#line 2213 "y.tab.c"
    break;

  case 84: /* non_all_function_value: INTVALUE  */
#line 573 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 2224 "y.tab.c"
    break;

  case 85: /* non_all_function_value: column  */
#line 580 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = (yyvsp[0].column_node);
                    node->value_type = V_COLUMN;
                    (yyval.function_value_node) = node;
                }
#line 2235 "y.tab.c"
    break;


#line 2239 "y.tab.c"

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

#line 591 "sql.y"

