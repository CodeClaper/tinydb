%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "intpr.h"
#include "y.tab.h"

int yywrap() {
    return 1;
}
int yylex();
%} 
%union 
{
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
};

%token NL
%token <keyword> BEGINN COMMIT
%token <keyword> CREATE SELECT INSERT UPDATE DELETE DESCRIBE
%token <keyword> FROM
%token <keyword> WHERE
%token <keyword> INTO
%token <keyword> SET
%token <keyword> VALUES
%token <keyword> TABLE
%token <keyword> SHOW
%token <keyword> TABLES
%token <keyword> MAX MIN COUNT SUM AVG
%token <keyword> TRUE FALSE
%token <keyword> NOT
%token <keyword> NULLX
%token <keyword> CHAR INT LONG STRING BOOL FLOAT DOUBLE DATE TIMESTAMP
%token <keyword> PRIMARY KEY
%token <keyword> EQ NE GT GE LT LE IN LIKE
%token <keyword> AND OR
%token <keyword> ALL
%token <keyword> COMMA SEMICOLON QUOTE POINT LEFTPAREN RIGHTPAREN
%token <keyword> SYSTEM CONFIG MEMORY
%token <s_value> IDENTIFIER
%token <i_value> INTVALUE
%token <f_value> FLOATVALUE
%token <s_value> STRINGVALUE
%type <b_value> BOOLVALUE
%type <s_value> table
%type <select_items_node> select_items 
%type <column_node> column
%type <column_set_node> columns 
%type <value_item_node> value_item
%type <value_item_set_node> value_items
%type <column_def_node> column_def
%type <column_def_set_node> column_defs
%type <primary_key_node> primary_key_statement
%type <cond_node> cond
%type <assignment_node> assignment
%type <assignment_set_node> assignments
%type <conn_type> conn
%type <data_type> data_type
%type <opr_type> opr
%type <function_value_node> function_value
%type <function_value_node> non_all_function_value
%type <function_node> function
%type <select_node> select_statement
%type <insert_node> insert_statement
%type <update_node> update_statement
%type <delete_node> delete_statement
%type <create_table_node> create_table_statement
%type <describe_node> describe_statement
%type <show_node> show_statement
%type <ast_node> statement;
%parse-param {ASTNode *ast_node}

%%
statements: 
            statement 
            | statements statement
            | statements
            ;
statement: 
            begin_transaction_statement
                {
                    ast_node->statement_type = BEGIN_TRANSACTION_STMT;
                }
            | commit_transaction_statement
                {
                    ast_node->statement_type = COMMIT_TRANSACTION_STMT;
                }
            | create_table_statement
                {
                    ast_node->statement_type = CREATE_TABLE_STMT;
                    ast_node->create_table_node = $1;
                }
            | select_statement 
                {
                    ast_node->statement_type = SELECT_STMT;
                    ast_node->select_node = $1;
                }
            | insert_statement 
                {
                    ast_node->statement_type = INSERT_STMT;
                    ast_node->insert_node = $1;
                }
            | update_statement
                {
                    ast_node->statement_type = UPDATE_STMT;
                    ast_node->update_node = $1;
                }
            | delete_statement
                {
                    ast_node->statement_type = DELETE_STMT;
                    ast_node->delete_node = $1;
                }
            | describe_statement
                {
                    ast_node->statement_type = DESCRIBE_STMT;
                    ast_node->describe_node = $1;
                }
            | show_statement 
                {
                    ast_node->statement_type = SHOW_STMT;
                    ast_node->show_node = $1;
                }
            ;
begin_transaction_statement:
            BEGINN end
            ;
commit_transaction_statement:
            COMMIT end
            ;
create_table_statement: 
            CREATE TABLE table LEFTPAREN column_defs RIGHTPAREN end
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = $3;
                    create_table_node->column_def_set_node = $5;
                    $$ = create_table_node;
                }
            | CREATE TABLE table LEFTPAREN column_defs COMMA primary_key_statement RIGHTPAREN end
                {
                    CreateTableNode *create_table_node = make_create_table_node();
                    create_table_node->table_name = $3;
                    create_table_node->column_def_set_node = $5;
                    create_table_node->primary_key_node = $7;
                    $$ = create_table_node;
                }
            ;
