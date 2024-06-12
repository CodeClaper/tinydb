%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "intpr.h"
#include "mmu.h"
#include "y.tab.h"

int yywrap() {
    return 1;
}
int yylex();
%} 
%union 
{
   char                         *strVal;
   int64_t                      intVal;
   double                       floatVal;
   bool                         boolVal;
   char                         *keyword;
   ReferValue                   *referVal;
   CompareType                  compare_type;
   DataTypeNode                 *data_type_node;
   ColumnDefName                *column_def_name;
   ColumnDefNode                *column_def_node;
   BaseTableElementNode         *base_table_element;
   ColumnDefOptNode             *column_def_opt;
   TableContraintDefNode        *table_contraint_def;
   ColumnNode                   *column_node;
   AtomNode                     *atom_node;
   ValueItemNode                *value_item_node;
   SelectionNode                *selection_node;
   ScalarExpNode                *scalar_exp_node;
   FunctionValueNode            *function_value_node;
   FunctionNode                 *function_node;
   CalculateNode                *calculate_node;
   AssignmentNode               *assignment_node;
   AssignmentSetNode            *assignment_set_node;
   ConditionNode                *condition_node;
   PredicateNode                *predicate_node;
   ComparisonNode               *comparison_node;
   LikeNode                     *like_node;
   InNode                       *in_node;
   LimitNode                    *limit_node;
   TableRefNode                 *table_ref_node;
   TableRefSetNode              *table_ref_set_node;
   QuerySpecNode                *query_spec_node;
   ValuesOrQuerySpecNode        *values_or_query_spec_node;
   FromClauseNode               *from_clause_node;
   WhereClauseNode              *where_clause_node;
   TableExpNode                 *table_exp_node; 
   CreateTableNode              *create_table_node;
   DropTableNode                *drop_table_node;
   SelectNode                   *select_node;
   InsertNode                   *insert_node;
   UpdateNode                   *update_node;
   DeleteNode                   *delete_node;
   DescribeNode                 *describe_node;
   ShowNode                     *show_node;
   Statement                    *statement;
   List                         *list;
};

%left OR
%left AND
%left '+' '-'
%left '*' '/'  
%left '(' ')'
%left '[' ']'

%token NL
%token <keyword> BEGINN COMMIT ROLLBACK
%token <keyword> CREATE DROP SELECT INSERT UPDATE DELETE DESCRIBE
%token <keyword> FROM
%token <keyword> WHERE
%token <keyword> INTO
%token <keyword> SET
%token <keyword> VALUES
%token <keyword> TABLE
%token <keyword> LIMIT
%token <keyword> SHOW
%token <keyword> TABLES
%token <keyword> PRIMARY KEY
%token <keyword> UNIQUE DEFAULT CHECK REFERENCES FOREIGN
%token <keyword> MAX MIN COUNT SUM AVG
%token <keyword> REF
%token <keyword> TRUE FALSE
%token <keyword> NULLX
%token <keyword> AS
%token <keyword> COMMENT
%token <keyword> CHAR INT LONG VARCHAR STRING BOOL FLOAT DOUBLE DATE TIMESTAMP
%token <keyword> EQ NE GT GE LT LE IN LIKE
%token <keyword> NOT
%token <keyword> SYSTEM CONFIG MEMORY
%token <strVal> IDENTIFIER
%token <intVal> INTVALUE
%token <floatVal> FLOATVALUE
%token <strVal> STRINGVALUE
%type <boolVal> BOOLVALUE
%type <referVal> REFERVALUE
%type <strVal> table
%type <strVal> range_variable
%type <scalar_exp_node> scalar_exp
%type <list> scalar_exp_commalist
%type <selection_node> selection
%type <column_node> column
%type <list> columns 
%type <atom_node> atom
%type <value_item_node> value_item
%type <list> value_items
%type <column_def_name> column_def_name
%type <list> column_def_name_commalist
%type <base_table_element> base_table_element
%type <list> base_table_element_commalist
%type <column_def_opt> column_def_opt
%type <list> column_def_opt_list
%type <table_contraint_def> table_contraint_def
%type <column_def_node> column_def
%type <list> column_defs
%type <condition_node> condition
%type <predicate_node> predicate
%type <comparison_node> comparison_predicate
%type <like_node> like_predicate
%type <in_node> in_predicate
%type <limit_node> opt_limit
%type <assignment_node> assignment
%type <assignment_set_node> assignments
%type <data_type_node> data_type
%type <intVal> array_dim_clause
%type <compare_type> compare
%type <function_value_node> function_value
%type <function_value_node> non_all_function_value
%type <function_node> function
%type <calculate_node> calculate
%type <table_ref_node> table_ref
%type <table_ref_set_node> table_ref_commalist
%type <query_spec_node> query_spec
%type <values_or_query_spec_node> values_or_query_spec
%type <from_clause_node> from_clause
%type <where_clause_node> where_clause
%type <where_clause_node> opt_where_clause
%type <table_exp_node> table_exp   
%type <select_node> select_statement
%type <insert_node> insert_statement
%type <update_node> update_statement
%type <delete_node> delete_statement
%type <create_table_node> create_table_statement
%type <drop_table_node> drop_table_statement
%type <describe_node> describe_statement
%type <show_node> show_statement
%type <statement> statement;
%type <list> statements;
%parse-param {List *states}

