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
    CHAR = 284,                    /* CHAR  */
    INT = 285,                     /* INT  */
    LONG = 286,                    /* LONG  */
    STRING = 287,                  /* STRING  */
    BOOL = 288,                    /* BOOL  */
    FLOAT = 289,                   /* FLOAT  */
    DOUBLE = 290,                  /* DOUBLE  */
    DATE = 291,                    /* DATE  */
    TIMESTAMP = 292,               /* TIMESTAMP  */
    PRIMARY = 293,                 /* PRIMARY  */
    KEY = 294,                     /* KEY  */
    EQ = 295,                      /* EQ  */
    NE = 296,                      /* NE  */
    GT = 297,                      /* GT  */
    GE = 298,                      /* GE  */
    LT = 299,                      /* LT  */
    LE = 300,                      /* LE  */
    IN = 301,                      /* IN  */
    LIKE = 302,                    /* LIKE  */
    AND = 303,                     /* AND  */
    OR = 304,                      /* OR  */
    ALL = 305,                     /* ALL  */
    COMMA = 306,                   /* COMMA  */
    SEMICOLON = 307,               /* SEMICOLON  */
    QUOTE = 308,                   /* QUOTE  */
    POINT = 309,                   /* POINT  */
    LEFTPAREN = 310,               /* LEFTPAREN  */
    RIGHTPAREN = 311,              /* RIGHTPAREN  */
    SYSTEM = 312,                  /* SYSTEM  */
    CONFIG = 313,                  /* CONFIG  */
    MEMORY = 314,                  /* MEMORY  */
    IDENTIFIER = 315,              /* IDENTIFIER  */
    INTVALUE = 316,                /* INTVALUE  */
    FLOATVALUE = 317,              /* FLOATVALUE  */
    STRINGVALUE = 318              /* STRINGVALUE  */
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
#define CHAR 284
#define INT 285
#define LONG 286
#define STRING 287
#define BOOL 288
#define FLOAT 289
#define DOUBLE 290
#define DATE 291
#define TIMESTAMP 292
#define PRIMARY 293
#define KEY 294
#define EQ 295
#define NE 296
#define GT 297
#define GE 298
#define LT 299
#define LE 300
#define IN 301
#define LIKE 302
#define AND 303
#define OR 304
#define ALL 305
#define COMMA 306
#define SEMICOLON 307
#define QUOTE 308
#define POINT 309
#define LEFTPAREN 310
#define RIGHTPAREN 311
#define SYSTEM 312
#define CONFIG 313
#define MEMORY 314
#define IDENTIFIER 315
#define INTVALUE 316
#define FLOATVALUE 317
#define STRINGVALUE 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "sql.y"

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
   SelectNode               *select_node;
   InsertNode               *insert_node;
   UpdateNode               *update_node;
   DeleteNode               *delete_node;
   DescribeNode             *describe_node;
   ShowNode                 *show_node;
   ASTNode                  *ast_node;

#line 225 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (ASTNode *ast_node);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
