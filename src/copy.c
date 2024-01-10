#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
#include "copy.h"
#include "free.h"
#include "data.h"
#include "index.h"
#include "meta.h"
#include "asserts.h"
#include "common.h"
#include "misc.h"
#include "mmu.h"

/* Copy value. */
void *copy_value(void *value, DataType data_type, MetaColumn *meta_column) {
    switch(data_type) {
        case T_BOOL: {
            bool *new_val = db_malloc(sizeof(bool), SDT_BOOL);
            memcpy(new_val, value, sizeof(bool));
            return new_val;
        }
        case T_INT: {
            int32_t *new_val = db_malloc(sizeof(int32_t), SDT_INT);
            memcpy(new_val, value, sizeof(int32_t));
            return new_val;
        }
        case T_LONG: {
            int64_t *new_val = db_malloc(sizeof(int64_t), SDT_INT);
            memcpy(new_val, value, sizeof(int64_t));
            return new_val;
        }
        case T_FLOAT: {
            float *new_val = db_malloc(sizeof(float), SDT_FLOAT);
            memcpy(new_val, value, sizeof(float));
            return new_val;
        }
        case T_DOUBLE: {
            double *new_val = db_malloc(sizeof(double), SDT_DOUBLE);
            memcpy(new_val, value, sizeof(double));
            return new_val;
        }
        case T_DATE:
        case T_TIMESTAMP: {
            time_t *new_val = db_malloc(sizeof(time_t), SDT_TIME_T);
            memcpy(new_val, value, sizeof(time_t));
            return new_val;
        }
        case T_CHAR:
        case T_STRING: {
            if (meta_column) {
                char *new_value = db_malloc(meta_column->column_length, SDT_STRING);
                memcpy(new_value, value, meta_column->column_length);
                return new_value;
            } else {
                char *new_value = db_malloc(strlen(value) + 1, SDT_STRING);
                memset(new_value, 0, strlen(value) + 1);
                strcpy(new_value, value);
                return new_value;
            }
        }
        case T_REFERENCE: {
            Refer *refer = db_malloc(sizeof(Refer), SDT_REFER);
            memcpy(refer, value, sizeof(Refer));
            return refer;
        }
        default:
            fatal("Not supported data type.");
    }    
}

/* Copy Key value pair. */
KeyValue *copy_key_value(KeyValue *key_value, MetaTable *meta_table) {
    
    /* check */
    if (key_value == NULL)
        return NULL;

    /* copy key value */
    KeyValue *key_value_copy = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value_copy->key = db_malloc(strlen(key_value->key) + 1, SDT_STRING);
    strcpy(key_value_copy->key, key_value->key);
    MetaColumn *meta_column = get_meta_column_by_name(meta_table, key_value->key); 

    /*Meta column may be null, in fact, key aggregate function, key is min, max, sum, avg ect. there is no meta column. */
    key_value_copy->value = copy_value(key_value->value, key_value->data_type, meta_column);
    key_value_copy->data_type = key_value->data_type;

    return key_value_copy;
}

/* Copy row. */
Row *copy_row(Row *row) {
    /* check */
    if (row == NULL)
        return NULL;
    Table *table = open_table(row->table_name);
    if (table == NULL)
        return NULL;

    /* copy row */
    Row *row_copy = db_malloc(sizeof(Row), SDT_ROW);
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    row_copy->key = copy_value(row->key, primary_meta_column->column_type, primary_meta_column);
    row_copy->column_len = row->column_len;
    row_copy->table_name = db_malloc(strlen(row->table_name) + 1, SDT_STRING);
    strcpy(row_copy->table_name, row->table_name);
    row_copy->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);

    int i;
    for(i = 0; i < row->column_len; i++) {
        row_copy->data[i] = copy_key_value(row->data[i], table->meta_table);
    }

    return row_copy;
}

/* Copy row igonore system reserved columns. */
Row *copy_row_without_reserved(Row *row) {
    /* check */
    if (row == NULL)
        return NULL;
    Table *table = open_table(row->table_name);
    if (table == NULL)
        return NULL;

    /* copy row. */
    Row *row_copy = db_malloc(sizeof(Row), SDT_ROW);
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    row_copy->key = copy_value(row->key, primary_meta_column->column_type, primary_meta_column);
    row_copy->table_name = db_malloc(strlen(row->table_name) + 1, SDT_STRING);
    strcpy(row_copy->table_name, row->table_name);
    row_copy->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_STRING);

    int i, j;
    for(i = 0, j = 0; i < row->column_len; i++) {
        /* copy key value. */
        KeyValue *key_value_copy = copy_key_value(*(row->data + i), table->meta_table);
        
        /* Skip system reserved columns. */
        MetaColumn *meta_column = get_all_meta_column_by_name(table->meta_table, key_value_copy->key);
        if (meta_column && meta_column->sys_reserved) {
            free_key_value(key_value_copy); /* Not need any more. */
            continue;
        }

        row_copy->data[j++] = key_value_copy;
        row_copy->column_len++;
    }

    return row_copy;
}

