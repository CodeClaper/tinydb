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
    COMMA = 259,                   /* COMMA  */
    SEMICOLON = 260,               /* SEMICOLON  */
    LEFTPAREN = 261,               /* LEFTPAREN  */
    RIGHTPAREN = 262,              /* RIGHTPAREN  */
    QUOTE = 263,                   /* QUOTE  */
    CREATE = 264,                  /* CREATE  */
    SELECT = 265,                  /* SELECT  */
    INSERT = 266,                  /* INSERT  */
    UPDATE = 267,                  /* UPDATE  */
    DELETE = 268,                  /* DELETE  */
    DESCRIBE = 269,                /* DESCRIBE  */
    FROM = 270,                    /* FROM  */
    WHERE = 271,                   /* WHERE  */
    INTO = 272,                    /* INTO  */
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
    INT = 284,                     /* INT  */
    STRING = 285,                  /* STRING  */
    BOOL = 286,                    /* BOOL  */
    FLOAT = 287,                   /* FLOAT  */
    DOUBLE = 288,                  /* DOUBLE  */
    DATE = 289,                    /* DATE  */
    TIMESTAMP = 290,               /* TIMESTAMP  */
    PRIMARY = 291,                 /* PRIMARY  */
    KEY = 292,                     /* KEY  */
    EQ = 293,                      /* EQ  */
    NE = 294,                      /* NE  */
    GT = 295,                      /* GT  */
    GE = 296,                      /* GE  */
    LT = 297,                      /* LT  */
    LE = 298,                      /* LE  */
    IN = 299,                      /* IN  */
    LIKE = 300,                    /* LIKE  */
    AND = 301,                     /* AND  */
    OR = 302,                      /* OR  */
    ALL = 303,                     /* ALL  */
    IDENTIFIER = 304,              /* IDENTIFIER  */
    INTVALUE = 305,                /* INTVALUE  */
    STRINGVALUE = 306              /* STRINGVALUE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NL 258
#define COMMA 259
#define SEMICOLON 260
#define LEFTPAREN 261
#define RIGHTPAREN 262
#define QUOTE 263
#define CREATE 264
#define SELECT 265
#define INSERT 266
#define UPDATE 267
#define DELETE 268
#define DESCRIBE 269
#define FROM 270
#define WHERE 271
#define INTO 272
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
#define INT 284
#define STRING 285
#define BOOL 286
#define FLOAT 287
#define DOUBLE 288
#define DATE 289
#define TIMESTAMP 290
#define PRIMARY 291
#define KEY 292
#define EQ 293
#define NE 294
#define GT 295
#define GE 296
#define LT 297
#define LE 298
#define IN 299
#define LIKE 300
#define AND 301
#define OR 302
#define ALL 303
#define IDENTIFIER 304
#define INTVALUE 305
#define STRINGVALUE 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "sql.y"

   char                     *s_value;
   int                      i_value;
   char                     *keyword;
   IntValueNode             *int_value_node;
   BoolValueNode            *bool_value_node;
   StringValueNode          *string_value_node;
   IdentNode                *ident_node;
   IdentSetNode             *ident_set_node;
   OprNode                  *opr_node;
   ConnNode                 *conn_node;
   DataTypeNode             *data_type_node;
   ColumnDefNode            *column_def_node;
   ColumnDefSetNode         *column_def_set_node;
   SelectItemsNode          *select_items_node;
   ColumnSetNode            *column_set_node;
   ValueItemNode            *value_item_node;
   ValueItemSetNode         *value_item_set_node;
   FunctionValueNode        *function_value_node;
   FunctionNode             *function_node;
   PrimaryKeyNode           *primary_key_node;
   FromItemNode             *from_item_node;
   ConditionNode            *cond_node;
   CreateTableNode          *create_table_node;
   SelectNode               *select_node;
   InsertNode               *insert_node;
   DescribeNode             *describe_node;
   ShowTablesNode           *show_table_node;

#line 271 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NL = 3,                         /* NL  */
  YYSYMBOL_COMMA = 4,                      /* COMMA  */
  YYSYMBOL_SEMICOLON = 5,                  /* SEMICOLON  */
  YYSYMBOL_LEFTPAREN = 6,                  /* LEFTPAREN  */
  YYSYMBOL_RIGHTPAREN = 7,                 /* RIGHTPAREN  */
  YYSYMBOL_QUOTE = 8,                      /* QUOTE  */
  YYSYMBOL_CREATE = 9,                     /* CREATE  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_INSERT = 11,                    /* INSERT  */
  YYSYMBOL_UPDATE = 12,                    /* UPDATE  */
  YYSYMBOL_DELETE = 13,                    /* DELETE  */
  YYSYMBOL_DESCRIBE = 14,                  /* DESCRIBE  */
  YYSYMBOL_FROM = 15,                      /* FROM  */
  YYSYMBOL_WHERE = 16,                     /* WHERE  */
  YYSYMBOL_INTO = 17,                      /* INTO  */
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
  YYSYMBOL_INT = 29,                       /* INT  */
  YYSYMBOL_STRING = 30,                    /* STRING  */
  YYSYMBOL_BOOL = 31,                      /* BOOL  */
  YYSYMBOL_FLOAT = 32,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 33,                    /* DOUBLE  */
  YYSYMBOL_DATE = 34,                      /* DATE  */
  YYSYMBOL_TIMESTAMP = 35,                 /* TIMESTAMP  */
  YYSYMBOL_PRIMARY = 36,                   /* PRIMARY  */
  YYSYMBOL_KEY = 37,                       /* KEY  */
  YYSYMBOL_EQ = 38,                        /* EQ  */
  YYSYMBOL_NE = 39,                        /* NE  */
  YYSYMBOL_GT = 40,                        /* GT  */
  YYSYMBOL_GE = 41,                        /* GE  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_IN = 44,                        /* IN  */
  YYSYMBOL_LIKE = 45,                      /* LIKE  */
  YYSYMBOL_AND = 46,                       /* AND  */
  YYSYMBOL_OR = 47,                        /* OR  */
  YYSYMBOL_ALL = 48,                       /* ALL  */
  YYSYMBOL_IDENTIFIER = 49,                /* IDENTIFIER  */
  YYSYMBOL_INTVALUE = 50,                  /* INTVALUE  */
  YYSYMBOL_STRINGVALUE = 51,               /* STRINGVALUE  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_statements = 53,                /* statements  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_statement_create_table = 55,    /* statement_create_table  */
  YYSYMBOL_statement_select = 56,          /* statement_select  */
  YYSYMBOL_statement_insert = 57,          /* statement_insert  */
  YYSYMBOL_statement_describe = 58,        /* statement_describe  */
  YYSYMBOL_statement_show_tables = 59,     /* statement_show_tables  */
  YYSYMBOL_statement_end = 60,             /* statement_end  */
  YYSYMBOL_create = 61,                    /* create  */
  YYSYMBOL_select = 62,                    /* select  */
  YYSYMBOL_insert = 63,                    /* insert  */
  YYSYMBOL_table = 64,                     /* table  */
  YYSYMBOL_describe = 65,                  /* describe  */
  YYSYMBOL_show = 66,                      /* show  */
  YYSYMBOL_tables = 67,                    /* tables  */
  YYSYMBOL_select_items = 68,              /* select_items  */
  YYSYMBOL_columns = 69,                   /* columns  */
  YYSYMBOL_column_defs = 70,               /* column_defs  */
  YYSYMBOL_column_def = 71,                /* column_def  */
  YYSYMBOL_column_type = 72,               /* column_type  */
  YYSYMBOL_primary_key = 73,               /* primary_key  */
  YYSYMBOL_from_item = 74,                 /* from_item  */
  YYSYMBOL_value_items = 75,               /* value_items  */
  YYSYMBOL_value_item = 76,                /* value_item  */
  YYSYMBOL_BOOLVALUE = 77,                 /* BOOLVALUE  */
  YYSYMBOL_identifiers = 78,               /* identifiers  */
  YYSYMBOL_cond = 79,                      /* cond  */
  YYSYMBOL_op = 80,                        /* op  */
  YYSYMBOL_conn = 81,                      /* conn  */
  YYSYMBOL_func = 82,                      /* func  */
  YYSYMBOL_function_value = 83,            /* function_value  */
  YYSYMBOL_into = 84,                      /* into  */
  YYSYMBOL_values = 85                     /* values  */
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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   111

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    88,    88,    89,    90,    93,    97,   101,   105,   109,
     115,   123,   134,   142,   151,   159,   170,   178,   184,   185,
     188,   191,   194,   197,   200,   203,   206,   209,   216,   225,
     233,   239,   246,   256,   257,   258,   260,   269,   277,   283,
     290,   298,   305,   313,   323,   328,   335,   341,   349,   357,
     367,   388,   389,   390,   391,   392,   393,   394,   395,   398,
     399,   402,   409,   416,   423,   430,   439,   447,   455,   463,
     466
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
  "\"end of file\"", "error", "\"invalid token\"", "NL", "COMMA",
  "SEMICOLON", "LEFTPAREN", "RIGHTPAREN", "QUOTE", "CREATE", "SELECT",
  "INSERT", "UPDATE", "DELETE", "DESCRIBE", "FROM", "WHERE", "INTO",
  "VALUES", "TABLE", "SHOW", "TABLES", "MAX", "MIN", "COUNT", "SUM", "AVG",
  "TRUE", "FALSE", "INT", "STRING", "BOOL", "FLOAT", "DOUBLE", "DATE",
  "TIMESTAMP", "PRIMARY", "KEY", "EQ", "NE", "GT", "GE", "LT", "LE", "IN",
  "LIKE", "AND", "OR", "ALL", "IDENTIFIER", "INTVALUE", "STRINGVALUE",
  "$accept", "statements", "statement", "statement_create_table",
  "statement_select", "statement_insert", "statement_describe",
  "statement_show_tables", "statement_end", "create", "select", "insert",
  "table", "describe", "show", "tables", "select_items", "columns",
  "column_defs", "column_def", "column_type", "primary_key", "from_item",
  "value_items", "value_item", "BOOLVALUE", "identifiers", "cond", "op",
  "conn", "func", "function_value", "into", "values", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-99)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      24,   -99,   -99,   -99,   -99,   -99,    16,   -99,   -99,   -99,
     -99,   -99,   -99,   -11,   -20,    29,   -17,    39,   -99,   -99,
     -99,   -99,   -12,    64,    66,    69,    71,    75,   -99,   -99,
      67,    79,   -99,   -99,   -17,   -99,     9,   -99,     9,    78,
      15,    15,    15,    15,    15,   -17,    36,     1,   -99,    83,
     -99,   -99,    38,   -99,   -99,   -99,    81,    82,    84,    85,
      87,     6,   -99,    25,   -99,    89,   -99,    37,    41,   -99,
     -99,   -99,   -99,   -99,   -99,    47,   -99,    90,    79,    -7,
     -99,   -99,   -99,   -99,   -18,     9,    12,     9,    72,    20,
     -99,   -99,   -99,    54,   -99,   -99,    61,   -99,    92,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,    -7,   -99,
      94,    93,    95,    -7,     9,    96,     9,    33,    -7,   -99,
     -99,   -99,   -99,    56,   -99,   -99,   -99,    47,    55,    97,
     -99,     9,   -99,   -99
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    20,    21,    22,    24,    25,     0,     2,     5,     6,
       7,     8,     9,     0,     0,     0,     0,     0,     1,     4,
       3,    23,     0,     0,     0,     0,     0,     0,    46,    47,
       0,    27,    28,    69,     0,    37,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
      16,    17,     0,    68,    67,    66,     0,     0,     0,     0,
       0,     0,    48,     0,    70,     0,    19,     0,     0,    30,
      61,    62,    63,    64,    65,     0,    13,     0,    29,     0,
      33,    34,    35,    32,     0,     0,     0,     0,     0,     0,
      44,    45,    40,     0,    38,    41,     0,    31,     0,    10,
      51,    52,    53,    54,    55,    56,    57,    58,     0,    12,
       0,     0,     0,     0,     0,     0,     0,    49,     0,    42,
      43,    39,    14,     0,    11,    59,    60,     0,     0,     0,
      50,     0,    36,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -99,   -99,   100,   -99,   -99,   -99,   -99,   -99,   -38,   -99,
     -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,   -99,    23,
     -99,   -99,   -21,   -10,   -98,   -99,    46,   -16,   -99,   -99,
     -99,    -2,   -99,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    10,    11,    12,    50,    13,
      14,    15,    22,    16,    17,    38,    30,    77,    68,    69,
      83,    98,    36,    93,    94,    95,    31,    87,   108,   127,
      32,    56,    34,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,    89,    23,    24,    25,    26,    27,    63,    21,    48,
     117,    49,    48,    47,    49,   121,    18,    19,    96,    64,
      90,    91,    75,    76,    61,     1,     2,     3,    28,    29,
       4,    67,    35,     1,     2,     3,     5,    39,     4,    57,
      58,    59,    60,    92,     5,    84,    33,    99,    85,   109,
     100,   101,   102,   103,   104,   105,   106,   107,   113,   113,
      37,   114,   131,    53,    54,    55,    80,    81,    82,   111,
      40,   112,    41,    28,    29,    42,   122,    43,   124,   125,
     126,    44,    45,    46,    52,    62,    66,    67,    70,    71,
      64,    72,    73,   133,    74,    79,    86,    88,   115,   116,
     118,   119,   123,   120,   132,   129,    20,    97,   128,    78,
     110,   130
};

