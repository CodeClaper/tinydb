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
    DROP = 262,                    /* DROP  */
    SELECT = 263,                  /* SELECT  */
    INSERT = 264,                  /* INSERT  */
    UPDATE = 265,                  /* UPDATE  */
    DELETE = 266,                  /* DELETE  */
    DESCRIBE = 267,                /* DESCRIBE  */
    FROM = 268,                    /* FROM  */
    WHERE = 269,                   /* WHERE  */
    INTO = 270,                    /* INTO  */
    SET = 271,                     /* SET  */
    VALUES = 272,                  /* VALUES  */
    TABLE = 273,                   /* TABLE  */
    SHOW = 274,                    /* SHOW  */
    TABLES = 275,                  /* TABLES  */
    MAX = 276,                     /* MAX  */
    MIN = 277,                     /* MIN  */
    COUNT = 278,                   /* COUNT  */
    SUM = 279,                     /* SUM  */
    AVG = 280,                     /* AVG  */
    TRUE = 281,                    /* TRUE  */
    FALSE = 282,                   /* FALSE  */
    NOT = 283,                     /* NOT  */
    NULLX = 284,                   /* NULLX  */
    CHAR = 285,                    /* CHAR  */
    INT = 286,                     /* INT  */
    LONG = 287,                    /* LONG  */
    STRING = 288,                  /* STRING  */
    BOOL = 289,                    /* BOOL  */
    FLOAT = 290,                   /* FLOAT  */
    DOUBLE = 291,                  /* DOUBLE  */
    DATE = 292,                    /* DATE  */
    TIMESTAMP = 293,               /* TIMESTAMP  */
    PRIMARY = 294,                 /* PRIMARY  */
    KEY = 295,                     /* KEY  */
    EQ = 296,                      /* EQ  */
    NE = 297,                      /* NE  */
    GT = 298,                      /* GT  */
    GE = 299,                      /* GE  */
    LT = 300,                      /* LT  */
    LE = 301,                      /* LE  */
    IN = 302,                      /* IN  */
    LIKE = 303,                    /* LIKE  */
    AND = 304,                     /* AND  */
    OR = 305,                      /* OR  */
    ALL = 306,                     /* ALL  */
    COMMA = 307,                   /* COMMA  */
    SEMICOLON = 308,               /* SEMICOLON  */
    QUOTE = 309,                   /* QUOTE  */
    POINT = 310,                   /* POINT  */
    LEFTPAREN = 311,               /* LEFTPAREN  */
    RIGHTPAREN = 312,              /* RIGHTPAREN  */
    SYSTEM = 313,                  /* SYSTEM  */
    CONFIG = 314,                  /* CONFIG  */
    MEMORY = 315,                  /* MEMORY  */
    IDENTIFIER = 316,              /* IDENTIFIER  */
    INTVALUE = 317,                /* INTVALUE  */
    FLOATVALUE = 318,              /* FLOATVALUE  */
    STRINGVALUE = 319              /* STRINGVALUE  */
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
#define DROP 262
#define SELECT 263
#define INSERT 264
#define UPDATE 265
#define DELETE 266
#define DESCRIBE 267
#define FROM 268
#define WHERE 269
#define INTO 270
#define SET 271
#define VALUES 272
#define TABLE 273
#define SHOW 274
#define TABLES 275
#define MAX 276
#define MIN 277
#define COUNT 278
#define SUM 279
#define AVG 280
#define TRUE 281
#define FALSE 282
#define NOT 283
#define NULLX 284
#define CHAR 285
#define INT 286
#define LONG 287
#define STRING 288
#define BOOL 289
#define FLOAT 290
#define DOUBLE 291
#define DATE 292
#define TIMESTAMP 293
#define PRIMARY 294
#define KEY 295
#define EQ 296
#define NE 297
#define GT 298
#define GE 299
#define LT 300
#define LE 301
#define IN 302
#define LIKE 303
#define AND 304
#define OR 305
#define ALL 306
#define COMMA 307
#define SEMICOLON 308
#define QUOTE 309
#define POINT 310
#define LEFTPAREN 311
#define RIGHTPAREN 312
#define SYSTEM 313
#define CONFIG 314
#define MEMORY 315
#define IDENTIFIER 316
#define INTVALUE 317
#define FLOATVALUE 318
#define STRINGVALUE 319

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

#line 228 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (ASTNode *ast_node);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
