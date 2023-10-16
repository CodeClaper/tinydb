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
#line 23 "sql.y"

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

#line 199 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
