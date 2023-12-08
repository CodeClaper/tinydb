#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
#include "mem.h"
#include "meta.h"
#include "misc.h"
#include "node.h"
#include "opr.h"
#include "pager.h"
#include "select.h"
#include "table.h"
#include "session.h"

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

/* Find meta column index, return NULL if not exist */
static MetaColumn *find_select_item_meta_column(QueryParam *query_param, uint32_t index) {
    SelectItemsNode *select_items_node = query_param->select_items;
    Table *table = open_table(query_param->table_name);
    switch (select_items_node->type) {
        case SELECT_ALL:
            return table->meta_table->meta_column[index];
        case SELECT_COLUMNS: {
            ColumnNode *column_node = *(select_items_node->column_set_node->columns + index);
            return get_meta_column_by_name(table->meta_table, column_node->column_name);
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
    uint32_t off_set = 0;
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
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
    switch (select_items_node->type) {
    case SELECT_ALL: {
        Table *table = open_table(query_param->table_name);
        return table->meta_table->column_size;
    }
    case SELECT_COLUMNS:
        return select_items_node->column_set_node->size;
    case SELECT_FUNCTION:
        return 1;
  }
}

/* Get value from value item node. */
void *get_value_from_value_item_node(ValueItemNode *value_item_node, DataType meta_data_type) {

    /* User can use '%s' fromat in sql to pass multiple types value including char, string, date, timestamp. 
     * So we must use meta column data type to define which data type of the value.
     * */
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
                    struct tm *tmp_time = db_malloc2(sizeof(struct tm), "struct tm");
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
                    struct tm *tmp_time = db_malloc2(sizeof(struct tm), "struct tm");
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

    uint32_t off_set = 0;
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
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
    return !cond_meta_column->is_primary || satisfy_internal_condition_node(min_key, max_key, target_key, condition_node->opr_type, cond_meta_column->column_type);

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
static void assign_funtion_sum_row_data(Row *row, void *destine, QueryParam *query_param) {

    /* Check if table exist. */
    Table *table = open_table(query_param->table_name);
    if (table == NULL) return; /* Return if not exist the table. */
    MetaTable *meta_table = table->meta_table;

    /* Get function value. */
    FunctionValueNode *function_value_node = query_param->select_items->function_node->value;

    /* Instance key value */
    KeyValue *key_value = db_malloc2(sizeof(KeyValue), "KeyValue");
    key_value->key = strdup(SUM_NAME);

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
                case T_DATE:
                case T_TIMESTAMP: {
                    int32_t val = 0;
                    key_value->value = &val;
                    key_value->data_type = T_INT;
                    break;
                }
                case T_BOOL: {
                    bool b_value = *(bool *)copy_value(destine + off_set, meta_column->column_type);
                    int32_t val = b_value ? 1 : 0;
                    key_value->value = &val;
                    key_value->data_type = T_INT;
                    break;
                }
                case T_CHAR: {
                    char c_val = *(char *)copy_value(destine + off_set, meta_column->column_type);
                    int32_t val = c_val;
                    key_value->value = &val;
                    key_value->data_type = T_INT;
                    break;
                }
                case T_INT:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type);
                    key_value->data_type = T_INT;
                    break;
                case T_FLOAT:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type);
                    key_value->data_type = T_FLOAT;
                    break;
                case T_DOUBLE:
                    key_value->value = copy_value(destine + off_set, meta_column->column_type);
                    key_value->data_type = T_DOUBLE;
                    break;
                    
            }
        }
        break;
    }

    // assgin to row data.
    *(row->data) = key_value;
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
    KeyValue *key_value = db_malloc2(sizeof(KeyValue), "KeyValue");
    key_value->key = strdup(MAX_NAME);

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
            key_value->value = copy_value(destinct + off_set, meta_column->column_type);
            key_value->data_type = meta_column->column_type;
        }
        break;
    }

    // assgin to row data.
    *(row->data) = key_value;
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
    KeyValue *key_value = db_malloc2(sizeof(KeyValue), "KeyValue");
    key_value->key = strdup(MIN_NAME);

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
            key_value->value = copy_value(destinct + off_set, meta_column->column_type);
            key_value->data_type = meta_column->column_type;
        }
        break;
    }

    // assgin to row data.
    *(row->data) = key_value;
}

