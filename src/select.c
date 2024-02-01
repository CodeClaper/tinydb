/*
 * ================================ Select Module ============================================
 * Select modeule support select statment. 
 * Besides, Update statement, delete statement also use these module for query under conditon.
 * ===========================================================================================
 * */
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
#include "copy.h"
#include "free.h"
#include "index.h"
#include "log.h"
#include "mmu.h"
#include "meta.h"
#include "ltree.h"
#include "compare.h"
#include "pager.h"
#include "select.h"
#include "table.h"
#include "asserts.h"
#include "session.h"
#include "lock.h"
#include "trans.h"
#include "refer.h"
#include "utils.h"
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
static MetaColumn *get_cond_meta_column(PredicateNode *predicate, MetaTable *meta_table);

/* Calulate offset of every column in cell. */
static uint32_t calc_offset(MetaTable *meta_table, char *column_name) {
    uint32_t off_set = 0;
    int i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0)
            break;
        off_set += meta_column->column_length;
    }
    return off_set;
}

/* Get value from value item node. */
void *get_value_from_value_item_node(ValueItemNode *value_item_node, MetaColumn *meta_column) {
    /* User can use '%s' fromat in sql to pass multiple types value including char, string, date, timestamp. 
     * So we must use meta column data type to define which data type of the value. */
    switch (meta_column->column_type) { 
        case T_CHAR: {
            switch (value_item_node->data_type) {
                case T_STRING:
                    value_item_node->data_type = T_CHAR;
                    return value_item_node->s_value;
                default:
                    db_log(PANIC, "Data type error.");
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
                    db_log(PANIC, "Data type error.");
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
                    db_log(PANIC, "Data type error.");
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
                    db_log(PANIC, "Data type error.");
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
                    db_log(PANIC, "Data type error.");
             }
             break;
        }
        case T_REFERENCE: {
            switch (value_item_node->r_value->type) {
                case DIRECTLY:
                    db_log(ERROR, "Not support directly fetch refer when query.");
                    return make_null_refer();
                case INDIRECTLY: {
                    return fetch_refer(meta_column, value_item_node->r_value->condition);
                }
            }
            break;
        }
        default:
            db_log(PANIC, "Not implement yet.");
    }
    return NULL;
}

/* Check if include internal comparison predicate. */
static bool include_internal_comparison_predicate(void *min_key, void *max_key, ComparisonNode *comparison, MetaTable *meta_table) {
    MetaColumn *meta_column = get_meta_column_by_name(meta_table, comparison->column->column_name);
    void *target_key = get_value_from_value_item_node(comparison->value, meta_column);
    DataType data_type = meta_column->column_type;
    switch (comparison->type) {
        case O_EQ:
            return less(min_key, target_key, data_type) && less_equal(target_key, max_key, data_type);
        case O_NE:
            return !(less(min_key, target_key, data_type) && less_equal(target_key, max_key, data_type));
        case O_GT:
            return greater(max_key, target_key, data_type);
        case O_GE:
            return greater_equal(max_key, target_key, data_type);
        case O_LT:
            return greater(target_key, min_key, data_type);
        case O_LE:
            return greater(target_key, min_key, data_type);
        default:
            db_log(PANIC, "Unknown compare type.");
    }
}


/* Check if include the internal predicate. */
static bool include_internal_predicate(void *min_key, void *max_key, PredicateNode *predicate, MetaTable *meta_table) {
    switch (predicate->type) {
        case PRE_COMPARISON:
            return include_internal_comparison_predicate(min_key, max_key, predicate->comparison, meta_table);
        /* For in or like predicate, no skip include. */
        case PRE_IN:
        case PRE_LIKE:
            return true;
    }
}


