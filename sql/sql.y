%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intpr.h"

int yywrap() {
    return 1;
}

int yyerror(const char *s) {
    fprintf(stderr, "Sql parse error, near by'%s'.\n", yylval);
}
%} 
%union 
{
   char                     *s_value;
   int                      i_value;
   char                     *keyword;
   IntValueNode             *int_value_node;
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
};
%token NL COMMA SEMICOLON LEFTPAREN RIGHTPAREN QUOTE
%token <keyword> CREATE SELECT INSERT UPDATE DELETE DESCRIBE
%token <keyword> FROM
%token <keyword> WHERE
%token <keyword> INTO
%token <keyword> VALUES
%token <keyword> TABLE
%token <keyword> SHOW
%token <keyword> TABLES
%token <keyword> MAX MIN COUNT SUM AVG
%token INT STRING BIT FLOAT DOUBLE DATE TIMESTAMP
%token PRIMARY KEY
%token EQ NE GT GE LT LE IN LIKE
%token AND OR
%token ALL
%token <ident_node>IDENTIFIER
%token <int_value_node>INTVALUE
%token <string_value_node>STRINGVALUE
%type <ident_set_node> identifiers
%type <data_type_node> column_type
%type <select_items_node> select_items 
%type <column_set_node> columns 
%type <from_item_node> from_item
%type <value_item_node> value_item
%type <value_item_set_node> value_items
%type <column_def_node> column_def
%type <column_def_set_node> column_defs
%type <primary_key_node> primary_key
%type <cond_node> cond
%type <opr_node> op
%type <conn_node> conn
%type <function_value_node> function_value
%type <function_node> func
%type <select_node> statement_select
%type <insert_node> statement_insert
%type <create_table_node> statement_create_table
%type <describe_node> statement_describe
%type <show_table_node> statement_show_tables

%%
statements: 
            statement 
            | statements statement
            | statements error
            ;
statement: 
            statement_create_table
                {
                   set_create_table_ast_node($1); 
                }
            |statement_select 
                {
                    set_select_ast_node($1);
                }
            | statement_insert 
                {
                    set_insert_ast_node($1);
                }
            | statement_describe
                {
                    set_describe_ast_node($1);
                }
            | statement_show_tables 
                {
                    set_show_tables_ast_node($1);
                }
            ;
statement_create_table: 
            create table IDENTIFIER LEFTPAREN column_defs RIGHTPAREN statement_end
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    IdentNode *node = make_ident_node($3);
                    create_table_node->table_name = node;
                    create_table_node->column_def_set_node = $5;
                    $$ = create_table_node;
                }
            | create table IDENTIFIER LEFTPAREN column_defs COMMA primary_key RIGHTPAREN statement_end
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    IdentNode *node = make_ident_node($3);
                    create_table_node->table_name = node;
                    create_table_node->column_def_set_node = $5;
                    create_table_node->primary_key_node = $7;
                    $$ = create_table_node;
                }
            ;
statement_select:
            select select_items FROM from_item WHERE cond statement_end
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = $2;
                    select_node->from_item_node = $4;
                    $$ = select_node;
                }
            | select select_items FROM from_item statement_end
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = $2;
                    select_node->from_item_node = $4;
                    $$ = select_node;
                }
            ;
statement_insert: 
            insert into from_item values LEFTPAREN value_items RIGHTPAREN statement_end
                {
                    InsertNode *node = make_insert_node();
                    node->if_ignore_columns = true;
                    node->from_item_node = $3;
                    node->value_item_set_node = $6;
                    $$ = node;
                }
            | insert into from_item LEFTPAREN columns RIGHTPAREN values LEFTPAREN value_items RIGHTPAREN statement_end
                {
                    InsertNode *node = make_insert_node();
                    node->if_ignore_columns = false;
                    node->from_item_node = $3;
                    node->columns_set_node = $5;
                    node->value_item_set_node = $9;
                    $$ = node;
                }
            ;
statement_describe:
            describe from_item statement_end
                {
                    DescribeNode *node = make_describe_node();
                    node->from_item_node = $2;
                    $$ = node;
                }
            ;
statement_show_tables:
            show tables statement_end
                {
                    $$ = make_show_tables_node();
                }
            ;
statement_end:
            NL
            | SEMICOLON NL
            ;