/* Copy refer. */
Refer *copy_refer(Refer *refer) {
    if (refer == NULL) return NULL;
    Refer *copy_refer = db_malloc(sizeof(Refer), SDT_REFER);
    memset(copy_refer, 0, sizeof(Refer));
    strcpy(copy_refer->table_name, refer->table_name);
    copy_refer->page_num = refer->page_num;
    copy_refer->cell_num = refer->cell_num;
    return copy_refer;
}

/* Copy meta column. */
MetaColumn *copy_meta_column(MetaColumn *meta_column) {
    if (meta_column == NULL)
        return NULL;
    MetaColumn *meta_column_copy = db_malloc(sizeof(MetaColumn), SDT_META_COLUMN);
    meta_column_copy->is_primary = meta_column->is_primary;
    meta_column_copy->column_type = meta_column->column_type;
    meta_column_copy->column_length = meta_column->column_length;
    meta_column_copy->sys_reserved = meta_column->sys_reserved;
    strcpy(meta_column_copy->column_name, meta_column->column_name);
    strcpy(meta_column_copy->table_name, meta_column->table_name);
    return meta_column_copy;
} 

/* Copy column node. */
ColumnNode *copy_column_node(ColumnNode *column_node) {
    if (column_node == NULL)
        return NULL;
    ColumnNode *column_node_copy = db_malloc(sizeof(ColumnNode), SDT_COLUMN_NODE);
    column_node_copy->has_sub_column = column_node->has_sub_column;
    if (column_node_copy->sub_column_name) {
        column_node_copy->sub_column_name = strdup(column_node->sub_column_name);
    }
    column_node_copy->column_name = strdup(column_node->column_name);
    return column_node_copy;
}

/* Copy column set node. */
ColumnSetNode *copy_column_set_node(ColumnSetNode *column_set_node) {
    if (column_set_node == NULL)
        return NULL;
    ColumnSetNode *column_set_node_copy = db_malloc(sizeof(ColumnSetNode), SDT_COLUMN_SET_NODE);
    column_set_node_copy->size = column_set_node->size;
    column_set_node_copy->columns = db_malloc(sizeof(ColumnNode *) * column_set_node_copy->size, SDT_POINTER);
    for (uint32_t i = 0; i < column_set_node_copy->size; i++) {
        *(column_set_node_copy->columns + i) = copy_column_node(*(column_set_node->columns + i));
    }
    return column_set_node_copy;
}

/* Copy value item node. */
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node == NULL)
        return NULL;
    ValueItemNode *value_item_node_copy = db_malloc(sizeof(ValueItemNode), SDT_VALUE_ITEM_NODE);
    value_item_node_copy->data_type = value_item_node->data_type;
    switch(value_item_node->data_type) {
        case T_CHAR:
        case T_STRING:
            value_item_node_copy->s_value = strdup(value_item_node->s_value);
            break;
        case T_INT:
        case T_LONG:
            value_item_node_copy->i_value = value_item_node->i_value;
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
        case T_REFERENCE: {
            value_item_node_copy->nest_value_item_set = db_malloc(sizeof(ValueItemSetNode), SDT_VALUE_ITEM_SET_NODE);
            memcpy(value_item_node_copy->nest_value_item_set, value_item_node->nest_value_item_set, sizeof(ValueItemSetNode));
            break;
        }
    }
    return value_item_node_copy;
}

/*Copy function value node. */
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node) {
    if (function_value_node == NULL)
        return NULL;
    FunctionValueNode *function_value_node_copy = db_malloc(sizeof(FunctionValueNode), SDT_FUNCTION_VALUE_NODE);
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

/* Copy function node. */
FunctionNode *copy_function_node(FunctionNode *function_node) {
    if (function_node == NULL)
        return NULL;
    FunctionNode *function_node_copy = db_malloc(sizeof(FunctionNode), SDT_FUNCTION_NODE);
    function_node_copy->function_type = function_node->function_type;
    function_node_copy->value = copy_function_value_node(function_node->value);
    return function_node_copy;
}

/* Copy condition node. */
ConditionNode *copy_condition_node(ConditionNode *condition_node) {
    if (condition_node == NULL)
        return NULL;
    ConditionNode *condition_node_copy = db_malloc(sizeof(ConditionNode), SDT_CONDITION_NODE);
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

/* Copy select items node. */
SelectItemsNode *copy_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node == NULL)
        return NULL;
    SelectItemsNode *select_items_node_copy = db_malloc(sizeof(SelectItemsNode), SDT_SELECT_ITEMS_NODE);
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

/* Copy query param. */
QueryParam *copy_query_param(QueryParam *query_param) {
    if (query_param == NULL)
        return NULL;
    QueryParam *query_param_copy = db_malloc(sizeof(QueryParam), SDT_QUERY_PARAM);
    query_param_copy->table_name = strdup(query_param->table_name);
    query_param_copy->condition_node = copy_condition_node(query_param->condition_node); 
    query_param_copy->select_items = copy_select_items_node(query_param->select_items);
    return query_param_copy;
}

/* Copy a dymamic memory block */
void *copy_block(void *value, size_t size) {
    void * copy_value = db_malloc(size, SDT_VOID);
    memcpy(copy_value, value, size);
    return copy_value;
}
