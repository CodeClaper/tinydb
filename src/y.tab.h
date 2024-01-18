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

#line 230 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (ASTNode *ast_node);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