static const yytype_uint8 yycheck[] =
{
      38,     8,    22,    23,    24,    25,    26,     6,    19,     3,
     108,     5,     3,    34,     5,   113,     0,     1,    36,    18,
      27,    28,    16,    61,    45,     9,    10,    11,    48,    49,
      14,    49,    49,     9,    10,    11,    20,    49,    14,    41,
      42,    43,    44,    50,    20,     4,    17,    85,     7,    87,
      38,    39,    40,    41,    42,    43,    44,    45,     4,     4,
      21,     7,     7,    48,    49,    50,    29,    30,    31,    49,
       6,    51,     6,    48,    49,     6,   114,     6,   116,    46,
      47,     6,    15,     4,     6,    49,     3,    49,     7,     7,
      18,     7,     7,   131,     7,     6,    49,     7,    37,     7,
       6,     8,     6,     8,     7,    49,     6,    84,   118,    63,
      88,   127
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    11,    14,    20,    53,    54,    55,    56,
      57,    58,    59,    61,    62,    63,    65,    66,     0,     1,
      54,    19,    64,    22,    23,    24,    25,    26,    48,    49,
      68,    78,    82,    17,    84,    49,    74,    21,    67,    49,
       6,     6,     6,     6,     6,    15,     4,    74,     3,     5,
      60,    60,     6,    48,    49,    50,    83,    83,    83,    83,
      83,    74,    49,     6,    18,    85,     3,    49,    70,    71,
       7,     7,     7,     7,     7,    16,    60,    69,    78,     6,
      29,    30,    31,    72,     4,     7,    49,    79,     7,     8,
      27,    28,    50,    75,    76,    77,    36,    71,    73,    60,
      38,    39,    40,    41,    42,    43,    44,    45,    80,    60,
      85,    49,    51,     4,     7,    37,     7,    76,     6,     8,
       8,    76,    60,     6,    60,    46,    47,    81,    75,    49,
      79,     7,     7,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    53,    54,    54,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    59,    60,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    68,    69,
      70,    70,    71,    72,    72,    72,    73,    74,    75,    75,
      76,    76,    76,    76,    77,    77,    78,    78,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    82,    82,    82,    82,    82,    83,    83,    83,    84,
      85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     1,
       7,     9,     7,     5,     8,    11,     3,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     1,     1,     5,     1,     1,     3,
       1,     1,     3,     3,     1,     1,     1,     1,     3,     3,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     4,     1,     1,     1,     1,
       1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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
yyparse (void)
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
  case 5: /* statement: statement_create_table  */
#line 94 "sql.y"
                {
                   set_create_table_ast_node((yyvsp[0].create_table_node)); 
                }
#line 1428 "y.tab.c"
    break;

  case 6: /* statement: statement_select  */
#line 98 "sql.y"
                {
                    set_select_ast_node((yyvsp[0].select_node));
                }
#line 1436 "y.tab.c"
    break;

  case 7: /* statement: statement_insert  */
#line 102 "sql.y"
                {
                    set_insert_ast_node((yyvsp[0].insert_node));
                }
#line 1444 "y.tab.c"
    break;

  case 8: /* statement: statement_describe  */
#line 106 "sql.y"
                {
                    set_describe_ast_node((yyvsp[0].describe_node));
                }
#line 1452 "y.tab.c"
    break;

  case 9: /* statement: statement_show_tables  */
#line 110 "sql.y"
                {
                    set_show_tables_ast_node((yyvsp[0].show_table_node));
                }
#line 1460 "y.tab.c"
    break;

  case 10: /* statement_create_table: create table IDENTIFIER LEFTPAREN column_defs RIGHTPAREN statement_end  */
#line 116 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    IdentNode *node = make_ident_node((yyvsp[-4].ident_node));
                    create_table_node->table_name = node;
                    create_table_node->column_def_set_node = (yyvsp[-2].column_def_set_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1472 "y.tab.c"
    break;

  case 11: /* statement_create_table: create table IDENTIFIER LEFTPAREN column_defs COMMA primary_key RIGHTPAREN statement_end  */
#line 124 "sql.y"
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    IdentNode *node = make_ident_node((yyvsp[-6].ident_node));
                    create_table_node->table_name = node;
                    create_table_node->column_def_set_node = (yyvsp[-4].column_def_set_node);
                    create_table_node->primary_key_node = (yyvsp[-2].primary_key_node);
                    (yyval.create_table_node) = create_table_node;
                }
#line 1485 "y.tab.c"
    break;

  case 12: /* statement_select: select select_items FROM from_item WHERE cond statement_end  */
#line 135 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-5].select_items_node);
                    select_node->from_item_node = (yyvsp[-3].from_item_node);
                    select_node->condition_node = (yyvsp[-1].cond_node);
                    (yyval.select_node) = select_node;
                }
