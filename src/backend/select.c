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
#include "type.h"
#include "free.h"
#include "index.h"
#include "log.h"
#include "mmu.h"
#include "mem.h"
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
#include "const.h"

/* Maximum number of rows fetched at once.*/
#define MAX_FETCH_ROWS 100 

/* Function name, also as key in out json. */
#define COUNT_NAME "count"
#define SUM_NAME "sum"
#define AVG_NAME "avg"
#define MAX_NAME "max"
#define MIN_NAME "min"
#define ADD_NAME "add"
#define SUB_NAME "sub"
#define MUL_NAME "mul"
#define DIV_NAME "div"

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

/* Query column value. */
static KeyValue *query_plain_column_value(SelectResult *select_result, ColumnNode *column, Row *row);

/* Calulate offset of every column in cell. */
static uint32_t calc_offset(MetaTable *meta_table, char *column_name) {
    uint32_t i, off_set = 0;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (streq(meta_column->column_name, column_name))
            break;
        off_set += meta_column->column_length;
    }
    return off_set;
}


/* Check if include internal comparison predicate for Value type. */
static bool include_internal_comparison_predicate_value(SelectResult *select_result, void *min_key, void *max_key, CompareType type, ValueItemNode *value_item, MetaColumn *meta_column) {
    void *target_key = get_value_from_value_item_node(value_item, meta_column);
    if (!target_key)
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
            UNEXPECTED_VALUE("Unknown compare type.");
            break;
    }

    free_value(target_key, data_type);

    return result;
}

