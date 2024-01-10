/*
 * ================================ Select Module ============================================
 * Select modeule support select statment. 
 * Besides, Update statement, delete statement also use these module for query under conditon.
 * ===========================================================================================
 * */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "check.h"
#include "common.h"
#include "cond.h"
#include "copy.h"
#include "free.h"
#include "index.h"
#include "intpr.h"
#include "log.h"
#include "mmu.h"
#include "meta.h"
#include "misc.h"
#include "node.h"
#include "opr.h"
#include "pager.h"
#include "select.h"
#include "table.h"
#include "asserts.h"
#include "session.h"
#include "lock.h"
#include "trans.h"
#include "refer.h"
#include "ret.h"

/* Maximum number of rows fetched at once.*/
#define MAX_FETCH_ROWS 100 

/* Function name, also as key in out json. */
#define COUNT_NAME "count"
#define SUM_NAME "sum"
#define AVG_NAME "avg"
#define MAX_NAME "max"
#define MIN_NAME "min"

/* Check if include the internal node. */
static bool include_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table);

/* Check if the key include the leaf node. */
static bool include_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table);

/* Get meta column by condition name. */
static MetaColumn *get_cond_meta_column(ConditionNode *condition_node, MetaTable *meta_table);

/* Find meta column index.
 * Return NULL if not exist */
static MetaColumn *find_select_item_meta_column(QueryParam *query_param, uint32_t index) {
    SelectItemsNode *select_items_node = query_param->select_items;
    Table *table = open_table(query_param->table_name);
    MetaTable *meta_table = table->meta_table;
    switch (select_items_node->type) {
        case SELECT_ALL:
            return meta_table->meta_column[index];
        case SELECT_COLUMNS: {
            /* Because there are system reserved column, so when index greater than column size, 
             * it is system reserved column. */
            int column_size = select_items_node->column_set_node->size;
            if (index < column_size) {
                ColumnNode *column_node = *(select_items_node->column_set_node->columns + index);
                return get_meta_column_by_name(table->meta_table, column_node->column_name);
            } else {
                index =  meta_table->column_size + index - column_size;
                return meta_table->meta_column[index];
            }
        }
        case SELECT_FUNCTION:
            return NULL;
    }
}

/* Calulate offset of every column in cell. */
static uint32_t calc_offset(QueryParam *query_param, char *column_name) {
    SelectItemsNode *select_items_node = query_param->select_items;
    Table *table = open_table(query_param->table_name);
    MetaTable *meta_table = table->meta_table;
    int i; uint32_t off_set = 0;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0)
            break;
        off_set += meta_column->column_length;
    }
    return off_set;
}

/* Get query param column size. */
static uint32_t get_query_columns_num(QueryParam *query_param) {
    SelectItemsNode *select_items_node = query_param->select_items;
    Table *table = open_table(query_param->table_name);
    switch (select_items_node->type) {
        case SELECT_ALL: {
            return table->meta_table->all_column_size;
        }
        case SELECT_COLUMNS:
            /* Get column size including system reserved columns. */
            return select_items_node->column_set_node->size + (table->meta_table->all_column_size - table->meta_table->column_size);
        case SELECT_FUNCTION:
            return 1 + (table->meta_table->all_column_size - table->meta_table->column_size);
  }
}