#line 1497 "y.tab.c"
    break;

  case 13: /* statement_select: select select_items FROM from_item statement_end  */
#line 143 "sql.y"
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = (yyvsp[-3].select_items_node);
                    select_node->from_item_node = (yyvsp[-1].from_item_node);
                    (yyval.select_node) = select_node;
                }
#line 1508 "y.tab.c"
    break;

  case 14: /* statement_insert: insert into from_item values LEFTPAREN value_items RIGHTPAREN statement_end  */
#line 152 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->if_ignore_columns = true;
                    node->from_item_node = (yyvsp[-5].from_item_node);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1520 "y.tab.c"
    break;

  case 15: /* statement_insert: insert into from_item LEFTPAREN columns RIGHTPAREN values LEFTPAREN value_items RIGHTPAREN statement_end  */
#line 160 "sql.y"
                {
                    InsertNode *node = make_insert_node();
                    node->if_ignore_columns = false;
                    node->from_item_node = (yyvsp[-8].from_item_node);
                    node->columns_set_node = (yyvsp[-6].column_set_node);
                    node->value_item_set_node = (yyvsp[-2].value_item_set_node);
                    (yyval.insert_node) = node;
                }
#line 1533 "y.tab.c"
    break;

  case 16: /* statement_describe: describe from_item statement_end  */
