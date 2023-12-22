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

#line 223 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (ASTNode *ast_node);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