/* Get value from value item node. */
void *get_value_from_value_item_node(ValueItemNode *value_item_node, DataType meta_data_type) {

    /* User can use '%s' fromat in sql to pass multiple types value including char, string, date, timestamp. 
     * So we must use meta column data type to define which data type of the value. */
    switch (meta_data_type) { 
        case T_CHAR: {
            switch (value_item_node->data_type) {
                case T_STRING:
                    value_item_node->data_type = T_CHAR;
                    return value_item_node->s_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_STRING:
            return value_item_node->s_value;
        case T_INT:
            return &value_item_node->i_value;
        case T_BOOL:
            return &value_item_node->b_value;
        case T_FLOAT: {
            switch (value_item_node->data_type) {
                case T_INT:
                    value_item_node->f_value = value_item_node->i_value;
                    value_item_node->data_type = T_FLOAT;
                case T_FLOAT:
                    return &value_item_node->f_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_DOUBLE: {
            switch (value_item_node->data_type) {
                case T_INT:
                    value_item_node->d_value = value_item_node->i_value;
                    value_item_node->data_type = T_DOUBLE;
                case T_FLOAT:
                    value_item_node->d_value = value_item_node->f_value;
                    value_item_node->data_type = T_DOUBLE;
                case T_DOUBLE:
                    return &value_item_node->d_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_TIMESTAMP: {
            switch (value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm), SDT_TIME_T);
                    strptime(value_item_node->s_value, "%Y-%m-%d %H:%M:%S", tmp_time);
                    value_item_node->t_value = mktime(tmp_time);
                    value_item_node->data_type = T_TIMESTAMP;
                    db_free(tmp_time);
                }
                case T_TIMESTAMP:
                    return &value_item_node->t_value;
                default:
                    fatal("Data type error.");
            }
            break;
        }
        case T_DATE: {
            switch (value_item_node->data_type) {
                case T_STRING: {
                    struct tm *tmp_time = db_malloc(sizeof(struct tm), SDT_TIME_T);
                    strptime(value_item_node->s_value, "%Y-%m-%d", tmp_time);
                    tmp_time->tm_sec = 0;
                    tmp_time->tm_min = 0;
                    tmp_time->tm_hour = 0;
                    value_item_node->t_value = mktime(tmp_time);
                    value_item_node->data_type = T_DATE;
                    db_free(tmp_time);
                }
                case T_DATE:
                    return &value_item_node->t_value;
                default:
                    fatal("Data type error.");
             }
             break;
        }
        case T_REFERENCE:
            return value_item_node->nest_value_item_set; 
        default:
            fatal("Not implement yet.");
    }
    return NULL;
}

/*Check if the row include the condition node. */
static bool satisfy_leaf_condition_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course the key include, so just return true. */
    if (condition_node == NULL)
        return true;

    int i; uint32_t off_set = 0;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        /* Define the column. */
        if (strcmp(meta_column->column_name, condition_node->column->column_name) == 0) {
            void *value = destinct + off_set;
            void *target = get_value_from_value_item_node(condition_node->value, meta_column->column_type);
            return eval(condition_node->opr_type, value, target, meta_column->column_type);
        }
        off_set += meta_column->column_length;
    }
    return false;
}

/* Check the tagert key if include the internal node.
 * @param min_key the min key of node (exclude the min key, acutally the min key is max key of previous node)
 * @param max_key the max key of node (include the max key)
 * @param target_key the target key to compare
 * @param opr_type operation type
 * @param key_data_type data type of key
 * */
static bool satisfy_internal_condition_node(void *min_key, void *max_key, void *target_key, OprType opr_type, DataType key_data_type) {
    switch (opr_type) {
        case O_EQ:
            return less(min_key, target_key, key_data_type) && less_equal(target_key, max_key, key_data_type);
        case O_NE:
            return !(less(min_key, target_key, key_data_type) && less_equal(target_key, max_key, key_data_type));
        case O_GT:
            return greater(max_key, target_key, key_data_type);
        case O_GE:
            return greater_equal(max_key, target_key, key_data_type);
        case O_LT:
            return greater(target_key, min_key, key_data_type);
        case O_LE:
            return greater(target_key, min_key, key_data_type);
        case O_IN:
        case O_LIKE:
            fatal("Not implement yet.");
    }
    return true;
}


/* Check if include the internal node if condition is logic condition. */
static bool include_logic_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {
    /* For logic condition node, check left node and right node. */
    switch(condition_node->conn_type) {
        case C_AND:
           return include_internal_node(min_key, max_key, condition_node->left, meta_table) && include_internal_node(max_key, max_key, condition_node->right, meta_table);
        case C_OR:
           return include_internal_node(min_key, max_key, condition_node->left, meta_table) || include_internal_node(max_key, max_key, condition_node->right, meta_table);
    } 
}

/* Check if include the internal node if condition is exec condition. */
static bool include_exec_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    MetaColumn *cond_meta_column = get_cond_meta_column(condition_node, meta_table);
    void *target_key = get_value_from_value_item_node(condition_node->value, cond_meta_column->column_type);

    /* Skipped the internal node must satisfy tow factors: 
     * key column and not satisfied internal node condition. */
    return !cond_meta_column->is_primary 
        || satisfy_internal_condition_node(min_key, max_key, target_key, condition_node->opr_type, cond_meta_column->column_type);
}

/* Check if include the internal node. */
static bool include_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course return true. */
    if (condition_node == NULL)
        return true;

    /* According to condition node type, has different way. */
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            return include_logic_internal_node(min_key, max_key, condition_node, meta_table);
        case EXEC_CONDITION:
            return include_exec_internal_node(min_key, max_key, condition_node, meta_table);
    }
}