#line 171 "sql.y"
                {
                    DescribeNode *node = make_describe_node();
                    node->from_item_node = (yyvsp[-1].from_item_node);
                    (yyval.describe_node) = node;
                }
#line 1543 "y.tab.c"
    break;

  case 17: /* statement_show_tables: show tables statement_end  */
#line 179 "sql.y"
                {
                    (yyval.show_table_node) = make_show_tables_node();
                }
#line 1551 "y.tab.c"
    break;

  case 27: /* select_items: identifiers  */
#line 210 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node-> ident_set_node= (yyvsp[0].ident_set_node);
                    select_items_node->is_function_node = false;
                    (yyval.select_items_node) = select_items_node;
                }
#line 1562 "y.tab.c"
    break;

  case 28: /* select_items: func  */
#line 217 "sql.y"
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->function_node= (yyvsp[0].function_node);
                    select_items_node->is_function_node = true;
                    (yyval.select_items_node) = select_items_node;
                }
#line 1573 "y.tab.c"
    break;

  case 29: /* columns: identifiers  */
#line 226 "sql.y"
                {
                    ColumnSetNode *column_set_node = make_column_set_node();
                    column_set_node -> ident_set_node = (yyvsp[0].ident_set_node);
                    (yyval.column_set_node) = column_set_node;
                }