/* Assign function value to row data. */
static void assign_function_row_data(Row *row, void *destinct, QueryParam *query_param) {

    FunctionNode *function_node = query_param->select_items->function_node;
    switch (function_node->function_type) {
        case F_COUNT:
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
    for (uint32_t i = 0; i < row->column_len; i++) {
        MetaColumn *meta_column = find_select_item_meta_column(query_param, i);
        uint32_t off_set = calc_offset(query_param, meta_column->column_name);
        
        /* Generate a key value pair. */
        KeyValue *key_value = db_malloc2(sizeof(KeyValue), "KeyValue");
        key_value->key = strdup(meta_column->column_name);
        key_value->value = copy_value(destinct + off_set, meta_column->column_type);
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
    Row *row = db_malloc2(sizeof(Row), "Row");
    row->column_len = get_query_columns_num(query_param);
    row->table_name = strdup(query_param->table_name);

    /* Assignment values to row data. */
    row->data = db_malloc2(sizeof(KeyValue *) * row->column_len, "Row.data");
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
    row->key = copy_value(destinct + priamry_key_set_off, primary_key_meta_column->column_type);
    return row;
}

/* Select through leaf node. */
static void select_from_leaf_node(SelectResult *select_result, QueryParam *query_param, void *leaf_node, Table *table, ROW_HANDLER row_handler, void *arg) {

    /* Get cell number, key length and value lenght. */
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* It`s necessary to use leaf node snapshot, beacuse when traversing cells, 
     * update or delete operation will change the data structure of leaf node,
     * which may causes bug.
     * */
    void *leaf_node_snapshot = copy_block(leaf_node, PAGE_SIZE);

    for (uint32_t i = 0; i < cell_num; i++) {

        /* Get leaf node cell value. */
        void *destinct = get_leaf_node_cell_value(leaf_node_snapshot, key_len, value_len, i);

        /* Check if the row data include, in another word, check if the row data satisfy the condition. */
        if (!include_leaf_node(destinct, query_param->condition_node, table->meta_table))
            continue;

        /* If satisfied, exeucte row handler function. */
        Row *row = generate_row(destinct, query_param, table->meta_table);
        row_handler(row, select_result, table, arg);
        /* Free useless row. */
        free_row(row);
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
     * which may causes bug.
     * */
    void *internal_node_snapshot = copy_block(internal_node, PAGE_SIZE);

    /* Loop for each interanl node cell to check if satisfy condition. */
    int32_t i;
    for (i = 0; i < keys_num; i++) {

        /* Check if index column, use index to avoid full text scanning. */
        {
            /* Current internal node cell key as max key, previous cell key as min key */
            void *max_key = get_internal_node_keys(internal_node_snapshot, i, key_len); 
            void *min_key = i == 0 ? NULL : get_internal_node_keys(internal_node_snapshot, i - 1, key_len);

            ConditionNode *condition_node = query_param->condition_node;
            if (!include_internal_node(min_key, max_key, condition_node, table->meta_table))
                continue;
        }

        /* Check other non-key column */
        uint32_t page_num = get_internal_node_child(internal_node_snapshot, i, key_len);
        void *node = get_page(table->pager, page_num);
        switch (get_node_type(node)) {
            case LEAF_NODE:
                select_from_leaf_node(select_result, query_param, node, table, row_handler, arg);
                break;
            case INTERNAL_NODE:
                select_from_internal_node(select_result, query_param, node, table, row_handler, arg);
                break;
        }
    }

    /* Don`t forget the right child. */
    uint32_t right_child_page_num = get_internal_node_right_child(internal_node_snapshot);
    /* Zero means there is no page. */
    if (right_child_page_num == 0) return;
    void *right_child = get_page(table->pager, right_child_page_num);
    switch (get_node_type(right_child)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, query_param, right_child, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, query_param, right_child, table, row_handler, arg);
            break;
    }
}

/* Convert from select node to query param */
QueryParam *convert_query_param(SelectNode *select_node) {
    QueryParam *query_param = db_malloc2(sizeof(QueryParam), "QueryParam");
    query_param->table_name = strdup(select_node->table_name);
    query_param->select_items = copy_select_items_node(select_node->select_items_node);
    ConditionNode *condition_node_copy = copy_condition_node(select_node->condition_node);
    query_param->condition_node = tree(condition_node_copy); // generate condition tree.
    clean_next(query_param->condition_node);
    return query_param;
}

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name) {
    SelectResult *select_result = db_malloc2(sizeof(SelectResult), "SelectResult");
    select_result->row_size = 0;
    select_result->table_name = strdup(table_name);
    select_result->sum.i = 0;
    return select_result;
}