%%
statements: 
    statement 
        {
            append_list(states, $1);
            $$ = states;
        }
    | statements statement
        {
            append_list($1, $2);
            $$ = $1;
        }
    ;
statement: 
    begin_transaction_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = BEGIN_TRANSACTION_STMT;
            $$ = statement;
        }
    | commit_transaction_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = COMMIT_TRANSACTION_STMT;
            $$ = statement;
        }
    | rollback_transaction_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = ROLLBACK_TRANSACTION_STMT;
            $$ = statement;
        }
    | create_table_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = CREATE_TABLE_STMT;
            statement->create_table_node = $1;
            $$ = statement;
        }
    | drop_table_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = DROP_TABLE_STMT;
            statement->drop_table_node = $1;
            $$ = statement;
        }
    | select_statement 
        {
            Statement *statement = make_statement();
            statement->statement_type = SELECT_STMT;
            statement->select_node = $1;
            $$ = statement;
        }
    | insert_statement 
        {
            Statement *statement = make_statement();
            statement->statement_type = INSERT_STMT;
            statement->insert_node = $1;
            $$ = statement;
        }
    | update_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = UPDATE_STMT;
            statement->update_node = $1;
            $$ = statement;
        }
    | delete_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = DELETE_STMT;
            statement->delete_node = $1;
            $$ = statement;
        }
    | describe_statement
        {
            Statement *statement = make_statement();
            statement->statement_type = DESCRIBE_STMT;
            statement->describe_node = $1;
            $$ = statement;
        }
    | show_statement 
        {
            Statement *statement = make_statement();
            statement->statement_type = SHOW_STMT;
            statement->show_node = $1;
            $$ = statement;
        }
    ;
begin_transaction_statement:
    BEGINN end
    ;
commit_transaction_statement:
    COMMIT end
    ;
rollback_transaction_statement:
    ROLLBACK end
    ;
/* Create table statement. */
create_table_statement: 
    CREATE TABLE table '(' base_table_element_commalist ')' end
        {
            CreateTableNode *create_table_node = make_create_table_node();
            create_table_node->table_name = $3;
            create_table_node->base_table_element_commalist = $5;
            $$ = create_table_node;
        }
    ;
/* Drop table Statement */
drop_table_statement:
    DROP TABLE table end
        {
            DropTableNode *drop_table_node = make_drop_table_node();
            drop_table_node->table_name = $3;
            $$ = drop_table_node;
        }
    ;
/* Select Statement */
select_statement:
    SELECT selection table_exp end
        {
            SelectNode *select_node = make_select_node();
            select_node->selection = $2;
            select_node->table_exp = $3;
            $$ = select_node;
        }
    ;
/* Insert Statement */
insert_statement: 
    INSERT INTO table values_or_query_spec end
        {
            InsertNode *node = make_insert_node();
            node->all_column = true;
            node->table_name = $3;
            node->values_or_query_spec = $4;
            $$ = node;
        }
    | INSERT INTO table '(' columns ')' values_or_query_spec end
        {
            InsertNode *node = make_insert_node();
            node->all_column = false;
            node->table_name = $3;
            node->column_list = $5;
            node->values_or_query_spec = $7;
            $$ = node;
        }
    ;
