#include "copy.h"
#include "data.h"
#include "common.h"
#include "misc.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Copy value
void *copy_value(void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
        case T_INT:
        case T_FLOAT:
        case T_DOUBLE:
        case T_CHAR:
            return value;
        case T_STRING:
            {
                char *new_value = malloc(strlen(value) + 1);
                memset(new_value, 0, strlen(value) + 1);
                strcpy(new_value, value);
                return new_value;
            }
        case T_DATE:
        case T_TIMESTAMP:
            fatal("Not implement yet.");
        default:
            return NULL;
    }    
}

// Copy Key value pair
KeyValue *copy_key_value(KeyValue *key_value) {
    if (key_value == NULL)
        return NULL;
    KeyValue *key_value_copy = malloc(sizeof(KeyValue));
    if (key_value_copy == NULL)
        MALLOC_ERROR;
    memset(key_value_copy, 0, sizeof(KeyValue));
    key_value_copy->key = malloc(strlen(key_value->key) + 1);
    strcpy(key_value_copy->key, key_value->key);
    key_value_copy->value = copy_value(key_value->value, key_value->data_type);
    key_value_copy->data_type = key_value->data_type;
    return key_value_copy;
}

//Copy row
Row *copy_row(Row *row) {
    if (row == NULL)
        return NULL;
    Row *row_copy = malloc(sizeof(Row));
    if (row_copy == NULL)
        MALLOC_ERROR;
    memset(row_copy, 0, sizeof(Row));
    row_copy->key = row->key;
    row_copy->column_len = row->column_len;
    row_copy->table_name = malloc(strlen(row->table_name) + 1);
    strcpy(row_copy->table_name, row->table_name);
    row_copy->data = malloc(sizeof(KeyValue *) * row->column_len);
    for(uint32_t i = 0; i < row->column_len; i++) {
        *(row_copy->data + i) = copy_key_value(*(row->data + i));
    }
    return row_copy;
}

//Copy meta column.
MetaColumn *copy_meta_column(MetaColumn *meta_column) {
    if (meta_column == NULL)
        return NULL;
    MetaColumn *meta_column_copy = malloc(sizeof(MetaColumn));
    if (meta_column_copy == NULL)
        MALLOC_ERROR;
    memset(meta_column_copy, 0, sizeof(MetaColumn));
    meta_column_copy->is_primary = meta_column->is_primary;
    meta_column_copy->column_type = meta_column->column_type;
    meta_column_copy->column_length = meta_column->column_length;
    for(uint32_t i = 0; i < MAX_COLUMN_NAME_LEN; i++) {
        meta_column_copy->column_name[i] = meta_column->column_name[i];
    }
    return meta_column_copy;
} 

//Copy int value node.
IntValueNode *copy_int_value_node(IntValueNode *int_value_node) {
    if (int_value_node == NULL)
        return NULL;
    IntValueNode *int_value_node_copy = malloc(sizeof(IntValueNode));
    if (int_value_node_copy == NULL)
        MALLOC_ERROR;
    memset(int_value_node_copy, 0, sizeof(IntValueNode));
    int_value_node_copy->i_value = int_value_node->i_value;
    return int_value_node_copy;
}

//Copy bool value node.
BoolValueNode *copy_bool_value_node(BoolValueNode *bool_value_node) {
    if (bool_value_node == NULL)
        return NULL;
    BoolValueNode *bool_value_node_copy = malloc(sizeof(BoolValueNode));
    if (bool_value_node_copy == NULL)
        MALLOC_ERROR;
    memset(bool_value_node_copy, 0, sizeof(BoolValueNode));
    bool_value_node_copy->b_value = bool_value_node->b_value;
    return bool_value_node_copy;
}

//Copy string value node.
StringValueNode *copy_string_value_node(StringValueNode *string_value_node) {
    if (string_value_node == NULL)
        return NULL;
    StringValueNode *string_value_node_copy = malloc(sizeof(StringValueNode));
    if (string_value_node_copy == NULL)
        MALLOC_ERROR;
    memset(string_value_node_copy, 0, sizeof(StringValueNode));
    string_value_node_copy->s_value = malloc(strlen(string_value_node->s_value) + 1);
    strcpy(string_value_node_copy->s_value, string_value_node->s_value);
    return string_value_node_copy;
}

//Copy ident node.
IdentNode *copy_ident_node(IdentNode *ident_node) {
    if (ident_node == NULL)
        return NULL;
    IdentNode *ident_node_copy = malloc(sizeof(IdentNode));
    if (ident_node_copy == NULL)
        MALLOC_ERROR;
    memset(ident_node_copy, 0, sizeof(IdentNode));
    ident_node_copy->name = malloc(strlen(ident_node->name) + 1);
    memset(ident_node_copy->name, 0, strlen(ident_node->name) + 1);
    strcpy(ident_node_copy->name, ident_node->name);
    return ident_node_copy;
}

//Copy ident set node.
IdentSetNode *copy_ident_set_node(IdentSetNode *ident_set_node) {
    IdentSetNode *ident_set_node_copy = malloc(sizeof(IdentSetNode));
    if (ident_set_node == NULL)
        MALLOC_ERROR;
    ident_set_node_copy->num = ident_set_node->num;
    ident_set_node_copy->all_column = ident_set_node->all_column;
    ident_set_node_copy->ident_node = malloc(sizeof(IdentNode *) * ident_set_node->num);
    if (ident_set_node->all_column == false) {
        for (uint32_t i = 0; i < ident_set_node_copy->num; i++) {
            *(ident_set_node_copy->ident_node + i) = copy_ident_node(*(ident_set_node->ident_node + i));
        }
    }
    return ident_set_node_copy;
}