/* Generate select reuslt. */
static void gen_select_result(QueryParam *query_param, SelectResult *select_result, ROW_HANDLER row_handler, void *arg) {
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return;
    void *root = get_page(table->pager, table->root_page_num);
    switch (get_node_type(root)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, query_param, root, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, query_param, root, table, row_handler, arg);
            break;
    }
}

/* Query with condition. */
void query_with_condition(QueryParam *query_param, SelectResult *select_result ,ROW_HANDLER row_handler, void *arg) {
    gen_select_result(query_param, select_result, row_handler, arg);
}

/* Send row data. */
static void send_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    db_send("{");
    for (uint32_t j = 0; j < row->column_len; j++) {
        KeyValue *key_value = *(row->data + j);
        char *key_value_pair_str = get_key_value_pair_str(key_value->key, key_value->value, key_value->data_type);
        db_send(key_value_pair_str);
        db_free(key_value_pair_str);
        /* If not the last column, these is ',' to split. */
        if (j < row->column_len - 1)
            db_send(", ");
    }
    db_send("}");

    /* If not the last row, these is ',' to split. */
    select_result->row_index--;
    if (select_result->row_index > 0)
        db_send(", ");
}

/* Count number of row, used in the sql function count(1) */
void count_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    select_result->row_index++;
    select_result->row_size++;
}

/* Execute sum funciton */
static void sum_row(Row *row, SelectResult *select_result, Table *table, void *arg) {

    char buff[BUFF_SIZE]; 
    
    /* Only look for first content of row data. */;
    KeyValue *key_value = row->data[0];
    assert(strcasecmp(key_value->key, SUM_NAME) == 0);

    switch(key_value->data_type) {
        case T_INT:
        case T_BOOL:
        case T_CHAR:
            select_result->sum.i += *(int32_t *)key_value->value; 
            break;
        case T_FLOAT:
            select_result->sum.f += *(float *)key_value->value;
            break;
        case T_DOUBLE:
            select_result->sum.d += *(double *)key_value->value;
            break;
        default:
            select_result->sum.i += 0;
            select_result->sum.f += 0;
            select_result->sum.d += 0;
            break;
    }

    select_result->row_index--;

    /* Send out sum result. 
     * Trigger when row index is zero, which means the last row. 
     * */
    if (select_result->row_index == 0) {
        switch(key_value->data_type) {
            case T_INT:
            case T_BOOL:
            case T_CHAR:
                sprintf(buff, "{%s: %d}\n", SUM_NAME, select_result->sum.i);
                break;
            case T_FLOAT:
                sprintf(buff, "{%s: %f}\n", SUM_NAME, select_result->sum.f);
                break;
            case T_DOUBLE:
                sprintf(buff, "{%s: %fd}\n", SUM_NAME, select_result->sum.d);
                break;
            default:
                sprintf(buff, "{%s: 0}\n", SUM_NAME);
                break;
        }
        db_send(buff);
    }
}


/* Execute avg funciton */
static void avg_row(Row *row, SelectResult *select_result, Table *table, void *arg) {

    char buff[BUFF_SIZE]; 
    
    /* Only look for first content of row data. */;
    KeyValue *key_value = row->data[0];
    assert(strcasecmp(key_value->key, SUM_NAME) == 0);

    switch(key_value->data_type) {
        case T_INT:
        case T_BOOL:
        case T_CHAR:
            select_result->sum.i += *(int *)key_value->value; 
            break;
        case T_FLOAT:
            select_result->sum.f += *(float *)key_value->value;
            break;
        case T_DOUBLE:
            select_result->sum.d += *(double *)key_value->value;
            break;
        default:
            select_result->sum.i += 0;
            select_result->sum.f += 0;
            select_result->sum.d += 0;
            break;
    }

    select_result->row_index--;

    /* Send out sum result. 
     * Trigger when row index is zero, which means the last row. 
     * */
    if (select_result->row_index == 0) {
        switch(key_value->data_type) {
            case T_INT:
            case T_BOOL:
            case T_CHAR:
                sprintf(buff, "{%s: %d}\n", AVG_NAME, select_result->sum.i / select_result->row_size);
                break;
            case T_FLOAT:
                sprintf(buff, "{%s: %f}\n", AVG_NAME, select_result->sum.f / select_result->row_size);
                break;
            case T_DOUBLE:
                sprintf(buff, "{%s: %fd}\n", AVG_NAME, select_result->sum.d / select_result->row_size);
                break;
            default:
                sprintf(buff, "{%s: 0}\n", AVG_NAME);
                break;
        }
        db_send(buff);
    }
}