/* Check if include the internal node if condition is logic condition. */
static bool include_logic_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {
    /* For logic condition node, check left node and right node. */
    switch(condition_node->conn_type) {
        case C_AND:
           return include_internal_node(min_key, max_key, condition_node->left, meta_table) && include_internal_node(max_key, max_key, condition_node->right, meta_table);
        case C_OR:
           return include_internal_node(min_key, max_key, condition_node->left, meta_table) || include_internal_node(max_key, max_key, condition_node->right, meta_table);
        case C_NONE:
            db_log(PANIC, "System logic error.");
    } 
}

/* Check if include the internal node if condition is exec condition. */
static bool include_exec_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    assert_true(condition_node->conn_type == C_NONE, "System logic error.");
    
    MetaColumn *cond_meta_column = get_cond_meta_column(condition_node->predicate, meta_table);

    /* Skipped the internal node must satisfy tow factors: 
     * key column and not satisfied internal node condition. */
    return !cond_meta_column->is_primary 
        || include_internal_predicate(min_key, max_key, condition_node->predicate, meta_table);
}

/* Check if include the internal node. */
static bool include_internal_node(void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course return true. */
    if (condition_node == NULL)
        return true;

    /* According to condition node type, has different way. */
    switch(condition_node->conn_type) {
        case C_OR:
        case C_AND:
            return include_logic_internal_node(min_key, max_key, condition_node, meta_table);
        case C_NONE:
            return include_exec_internal_node(min_key, max_key, condition_node, meta_table);
    }
}

/* Check if include leaf node if the condition is logic condition. */
static bool include_logic_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {
    switch(condition_node->conn_type) {
        case C_AND:
            return include_leaf_node(destinct, condition_node->left, meta_table) && include_leaf_node(destinct, condition_node->right, meta_table);
        case C_OR:
            return include_leaf_node(destinct, condition_node->left, meta_table) || include_leaf_node(destinct, condition_node->right, meta_table);
        case C_NONE:
            db_log(PANIC, "System Logic Error");
    } 
}


/* Check if include leaf node satisfy comparison predicate. */
static bool include_leaf_comparison_predicate(void *destinct, ComparisonNode *comparison, MetaTable *meta_table) {
    int i; uint32_t off_set = 0;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        /* Define the column. */
        if (strcmp(meta_column->column_name, comparison->column->column_name) == 0) {
            void *value = destinct + off_set;
            void *target = get_value_from_value_item_node(comparison->value, meta_column);
            return eval(comparison->type, value, target, meta_column->column_type);
        }
        off_set += meta_column->column_length;
    }
    return false;
}

/* Check if include in value item set. */
static bool check_in_value_item_set(ValueItemSetNode *value_item_set_node, void *value, MetaColumn *meta_column) {
    int i;
    for (i = 0; i < value_item_set_node->num; i++) {
        void *target = get_value_from_value_item_node(value_item_set_node->value_item_node[i], meta_column);
        if (equal(value, target, meta_column->column_type))
            return true;
    }
    return false;
}

/* Check if include leaf node satisfy in predicate. */
static bool include_leaf_in_predicate(void *destinct, InNode *in_node, MetaTable *meta_table) {
    int i; uint32_t off_set = 0;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        /* Define the column. */
        if (strcmp(meta_column->column_name, in_node->column->column_name) == 0) {
            void *value = destinct + off_set;
            return check_in_value_item_set(in_node->value_set, value, meta_column);
        }
        off_set += meta_column->column_length;
    }
    return false;
}

/* Check if satisfy like string value. */
static bool check_like_string_value(char *value, char *target) {
    int value_len = strlen(value);
    int target_len = strlen(target);
    if (value_len == 0 || target_len == 0)
        return false;

    if (target[0] == '%' && target[target_len - 1] == '%') {
        char str_dup[target_len];
        memset(str_dup, 0, target_len);
        memcpy(str_dup, target + 1, target_len -2);
        contains(value, str_dup);
    }
    else if (target[0] == '%')
        return endwith(value, target + 1);
    else if (target[target_len - 1] == '%') {
        char str_dup[target_len];
        memset(str_dup, 0, target_len);
        memcpy(str_dup, target, target_len - 1);
        return startwith(value, str_dup);
    } 
    else 
        return strcmp(value, target) == 0;
}