/* Check if include internal comparison predicate. */
static bool include_internal_comparison_predicate(SelectResult *select_result, void *min_key, void *max_key, ComparisonNode *comparison, MetaTable *meta_table) {
    ColumnNode *column = comparison->column;

    /* Other table query condition regard as true. */
    if (column->range_variable) {
        char *table_mame = search_table_via_alias(select_result, column->range_variable);

        if (select_result->last_derived && !table_mame) {
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
            return include_internal_comparison_predicate_value(select_result, 
                                                               min_key, 
                                                               max_key, 
                                                               comparison->type, 
                                                               comparsion_value->value, 
                                                               meta_column);
        /* Other comparison value type, regarded as true for including internal predicate. */
        case SCALAR_COLUMN:
        case SCALAR_FUNCTION:
        case SCALAR_CALCULATE:
            return true;
        default:
            UNEXPECTED_VALUE("Not support comparison value type.");
            return false;
    }
}


/* Check if include the internal predicate. */
static bool include_internal_predicate(SelectResult *select_result, void *min_key, void *max_key, PredicateNode *predicate, MetaTable *meta_table) {
    switch (predicate->type) {
        case PRE_COMPARISON:
            return include_internal_comparison_predicate(select_result, 
                                                         min_key, 
                                                         max_key, 
                                                         predicate->comparison, 
                                                         meta_table);
        /* For in or like predicate, no skip include. */
        case PRE_IN:
        case PRE_LIKE:
            return true;
        default:
            UNEXPECTED_VALUE(predicate->type);
            return false;
    }
}


/* Check if include the internal node if condition is logic condition. */
static bool include_logic_internal_node(SelectResult *select_result, void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {
    /* For logic condition node, check left node and right node. */
    switch(condition_node->conn_type) {
        case C_AND:
           return include_internal_node(select_result, min_key, max_key, condition_node->left, meta_table) 
                && include_internal_node(select_result, max_key, max_key, condition_node->right, meta_table);
        case C_OR:
           return include_internal_node(select_result, min_key, max_key, condition_node->left, meta_table) 
                || include_internal_node(select_result, max_key, max_key, condition_node->right, meta_table);
        case C_NONE:
            db_log(PANIC, "System logic error.");
            return false;
        default:
            UNEXPECTED_VALUE(condition_node->conn_type);
            return false;
    } 
}

/* Check if include the internal node if condition is exec condition. */
static bool include_exec_internal_node(SelectResult *select_result, void *min_key, void *max_key, ConditionNode *condition_node, MetaTable *meta_table) {

    assert_true(condition_node->conn_type == C_NONE, "System logic error.");
    
    MetaColumn *cond_meta_column = get_cond_meta_column(condition_node->predicate, meta_table);

    /* Skipped the internal node must satisfy flowing factors: 
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
        default:
            UNEXPECTED_VALUE(condition_node->conn_type);
            return false;
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
            return false;
        default:
            UNEXPECTED_VALUE(condition_node->conn_type);
            return false;
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
    free_value(target, meta_column->column_type);
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
                Row *sub_row = define_visible_row(refer);
                bool ret = check_row_predicate(select_result, sub_row, column->sub_column, comparison); 
                free_row(sub_row);
                return ret;
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
                        UNEXPECTED_VALUE(comparison_value->type);
                        return false;
                }
            }

        }
    }

    /* When column skip test, 
     * it may exists in other tables when multi-table query. */
    return true;
}


/* Check if include leaf node satisfy comparison predicate. */
static bool include_leaf_comparison_predicate(SelectResult *select_result, Row *row, ComparisonNode *comparison) {
    return check_row_predicate(select_result, row, comparison->column, comparison);
}

/* Check if include in value item set. */
static bool check_in_value_item_set(ValueItemSetNode *value_item_set_node, void *value, MetaColumn *meta_column) {
    bool ret = false;
    uint32_t i;
    for (i = 0; i < value_item_set_node->num; i++) {
        void *target = get_value_from_value_item_node(value_item_set_node->value_item_node[i], meta_column);
        ret = equal(value, target, meta_column->column_type);
        free_value(target, meta_column->column_type);
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
        if (streq(key_value->key, in_node->column->column_name)) {
            MetaColumn *meta_column = get_meta_column_by_name(table->meta_table , key_value->key);
            return check_in_value_item_set(in_node->value_set, key_value->value, meta_column);
        }
    }
    return false;
}

/* Check if satisfy like string value. */
static bool check_like_string_value(char *value, char *target) {
    size_t value_len = strlen(value);
    size_t target_len = strlen(target);
    if (value_len == 0 || target_len == 0)
        return false;

    if (target[0] == '%' && target[target_len - 1] == '%') {
        char str_dup[target_len];
        memset(str_dup, 0, target_len);
        memcpy(str_dup, target + 1, target_len -2);
        return contains(value, str_dup);
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
        return streq(value, target);
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
            free_value(target_value, meta_column->column_type);
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
        default:
            UNEXPECTED_VALUE(predicate->type);
            return false;
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
        default:
            UNEXPECTED_VALUE(condition_node->conn_type);
            return false;
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
            UNEXPECTED_VALUE(predicate->type);
            return NULL;
    }
}

/* Get row array value. 
 * Return ArrayValue.
 * */
static ArrayValue *get_row_array_value(void *destination, MetaColumn *meta_column) {

    uint32_t array_num = get_array_number(destination);

    /* Generate ArrayValue instance. */
    ArrayValue *array_value = new_array_value(meta_column->column_type, array_num);

    uint32_t span = (meta_column->column_length - LEAF_NODE_ARRAY_NUM_SIZE - LEAF_NODE_CELL_NULL_FLAG_SIZE) / meta_column->array_cap;
    uint32_t i;
    for (i = 0; i < array_num; i++) {
        void *value = get_array_value(destination, i, span);
        array_value->set[i] = copy_value(value, meta_column->column_type);
    }
    return array_value;
}

/* Assignment row value. */
static void *assign_row_value(void *destination, MetaColumn *meta_column) {
    return meta_column->array_dim ==  0
            /* For non-array data. */
            ? copy_value(destination + LEAF_NODE_CELL_NULL_FLAG_SIZE, meta_column->column_type) 
            /* For array data. */
            : get_row_array_value(destination, meta_column); 
}

/* Generate select row. */
static Row *generate_row(void *destination, MetaTable *meta_table) {

    /* Instance new row. */
    Row *row = new_row(NULL, db_strdup(meta_table->table_name), meta_table->all_column_size);

    /* Assignment row data. */
    uint32_t i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        /* Get the column offset. */
        uint32_t offset = calc_offset(meta_table, meta_column->column_name);

        /* Generate a key value pair. */
        KeyValue *key_value = is_null_cell(destination + offset) 
            ? new_key_value(db_strdup(meta_column->column_name), NULL, meta_column->column_type)
            : new_key_value(db_strdup(meta_column->column_name), assign_row_value(destination + offset, meta_column), meta_column->column_type);
        key_value->is_array = meta_column->array_dim > 0;
        key_value->table_name = db_strdup(meta_table->table_name);

        row->data[i] = key_value;
        
        /* Assign primary key. */
        if (meta_column->is_primary)
            row->key = assign_row_value(destination + offset, meta_column);
    }

    return row;
}

/* Define row by refer. 
 * Return row not matter if it is deleted.
 * */
Row *define_row(Refer *refer) {

    Assert(refer);

    /* Check table exists. */
    Table *table = open_table(refer->table_name);
    if (!table)
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

/* Define row by refer. 
 * Return undelted, filtered row, return NULL if deleted.
 * */
Row *define_visible_row(Refer *refer) {
    Row *row = define_row(refer);
    if (row_is_deleted(row)) 
        return NULL;
    else {
        Row *filter_row = copy_row_without_reserved(row);
        free_row(row);
        return filter_row;
    }
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
static void select_from_leaf_node(SelectResult *select_result, ConditionNode *condition, 
                                  uint32_t page_num, Table *table, 
                                  ROW_HANDLER row_handler, void *arg) {

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
            ListCell *lc;
            foreach (lc, derived->rows) {

                /* Merge derived-row. */
                Row *derived_row = lfirst(lc);
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
static void select_from_internal_node(SelectResult *select_result, ConditionNode *condition, 
                                      uint32_t page_num, Table *table, ROW_HANDLER row_handler, void *arg) {

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
    NodeType node_type = get_node_type(right_child);
    switch (node_type) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, condition, right_child_page_num, table, row_handler, arg);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, condition, right_child_page_num, table, row_handler, arg);
            break;
        default:
            UNEXPECTED_VALUE(node_type);
            break;
    }

    /* Free memory. */
    free_block(internal_node_snapshot);
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
    append_list(select_result->rows, copy_row_without_reserved(row));
}

/* Calulate column sum value. */
static KeyValue *calc_column_sum_value(ColumnNode *column, SelectResult *select_result) {
    
    double sum = 0;
    ListCell *lc;
    foreach (lc, select_result->rows) {
        Row *row = lfirst(lc);
        KeyValue *key_value = query_plain_column_value(select_result, column, row);
        switch (key_value->data_type) {
            case T_INT: {
                sum += *(int32_t *)key_value->value;
                break;
            }
            case T_LONG: {
                sum += *(int64_t *)key_value->value;
                break;
            }
            case T_FLOAT: {
                sum += *(float *)key_value->value;
                break;
            }
            case T_DOUBLE: {
                sum += *(double *)key_value->value;
                break;
            }
            case T_REFERENCE: 
            case T_ROW: {
                db_log(ERROR, "Reference type not used for sum function.");
                break;
            }
            default: {
                sum += 0;
                break;
            }
        }

        free_key_value(key_value);
    }

    return new_key_value(db_strdup(SUM_NAME), 
                         copy_value(&sum, T_DOUBLE), 
                         T_DOUBLE);
}


/* Calulate column avg value. */
static KeyValue *calc_column_avg_value(ColumnNode *column, SelectResult *select_result) {
    double sum = 0;
    double avg = 0;
    ListCell *lc;
    foreach (lc, select_result->rows) {
        Row *row = lfirst(lc);
        KeyValue *key_value = query_plain_column_value(select_result, column, row);
        switch (key_value->data_type) {
            case T_INT: {
                sum += *(int32_t *)key_value->value;
                break;
            }
            case T_LONG: {
                sum += *(int64_t *)key_value->value;
                break;
            }
            case T_FLOAT: {
                sum += *(float *)key_value->value;
                break;
            }
            case T_DOUBLE: {
                sum += *(double *)key_value->value;
                break;
            }
            case T_REFERENCE: 
            case T_ROW: {
                db_log(ERROR, "Reference type not used for avg function.");
                break;
            }
            default: {
                sum += 0;
                break;
            }
        }
        free_key_value(key_value);
    }
    avg = sum / len_list(select_result->rows);

    return new_key_value(db_strdup(AVG_NAME), 
                         copy_value(&avg, T_DOUBLE), 
                         T_DOUBLE);
}


/* Calulate column max value.*/
static KeyValue *calc_column_max_value(ColumnNode *column, SelectResult *select_result) {
    void *max_value = NULL;
    DataType data_type;
    ListCell *lc;
    foreach (lc, select_result->rows) {
        Row *row = lfirst(lc);
        KeyValue *current = query_plain_column_value(select_result, column, row);
        void *current_value = current->value;
        if (!max_value || greater(current_value, max_value, current->data_type)) {
            data_type = current->data_type;
            if (max_value)
                free_value(max_value, data_type);
            max_value = copy_value(current_value, data_type);
        }
        free_key_value(current);
    }

    return new_key_value(db_strdup(MAX_NAME), 
                         max_value, 
                         data_type);
}

/* Calulate column max value.*/
static KeyValue *calc_column_min_value(ColumnNode *column, SelectResult *select_result) {
    void *min_value = NULL;
    DataType data_type;
    ListCell *lc;
    foreach (lc, select_result->rows) {
        Row *row = lfirst(lc);
        KeyValue *current = query_plain_column_value(select_result, column, row);
        void *current_value = current->value;
        if (min_value == NULL || less(current_value, min_value, current->data_type)) {
            data_type = current->data_type;
            if (min_value)
                free_value(min_value, data_type);
            min_value = copy_value(current_value, data_type);
        }
        free_key_value(current);
    }

    return new_key_value(db_strdup(MIN_NAME), 
                         min_value, 
                         data_type);
}


/* Query count function. */
static KeyValue *query_count_function(FunctionValueNode *value, SelectResult *select_result) {
    uint32_t row_size = len_list(select_result->rows);
    return new_key_value(db_strdup("count"), 
                         copy_value(&row_size, T_INT), 
                         T_INT);
}

/* Query sum function. */
static KeyValue *query_sum_function(FunctionValueNode *value, SelectResult *select_result) {
    switch (value->value_type) {
        case V_COLUMN: 
            return calc_column_sum_value(value->column, select_result);
        case V_INT: {
            double sum = value->i_value * len_list(select_result->rows);
            return new_key_value(db_strdup(SUM_NAME), 
                                 copy_value(&sum, T_DOUBLE), 
                                 T_DOUBLE);
        }
        case V_ALL: {
            db_log(ERROR, "Sum function not support '*'");
            return NULL;
        }
        default: {
            UNEXPECTED_VALUE(value->value_type);
            return NULL;
        }
    }
}

/* Query avg function. */
KeyValue *query_avg_function(FunctionValueNode *value, SelectResult *select_result) {

    switch (value->value_type) {
        case V_COLUMN:
            return calc_column_avg_value(value->column, select_result);
        case V_INT: 
            return new_key_value(db_strdup(AVG_NAME), 
                                 copy_value(&value->i_value, T_DOUBLE), 
                                 T_DOUBLE);
        case V_ALL: 
            db_log(ERROR, "Avg function not support '*'");
            return NULL;
        default:
            UNEXPECTED_VALUE(value->value_type);
            return NULL;
    }
}

/* Query max function. */
KeyValue *query_max_function(FunctionValueNode *value, SelectResult *select_result) {

    switch (value->value_type) {
        case V_COLUMN: 
            return calc_column_max_value(value->column, select_result);
        case V_INT: 
            return new_key_value(db_strdup(MAX_NAME), 
                                 copy_value(&value->i_value, T_INT), 
                                 T_INT);
        case V_ALL: 
            db_log(ERROR, "Max function not support '*'.");
            return NULL;
        default:
            UNEXPECTED_VALUE(value->value_type);
            return NULL;
    }
} 


/* Query min function. */
KeyValue *query_min_function(FunctionValueNode *value, SelectResult *select_result) {

    switch (value->value_type) {
        case V_COLUMN:
            return calc_column_min_value(value->column, select_result);
        case V_INT: 
            return new_key_value(db_strdup(MIN_NAME), 
                                 copy_value(&value->i_value, T_INT), 
                                 T_INT);
        case V_ALL: 
            db_log(PANIC, "Min function not support '*'");
            return NULL;
        default:
            UNEXPECTED_VALUE(value->value_type);
            return NULL;
    }
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
            UNEXPECTED_VALUE("Not implement function yet.");
            return NULL;
    }
}


/* Query column value. */
static KeyValue *query_plain_column_value(SelectResult *select_result, ColumnNode *column, Row *row) {

    if (!row)
        return new_key_value(
            db_strdup(column->column_name), 
            NULL, 
            T_ROW);

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
                    Row *sub_row = define_visible_row(refer);
                    if (column->has_sub_column && column->sub_column) {
                        KeyValue *sub_key_value = query_plain_column_value(select_result, column->sub_column, sub_row);
                        free_row(sub_row);
                        return sub_key_value;
                    } else if (column->has_sub_column && column->scalar_exp_set) {
                        Row *filtered_subrow = query_plain_row_selection(select_result, column->scalar_exp_set, sub_row);
                        free_row(sub_row);
                        return new_key_value(db_strdup(column->column_name), filtered_subrow, T_ROW);
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
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    int32_t sum = *(int32_t *)left->value + *(int32_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_INT), 
                                         T_INT);
                }
                case T_LONG: {
                    int64_t sum = *(int32_t *)left->value + *(int64_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_LONG), 
                                         T_LONG);
                }
                case T_FLOAT: {
                    float sum = *(int32_t *)left->value + *(float *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double sum = *(int32_t *)left->value + *(double *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&zero, T_DOUBLE), 
                                         T_DOUBLE);
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t sum = *(int64_t *)left->value + *(int32_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_LONG), 
                                         T_LONG);
                }
                case T_LONG: {
                    int64_t sum = *(int64_t *)left->value + *(int64_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_LONG), 
                                         T_LONG);
                }
                case T_FLOAT: {
                    float sum = *(int64_t *)left->value + *(float *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double sum = *(int64_t *)left->value + *(double *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    float sum = *(float *)left->value + *(int32_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_LONG: {
                    float sum = *(float *)left->value + *(int64_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_FLOAT: {
                    float sum = *(float *)left->value + *(float *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double sum = *(float *)left->value + *(double *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double sum = *(double *)left->value + *(int32_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double sum = *(double *)left->value + *(int64_t *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double sum = *(double *)left->value + *(float *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double sum = *(double *)left->value + *(double *)right->value;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&sum, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(ADD_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        default: {
            int zero = 0;
            return new_key_value(db_strdup(ADD_NAME), 
                                 copy_value(&zero, T_INT), 
                                 T_INT);
        }
    }
}

/* Calulate substraction .*/
static KeyValue *calulate_substraction(KeyValue *left, KeyValue *right) {
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    int32_t sub = *(int32_t *)left->value - *(int32_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_INT), 
                                         T_INT);
                }
                case T_LONG: {
                    int64_t sub = *(int32_t *)left->value - *(int64_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_LONG), 
                                         T_LONG);
                }
                case T_FLOAT: {
                    float sub = *(int32_t *)left->value - *(float *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double sub = *(int32_t *)left->value - *(double *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t sub = *(int64_t *)left->value - *(int32_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_LONG), 
                                         T_LONG);
                }
                case T_LONG: {
                    int64_t sub = *(int64_t *)left->value - *(int64_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_LONG), 
                                         T_LONG);
                }
                case T_FLOAT: {
                    float sub = *(int64_t *)left->value - *(float *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double sub = *(int64_t *)left->value - *(double *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    float sub = *(float *)left->value - *(int32_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_LONG: {
                    float sub = *(float *)left->value - *(int64_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_FLOAT: {
                    float sub = *(float *)left->value - *(float *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double sub = *(float *)left->value - *(double *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double sub = *(double *)left->value - *(int32_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double sub = *(double *)left->value - *(int64_t *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double sub = *(double *)left->value - *(float *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double sub = *(double *)left->value - *(double *)right->value;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&sub, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(SUB_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        default: {
            int zero = 0;
            return new_key_value(db_strdup(SUB_NAME), 
                                 copy_value(&zero, T_INT), 
                                 T_INT);
        }
    }
}


/* Calulate multiplication .*/
static KeyValue *calulate_multiplication(KeyValue *left, KeyValue *right) {
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t mul = (*(int32_t *)left->value) * (*(int32_t *)right->value);
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_INT), 
                                         T_INT);
                }
                case T_LONG: {
                    int64_t mul = *(int64_t *)left->value * *(int64_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_LONG), 
                                         T_LONG);
                }
                case T_FLOAT: {
                    float mul = *(int32_t *)left->value * *(float *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double mul = *(int32_t *)left->value * *(double *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    int64_t mul = *(int64_t *)left->value * *(int32_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_LONG), 
                                         T_LONG);
                }
                case T_LONG: {
                    int64_t mul = *(int64_t *)left->value * *(int64_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_LONG), 
                                         T_LONG);
                }
                case T_FLOAT: {
                    float mul = *(int64_t *)left->value * *(float *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double mul = *(int64_t *)left->value * *(double *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_LONG), 
                                         T_LONG);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&zero, T_LONG), 
                                         T_LONG);
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    float mul = *(float *)left->value * *(int32_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_LONG: {
                    float mul = *(float *)left->value * *(int64_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_FLOAT: {
                    float mul = *(float *)left->value * *(float *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_FLOAT), 
                                         T_FLOAT);
                }
                case T_DOUBLE: {
                    double mul = *(float *)left->value * *(double *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double mul = *(double *)left->value * *(int32_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double mul = *(double *)left->value * *(int64_t *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double mul = *(double *)left->value * *(float *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double mul = *(double *)left->value * *(double *)right->value;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&mul, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(MUL_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        default: {
            int zero = 0;
            return new_key_value(db_strdup(MUL_NAME), 
                                 copy_value(&zero, T_INT), 
                                 T_INT);
        }
    }
}

/* Calulate division .*/
static KeyValue *calulate_division(KeyValue *left, KeyValue *right) {
    
    switch (left->data_type) {
        case T_INT: {
            switch (right->data_type) {
                case T_INT: {
                    double div = (double)(*(int32_t *)left->value) / (*(int32_t *)right->value);
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double div = (double)(*(int64_t *)left->value) / (*(int64_t *)right->value);
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double div = (double)(*(int32_t *)left->value) / (*(float *)right->value);
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double div = (double)(*(int32_t *)left->value) / *(double *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_LONG: {
            switch (right->data_type) {
                case T_INT: {
                    double div = (double)*(int64_t *)left->value / *(int32_t *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double div = (double)*(int64_t *)left->value / *(int64_t *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double div = (double)*(int64_t *)left->value / *(float *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double div = (double)*(int64_t *)left->value / *(double *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_FLOAT: {
            switch (right->data_type) {
                case T_INT: {
                    double div = (double)*(float *)left->value / *(int32_t *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double div = (double)*(float *)left->value / *(int64_t *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double div = (double)*(float *)left->value / *(float *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double div = (double)*(float *)left->value / *(double *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        case T_DOUBLE: {
            switch (right->data_type) {
                case T_INT: {
                    double div = *(double *)left->value / *(int32_t *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_LONG: {
                    double div = *(double *)left->value / *(int64_t *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_FLOAT: {
                    double div = *(double *)left->value / *(float *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                case T_DOUBLE: {
                    double div = *(double *)left->value / *(double *)right->value;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&div, T_DOUBLE), 
                                         T_DOUBLE);
                }
                default: {
                    int zero = 0;
                    return new_key_value(db_strdup(DIV_NAME), 
                                         copy_value(&zero, T_INT), 
                                         T_INT);
                }
            }
            break;
        }
        default: {
            int zero = 0;
            return new_key_value(db_strdup(DIV_NAME), 
                                 copy_value(&zero, T_INT), 
                                 T_INT);
        }
    }
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
        default:
            UNEXPECTED_VALUE(calculate->type);
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
            if (list_empty(select_result->rows))
                return new_key_value(db_strdup(column->column_name), NULL, meta_column->column_type);
            else
                /* Default, when query function and column data, column only return first data. */
                return query_plain_column_value(select_result, column, lfirst(first_cell(select_result->rows)));
        }
        case SCALAR_FUNCTION:
            return query_function_column_value(scalar_exp->function, select_result);
        case SCALAR_CALCULATE:
            return query_function_calculate_column_value(scalar_exp->calculate, select_result);
        case SCALAR_VALUE: {
            ValueItemNode *value = scalar_exp->value;
            if (list_empty(select_result->rows)) 
                return new_key_value(db_strdup("value"), NULL, convert_data_type(value->value.atom->type));
            else
                return query_value_item(value, lfirst(first_cell(select_result->rows)));
        }
        default: {
            UNEXPECTED_VALUE("Unknown scalar type");
            return NULL;
        }
    } 
}

/* Query function data. */
static void query_fuction_selecton(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {

    Row *row = new_row(NULL, db_strdup(select_result->table_name), scalar_exp_set->size);

    uint32_t i;
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
    free_list_deep(select_result->rows);

    select_result->rows = create_list(NODE_ROW);
    append_list(select_result->rows, row);
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
    Assert(value_item->type == V_ATOM);
    AtomNode *atom_node = value_item->value.atom;
    switch (atom_node->type) {
        case A_INT:
            return new_key_value(db_strdup("value"), 
                                 copy_value(&atom_node->value.intval, T_LONG), 
                                 T_LONG);
        case A_BOOL:
            return new_key_value(db_strdup("value"), 
                                 copy_value(&atom_node->value.boolval, T_BOOL), 
                                 T_BOOL);
        case A_FLOAT:
            return new_key_value(db_strdup("value"), 
                                 copy_value(&atom_node->value.boolval, T_DOUBLE), 
                                 T_DOUBLE);
        case A_STRING:
            return new_key_value(db_strdup("value"), 
                                 copy_value(atom_node->value.strval, T_STRING), 
                                 T_STRING);
        case A_REFERENCE:
            return new_key_value(db_strdup("value"), 
                                 make_null_refer(),
                                 T_STRING);
        default:
            UNEXPECTED_VALUE(atom_node->type);
            return NULL;
    }
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
            return NULL;
        default:
            UNEXPECTED_VALUE(scalar_exp->type);
            return NULL;
    }
}

/* Query a Row of Selection,
 * Actually, the Selection is pure-column scalars. */
static Row *query_plain_row_selection(SelectResult *select_result, ScalarExpSetNode *scalar_exp_set, Row *row) {

    if (!row) 
        return NULL;
    
    Table *table = open_table(row->table_name);
    MetaColumn *key_meta_column = get_primary_key_meta_column(table->meta_table);

    Row *sub_row = new_row(copy_value(row->key, key_meta_column->column_type), 
                            db_strdup(row->table_name), 
                            scalar_exp_set->size);

    uint32_t i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        KeyValue *key_value = query_row_value(select_result, scalar_exp, row);
        if (scalar_exp->alias) {
            /* Rename as alias. */
            free_value(key_value->key, T_STRING);
            key_value->key = db_strdup(scalar_exp->alias);
        }
        sub_row->data[i] = key_value;
    }
    return sub_row;
}

/* Query all columns data. */
static void query_columns_selection(ScalarExpSetNode *scalar_exp_set, SelectResult *select_result) {
    ListCell *lc;
    foreach (lc, select_result->rows) {
        Row *row = lfirst(lc);
        lfirst(lc) = query_plain_row_selection(select_result, scalar_exp_set, row);
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
        default:
            UNEXPECTED_VALUE(scalar_exp->type);
            return false;
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
    result->rows = len_list(select_result->rows);
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
