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
    CREATE = 259,                  /* CREATE  */
    SELECT = 260,                  /* SELECT  */
    INSERT = 261,                  /* INSERT  */
    UPDATE = 262,                  /* UPDATE  */
    DELETE = 263,                  /* DELETE  */
    DESCRIBE = 264,                /* DESCRIBE  */
    FROM = 265,                    /* FROM  */
    WHERE = 266,                   /* WHERE  */
    INTO = 267,                    /* INTO  */
    SET = 268,                     /* SET  */
    VALUES = 269,                  /* VALUES  */
    TABLE = 270,                   /* TABLE  */
    SHOW = 271,                    /* SHOW  */
    TABLES = 272,                  /* TABLES  */
    MAX = 273,                     /* MAX  */
    MIN = 274,                     /* MIN  */
    COUNT = 275,                   /* COUNT  */
    SUM = 276,                     /* SUM  */
    AVG = 277,                     /* AVG  */
    TRUE = 278,                    /* TRUE  */
    FALSE = 279,                   /* FALSE  */
    NOT = 280,                     /* NOT  */
    NULLX = 281,                   /* NULLX  */
    INT = 282,                     /* INT  */
    CHAR = 283,                    /* CHAR  */
    STRING = 284,                  /* STRING  */
    BOOL = 285,                    /* BOOL  */
    FLOAT = 286,                   /* FLOAT  */
    DOUBLE = 287,                  /* DOUBLE  */
    DATE = 288,                    /* DATE  */
    TIMESTAMP = 289,               /* TIMESTAMP  */
    PRIMARY = 290,                 /* PRIMARY  */
    KEY = 291,                     /* KEY  */
    EQ = 292,                      /* EQ  */
    NE = 293,                      /* NE  */
    GT = 294,                      /* GT  */
    GE = 295,                      /* GE  */
    LT = 296,                      /* LT  */
    LE = 297,                      /* LE  */
    IN = 298,                      /* IN  */
    LIKE = 299,                    /* LIKE  */
    AND = 300,                     /* AND  */
    OR = 301,                      /* OR  */
    ALL = 302,                     /* ALL  */
    COMMA = 303,                   /* COMMA  */
    SEMICOLON = 304,               /* SEMICOLON  */
    QUOTE = 305,                   /* QUOTE  */
    POINT = 306,                   /* POINT  */
    LEFTPAREN = 307,               /* LEFTPAREN  */
    RIGHTPAREN = 308,              /* RIGHTPAREN  */
    SYSTEM = 309,                  /* SYSTEM  */
    CONFIG = 310,                  /* CONFIG  */
    MEMORY = 311,                  /* MEMORY  */
    IDENTIFIER = 312,              /* IDENTIFIER  */
    INTVALUE = 313,                /* INTVALUE  */
    FLOATVALUE = 314,              /* FLOATVALUE  */
    STRINGVALUE = 315              /* STRINGVALUE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NL 258
#define CREATE 259
#define SELECT 260
#define INSERT 261
#define UPDATE 262
#define DELETE 263
#define DESCRIBE 264
#define FROM 265
#define WHERE 266
#define INTO 267
#define SET 268
#define VALUES 269
#define TABLE 270
#define SHOW 271
#define TABLES 272
#define MAX 273
#define MIN 274
#define COUNT 275
#define SUM 276
#define AVG 277
#define TRUE 278
#define FALSE 279
#define NOT 280
#define NULLX 281
#define INT 282
#define CHAR 283
#define STRING 284
#define BOOL 285
#define FLOAT 286
#define DOUBLE 287
#define DATE 288
#define TIMESTAMP 289
#define PRIMARY 290
#define KEY 291
#define EQ 292
#define NE 293
#define GT 294
#define GE 295
#define LT 296
#define LE 297
#define IN 298
#define LIKE 299
#define AND 300
#define OR 301
#define ALL 302
#define COMMA 303
#define SEMICOLON 304
#define QUOTE 305
#define POINT 306
#define LEFTPAREN 307
#define RIGHTPAREN 308
#define SYSTEM 309
#define CONFIG 310
#define MEMORY 311
#define IDENTIFIER 312
#define INTVALUE 313
#define FLOATVALUE 314
#define STRINGVALUE 315

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

#line 290 "y.tab.c"

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
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_SELECT = 5,                     /* SELECT  */
  YYSYMBOL_INSERT = 6,                     /* INSERT  */
  YYSYMBOL_UPDATE = 7,                     /* UPDATE  */
  YYSYMBOL_DELETE = 8,                     /* DELETE  */
  YYSYMBOL_DESCRIBE = 9,                   /* DESCRIBE  */
  YYSYMBOL_FROM = 10,                      /* FROM  */
  YYSYMBOL_WHERE = 11,                     /* WHERE  */
  YYSYMBOL_INTO = 12,                      /* INTO  */
  YYSYMBOL_SET = 13,                       /* SET  */
  YYSYMBOL_VALUES = 14,                    /* VALUES  */
  YYSYMBOL_TABLE = 15,                     /* TABLE  */
  YYSYMBOL_SHOW = 16,                      /* SHOW  */
  YYSYMBOL_TABLES = 17,                    /* TABLES  */
  YYSYMBOL_MAX = 18,                       /* MAX  */
  YYSYMBOL_MIN = 19,                       /* MIN  */
  YYSYMBOL_COUNT = 20,                     /* COUNT  */
  YYSYMBOL_SUM = 21,                       /* SUM  */
  YYSYMBOL_AVG = 22,                       /* AVG  */
  YYSYMBOL_TRUE = 23,                      /* TRUE  */
  YYSYMBOL_FALSE = 24,                     /* FALSE  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_NULLX = 26,                     /* NULLX  */
  YYSYMBOL_INT = 27,                       /* INT  */
  YYSYMBOL_CHAR = 28,                      /* CHAR  */
  YYSYMBOL_STRING = 29,                    /* STRING  */
  YYSYMBOL_BOOL = 30,                      /* BOOL  */
  YYSYMBOL_FLOAT = 31,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 32,                    /* DOUBLE  */
  YYSYMBOL_DATE = 33,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 34,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 35,                   /* PRIMARY  */
  YYSYMBOL_KEY = 36,                       /* KEY  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_NE = 38,                        /* NE  */
  YYSYMBOL_GT = 39,                        /* GT  */
  YYSYMBOL_GE = 40,                        /* GE  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_IN = 43,                        /* IN  */
  YYSYMBOL_LIKE = 44,                      /* LIKE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_OR = 46,                        /* OR  */
  YYSYMBOL_ALL = 47,                       /* ALL  */
  YYSYMBOL_COMMA = 48,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 49,                 /* SEMICOLON  */
  YYSYMBOL_QUOTE = 50,                     /* QUOTE  */
  YYSYMBOL_POINT = 51,                     /* POINT  */
  YYSYMBOL_LEFTPAREN = 52,                 /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 53,                /* RIGHTPAREN  */
  YYSYMBOL_SYSTEM = 54,                    /* SYSTEM  */
  YYSYMBOL_CONFIG = 55,                    /* CONFIG  */
  YYSYMBOL_MEMORY = 56,                    /* MEMORY  */
  YYSYMBOL_IDENTIFIER = 57,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 58,                  /* INTVALUE  */
  YYSYMBOL_FLOATVALUE = 59,                /* FLOATVALUE  */
  YYSYMBOL_STRINGVALUE = 60,               /* STRINGVALUE  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_statements = 62,                /* statements  */
  YYSYMBOL_statement = 63,                 /* statement  */
  YYSYMBOL_create_table_statement = 64,    /* create_table_statement  */
  YYSYMBOL_select_statement = 65,          /* select_statement  */
  YYSYMBOL_insert_statement = 66,          /* insert_statement  */
  YYSYMBOL_update_statement = 67,          /* update_statement  */
  YYSYMBOL_delete_statement = 68,          /* delete_statement  */
  YYSYMBOL_describe_statement = 69,        /* describe_statement  */
  YYSYMBOL_show_statement = 70,            /* show_statement  */
  YYSYMBOL_select_items = 71,              /* select_items  */
  YYSYMBOL_table = 72,                     /* table  */
  YYSYMBOL_columns = 73,                   /* columns  */
  YYSYMBOL_column_defs = 74,               /* column_defs  */
  YYSYMBOL_column_def = 75,                /* column_def  */
  YYSYMBOL_data_type = 76,                 /* data_type  */
  YYSYMBOL_primary_key_statement = 77,     /* primary_key_statement  */
  YYSYMBOL_column = 78,                    /* column  */
  YYSYMBOL_value_items = 79,               /* value_items  */
  YYSYMBOL_value_item = 80,                /* value_item  */
  YYSYMBOL_BOOLVALUE = 81,                 /* BOOLVALUE  */
  YYSYMBOL_assignments = 82,               /* assignments  */
  YYSYMBOL_assignment = 83,                /* assignment  */
  YYSYMBOL_cond = 84,                      /* cond  */
  YYSYMBOL_opr = 85,                       /* opr  */
  YYSYMBOL_conn = 86,                      /* conn  */
  YYSYMBOL_function = 87,                  /* function  */
  YYSYMBOL_function_value = 88,            /* function_value  */
  YYSYMBOL_non_all_function_value = 89,    /* non_all_function_value  */
  YYSYMBOL_end = 90                        /* end  */
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
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   103,   103,   104,   105,   108,   113,   118,   123,   128,
     133,   138,   145,   152,   162,   170,   179,   187,   198,   205,
     215,   221,   230,   238,   242,   248,   255,   262,   270,   276,
     282,   289,   295,   302,   312,   323,   334,   345,   346,   347,
     348,   349,   350,   351,   352,   355,   363,   370,   380,   386,
     393,   400,   407,   414,   421,   430,   434,   440,   446,   453,
     462,   471,   484,   485,   486,   487,   488,   489,   490,   491,
     494,   495,   498,   505,   512,   519,   526,   535,   542,   549,
     557,   564,   573,   574
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
  "\"end of file\"", "error", "\"invalid token\"", "NL", "CREATE",
  "SELECT", "INSERT", "UPDATE", "DELETE", "DESCRIBE", "FROM", "WHERE",
  "INTO", "SET", "VALUES", "TABLE", "SHOW", "TABLES", "MAX", "MIN",
  "COUNT", "SUM", "AVG", "TRUE", "FALSE", "NOT", "NULLX", "INT", "CHAR",
  "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE", "TIMESTAMP", "PRIMARY",
  "KEY", "EQ", "NE", "GT", "GE", "LT", "LE", "IN", "LIKE", "AND", "OR",
  "ALL", "COMMA", "SEMICOLON", "QUOTE", "POINT", "LEFTPAREN", "RIGHTPAREN",
  "SYSTEM", "CONFIG", "MEMORY", "IDENTIFIER", "INTVALUE", "FLOATVALUE",
  "STRINGVALUE", "$accept", "statements", "statement",
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