/* Check if include leaf node satisfy like predicate. */
static bool include_leaf_like_predicate(void *destinct, LikeNode *like_node, MetaTable *meta_table) {
    int i; uint32_t off_set = 0;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Define the column. */
        if (strcmp(meta_column->column_name, like_node->column->column_name) == 0) {
            void *value = destinct + off_set;
            void *target = get_value_from_value_item_node(like_node->value, meta_column);
            return check_like_string_value(value, target);
        }
        off_set += meta_column->column_length;
    }
    return false;
}

/* Check if include leaf node if the condition is exec condition. */
static bool include_exec_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course the key include, so just return true. */
    if (condition_node == NULL)
        return true;

    assert_true(condition_node->conn_type == C_NONE, "System logic error.");

    PredicateNode *predicate = condition_node->predicate;

    switch (predicate->type) {
        case PRE_COMPARISON:
            return include_leaf_comparison_predicate(destinct, predicate->comparison, meta_table);
        case PRE_IN:
            return include_leaf_in_predicate(destinct, predicate->in, meta_table);
        case PRE_LIKE:
            return include_leaf_like_predicate(destinct, predicate->like, meta_table);
    }

}

/* Check if the key include the leaf node. */
static bool include_leaf_node(void *destinct, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course the key include, so just return true. */
    if (condition_node == NULL) 
          return true;

    switch(condition_node->conn_type) {
        case C_OR:
        case C_AND:
            return include_logic_leaf_node(destinct, condition_node, meta_table);
        case C_NONE:
            return include_exec_leaf_node(destinct, condition_node, meta_table);
    }
}

/* Get meta column by condition name. */
static MetaColumn *get_cond_meta_column(PredicateNode *predicate, MetaTable *meta_table) {
    if (predicate == NULL)
        return NULL;
    switch (predicate->type)  {
        case PRE_COMPARISON:
            return get_meta_column_by_name(meta_table, predicate->comparison->column->column_name);
        case PRE_LIKE:
            return get_meta_column_by_name(meta_table, predicate->like->column->column_name);
        case PRE_IN:
            return get_meta_column_by_name(meta_table, predicate->in->column->column_name);
        default:
            db_log(ERROR, "Unknown predicate type.");
    }
}

/* Generate select row. */
static Row *generate_row(void *destinct, MetaTable *meta_table) {

    /* Define row data. */
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->column_len = meta_table->all_column_size;
    row->table_name = db_strdup(meta_table->table_name);
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);

    /* Assignment row data. */
    int i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        uint32_t off_set = calc_offset(meta_table, meta_column->column_name);
        
        /* Generate a key value pair. */
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->value = copy_value(destinct + off_set, meta_column->column_type, meta_column);
        key_value->data_type = meta_column->column_type;

        row->data[i] = key_value;

        if (meta_column->is_primary)
            row->key = copy_value(destinct + off_set, meta_column->column_type, meta_column);
    }

    return row;
}

/* Define row by refer. */
Row *define_row(Refer *refer) {
    /* Check table exists. */
    Table *table = open_table(refer->table_name);
    if (table == NULL) 
        return NULL;

    /* CHeck if refer null. */
    if (refer_null(refer))
        return NULL;

    /* Data */
    uint32_t key_len, value_len;
    value_len = calc_table_row_length(table);
    key_len = calc_primary_key_length(table);
    void *leaf_node = get_page(table->pager, refer->page_num);
    void *destinct = get_leaf_node_cell_value(leaf_node, key_len, value_len, refer->cell_num);

    return generate_row(destinct, table->meta_table);
}

