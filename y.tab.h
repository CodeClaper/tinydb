/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
    IDENTIFIER = 309,              /* IDENTIFIER  */
    INTVALUE = 310,                /* INTVALUE  */
    FLOATVALUE = 311,              /* FLOATVALUE  */
    STRINGVALUE = 312              /* STRINGVALUE  */
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
#define IDENTIFIER 309
#define INTVALUE 310
#define FLOATVALUE 311
#define STRINGVALUE 312

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "sql.y"

   char                     *s_value;
   int                      i_value;
   float                    f_value;
   bool                     b_value;
   char                     c_value;
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
   ConditionNode            *cond_node;
   CreateTableNode          *create_table_node;
   SelectNode               *select_node;
   InsertNode               *insert_node;
   DescribeNode             *describe_node;
   ShowTablesNode           *show_table_node;

#line 209 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
