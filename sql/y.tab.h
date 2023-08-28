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
    FROM = 269,                    /* FROM  */
    WHERE = 270,                   /* WHERE  */
    INTO = 271,                    /* INTO  */
    VALUES = 272,                  /* VALUES  */
    TABLE = 273,                   /* TABLE  */
    MAX = 274,                     /* MAX  */
    MIN = 275,                     /* MIN  */
    COUNT = 276,                   /* COUNT  */
    SUM = 277,                     /* SUM  */
    AVERAGE = 278,                 /* AVERAGE  */
    INT = 279,                     /* INT  */
    STRING = 280,                  /* STRING  */
    BIT = 281,                     /* BIT  */
    FLOAT = 282,                   /* FLOAT  */
    DOUBLE = 283,                  /* DOUBLE  */
    DATE = 284,                    /* DATE  */
    TIMESTAMP = 285,               /* TIMESTAMP  */
    PRIMARY = 286,                 /* PRIMARY  */
    KEY = 287,                     /* KEY  */
    EQ = 288,                      /* EQ  */
    NE = 289,                      /* NE  */
    GT = 290,                      /* GT  */
    GE = 291,                      /* GE  */
    LT = 292,                      /* LT  */
    LE = 293,                      /* LE  */
    IN = 294,                      /* IN  */
    LIKE = 295,                    /* LIKE  */
    AND = 296,                     /* AND  */
    OR = 297,                      /* OR  */
    ALL = 298,                     /* ALL  */
    IDENTIFIER = 299,              /* IDENTIFIER  */
    INTVALUE = 300,                /* INTVALUE  */
    STRINGVALUE = 301              /* STRINGVALUE  */
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
#define FROM 269
#define WHERE 270
#define INTO 271
#define VALUES 272
#define TABLE 273
#define MAX 274
#define MIN 275
#define COUNT 276
#define SUM 277
#define AVERAGE 278
#define INT 279
#define STRING 280
#define BIT 281
#define FLOAT 282
#define DOUBLE 283
#define DATE 284
#define TIMESTAMP 285
#define PRIMARY 286
#define KEY 287
#define EQ 288
#define NE 289
#define GT 290
#define GE 291
#define LT 292
#define LE 293
#define IN 294
#define LIKE 295
#define AND 296
#define OR 297
#define ALL 298
#define IDENTIFIER 299
#define INTVALUE 300
#define STRINGVALUE 301

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "sql.y"

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

#line 184 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
