#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "intpr.h"
#include "free.h"


static ASTNode *root = NULL;

//****************************** allocate ***************************************

// make a function value node.
FunctionValueNode *make_function_value_node() {
    FunctionValueNode *function_value_node = malloc(sizeof(FunctionValueNode));
    memset(function_value_node, 0, sizeof(FunctionValueNode));
    return function_value_node;
}

// make a functon node
FunctionNode *make_function_node() {
    FunctionNode *function_node = malloc(sizeof(FunctionNode));
    memset(function_node, 0, sizeof(FunctionNode));
    return function_node;
}

// make a select items node.
SelectItemsNode *make_select_items_node() {
    SelectItemsNode *select_items_node = malloc(sizeof(SelectItemsNode));
    memset(select_items_node, 0, sizeof(SelectItemsNode));
    return select_items_node;
}

// make a column node.
ColumnNode *make_column_node() {
    ColumnNode *column_node = malloc(sizeof(ColumnNode));
    memset(column_node, 0, sizeof(ColumnNode));
    return column_node;
}

// make a column set node.
ColumnSetNode *make_column_set_node() {
    ColumnSetNode *column_set_node = malloc(sizeof(ColumnSetNode));
    memset(column_set_node, 0, sizeof(ColumnSetNode));
    column_set_node->size = 0;
    column_set_node->columns = malloc(0);
    return column_set_node;
}

// add column node to set.
void add_column_to_set(ColumnSetNode *column_set_node, ColumnNode *column_node) {
    column_set_node->columns = realloc(column_set_node->columns, sizeof(ColumnNode *) * (column_set_node->size + 1));
    *(column_set_node->columns + column_set_node->size) = column_node;
    column_set_node->size++;
}

// make a value item node.
ValueItemNode *make_value_item_node() {
    ValueItemNode *value_item_node = malloc(sizeof(ValueItemNode));
    memset(value_item_node, 0, sizeof(ValueItemNode));
    return value_item_node;
}

ValueItemSetNode *make_value_item_set_node() {
    ValueItemSetNode *node = malloc(sizeof(ValueItemSetNode));
    memset(node, 0, sizeof(ValueItemSetNode));
    node->value_item_node = malloc(0);
    node->num = 0;
    return node;
}

// add value item into set.
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node) {
    node->value_item_node = realloc(node->value_item_node, sizeof(ValueItemNode *) * (node->num + 1));
    *(node->value_item_node + node->num) = value_item_node;
    node->num++;
}


// make a condition node.
ConditionNode *make_cond_node() {
    ConditionNode *cond_node = malloc(sizeof(ConditionNode));
    memset(cond_node, 0, sizeof(ConditionNode));
    return cond_node;
}

// make an assignment node.
AssignmentNode *make_assignment_node() {
    AssignmentNode *assignment_node = malloc(sizeof(AssignmentNode));
    memset(assignment_node, 0, sizeof(AssignmentNode));
    return assignment_node;
}


// make an assignment set node.
AssignmentSetNode *make_assignment_set_node() {
    AssignmentSetNode *assignment_set_node = malloc(sizeof(AssignmentSetNode));
    memset(assignment_set_node, 0, sizeof(AssignmentSetNode));
    assignment_set_node->assignment_node = malloc(0);
    assignment_set_node->num = 0;
    return assignment_set_node;
}

// add assignment to set.
void add_assignment_to_set(AssignmentSetNode *assignment_set_node, AssignmentNode *assignment_node) {
    assignment_set_node->assignment_node = realloc(assignment_set_node->assignment_node, sizeof(AssignmentNode *) * (assignment_set_node->num + 1));
    *(assignment_set_node->assignment_node + assignment_set_node->num) = assignment_node; 
    assignment_set_node->num++;
}

// make a column def node.
ColumnDefNode *make_column_def_node() {
    ColumnDefNode *column_def_node = malloc(sizeof(ColumnDefNode));
    memset(column_def_node, 0, sizeof(ColumnDefNode));
    return column_def_node;
}