/* Select through leaf node. */
static void select_from_leaf_node(SelectResult *select_result, ConditionNode *condition, uint32_t page_num, Table *table, ROW_HANDLER row_handler, void *arg) {

    void *leaf_node = get_page(table->pager, page_num);

    /* Get cell number, key length and value lenght. */
    uint32_t key_len, value_len, cell_num ;
    key_len = calc_primary_key_length(table);
    value_len = calc_table_row_length(table);
    cell_num = get_leaf_node_cell_num(leaf_node);

    /* It`s necessary to use leaf node snapshot, beacuse when traversing cells, 
     * update or delete operation will change the data structure of leaf node,
     * which may causes bug. */
    void *leaf_node_snapshot = copy_block(leaf_node, PAGE_SIZE);

    int i;
    for (i = 0; i < cell_num; i++) {
    
        /* Get leaf node cell value. */
        void *destinct = get_leaf_node_cell_value(leaf_node_snapshot, key_len, value_len, i);

        /* Check if the row data include, in another word, check if the row data satisfy the condition. */
        if (!include_leaf_node(destinct, condition, table->meta_table))
            continue;

        /* If satisfied, exeucte row handler function. */
        Row *row = generate_row(destinct, table->meta_table);

        /* Execute row handler. */
        row_handler(row, select_result, table, NULL);

        /* Free useless row. */
        free_row(row);
    }
    
    /* Free useless pointer. */
    db_free(leaf_node_snapshot);
}

/* Select through internal node. */
static void select_from_internal_node(SelectResult *select_result, ConditionNode *condition, void *internal_node, Table *table, ROW_HANDLER row_handler, void *arg) {

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

            if (!include_internal_node(min_key, max_key, condition, table->meta_table))
                continue;
        }

        /* Check other non-key column */
        uint32_t page_num = get_internal_node_child(internal_node_snapshot, i, key_len);
        void *node = get_page(table->pager, page_num);
        switch (get_node_type(node)) {
            case LEAF_NODE:
                select_from_leaf_node(select_result, condition, page_num, table, row_handler, arg);
                break;
            case INTERNAL_NODE:
                select_from_internal_node(select_result, condition, node, table, row_handler, arg);
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
            select_from_leaf_node(select_result, condition, right_child_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, condition, right_child, table, row_handler, arg);
            break;
    }

    /* free memory. */
    db_free(internal_node_snapshot);
}

/* Convert from select node to query param */
QueryParam *convert_query_param(SelectNode *select_node) {
    QueryParam *query_param = db_malloc(sizeof(QueryParam), SDT_QUERY_PARAM);
    query_param->table_name = db_strdup(select_node->table_name);
    query_param->selection = copy_selection_node(select_node->selection);
    query_param->condition_node = copy_condition_node(select_node->condition_node);
    query_param->limit_node = copy_limit_node(select_node->limit_node);
    return query_param;
}

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name) {
    SelectResult *select_result = db_malloc(sizeof(SelectResult), SDT_SELECT_RESULT);
    select_result->row_size = 0;
    select_result->row_index = 0;
    select_result->limit_index = 0;
    select_result->table_name = db_strdup(table_name);
    select_result->sum = 0;
    select_result->rows = NULL;
    return select_result;
}

/* Query with condition. */
void query_with_condition(ConditionNode *condition, SelectResult *select_result, ROW_HANDLER row_handler, void *arg) {
    Table *table = open_table(select_result->table_name);
    if (table == NULL)
        return;
    void *root = get_page(table->pager, table->root_page_num);
    switch (get_node_type(root)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, condition, table->root_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, condition, root, table, row_handler, arg);
            break;
    }
}

/* Count number of row, used in the sql function count(1) */
void count_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    /* Only select visible row. */
    if (!row_is_visible(row)) 
        return;
    select_result->row_size++;
}

/* Select row data. */
void select_row(Row *row, SelectResult *select_result, Table *table, void *arg) {
    /* Only select visible row. */
    if (!row_is_visible(row)) 
        return;
    select_result->rows[select_result->row_index++] = copy_row_without_reserved(row);
}


/* Check if exists function type scalar exp. */
static bool exists_function_scalar_exp(ScalarExpSetNode *scalar_exp_set) {
    int i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        if (scalar_exp_set->data[i]->type == SCALAR_FUNCTION)
            return true;
    }
    return false;
}