/* Execute max function. */
static void max_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    
    /* Only look for first content of row data. */;
    KeyValue *key_value = row->data[0];

    /* At first, the max row is null. */
    if (select_result->max_row == NULL) 
        select_result->max_row = copy_row(row);
    else {
        Row *max_row = select_result->max_row;
        KeyValue *max_row_key_value = max_row->data[0];
        /* If current row value greater than max row, assign current row as the max row. */
        if (greater(key_value->value, max_row_key_value->value, key_value->data_type)) {
            free_row(select_result->max_row);
            select_result->max_row = copy_row(row);
        }
    }

    /* Send out max row result. 
     * Trigger when row index is zero, which means the last row. 
     * */
    select_result->row_index--;
    if (select_result->row_index == 0) {
        send_row(select_result->max_row, select_result, table, arg);
        db_send("\n");
    }
}

/* Execute min function. */
static void min_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    
    /* Only look for first content of row data. */;
    KeyValue *key_value = row->data[0];

    /* At first, the min row is null, initilise it. */
    if (select_result->min_row == NULL) 
        select_result->min_row = copy_row(row);
    else {
        /* If current row value less than min row, assign current row as the mix row. */
        Row *min_row = select_result->min_row;
        KeyValue *min_row_key_value = min_row->data[0];
        if (less(key_value->value, min_row_key_value->value, key_value->data_type)) {
            free_row(select_result->min_row);
            select_result->min_row = copy_row(row);
        }
    }

    /* Send out mix row result. 
     * Trigger when row index is zero, which means the last row. 
     * */
    select_result->row_index--;
    if (select_result->row_index == 0) {
        send_row(select_result->min_row, select_result, table, arg);
        db_send("\n");
    }
}


/* Execute aggregate function count(). */
static void exec_function_count(QueryParam *query_param) {

    char buff[BUFF_SIZE];

    /* Generate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);
    
    /* Compose count result info and send out. */
    sprintf(buff, "{%s: %d}\n", COUNT_NAME, select_result->row_size);
    db_send(buff);
}

/* Execute aggregate function sum(). */
static void exec_function_sum(QueryParam *query_param) {
     
    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Sum row. */
    query_with_condition(query_param, select_result, sum_row, NULL);

} 

/* Execute aggregate function avg(). */
static void exec_function_avg(QueryParam *query_param) {

    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Avg row. */
    query_with_condition(query_param, select_result, avg_row, NULL);
}

/* Execute aggregate function max(). */
static void exec_function_max(QueryParam *query_param) {
    
    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Max row. */
    query_with_condition(query_param, select_result, max_row, NULL);
}

/* Execute aggregate function min(). */
static void exec_function_min(QueryParam *query_param) {

    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Min row. */
    query_with_condition(query_param, select_result, min_row, NULL);
}


/* Execute function select statement. 
 * Now supported aggregate function:
 *     COUNT
 *     SUM
 *     AVG
 *     MAX
 *     MIN
 * */
static void exec_function_select_statement(QueryParam *query_param) {
    FunctionNode *function_node = query_param->select_items->function_node;
    switch(function_node->function_type) {
        case F_COUNT:
            exec_function_count(query_param);
            break;
        case F_SUM:
            exec_function_sum(query_param);
            break;
        case F_AVG:
            exec_function_avg(query_param);
            break;   
        case F_MAX:
            exec_function_max(query_param);
            break;
        case F_MIN:
            exec_function_min(query_param);
            break;
    }
}


/* Execute plain select statement. 
 * For plain select statment (without sql function in select items), 
 * at first, execute count row function to get satisfied row number which
 * is important for next select operation.
 * */
static void exec_plain_select_statement(QueryParam *query_param) {

    /* Genrate select result. */
    SelectResult *select_result = new_select_result(query_param->table_name);

    /* Count row number. */
    query_with_condition(query_param, select_result, count_row, NULL);

    /* Send row data in json format. */
    db_send("[");
    query_with_condition(query_param, select_result, send_row, NULL);
    db_send("]\n");

    free_select_result(select_result);
}


/* Execute select statement. */
ExecuteResult exec_select_statement(SelectNode *select_node) {
    QueryParam *query_param = convert_query_param(select_node);
    if (check_query_param(query_param)) {
        switch(query_param->select_items->type) {
            case SELECT_ALL:
            case SELECT_COLUMNS:
                exec_plain_select_statement(query_param);
                break;
            case SELECT_FUNCTION:
                exec_function_select_statement(query_param);
                break;
        }
    }
    free_query_param(query_param);
    return EXECUTE_SUCCESS;
}
