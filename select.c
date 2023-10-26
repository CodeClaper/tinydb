#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "select.h"
#include "table.h"
#include "pager.h"
#include "node.h"
#include "meta.h"
#include "common.h"
#include "misc.h"
#include "cond.h"
#include "row.h"
#include "opr.h"
#include "copy.h"
#include "free.h"
#include "output.h"
#include "log.h"
#include "index.h"
#include "intpr.h"

//Get table name.
static char *get_table_name(SelectNode *select_node) {
    return select_node->table_name;
}

// find meta column index, return NULL if not exist
static MetaColumn *find_select_item_meta_column(QueryParam *query_param, uint32_t index) {
    SelectItemsNode *select_items_node = query_param->select_items;
    Table *table = open_table(query_param->table_name);
    switch(select_items_node->type) {
        case SELECT_ALL:
            return table->meta_table->meta_column[index];
        case SELECT_COLUMNS: 
            {
                ColumnNode *column_node = *(select_items_node->column_set_node->columns + index);
                return get_meta_column_by_name(table->meta_table, column_node->column_name);
            }
        case SELECT_FUNCTION:
            return NULL;
    }
}

static uint32_t calc_off_set(QueryParam *query_param, char *column_name) {
    SelectItemsNode *select_items_node = query_param->select_items;
    Table *table = open_table(query_param->table_name);
    MetaTable *meta_table = table->meta_table;
    uint32_t off_set = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0)
            break;
        off_set += meta_column->column_length;
    }
    return off_set;
}

//Get query param column size.
static uint32_t get_query_columns_num(QueryParam *query_param) {
    SelectItemsNode *select_items_node = query_param->select_items;
    switch(select_items_node->type) {
        case SELECT_ALL:
            {
                Table *table = open_table(query_param->table_name);
                return table->meta_table->column_size;
            }
        case SELECT_COLUMNS:
            return select_items_node->column_set_node->size;
        case SELECT_FUNCTION:
            return 1;
    }
}