/* Check if include leaf node if the condition is logic condition. */
static bool include_logic_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {
    switch(condition_node->conn_type) {
        case C_AND:
            return include_leaf_node(destinct, condition_node->left, meta_table) && include_leaf_node(destinct, condition_node->right, meta_table);
        case C_OR:
            return include_leaf_node(destinct, condition_node->right, meta_table) || include_leaf_node(destinct, condition_node->right, meta_table);
    } 
}


/* Check if include leaf node if the condition is exec condition. */
static bool include_exec_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {
    return satisfy_leaf_condition_node(destinct, condition_node, meta_table);
}

/* Check if the key include the leaf node. */
static bool include_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course the key include, so just return true. */
    if (condition_node == NULL) 
          return true;

    switch(condition_node->type) {
        case LOGIC_CONDITION:
            return include_logic_leaf_node(destinct, condition_node, meta_table);
        case EXEC_CONDITION:
            return include_exec_leaf_node(destinct, condition_node, meta_table);
    }
}

/* Get meta column by condition name. */
static MetaColumn *get_cond_meta_column(ConditionNode *condition_node, MetaTable *meta_table) {
    if (condition_node == NULL)
        return NULL;
    return get_meta_column_by_name(meta_table, condition_node->column->column_name);
}

/* Assign function count() value to row data. */
static void assign_function_count_row_data(Row *row, void *destine, QueryParam *query_param) {
    /* Check if table exist. */
    Table *table = open_table(query_param->table_name);
    if (table == NULL) return; /* Return if not exist the table. */
    MetaTable *meta_table = table->meta_table;

    int32_t val = 1;
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(COUNT_NAME);
    key_value->value = copy_value(&val, T_INT, NULL);
    key_value->data_type = T_INT;
    row->data[0] = key_value;

    /* Assign system reserved column. */
    int i, j;
    for(i = meta_table->column_size, j = 1; i < meta_table->all_column_size; i++, j++) {
        MetaColumn *sys_reserved_meta_column = meta_table->meta_column[i];
        assert_true(sys_reserved_meta_column->sys_reserved, "Ststem Logic error. \n");
        uint32_t off_set = calc_offset(query_param, sys_reserved_meta_column->column_name);
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(sys_reserved_meta_column->column_name);
        key_value->value = copy_value(destine + off_set, sys_reserved_meta_column->column_type, sys_reserved_meta_column);
        key_value->data_type = sys_reserved_meta_column->column_type;
        /* Assign system reserved value to row. */
        row->data[j] = key_value;
    }
}

/* Assign function sum() value to row data. */
static void assign_funtion_sum_row_data(Row *row, void *destine, QueryParam *query_param) {

    /* Check if table exist. */
    Table *table = open_table(query_param->table_name);
    if (table == NULL) return; /* Return if not exist the table. */
    MetaTable *meta_table = table->meta_table;

    /* Get function value. */
    FunctionValueNode *function_value_node = query_param->select_items->function_node->value;

    /* Instance key value */
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(SUM_NAME);

    /* According function value type, these are diffrent ways to deal with the row data: 
     * For V_ALL, there is no pointer to sum the value, just regard as zero;
     * For V_INT, absolutely a numerical type, just return the integer value.
     * For V_COLUMN, if the column data type is numerical, return the numerical value, otherwise, return zero;
     * */
    switch (function_value_node->value_type) {
        case V_ALL: {
            uint32_t val = 0;
            key_value->value = &val;
            key_value->data_type = T_INT;
            break;
        }
        case V_INT: {
            key_value->value = &function_value_node->i_value;
            key_value->data_type = T_INT;
            break;
        }
        case V_COLUMN: {
            /* IF numerical data type column, return the numerical value, otherwise return zero */
            ColumnNode *column_node = function_value_node->column;
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_node->column_name);
            uint32_t off_set = calc_offset(query_param, meta_column->column_name);
            switch (meta_column->column_type) {
                case T_STRING:
                case T_REFERENCE:
                case T_DATE:
                case T_TIMESTAMP: {
                    int32_t val = 0;
                    key_value->value = &val;
                    key_value->data_type = T_INT;
                    break;
                }
                case T_BOOL: {
                    bool b_value = *(bool *)copy_value(destine + off_set, meta_column->column_type, meta_column);
                    int32_t val = b_value ? 1 : 0;
                    key_value->value = &val;
                    key_value->data_type = T_INT;
                    break;
                }
                case T_CHAR: {
                    char c_val = *(char *)copy_value(destine + off_set, meta_column->column_type, meta_column);
                    int32_t val = c_val;
                    key_value->value = &val;
                    key_value->data_type = T_INT;
                    break;
                }
                case T_INT:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type, meta_column);
                    key_value->data_type = T_INT;
                    break;
                case T_LONG:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type, meta_column);
                    key_value->data_type = T_LONG;
                    break;
                case T_FLOAT:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type, meta_column);
                    key_value->data_type = T_FLOAT;
                    break;
                case T_DOUBLE:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type, meta_column);
                    key_value->data_type = T_DOUBLE;
                    break;
            }
            break;
        }
    }

    /* Assgin to row frist data. */
    row->data[0] = key_value;
    
    /* Assign system reserved column. */
    int i, j;
    for(i = meta_table->column_size, j = 1; i < meta_table->all_column_size; i++, j++) {
        MetaColumn *sys_reserved_meta_column = meta_table->meta_column[i];
        assert_true(sys_reserved_meta_column->sys_reserved, "Ststem Logic error. \n");
        uint32_t off_set = calc_offset(query_param, sys_reserved_meta_column->column_name);
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(sys_reserved_meta_column->column_name);
        key_value->value = copy_value(destine + off_set, sys_reserved_meta_column->column_type, sys_reserved_meta_column);
        key_value->data_type = sys_reserved_meta_column->column_type;
        /* Assign system reserved value to row. */
        row->data[j] = key_value;
    }
}