/* Update Statement */
update_statement:
    UPDATE table SET assignments opt_where_clause end
        {
            UpdateNode *node = make_update_node();
            node->table_name = $2;
            node->assignment_set_node = $4;
            node->where_clause = $5;
            $$ = node;
        }
    ;
/* Delete Statement. */
delete_statement:
    DELETE FROM table end
        {
            DeleteNode *node = make_delete_node();
            node->table_name = $3;
            $$ = node;
        }
    | DELETE FROM table WHERE condition end
        {
            DeleteNode *node = make_delete_node();
            node->table_name = $3;
            node->condition_node = $5;
            $$ = node;
        }
    ;
/* Describe Statement. */
describe_statement:
    DESCRIBE table end
        {
            DescribeNode *node = make_describe_node();
            node->table_name = $2;
            $$ = node;
        }
    ;
/* Show Statement. */
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
selection:
    scalar_exp_commalist
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = false;
            selection_node->scalar_exp_list = $1;
            $$ = selection_node;
        }
    | '*'
        {
            SelectionNode *selection_node = make_selection_node();
            selection_node->all_column = true;
            $$ = selection_node;
        }
    ;
table_exp:
    from_clause opt_where_clause
        {
            TableExpNode *table_exp = make_table_exp_node();
            table_exp->from_clause = $1;
            table_exp->where_clause = $2;
            $$ = table_exp;
        }
    ;
from_clause:
    /* empty */
        {
            $$ = NULL;
        }
    | FROM table_ref_commalist
        {
            FromClauseNode *from_clause = make_from_clause_node();
            from_clause->from = $2;
            $$ = from_clause;
        }
    ;
table_ref_commalist:
    table_ref 
        {
            TableRefSetNode *table_ref_set = make_table_ref_set_node();
            add_table_ref_to_set(table_ref_set, $1);
            $$ = table_ref_set;
        }
    | table_ref_commalist ',' table_ref 
        {
            add_table_ref_to_set($1, $3);
            $$ = $1;
        }
    ;
table_ref:
    table
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = $1;
            $$ = table_ref;
        }
    | table range_variable 
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = $1;
            table_ref->range_variable = $2;
            $$ = table_ref;
        }
    | table AS range_variable 
        {
            TableRefNode *table_ref = make_table_ref_node();
            table_ref->table = $1;
            table_ref->range_variable = $3;
            $$ = table_ref;
        }
    ;
table:       
    IDENTIFIER     
        {
            $$ = $1;
        }
    ;
range_variable:
    IDENTIFIER
        {
            $$ = $1;
        }
    ;
opt_where_clause:
    /* empty */
        {
            $$ = NULL;
        }
    | where_clause
        {
            $$ = $1;
        }
    ;
where_clause:
    WHERE condition
        {
            WhereClauseNode *where_clause_node = make_where_clause_node();
            where_clause_node->condition = $2;
            $$ = where_clause_node;
        }
    ;
values_or_query_spec:
    VALUES '(' value_items')'
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_VALUES;
            values_or_query_spec->values = $3;
            $$ = values_or_query_spec;
        }
    | query_spec 
        {
            ValuesOrQuerySpecNode *values_or_query_spec = make_values_or_query_spec_node();
            values_or_query_spec->type = VQ_QUERY_SPEC;
            values_or_query_spec->query_spec = $1;
            $$ = values_or_query_spec;
        }
    ;
query_spec:
    SELECT selection table_exp
        {
            QuerySpecNode *query_spec = make_query_spec_node();
            query_spec->selection = $2;
            query_spec->table_exp = $3;
            $$ = query_spec;
        }
    ;
scalar_exp_commalist:
    scalar_exp
        {
            List *scalar_exp_list = create_list(NODE_SCALAR_EXP);
            append_list(scalar_exp_list, $1);
            $$ = scalar_exp_list;
        }
    | scalar_exp_commalist ',' scalar_exp
        {
            append_list($1, $3);
            $$ = $1;
        }
    ;