//Get value from value item node.
void *get_value_from_value_item_node(ValueItemNode *value_item_node, DataType meta_data_type) {
    switch(meta_data_type) {
        case T_CHAR:
            {
                switch(value_item_node->data_type) {
                    case T_STRING:
                        value_item_node->c_value = *value_item_node->s_value;
                    case T_CHAR:
                        value_item_node->data_type = T_CHAR;
                        return &value_item_node->c_value;
                    default:
                        fatal("Data type error.");
                }
            }
        case T_STRING:
            return value_item_node->s_value;
        case T_INT:
            return &value_item_node->i_value;
        case T_BOOL:
            return &value_item_node->b_value;
        case T_FLOAT: 
            {
                switch(value_item_node->data_type) {
                    case T_INT:
                        value_item_node->f_value = value_item_node->i_value;
                    case T_FLOAT:
                        value_item_node->data_type = T_FLOAT;
                        return &value_item_node->f_value;
                    default:
                        fatal("Data type error.");
                }
            }
        case T_DOUBLE: 
            {
                switch(value_item_node->data_type) {
                    case T_INT:
                        value_item_node->d_value = value_item_node->i_value;
                    case T_FLOAT:
                        value_item_node->d_value = value_item_node->f_value;
                    case T_DOUBLE:
                        value_item_node->data_type = T_DOUBLE;
                        return &value_item_node->d_value;
                    default:
                        fatal("Data type error.");
                }
            }
        case T_TIMESTAMP:
            {
                switch(value_item_node->data_type)
                {
                    case T_STRING:
                        {
                            struct tm *tmp_time = malloc(sizeof(struct tm));
                            strptime(value_item_node->s_value, "%Y-%m-%d %H:%M:%S", tmp_time);
                            value_item_node->t_value = mktime(tmp_time);
                            value_item_node->data_type = T_TIMESTAMP;
                        }
                    case T_TIMESTAMP:
                        return &value_item_node->t_value;
                    default:
                        fatal("Data type error.");
                }
                break;
            }
        case T_DATE: 
            {
                switch(value_item_node->data_type)
                {
                    case T_STRING:
                        {
                            struct tm *tmp_time = malloc(sizeof(struct tm));
                            strptime(value_item_node->s_value, "%Y-%m-%d", tmp_time);
                            tmp_time->tm_sec = 0;
                            tmp_time->tm_min = 0;
                            tmp_time->tm_hour = 0;
                            value_item_node->t_value = mktime(tmp_time);
                            value_item_node->data_type = T_DATE;
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

//Check if include the internal node.
static bool include_internal_node(void *min_key, void *max_key, void *target_key, OprType opr_type, DataType key_data_type) {
    switch(opr_type) {
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

// check if include the leaf node.
static bool include_leaf_node(void *destinct, QueryParam *query_param, MetaTable *meta_table) {
    ConditionNode *condition_node = query_param->condition_node;
    if (condition_node == NULL) // if not condition, just return true.
        return true;
    uint32_t off_set = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, condition_node->column->column_name) == 0) {
            void *value = destinct + off_set;
            void *target = get_value_from_value_item_node(condition_node->value, meta_column->column_type);
            return eval(condition_node->opr_type, value, target, meta_column->column_type);
        }
        off_set += meta_column->column_length;
    }
    return false;
}

//Get meta column by condition name
static MetaColumn *get_cond_meta_column(QueryParam *query_param) {
    ConditionNode *condition_node = query_param->condition_node;
    if (condition_node == NULL)
        return NULL;
    Table *table = open_table(query_param->table_name);
    MetaTable *meta_table = table->meta_table;
    return get_meta_column_by_name(meta_table, query_param->condition_node->column->column_name);
}

//Generate select row.
static Row *generate_row(void *destinct, QueryParam *query_param, MetaTable *meta_table) {
    Row *row = malloc(sizeof(Row));
    if (row == NULL)
        MALLOC_ERROR;
    memset(row, 0, sizeof(Row));
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return NULL;
    row->column_len = get_query_columns_num(query_param);
    row->table_name = strdup(query_param->table_name);
    // define row data. 
    row->data = malloc(sizeof(KeyValue *) * row->column_len);
    bool is_function = query_param->select_items->type == SELECT_FUNCTION;
    if (is_function)
    {

    } 
    else
    {
        for (uint32_t i = 0; i < row->column_len; i++) {
            MetaColumn *meta_column = find_select_item_meta_column(query_param, i);     
            KeyValue *key_value = malloc(sizeof(KeyValue));
            memset(key_value, 0, sizeof(KeyValue));
            uint32_t off_set = calc_off_set(query_param, meta_column->column_name);
            key_value->key = strdup(meta_column->column_name);
            key_value->value = copy_value(destinct + off_set, meta_column->column_type);
            key_value->data_type = meta_column->column_type;
            *(row->data + i) = key_value;
        }
    }
    //define row key
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    uint32_t priamry_key_set_off = calc_off_set(query_param, primary_key_meta_column->column_name);
    row->key = copy_value(destinct + priamry_key_set_off, primary_key_meta_column->column_type);
    return row;
}

//Select through leaf node
static void select_from_leaf_node(SelectResult *select_result, QueryParam *query_param, void *leaf_node, Table *table) {
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);
    for (uint32_t i = 0; i < cell_num; i++) {
        void *destinct = get_leaf_node_cell_value(leaf_node, key_len, value_len, i); 
        if (!include_leaf_node(destinct, query_param, table->meta_table))
            continue;
        Row *row = generate_row(destinct, query_param, table->meta_table);
        select_result->row = realloc(select_result->row, sizeof(Row *) * (select_result->row_size + 1));
        *(select_result->row + select_result->row_size) = row;
        select_result->row_size++;
    }
}

// select through internal node
static void select_from_internal_node(SelectResult *select_result, QueryParam *query_param, void *internal_node, Table *table) {
    MetaColumn *cond_meta_column = get_cond_meta_column(query_param);
    uint32_t keys_num = get_internal_node_keys_num(internal_node);
    uint32_t key_len = calc_primary_key_length(table);
    MetaColumn *priamry_key_meta_column = get_primary_key_meta_column(table->meta_table);
    for(int32_t i = 0; i < keys_num; i++) {
        // check if index column to avoid full text scanning.
        if (cond_meta_column != NULL && cond_meta_column->is_primary) {
            void *max_key = get_internal_node_keys(internal_node, i, key_len);
            void *min_key = i == 0 ? NULL : get_internal_node_keys(internal_node, i - 1, key_len);
            ConditionNode *condition_node = query_param->condition_node;
            void* compare_value = get_value_from_value_item_node(condition_node->value, cond_meta_column->column_type);
            if (!include_internal_node(min_key, max_key, compare_value, condition_node->opr_type, priamry_key_meta_column->column_type))
                continue;
        }
        uint32_t page_num = get_internal_node_child(internal_node, i, key_len);
        void *node = get_page(table->pager, page_num);
        switch (get_node_type(node)) {
            case LEAF_NODE:
                select_from_leaf_node(select_result, query_param, node, table);
                break;
            case INTERNAL_NODE:
                select_from_internal_node(select_result, query_param, node, table);
                break;
        }
    }
    // don`t forget the right child
    uint32_t right_child_page_num = get_internal_node_right_child(internal_node);
    void *right_child = get_page(table->pager, right_child_page_num);
    switch (get_node_type(right_child)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, query_param, right_child, table);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, query_param, right_child, table);
            break;
    }
}

// convert from select node to query param
QueryParam *convert_query_param(SelectNode *select_node) {
    QueryParam *query_param = malloc(sizeof(QueryParam));
    memset(query_param, 0, sizeof(QueryParam));
    query_param->table_name = strdup(get_table_name(select_node));
    query_param->select_items = copy_select_items_node(select_node->select_items_node);
    ConditionNode *condition_node_copy = copy_condition_node(select_node->condition_node);
    query_param->condition_node = tree(condition_node_copy); // generate condition tree.
    clean_next(query_param->condition_node);
    return query_param;
}

 
// generate select reuslt.
SelectResult *gen_select_result(QueryParam *query_param) {
    SelectResult *select_result = malloc(sizeof(SelectResult));
    if (select_result == NULL)
        MALLOC_ERROR;
    select_result->row_size = 0;
    select_result->row = malloc(0);
    select_result->table_name = strdup(query_param->table_name);
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return NULL;
    void *root = get_page(table->pager, table->root_page_num);
    switch (get_node_type(root)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, query_param ,root, table);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, query_param ,root, table);
            break;
    }
    return select_result;
}

