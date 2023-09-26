#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "intpr.h"


static ASTNode *root = NULL;

//****************************** allocate ***************************************

// make an int value node.
IntValueNode *make_int_value_node(int i) {
    IntValueNode *int_value_node = malloc(sizeof(IntValueNode));
    int_value_node->i_value = i;
    return int_value_node;
}

StringValueNode *make_string_value_node(char *s) {
    StringValueNode *string_value_node = malloc(sizeof(StringValueNode));
    string_value_node->s_value = malloc(strlen(s) + 1);
    memset(string_value_node->s_value, 0, strlen(s) + 1);
    strcpy(string_value_node->s_value, strdup(s));
#ifdef DEBUG
    printf("STRINGVALUE: %s\n", string_value_node->s_value);
#endif
    return string_value_node;
}

// make an ident node.
IdentNode *make_ident_node(char *s) {
    IdentNode *ident_node = malloc(sizeof(IdentNode));
    ident_node->name = malloc(strlen(s) + 1);
    memset(ident_node->name, 0, strlen(s) + 1);
    strcpy(ident_node->name, strdup(s));
#ifdef DEBUG
    printf("IDENT: %s\n", ident_node->name);
#endif
    return ident_node;
}

// make an ident set node.
IdentSetNode *make_ident_set_node() {
    IdentSetNode *ident_set_node = malloc(sizeof(IdentSetNode));
    ident_set_node->num = 0;
    ident_set_node->ident_node = malloc(0);
    return ident_set_node;
}

// make a function value node.
FunctionValueNode *make_function_value_node() {
    FunctionValueNode *function_value_node = malloc(sizeof(FunctionValueNode));
    return function_value_node;
}

// make a functon node
FunctionNode *make_function_node() {
    FunctionNode *function_node = malloc(sizeof(FunctionNode));
    return function_node;
}

// add a new ident node to set
void add_ident(IdentSetNode *ident_set_node, IdentNode *ident_node) {
    ident_set_node->ident_node = realloc(ident_set_node->ident_node, sizeof(IdentNode *) * (ident_set_node->num + 1));
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
    node->value_item_node = realloc(node->value_item_node, sizeof(ValueItemNode *) * (node->num + 1));
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

// make a data type node.
DataTypeNode *make_data_type_node(DataType data_type) {
    DataTypeNode *data_type_node = malloc(sizeof(DataTypeNode));
    data_type_node->data_type = data_type;
    return data_type_node;
}

// make a column def node.
ColumnDefNode *make_column_def_node() {
    ColumnDefNode *column_def_node = malloc(sizeof(ColumnDefNode));
    return column_def_node;
}

// make a column def set node.
ColumnDefSetNode *make_column_def_set_node() {
    ColumnDefSetNode *column_def_set_node = malloc(sizeof(ColumnDefSetNode));
    column_def_set_node->column_def = malloc(0);
    column_def_set_node->column_size = 0;
    return column_def_set_node;
}

// add column def node to set.
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node) {
    columns_def_set_node->column_def = realloc(columns_def_set_node->column_def, sizeof(ColumnDefNode *) * (columns_def_set_node->column_size + 1));
    *(columns_def_set_node->column_def + columns_def_set_node->column_size) = column_def_node;
    columns_def_set_node->column_size++;
}

// make a primary key node.
PrimaryKeyNode *make_primary_key_node() {
    PrimaryKeyNode *primary_key_node = malloc(sizeof(PrimaryKeyNode));
    return primary_key_node;
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

// make a create table node.
CreateTableNode *make_create_table_node() {
    CreateTableNode *create_table_node = malloc(sizeof(CreateTableNode));
    return create_table_node;
}

// make a describe node.
DescribeNode *make_describe_node() {
    DescribeNode *describe_node = malloc(sizeof(DescribeNode));
    return describe_node;
}

// make a shwo table node.
ShowTablesNode *make_show_tables_node() {
    ShowTablesNode *show_tables_node = malloc(sizeof(ShowTablesNode));
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

//****************************** free ****************************************

void free_ident_node(IdentNode *ident_node) {
    if (ident_node !=NULL) {
        free(ident_node->name);
        free(ident_node);
    }
}

void free_int_value_node(IntValueNode *int_value_node) {
    if (int_value_node != NULL)
        free(int_value_node);
}

void free_string_value_node(StringValueNode *string_value_node) {
    if (string_value_node != NULL) {
        if (string_value_node != NULL)
            free(string_value_node->s_value);
        free(string_value_node);
    }
}

void free_conn_node(ConnNode *conn_node) {
    if (conn_node != NULL)
        free(conn_node);
}

void free_data_type_node(DataTypeNode *data_type_node) {
    if (data_type_node != NULL)
        free(data_type_node);
}

void free_opr_node(OprNode *opr_node) {
    if (opr_node != NULL)
        free(opr_node);
}

void free_ident_set_node(IdentSetNode *ident_set_node) {
    if (ident_set_node != NULL) {
        for(uint32_t i = 0; i < ident_set_node->num; i++) {
            free(*(ident_set_node->ident_node + i));
        }
        free(ident_set_node->ident_node);
        free(ident_set_node);
    }
}

void free_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node != NULL) {
        free_ident_set_node(select_items_node->ident_set_node);
        free(select_items_node);
    }
}

