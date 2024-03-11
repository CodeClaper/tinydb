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

/* Query column value. */
static KeyValue *query_function_value(ScalarExpNode *scalar_exp, SelectResult *select_result);

/* Query row value. */
static KeyValue *query_row_value(ScalarExpNode *scalar_exp, Row *row);

/* Query a Row of Selection,
 * Actually, the Selection is all-column. */
static Row *query_plain_row_selection(ScalarExpSetNode *scalar_exp_set, Row *row);

/* Generate select row. */
static Row *generate_row(void *destinct, MetaTable *meta_table);

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
                    db_log(WARN, "Not support directly fetch refer when query.");
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
    if (target_key == NULL)
        return false;
    DataType data_type = meta_column->column_type;

    bool result = false;
    switch (comparison->type) {
        case O_EQ:
            result = less(min_key, target_key, data_type) && less_equal(target_key, max_key, data_type);
            break;
        case O_NE:
            result = !(less(min_key, target_key, data_type) && less_equal(target_key, max_key, data_type));
            break;
        case O_GT:
            result = greater(max_key, target_key, data_type);
            break;
        case O_GE:
            result = greater_equal(max_key, target_key, data_type);
            break;
        case O_LT:
            result = greater(target_key, min_key, data_type);
            break;
        case O_LE:
            result = greater(target_key, min_key, data_type);
            break;
        default:
            db_log(PANIC, "Unknown compare type.");
    }

    if (meta_column->column_type == T_REFERENCE)
        free_refer((Refer *) target_key);
    return result;
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

/* Check the row predicate. */
static bool check_row_predicate(Row *row, ColumnNode *column, ComparisonNode *comparison) {
    Table *table = open_table(row->table_name);
    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (strcmp(key_value->key, column->column_name) == 0) {
            bool ret;
            MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, key_value->key);
            if (column->has_sub_column) {
                /* If has sub column, must be Reference. */
                if (meta_column->column_type != T_REFERENCE)
                    db_log(ERROR, "Column '%s' is not Reference, no sub rows found", column->column_name);
                /* Get subrow, and recursion. */
                Refer *refer = key_value->value;
                Row *sub_row = define_row(refer);
                ret = check_row_predicate(sub_row, column->sub_column, comparison); 
            } else {
                void *target = get_value_from_value_item_node(comparison->value, meta_column);
                ret = eval(comparison->type, key_value->value, target, meta_column->column_type);
                /* Reference data is allocated, so free it. */
                if (meta_column->column_type == T_REFERENCE)
                    free_refer(target);
            }
            return ret;
        }
    }
    db_log(ERROR, "System logic error, not found column '%s' in table '%s'.", column->column_name, table->meta_table->table_name);
}


/* Check if include leaf node satisfy comparison predicate. */
static bool include_leaf_comparison_predicate(void *destinct, ComparisonNode *comparison, MetaTable *meta_table) {
    Row *row = generate_row(destinct, meta_table);
    return check_row_predicate(row, comparison->column, comparison);
}

/* Check if include in value item set. */
static bool check_in_value_item_set(ValueItemSetNode *value_item_set_node, void *value, MetaColumn *meta_column) {
    bool ret = false;
    int i;
    for (i = 0; i < value_item_set_node->num; i++) {
        void *target = get_value_from_value_item_node(value_item_set_node->value_item_node[i], meta_column);
        ret = equal(value, target, meta_column->column_type);

        /* Reference data is allocated, so free it. */
        if (meta_column->column_type == T_REFERENCE)
            free_refer(target);

        if (ret)
            break;
    }
    return ret;
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
    bool ret = false;
    uint32_t off_set = 0;

    int i; 
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Define the column. */
        if (strcmp(meta_column->column_name, like_node->column->column_name) == 0) {
            void *value = destinct + off_set;
            void *target = get_value_from_value_item_node(like_node->value, meta_column);
            ret = check_like_string_value(value, target);

            /* Reference data is allocated, so free it. */
            if (meta_column->column_type == T_REFERENCE)
                free_refer(target);

            break;
        }
        off_set += meta_column->column_length;
    }
    return ret;
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

        /* Get the column offset. */
        uint32_t offset = calc_offset(meta_table, meta_column->column_name);
        
        /* Generate a key value pair. */
        KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->value = copy_value(destinct + offset, meta_column->column_type);
        key_value->data_type = meta_column->column_type;

        row->data[i] = key_value;

        if (meta_column->is_primary)
            row->key = copy_value(destinct + offset, meta_column->column_type);
    }

    return row;
}

