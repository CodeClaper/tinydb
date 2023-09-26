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
#include "sql/intpr.h"

static char *get_table_name(SelectNode *select_node) {
    return select_node->from_item_node->table->name;
}

// checkout if meta column exist in select param
static bool if_exist(SelectParam *select_param, MetaColumn *meta_column) {
    for(uint32_t i = 0; i < select_param->column_size; i++) {
        MetaColumn *current = *(select_param->meta_columns + i);
        if (strcmp(current->column_name, meta_column->column_name) == 0) {
            return true;
        }
    }
    return false;
}

// generate select row.
static Row *generate_row(void *destinct, SelectParam *select_param, MetaTable *meta_table) {
    Row *row = malloc(sizeof(Row));
    if (row == NULL)
        MALLOC_ERROR;
    row->column_len = 0;
    row->table_name = strdup(select_param->table_name);
    row->data = malloc(sizeof(KeyValue *) * select_param->column_size);
    uint32_t off_set = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (if_exist(select_param, meta_column)) {
            KeyValue *key_value = malloc(sizeof(KeyValue));
            key_value->key = strdup(meta_column->column_name);
            key_value->value = destinct + off_set;
            *(row->data + row->column_len) = key_value;
            row->column_len++;
        }
        off_set += meta_column->column_length;
    }
    return row;
}

// select work through leaf node
static void select_from_leaf_node(SelectResult *select_result, SelectParam *select_param, void *leaf_node, Table *table) {
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t row_size = calc_table_row_length(table);
    for (uint32_t i = 0; i < cell_num; i++) {
        void *destinct = get_leaf_node_cell_value(leaf_node, row_size, i); 
        select_result->row = realloc(select_result->row, sizeof(Row *) * (select_result->row_len + 1));
        *(select_result->row + select_result->row_len)  = generate_row(destinct, select_param, table->meta_table);
        select_result->row_len++;
    }
}

// select work through internal node
static void select_from_internal_node(SelectResult *select_result, SelectParam *select_param, void *internal_node, Table *table) {
    uint32_t keys_num = get_internal_node_keys_num(internal_node);
    for(int32_t i = 0; i < keys_num; i++) {
        uint32_t page_num = get_internal_node_child(internal_node, i);
        void *node = get_page(table->pager, page_num);
        switch (get_node_type(node)) {
            case LEAF_NODE:
                select_from_leaf_node(select_result, select_param, node, table);
                break;
            case INTERNAL_NODE:
                select_from_internal_node(select_result, select_param, node, table);
                break;
        }
    }
    // don`t forget the right child
    uint32_t right_child_page_num = get_internal_node_right_child(internal_node);
    void *right_child = get_page(table->pager, right_child_page_num);
    switch (get_node_type(right_child)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, select_param, right_child, table);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, select_param, right_child, table);
            break;
    }
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


