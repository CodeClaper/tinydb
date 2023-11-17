#include <stdint.h>
#include <string.h>
#include "copy.h"
#include "data.h"
#include "common.h"
#include "misc.h"
#include "mem.h"

//Copy value
void *copy_value(void *value, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
        case T_INT:
        case T_FLOAT:
        case T_DOUBLE:
        case T_CHAR:
        case T_TIMESTAMP:
        case T_DATE:
            return value;
        case T_STRING:
            {
                char *new_value = db_malloc2(strlen(value) + 1, "String value");
                strcpy(new_value, value);
                return new_value;
            }
        default:
            return NULL;
    }    
}

// Copy Key value pair
KeyValue *copy_key_value(KeyValue *key_value) {
    if (key_value == NULL)
        return NULL;
    KeyValue *key_value_copy = db_malloc2(sizeof(KeyValue), "KeyValue");
    key_value_copy->key = db_malloc2(strlen(key_value->key) + 1, "Keyvalue.Key");
    strcpy(key_value_copy->key, key_value->key);
    key_value_copy->value = copy_value(key_value->value, key_value->data_type);
    key_value_copy->data_type = key_value->data_type;
    return key_value_copy;
}

//Copy row
Row *copy_row(Row *row) {
    if (row == NULL)
        return NULL;
    Row *row_copy = db_malloc2(sizeof(Row), "Row");
    row_copy->key = row->key;
    row_copy->column_len = row->column_len;
    row_copy->table_name = db_malloc2(strlen(row->table_name) + 1, "Row.table_name");
    strcpy(row_copy->table_name, row->table_name);
    row_copy->data = db_malloc2(sizeof(KeyValue *) * row->column_len, "Row.data");
    for(uint32_t i = 0; i < row->column_len; i++) {
        *(row_copy->data + i) = copy_key_value(*(row->data + i));
    }
    return row_copy;
}

//Copy meta column.
MetaColumn *copy_meta_column(MetaColumn *meta_column) {
    if (meta_column == NULL)
        return NULL;
    MetaColumn *meta_column_copy = db_malloc2(sizeof(MetaColumn), "MetaColumn");
    meta_column_copy->is_primary = meta_column->is_primary;
    meta_column_copy->column_type = meta_column->column_type;
    meta_column_copy->column_length = meta_column->column_length;
    for(uint32_t i = 0; i < MAX_COLUMN_NAME_LEN; i++) {
        meta_column_copy->column_name[i] = meta_column->column_name[i];
    }
    return meta_column_copy;
} 

//Copy column node.
ColumnNode *copy_column_node(ColumnNode *column_node) {
    if (column_node == NULL)
        return NULL;
    ColumnNode *column_node_copy = db_malloc2(sizeof(ColumnNode), "ColumnNode");
    column_node_copy->exist_table_name = column_node->exist_table_name;
    if (column_node_copy->exist_table_name) {
        column_node_copy->table_name = db_malloc2(strlen(column_node->table_name) + 1, "ColumnNode");
        strcpy(column_node_copy->table_name, column_node->table_name);
    }
    column_node_copy->column_name = db_malloc2(strlen(column_node->column_name) + 1, "ColumnNode");
    strcpy(column_node_copy->column_name, column_node->column_name);
    return column_node_copy;
}

//Copy column set node.
ColumnSetNode *copy_column_set_node(ColumnSetNode *column_set_node) {
    if (column_set_node == NULL)
        return NULL;
    ColumnSetNode *column_set_node_copy = db_malloc2(sizeof(ColumnSetNode), "ColumnSetNode");
    column_set_node_copy->size = column_set_node->size;
    column_set_node_copy->columns = db_malloc2(sizeof(ColumnNode *) * column_set_node_copy->size, "ColumnSetNode.columns");
    for (uint32_t i = 0; i < column_set_node_copy->size; i++) {
        *(column_set_node_copy->columns + i) = copy_column_node(*(column_set_node->columns + i));
    }
    return column_set_node_copy;
}