#define YYPACT_NINF (-96)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      79,    -8,    44,     6,   -23,    57,   -23,     2,   133,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -23,    18,    28,
      29,    38,    40,   -96,    45,    87,    51,   -96,   -96,   -23,
     -96,    85,   -23,    -1,    -1,    -1,   -96,   -96,    48,    -3,
      -3,   -31,   -31,   -31,    46,   -23,    47,    -9,    47,    10,
     -96,   102,   -96,   -96,   -96,    47,   -96,   -96,    53,    54,
     -96,   -96,   -96,    58,    59,    60,   -96,    11,   -96,    62,
      47,    80,     1,   -96,    47,   -96,   -96,   -28,   -96,    94,
     -96,   -96,   -96,   -96,   -96,    47,   -96,    50,   -20,    50,
      47,    47,   -96,   117,    -1,   -34,    -1,   -96,   -96,    64,
     -96,   -96,   -96,   -96,   -96,   -96,    93,    -1,   -96,   -96,
      50,   -96,   -96,   -96,   -18,   -96,   -96,   105,   -96,    -1,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,    50,
     -96,    95,   -96,    76,   -96,    72,   106,   -96,   -17,    50,
      -1,    82,   -96,    30,    83,    -1,    90,   -96,   -96,   -96,
     -96,    50,   -96,   -96,    47,    47,   -96,   -96,     4,   -96,
      91,    -1,   -96,   -96
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
       0,     0,     0,    27,    46,     0,    25,    29,    26,     0,
      28,     0,     0,     0,     0,     0,     1,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    22,    23,    24,     0,    80,    81,     0,     0,
      79,    77,    78,     0,     0,     0,    47,     0,    30,     0,
       0,     0,     0,    57,     0,    20,    83,     0,    31,     0,
      72,    73,    74,    75,    76,     0,    15,     0,     0,     0,
       0,     0,    18,     0,     0,     0,     0,    37,    38,    39,
      40,    41,    42,    44,    43,    35,    33,     0,    55,    56,
       0,    50,    53,    52,     0,    48,    51,     0,    59,     0,
      58,    62,    63,    64,    65,    66,    67,    68,    69,     0,
      21,     0,    32,     0,    12,     0,     0,    14,     0,     0,
       0,     0,    19,    60,     0,     0,     0,    36,    54,    49,
      16,     0,    70,    71,     0,     0,    13,    34,     0,    61,
       0,     0,    45,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -96,   -96,   137,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,     0,    77,   -96,    55,   -96,   -96,    -2,   -95,   -78,
     -96,   -96,    61,   -82,   -96,   -96,   -96,    35,   108,   -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      25,    31,    26,    77,    78,   106,   133,    93,   114,   115,
     116,    72,    73,    94,   129,   154,    28,    63,    58,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      27,   131,    50,   107,    50,    69,    33,    17,   119,    53,
      54,   118,    90,    50,    50,   138,    60,    38,    29,    34,
      95,    74,    85,    24,    75,    96,    24,    61,    46,    47,
     139,   139,    49,   117,    30,   140,   148,    57,    57,    62,
      62,    62,    86,    70,    68,    67,    71,    92,    51,    91,
      51,   143,   139,    79,    24,    56,   158,   161,    35,    51,
      51,   149,    18,    19,    20,    21,    22,    32,    27,   130,
      39,   134,   159,   108,   109,   152,   153,    64,    65,   105,
      40,    41,   137,     1,     2,     3,     4,     5,     6,    71,
      42,    23,    43,    79,   142,     7,    44,    45,    48,    46,
      55,    24,   110,    66,    24,    76,    80,    81,   111,   112,
     113,    82,    83,    84,    87,   150,   135,    89,   136,   141,
     156,    97,    98,    99,   100,   101,   102,   103,   104,   145,
     146,   144,   147,    36,   151,   155,   163,     1,     2,     3,
       4,     5,     6,   157,   162,    37,     0,    88,    59,     7,
     132,    30,   120,   160,   121,   122,   123,   124,   125,   126,
     127,   128
};