create:
            CREATE
            ;
select: 
            SELECT 
            ;
insert:     
            INSERT
            ;
table:      
            TABLE
            ;
describe:
            DESCRIBE
            ;
show:       
            SHOW
            ;
tables:     
            TABLES
            ;
select_items: 
            identifiers
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node-> ident_set_node= $1;
                    select_items_node->is_function_node = false;
                    $$ = select_items_node;
                }
            | func
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->function_node= $1;
                    select_items_node->is_function_node = true;
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
column_defs:
            column_def
                {
                    ColumnDefSetNode *column_def_set_node = make_column_def_set_node();
                    add_column_def_to_set(column_def_set_node, $1);
                    $$ = column_def_set_node;
                }
            | column_defs COMMA column_def
                {
                    $$ = $1;
                    add_column_def_to_set($$, $3);
                }
            ;
column_def:
           IDENTIFIER column_type
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    IdentNode *node = make_ident_node($1);
                    column_def_node->column_name = node;
                    column_def_node->column_type = $2;
                    $$ = column_def_node;
                }
           ;
column_type:
           INT          { $$ = make_data_type_node(T_INT); }
           | STRING     { $$ = make_data_type_node(T_STRING);}
           | BIT        { $$ = make_data_type_node(T_BIT); }
primary_key:
           PRIMARY KEY LEFTPAREN IDENTIFIER RIGHTPAREN
                {
                    PrimaryKeyNode *primary_key_node = make_primary_key_node();
                    IdentNode *node = make_ident_node($4);
                    primary_key_node->primary_key_column = node;
                    $$ = primary_key_node;
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
            INTVALUE
                {
                    ValueItemNode *node = make_value_item_node();
                    IntValueNode *int_value_node = make_int_value_node($1);
                    node->i_value = int_value_node;
                    node->data_type = T_INT;
                    $$ = node;
                }
            | QUOTE IDENTIFIER QUOTE 
                {
                    ValueItemNode *node = make_value_item_node();
                    StringValueNode *string_value_node = make_string_value_node($2);
                    node->s_value = string_value_node;
                    node->data_type = T_STRING;
                    $$ = node;
                }
            | QUOTE STRINGVALUE QUOTE 
                {
                    ValueItemNode *node = make_value_item_node();
                    StringValueNode *string_value_node = make_string_value_node($2);
                    node->s_value = string_value_node;
                    node->data_type = T_STRING;
                    $$ = node;
                }
            ;
identifiers: 
            ALL
                { 
                    IdentSetNode *ident_set_node = make_ident_set_node();
                    ident_set_node->all_column = true;
                    $$ = ident_set_node;
                }
            | IDENTIFIER 
                { 
                    IdentSetNode *ident_set_node = make_ident_set_node();
                    ident_set_node->all_column = false;
                    IdentNode *node = make_ident_node($1);
                    add_ident(ident_set_node, node);
                    $$ = ident_set_node;
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
            | INTVALUE;
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
            MAX LEFTPAREN function_value RIGHTPAREN
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MAX;
                    function_node->value = $3;
                    $$ = function_node;
                }
            | MIN LEFTPAREN function_value RIGHTPAREN
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MIN;
                    function_node->value = $3;
                    $$ = function_node;
                }
            | COUNT LEFTPAREN function_value RIGHTPAREN
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_COUNT;
                    function_node->value = $3;
                    $$ = function_node;
                }
            | SUM LEFTPAREN function_value RIGHTPAREN
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_SUM;
                    function_node->value = $3;
                    $$ = function_node;
                }
            | AVG LEFTPAREN function_value RIGHTPAREN
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_AVG;
                    function_node->value = $3;
                    $$ = function_node;
                }
            ;
function_value:
            INTVALUE
                {
                    FunctionValueNode *node = make_function_value_node();
                    IntValueNode *int_value_node = make_int_value_node($1);
                    node->i_value = int_value_node;
                    $$ = node;
                }
            | IDENTIFIER 
                {
                    FunctionValueNode *node = make_function_value_node();
                    IdentNode *ident_node = make_ident_node($1);
                    node->id_value = ident_node;
                    $$ = node;
                }
            ;
into:
            INTO
            ;
values:     
            VALUES
            ;
%%