select_statement:
            SELECT select_items FROM table WHERE cond  end
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = $2;
                    select_node->table_name = $4;
                    select_node->condition_node = $6;
                    $$ = select_node;
                }
            | SELECT select_items FROM table end
                {
                    SelectNode *select_node = make_select_node();
                    select_node->select_items_node = $2;
                    select_node->table_name = $4;
                    $$ = select_node;
                }
            ;
insert_statement: 
            INSERT INTO table VALUES LEFTPAREN value_items RIGHTPAREN end
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = true;
                    node->table_name = $3;
                    node->value_item_set_node = $6;
                    $$ = node;
                }
            | INSERT INTO table LEFTPAREN columns RIGHTPAREN VALUES LEFTPAREN value_items RIGHTPAREN end
                {
                    InsertNode *node = make_insert_node();
                    node->all_column = false;
                    node->table_name = $3;
                    node->columns_set_node = $5;
                    node->value_item_set_node = $9;
                    $$ = node;
                }
            ;
update_statement:
            UPDATE table SET assignments end
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = $2;
                    node->assignment_set_node = $4;
                    $$ = node;
                }
            | UPDATE table SET assignments WHERE cond end
                {
                    UpdateNode *node = make_update_node();
                    node->table_name = $2;
                    node->assignment_set_node = $4;
                    node->condition_node = $6;
                    $$ = node;
                }
            ;
delete_statement:
            DELETE FROM table end
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = $3;
                    $$ = node;
                }
            | DELETE FROM table WHERE cond end
                {
                    DeleteNode *node = make_delete_node();
                    node->table_name = $3;
                    node->condition_node = $5;
                    $$ = node;
                }
            ;
describe_statement:
            DESCRIBE table end
                {
                    DescribeNode *node = make_describe_node();
                    node->table_name = strdup($2);
                    $$ = node;
                }
            ;
show_statement:
            SHOW TABLES end
                {
                    $$ = make_show_node(SHOW_TABLES);
                }
            | SHOW MEMORY end
                {
                    $$ = make_show_node(SHOW_MEMORY);
                }
            ;
select_items: 
            columns
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_COLUMNS;
                    select_items_node->column_set_node= $1;
                    $$ = select_items_node;
                }
            | function
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_FUNCTION;
                    select_items_node->function_node = $1;
                    $$ = select_items_node;
                }
            | ALL 
                {
                    SelectItemsNode *select_items_node = make_select_items_node();
                    select_items_node->type = SELECT_ALL;
                    $$ = select_items_node;
                }
            ;
table:       
            IDENTIFIER     
                {
                    $$ = $1;
                }
            ;
columns:
            column
                {
                    ColumnSetNode *column_set_node = make_column_set_node();
                    add_column_to_set(column_set_node, $1);
                    $$ = column_set_node;
                }
            | columns COMMA column
                {
                    $$ = $1;
                    add_column_to_set($$, $3);
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
           column data_type
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = $1;
                    column_def_node->data_type = $2;
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = false;
                    column_def_node->is_define_len = false;
                    $$ = column_def_node;
                }
           | column STRING LEFTPAREN INTVALUE RIGHTPAREN
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = $1;
                    column_def_node->data_type = T_STRING;
                    column_def_node->data_len = $4;
                    column_def_node->is_define_len = true;
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = false;
                    $$ = column_def_node;
                }
            | column table
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = $1;
                    column_def_node->data_type = T_REFERENCE;
                    column_def_node->table_name = $2;
                    column_def_node->is_define_len = false;
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = false;
                    $$ = column_def_node;
                }
            | column data_type NOT NULLX
                {
                    ColumnDefNode *column_def_node = make_column_def_node();
                    column_def_node->column = $1;
                    column_def_node->data_type = $2;
                    column_def_node->is_primary = false;
                    column_def_node->allow_null = true;
                    $$ = column_def_node;
                }
           ;
data_type:
           INT          { $$ = T_INT; }
           | LONG       { $$ = T_LONG;  }
           | CHAR       { $$ = T_CHAR; }
           | STRING     { $$ = T_STRING; }
           | BOOL       { $$ = T_BOOL; }
           | FLOAT      { $$ = T_FLOAT; }  
           | DOUBLE     { $$ = T_DOUBLE; }
           | TIMESTAMP  { $$ = T_TIMESTAMP; }
           | DATE       { $$ = T_DATE; }
           ;
