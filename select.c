#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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
#include "sql/intpr.h"

static char *get_table_name(SelectNode *select_node) {
    return select_node->from_item_node->table->name;
}

// checkout if meta column exist in select param
static bool if_exist(QueryParam *query_param, MetaColumn *meta_column) {
    for(uint32_t i = 0; i < query_param->column_size; i++) {
        MetaColumn *current = *(query_param->meta_columns + i);
        if (strcmp(current->column_name, meta_column->column_name) == 0) {
            return true;
        }
    }
    return false;
}

// find meta column by column name, return NULL if not exist
static MetaColumn *find_meta_column_by_name(MetaTable *meta_table, char *column_name) {
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0) {
            return meta_column;
        }
    }
    return NULL;
}

//Get value from value item node.
static void *get_value_from_value_item_node(ValueItemNode *value_item_node) {
    switch(value_item_node->data_type) {
        case T_STRING:
            return value_item_node->s_value->s_value;
        case T_INT:
            return &value_item_node->i_value->i_value;
        default:
            return NULL;
    }
}

//Check if include the internal node.
static bool include_internal_node(uint32_t min_key, uint32_t max_key, uint32_t target_key, OpType op_type) {
    switch(op_type) {
        case O_EQ:
            return min_key < target_key && target_key <= max_key;
        case O_NE:
            return !(min_key < target_key && target_key <= max_key);
        case O_GT:
            return max_key > target_key;
        case O_GE:
            return max_key >= target_key;
        case O_LT:
            return target_key > min_key;
        case O_LE:
            return target_key > min_key;
        case O_IN:
        case O_LIKE:
            fatal("not support");
            
    }
    return true;
}

// check if include the leaf node.
static bool include_leaf_node(void *destinct, QueryParam *query_param, MetaTable *meta_table) {
    ConditionNode *condition_node = query_param->condition_node;
    if (condition_node == NULL)
        return true;
    uint32_t off_set = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, condition_node->column->name) == 0) {
            void *value = destinct + off_set;
            void *target = get_value_from_value_item_node(condition_node->compare);
            return eval(condition_node->opr_node->op_type, value, target, meta_column->column_type);
        }
        off_set += meta_column->column_length;
    }
    return false;
}

//Get meta column by condition name
static MetaColumn *get_cond_meta_column(QueryParam *query_param) {
    if (query_param->condition_node == NULL)
        return NULL;
    char *col_name = query_param->condition_node->column->name;
    for(uint32_t i = 0; i < query_param->column_size; i++) {
        MetaColumn *meta_column = *(query_param->meta_columns + i);
        if (strcmp(meta_column->column_name, col_name) == 0)
            return meta_column;
    }
    return NULL;
}

//Generate select row.
static Row *generate_row(void *destinct, QueryParam *query_param, MetaTable *meta_table) {
    Row *row = malloc(sizeof(Row));
    if (row == NULL)
        MALLOC_ERROR;
    memset(row, 0, sizeof(Row));
    row->column_len = 0;
    row->table_name = strdup(query_param->table_name);
    row->data = malloc(sizeof(KeyValue *) * query_param->column_size);
    uint32_t off_set = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (meta_column->is_primary) {
            row->key = *(uint32_t *)(destinct + off_set);
        }
        if (if_exist(query_param, meta_column)) {
            KeyValue *key_value = malloc(sizeof(KeyValue));
            key_value->key = strdup(meta_column->column_name);
            key_value->value = copy_value(destinct + off_set, meta_column->column_type);
            key_value->data_type = meta_column->column_type;
            *(row->data + row->column_len) = key_value;
            row->column_len++;
        }
        off_set += meta_column->column_length;
    }
    return row;
}

//Select through leaf node
static void select_from_leaf_node(SelectResult *select_result, QueryParam *query_param, void *leaf_node, Table *table) {
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t row_size = calc_table_row_length(table);
    for (uint32_t i = 0; i < cell_num; i++) {
        void *destinct = get_leaf_node_cell_value(leaf_node, row_size, i); 
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
    for(int32_t i = 0; i < keys_num; i++) {
        // check if index column, and avoid full text 
        if (cond_meta_column != NULL && cond_meta_column->is_primary) {
            uint32_t max_key = get_internal_node_keys(internal_node, i);
            uint32_t min_key = i == 0 ? 0 : get_internal_node_keys(internal_node, i - 1);
            ConditionNode *condition_node = query_param->condition_node;
            uint32_t compare_value = *(uint32_t *)get_value_from_value_item_node(condition_node->compare);
            if (!include_internal_node(min_key, max_key, compare_value, condition_node->opr_node->op_type))
                continue;
        }
        uint32_t page_num = get_internal_node_child(internal_node, i);
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

// convert from select node to select param
QueryParam *convert_query_param(SelectNode *select_node) {
    QueryParam *query_param = malloc(sizeof(QueryParam));
    memset(query_param, 0, sizeof(QueryParam));
    query_param->table_name = strdup(get_table_name(select_node));
    query_param->is_function = select_node->select_items_node->is_function_node;
    Table *table = open_table(query_param->table_name);
    if (table == NULL)
        return NULL;
    if (query_param->is_function) 
    {
        memcpy(query_param->function_node, select_node->select_items_node->function_node, sizeof(FunctionNode));
    } 
    else 
    {
        if (select_node->select_items_node->ident_set_node->all_column)
        {
            MetaTable *meta_table = table->meta_table;
            query_param->column_size = meta_table->column_size;
            query_param->meta_columns = malloc(sizeof(MetaTable *) * meta_table->column_size);
            for(int i = 0; i < meta_table->column_size; i++) {
                MetaColumn *meta_column = meta_table->meta_column[i];
                *(query_param->meta_columns + i) = malloc(sizeof(MetaColumn));
                memset(*(query_param->meta_columns + i), 0, sizeof(MetaColumn));
                memcpy(*(query_param->meta_columns + i), meta_column, sizeof(MetaColumn));
            }
        } 
        else 
        {
            query_param->column_size = select_node->select_items_node->ident_set_node->num;
            query_param->meta_columns = malloc(0);
            for(int i = 0; i < query_param->column_size; i++) {
                IdentNode *current = *(select_node->select_items_node->ident_set_node->ident_node + i);
                MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, current->name);
                if (meta_column == NULL) {
                    fprintf(stderr, "Column '%s' dost not exist in table '%s'\n", current->name, query_param->table_name);
                    return NULL;
                }
                query_param->meta_columns = realloc(query_param->meta_columns, sizeof(MetaColumn *) * (i + 1));
                *(query_param->meta_columns + i) = malloc(sizeof(MetaColumn));
                memset(*(query_param->meta_columns + i), 0, sizeof(MetaColumn));
                memcpy(*(query_param->meta_columns + i), meta_column, sizeof(MetaColumn));
            }
        }
    }
    query_param->condition_node = tree(select_node->condition_node); // generate condition tree.
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
            MetaColumn *meta_column = table->meta_table->meta_column[j];
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
            MetaColumn *meta_column = *(query_param->meta_columns + j);
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
    switch(condition_node->conn_node->conn_type) {
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
