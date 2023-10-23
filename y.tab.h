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
    STRING = 283,                  /* STRING  */
    BOOL = 284,                    /* BOOL  */
    FLOAT = 285,                   /* FLOAT  */
    DOUBLE = 286,                  /* DOUBLE  */
    DATE = 287,                    /* DATE  */
    TIMESTAMP = 288,               /* TIMESTAMP  */
    PRIMARY = 289,                 /* PRIMARY  */
    KEY = 290,                     /* KEY  */
    EQ = 291,                      /* EQ  */
    NE = 292,                      /* NE  */
    GT = 293,                      /* GT  */
    GE = 294,                      /* GE  */
    LT = 295,                      /* LT  */
    LE = 296,                      /* LE  */
    IN = 297,                      /* IN  */
    LIKE = 298,                    /* LIKE  */
    AND = 299,                     /* AND  */
    OR = 300,                      /* OR  */
    ALL = 301,                     /* ALL  */
    COMMA = 302,                   /* COMMA  */
    SEMICOLON = 303,               /* SEMICOLON  */
    QUOTE = 304,                   /* QUOTE  */
    POINT = 305,                   /* POINT  */
    LEFTPAREN = 306,               /* LEFTPAREN  */
    RIGHTPAREN = 307,              /* RIGHTPAREN  */
    IDENTIFIER = 308,              /* IDENTIFIER  */
    INTVALUE = 309,                /* INTVALUE  */
    FLOATVALUE = 310,              /* FLOATVALUE  */
    STRINGVALUE = 311              /* STRINGVALUE  */
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
#define STRING 283
#define BOOL 284
#define FLOAT 285
#define DOUBLE 286
#define DATE 287
#define TIMESTAMP 288
#define PRIMARY 289
#define KEY 290
#define EQ 291
#define NE 292
#define GT 293
#define GE 294
#define LT 295
#define LE 296
#define IN 297
#define LIKE 298
#define AND 299
#define OR 300
#define ALL 301
#define COMMA 302
#define SEMICOLON 303
#define QUOTE 304
#define POINT 305
#define LEFTPAREN 306
#define RIGHTPAREN 307
#define IDENTIFIER 308
#define INTVALUE 309
#define FLOATVALUE 310
#define STRINGVALUE 311

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
   ConditionNode            *cond_node;
   CreateTableNode          *create_table_node;
   SelectNode               *select_node;
   InsertNode               *insert_node;
   DescribeNode             *describe_node;
   ShowTablesNode           *show_table_node;

#line 206 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
