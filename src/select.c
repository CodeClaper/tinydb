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
#include "json.h"
#include "list.h"

/* Maximum number of rows fetched at once.*/
#define MAX_FETCH_ROWS 100 

/* Function name, also as key in out json. */
#define COUNT_NAME "count"
#define SUM_NAME "sum"
#define AVG_NAME "avg"
#define MAX_NAME "max"
#define MIN_NAME "min"

/* Check if include the internal node. */
static bool include_internal_node(SelectResult *select_result, void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table);

/* Check if the key include the leaf node. */
static bool include_leaf_node(SelectResult *select_result, Row *row, ConditionNode *condition_node);

/* Get meta column by condition name. */
static MetaColumn *get_cond_meta_column(PredicateNode *predicate, MetaTable *meta_table);

/* Query column value. */
static KeyValue *query_function_value(ScalarExpNode *scalar_exp, SelectResult *select_result);

/* Query value item in scalar_exp. */
static KeyValue *query_value_item(ValueItemNode *value_item, Row *row);

/* Query row value. */
static KeyValue *query_row_value(SelectResult *select_result, ScalarExpNode *scalar_exp, Row *row);

/* Query a Row of Selection,
 * Actually, the Selection is all-column. */
static Row *query_plain_row_selection(SelectResult *select_result, ScalarExpSetNode *scalar_exp_set, Row *row);

/* Generate select row. */
static Row *generate_row(void *destinct, MetaTable *meta_table);

/* Search table via alias name in SelectResult. 
 * Note: range variable may be table name or table alias name.
 * */
static char *search_table_via_alias(SelectResult *select_result, char *range_variable);

/* Calulate offset of every column in cell. */
static uint32_t calc_offset(MetaTable *meta_table, char *column_name) {
    uint32_t i, off_set = 0;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0)
            break;
        off_set += meta_column->column_length;
    }
    return off_set;
}