/* Define row by refer. */
Row *define_row(Refer *refer) {
    /* Check table exists. */
    Table *table = open_table(refer->table_name);
    if (table == NULL) 
        return NULL;

    /* Check if refer null. */
    if (refer_null(refer))
        return NULL;

    /* Data */
    uint32_t key_len, value_len;
    value_len = calc_table_row_length(table);
    key_len = calc_primary_key_length(table);
    void *leaf_node = get_page(table->meta_table->table_name, table->pager, refer->page_num);
    void *destinct = get_leaf_node_cell_value(leaf_node, key_len, value_len, refer->cell_num);

    return generate_row(destinct, table->meta_table);
}

/* Select through leaf node. */
static void select_from_leaf_node(SelectResult *select_result, ConditionNode *condition, uint32_t page_num, Table *table, ROW_HANDLER row_handler, void *arg) {

    void *leaf_node = get_page(table->meta_table->table_name, table->pager, page_num);

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
        if (!include_leaf_node(destinct, condition, table->meta_table)) {
            continue;
        }

        /* If satisfied, exeucte row handler function. */
        Row *row = generate_row(destinct, table->meta_table);

        /* Execute row handler. */
        row_handler(row, select_result, table, arg);

        /* Free useless row. */
        free_row(row);
    }
    
    /* Free useless memory. */
    free_block(leaf_node_snapshot);
}

/* Select through internal node. */
static void select_from_internal_node(SelectResult *select_result, ConditionNode *condition, uint32_t page_num, Table *table, ROW_HANDLER row_handler, void *arg) {

    void *internal_node = get_page(table->meta_table->table_name, table->pager, page_num);

    /* Get keys number, key length. */
    uint32_t keys_num, key_len;
    keys_num = get_internal_node_keys_num(internal_node);
    key_len = calc_primary_key_length(table);

    /* It`s necessary to use internal node snapshot, beacuse when traversing cells, 
     * update or delete operation will change the data structure of internal node,
     * which may causes bug. */
    void *internal_node_snapshot = copy_block(internal_node, PAGE_SIZE);

    /* Loop each interanl node cell to check if satisfy condition. */
    int i;
    for (i = 0; i < keys_num; i++) {
    
        /* Check if index column, use index to avoid full text scanning. */
        {
            /* Current internal node cell key as max key, previous cell key as min key. */
            void *max_key = get_internal_node_key(internal_node_snapshot, i, key_len); 
            void *min_key = i == 0 ? NULL : get_internal_node_key(internal_node_snapshot, i - 1, key_len);

            if (!include_internal_node(min_key, max_key, condition, table->meta_table))
                continue;
        }

        /* Check other non-key column */
        uint32_t page_num = get_internal_node_child(internal_node_snapshot, i, key_len);
        void *node = get_page(table->meta_table->table_name, table->pager, page_num);
        switch (get_node_type(node)) {
            case LEAF_NODE:
                select_from_leaf_node(select_result, condition, page_num, table, row_handler, arg);
                break;
            case INTERNAL_NODE:
                select_from_internal_node(select_result, condition, page_num, table, row_handler, arg);
                break;
            default:
                db_log(PANIC, "Unknown node type.");
                break;
        }
    }

    /* Don`t forget the right child. */
    uint32_t right_child_page_num = get_internal_node_right_child(internal_node_snapshot);

    /* Zero means there is no page. */
    if (right_child_page_num == 0) {
        free_block(internal_node_snapshot);
        return;
    } 
    
    /* Fetch right child. */
    void *right_child = get_page(table->meta_table->table_name, table->pager, right_child_page_num);
    switch (get_node_type(right_child)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, condition, right_child_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, condition, right_child_page_num, table, row_handler, arg);
            break;
    }

    /* Free memory. */
    free_block(internal_node_snapshot);
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
    select_result->rows = NULL;
    return select_result;
}

