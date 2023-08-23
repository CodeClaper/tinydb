#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "intpr.h"

static ASTNode *root = NULL;

// make a const node.
ConstNode *make_const_node(int i) {
    ConstNode *const_node = malloc(sizeof(ConstNode));
    const_node->i_value = i;
    return const_node;
}
// make an ident node.
IdentNode *make_ident_node(char *s) {
    IdentNode *ident_node = malloc(sizeof(IdentNode));
    ident_node->name = malloc(MAX_COLUMN_NAME_LEN);
    memset(ident_node->name, 0, MAX_COLUMN_NAME_LEN);
    strcpy(ident_node->name, s);
    return ident_node;
}

// make an ident set node.
IdentSetNode *make_ident_set_node() {
    IdentSetNode *ident_set_node = malloc(sizeof(IdentSetNode));
    ident_set_node->num = 0;
    ident_set_node->ident_node = malloc(0);
    return ident_set_node;
}

// add a new ident node to set
void add_ident(IdentSetNode *ident_set_node, IdentNode *ident_node) {
    *(ident_set_node->ident_node + ident_set_node->num) = ident_node;
    ident_set_node->num ++;
}

// make a from item node.
FromItemNode *make_from_item_node() {
    FromItemNode *from_item_node = malloc(sizeof(FromItemNode));
    return from_item_node;
}

// make a select items node.
SelectItemsNode *make_select_items_node() {
    SelectItemsNode *select_items_node = malloc(sizeof(SelectItemsNode));
    return select_items_node;
}

// make a column set node.
ColumnSetNode *make_column_set_node() {
    ColumnSetNode *column_set_node = malloc(sizeof(ColumnSetNode));
    return column_set_node;
}

// make a value item node.
ValueItemNode *make_value_item_node() {
    ValueItemNode *value_item_node = malloc(sizeof(ValueItemNode));
    return value_item_node;
}

ValueItemSetNode *make_value_item_set_node() {
    ValueItemSetNode *node = malloc(sizeof(ValueItemSetNode));
    node->value_item_node = malloc(0);
    node->num = 0;
    return node;
}
// add value item into set.
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node) {
    *(node->value_item_node + node->num) = value_item_node;
    node->num++;
}


// make a condition node.
ConditionNode *make_cond_node() {
    ConditionNode *cond_node = malloc(sizeof(ConditionNode));
    return cond_node;
}

// make a operator node.
OprNode *make_opr_node(OpType op_type) {
    OprNode *opr_node = malloc(sizeof(OprNode));
    opr_node->op_type = op_type;
    return opr_node;
}

// make a connnection node.
ConnNode *make_conn_node(ConnType conn_type) {
    ConnNode *conn_node = malloc(sizeof(ConnNode));
    conn_node->conn_type = conn_type;
    return conn_node;
}

// make a select node.
SelectNode *make_select_node() {
    SelectNode *select_node = malloc(sizeof(SelectNode));
    return select_node;
}

// make an insert node.
InsertNode *make_insert_node() {
    InsertNode *insert_node = malloc(sizeof(InsertNode));
    return insert_node;
}

void graph(SelectNode *select_node) {
    FromItemNode *from_item_node = select_node->from_item_node;
    SelectItemsNode *select_items_node = select_node->select_items_node;
    printf("table name == '%s'\n", from_item_node->table->name);
    IdentSetNode *ident_set_node = select_items_node->ident_set_node;
    for(int i = 0; i < ident_set_node->num; i++) {
        IdentNode *ident_node = *(ident_set_node->ident_node + i);
        printf("column[%d] === '%s'\t", i, ident_node->name);
    }
    printf("\n");
}

void set_select_ast_node(SelectNode *select_node) {
    root = malloc(sizeof(ASTNode));
    root->statement_type = SELECT_STMT;
    root->select_node = select_node;
}

void set_insert_ast_node(InsertNode *insert_node) {
    root = malloc(sizeof(InsertNode));
    root->statement_type = INSERT_STMT;
    root->insert_node = insert_node;
}

ASTNode *get_ast_node() {
    return root;
}

void free_select_ast_node(SelectNode *select_node) {
    
}

void free_insert_ast_node(InsertNode *insert_node) {

}

void free_ast_node(ASTNode *node) {
    switch(node->statement_type) {
        case SELECT_STMT:
            free_select_ast_node(node->select_node);
            break;
        case INSERT_STMT:
            free_insert_ast_node(node->insert_node);
            break;
        case UPDATE_STMT:
        case DELETE_STMT:
            break;
        
    }
    free(node);
}