/* Get KeyValue from a Row.
 * return NULL if not found. */
static KeyValue *get_key_value_from_row(Row *row, char *column_name) {
    int i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (strcmp(column_name, key_value->key) == 0)
            return key_value;
    }
    return NULL;
}

/* Calulate column sum value. */
static void calc_column_sum_value(KeyValue *key_value, ColumnNode *column, SelectResult *select_result) {
    Table *table = open_table(select_result->table_name);
    MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column->column_name);

    double sum = 0;
    switch (meta_column->column_type) {
        case T_INT: {
            int i ;
            for (i = 0; i < select_result->row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(int32_t *)key_value->value;
            }
            break;
        }
        case T_LONG: {
            int i ;
            for (i = 0; i < select_result->row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(int64_t *)key_value->value;
            }
            break;
        }
        case T_FLOAT: {
            int i ;
            for (i = 0; i < select_result->row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(float *)key_value->value;
            }
            break;
        }
        case T_DOUBLE: {
            int i ;
            for (i = 0; i < select_result->row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(double *)key_value->value;
            }
            break;
        }
        default: {
            sum = 0;
            break;
        }

    }

    key_value->value = copy_value(&sum, T_DOUBLE, NULL);
    key_value->data_type = T_DOUBLE;
}


/* Calulate column avg value. */
static void calc_column_avg_value(KeyValue *key_value, ColumnNode *column, SelectResult *select_result) {
    Table *table = open_table(select_result->table_name);
    MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column->column_name);
    int row_size = select_result->row_size;

    double avg = 0;
    switch (meta_column->column_type) {
        case T_INT: {
            double sum = 0;
            int i ;
            for (i = 0; i < row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(int32_t *)key_value->value;
            }
            avg = sum / row_size;
            break;
        }
        case T_LONG: {
            double sum = 0;
            int i ;
            for (i = 0; i < row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(int64_t *)key_value->value;
            }
            avg = sum / row_size;
            break;
        }
        case T_FLOAT: {
            double sum = 0;
            int i ;
            for (i = 0; i < select_result->row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(float *)key_value->value;
            }
            avg = sum / row_size;
            break;
        }
        case T_DOUBLE: {
            double sum = 0;
            int i ;
            for (i = 0; i < select_result->row_size; i++) {
                Row *row = select_result->rows[i];
                KeyValue *key_value = get_key_value_from_row(row, column->column_name);
                assert_not_null(key_value, "Not found column '%s' in table '%s' row. ", column->column_name, table->meta_table->table_name);
                sum += *(double *)key_value->value;
            }
            avg = sum / row_size;
            break;
        }
        default: {
            avg = 0;
            break;
        }
    }

    key_value->data_type = T_DOUBLE;
    key_value->value = copy_value(&avg, T_DOUBLE, NULL);
}


/* Calulate column max value.*/
static void calc_column_max_value(KeyValue *key_value, ColumnNode *column, SelectResult *select_result) {
    Table *table = open_table(select_result->table_name);
    MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column->column_name);

    void *max_value = NULL;
    int i;
    for (i = 0; i < select_result->row_size; i++) {
        Row *row = select_result->rows[i];
        KeyValue *current = get_key_value_from_row(row, column->column_name);
        void *current_value = current->value;
        if (max_value == NULL || greater(current_value, max_value, meta_column->column_type)) {
            max_value = current_value;
        }
    }

    key_value->value = copy_value(max_value, meta_column->column_type, NULL);
    key_value->data_type = meta_column->column_type;

}