static const yytype_int16 yycheck[] =
{
       2,    35,     3,    85,     3,    14,     6,    15,    90,    34,
      35,    89,    11,     3,     3,   110,    47,    17,    12,    17,
      48,    11,    11,    57,    49,    53,    57,    58,    48,    29,
      48,    48,    32,    53,    57,    53,    53,    39,    40,    41,
      42,    43,    67,    52,    46,    45,    48,    72,    49,    48,
      49,   129,    48,    55,    57,    58,   151,    53,    56,    49,
      49,   139,    18,    19,    20,    21,    22,    10,    70,    94,
      52,    96,   154,    23,    24,    45,    46,    42,    43,    79,
      52,    52,   107,     4,     5,     6,     7,     8,     9,    91,
      52,    47,    52,    95,   119,    16,    51,    10,    13,    48,
      52,    57,    52,    57,    57,     3,    53,    53,    58,    59,
      60,    53,    53,    53,    52,   140,    52,    37,    25,    14,
     145,    27,    28,    29,    30,    31,    32,    33,    34,    53,
      58,    36,    26,     0,    52,    52,   161,     4,     5,     6,
       7,     8,     9,    53,    53,     8,    -1,    70,    40,    16,
      95,    57,    91,   155,    37,    38,    39,    40,    41,    42,
      43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    16,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    15,    18,    19,
      20,    21,    22,    47,    57,    71,    73,    78,    87,    12,
      57,    72,    10,    72,    17,    56,     0,    63,    72,    52,
      52,    52,    52,    52,    51,    10,    48,    72,    13,    72,
       3,    49,    90,    90,    90,    52,    58,    78,    89,    89,
      47,    58,    78,    88,    88,    88,    57,    72,    78,    14,
      52,    78,    82,    83,    11,    90,     3,    74,    75,    78,
      53,    53,    53,    53,    53,    11,    90,    52,    73,    37,
      11,    48,    90,    78,    84,    48,    53,    27,    28,    29,
      30,    31,    32,    33,    34,    72,    76,    84,    23,    24,
      52,    58,    59,    60,    79,    80,    81,    53,    80,    84,
      83,    37,    38,    39,    40,    41,    42,    43,    44,    85,
      90,    35,    75,    77,    90,    52,    25,    90,    79,    48,
      53,    14,    90,    80,    36,    53,    58,    26,    53,    80,
      90,    52,    45,    46,    86,    52,    90,    53,    79,    84,
      78,    53,    53,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      68,    68,    69,    70,    70,    71,    71,    71,    72,    73,
      73,    74,    74,    75,    75,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    78,    78,    79,    79,
      80,    80,    80,    80,    80,    81,    81,    82,    82,    83,
      84,    84,    85,    85,    85,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    87,    87,    87,    88,    88,    88,
      89,    89,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     7,     9,     7,     5,     8,    11,     5,     7,
       4,     6,     3,     3,     3,     1,     1,     1,     1,     1,
       3,     1,     3,     2,     5,     2,     4,     1,     1,     1,
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
  case 5: /* statement: create_table_statement  */
#line 109 "sql.y"
                {
                    ast_node->statement_type = CREATE_TABLE_STMT;
                    ast_node->create_table_node = (yyvsp[0].create_table_node);
                }
#line 1478 "y.tab.c"
    break;

  case 6: /* statement: select_statement  */
#line 114 "sql.y"
                {
                    ast_node->statement_type = SELECT_STMT;
                    ast_node->select_node = (yyvsp[0].select_node);
                }
#line 1487 "y.tab.c"
    break;

  case 7: /* statement: insert_statement  */
#line 119 "sql.y"
                {
                    ast_node->statement_type = INSERT_STMT;
                    ast_node->insert_node = (yyvsp[0].insert_node);
                }
#line 1496 "y.tab.c"
    break;

  case 8: /* statement: update_statement  */
#line 124 "sql.y"
                {
                    ast_node->statement_type = UPDATE_STMT;
                    ast_node->update_node = (yyvsp[0].update_node);
                }
#line 1505 "y.tab.c"
    break;

  case 9: /* statement: delete_statement  */
#line 129 "sql.y"
                {
                    ast_node->statement_type = DELETE_STMT;
                    ast_node->delete_node = (yyvsp[0].delete_node);
                }
#line 1514 "y.tab.c"
    break;

  case 10: /* statement: describe_statement  */
#line 134 "sql.y"
                {
                    ast_node->statement_type = DESCRIBE_STMT;
                    ast_node->describe_node = (yyvsp[0].describe_node);
                }
#line 1523 "y.tab.c"
    break;

  case 11: /* statement: show_statement  */
#line 139 "sql.y"
                {
                    ast_node->statement_type = SHOW_STMT;
                    ast_node->show_node = (yyvsp[0].show_node);
                }
#line 1532 "y.tab.c"
    break;

  case 12: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs RIGHTPAREN end  */
#line 146 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = (yyvsp[-4].s_value);
                    create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1543 "y.tab.c"
    break;

  case 13: /* create_table_statement: CREATE TABLE table LEFTPAREN column_defs COMMA primary_key_statement RIGHTPAREN end  */
#line 153 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = (yyvsp[-6].s_value);
                    create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
                    create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1555 "y.tab.c"
    break;

  case 14: /* select_statement: SELECT select_items FROM table WHERE cond end  */
#line 163 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-5].select_items_node);
                    select_node->table_name = (yyvsp[-3].s_value);
                    select_node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.select_node) = select_node;
                }