// print key value
static void print_row_value(KeyValue *key_value) {
    switch(key_value->data_type) {
        case T_INT:
            fprintf(stdout, "%d", *(uint32_t *)key_value->value);
            break;
        case T_STRING:
            fprintf(stdout, "\"%s\"", (char *)key_value->value);
            break;
        case T_FLOAT:
            fprintf(stdout, "%f", *(float *)key_value->value);
            break;
        case T_DOUBLE:
            fprintf(stdout, "%f", *(double *)key_value->value);
            break;
        default:
            fprintf(stdout, "not support data type");
    }
}

// print select result beauty format.
void print_select_result_beauty(SelectResult *select_result) {
    uint32_t i, j;
    Table *table = open_table(select_result->table_name);
    if (table == NULL)
        return;
    fprintf(stdout, "[");
    if (select_result->row_size > 0)
        fprintf(stdout, "\n");
    for (i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        fprintf(stdout, "\t{"); 
        if (row->column_len > 0)
            fprintf(stdout, "\n");
        for (j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            fprintf(stdout, "\t\t%s:\t", key_value->key);
            print_row_value(key_value);
            if (j < row->column_len - 1)
                fprintf(stdout, ",\n");
            else
                fprintf(stdout, "\n");
        }
        if (i < select_result->row_size - 1)
            fprintf(stdout, "\t},\n"); 
        else
            fprintf(stdout, "\t}\n"); 
    }
    fprintf(stdout, "]\n");
    fprintf(stdout, "Successfully select %d rows.\n", select_result->row_size);
}