/* Assign function max() value to row data. */
static void assign_function_max_row_data(Row *row, void *destinct, QueryParam *query_param) {
    
    /* Check if table exist. */
    Table *table = open_table(query_param->table_name);
    if (table == NULL) return; /* Return if not exist the table. */
    MetaTable *meta_table = table->meta_table;

    /* Get function value. */
    FunctionValueNode *function_value_node = query_param->select_items->function_node->value;

    /* Instance key value */
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(MAX_NAME);

    /* According function input value type, these are diffrent ways to deal with the row data: 
     * For V_ALL, there is a error, not allow use '*' as max function input value. ;
     * For V_INT, absolutely a numerical type, just return the integer value.
     * For V_COLUMN, return the column value.
     * */
    switch (function_value_node->value_type) {
        case V_ALL: 
            fatal("Not allow use all as max function input value.");
            break;
        case V_INT: {
            key_value->value = &function_value_node->i_value;
            key_value->data_type = T_INT;
            break;
        }
        case V_COLUMN: {
            /* IF numerical data type column, return the numerical value, otherwise return zero */
            ColumnNode *column_node = function_value_node->column;
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_node->column_name);
            uint32_t off_set = calc_offset(query_param, meta_column->column_name);
            key_value->value = copy_value(destinct + off_set, meta_column->column_type, meta_column);
            key_value->data_type = meta_column->column_type;
        }
        break;
    }

    /* Assgin to row data. */
    row->data[0] = key_value;

    /* Assign system reserved column. */
    int i, j;
    for(i = meta_table->column_size, j = 1; i < meta_table->all_column_size; i++, j++) {
        MetaColumn *sys_reserved_meta_column = meta_table->meta_column[i];
        assert_true(sys_reserved_meta_column->sys_reserved, "Ststem Logic error. \n");
        uint32_t off_set = calc_offset(query_param, sys_reserved_meta_column->column_name);
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(sys_reserved_meta_column->column_name);
        key_value->value = copy_value(destinct + off_set, sys_reserved_meta_column->column_type, sys_reserved_meta_column);
        key_value->data_type = sys_reserved_meta_column->column_type;
        /* Assign system reserved value to row. */
        row->data[j] = key_value;
    }
}