/* Calulate column max value.*/
static void calc_column_min_value(KeyValue *key_value, ColumnNode *column, SelectResult *select_result) {
    Table *table = open_table(select_result->table_name);
    MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column->column_name);

    void *min_value = NULL;
    int i;
    for (i = 0; i < select_result->row_size; i++) {
        Row *row = select_result->rows[i];
        KeyValue *current = get_key_value_from_row(row, column->column_name);
        void *current_value = current->value;
        if (min_value == NULL || less(current_value, min_value, meta_column->column_type)) {
            min_value = current_value;
        }
    }

    key_value->value = copy_value(min_value, meta_column->column_type, NULL);
    key_value->data_type = meta_column->column_type;

}


/* Query count function. */
static KeyValue *query_count_function(FunctionValueNode *value, SelectResult *selct_result) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("count");
    key_value->data_type = T_INT;
    key_value->value = copy_value(&selct_result->row_size, T_INT, NULL);
    return key_value;
}

/* Query sum function. */
static KeyValue *query_sum_function(FunctionValueNode *value, SelectResult *select_result) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("sum");

    switch (value->value_type) {
        case V_COLUMN: {
            calc_column_sum_value(key_value, value->column, select_result);
            break;
        }
        case V_INT: {
            double sum = value->i_value * select_result->row_size;
            key_value->value = copy_value(&sum, T_DOUBLE, NULL);
            key_value->data_type = T_DOUBLE;
            break;
        }
        case V_ALL: {
            db_log(PANIC, "Sum function not support '*'");
            break;
        }
    }

    return key_value;
}

/* Query avg function. */
KeyValue *query_avg_function(FunctionValueNode *value, SelectResult *select_result) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("avg");

    switch (value->value_type) {
        case V_COLUMN: {
            calc_column_avg_value(key_value, value->column, select_result);
            break;
        }
        case V_INT: {
            double sum = value->i_value;
            key_value->value = copy_value(&sum, T_DOUBLE, NULL);
            key_value->data_type = T_DOUBLE;
            break;
        }
        case V_ALL: {
            db_log(PANIC, "Avg function not support '*'");
            break;
        }
    }

    return key_value;
}

/* Query max function. */
KeyValue *query_max_function(FunctionValueNode *value, SelectResult *select_result) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("max");

    switch (value->value_type) {
        case V_COLUMN: {
            calc_column_max_value(key_value, value->column, select_result);
            break;
        }
        case V_INT: {
            key_value->value = copy_value(&value->i_value, T_INT, NULL);
            key_value->data_type = T_INT;
            break;
        }
        case V_ALL: {
            db_log(PANIC, "Max function not support '*'");
            break;
        }
    }
    return key_value;
} 


/* Query min function. */
KeyValue *query_min_function(FunctionValueNode *value, SelectResult *select_result) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("min");

    switch (value->value_type) {
        case V_COLUMN: {
            calc_column_min_value(key_value, value->column, select_result);
            break;
        }
        case V_INT: {
            key_value->value = copy_value(&value->i_value, T_INT, NULL);
            key_value->data_type = T_INT;
            break;
        }
        case V_ALL: {
            db_log(PANIC, "Min function not support '*'");
            break;
        }
    }
    return key_value;
} 

static KeyValue *query_scalar_function(FunctionNode *function, SelectResult *select_result) {
    switch (function->type) { 
        case F_COUNT:
            return query_count_function(function->value, select_result);
        case F_SUM:
            return query_sum_function(function->value, select_result);
        case F_AVG:
            return query_avg_function(function->value, select_result);
        case F_MAX:
            return query_max_function(function->value, select_result);
        case F_MIN:
            return query_min_function(function->value, select_result);
        default:
            db_log(ERROR, "Not implement function yet.");
    }
}

static KeyValue *query_scalar_column(ColumnNode *column, SelectResult *select_result) {
    Table *table = open_table(select_result->table_name);
    if (select_result->row_size == 0) {
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = strdup(column->column_name);
        key_value->value = NULL;
        return key_value;
    } else {
        Row *first_row = select_result->rows[0];
        int i;
        for (i = 0;  i < first_row->column_len; i++) {
            KeyValue *key_value = first_row->data[i];
            if (strcmp(column->column_name, key_value->key) == 0)
                return copy_key_value(key_value, table->meta_table);
        }
        db_log(PANIC, "Not found column '%s' in table '%s'", column->column_name, table->meta_table->table_name);
    }
}

