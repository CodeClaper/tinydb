#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "intpr.h"
#include "data.h"
#include "mmu.h"
#include "free.h"


//****************************** allocate ***************************************

// make a function value node.
FunctionValueNode *make_function_value_node() {
    FunctionValueNode *function_value_node = db_malloc2(sizeof(FunctionValueNode), "FunctionValueNode");
    return function_value_node;
}

// make a functon node
FunctionNode *make_function_node() {
    FunctionNode *function_node = db_malloc2(sizeof(FunctionNode), "FunctionNode");
    return function_node;
}

// make a select items node.
SelectItemsNode *make_select_items_node() {
    SelectItemsNode *select_items_node = db_malloc2(sizeof(SelectItemsNode), "SelectItemsNode");
    return select_items_node;
}

// make a column node.
ColumnNode *make_column_node() {
    ColumnNode *column_node = db_malloc2(sizeof(ColumnNode), "ColumnNode");
    return column_node;
}

// make a column set node.
ColumnSetNode *make_column_set_node() {
    ColumnSetNode *column_set_node = db_malloc2(sizeof(ColumnSetNode), "ColumnSetNode");
    column_set_node->size = 0;
    column_set_node->columns = db_malloc2(0, "ColumnSetNode.columns");
    return column_set_node;
}

// add column node to set.
void add_column_to_set(ColumnSetNode *column_set_node, ColumnNode *column_node) {
    column_set_node->columns = db_realloc(column_set_node->columns, sizeof(ColumnNode *) * (column_set_node->size + 1));
    *(column_set_node->columns + column_set_node->size) = column_node;
    column_set_node->size++;
}

// make a value item node.
ValueItemNode *make_value_item_node() {
    ValueItemNode *value_item_node = db_malloc2(sizeof(ValueItemNode), "ValueItemNode");
    return value_item_node;
}

ValueItemSetNode *make_value_item_set_node() {
    ValueItemSetNode *node = db_malloc2(sizeof(ValueItemSetNode), "ValueItemSetNode");
    node->value_item_node = db_malloc2(0, "ValueItemSetNode.value_item_node");
    node->num = 0;
    return node;
}

// add value item into set.
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node) {
    node->value_item_node = db_realloc(node->value_item_node, sizeof(ValueItemNode *) * (node->num + 1));
    *(node->value_item_node + node->num) = value_item_node;
    node->num++;
}


// make a condition node.
ConditionNode *make_cond_node() {
    ConditionNode *cond_node = db_malloc2(sizeof(ConditionNode), "ConditionNode");
    return cond_node;
}

// make an assignment node.
AssignmentNode *make_assignment_node() {
    AssignmentNode *assignment_node = db_malloc2(sizeof(AssignmentNode), "AssignmentNode");
    return assignment_node;
}


// make an assignment set node.
AssignmentSetNode *make_assignment_set_node() {
    AssignmentSetNode *assignment_set_node = db_malloc2(sizeof(AssignmentSetNode), "AssignmentSetNode");
    assignment_set_node->assignment_node = db_malloc2(0, "AssignmentSetNode.assignment_set_node");
    assignment_set_node->num = 0;
    return assignment_set_node;
}

// add assignment to set.
void add_assignment_to_set(AssignmentSetNode *assignment_set_node, AssignmentNode *assignment_node) {
    assignment_set_node->assignment_node = db_realloc(assignment_set_node->assignment_node, sizeof(AssignmentNode *) * (assignment_set_node->num + 1));
    *(assignment_set_node->assignment_node + assignment_set_node->num) = assignment_node; 
    assignment_set_node->num++;
}

// make a column def node.
ColumnDefNode *make_column_def_node() {
    ColumnDefNode *column_def_node = db_malloc2(sizeof(ColumnDefNode), "ColumnDefNode");
    return column_def_node;
}

// make a column def set node.
ColumnDefSetNode *make_column_def_set_node() {
    ColumnDefSetNode *column_def_set_node = db_malloc2(sizeof(ColumnDefSetNode), "ColumnDefSetNode");
    column_def_set_node->column_defs = db_malloc2(0, "ColumnDefSetNode.column_defs");
    column_def_set_node->size = 0;
    return column_def_set_node;
}

// add column def node to set.
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node) {
    columns_def_set_node->column_defs = db_realloc(columns_def_set_node->column_defs, sizeof(ColumnDefNode *) * (columns_def_set_node->size + 1));
    *(columns_def_set_node->column_defs + columns_def_set_node->size) = column_def_node;
    columns_def_set_node->size++;
}

// make a primary key node.
PrimaryKeyNode *make_primary_key_node() {
    PrimaryKeyNode *primary_key_node = db_malloc2(sizeof(PrimaryKeyNode), "PrimaryKeyNode");
    return primary_key_node;
}

// make a select node.
SelectNode *make_select_node() {
    SelectNode *select_node = db_malloc2(sizeof(SelectNode), "SelectNode");
    return select_node;
}

// make an insert node.
InsertNode *make_insert_node() {
    InsertNode *insert_node = db_malloc2(sizeof(InsertNode), "InsertNode");
    return insert_node;
}

// make an update node.
UpdateNode *make_update_node() {
    UpdateNode *update_node = db_malloc2(sizeof(UpdateNode), "UpdateNode");
    return update_node;
}

// make delete node.
DeleteNode *make_delete_node() {
    DeleteNode *delete_node = db_malloc2(sizeof(DeleteNode), "DeleteNode");
    return delete_node;
}

// make a create table node.
CreateTableNode *make_create_table_node() {
    CreateTableNode *create_table_node = db_malloc2(sizeof(CreateTableNode), "CreateTableNode");
    return create_table_node;
}

/* Make a DropTableNode. */
DropTableNode *make_drop_table_node() {
    DropTableNode *drop_table_node = db_malloc2(sizeof(DropTableNode), "DropTableNode");
    return drop_table_node;
}

// make a describe node.
DescribeNode *make_describe_node() {
    DescribeNode *describe_node = db_malloc2(sizeof(DescribeNode), "DescribeNode");
    return describe_node;
}

// make a show table node.
ShowNode *make_show_node(ShowNodeType type) {
    ShowNode *show_node = db_malloc2(sizeof(ShowNode), "ShowNode");
    show_node->type = type;
    return show_node;
}

// make an ast node.
ASTNode *make_ast_node() {
    ASTNode *ast_node = db_malloc2(sizeof(ASTNode), "ASTNode");
    return ast_node;
}