/* Assign function min() value to row data. */
static void assign_function_min_row_data(Row *row, void *destinct, QueryParam *query_param) {
    
    /* Check if table exist. */
    Table *table = open_table(query_param->table_name);
    if (table == NULL) return; /* Return if not exist the table. */
    MetaTable *meta_table = table->meta_table;

    /* Get function value. */
    FunctionValueNode *function_value_node = query_param->select_items->function_node->value;

    /* Instance key value */
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(MIN_NAME);

    /* According function input value type, these are diffrent ways to deal with the row data: 
     * For V_ALL, there is a error, not allow use '*' as max function input value. ;
     * For V_INT, absolutely a numerical type, just return the integer value.
     * For V_COLUMN, return the column value.
     * */
    switch (function_value_node->value_type) {
        case V_ALL: 
            fatal("Not allow use all as min function input value.");
            break;
        case V_INT: {
            key_value->value = &function_value_node->i_value;
            key_value->data_type = T_INT;
            break;
        }
        case V_COLUMN: {
            /* IF numerical data type column, return the numerical value, otherwise return zero */
            ColumnNode *column_node = function_value_node->column;
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_node->column_name);
            uint32_t off_set = calc_offset(query_param, meta_column->column_name);
            key_value->value = copy_value(destinct + off_set, meta_column->column_type, meta_column);
            key_value->data_type = meta_column->column_type;
        }
        break;
    }

    /* Assgin to row data. */
    row->data[0] = key_value;

    /* Assign system reserved column. */
    int i, j;
    for(i = meta_table->column_size, j = 1; i < meta_table->all_column_size; i++, j++) {
        MetaColumn *sys_reserved_meta_column = meta_table->meta_column[i];
        assert_true(sys_reserved_meta_column->sys_reserved, "Ststem Logic error. \n");
        uint32_t off_set = calc_offset(query_param, sys_reserved_meta_column->column_name);
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(sys_reserved_meta_column->column_name);
        key_value->value = copy_value(destinct + off_set, sys_reserved_meta_column->column_type, sys_reserved_meta_column);
        key_value->data_type = sys_reserved_meta_column->column_type;
        /* Assign system reserved value to row. */
        row->data[j] = key_value;
    }
}

/* Assign function value to row data. */
static void assign_function_row_data(Row *row, void *destinct, QueryParam *query_param) {

    FunctionNode *function_node = query_param->select_items->function_node;
    switch (function_node->function_type) {
        case F_COUNT:
            assign_function_count_row_data(row, destinct, query_param);
            break;
        case F_SUM:
            assign_funtion_sum_row_data(row, destinct, query_param);
            break;
        case F_AVG:
            /* For avg, also first sum and then divied by total row size. */
            assign_funtion_sum_row_data(row, destinct, query_param);
            break;
        case F_MAX:
            assign_function_max_row_data(row, destinct, query_param);
            break;
        case F_MIN:
            assign_function_min_row_data(row, destinct, query_param);
            break;
    }
}

/* Assign value to row data. */
static void assign_plain_row_data(Row *row, void *destinct, QueryParam *query_param) {
    int i;
    for (i = 0; i < row->column_len; i++) {
        MetaColumn *meta_column = find_select_item_meta_column(query_param, i);

        uint32_t off_set = calc_offset(query_param, meta_column->column_name);
        
        /* Generate a key value pair. */
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->value = copy_value(destinct + off_set, meta_column->column_type, meta_column);
        key_value->data_type = meta_column->column_type;
        *(row->data + i) = key_value;
    }
}

/* Generate select row. */
static Row *generate_row(void *destinct, QueryParam *query_param, MetaTable *meta_table) {

    /* Check if table exist.*/
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
      return NULL;

    /* Define row data. */
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->column_len = get_query_columns_num(query_param);
    row->table_name = db_strdup(query_param->table_name);

    /* Assignment values to row data. */
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);
    switch (query_param->select_items->type) {
        case SELECT_ALL:
        case SELECT_COLUMNS:
            assign_plain_row_data(row, destinct, query_param);
            break;
        case SELECT_FUNCTION:
            assign_function_row_data(row, destinct, query_param);
            break;
    }

    /* Define row key. */
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    uint32_t priamry_key_set_off = calc_offset(query_param, primary_key_meta_column->column_name);
    row->key = copy_value(destinct + priamry_key_set_off, primary_key_meta_column->column_type, primary_key_meta_column);

    return row;
}

/* Define row by refer. */
Row *define_row(Refer *refer) {
    uint32_t key_len, value_len;
    Table *table = open_table(refer->table_name);
    if (table == NULL) return NULL;
    value_len = calc_table_row_length(table);
    key_len = calc_primary_key_length(table);
    void *leaf_node = get_page(table->pager, refer->page_num);
    void *destinct = get_leaf_node_cell_value(leaf_node, key_len, value_len, refer->cell_num);
    
    QueryParam *query_param = db_malloc(sizeof(QueryParam), SDT_QUERY_PARAM);
    query_param->table_name = db_strdup(refer->table_name);
    query_param->select_items = db_malloc(sizeof(SelectItemsNode), SDT_QUERY_PARAM);
    query_param->select_items->type = SELECT_ALL;

    Row *row = generate_row(destinct, query_param, table->meta_table);
    
    /* Free memory. */
    free_query_param(query_param);

    return row;
}