void free_column_def_node(ColumnDefNode *column_def_node) {
    if (column_def_node != NULL) {
        free_ident_node(column_def_node->column_name);
        free_data_type_node(column_def_node->column_type);
        free(column_def_node);
    }
}

void free_column_def_set_node(ColumnDefSetNode *column_def_set_node) {
    if (column_def_set_node != NULL) {
        for(uint32_t i = 0; i < column_def_set_node->column_size; i++) {
            free_column_def_node(*(column_def_set_node->column_def + i));
        }
        free(column_def_set_node->column_def);
        free(column_def_set_node);
    } 
}

void free_primary_key_node(PrimaryKeyNode *primary_key_node) {
    if (primary_key_node != NULL) {
        free_ident_node(primary_key_node->primary_key_column);
        free(primary_key_node);
    }
}

void free_column_set_node(ColumnSetNode *column_set_node) {
    if (column_set_node != NULL) {
        free_ident_set_node(column_set_node->ident_set_node);
        free(column_set_node);
    }
}

void free_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node != NULL) {
        if (value_item_node->data_type == T_INT)
            free_int_value_node(value_item_node->i_value);
        else if (value_item_node->data_type == T_STRING)
            free_string_value_node(value_item_node->s_value);
        free(value_item_node);
    }
}

void free_value_item_set_node(ValueItemSetNode *value_item_set_node) {
    if (value_item_set_node != NULL) {
        for(uint32_t i = 0; i < value_item_set_node->num; i++) {
            free_value_item_node(*(value_item_set_node->value_item_node + i));
        }
        free(value_item_set_node->value_item_node);
        free(value_item_set_node);
    }
}

void free_from_item_node(FromItemNode *from_item_node) {
    if (from_item_node != NULL) {
        free_ident_node(from_item_node->table);
        free(from_item_node);
    }
}

void free_condition_node(ConditionNode *condition_node) {
    if (condition_node != NULL) {
        free_ident_node(condition_node->column);
        free_opr_node(condition_node->opr_node);
        free_conn_node(condition_node->conn_node);
        free_condition_node(condition_node->next);
        free(condition_node);
    }
}

void free_create_table_node(CreateTableNode *create_table_node) {
    if (create_table_node != NULL) {
        free_ident_node(create_table_node->table_name);
        free_column_def_set_node(create_table_node->column_def_set_node);
        free_primary_key_node(create_table_node->primary_key_node);
        free(create_table_node);
    }
}

void free_select_node(SelectNode *select_node) {
    if (select_node != NULL) {
        free_select_items_node(select_node->select_items_node);
        free_from_item_node(select_node->from_item_node);
        free_condition_node(select_node->condition_node);
        free(select_node);
    }
}

void free_insert_node(InsertNode *insert_node) {
    if (insert_node != NULL) {
        free_from_item_node(insert_node->from_item_node);
        if (!insert_node->if_ignore_columns)
            free_column_set_node(insert_node->columns_set_node);
        free_value_item_set_node(insert_node->value_item_set_node);
        free(insert_node);
    }
}

void free_ast_node(ASTNode *node) {
    switch(node->statement_type) {
        case SELECT_STMT:
            free_select_node(node->select_node);
            break;
        case INSERT_STMT:
            free_insert_node(node->insert_node);
            break;
        case UPDATE_STMT:
        case DELETE_STMT:
            break;
        case CREATE_TABLE_STMT:
            break;
        case DESCRIBE_STMT:
            break;
        case SHOW_TABLES_STMT:
            break;
    }
    free(node);
}