#line 1567 "y.tab.c"
    break;

  case 15: /* select_statement: SELECT select_items FROM table end  */
#line 171 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-3].select_items_node);
                    select_node->table_name = (yyvsp[-1].s_value);
                    (yyval.select_node) = select_node;
                }
#line 1578 "y.tab.c"
    break;

  case 16: /* insert_statement: INSERT INTO table VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 180 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = true;
                    node->table_name = (yyvsp[-5].s_value);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1590 "y.tab.c"
    break;

  case 17: /* insert_statement: INSERT INTO table LEFTPAREN columns RIGHTPAREN VALUES LEFTPAREN value_items RIGHTPAREN end  */
#line 188 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = false;
                    node->table_name = (yyvsp[-8].s_value);
                    node->columns_set_node = (yyvsp[-6].column_set_node);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1603 "y.tab.c"
    break;

  case 18: /* update_statement: UPDATE table SET assignments end  */
#line 199 "sql.y"
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = (yyvsp[-3].s_value);
                    node->assignment_set_node = (yyvsp[-1].assignment_set_node);
                    (yyval.update_node) = node;
                }
#line 1614 "y.tab.c"
    break;

  case 19: /* update_statement: UPDATE table SET assignments WHERE cond end  */
#line 206 "sql.y"
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = (yyvsp[-5].s_value);
                    node->assignment_set_node = (yyvsp[-3].assignment_set_node);
                    node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.update_node) = node;
                }