scalar_exp:
    calculate
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_CALCULATE;
            scalar_exp_node->calculate = $1;
            $$ = scalar_exp_node;
        }
    | column
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_COLUMN;
            scalar_exp_node->column = $1;
            $$ = scalar_exp_node;
        }
    | function
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_FUNCTION;
            scalar_exp_node->function = $1;
            $$ = scalar_exp_node;
        }
    | value_item 
        {
            ScalarExpNode *scalar_exp_node = make_scalar_exp_node();
            scalar_exp_node->type = SCALAR_VALUE;
            scalar_exp_node->value = $1;
            $$ = scalar_exp_node;
        }
    | '(' scalar_exp ')'
        {
            $$ = $2;
        }
    | scalar_exp AS IDENTIFIER
        {
            $1->alias = $3;
            $$ = $1;
        }
    ;
calculate:
    scalar_exp '+' scalar_exp
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_ADD;
            calculate_node->left = $1;
            calculate_node->right = $3;
            $$ = calculate_node;
        }
    | scalar_exp '-' scalar_exp
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_SUB;
            calculate_node->left = $1;
            calculate_node->right = $3;
            $$ = calculate_node;
        }
    | scalar_exp '*' scalar_exp
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_MUL;
            calculate_node->left = $1;
            calculate_node->right = $3;
            $$ = calculate_node;
        }
    | scalar_exp '/' scalar_exp
        {
            CalculateNode *calculate_node = make_calculate_node();
            calculate_node->type = CAL_DIV;
            calculate_node->left = $1;
            calculate_node->right = $3;
            $$ = calculate_node;
        }
    ;
columns:
    column
        {
            List *column_set_node = create_list(NODE_COLUMN);
            append_list(column_set_node, $1);
            $$ = column_set_node;
        }
    | columns ',' column
        {
            $$ = $1;
            append_list($$, $3);
        }
    ;
base_table_element_commalist:
    base_table_element
        {
            List *base_table_element_commalist = create_list(NODE_BASE_TABLE_ELEMENT);
            append_list(base_table_element_commalist, $1);
            $$ = base_table_element_commalist;
        }
    | base_table_element_commalist ',' base_table_element
        {
            append_list($1, $3);
            $$ = $1;
        }
    ;
base_table_element:
    column_def
        {
            $$ = make_base_table_element_node();
            $$->column_def = $1;
            $$->table_contraint_def = NULL;
            $$->type = TELE_COLUMN_DEF;
        }
    | table_contraint_def
        {
            $$ = make_base_table_element_node();
            $$->column_def = NULL;
            $$->table_contraint_def = $1;
            $$->type = TELE_TABLE_CONTRAINT_DEF;
        }
    ;
column_defs:
    column_def
        {
            list *column_def_list = create_list(NODE_COLUMN_DEF_NODE);
            append_list(column_def_list, $1);
            $$ = column_def_list;
        }
    | column_defs ',' column_def
        {
            append_list($1, $3);
            $$ = $1;
        }
    ;
column_def:
    column_def_name data_type array_dim_clause column_def_opt_list
        {
            ColumnDefNode *column_def = make_column_def_node();
            column_def->column = $1;
            column_def->data_type = $2;
            column_def->array_dim = $3;
            column_def->column_def_opt_list = $4;
            $$ = column_def;
        }
    ;
column_def_name_commalist:
    column_def_name
        {
            List *list = create_list(NODE_COLUMN_DEF_NAME);
            append_list(list, $1);
            $$ = list;
        }
    | column_def_name_commalist ',' column_def_name
        {
            append_list($1, $3);
            $$ = $1;
        }
    ;
column_def_name:
    IDENTIFIER
        {
            ColumnDefName *column_def_name = make_column_def_name();
            column_def_name->column = $1;
            $$ = column_def_name;
        }
    ;
data_type:
    INT          
        { 
            $$ = make_data_type_node();
            $$->type = T_INT; 
        }
    | LONG       
        { 
            $$ = make_data_type_node();
            $$->type = T_LONG;  
        }
    | CHAR       
        { 
            $$ = make_data_type_node();
            $$->type = T_CHAR; 
        }
    | VARCHAR '(' INTVALUE ')'
        {
            $$ = make_data_type_node();
            $$->type = T_VARCHAR; 
            $$->len = $3; 
        }
    | STRING     
        { 
            $$ = make_data_type_node();
            $$->type = T_STRING; 
        }
    | BOOL       
        { 
            $$ = make_data_type_node();
            $$->type = T_BOOL; 
        }
    | FLOAT      
        { 
            $$ = make_data_type_node();
            $$->type = T_FLOAT; 
        }  
    | DOUBLE     
        { 
            $$ = make_data_type_node();
            $$->type = T_DOUBLE; 
        }
    | TIMESTAMP  
        { 
            $$ = make_data_type_node();
            $$->type = T_TIMESTAMP; 
        }
    | DATE       
        { 
            $$ = make_data_type_node();
            $$->type = T_DATE; 
        }
    | table 
        {
            $$ = make_data_type_node();
            $$->type = T_REFERENCE;
            $$->table_name = $1;
        }
    ;