/* Check if include internal comparison predicate for Value type. */
static bool include_internal_comparison_predicate_value(SelectResult *select_result, void *min_key, void *max_key, CompareType type, ValueItemNode *value_item, MetaColumn *meta_column) {
    void *target_key = get_value_from_value_item_node(value_item, meta_column);

    if (target_key == NULL)
        return true;
    DataType data_type = meta_column->column_type;

    bool result = false;
    switch (type) {
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

/* Check if include internal comparison predicate. */
static bool include_internal_comparison_predicate(SelectResult *select_result, void *min_key, void *max_key, ComparisonNode *comparison, MetaTable *meta_table) {
    ColumnNode *column = comparison->column;

    /* Other table query condition regard as true. */
    if (column->range_variable) {
        char *table_mame = search_table_via_alias(select_result, column->range_variable);

        if (select_result->last_derived && table_mame == NULL) {
            db_log(ERROR, "Unknown column '%s.%s' in where clause. ", column->range_variable, column->column_name);
            return false;
        }

        if (!table_mame || !streq(table_mame, meta_table->table_name))
            return true;
    }

    MetaColumn *meta_column = get_meta_column_by_name(meta_table, column->column_name);
    if (meta_table == NULL) {
        db_log(ERROR, "Not found column '%s'. ", column->column_name);
        return true;
    }

    ScalarExpNode *comparsion_value = comparison->value;
    switch (comparsion_value->type) {
        case SCALAR_VALUE:
            return include_internal_comparison_predicate_value(select_result, min_key, max_key, comparison->type, comparsion_value->value, meta_column);
        /* Other comparison value type, regarded as true for including internal predicate. */
        case SCALAR_COLUMN:
        case SCALAR_FUNCTION:
        case SCALAR_CALCULATE:
            return true;
        default:
            db_log(PANIC, "Not support comparison value type.");
    }
}


/* Check if include the internal predicate. */
static bool include_internal_predicate(SelectResult *select_result, void *min_key, void *max_key, PredicateNode *predicate, MetaTable *meta_table) {
    switch (predicate->type) {
        case PRE_COMPARISON:
            return include_internal_comparison_predicate(select_result, min_key, max_key, predicate->comparison, meta_table);
        /* For in or like predicate, no skip include. */
        case PRE_IN:
        case PRE_LIKE:
            return true;
    }
}


/* Check if include the internal node if condition is logic condition. */
static bool include_logic_internal_node(SelectResult *select_result, void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {
    /* For logic condition node, check left node and right node. */
    switch(condition_node->conn_type) {
        case C_AND:
           return include_internal_node(select_result, min_key, max_key, condition_node->left, meta_table) && include_internal_node(select_result, max_key, max_key, condition_node->right, meta_table);
        case C_OR:
           return include_internal_node(select_result, min_key, max_key, condition_node->left, meta_table) || include_internal_node(select_result, max_key, max_key, condition_node->right, meta_table);
        case C_NONE:
            db_log(PANIC, "System logic error.");
    } 
}

/* Check if include the internal node if condition is exec condition. */
static bool include_exec_internal_node(SelectResult *select_result, void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    assert_true(condition_node->conn_type == C_NONE, "System logic error.");
    
    MetaColumn *cond_meta_column = get_cond_meta_column(condition_node->predicate, meta_table);

    /* Skipped the internal node must satisfy tow factors: 
     * (1) Current condition is current table columns.
     * (2) It is primary key
     * (3) not satisfied internal node condition. 
     */
    return !cond_meta_column 
           || !cond_meta_column->is_primary 
           || include_internal_predicate(select_result, min_key, max_key, condition_node->predicate, meta_table);
}

/* Check if include the internal node. */
static bool include_internal_node(SelectResult *select_result, void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    /* If without condition, of course return true. */
    if (condition_node == NULL)
        return true;

    /* According to condition node type, has different way. */
    switch(condition_node->conn_type) {
        case C_OR:
        case C_AND:
            return include_logic_internal_node(select_result, min_key, max_key, condition_node, meta_table);
        case C_NONE:
            return include_exec_internal_node(select_result, min_key, max_key, condition_node, meta_table);
    }
}

/* Check if include leaf node if the condition is logic condition. */
static bool include_logic_leaf_node(SelectResult *select_result, Row *row, ConditionNode *condition_node) {
    switch(condition_node->conn_type) {
        case C_AND:
            return include_leaf_node(select_result, row, condition_node->left) 
                && include_leaf_node(select_result, row, condition_node->right);
        case C_OR:
            return include_leaf_node(select_result, row, condition_node->left) 
                || include_leaf_node(select_result, row, condition_node->right);
        case C_NONE:
            db_log(PANIC, "System Logic Error");
    } 
}

/* Check the row predicate for column. */
static bool check_row_predicate_column(SelectResult *select_result, Row *row, void *value, ColumnNode *column, CompareType type, MetaColumn *meta_column) {
    char *table_name = search_table_via_alias(select_result, column->range_variable);
    if (select_result->last_derived && table_name == NULL) {
        db_log(ERROR, "Unknown column '%s.%s' in where clause. ", column->range_variable, column->column_name);
        return false;
    }
    
    /* Other table query, skip. */
    if (table_name == NULL)
        return true;

    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (streq(key_value->table_name, table_name) && streq(key_value->key, column->column_name)) {
            return eval(type, value, key_value->value, meta_column->column_type);
        }
    }
    
    db_log(ERROR, "Unknown column '%s.%s' in where clause. ", column->range_variable, column->column_name);
    return false;
}

/* Check the row predicate for value. */
static bool check_row_predicate_value(SelectResult *select_result, void *value, ValueItemNode *value_item, CompareType type, MetaColumn *meta_column) {
    bool ret = false;
    void *target = get_value_from_value_item_node(value_item, meta_column);
    ret = eval(type, value, target, meta_column->column_type);
    /* Reference data is allocated, so free it. */
    if (meta_column->column_type == T_REFERENCE)
        free_refer(target);

    return ret;
}

/* Check the row predicate. */
static bool check_row_predicate(SelectResult *select_result, Row *row, ColumnNode *column, ComparisonNode *comparison) {

    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (streq(key_value->key, column->column_name)) {
            
            /* If exists range variable, check if equals. */
            if (column->range_variable) {
                char *table_name = search_table_via_alias(select_result, column->range_variable);
                if (select_result->last_derived && table_name == NULL) {
                    db_log(ERROR, "Unknown column '%s.%s' in where clause. ", column->range_variable, column->column_name);
                    return false;
                }
                /* May subling tables, skip it temporarily. */
                if (!table_name || !streq(table_name, key_value->table_name))
                    continue;
            }

            Table *table = open_table(key_value->table_name);
            MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, key_value->key);
            
            if (meta_column == NULL) {
                db_log(ERROR, "Not found column '%s'. ", column->column_name);
                return false;
            }

            if (column->has_sub_column && column->sub_column) {
                /* Just check, if column has sub column, it must be Reference type. */
                Assert(meta_column->column_type == T_REFERENCE);

                /* Get subrow, and recursion. */
                Refer *refer = key_value->value;
                Row *sub_row = define_row(refer);
                return check_row_predicate(select_result, sub_row, column->sub_column, comparison); 

            } else if (column->has_sub_column && column->scalar_exp_set) {
                db_log(ERROR, "Not support support sub column for pridicate.");
                return false;
            } else {
                ScalarExpNode *comparison_value = comparison->value;
                switch (comparison_value->type) {
                    case SCALAR_COLUMN:
                        return check_row_predicate_column(select_result, row, key_value->value, comparison_value->column, comparison->type, meta_column);    
                    case SCALAR_VALUE: 
                        return check_row_predicate_value(select_result, key_value->value, comparison_value->value, comparison->type, meta_column);
                    case SCALAR_FUNCTION:
                        db_log(ERROR, "Not support function as comparison value.");
                        return false;
                    case SCALAR_CALCULATE:
                        db_log(ERROR, "Not support calcuation comparison value.");
                        return false;
                    default:
                        db_log(PANIC, "Unknown Scalar type.");
                }
            }

        }
    }

    /* When column skip test, it may exists in other tables when multi-table query. */
    return true;
}