/* Select through leaf node. */
static void select_from_leaf_node(SelectResult *select_result, QueryParam *query_param, uint32_t page_num, Table *table, ROW_HANDLER row_handler, void *arg) {

    void *leaf_node = get_page(table->pager, page_num);

    /* Get cell number, key length and value lenght. */
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* It`s necessary to use leaf node snapshot, beacuse when traversing cells, 
     * update or delete operation will change the data structure of leaf node,
     * which may causes bug. */
    void *leaf_node_snapshot = copy_block(leaf_node, PAGE_SIZE);

    int i;
    for (i = 0; i < cell_num; i++) {
    
        /* Get leaf node cell value. */
        void *destinct = get_leaf_node_cell_value(leaf_node_snapshot, key_len, value_len, i);

        /* Check if the row data include, in another word, check if the row data satisfy the condition. */
        if (!include_leaf_node(destinct, query_param->condition_node, table->meta_table))
            continue;

        /* If satisfied, exeucte row handler function. */
        Row *row = generate_row(destinct, query_param, table->meta_table);

        /* Execute row handler. */
        Cursor *cursor = new_cursor(table, page_num, i);
        row_handler(row, select_result, cursor, arg);

        /* Free useless row. */
        free_row(row);
        free_cursor(cursor);
    }
    
    /* Free useless pointer. */
    db_free(leaf_node_snapshot);
}

/* Select through internal node. */
static void select_from_internal_node(SelectResult *select_result, QueryParam *query_param, void *internal_node, Table *table, ROW_HANDLER row_handler, void *arg) {

    /* Get keys number, key length. */
    uint32_t keys_num, key_len;
    keys_num = get_internal_node_keys_num(internal_node);
    key_len = calc_primary_key_length(table);

    /* It`s necessary to use internal node snapshot, beacuse when traversing cells, 
     * update or delete operation will change the data structure of internal node,
     * which may causes bug.*/
    void *internal_node_snapshot = copy_block(internal_node, PAGE_SIZE);

    /* Loop for each interanl node cell to check if satisfy condition. */
    int i;
    for (i = 0; i < keys_num; i++) {
        /* Check if index column, use index to avoid full text scanning. */
        {
            /* Current internal node cell key as max key, previous cell key as min key */
            void *max_key = get_internal_node_key(internal_node_snapshot, i, key_len); 
            void *min_key = i == 0 ? NULL : get_internal_node_key(internal_node_snapshot, i - 1, key_len);

            ConditionNode *condition_node = query_param->condition_node;
            if (!include_internal_node(min_key, max_key, condition_node, table->meta_table))
                continue;
        }

        /* Check other non-key column */
        uint32_t page_num = get_internal_node_child(internal_node_snapshot, i, key_len);
        void *node = get_page(table->pager, page_num);
        switch (get_node_type(node)) {
            case LEAF_NODE:
                select_from_leaf_node(select_result, query_param, page_num, table, row_handler, arg);
                break;
            case INTERNAL_NODE:
                select_from_internal_node(select_result, query_param, node, table, row_handler, arg);
                break;
        }
    }

    /* Don`t forget the right child. */
    uint32_t right_child_page_num = get_internal_node_right_child(internal_node_snapshot);

    /* Zero means there is no page. */
    if (right_child_page_num == 0) 
        return;
    void *right_child = get_page(table->pager, right_child_page_num);
    switch (get_node_type(right_child)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, query_param, right_child_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, query_param, right_child, table, row_handler, arg);
            break;
    }

    /* free memory. */
    db_free(internal_node_snapshot);
}

/* Convert from select node to query param */
QueryParam *convert_query_param(SelectNode *select_node) {
    QueryParam *query_param = db_malloc(sizeof(QueryParam), SDT_QUERY_PARAM);
    query_param->table_name = db_strdup(select_node->table_name);
    query_param->select_items = copy_select_items_node(select_node->select_items_node);
    ConditionNode *condition_node_copy = copy_condition_node(select_node->condition_node);
    query_param->condition_node = tree(condition_node_copy); // generate condition tree.
    clean_next(query_param->condition_node);
    return query_param;
}

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name) {
    SelectResult *select_result = db_malloc(sizeof(SelectResult), SDT_SELECT_RESULT);
    select_result->row_size = 0;
    select_result->table_name = db_strdup(table_name);
    select_result->sum = 0;
    select_result->rows = NULL;
    return select_result;
}

/* Query with condition. */
void query_with_condition(QueryParam *query_param, SelectResult *select_result, ROW_HANDLER row_handler, void *arg) {
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return;
    void *root = get_page(table->pager, table->root_page_num);
    switch (get_node_type(root)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, query_param, table->root_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, query_param, root, table, row_handler, arg);
            break;
    }
}