array_dim_clause:
    /* empty */
        {
            $$ = 0;
        }
    | '[' ']'
        {
            $$ = 1;
        }
    | array_dim_clause '[' ']'
        {
            $$++;
        }
    ;
column_def_opt_list:
    /* empty */
        {
            $$ = NULL;
        }
    | column_def_opt
        {
            $$ = create_list(NODE_COLUMN_DEF_OPT);
            append_list($$, $1);
        }
    | column_def_opt_list column_def_opt
        {
            append_list($1, $2);
            $$ = $1;
        }
    ;
column_def_opt:
    NOT NULLX
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_NOT_NULL; 
        }
    | UNIQUE
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_UNIQUE; 
        }
    | PRIMARY KEY
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_PRIMARY_KEY; 
        }
    | DEFAULT value_item
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_DEFAULT_VALUE;
            $$->value = $2;
        }
    | DEFAULT NULLX
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_DEFAULT_NULL;
        }
    | COMMENT STRINGVALUE
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_COMMENT;
            $$->comment = $2;
        }
    | CHECK '(' condition ')'
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_CHECK_CONDITION;
            $$->condition = $3;
        }
    | REFERENCES table
        {
            $$ = make_column_def_opt_node();
            $$->opt_type = OPT_REFERENECS;
            $$->refer_table = $2;
        }
    ;
table_contraint_def:
    UNIQUE '(' column_def_name_commalist ')'
        {
            $$ = make_table_contraint_def_node();
            $$->type = TCONTRAINT_UNIQUE;
            $$->column_commalist = $3;
        }
    | PRIMARY KEY '(' column_def_name_commalist ')'
        {
            $$ = make_table_contraint_def_node();
            $$->type = TCONTRAINT_PRIMARY_KEY;
            $$->column_commalist = $4;
        }
    | FOREIGN KEY '(' column_def_name_commalist ')' REFERENCES table
        {
            $$ = make_table_contraint_def_node();
            $$->type = TCONTRAINT_FOREIGN_KEY;
            $$->column_commalist = $4;
            $$->table = $7;
        }
    | CHECK '(' condition ')'
        {
            $$ = make_table_contraint_def_node();
            $$->type = TCONTRAINT_CHECK;
            $$->condition = $3;
        }
    ;
column: 
    IDENTIFIER
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = $1;
            column_node->has_sub_column = false;
            $$ = column_node;
        }
    | '(' IDENTIFIER ')' '.'  column 
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = $2;
            column_node->sub_column = $5;
            column_node->has_sub_column = true;
            $$ = column_node;
        }
    | IDENTIFIER '{' scalar_exp_commalist '}'
        {
            ColumnNode *column_node = make_column_node();
            column_node->column_name = $1;
            column_node->scalar_exp_list = $3;
            column_node->has_sub_column = true;
            $$ = column_node;
        }
    | IDENTIFIER '.' column
        {
            $$ = $3;
            $$->range_variable = $1;
        }
    ;
value_items:
    value_item
        {
            List *value_list = create_list(NODE_VALUE_ITEM);
            append_list(value_list, $1);
            $$ = value_list;
        }
    | value_items ',' value_item
        {
            $$ = $1;
            append_list($$, $3);
        }
    ;
value_item:
    atom
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_ATOM;
            node->value.atom = $1;
            $$ = node;
        }
    | NULLX
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_NULL;
            $$ = node;
        }
    | '[' value_items ']'
        {
            ValueItemNode *node = make_value_item_node();
            node->type = V_ARRAY;
            node->value.value_list = $2;
            $$ = node;
        }
    ;
