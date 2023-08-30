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
    MAX = 275,                     /* MAX  */
    MIN = 276,                     /* MIN  */
    COUNT = 277,                   /* COUNT  */
    SUM = 278,                     /* SUM  */
    AVERAGE = 279,                 /* AVERAGE  */
    INT = 280,                     /* INT  */
    STRING = 281,                  /* STRING  */
    BIT = 282,                     /* BIT  */
    FLOAT = 283,                   /* FLOAT  */
    DOUBLE = 284,                  /* DOUBLE  */
    DATE = 285,                    /* DATE  */
    TIMESTAMP = 286,               /* TIMESTAMP  */
    PRIMARY = 287,                 /* PRIMARY  */
    KEY = 288,                     /* KEY  */
    EQ = 289,                      /* EQ  */
    NE = 290,                      /* NE  */
    GT = 291,                      /* GT  */
    GE = 292,                      /* GE  */
    LT = 293,                      /* LT  */
    LE = 294,                      /* LE  */
    IN = 295,                      /* IN  */
    LIKE = 296,                    /* LIKE  */
    AND = 297,                     /* AND  */
    OR = 298,                      /* OR  */
    ALL = 299,                     /* ALL  */
    IDENTIFIER = 300,              /* IDENTIFIER  */
    INTVALUE = 301,                /* INTVALUE  */
    STRINGVALUE = 302              /* STRINGVALUE  */
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
#define MAX 275
#define MIN 276
#define COUNT 277
#define SUM 278
#define AVERAGE 279
#define INT 280
#define STRING 281
#define BIT 282
#define FLOAT 283
#define DOUBLE 284
#define DATE 285
#define TIMESTAMP 286
#define PRIMARY 287
#define KEY 288
#define EQ 289
#define NE 290
#define GT 291
#define GE 292
#define LT 293
#define LE 294
#define IN 295
#define LIKE 296
#define AND 297
#define OR 298
#define ALL 299
#define IDENTIFIER 300
#define INTVALUE 301
#define STRINGVALUE 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "sql.y"

   char             *s_value;
   int              i_value;
   char             *keyword;
   IntValueNode     *int_value_node;
   StringValueNode  *string_value_node;
   IdentNode        *ident_node;
   IdentSetNode     *ident_set_node;
   OprNode          *opr_node;
   ConnNode         *conn_node;
   DataTypeNode     *data_type_node;
   ColumnDefNode    *column_def_node;
   ColumnDefSetNode *column_def_set_node;
   SelectItemsNode  *select_items_node;
   ColumnSetNode    *column_set_node;
   ValueItemNode    *value_item_node;
   ValueItemSetNode *value_item_set_node;
   PrimaryKeyNode   *primary_key_node;
   FromItemNode     *from_item_node;
   ConditionNode    *cond_node;
   CreateTableNode  *create_table_node;
   SelectNode       *select_node;
   InsertNode       *insert_node;
   DescribeNode     *describe_node;

#line 187 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
