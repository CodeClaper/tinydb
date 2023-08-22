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
    SELECT = 264,                  /* SELECT  */
    INSERT = 265,                  /* INSERT  */
    UPDATE = 266,                  /* UPDATE  */
    DELETE = 267,                  /* DELETE  */
    FROM = 268,                    /* FROM  */
    WHERE = 269,                   /* WHERE  */
    INTO = 270,                    /* INTO  */
    VALUES = 271,                  /* VALUES  */
    MAX = 272,                     /* MAX  */
    MIN = 273,                     /* MIN  */
    COUNT = 274,                   /* COUNT  */
    SUM = 275,                     /* SUM  */
    AVERAGE = 276,                 /* AVERAGE  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    ALL = 279,                     /* ALL  */
    IDENTIFIER = 280,              /* IDENTIFIER  */
    CONST = 281,                   /* CONST  */
    EQ = 282,                      /* EQ  */
    NE = 283,                      /* NE  */
    GT = 284,                      /* GT  */
    GE = 285,                      /* GE  */
    LT = 286,                      /* LT  */
    LE = 287,                      /* LE  */
    IN = 288,                      /* IN  */
    LIKE = 289                     /* LIKE  */
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
#define SELECT 264
#define INSERT 265
#define UPDATE 266
#define DELETE 267
#define FROM 268
#define WHERE 269
#define INTO 270
#define VALUES 271
#define MAX 272
#define MIN 273
#define COUNT 274
#define SUM 275
#define AVERAGE 276
#define AND 277
#define OR 278
#define ALL 279
#define IDENTIFIER 280
#define CONST 281
#define EQ 282
#define NE 283
#define GT 284
#define GE 285
#define LT 286
#define LE 287
#define IN 288
#define LIKE 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "sql.y"

   char *s_value;
   int i_value;
   char *keyword;
   ConstNode *const_node;
   IdentNode *ident_node;
   IdentSetNode *ident_set_node;
   SelectItemsNode *select_items_node;
   ColumnSetNode *column_set_node;
   ValueItemNode *value_item_node;
   ValueItemSetNode *value_item_set_node;
   FromItemNode *from_item_node;
   SelectNode *select_node;
   InsertNode *insert_node;

#line 151 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