atom:
    INTVALUE
        {
            AtomNode *node = make_atom_node();
            node->value.intval = $1;
            node->type = A_INT;
            $$ = node;
        }
    | BOOLVALUE
        {
            AtomNode *node = make_atom_node();
            node->value.boolval = $1;
            node->type = A_BOOL;
            $$ = node;
        }
    | STRINGVALUE 
        {
            AtomNode *node = make_atom_node();
            node->value.strval = $1;
            node->type = A_STRING;
            $$ = node;
        }
    | FLOATVALUE 
        {
            AtomNode *node = make_atom_node();
            node->value.floatval = $1;
            node->type = A_FLOAT;
            $$ = node;
        }
    | REFERVALUE
        {
            AtomNode *node = make_atom_node();
            node->value.referval = $1;
            node->type = A_REFERENCE;
            $$ = node;
        }
    ;
REFERVALUE:
    /* Directly insert way. */
    '(' value_items ')'
        {
            ReferValue *refer = make_refer_value();
            refer->type = DIRECTLY;
            refer->nest_value_list = $2;
            $$ = refer;
        }
    /* Indirectly fetch already row refer. */
    | REF '(' condition ')' 
        {
            ReferValue *refer = make_refer_value();
            refer->type = INDIRECTLY;
            refer->condition = $3;
            $$ = refer;
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
    | assignments ',' assignment
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
condition: 
    condition OR condition
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_OR;
            condition->left = $1;
            condition->right = $3;
            $$ = condition;
        }
    | condition AND condition
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_AND;
            condition->left = $1;
            condition->right = $3;
            $$ = condition;
        }
    | '(' condition ')'
        {
            $$ = $2;
        }
    | predicate
        {
            ConditionNode *condition = make_condition_node();
            condition->conn_type = C_NONE;
            condition->predicate = $1;
            $$ = condition;
        }
    ;
predicate:
    comparison_predicate
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_COMPARISON;
            predicate->comparison = $1;
            $$ = predicate;
        }
    | like_predicate
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_LIKE;
            predicate->like = $1;
            $$ = predicate;
        }
    | in_predicate
        {
            PredicateNode *predicate = make_predicate_node();
            predicate->type = PRE_IN;
            predicate->in = $1;
            $$ = predicate;
        }
    ;
comparison_predicate:
    column compare scalar_exp
        {
            ComparisonNode *comparison_node = make_comparison_node();
            comparison_node->column = $1;
            comparison_node->type = $2;
            comparison_node->value = $3;
            $$ = comparison_node;
        }
    ;
like_predicate:
    column LIKE value_item
        {
            LikeNode *like_node = make_like_node();
            like_node->column = $1;
            like_node->value = $3;
            $$ = like_node;
        }
    ;
in_predicate: 
    column IN '(' value_items ')'
        {
            InNode *in_node = make_in_node();
            in_node->column = $1;
            in_node->value_list = $4;
            $$ = in_node;
        }
    ;
opt_limit:  
    // empty
        {
            $$ = NULL;
        }
    | LIMIT INTVALUE
        {
            LimitNode *limit_node = make_limit_node();
            limit_node->start = 0;
            limit_node->end = $2;
            $$ = limit_node;
        }
    | LIMIT INTVALUE ',' INTVALUE
        {
            LimitNode *limit_node = make_limit_node();
            limit_node->start = $2;
            limit_node->end = $4;
            $$ = limit_node;
        }
    ;
compare: 
    EQ      { $$ = O_EQ; }
    | NE    { $$ = O_NE; }
    | GT    { $$ = O_GT; }
    | GE    { $$ = O_GE; }
    | LT    { $$ = O_LT; }
    | LE    { $$ = O_LE; }
    ;
function:       
    MAX '(' non_all_function_value ')'
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MAX;
            function_node->value = $3;
            $$ = function_node;
        }
    | MIN '(' non_all_function_value ')'
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_MIN;
            function_node->value = $3;
            $$ = function_node;
        }
    | COUNT '(' function_value ')'
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_COUNT;
            function_node->value = $3;
            $$ = function_node;
        }
    | SUM '(' function_value ')'
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_SUM;
            function_node->value = $3;
            $$ = function_node;
        }
    | AVG '(' function_value ')'
        {
            FunctionNode *function_node = make_function_node();        
            function_node->type = F_AVG;
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
    | '*'
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
    | ';' NL
    ;
%%