// make a column def set node.
ColumnDefSetNode *make_column_def_set_node() {
    ColumnDefSetNode *column_def_set_node = malloc(sizeof(ColumnDefSetNode));
    memset(column_def_set_node, 0, sizeof(ColumnDefSetNode));
    column_def_set_node->column_defs = malloc(0);
    column_def_set_node->size = 0;
    return column_def_set_node;
}

// add column def node to set.
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node) {
    columns_def_set_node->column_defs = realloc(columns_def_set_node->column_defs, sizeof(ColumnDefNode *) * (columns_def_set_node->size + 1));
    *(columns_def_set_node->column_defs + columns_def_set_node->size) = column_def_node;
    columns_def_set_node->size++;
}

// make a primary key node.
PrimaryKeyNode *make_primary_key_node() {
    PrimaryKeyNode *primary_key_node = malloc(sizeof(PrimaryKeyNode));
    memset(primary_key_node, 0, sizeof(PrimaryKeyNode));
    return primary_key_node;
}

// make a select node.
SelectNode *make_select_node() {
    SelectNode *select_node = malloc(sizeof(SelectNode));
    memset(select_node, 0, sizeof(SelectNode)); 
    return select_node;
}

// make an insert node.
InsertNode *make_insert_node() {
    InsertNode *insert_node = malloc(sizeof(InsertNode));
    memset(insert_node, 0, sizeof(InsertNode));
    return insert_node;
}

// make an update node.
UpdateNode *make_update_node() {
    UpdateNode *update_node = malloc(sizeof(UpdateNode));
    memset(update_node, 0, sizeof(UpdateNode));
    return update_node;
}

// make delete node.
DeleteNode *make_delete_node() {
    DeleteNode *delete_node = malloc(sizeof(DeleteNode));
    memset(delete_node, 0, sizeof(DeleteNode));
    return delete_node;
}

// make a create table node.
CreateTableNode *make_create_table_node() {
    CreateTableNode *create_table_node = malloc(sizeof(CreateTableNode));
    memset(create_table_node, 0, sizeof(CreateTableNode));
    return create_table_node;
}

// make a describe node.
DescribeNode *make_describe_node() {
    DescribeNode *describe_node = malloc(sizeof(DescribeNode));
    memset(describe_node, 0, sizeof(DescribeNode));
    return describe_node;
}

// make a shwo table node.
ShowTablesNode *make_show_tables_node() {
    ShowTablesNode *show_tables_node = malloc(sizeof(ShowTablesNode));
    memset(show_tables_node, 0, sizeof(ShowTablesNode));
    return show_tables_node;
}

void set_select_ast_node(SelectNode *select_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = SELECT_STMT;
    root->select_node = select_node;
}

void set_insert_ast_node(InsertNode *insert_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = INSERT_STMT;
    root->insert_node = insert_node;
}

void set_update_ast_node(UpdateNode *update_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = UPDATE_STMT;
    root->update_node = update_node;
}

void set_delete_ast_node(DeleteNode *delete_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = DELETE_STMT;
    root->delete_node = delete_node;
}

void set_create_table_ast_node(CreateTableNode *create_table_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = CREATE_TABLE_STMT;
    root->create_table_node = create_table_node;
}

void set_describe_ast_node(DescribeNode *describe_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = DESCRIBE_STMT;
    root->describe_node = describe_node;
}

void set_show_tables_ast_node(ShowTablesNode *show_table_node) {
    if (root == NULL)
        root = malloc(sizeof(ASTNode));
    else {
        ASTNode *temp = root;
        root = malloc(sizeof(ASTNode));
        free_ast_node(temp);
    }
    root->statement_type = SHOW_TABLES_STMT;
    root->show_tables_node = show_table_node;
}


ASTNode *get_ast_node() {
    return root;
}