#line 1626 "y.tab.c"
    break;

  case 20: /* delete_statement: DELETE FROM table end  */
#line 216 "sql.y"
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = (yyvsp[-1].s_value);
                    (yyval.delete_node) = node;
                }
#line 1636 "y.tab.c"
    break;

  case 21: /* delete_statement: DELETE FROM table WHERE cond end  */
#line 222 "sql.y"
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = (yyvsp[-3].s_value);
                    node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.delete_node) = node;
                }
#line 1647 "y.tab.c"
    break;

  case 22: /* describe_statement: DESCRIBE table end  */
#line 231 "sql.y"
                {
                    DescribeNode *node = make_describe_node();
                    node->table_name = strdup((yyvsp[-1].s_value));
                    (yyval.describe_node) = node;
                }
#line 1657 "y.tab.c"
    break;

  case 23: /* show_statement: SHOW TABLES end  */
#line 239 "sql.y"
                {
                    (yyval.show_node) = make_show_node(SHOW_TABLES);
                }
#line 1665 "y.tab.c"
    break;

  case 24: /* show_statement: SHOW MEMORY end  */
#line 243 "sql.y"
                {
                    (yyval.show_node) = make_show_node(SHOW_MEMORY);
                }
#line 1673 "y.tab.c"
    break;

  case 25: /* select_items: columns  */