//Copy value item node.
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node == NULL)
        return NULL;
    ValueItemNode *value_item_node_copy = db_malloc2(sizeof(ValueItemNode), "ValueItemNode");
    value_item_node_copy->data_type = value_item_node->data_type;
    switch(value_item_node->data_type) {
        case T_CHAR:
            value_item_node->c_value = value_item_node->c_value;
            break;
        case T_INT:
            value_item_node_copy->i_value = value_item_node->i_value;
            break;
        case T_STRING:
            value_item_node_copy->s_value = strdup(value_item_node->s_value);
            break;
        case T_BOOL:
            value_item_node_copy->b_value = value_item_node->b_value;
            break;
        case T_FLOAT:
            value_item_node_copy->f_value = value_item_node->f_value;
            break;
        case T_DOUBLE:
            value_item_node_copy->d_value = value_item_node->d_value;
            break;
        case T_TIMESTAMP:
        case T_DATE:
            value_item_node_copy->t_value = value_item_node->t_value;
            break;
    }
    return value_item_node_copy;
}

//Copy function value node.
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node) {
    if (function_value_node == NULL)
        return NULL;
    FunctionValueNode *function_value_node_copy = db_malloc2(sizeof(FunctionValueNode), "FunctionValueNode");
    function_value_node_copy->value_type = function_value_node->value_type;
    switch(function_value_node->value_type) {
        case V_INT:
            function_value_node_copy->i_value = function_value_node->i_value;
            break;
        case V_COLUMN:
            function_value_node_copy->column = copy_column_node(function_value_node->column);
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
    FunctionNode *function_node_copy = db_malloc2(sizeof(FunctionNode), "FunctionNode");
    function_node_copy->function_type = function_node->function_type;
    function_node_copy->value = copy_function_value_node(function_node->value);
    return function_node_copy;
}

//Copy condition node.
ConditionNode *copy_condition_node(ConditionNode *condition_node) {
    if (condition_node == NULL)
        return NULL;
    ConditionNode *condition_node_copy = db_malloc2(sizeof(ConditionNode), "ConditionNode");
    condition_node_copy->type = condition_node->type;
    if (condition_node->left)
        condition_node_copy->left = copy_condition_node(condition_node->left);
    if (condition_node->right)
        condition_node_copy->right = copy_condition_node(condition_node->right);
    if (condition_node->next)
        condition_node_copy->next = copy_condition_node(condition_node->next);
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            condition_node_copy->conn_type = condition_node->conn_type;
            break;
        case EXEC_CONDITION:
            condition_node_copy->column = copy_column_node(condition_node->column);
            condition_node_copy->opr_type = condition_node->opr_type;
            condition_node_copy->value = copy_value_item_node(condition_node->value);
            condition_node_copy->conn_type = condition_node->conn_type;
            break;
    }
    return condition_node_copy;
}

//Copy select items node.
SelectItemsNode *copy_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node == NULL)
        return NULL;
    SelectItemsNode *select_items_node_copy = db_malloc2(sizeof(SelectItemsNode), "SelectItemsNode");
    select_items_node_copy->type = select_items_node->type;
    switch(select_items_node_copy->type) {
        case SELECT_FUNCTION:
            select_items_node_copy->function_node = copy_function_node(select_items_node->function_node);
            break;
        case SELECT_COLUMNS:
            select_items_node_copy->column_set_node = copy_column_set_node(select_items_node->column_set_node);
            break;
        case SELECT_ALL:
            break;
    }
    return select_items_node_copy;
}

//Copy query param.
QueryParam *copy_query_param(QueryParam *query_param) {
    if (query_param == NULL)
        return NULL;
    QueryParam *query_param_copy = db_malloc2(sizeof(QueryParam), "QueryParam");
    query_param_copy->table_name = db_malloc2(strlen(query_param->table_name) + 1, "QueryParam.table_name");
    strcpy(query_param_copy->table_name, query_param->table_name);
    query_param_copy->condition_node = copy_condition_node(query_param->condition_node); 
    query_param_copy->select_items = copy_select_items_node(query_param->select_items);
    return query_param_copy;
}

/* Copy a dymamic memory block */
void *copy_block(void *value, size_t size) {
    void * copy_value = db_malloc2(size, "void");
    memcpy(copy_value, value, size);
    return copy_value;
}
