%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intpr.h"

int yywrap() {
    return 1;
}

int yyerror(const char *s) {
    fprintf(stderr, "Sql parse error, '%s'.\n", s);
}
%}
%union 
{
   char *s_value;
   int i_value;
   char *keyword;
   ConstNode *const_node;
   IdentNode *ident_node;
   IdentSetNode *ident_set_node;
   OprNode *opr_node;
   ConnNode *conn_node;
   SelectItemsNode *select_items_node;
   ColumnSetNode *column_set_node;
   ValueItemNode *value_item_node;
   ValueItemSetNode *value_item_set_node;
   FromItemNode *from_item_node;
   ConditionNode *cond_node;
   SelectNode *select_node;
   InsertNode *insert_node;
};
%token NL COMMA SEMICOLON LEFTPAREN RIGHTPAREN QUOTE
%token <keyword> SELECT INSERT UPDATE DELETE
%token <keyword> FROM
%token <keyword> WHERE
%token <keyword> INTO
%token <keyword> VALUES
%token <keyword> MAX MIN COUNT SUM AVERAGE
%token AND OR
%token ALL
%token <ident_node> IDENTIFIER
%token <const_node> CONST
%type <ident_set_node> identifiers
%type <select_items_node> select_items 
%type <column_set_node> columns 
%type <from_item_node> from_item
%type <value_item_node> value_item
%type <value_item_set_node> value_items
%type <cond_node> cond
%type <opr_node> op
%type <conn_node> conn
%type <select_node> statement_select
%type <insert_node> statement_insert
%token EQ NE GT GE LT LE IN LIKE

%%
statements: 
            statement 
            | statements statement
            | statements error
            ;
statement: 
            statement_select 
                {
                    set_select_ast_node($1);
                }
            | statement_insert 
                {
                    set_insert_ast_node($1);
                }
            ;
statement_select:
            select select_items FROM from_item WHERE cond SEMICOLON NL
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = $2;
                    select_node->from_item_node = $4;
                    $$ = select_node;
                }
            | select select_items FROM from_item SEMICOLON NL
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = $2;
                    select_node->from_item_node = $4;
                    $$ = select_node;
                }
            ;
statement_insert: 
            insert into from_item values LEFTPAREN value_items RIGHTPAREN SEMICOLON NL
                {
                    InsertNode *node = make_insert_node();
                    node->if_ignore_columns = true;
                    node->from_item_node = $3;
                    node->value_item_set_node = $6;
                    $$ = node;
                }
            | insert into from_item LEFTPAREN columns RIGHTPAREN values LEFTPAREN value_items RIGHTPAREN SEMICOLON NL
                {
                    InsertNode *node = make_insert_node();
                    node->if_ignore_columns = false;
                    node->from_item_node = $3;
                    node->columns_set_node = $5;
                    node->value_item_set_node = $9;
                    $$ = node;
                }
            ;
select: 
            SELECT 
            ;
insert:     
            INSERT
            ;
select_items: 
            identifiers
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node-> ident_set_node= $1;
                    $$ = select_items_node;
                }
            ;
columns:
            identifiers 
                {
                    ColumnSetNode *column_set_node = make_column_set_node();
                    column_set_node -> ident_set_node = $1;
                    $$ = column_set_node;
                }
            ;
from_item: 
            IDENTIFIER
                {
                    IdentNode *node = make_ident_node($1);
                    $$ = make_from_item_node();
                    $$->table = node;
                }
            ;
value_items:
            value_item
                {
                    ValueItemSetNode *node = make_value_item_set_node();
                    add_value_item(node, $1);
                    $$ = node;
                }
            | value_items COMMA value_item
                {
                    $$ = $1;
                    add_value_item($$, $3);
                }
            ;
value_item:
            CONST
                {
                    ValueItemNode *node = make_value_item_node();
                    ConstNode *const_node = make_const_node($1);
                    node->i_value = const_node;
                    $$ = node;
                }
            | QUOTE IDENTIFIER QUOTE 
                {
                    ValueItemNode *node = make_value_item_node();
                    IdentNode *ident_node = make_ident_node($2);
                    node->s_value = ident_node;
                    $$ = node;
                }
            ;
identifiers: 
            ALL
                { 
                    IdentNode *node = make_ident_node("*");
                    $$ = make_ident_set_node();
                    add_ident($$, node);
                }
            | IDENTIFIER 
                { 
                    IdentNode *node = make_ident_node($1);
                    $$ = make_ident_set_node();
                    add_ident($$, node);
                }
           | identifiers COMMA IDENTIFIER 
                { 
                    $$ = $1;
                    IdentNode *node = make_ident_node($3);
                    add_ident($$, node);
                }
           ;
cond: 
            IDENTIFIER op compare
                {
                    ConditionNode *cond_node = make_cond_node();
                    IdentNode *ident_node = make_ident_node($1);
                    cond_node->column = ident_node;
                    cond_node->opr_node = $2;
                    $$ = cond_node;
                }
            | IDENTIFIER op compare conn cond
                {
                    ConditionNode *cond_node = make_cond_node();
                    IdentNode *ident_node = make_ident_node($1);
                    cond_node->column = ident_node;
                    cond_node->opr_node = $2;
                    $$ = cond_node;
                }
            ;
compare: 
            IDENTIFIER 
                { 
                    IdentNode *node = make_ident_node($1);
                }
            | CONST;
op: 
            EQ      { $$ = make_opr_node(O_EQ); }
            | NE    { $$ = make_opr_node(O_NE); }
            | GT    { $$ = make_opr_node(O_GT); }
            | GE    { $$ = make_opr_node(O_GE); }
            | LT    { $$ = make_opr_node(O_LT); }
            | LE    { $$ = make_opr_node(O_LE); }
            | IN    { $$ = make_opr_node(O_IN); }
            | LIKE  { $$ = make_opr_node(O_LIKE); }
            ;
conn: 
            AND     { $$ = make_conn_node(C_AND); }
            | OR    { $$ = make_conn_node(C_OR); }
            ;
func: 
            MAX
            | MIN
            | COUNT
            | SUM
            | AVERAGE
            ;
into:
            INTO
            ;
values:     
            VALUES
            ;
%%