#line 249 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_COLUMNS;
                    select_items_node->column_set_node= (yyvsp[0].column_set_node);
                    (yyval.select_items_node) = select_items_node;
                }
#line 1684 "y.tab.c"
    break;

  case 26: /* select_items: function  */
#line 256 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_FUNCTION;
                    select_items_node->function_node = (yyvsp[0].function_node);
                    (yyval.select_items_node) = select_items_node;
                }
#line 1695 "y.tab.c"
    break;

  case 27: /* select_items: ALL  */
#line 263 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_ALL;
                    (yyval.select_items_node) = select_items_node;
                }
#line 1705 "y.tab.c"
    break;

  case 28: /* table: IDENTIFIER  */
#line 271 "sql.y"
                {
                    (yyval.s_value) = (yyvsp[0].s_value);
                }
#line 1713 "y.tab.c"
    break;

  case 29: /* columns: column  */
#line 277 "sql.y"
                {
                    ColumnSetNode *column_set_node = make_column_set_node();
                    add_column_to_set(column_set_node, (yyvsp[0].column_node));
                    (yyval.column_set_node) = column_set_node;
                }
#line 1723 "y.tab.c"
    break;

  case 30: /* columns: columns COMMA column  */
#line 283 "sql.y"
                {
                    (yyval.column_set_node) = (yyvsp[-2].column_set_node);
                    add_column_to_set((yyval.column_set_node), (yyvsp[0].column_node));
                }
#line 1732 "y.tab.c"
    break;

  case 31: /* column_defs: column_def  */
#line 290 "sql.y"
                {
                    ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
                    add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
                    (yyval.column_def_set_node) = column_def_set_node;
                }
#line 1742 "y.tab.c"
    break;

  case 32: /* column_defs: column_defs COMMA column_def  */
#line 296 "sql.y"
                {
                    (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
                    add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
                }
#line 1751 "y.tab.c"
    break;

  case 33: /* column_def: column data_type  */
#line 303 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-1].column_node);
                    column_def_node->data_type = (yyvsp[0].data_type);
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = false;
                    column_def_node->is_define_len = false;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1765 "y.tab.c"
    break;

  case 34: /* column_def: column STRING LEFTPAREN INTVALUE RIGHTPAREN  */
#line 313 "sql.y"
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
#line 1780 "y.tab.c"
    break;

  case 35: /* column_def: column table  */
#line 324 "sql.y"
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
#line 1795 "y.tab.c"
    break;

  case 36: /* column_def: column data_type NOT NULLX  */
#line 335 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = (yyvsp[-3].column_node);
                    column_def_node->data_type = (yyvsp[-2].data_type);
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = true;
                    (yyval.column_def_node) = column_def_node;
                }
#line 1808 "y.tab.c"
    break;

  case 37: /* data_type: INT  */
#line 345 "sql.y"
                        { (yyval.data_type) = T_INT; }
#line 1814 "y.tab.c"
    break;

  case 38: /* data_type: CHAR  */
#line 346 "sql.y"
                        { (yyval.data_type) = T_CHAR; }
#line 1820 "y.tab.c"
    break;

  case 39: /* data_type: STRING  */
#line 347 "sql.y"
                        { (yyval.data_type) = T_STRING; }
#line 1826 "y.tab.c"
    break;

  case 40: /* data_type: BOOL  */
#line 348 "sql.y"
                        { (yyval.data_type) = T_BOOL; }
#line 1832 "y.tab.c"
    break;

  case 41: /* data_type: FLOAT  */