primary_key_statement:
           PRIMARY KEY LEFTPAREN column RIGHTPAREN
                {
                    PrimaryKeyNode *primary_key_node = make_primary_key_node();
                    primary_key_node->column = $4;
                    $$ = primary_key_node;
                }
           ;
column: 
            IDENTIFIER
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = strdup($1);
                    column_node->has_sub_column = false;
                    $$ = column_node;
                }
            | IDENTIFIER POINT IDENTIFIER
                {
                    ColumnNode *column_node = make_column_node();
                    column_node->column_name = strdup($1);
                    column_node->sub_column_name = strdup($3);
                    column_node->has_sub_column = true;
                    $$ = column_node;
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
                    node->i_value = $1;
                    node->data_type = T_INT;
                    $$ = node;
                }
            | BOOLVALUE
                {
                    ValueItemNode *node = make_value_item_node();
                    node->b_value = $1;
                    node->data_type = T_BOOL;
                    $$ = node;
                }
            | STRINGVALUE 
                {
                    ValueItemNode *node = make_value_item_node();
                    node->s_value = $1;
                    node->data_type = T_STRING;
                    $$ = node;
                }
            | FLOATVALUE 
                {
                    ValueItemNode *node = make_value_item_node();
                    node->f_value = $1;
                    node->data_type = T_FLOAT;
                    $$ = node;
                }
            | LEFTPAREN value_items RIGHTPAREN
                {
                    ValueItemNode *node = make_value_item_node();
                    node->nest_value_item_set = $2;
                    node->data_type = T_REFERENCE;
                    $$ = node;
                }
            ;
BOOLVALUE:
            TRUE
                {
                    $$ = true;
                }
            | FALSE
                {
                    $$ = false;
                }
            ;
assignments:
           assignment
                {
                    AssignmentSetNode *node = make_assignment_set_node();
                    add_assignment_to_set(node, $1);
                    $$ = node;
                }
           | assignments COMMA assignment
                {
                    add_assignment_to_set($1, $3);
                    $$ = $1;
                }
           ;
assignment:
		  column EQ value_item
                {
                    AssignmentNode *node = make_assignment_node();
                    node->column = $1;
                    node->value = $3;
                    $$ = node;
                }
          ;
cond: 
            column opr value_item
                {
                    ConditionNode *cond_node = make_cond_node();
                    cond_node->column = $1;
                    cond_node->opr_type = $2;
                    cond_node->value = $3;
                    cond_node->type = EXEC_CONDITION;
                    $$ = cond_node;
                }
            | column opr value_item conn cond
                {
                    ConditionNode *cond_node = make_cond_node();
                    cond_node->column = $1;
                    cond_node->opr_type = $2;
                    cond_node->value = $3;
                    cond_node->conn_type = $4;
                    cond_node->next = $5;
                    cond_node->type = EXEC_CONDITION;
                    $$ = cond_node;
                }
            ;
opr: 
            EQ      { $$ = O_EQ; }
            | NE    { $$ = O_NE; }
            | GT    { $$ = O_GT; }
            | GE    { $$ = O_GE; }
            | LT    { $$ = O_LT; }
            | LE    { $$ = O_LE; }
            | IN    { $$ = O_IN; }
            | LIKE  { $$ = O_LIKE; }
            ;
conn: 
            AND     { $$ = C_AND; }
            | OR    { $$ = C_OR; }
            ;
function:       
            MAX LEFTPAREN non_all_function_value RIGHTPAREN
                {
                    FunctionNode *function_node = make_function_node();        
                    function_node->function_type = F_MAX;
                    function_node->value = $3;
                    $$ = function_node;
                }
            | MIN LEFTPAREN non_all_function_value RIGHTPAREN
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
                    node->i_value = $1;
                    node->value_type = V_INT;
                    $$ = node;
                }
            | column 
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = $1;
                    node->value_type = V_COLUMN;
                    $$ = node;
                }
            | ALL
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->value_type = V_ALL;
                    $$ = node;
                }
            ;
non_all_function_value:
            INTVALUE
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->i_value = $1;
                    node->value_type = V_INT;
                    $$ = node;
                }
            | column 
                {
                    FunctionValueNode *node = make_function_value_node();
                    node->column = $1;
                    node->value_type = V_COLUMN;
                    $$ = node;
                }
            ;
end:        
            NL
            | SEMICOLON NL
            ;
%%