//Copy value item node.
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node == NULL)
        return NULL;
    ValueItemNode *value_item_node_copy = malloc(sizeof(ValueItemNode));
    if (value_item_node_copy == NULL)
        MALLOC_ERROR;
    memset(value_item_node_copy, 0, sizeof(ValueItemNode));
    value_item_node_copy->data_type = value_item_node->data_type;
    switch(value_item_node->data_type) {
        case T_INT:
            value_item_node_copy->i_value = copy_int_value_node(value_item_node->i_value);
            break;
        case T_STRING:
            value_item_node_copy->s_value = copy_string_value_node(value_item_node->s_value);
            break;
        case T_BOOL:
            value_item_node_copy->b_value = copy_bool_value_node(value_item_node->b_value);
            break;
        default:
            fatal("Not implement yet.");
    }
    return value_item_node_copy;
}

//Copy function value node.
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node) {
    if (function_value_node == NULL)
        return NULL;
    FunctionValueNode *function_value_node_copy = malloc(sizeof(FunctionValueNode));
    if (function_value_node_copy == NULL)
        MALLOC_ERROR;
    memset(function_value_node_copy, 0, sizeof(FunctionValueNode));
    function_value_node_copy->value_type = function_value_node->value_type;
    switch(function_value_node->value_type) {
        case V_INT:
            function_value_node_copy->i_value = copy_int_value_node(function_value_node->i_value);
            break;
        case V_IDENT:
            function_value_node_copy->id_value = copy_ident_node(function_value_node->id_value);
            break;
        case V_ALL:
            break;
    }
    return function_value_node_copy;
}

//Copy function node.
FunctionNode *copy_function_node(FunctionNode *function_node) {
    if (function_node == NULL)
        return NULL;
    FunctionNode *function_node_copy = malloc(sizeof(FunctionNode));
    if (function_node_copy == NULL)
        MALLOC_ERROR;
    memset(function_node_copy, 0, sizeof(FunctionNode));
    function_node_copy->function_type = function_node->function_type;
    function_node_copy->value = copy_function_value_node(function_node->value);
    return function_node_copy;
}

//Copy opr node.
OprNode *copy_opr_node(OprNode *opr_node) {
    if (opr_node == NULL)
        return NULL;
    OprNode *opr_node_copy = malloc(sizeof(OprNode));
    if (opr_node_copy == NULL)
        MALLOC_ERROR;
    memset(opr_node_copy, 0, sizeof(OprNode));
    opr_node_copy->op_type = opr_node->op_type;
    return opr_node_copy;
}

//Copy conn node.
ConnNode *copy_conn_node(ConnNode *conn_node) {
    if (conn_node == NULL)
        return NULL;
    ConnNode *conn_node_copy = malloc(sizeof(ConnNode));
    if (conn_node_copy == NULL)
        MALLOC_ERROR;
    memset(conn_node_copy, 0, sizeof(ConnNode));
    conn_node_copy->conn_type = conn_node->conn_type;
    return conn_node_copy;
}

//Copy condition node.
ConditionNode *copy_condition_node(ConditionNode *condition_node) {
    if (condition_node == NULL)
        return NULL;
    ConditionNode *condition_node_copy = malloc(sizeof(ConditionNode));
    if (condition_node_copy == NULL)
        MALLOC_ERROR;
    memset(condition_node_copy, 0, sizeof(ConditionNode));
    condition_node_copy->type = condition_node->type;
    if (condition_node->left)
        condition_node_copy->left = copy_condition_node(condition_node->left);
    if (condition_node->right)
        condition_node_copy->right = copy_condition_node(condition_node->right);
    if (condition_node->next)
        condition_node_copy->next = copy_condition_node(condition_node->next);
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            condition_node_copy->conn_node = copy_conn_node(condition_node->conn_node);
            break;
        case EXEC_CONDITION:
            condition_node_copy->column = copy_ident_node(condition_node->column);
            condition_node_copy->opr_node = copy_opr_node(condition_node->opr_node);
            condition_node_copy->compare = copy_value_item_node(condition_node->compare);
            condition_node_copy->conn_node = copy_conn_node(condition_node->conn_node);
            break;
    }
    return condition_node_copy;
}

//Copy select items node.
SelectItemsNode *copy_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node == NULL)
        return NULL;
    SelectItemsNode *select_items_node_copy = malloc(sizeof(SelectItemsNode));
    if (select_items_node_copy == NULL)
        MALLOC_ERROR;
    memset(select_items_node_copy, 0, sizeof(SelectItemsNode));
    select_items_node_copy->is_function_node = select_items_node->is_function_node;
    select_items_node_copy->function_node = copy_function_node(select_items_node->function_node);
    select_items_node_copy->ident_set_node = copy_ident_set_node(select_items_node->ident_set_node);
    return select_items_node_copy;
}

//Copy query param.
QueryParam *copy_query_param(QueryParam *query_param) {
    if (query_param == NULL)
        return NULL;
    QueryParam *query_param_copy = malloc(sizeof(QueryParam));
    if (query_param_copy == NULL)
        MALLOC_ERROR;
    memset(query_param_copy, 0, sizeof(QueryParam));
    query_param_copy->table_name = malloc(strlen(query_param->table_name) + 1);
    memset(query_param_copy->table_name, 0, strlen(query_param->table_name) + 1);
    strcpy(query_param_copy->table_name, query_param->table_name);
    query_param_copy->condition_node = copy_condition_node(query_param->condition_node); 
    query_param_copy->select_items = copy_select_items_node(query_param->select_items);
    return query_param_copy;
}