#line 349 "sql.y"
                        { (yyval.data_type) = T_FLOAT; }
#line 1838 "y.tab.c"
    break;

  case 42: /* data_type: DOUBLE  */
#line 350 "sql.y"
                        { (yyval.data_type) = T_DOUBLE; }
#line 1844 "y.tab.c"
    break;

  case 43: /* data_type: TIMESTAMP  */
#line 351 "sql.y"
                        { (yyval.data_type) = T_TIMESTAMP; }
#line 1850 "y.tab.c"
    break;

  case 44: /* data_type: DATE  */
#line 352 "sql.y"
                        { (yyval.data_type) = T_DATE; }
#line 1856 "y.tab.c"
    break;

  case 45: /* primary_key_statement: PRIMARY KEY LEFTPAREN column RIGHTPAREN  */
#line 356 "sql.y"
                {
                    PrimaryKeyNode *primary_key_node = make_primary_key_node();
                    primary_key_node->column = (yyvsp[-1].column_node);
                    (yyval.primary_key_node) = primary_key_node;
                }
#line 1866 "y.tab.c"
    break;

  case 46: /* column: IDENTIFIER  */
#line 364 "sql.y"
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = strdup((yyvsp[0].s_value));
                    column_node->has_sub_column = false;
                    (yyval.column_node) = column_node;
                }
#line 1877 "y.tab.c"
    break;

  case 47: /* column: IDENTIFIER POINT IDENTIFIER  */
#line 371 "sql.y"
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = strdup((yyvsp[-2].s_value));
                    column_node->sub_column_name = strdup((yyvsp[0].s_value));
                    column_node->has_sub_column = true;
                    (yyval.column_node) = column_node;
                }
#line 1889 "y.tab.c"
    break;

  case 48: /* value_items: value_item  */
#line 381 "sql.y"
                {
                    ValueItemSetNode *node = make_value_item_set_node();
                    add_value_item(node, (yyvsp[0].value_item_node));
                    (yyval.value_item_set_node) = node;
                }
#line 1899 "y.tab.c"
    break;

  case 49: /* value_items: value_items COMMA value_item  */
#line 387 "sql.y"
                {
                    (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
                    add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
                }
#line 1908 "y.tab.c"
    break;

  case 50: /* value_item: INTVALUE  */
#line 394 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->data_type = T_INT;
                    (yyval.value_item_node) = node;
                }
#line 1919 "y.tab.c"
    break;

  case 51: /* value_item: BOOLVALUE  */
#line 401 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->b_value = (yyvsp[0].b_value);
                    node->data_type = T_BOOL;
                    (yyval.value_item_node) = node;
                }
#line 1930 "y.tab.c"
    break;

  case 52: /* value_item: STRINGVALUE  */
#line 408 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->s_value = (yyvsp[0].s_value);
                    node->data_type = T_STRING;
                    (yyval.value_item_node) = node;
                }
#line 1941 "y.tab.c"
    break;

  case 53: /* value_item: FLOATVALUE  */
#line 415 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->f_value = (yyvsp[0].f_value);
                    node->data_type = T_FLOAT;
                    (yyval.value_item_node) = node;
                }
#line 1952 "y.tab.c"
    break;

  case 54: /* value_item: LEFTPAREN value_items RIGHTPAREN  */
#line 422 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->nest_value_item_set = (yyvsp[-1].value_item_set_node);
                    node->data_type = T_REFERENCE;
                    (yyval.value_item_node) = node;
                }
#line 1963 "y.tab.c"
    break;

  case 55: /* BOOLVALUE: TRUE  */
#line 431 "sql.y"
                {
                    (yyval.b_value) = true;
                }
#line 1971 "y.tab.c"
    break;

  case 56: /* BOOLVALUE: FALSE  */
#line 435 "sql.y"
                {
                    (yyval.b_value) = false;
                }
#line 1979 "y.tab.c"
    break;

  case 57: /* assignments: assignment  */
#line 441 "sql.y"
                {
                    AssignmentSetNode *node = make_assignment_set_node();
                    add_assignment_to_set(node, (yyvsp[0].assignment_node));
                    (yyval.assignment_set_node) = node;
                }
#line 1989 "y.tab.c"
    break;

  case 58: /* assignments: assignments COMMA assignment  */
#line 447 "sql.y"
                {
                    add_assignment_to_set((yyvsp[-2].assignment_set_node), (yyvsp[0].assignment_node));
                    (yyval.assignment_set_node) = (yyvsp[-2].assignment_set_node);
                }