#line 1583 "y.tab.c"
    break;

  case 30: /* column_defs: column_def  */
#line 234 "sql.y"
                {
                    ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
                    add_column_def_to_set(column_def_set_node, (yyvsp[0].column_def_node));
                    (yyval.column_def_set_node) = column_def_set_node;
                }
#line 1593 "y.tab.c"
    break;

  case 31: /* column_defs: column_defs COMMA column_def  */
#line 240 "sql.y"
                {
                    (yyval.column_def_set_node) = (yyvsp[-2].column_def_set_node);
                    add_column_def_to_set((yyval.column_def_set_node), (yyvsp[0].column_def_node));
                }
#line 1602 "y.tab.c"
    break;

  case 32: /* column_def: IDENTIFIER column_type  */
#line 247 "sql.y"
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    IdentNode *node = make_ident_node((yyvsp[-1].ident_node));
                    column_def_node->column_name = node;
                    column_def_node->column_type = (yyvsp[0].data_type_node);
                    (yyval.column_def_node) = column_def_node;
                }
#line 1614 "y.tab.c"
    break;

  case 33: /* column_type: INT  */
#line 256 "sql.y"
                        { (yyval.data_type_node) = make_data_type_node(T_INT); }
#line 1620 "y.tab.c"
    break;

  case 34: /* column_type: STRING  */