/* Count number of row, used in the sql function count(1) */
void count_row(Row *row, SelectResult *select_result, Cursor *cursor, void *arg) {
    /* Only count visible row. */
    if (row_is_visible(row))
        select_result->row_size++;
}

/* Send row data. */
static void select_row(Row *row, SelectResult *select_result, Cursor *cursor, void *arg) {
    /* Only select visible row. */
    if (row_is_visible(row))
        select_result->rows[select_result->row_index++] = copy_row_without_reserved(row);
}

/* Execute sum funciton */
static void sum_row(Row *row, SelectResult *select_result, Cursor *cursor, void *arg) {
    /* Only sum visible row. */
    if (!row_is_visible(row)) 
        return;
    KeyValue *key_value = row->data[0];
    switch(key_value->data_type) {
        case T_INT:
        case T_BOOL:
        case T_CHAR:
            select_result->sum += *(int32_t *) key_value->value;
            break;
        case T_FLOAT:
            select_result->sum += *(float *) key_value->value;
            break;
        case T_DOUBLE:
            select_result->sum += *(double *) key_value->value;
            break;
        default:
            select_result->sum += 0;
            break;
    }
    select_result->row_size++;
}

/* Execute max function. */
static void max_row(Row *row, SelectResult *select_result, Cursor *cursor, void *arg) {

    /* Only visible row. */
    if (!row_is_visible(row))
        return;
    
    /* Only look for first content of row data. */;
    KeyValue *key_value = row->data[0];

    /* At first, the max row is null. */
    if (select_result->max_row == NULL) 
        select_result->max_row = copy_row_without_reserved(row);
    else {
        Row *max_row = select_result->max_row;
        KeyValue *max_row_key_value = max_row->data[0];
        /* If current row value greater than max row, assign current row as the max row. */
        if (greater(key_value->value, max_row_key_value->value, key_value->data_type)) {
            free_row(select_result->max_row);
            select_result->max_row = copy_row_without_reserved(row);
        }
    }

    select_result->row_size++;
}

/* Execute min function. */
static void min_row(Row *row, SelectResult *select_result, Cursor *cursor, void *arg) {
    
    /* Only for visible row. */
    if (!row_is_visible(row))
        return;

    /* Only look for first content of row data. */;
    KeyValue *key_value = row->data[0];

    /* At first, the min row is null, initilise it. */
    if (select_result->min_row == NULL) 
        select_result->min_row = copy_row_without_reserved(row);
    else {
        /* If current row value less than min row, assign current row as the mix row. */
        Row *min_row = select_result->min_row;
        KeyValue *min_row_key_value = min_row->data[0];
        if (less(key_value->value, min_row_key_value->value, key_value->data_type)) {
            free_row(select_result->min_row);
            select_result->min_row = copy_row_without_reserved(row);
        }
    }

    select_result->row_size++;
}


/* Execute aggregate function count(). */
static void exec_function_count(QueryParam *query_param, DBResult *result) {

    /* Generate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    success_result(result, "Count function exeucted successfully.");

    int32_t row_size = select_result->row_size;
    /* Prepare enough memory space. */
    select_result->row_size = 1;
    select_result->rows = db_malloc(sizeof(Row *) * select_result->row_size, SDT_POINTER);

    /* For the count row. */
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->table_name = db_strdup(query_param->table_name);
    row->data = db_malloc(sizeof(KeyValue *) * 1, SDT_POINTER);
    row->column_len = 1;

    /* For key value. */
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(COUNT_NAME);
    key_value->value = copy_value(&row_size, T_INT, NULL);
    key_value->data_type = T_INT;

    /* Assignment. */
    row->data[0] = key_value;
    select_result->rows[0] = row;
    result->data = select_result;
    result->rows = row_size;
}

/* Execute aggregate function sum(). */
static void exec_function_sum(QueryParam *query_param, DBResult *result) {
     
    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Plus row data. */
    query_with_condition(query_param, select_result, sum_row, NULL);

    /* success result. */
    success_result(result, "Sum function exeucted successfully.");

    int row_size = select_result->row_size;
    /* Prepare enough memory space. */
    select_result->row_size = 1;
    select_result->rows = db_malloc(sizeof(Row *) * 1, SDT_POINTER);

    /* For the SUM row. */
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->table_name = db_strdup(query_param->table_name);
    row->data = db_malloc(sizeof(KeyValue *) * 1, SDT_POINTER);
    row->column_len = 1;

    /* For key value. */
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(SUM_NAME);
    key_value->value = copy_value(&select_result->sum, T_DOUBLE, NULL);
    key_value->data_type = T_DOUBLE;

    /* Assignment. */
    row->data[0] = key_value;
    select_result->rows[0] = row;
    result->data = select_result;
    result->rows = row_size;
} 