// convert from select node to select param
SelectParam *convert_select_param(SelectNode *select_node) {
    SelectParam *select_param = malloc(sizeof(SelectParam));
    select_param->table_name = strdup(get_table_name(select_node));
    select_param->is_function = select_node->select_items_node->is_function_node;
    Table *table = open_table(select_param->table_name);
    if (select_param->is_function)
        memcpy(select_param->function_node, select_node->select_items_node->function_node, sizeof(FunctionNode));
    else {
        if (select_node->select_items_node->ident_set_node->all_column) {
            MetaTable *meta_table = table->meta_table;
            select_param->column_size = meta_table->column_size;
            select_param->meta_columns = malloc(sizeof(MetaTable *) * meta_table->column_size);
            for(int i = 0; i < meta_table->column_size; i++) {
                MetaColumn *meta_column = meta_table->meta_column[i];
                *(select_param->meta_columns + i) = malloc(sizeof(MetaColumn));
                memset(*(select_param->meta_columns + i), 0, sizeof(MetaColumn));
                memcpy(*(select_param->meta_columns + i), meta_column, sizeof(MetaColumn));
            }
        } else {
            select_param->column_size = select_node->select_items_node->ident_set_node->num;
            select_param->meta_columns = malloc(0);
            for(int i = 0; i < select_param->column_size; i++) {
                IdentNode *current = *(select_node->select_items_node->ident_set_node->ident_node + i);
                MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, current->name);
                if (meta_column == NULL) {
                    fprintf(stderr, "Column '%s' dost not exist in table '%s'\n", current->name, select_param->table_name);
                    return NULL;
                }
                select_param->meta_columns = realloc(select_param->meta_columns, sizeof(MetaColumn *) * (i + 1));
                *(select_param->meta_columns + i) = malloc(sizeof(MetaColumn));
                memset(*(select_param->meta_columns + i), 0, sizeof(MetaColumn));
                memcpy(*(select_param->meta_columns + i), meta_column, sizeof(MetaColumn));
            }
        }
    }
    return select_param;
}

 
// generate select reuslt.
SelectResult *gen_select_result(SelectParam *select_param) {
    SelectResult *select_result = malloc(sizeof(SelectResult));
    if (select_result == NULL)
        MALLOC_ERROR;
    select_result->row_len = 0;
    select_result->row = malloc(0);
    select_result->table_name = strdup(select_param->table_name);
    Table *table = open_table(select_param->table_name);
    if (table == NULL)
        return NULL;
    void *root = get_page(table->pager, table->root_page_num);
    switch (get_node_type(root)) {
        case LEAF_NODE:
            select_from_leaf_node(select_result, select_param ,root, table);
            break;
        case INTERNAL_NODE:
            select_from_internal_node(select_result, select_param ,root, table);
            break;
    }
    return select_result;
}

static void print_row_value(void *value, MetaColumn *meta_column) {
    switch(meta_column->column_type) {
        case T_INT:
            fprintf(stdout, "%d", *(uint32_t *)value);
            break;
        case T_STRING:
            fprintf(stdout, "\"%s\"", (char *)value);
            break;
        case T_FLOAT:
            fprintf(stdout, "%f", *(float *)value);
            break;
        case T_DOUBLE:
            fprintf(stdout, "%f", *(double *)value);
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
    if (select_result->row_len > 0)
        fprintf(stdout, "\n");
    for (i = 0; i < select_result->row_len; i++) {
        Row *row = *(select_result->row + i);
        fprintf(stdout, "\t{"); 
        if (row->column_len > 0)
            fprintf(stdout, "\n");
        for (j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            MetaColumn *meta_column = table->meta_table->meta_column[j];
            fprintf(stdout, "\t\t%s:\t", key_value->key);
            print_row_value(key_value->value, meta_column);
            if (j < row->column_len - 1)
                fprintf(stdout, ",\n");
            else
                fprintf(stdout, "\n");
        }
        if (i < select_result->row_len - 1)
            fprintf(stdout, "\t},\n"); 
        else
            fprintf(stdout, "\t}\n"); 
    }
    fprintf(stdout, "]\n");
    fprintf(stdout, "Successfully select %d rows.\n", select_result->row_len);
}


// print select result plain format.
void print_select_result_plain(SelectResult *select_result, SelectParam *select_param) {
    fprintf(stdout, "[");
    for (uint32_t i = 0; i < select_result->row_len; i++) {
        Row *row = *(select_result->row + i);
        fprintf(stdout, "{"); 
        for (uint32_t j = 0; j < row->column_len; j++) {
            KeyValue *key_value = *(row->data + j);
            MetaColumn *meta_column = *(select_param->meta_columns + j);
            fprintf(stdout, "\"%s\": ", key_value->key);
            print_row_value(key_value->value, meta_column);
            if (j < row->column_len - 1) 
                fprintf(stdout, ", ");
        }
        fprintf(stdout, "}"); 
        if (i < select_result->row_len - 1)
            fprintf(stdout, ", ");
    }
    fprintf(stdout, "]\n");
    fprintf(stdout, "Successfully select %d rows.\n", select_result->row_len);
}



// print select result plain format.
void print_select_result_count(SelectResult *select_result) {
    fprintf(stdout, "%d\n", select_result->row_len);
}