/* Query with condition. */
void query_with_condition(ConditionNode *condition, SelectResult *select_result, ROW_HANDLER row_handler, void *arg) {
    Table *table = open_table(select_result->table_name);
    if (table == NULL)
        return;
    void *root = get_page(table->meta_table->table_name, table->pager, table->root_page_num);
    switch (get_node_type(root)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, condition, table->root_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, condition, table->root_page_num, table, row_handler, arg);
            break;
        default:
            db_log(PANIC, "Unknown data type occurs in <query_with_condition>.");
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
    select_result->rows = db_realloc(select_result->rows, sizeof(Row *) * (select_result->row_size + 1));
    select_result->rows[select_result->row_size++] = copy_row_without_reserved(row);
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
    
    assert_not_null(meta_column, "Sysmte Logic Error, in <calc_coluymn_sum_value>");

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

    key_value->value = copy_value(&sum, T_DOUBLE);
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
    key_value->value = copy_value(&avg, T_DOUBLE);
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

    key_value->value = copy_value(max_value, meta_column->column_type);
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

    key_value->value = copy_value(min_value, meta_column->column_type);
    key_value->data_type = meta_column->column_type;

}


/* Query count function. */
static KeyValue *query_count_function(FunctionValueNode *value, SelectResult *selct_result) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("count");
    key_value->data_type = T_INT;
    key_value->value = copy_value(&selct_result->row_size, T_INT);
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
            key_value->value = copy_value(&sum, T_DOUBLE);
            key_value->data_type = T_DOUBLE;
            break;
        }
        case V_ALL: {
            db_log(ERROR, "Sum function not support '*'");
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
            key_value->value = copy_value(&sum, T_DOUBLE);
            key_value->data_type = T_DOUBLE;
            break;
        }
        case V_ALL: {
            db_log(ERROR, "Avg function not support '*'");
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
            key_value->value = copy_value(&value->i_value, T_INT);
            key_value->data_type = T_INT;
            break;
        }
        case V_ALL: {
            db_log(ERROR, "Max function not support '*'");
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
            key_value->value = copy_value(&value->i_value, T_INT);
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

/* Query scalar function */
static KeyValue *query_function_column_value(FunctionNode *function, SelectResult *select_result) {
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

/* Generate new KeyValue instance. */
static KeyValue *new_key_value(char *key, void *value, DataType data_type) {
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = key;
    key_value->value = value;
    key_value->data_type = data_type;
    return key_value;
}

/* Query column value. */
static KeyValue *query_plain_column_value(ColumnNode *column, Row *row) {
    Table *table = open_table(row->table_name);
    for (uint32_t i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (strcmp(column->column_name, key_value->key) == 0) {
            /* Reference type and query sub column. */
            if (key_value->data_type == T_REFERENCE) {
                Refer *refer = (Refer *)key_value->value;
                Row *sub_row = define_row(refer);
                if (column->has_sub_column && column->sub_column)
                    return query_plain_column_value(column->sub_column, sub_row);
                else if (column->has_sub_column && column->scalar_exp_set) {
                    Row *filter_sub_row = query_plain_row_selection(column->scalar_exp_set, sub_row);
                    return new_key_value(db_strdup(column->column_name), filter_sub_row, T_ROW);
                } else if (!column->has_sub_column) {
                    return new_key_value(db_strdup(column->column_name), sub_row, T_ROW);
                }
            }
            else if (column->has_sub_column) 
                db_log(ERROR, "Column '%s' is not Reference type, no sub column found.", column->column_name);
            else
                return copy_key_value(key_value);
        }
    }
    db_log(ERROR, "Not found column '%s' in table '%s'", column->column_name, table->meta_table->table_name);
}

/* Calulate addition. */
static KeyValue *calulate_addition(KeyValue *left, KeyValue *right) {
    
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("add");
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    int32_t sum = *(int32_t *)left->value + *(int32_t *)right->value;
                    key_value->value = copy_value(&sum, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
                case T_LONG: {
                    int64_t sum = *(int32_t *)left->value + *(int64_t *)right->value;
                    key_value->value = copy_value(&sum, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float sum = *(int32_t *)left->value + *(float *)right->value;
                    key_value->value = copy_value(&sum, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double sum = *(int32_t *)left->value + *(double *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t sum = *(int64_t *)left->value + *(int32_t *)right->value;
                    key_value->value = copy_value(&sum, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_LONG: {
                    int64_t sum = *(int64_t *)left->value + *(int64_t *)right->value;
                    key_value->value = copy_value(&sum, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float sum = *(int64_t *)left->value + *(float *)right->value;
                    key_value->value = copy_value(&sum, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double sum = *(int64_t *)left->value + *(double *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    float sum = *(float *)left->value + *(int32_t *)right->value;
                    key_value->value = copy_value(&sum, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_LONG: {
                    float sum = *(float *)left->value + *(int64_t *)right->value;
                    key_value->value = copy_value(&sum, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_FLOAT: {
                    float sum = *(float *)left->value + *(float *)right->value;
                    key_value->value = copy_value(&sum, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double sum = *(float *)left->value + *(double *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double sum = *(double *)left->value + *(int32_t *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double sum = *(double *)left->value + *(int64_t *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double sum = *(double *)left->value + *(float *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_DOUBLE: {
                    double sum = *(double *)left->value + *(double *)right->value;
                    key_value->value = copy_value(&sum, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        default: {
            int zero = 0;
            key_value->value = copy_value(&zero, T_INT);
            key_value->data_type = T_INT;
            break;
        }
    }

    return key_value;
}

/* Calulate substraction .*/
static KeyValue *calulate_substraction(KeyValue *left, KeyValue *right) {
    
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("sub");
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    int32_t sub = *(int32_t *)left->value - *(int32_t *)right->value;
                    key_value->value = copy_value(&sub, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
                case T_LONG: {
                    int64_t sub = *(int32_t *)left->value - *(int64_t *)right->value;
                    key_value->value = copy_value(&sub, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float sub = *(int32_t *)left->value - *(float *)right->value;
                    key_value->value = copy_value(&sub, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double sub = *(int32_t *)left->value - *(double *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t sub = *(int64_t *)left->value - *(int32_t *)right->value;
                    key_value->value = copy_value(&sub, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_LONG: {
                    int64_t sub = *(int64_t *)left->value - *(int64_t *)right->value;
                    key_value->value = copy_value(&sub, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float sub = *(int64_t *)left->value - *(float *)right->value;
                    key_value->value = copy_value(&sub, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double sub = *(int64_t *)left->value - *(double *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    float sub = *(float *)left->value - *(int32_t *)right->value;
                    key_value->value = copy_value(&sub, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_LONG: {
                    float sub = *(float *)left->value - *(int64_t *)right->value;
                    key_value->value = copy_value(&sub, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_FLOAT: {
                    float sub = *(float *)left->value - *(float *)right->value;
                    key_value->value = copy_value(&sub, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double sub = *(float *)left->value - *(double *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double sub = *(double *)left->value - *(int32_t *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double sub = *(double *)left->value - *(int64_t *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double sub = *(double *)left->value - *(float *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_DOUBLE: {
                    double sub = *(double *)left->value - *(double *)right->value;
                    key_value->value = copy_value(&sub, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        default: {
            int zero = 0;
            key_value->value = copy_value(&zero, T_INT);
            key_value->data_type = T_INT;
            break;
        }
    }

    return key_value;
}


/* Calulate multiplication .*/
static KeyValue *calulate_multiplication(KeyValue *left, KeyValue *right) {
    
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("mul");
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t mul = (*(int32_t *)left->value) * (*(int32_t *)right->value);
                    key_value->value = copy_value(&mul, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_LONG: {
                    int64_t mul = *(int64_t *)left->value * *(int64_t *)right->value;
                    key_value->value = copy_value(&mul, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float mul = *(int32_t *)left->value * *(float *)right->value;
                    key_value->value = copy_value(&mul, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double mul = *(int32_t *)left->value * *(double *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t mul = *(int64_t *)left->value * *(int32_t *)right->value;
                    key_value->value = copy_value(&mul, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_LONG: {
                    int64_t mul = *(int64_t *)left->value * *(int64_t *)right->value;
                    key_value->value = copy_value(&mul, T_LONG);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float mul = *(int64_t *)left->value * *(float *)right->value;
                    key_value->value = copy_value(&mul, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double mul = *(int64_t *)left->value * *(double *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    float mul = *(float *)left->value * *(int32_t *)right->value;
                    key_value->value = copy_value(&mul, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_LONG: {
                    float mul = *(float *)left->value * *(int64_t *)right->value;
                    key_value->value = copy_value(&mul, T_FLOAT);
                    key_value->data_type = T_LONG;
                    break;
                }
                case T_FLOAT: {
                    float mul = *(float *)left->value * *(float *)right->value;
                    key_value->value = copy_value(&mul, T_FLOAT);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double mul = *(float *)left->value * *(double *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double mul = *(double *)left->value * *(int32_t *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double mul = *(double *)left->value * *(int64_t *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double mul = *(double *)left->value * *(float *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double mul = *(double *)left->value * *(double *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        default: {
            int zero = 0;
            key_value->value = copy_value(&zero, T_INT);
            key_value->data_type = T_INT;
            break;
        }
    }

    return key_value;
}

/* Calulate division .*/
static KeyValue *calulate_division(KeyValue *left, KeyValue *right) {
    
    KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
    key_value->key = db_strdup("div");
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    double div = (double)(*(int32_t *)left->value) / (*(int32_t *)right->value);
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double div = (double)(*(int64_t *)left->value) / (*(int64_t *)right->value);
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double div = (double)(*(int32_t *)left->value) / (*(float *)right->value);
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_DOUBLE: {
                    double mul = (double)(*(int32_t *)left->value) / *(double *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    double div = (double)*(int64_t *)left->value / *(int32_t *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double div = (double)*(int64_t *)left->value / *(int64_t *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double div = (double)*(int64_t *)left->value / *(float *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_DOUBLE: {
                    double div = (double)*(int64_t *)left->value / *(double *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    double div = (double)*(float *)left->value / *(int32_t *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double div = (double)*(float *)left->value / *(int64_t *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double div = (double)*(float *)left->value / *(float *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_DOUBLE: {
                    double mul = (double)*(float *)left->value / *(double *)right->value;
                    key_value->value = copy_value(&mul, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double div = *(double *)left->value / *(int32_t *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_LONG: {
                    double div = *(double *)left->value / *(int64_t *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                case T_FLOAT: {
                    double div = *(double *)left->value / *(float *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_FLOAT;
                    break;
                }
                case T_DOUBLE: {
                    double div = *(double *)left->value / *(double *)right->value;
                    key_value->value = copy_value(&div, T_DOUBLE);
                    key_value->data_type = T_DOUBLE;
                    break;
                }
                default: {
                    int zero = 0;
                    key_value->value = copy_value(&zero, T_INT);
                    key_value->data_type = T_INT;
                    break;
                }
            }
            break;
        }
        default: {
            int zero = 0;
            key_value->value = copy_value(&zero, T_INT);
            key_value->data_type = T_INT;
            break;
        }
    }

    return key_value;
}

/* Query function calculate. */
static KeyValue *query_function_calculate_column_value(CalculateNode *calculate, SelectResult *select_result) {
    KeyValue *result = NULL;

    KeyValue *left = query_function_value(calculate->left, select_result);
    KeyValue *right = query_function_value(calculate->right, select_result);
    
    switch (calculate->type) {
        case CAL_ADD:
            result = calulate_addition(left, right);
            break;
        case CAL_SUB:
            result = calulate_substraction(left, right);
            break;
        case CAL_MUL:
            result = calulate_multiplication(left, right);
            break;
        case CAL_DIV:
            result = calulate_division(left, right);
            break;
    }

    free_key_value(left);
    free_key_value(right);

    return result;
}


/* Query column value. */
static KeyValue *query_function_value(ScalarExpNode *scalar_exp, SelectResult *select_result) {
    switch (scalar_exp->type) {
        case SCALAR_COLUMN: {
            ColumnNode *column = scalar_exp->column;
            if (select_result->row_size == 0) {
                Table *table = open_table(select_result->table_name);
                KeyValue *key_value = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
                key_value->key = db_strdup(column->column_name);
                MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column->column_name);
                key_value->value = NULL;
                key_value->data_type = meta_column->column_type;
                return key_value;
            }
            /* Default, when query function and column data, column only return first data. */
            return query_plain_column_value(column, select_result->rows[0]);
        }
        case SCALAR_FUNCTION:
            return query_function_column_value(scalar_exp->function, select_result);
        case SCALAR_CALCULATE:
            return query_function_calculate_column_value(scalar_exp->calculate, select_result);
    } 
}

/* Query function data. */
static void query_fuction_selecton(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {
    Row *row = db_malloc(sizeof(Row), SDT_ROW);
    row->table_name = db_strdup(select_result->table_name);
    row->column_len = scalar_exp_set->size;
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);

    int i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        KeyValue *key_value = query_function_value(scalar_exp, select_result);        
        if (scalar_exp->alias) {
            free_value(key_value->key, T_STRING);
            key_value->key = db_strdup(scalar_exp->alias);
        }
        row->data[i] = key_value;
    }

    /* Free old rows memory. */
    int j;
    for (j = 0; j <select_result->row_size; j++) {
        free_row(select_result->rows[j]);
    }

    select_result->rows = db_realloc(select_result->rows, sizeof(Row *) * 1);
    select_result->row_size = 1;
    select_result->rows[0] = row;
}

/* Query all-columns calcuate column value. */
static KeyValue *query_all_columns_calculate_column_value(CalculateNode *calculate, Row *row) {
    KeyValue *result = NULL;

    KeyValue *left = query_row_value(calculate->left, row);
    KeyValue *right = query_row_value(calculate->right, row);

    switch (calculate->type) {
        case CAL_ADD:
            result = calulate_addition(left, right);
            break;
        case CAL_SUB:
            result = calulate_substraction(left, right);
            break;
        case CAL_MUL:
            result = calulate_multiplication(left, right);
            break;
        case CAL_DIV:
            result = calulate_division(left, right);
            break;
    }
    
    /* Free memory.*/
    free_key_value(left);
    free_key_value(right);

    return result;
}

/* Query row value. */
static KeyValue *query_row_value(ScalarExpNode *scalar_exp, Row *row) {
    switch (scalar_exp->type) {
        case SCALAR_COLUMN:
            return query_plain_column_value(scalar_exp->column, row);
        case SCALAR_CALCULATE:
            return query_all_columns_calculate_column_value(scalar_exp->calculate, row);            
        case SCALAR_FUNCTION:
            db_log(PANIC, "System logic error at <query_row_value>");
    }
}

/* Query a Row of Selection,
 * Actually, the Selection is all-column. */
static Row *query_plain_row_selection(ScalarExpSetNode *scalar_exp_set, Row *row) {
    
    Table *table = open_table(row->table_name);
    MetaColumn *key_meta_column = get_primary_key_meta_column(table->meta_table);

    Row *new_row = db_malloc(sizeof(Row), SDT_ROW);
    new_row->key = copy_value(row->key, key_meta_column->column_type);
    new_row->table_name = db_strdup(row->table_name);
    new_row->column_len = scalar_exp_set->size;
    new_row->data = db_malloc(sizeof(KeyValue *) * new_row->column_len, SDT_POINTER);

    uint32_t i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        KeyValue *key_value = query_row_value(scalar_exp, row);
        if (scalar_exp->alias) {
            free_value(key_value->key, T_STRING);
            key_value->key = db_strdup(scalar_exp->alias);
        }
        new_row->data[i] = key_value;
    }
    return new_row;
}

/* Query all columns data. */
static void query_columns_selection(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {
    uint32_t i;
    for (i = 0; i < select_result->row_size; i++) {
        Row *row = select_result->rows[i];
        select_result->rows[i] = query_plain_row_selection(scalar_exp_set, row);
        free_row(row);
    }
}

/* Check if ScalarExpNode is Function. 
 * If CALCULATE, will check its children. */
static bool is_function_scalar_exp(ScalarExpNode *scalar_exp) {
    switch (scalar_exp->type) {
        case SCALAR_FUNCTION:
            return true;
        case SCALAR_COLUMN:
            return false;
        case SCALAR_CALCULATE:
            return is_function_scalar_exp(scalar_exp->calculate->left) 
                || is_function_scalar_exp(scalar_exp->calculate->right);
    }
}

/* Check if exists function type scalar exp. */
static bool exists_function_scalar_exp(ScalarExpSetNode *scalar_exp_set) {
    int i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        /* Check self if SCALAR_FUNCTION. */
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        if (is_function_scalar_exp(scalar_exp))
            return true;
    }
    return false;
}


/* Query selection. */
static void query_with_selection(SelectionNode *selection, SelectResult *select_result) {
    if (selection->all_column)
        return;
    if (exists_function_scalar_exp(selection->scalar_exp_set)) 
        query_fuction_selecton(selection->scalar_exp_set, select_result);
    else 
        query_columns_selection(selection->scalar_exp_set, select_result);
}

/* Execute select statement. */
void exec_select_statement(SelectNode *select_node, DBResult *result) {
    QueryParam *query_param = convert_query_param(select_node);
    if (check_query_param(query_param)) {
        /* Genrate select result. */
        SelectResult *select_result = new_select_result(query_param->table_name);

        /* Select with condition to define which rows. */
        query_with_condition(query_param->condition_node, select_result, select_row, NULL);

        /* Query Selection to define row content. */
        query_with_selection(query_param->selection, select_result);

        /* If select all, return all row data. */
        result->rows = select_result->row_size;
        result->data = select_result;
        result->success = true;

        /* Make up success result. */
        db_log(SUCCESS, "Query data successfully.");
    }

    free_query_param(query_param);
}