// print select result plain format.
void print_select_result_plain(SelectResult *select_result, QueryParam *query_param) {
    fprintf(stdout, "[");
    for (uint32_t i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        fprintf(stdout, "{"); 
        for (uint32_t j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            fprintf(stdout, "\"%s\": ", key_value->key);
            print_row_value(key_value);
            if (j < row->column_len - 1) 
                fprintf(stdout, ", ");
        }
        fprintf(stdout, "}"); 
        if (i < select_result->row_size - 1)
            fprintf(stdout, ", ");
    }
    fprintf(stdout, "]\n");
    fprintf(stdout, "Successfully select %d rows.\n", select_result->row_size);
}

//Genetate output.
void put_select_result(SelectResult *select_result, QueryParam *query_param, Output *out_put) {
    uint32_t buff_size = BUFF_SIZE;
    print_data(out_put, strdup("["));
    for (uint32_t i = 0; i < select_result->row_size; i++) {
        Row *row = *(select_result->row + i);
        print_data(out_put, strdup("{")); 
        for (uint32_t j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            print_data(out_put, get_key_value_pair_str(key_value->key, key_value->value, key_value->data_type));
            if (j < row->column_len - 1) 
                print_data(out_put,strdup(", "));
        }
        print_data(out_put, strdup("}")); 
        if (i < select_result->row_size - 1)
            print_data(out_put, strdup(", "));
    }
    print_data(out_put, strdup("]"));
}

// print select result plain format.
void print_select_result_count(SelectResult *select_result) {
    fprintf(stdout, "%d\n", select_result->row_size);
}

//Generate new query param and replace condition node.
static QueryParam *new_query_param(QueryParam *query_param, ConditionNode *new_condition) {
    QueryParam *query_param_copy = copy_query_param(query_param);
    ConditionNode *old_condition_node = query_param_copy->condition_node;
    query_param_copy->condition_node = copy_condition_node(new_condition); // replace new conditon node.
    free_condition_node(old_condition_node); // free old conditon node.
    return query_param_copy;
}

//And loigc condition process
SelectResult *and_logic_cond_proc(QueryParam *query_param) {
    ConditionNode *condition_node = query_param->condition_node;
    // copy new query param
    QueryParam *left_query_param = new_query_param(query_param, condition_node->left);
    QueryParam *right_query_param = new_query_param(query_param, condition_node->right);
    // Separately calulate result and reduce
    SelectResult *left_select_result = query_with_condition(left_query_param);
    SelectResult *right_select_result = query_with_condition(right_query_param);
    SelectResult *result = reduce(left_select_result, right_select_result);
    // Free 
    free_query_param(left_query_param);
    free_query_param(right_query_param);
    free_select_result(left_select_result); 
    free_select_result(right_select_result);
    return result;
}

//Or logic condition process
SelectResult *or_logic_cond_proc(QueryParam *query_param) {
    ConditionNode *condition_node = query_param->condition_node;
    // copy new query param
    QueryParam *left_query_param = new_query_param(query_param, condition_node->left);
    QueryParam *right_query_param = new_query_param(query_param, condition_node->right);
    // Separately calulate result and merge
    SelectResult *left_select_result = query_with_condition(left_query_param);
    SelectResult *right_select_result = query_with_condition(right_query_param);
    SelectResult *result = merge(left_select_result, right_select_result);
    // Free
    free_query_param(left_query_param);
    free_query_param(right_query_param);
    free_select_result(right_select_result); 
    return result;
}

//Logic condition process
SelectResult *logic_cond_proc(QueryParam *query_param) {
    ConditionNode *condition_node = query_param->condition_node;
    switch(condition_node->conn_type) {
        case C_AND:
            return and_logic_cond_proc(query_param);
        case C_OR:
            return or_logic_cond_proc(query_param);
    }
}

//Exec condition process
SelectResult *exec_cond_proc(QueryParam *query_param) {
    return gen_select_result(query_param);
}


//Query with condition
SelectResult *query_with_condition(QueryParam *query_param) {
    ConditionNode *condition_node = query_param->condition_node;
    if (condition_node == NULL)
        return gen_select_result(query_param);
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            return logic_cond_proc(query_param);
        case EXEC_CONDITION:
            return exec_cond_proc(query_param);
    }
}