#line 257 "sql.y"
                        { (yyval.data_type_node) = make_data_type_node(T_STRING);}
#line 1626 "y.tab.c"
    break;

  case 35: /* column_type: BOOL  */
#line 258 "sql.y"
                         { (yyval.data_type_node) = make_data_type_node(T_BOOL); }
#line 1632 "y.tab.c"
    break;

  case 36: /* primary_key: PRIMARY KEY LEFTPAREN IDENTIFIER RIGHTPAREN  */
#line 261 "sql.y"
                {
                    PrimaryKeyNode *primary_key_node = make_primary_key_node();
                    IdentNode *node = make_ident_node((yyvsp[-1].ident_node));
                    primary_key_node->primary_key_column = node;
                    (yyval.primary_key_node) = primary_key_node;
                }
#line 1643 "y.tab.c"
    break;

  case 37: /* from_item: IDENTIFIER  */
#line 270 "sql.y"
                {
                    IdentNode *node = make_ident_node((yyvsp[0].ident_node));
                    (yyval.from_item_node) = make_from_item_node();
                    (yyval.from_item_node)->table = node;
                }
#line 1653 "y.tab.c"
    break;

  case 38: /* value_items: value_item  */
#line 278 "sql.y"
                {
                    ValueItemSetNode *node = make_value_item_set_node();
                    add_value_item(node, (yyvsp[0].value_item_node));
                    (yyval.value_item_set_node) = node;
                }