/* Check if include leaf node satisfy comparison predicate. */
static bool include_leaf_comparison_predicate(SelectResult *select_result, Row *row, ComparisonNode *comparison) {
    return check_row_predicate(select_result, row, comparison->column, comparison);
}

/* Check if include in value item set. */
static bool check_in_value_item_set(ValueItemSetNode *value_item_set_node, void *value, MetaColumn *meta_column) {
    bool ret = false;
    for (uint32_t i = 0; i < value_item_set_node->num; i++) {
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
static bool include_leaf_in_predicate(Row *row, InNode *in_node) {
    Table *table = open_table(row->table_name);
    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        /* Define the column. */
        if (strcmp(key_value->key, in_node->column->column_name) == 0) {
            MetaColumn *meta_column = get_meta_column_by_name(table->meta_table , key_value->key);
            return check_in_value_item_set(in_node->value_set, key_value->value, meta_column);
        }
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
static bool include_leaf_like_predicate(Row *row, LikeNode *like_node) {
    Table *table = open_table(row->table_name);
    bool ret = false;
    uint32_t i; 
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        /* Define the column. */
        if (strcmp(key_value->key, like_node->column->column_name) == 0) {
            MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, key_value->key);
            void *target_value = get_value_from_value_item_node(like_node->value, meta_column);
            ret = check_like_string_value(key_value->value, target_value);

            /* Reference data is allocated, so free it. */
            if (meta_column->column_type == T_REFERENCE)
                free_refer(target_value);
            break;
        }
    }
    return ret;
}

/* Check if include leaf node if the condition is exec condition. */
static bool include_exec_leaf_node(SelectResult *select_result, Row *row, ConditionNode *condition_node) {

    /* If without condition, of course the key include, so just return true. */
    if (condition_node == NULL)
        return true;

    assert_true(condition_node->conn_type == C_NONE, "System logic error.");

    PredicateNode *predicate = condition_node->predicate;

    switch (predicate->type) {
        case PRE_COMPARISON:
            return include_leaf_comparison_predicate(select_result, row, predicate->comparison);
        case PRE_IN:
            return include_leaf_in_predicate(row, predicate->in);
        case PRE_LIKE:
            return include_leaf_like_predicate(row, predicate->like);
    }

}

/* Check if the key include the leaf node. */
static bool include_leaf_node(SelectResult *select_result, Row *row, ConditionNode *condition_node) {

    /* If without condition, of course the key include, so just return true. */
    if (condition_node == NULL) 
          return true;

    switch(condition_node->conn_type) {
        case C_OR:
        case C_AND:
            return include_logic_leaf_node(select_result, row, condition_node);
        case C_NONE:
            return include_exec_leaf_node(select_result, row, condition_node);
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

/* Get row array value. 
 * Return data as list.
 * */
static List *get_row_array_value(void *destination, MetaColumn *meta_column) {
    uint32_t array_num = get_array_number(destination);
    List *list = create_list(meta_column->column_type);
    size_t array_num_size = sizeof(uint32_t);
    uint32_t span = (meta_column->column_length - sizeof(uint32_t)) / meta_column->array_cap;
    uint32_t i;
    for (i = 0; i < array_num; i++) {
        void *value = (destination + array_num_size + i * span);
        append_list(list, value);
    }
    return list;
}

/* Assignment row value. */
static void *assign_row_value(void *destination, MetaColumn *meta_column) {
    return meta_column->array_dim ==  0
            /* For non-array data. */
            ? copy_value(destination, meta_column->column_type) 
            /* For array data. */
            : get_row_array_value(destination, meta_column); 
}

/* Generate select row. */
static Row *generate_row(void *destination, MetaTable *meta_table) {

    /* Instance new row. */
    Row *row = instance(Row);

    /* Base info. */
    row->column_len = meta_table->all_column_size;
    row->table_name = db_strdup(meta_table->table_name);
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, "pointer");

    /* Assignment row data. */
    uint32_t i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Get the column offset. */
        uint32_t offset = calc_offset(meta_table, meta_column->column_name);
        
        /* Generate a key value pair. */
        KeyValue *key_value = instance(KeyValue);
        key_value->key = db_strdup(meta_column->column_name);
        key_value->data_type = meta_column->column_type;
        key_value->is_array = meta_column->array_dim > 0;
        key_value->value = assign_row_value(destination + offset, meta_column);
        key_value->table_name = db_strdup(meta_table->table_name);
        row->data[i] = key_value;
        
        /* Assign primary key. */
        if (meta_column->is_primary)
            row->key = copy_value(destination + offset, meta_column->column_type);
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

/* Merge tow row into new one. */
static Row *merge_row(Row *row1, Row *row2) {
    /* According the first row generate new merge row. */
    Row *row = copy_row(row1);
    row->column_len = row1->column_len + row2->column_len;
    row->data = db_realloc(row->data, sizeof(KeyValue *) * row->column_len);

    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        if (i >= row1->column_len)
            row->data[i] = copy_key_value(row2->data[i - row1->column_len]);
    }

    return row;
}

/* Search table via alias name in SelectResult. 
 * Note: range variable may be table name or table alias name.
 * */
static char *search_table_via_alias(SelectResult *select_result, char *range_variable) {
    if (select_result == NULL) 
        db_log(PANIC, "Support SelectResult. ");

    /* Either table name or range variable is equal. */
    if (streq(select_result->table_name, range_variable) || streq(select_result->range_variable, range_variable))
        return select_result->table_name;

    if (select_result->derived)
        return search_table_via_alias(select_result->derived, range_variable);

    return NULL;
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

    uint32_t i;
    for (i = 0; i < cell_num; i++) {

        /* Get leaf node cell value. */
        void *destinct = get_leaf_node_cell_value(leaf_node_snapshot, key_len, value_len, i);

        /* If satisfied, exeucte row handler function. */
        Row *row = generate_row(destinct, table->meta_table);

        SelectResult *derived = select_result->derived;

        if (derived) {

            /* Cartesian product. */
            uint32_t j;
            for (j = 0; j < derived->row_size; j++) {

                /* Merge derived-row. */
                Row *derived_row = derived->rows[j];
                Row *mrow = merge_row(derived_row, row);

                /* Check if the row data include, 
                 * in another word, check if the row data satisfy the condition. */
                if (include_leaf_node(select_result, mrow, condition)) 
                    /* Execute row handler. */
                    row_handler(mrow, select_result, table, arg);

                /* Free useless row. */
                free_row(mrow);
            }

            /* Free useless row. */
            free_row(row);

            continue;
        }

        /* Check if the row data include, in another word, check if the row data satisfy the condition. */
        if (include_leaf_node(select_result, row, condition)) 
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
    uint32_t i;
    for (i = 0; i < keys_num; i++) {
    
        /* Check if index column, use index to avoid full text scanning. */
        {
            /* Current internal node cell key as max key, previous cell key as min key. */
            void *max_key = get_internal_node_key(internal_node_snapshot, i, key_len); 
            void *min_key = i == 0 ? NULL : get_internal_node_key(internal_node_snapshot, i - 1, key_len);

            if (!include_internal_node(select_result, min_key, max_key, condition, table->meta_table))
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

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name) {
    SelectResult *select_result = instance(SelectResult);
    select_result->row_size = 0;
    select_result->row_index = 0;
    select_result->table_name = table_name ? db_strdup(table_name) : NULL;
    select_result->range_variable = NULL;
    select_result->rows = db_malloc(0, "pointer");
    select_result->derived = NULL;
    select_result->last_derived = false;
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

/* Get KeyValue from a Row by column name.
 * Return NULL if not found KeyValue match the column name. */
static KeyValue *get_key_value_from_row(Row *row, char *column_name) {
    int i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (streq(column_name, key_value->key))
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
    KeyValue *key_value = instance(KeyValue);
    key_value->key = db_strdup("count");
    key_value->data_type = T_INT;
    key_value->value = copy_value(&selct_result->row_size, T_INT);
    return key_value;
}

/* Query sum function. */
static KeyValue *query_sum_function(FunctionValueNode *value, SelectResult *select_result) {
    KeyValue *key_value = instance(KeyValue);
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
    KeyValue *key_value = instance(KeyValue);
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
    KeyValue *key_value = instance(KeyValue);
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
    KeyValue *key_value = instance(KeyValue);
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
    KeyValue *key_value = instance(KeyValue);
    key_value->key = key;
    key_value->value = value;
    key_value->data_type = data_type;
    return key_value;
}

/* Query column value. */
static KeyValue *query_plain_column_value(SelectResult *select_result, ColumnNode *column, Row *row) {

    /* Get table name via alias name. */
    char *table_name = search_table_via_alias(select_result, column->range_variable);
    if (column->range_variable && table_name == NULL) {
        db_log(ERROR, "Unknown table alias '%s' in select items. ", column->range_variable);
        return NULL;
    }

    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];

        if (streq(column->column_name, key_value->key) 
            && (table_name == NULL || streq(table_name, key_value->table_name))) {
            /* Reference type and query sub column. */
            if (key_value->data_type == T_REFERENCE) {
                Refer *refer = (Refer *)key_value->value;
                Row *sub_row = define_row(refer);
                if (column->has_sub_column && column->sub_column)
                    return query_plain_column_value(select_result, column->sub_column, sub_row);
                else if (column->has_sub_column && column->scalar_exp_set) {
                    Row *filter_sub_row = query_plain_row_selection(select_result, column->scalar_exp_set, sub_row);
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
    db_log(ERROR, "Not found column '%s'. ", column->column_name);
    return NULL;
}

/* Calulate addition. */
static KeyValue *calulate_addition(KeyValue *left, KeyValue *right) {
    
    KeyValue *key_value = instance(KeyValue);
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
    
    KeyValue *key_value = instance(KeyValue);
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
    
    KeyValue *key_value = instance(KeyValue);
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
    
    KeyValue *key_value = instance(KeyValue);
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
    Table *table = open_table(select_result->table_name);
    switch (scalar_exp->type) {
        case SCALAR_COLUMN: {
            ColumnNode *column = scalar_exp->column;
            MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column->column_name);
            if (select_result->row_size == 0) {
                KeyValue *key_value = instance(KeyValue);
                key_value->key = db_strdup(column->column_name);
                key_value->value = NULL;
                key_value->data_type = meta_column->column_type;
                return key_value;
            }
            /* Default, when query function and column data, column only return first data. */
            return query_plain_column_value(select_result, column, select_result->rows[0]);
        }
        case SCALAR_FUNCTION:
            return query_function_column_value(scalar_exp->function, select_result);
        case SCALAR_CALCULATE:
            return query_function_calculate_column_value(scalar_exp->calculate, select_result);
        case SCALAR_VALUE: {
            ValueItemNode *value = scalar_exp->value;
            if (select_result->row_size == 0) {
                KeyValue *key_value = instance(KeyValue);
                key_value->key = db_strdup("value");
                key_value->value = NULL;
                key_value->data_type = value->data_type;
                return key_value;
            }
            return query_value_item(value, select_result->rows[0]);
        }
        default:
            db_log(PANIC, "Unknown scalar type");
    } 
}

/* Query function data. */
static void query_fuction_selecton(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {
    Row *row = instance(Row);
    row->table_name = db_strdup(select_result->table_name);
    row->column_len = scalar_exp_set->size;
    row->data = db_malloc(sizeof(KeyValue *) * row->column_len, "pointer");

    for (uint32_t i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        KeyValue *key_value = query_function_value(scalar_exp, select_result);        
        if (scalar_exp->alias) {
            free_value(key_value->key, T_STRING);
            key_value->key = db_strdup(scalar_exp->alias);
        }
        row->data[i] = key_value;
    }

    /* Free old rows memory. */
    for (uint32_t j = 0; j <select_result->row_size; j++) {
        free_row(select_result->rows[j]);
    }

    select_result->rows = db_realloc(select_result->rows, sizeof(Row *) * 1);
    select_result->row_size = 1;
    select_result->rows[0] = row;
}

/* Query all-columns calcuate column value. */
static KeyValue *query_all_columns_calculate_column_value(SelectResult *select_result, CalculateNode *calculate, Row *row) {
    KeyValue *result = NULL;

    KeyValue *left = query_row_value(select_result, calculate->left, row);
    KeyValue *right = query_row_value(select_result, calculate->right, row);

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

/* Query value item in scalar_exp. */
static KeyValue *query_value_item(ValueItemNode *value_item, Row *row) {
    void *value = NULL;
    switch (value_item->data_type) {
        case T_CHAR:
        case T_STRING:
            value = copy_value(value_item->value.strVal, value_item->data_type);
            break;
        case T_REFERENCE:
            value = copy_value(value_item->value.refVal, value_item->data_type);
            break;
        case T_ARRAY:
            value = copy_value(value_item->value.arrayVal, value_item->data_type);
            break;
        default:
            value = copy_value(&value_item->value, value_item->data_type);
            break;
    }
    assert_not_null(value, "System error occurs at <query_value_item>");
    return new_key_value(db_strdup("value"), value, value_item->data_type);
}

/* Query row value. */
static KeyValue *query_row_value(SelectResult *select_result, ScalarExpNode *scalar_exp, Row *row) {
    switch (scalar_exp->type) {
        case SCALAR_COLUMN:
            return query_plain_column_value(select_result, scalar_exp->column, row);
        case SCALAR_CALCULATE:
            return query_all_columns_calculate_column_value(select_result, scalar_exp->calculate, row);            
        case SCALAR_VALUE:
            return query_value_item(scalar_exp->value, row);
        case SCALAR_FUNCTION:
            db_log(PANIC, "System logic error at <query_row_value>");
    }
}

/* Query a Row of Selection,
 * Actually, the Selection is all-column. */
static Row *query_plain_row_selection(SelectResult *select_result, ScalarExpSetNode *scalar_exp_set, Row *row) {
    
    Table *table = open_table(row->table_name);
    MetaColumn *key_meta_column = get_primary_key_meta_column(table->meta_table);

    Row *new_row = instance(Row);
    new_row->key = copy_value(row->key, key_meta_column->column_type);
    new_row->table_name = db_strdup(row->table_name);
    new_row->column_len = scalar_exp_set->size;
    new_row->data = db_malloc(sizeof(KeyValue *) * new_row->column_len, "pointer");

    uint32_t i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        KeyValue *key_value = query_row_value(select_result, scalar_exp, row);
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
        select_result->rows[i] = query_plain_row_selection(select_result, scalar_exp_set, row);
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
        case SCALAR_VALUE:
            return false;
        case SCALAR_CALCULATE:
            return is_function_scalar_exp(scalar_exp->calculate->left) 
                || is_function_scalar_exp(scalar_exp->calculate->right);
    }
}

/* Check if exists function type scalar exp. */
static bool exists_function_scalar_exp(ScalarExpSetNode *scalar_exp_set) {
    uint32_t i;
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

/* Get TableExpNode condition. 
 * If exists where clause, return its condition.
 * Else, return NULL.
 * */
static ConditionNode *get_table_exp_condition(TableExpNode *table_exp) {
    WhereClauseNode *where_clause = table_exp->where_clause;
    if (where_clause)
        return where_clause->condition;
    else 
        return NULL;
}

/* Query with condition when multiple table. */
static SelectResult *query_multi_table_with_condition(SelectNode *select_node) {

    /* If no from clause, return an empty select result. */
    if (select_node->table_exp->from_clause == NULL) 
        return new_select_result(NULL);

    TableRefSetNode *table_ref_set = select_node->table_exp->from_clause->from;
    SelectResult *result = NULL;

    Assert(table_ref_set->size > 0);

    uint32_t i; 
    for (i = 0; i < table_ref_set->size; i++) {

        TableRefNode *table_ref = table_ref_set->set[i];
        SelectResult *current_result = new_select_result(table_ref->table);

        /* If use not define tale alias name, use table name as range variable automatically. */
        current_result->range_variable = table_ref->range_variable 
                                        ? db_strdup(table_ref->range_variable) 
                                        : db_strdup(table_ref->table);
        current_result->derived = result;
        current_result->last_derived = (i == table_ref_set->size - 1);

        /* Select with condition to define which rows. */
        ConditionNode *condition = get_table_exp_condition(select_node->table_exp);

        /* Query with condition to filter satisfied conditions rows. */
        query_with_condition(condition, current_result, select_row, NULL);

        result = current_result;
    }
    return result;
}

/* Execute select statement. */
void exec_select_statement(SelectNode *select_node, DBResult *result) {

    /* Check SelectNode valid. */
    check_select_node(select_node);

    /* Query multiple table with conditon and get select result which is after row filtered. */
    SelectResult *select_result = query_multi_table_with_condition(select_node);

    /* Query Selection to define row content. */
    query_with_selection(select_node->selection, select_result);

    /* If select all, return all row data. */
    result->rows = select_result->row_size;
    result->data = select_result;
    result->success = true;
    result->message = format("Query %d rows data from table '%s' successfully.", 
                             result->rows, 
                             select_result->table_name);

    /* Make up success result. */
    db_log(SUCCESS, "Query %d rows data from table '%s' successfully.", 
           result->rows, 
           select_result->table_name);
}