/* Execute aggregate function avg(). */
static void exec_function_avg(QueryParam *query_param, DBResult *result) {

    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Plus row data. */
    query_with_condition(query_param, select_result, sum_row, NULL);

    /* success result. */
    success_result(result, "Avg function exeucted successfully.");

    int row_size = select_result->row_size;
    /* Prepare enough memory space. */
    select_result->row_size = 1;
    select_result->rows = db_malloc(sizeof(Row *) * 1, SDT_POINTER);

    /* For the SUM row. */
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->table_name = db_strdup(query_param->table_name);
    row->data = db_malloc(sizeof(KeyValue *) * 1, SDT_ROW);
    row->column_len = 1;

    /* For key value. */
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup(AVG_NAME);
    double value = select_result->sum / row_size;
    key_value->value = copy_value(&value, T_DOUBLE, NULL);
    key_value->data_type = T_DOUBLE;

    /* Assignment. */
    row->data[0] = key_value;
    select_result->rows[0] = row;
    result->data = select_result;
    result->rows = row_size;
}

/* Execute aggregate function max(). */
static void exec_function_max(QueryParam *query_param, DBResult *result) {
    
    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Max row. */
    query_with_condition(query_param, select_result, max_row, NULL);

    /* success result. */
    success_result(result, "Max function executed successfully.");

    int row_size = select_result->row_size;
    /* Prepare enough memory space. */
    select_result->row_size = 1;
    select_result->rows = db_malloc(sizeof(Row *) * 1, SDT_POINTER);

    /* For the SUM row. */
    Row *row = copy_row(select_result->max_row);
    /* Assignment. */
    select_result->rows[0] = row;
    result->data = select_result;
    result->rows = row_size;

}

/* Execute aggregate function min(). */
static void exec_function_min(QueryParam *query_param, DBResult *result) {

    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Min row. */
    query_with_condition(query_param, select_result, min_row, NULL);

    /* success result. */
    success_result(result, "Min function executed successfully.");

    int row_size = select_result->row_size;
    /* Prepare enough memory space. */
    select_result->row_size = 1;
    select_result->rows = db_malloc(sizeof(Row *) * 1, SDT_POINTER);

    /* For the SUM row. */
    Row *row = copy_row(select_result->min_row);
    /* Assignment. */
    select_result->rows[0] = row;
    result->data = select_result;
    result->rows = row_size;
}


/* Execute function select statement. 
 * Now supported aggregate function:
 *     COUNT
 *     SUM
 *     AVG
 *     MAX
 *     MIN
 * */
static void exec_function_select_statement(QueryParam *query_param, DBResult *result) {
    FunctionNode *function_node = query_param->select_items->function_node;
    switch(function_node->function_type) {
        case F_COUNT:
            exec_function_count(query_param, result);
            break;
        case F_SUM:
            exec_function_sum(query_param, result);
            break;
        case F_AVG:
            exec_function_avg(query_param, result);
            break;   
        case F_MAX:
            exec_function_max(query_param, result);
            break;
        case F_MIN:
            exec_function_min(query_param, result);
            break;
    }
}


/* Execute plain select statement. */
static void exec_plain_select_statement(QueryParam *query_param, DBResult *result) {

    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Prepare enough memory space. */
    select_result->rows = db_malloc(sizeof(Row *) * select_result->row_size, SDT_POINTER);

    /* Send row data in json format. */
    query_with_condition(query_param, select_result, select_row, NULL);

    /* success result. */
    success_result(result, "Query data successfully.");

    /* Assign exeuction result. */
    result->rows = select_result->row_size;
    result->data = select_result;
}


/* Execute select statement. */
void exec_select_statement(SelectNode *select_node, DBResult *result) {
    QueryParam *query_param = convert_query_param(select_node);
    if (check_query_param(query_param, result)) {
        switch(query_param->select_items->type) {
            case SELECT_ALL:
            case SELECT_COLUMNS:
                exec_plain_select_statement(query_param, result);
                break;
            case SELECT_FUNCTION:
                exec_function_select_statement(query_param, result);
                break;
        }
    }
    free_query_param(query_param);
}