#line 1663 "y.tab.c"
    break;

  case 39: /* value_items: value_items COMMA value_item  */
#line 284 "sql.y"
                {
                    (yyval.value_item_set_node) = (yyvsp[-2].value_item_set_node);
                    add_value_item((yyval.value_item_set_node), (yyvsp[0].value_item_node));
                }
#line 1672 "y.tab.c"
    break;

  case 40: /* value_item: INTVALUE  */
#line 291 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    IntValueNode *int_value_node = make_int_value_node((yyvsp[0].int_value_node));
                    node->i_value = int_value_node;
                    node->data_type = T_INT;
                    (yyval.value_item_node) = node;
                }
#line 1684 "y.tab.c"
    break;

  case 41: /* value_item: BOOLVALUE  */
#line 299 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    node->b_value = (yyvsp[0].bool_value_node);
                    node->data_type = T_BOOL;
                    (yyval.value_item_node) = node;
                }
#line 1695 "y.tab.c"
    break;

  case 42: /* value_item: QUOTE IDENTIFIER QUOTE  */
#line 306 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    StringValueNode *string_value_node = make_string_value_node((yyvsp[-1].ident_node));
                    node->s_value = string_value_node;
                    node->data_type = T_STRING;
                    (yyval.value_item_node) = node;
                }
#line 1707 "y.tab.c"
    break;

  case 43: /* value_item: QUOTE STRINGVALUE QUOTE  */
#line 314 "sql.y"
                {
                    ValueItemNode *node = make_value_item_node();
                    StringValueNode *string_value_node = make_string_value_node((yyvsp[-1].string_value_node));
                    node->s_value = string_value_node;
                    node->data_type = T_STRING;
                    (yyval.value_item_node) = node;
                }
#line 1719 "y.tab.c"
    break;

  case 44: /* BOOLVALUE: TRUE  */
#line 324 "sql.y"
                {
                    BoolValueNode *node = make_bool_value_node(true);
                    (yyval.bool_value_node) = node;
                }
#line 1728 "y.tab.c"
    break;

  case 45: /* BOOLVALUE: FALSE  */
#line 329 "sql.y"
                {
                    BoolValueNode *node = make_bool_value_node(false);
                    (yyval.bool_value_node) = node;
                }
#line 1737 "y.tab.c"
    break;

  case 46: /* identifiers: ALL  */
#line 336 "sql.y"
                { 
                    IdentSetNode *ident_set_node = make_ident_set_node();
                    ident_set_node->all_column = true;
                    (yyval.ident_set_node) = ident_set_node;
                }
#line 1747 "y.tab.c"
    break;

  case 47: /* identifiers: IDENTIFIER  */
#line 342 "sql.y"
                { 
                    IdentSetNode *ident_set_node = make_ident_set_node();
                    ident_set_node->all_column = false;
                    IdentNode *node = make_ident_node((yyvsp[0].ident_node));
                    add_ident(ident_set_node, node);
                    (yyval.ident_set_node) = ident_set_node;
                }
#line 1759 "y.tab.c"
    break;

  case 48: /* identifiers: identifiers COMMA IDENTIFIER  */
#line 350 "sql.y"
                { 
                    (yyval.ident_set_node) = (yyvsp[-2].ident_set_node);
                    IdentNode *node = make_ident_node((yyvsp[0].ident_node));
                    add_ident((yyval.ident_set_node), node);
                }
#line 1769 "y.tab.c"
    break;

  case 49: /* cond: IDENTIFIER op value_item  */
#line 358 "sql.y"
                {
                    ConditionNode *cond_node = make_cond_node();
                    IdentNode *ident_node = make_ident_node((yyvsp[-2].ident_node));
                    cond_node->column = ident_node;
                    cond_node->opr_node = (yyvsp[-1].opr_node);
                    cond_node->compare = (yyvsp[0].value_item_node);
                    cond_node->type = EXEC_CONDITION;
                    (yyval.cond_node) = cond_node;
                }