/* Query column value. */
static KeyValue *query_column_value(ScalarExpNode *scalar_exp, SelectResult *select_result) {
    switch (scalar_exp->type) {
        case SCALAR_COLUMN:
            return query_scalar_column(scalar_exp->column, select_result);
        case SCALAR_FUNCTION:
            return query_scalar_function(scalar_exp->function, select_result);
    } 
}

/* Query function data. */
static void query_function_data(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->table_name = db_strdup(select_result->table_name);
    row->column_len = scalar_exp_set->size;
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);

    int i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *sclar_exp = scalar_exp_set->data[i];
        row->data[i] = query_column_value(sclar_exp, select_result);        
    }

    select_result->row_size = 1;
    select_result->rows[0] = row;
}

/* Check column if exists in ScalarExpSetNode */
static bool exists_in_scalr_exp_set(char *column_name, ScalarExpSetNode *scalar_exp_set) {
    int i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp_node = scalar_exp_set->data[i];
        if (scalar_exp_node->type == SCALAR_COLUMN && strcmp(column_name, scalar_exp_node->column->column_name) == 0)
            return true;
    }
    return false;
}

/* Copy a Row with Selection,
 * Actually, the Selection is all-column. */
static Row *copy_row_by_selection(ScalarExpSetNode *scalar_exp_set, Row *row) {
    
    Table *table = open_table(row->table_name);
    MetaColumn *key_meta_column = get_primary_key_meta_column(table->meta_table);

    Row *copy = db_malloc(sizeof(Row), SDT_ROW);
    copy->key = copy_value(row->key, key_meta_column->column_type, key_meta_column);
    copy->table_name = db_strdup(row->table_name);
    copy->column_len = scalar_exp_set->size;
    copy->data = db_malloc(sizeof(KeyValue *) * copy->column_len, SDT_POINTER);

    int i, j;
    for (i = 0, j = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (exists_in_scalr_exp_set(key_value->key, scalar_exp_set)) {
            copy->data[j++] = copy_key_value(key_value, table->meta_table);
        }
    }

    assert_true(copy->column_len == j, "System Logic Error");

    return copy;
}

/* Query all columns data. */
static void query_all_column_data(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {
    int i;
    for (i = 0; i < select_result->row_size; i++) {
        Row *row = select_result->rows[i];
        select_result->rows[i] = copy_row_by_selection(scalar_exp_set, row);
        db_free(row);
    }
}

/* Query selection. */
static void query_with_selection(SelectionNode *selection, SelectResult *select_result) {
    if (selection->all_column)
        return;

    if (exists_function_scalar_exp(selection->scalar_exp_set)) {
        query_function_data(selection->scalar_exp_set, select_result);
    } else {
        query_all_column_data(selection->scalar_exp_set, select_result);
    }
}

/* Execute select statement. */
void exec_select_statement(SelectNode *select_node, DBResult *result) {
    QueryParam *query_param = convert_query_param(select_node);
    if (check_query_param(query_param)) {
        /* Genrate select result. */
        SelectResult *select_result = new_select_result(query_param->table_name);

        /* Count row number. */
        query_with_condition(query_param->condition_node, select_result, count_row, NULL);

        /* Prepare enough memory space. */
        select_result->rows = db_malloc(sizeof(Row *) * select_result->row_size, SDT_POINTER);

        select_result->limit_index = 0;

        /* Put rows to buffer. */
        query_with_condition(query_param->condition_node, select_result, select_row, NULL);

        /* Query Selection. */
        query_with_selection(query_param->selection, select_result);

        /* If select all, return all row data. */
        result->rows = select_result->row_size;
        result->data = select_result;
        result->success = true;

        /* success result. */
        db_log(SUCCESS, "Query data successfully.");
    }

    free_query_param(query_param);
}