#line 1998 "y.tab.c"
    break;

  case 59: /* assignment: column EQ value_item  */
#line 454 "sql.y"
                {
                    AssignmentNode *node = make_assignment_node();
                    node->column = (yyvsp[-2].column_node);
                    node->value = (yyvsp[0].value_item_node);
                    (yyval.assignment_node) = node;
                }
#line 2009 "y.tab.c"
    break;

  case 60: /* cond: column opr value_item  */
#line 463 "sql.y"
                {
                    ConditionNode *cond_node = make_cond_node();
                    cond_node->column = (yyvsp[-2].column_node);
                    cond_node->opr_type = (yyvsp[-1].opr_type);
                    cond_node->value = (yyvsp[0].value_item_node);
                    cond_node->type = EXEC_CONDITION;
                    (yyval.cond_node) = cond_node;
                }
#line 2022 "y.tab.c"
    break;

  case 61: /* cond: column opr value_item conn cond  */
#line 472 "sql.y"
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
#line 2037 "y.tab.c"
    break;

  case 62: /* opr: EQ  */
#line 484 "sql.y"
                    { (yyval.opr_type) = O_EQ; }
#line 2043 "y.tab.c"
    break;

  case 63: /* opr: NE  */
#line 485 "sql.y"
                    { (yyval.opr_type) = O_NE; }
#line 2049 "y.tab.c"
    break;

  case 64: /* opr: GT  */
#line 486 "sql.y"
                    { (yyval.opr_type) = O_GT; }
#line 2055 "y.tab.c"
    break;

  case 65: /* opr: GE  */
#line 487 "sql.y"
                    { (yyval.opr_type) = O_GE; }
#line 2061 "y.tab.c"
    break;

  case 66: /* opr: LT  */
#line 488 "sql.y"
                    { (yyval.opr_type) = O_LT; }
#line 2067 "y.tab.c"
    break;

  case 67: /* opr: LE  */
#line 489 "sql.y"
                    { (yyval.opr_type) = O_LE; }
#line 2073 "y.tab.c"
    break;

  case 68: /* opr: IN  */
#line 490 "sql.y"
                    { (yyval.opr_type) = O_IN; }
#line 2079 "y.tab.c"
    break;

  case 69: /* opr: LIKE  */
#line 491 "sql.y"
                    { (yyval.opr_type) = O_LIKE; }
#line 2085 "y.tab.c"
    break;

  case 70: /* conn: AND  */
#line 494 "sql.y"
                    { (yyval.conn_type) = C_AND; }
#line 2091 "y.tab.c"
    break;

  case 71: /* conn: OR  */
#line 495 "sql.y"
                    { (yyval.conn_type) = C_OR; }
#line 2097 "y.tab.c"
    break;

  case 72: /* function: MAX LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 499 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MAX;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2108 "y.tab.c"
    break;

  case 73: /* function: MIN LEFTPAREN non_all_function_value RIGHTPAREN  */
#line 506 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MIN;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2119 "y.tab.c"
    break;

  case 74: /* function: COUNT LEFTPAREN function_value RIGHTPAREN  */
#line 513 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_COUNT;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2130 "y.tab.c"
    break;

  case 75: /* function: SUM LEFTPAREN function_value RIGHTPAREN  */
#line 520 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_SUM;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2141 "y.tab.c"
    break;

  case 76: /* function: AVG LEFTPAREN function_value RIGHTPAREN  */
#line 527 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_AVG;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 2152 "y.tab.c"
    break;

  case 77: /* function_value: INTVALUE  */
#line 536 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 2163 "y.tab.c"
    break;

  case 78: /* function_value: column  */
#line 543 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = (yyvsp[0].column_node);
                    node->value_type = V_COLUMN;
                    (yyval.function_value_node) = node;
                }
#line 2174 "y.tab.c"
    break;

  case 79: /* function_value: ALL  */
#line 550 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->value_type = V_ALL;
                    (yyval.function_value_node) = node;
                }
#line 2184 "y.tab.c"
    break;

  case 80: /* non_all_function_value: INTVALUE  */
#line 558 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = (yyvsp[0].i_value);
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 2195 "y.tab.c"
    break;

  case 81: /* non_all_function_value: column  */
#line 565 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = (yyvsp[0].column_node);
                    node->value_type = V_COLUMN;
                    (yyval.function_value_node) = node;
                }
#line 2206 "y.tab.c"
    break;


#line 2210 "y.tab.c"

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

#line 576 "sql.y"