#line 1783 "y.tab.c"
    break;

  case 50: /* cond: IDENTIFIER op value_item conn cond  */
#line 368 "sql.y"
                {
                    ConditionNode *cond_node = make_cond_node();
                    IdentNode *ident_node = make_ident_node((yyvsp[-4].ident_node));
                    cond_node->column = ident_node;
                    cond_node->opr_node = (yyvsp[-3].opr_node);
                    cond_node->compare = (yyvsp[-2].value_item_node);
                    cond_node->conn_node = (yyvsp[-1].conn_node);
                    cond_node->next = (yyvsp[0].cond_node);
                    cond_node->type = EXEC_CONDITION;
                    (yyval.cond_node) = cond_node;
                }
#line 1799 "y.tab.c"
    break;

  case 51: /* op: EQ  */
#line 388 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_EQ); }
#line 1805 "y.tab.c"
    break;

  case 52: /* op: NE  */
#line 389 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_NE); }
#line 1811 "y.tab.c"
    break;

  case 53: /* op: GT  */
#line 390 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_GT); }
#line 1817 "y.tab.c"
    break;

  case 54: /* op: GE  */
#line 391 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_GE); }
#line 1823 "y.tab.c"
    break;

  case 55: /* op: LT  */
#line 392 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_LT); }
#line 1829 "y.tab.c"
    break;

  case 56: /* op: LE  */
#line 393 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_LE); }
#line 1835 "y.tab.c"
    break;

  case 57: /* op: IN  */
#line 394 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_IN); }
#line 1841 "y.tab.c"
    break;

  case 58: /* op: LIKE  */
#line 395 "sql.y"
                    { (yyval.opr_node) = make_opr_node(O_LIKE); }
#line 1847 "y.tab.c"
    break;

  case 59: /* conn: AND  */
#line 398 "sql.y"
                    { (yyval.conn_node) = make_conn_node(C_AND); }
#line 1853 "y.tab.c"
    break;

  case 60: /* conn: OR  */
#line 399 "sql.y"
                    { (yyval.conn_node) = make_conn_node(C_OR); }
#line 1859 "y.tab.c"
    break;

  case 61: /* func: MAX LEFTPAREN function_value RIGHTPAREN  */
#line 403 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MAX;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 1870 "y.tab.c"
    break;

  case 62: /* func: MIN LEFTPAREN function_value RIGHTPAREN  */
#line 410 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MIN;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 1881 "y.tab.c"
    break;

  case 63: /* func: COUNT LEFTPAREN function_value RIGHTPAREN  */
#line 417 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_COUNT;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 1892 "y.tab.c"
    break;

  case 64: /* func: SUM LEFTPAREN function_value RIGHTPAREN  */
#line 424 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_SUM;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 1903 "y.tab.c"
    break;

  case 65: /* func: AVG LEFTPAREN function_value RIGHTPAREN  */
#line 431 "sql.y"
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_AVG;
                    function_node->value = (yyvsp[-1].function_value_node);
                    (yyval.function_node) = function_node;
                }
#line 1914 "y.tab.c"
    break;

  case 66: /* function_value: INTVALUE  */
#line 440 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    IntValueNode *int_value_node = make_int_value_node((yyvsp[0].int_value_node));
                    node->i_value = int_value_node;
                    node->value_type = V_INT;
                    (yyval.function_value_node) = node;
                }
#line 1926 "y.tab.c"
    break;

  case 67: /* function_value: IDENTIFIER  */
#line 448 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    IdentNode *ident_node = make_ident_node((yyvsp[0].ident_node));
                    node->id_value = ident_node;
                    node->value_type = V_IDENT;
                    (yyval.function_value_node) = node;
                }
#line 1938 "y.tab.c"
    break;

  case 68: /* function_value: ALL  */
#line 456 "sql.y"
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->value_type = V_ALL;
                    (yyval.function_value_node) = node;
                }
#line 1948 "y.tab.c"
    break;


#line 1952 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 468 "sql.y"

