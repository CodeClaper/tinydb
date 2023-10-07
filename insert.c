#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "common.h"
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "node.h"
#include "table.h"
#include "pager.h"
#include "insert.h"
#include "index.h"


// check if key already exists in db
static bool check_duplicate_key(Cursor *cursor, uint32_t key) {
    void *node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t row_length = calc_table_row_length(cursor->table);
    uint32_t target = get_leaf_node_cell_key(node, cursor->cell_num, row_length);
    return target == key;
}

// get table name in select node.
static char *get_table_name(InsertNode *insert_node) {
    return insert_node->from_item_node->table->name;
}

static uint32_t get_insert_column_size(InsertNode *insert_node, MetaTable *meta_table) {
    if (insert_node->if_ignore_columns)
        return meta_table->column_size;
    else 
        return insert_node->columns_set_node->ident_set_node->num;
}

static uint32_t get_value_size(InsertNode *insert_node) {
    return insert_node->value_item_set_node->num;
}

static char *get_column_name(InsertNode *insert_node, uint32_t index, MetaTable *meta_table) {
    if (insert_node->if_ignore_columns)
        return meta_table->meta_column[index]->column_name;
    else 
        return ((IdentNode *)(insert_node->columns_set_node->ident_set_node->ident_node + index))->name;
}

static void *get_column_value(InsertNode *insert_node, uint32_t index, MetaColumn *meta_column) {
    ValueItemNode* value_item_node = *(insert_node->value_item_set_node->value_item_node + index);
    switch(meta_column->column_type) {
        case T_STRING:
            return (char *)value_item_node->s_value->s_value;
        case T_INT:
            return &(value_item_node->i_value->i_value);
        case T_BOOL:
        case T_DOUBLE:
        case T_FLOAT:
        case T_DATE:
        case T_CHAR:
        case T_TIMESTAMP:
            fatal("not support type.");
    }
    fprintf(stderr, "Unspported column type. \n");
    return NULL;
}

// generate insert row
static Row *generate_insert_row(InsertNode *insert_node) {
    uint32_t i, column_len;
    Row *row = malloc(sizeof(Row));
    if (NULL == row) 
        MALLOC_ERROR;
    row->table_name = get_table_name(insert_node);
    Table *table = open_table(row->table_name);
    if (table == NULL) {
        return NULL;
    }
    MetaTable *meta_table = table->meta_table;
    column_len = get_insert_column_size(insert_node, meta_table);
    if (column_len != get_value_size(insert_node)) {
        fprintf(stderr,"Column count doesn't match value count.\n");
        return NULL;
    }
    row->data = malloc(sizeof(KeyValue *) * column_len);
    row->column_len = column_len;
    for(i = 0; i < column_len; i++) {
        KeyValue *key_value = malloc(sizeof(KeyValue));
        char *column_name = get_column_name(insert_node, i, meta_table);
        key_value->key = strdup(column_name);
#ifdef DEBUG
        printf("key: %s\n", key_value->key);
#endif
        MetaColumn *meta_column = get_meta_column_by_name(meta_table, key_value->key);
        if (meta_column == NULL) {
            fprintf(stderr, "Inner error, not find meta column info by name '%s'", key_value->key);
            exit(1);
        }
        key_value->value = get_column_value(insert_node, i, meta_column);
        if (meta_column->is_primary) {
            row->key = define_key(key_value->value, meta_column);
        }
        *(row->data + i) = key_value;
        printf("");
    }
    return row;
}

// execute insert statement.
ExecuteResult exec_insert_statement(InsertNode *insert_node) {
    Row *row = generate_insert_row(insert_node);
    if (row == NULL)
        return EXIT_FAILURE;
    Table *table = open_table(row->table_name);
    void *root_node = get_page(table->pager, table->root_page_num); 
    Cursor *cursor = define_cursor(table, row->key);
    if (check_duplicate_key(cursor, row->key)) {
        fprintf(stderr, "key '%d' already exists, not allow duplicate key. \n", row->key);
        return EXECUTE_DUPLICATE_KEY;
    }
    insert_leaf_node(cursor, row);
    fprintf(stdout, "Successfully insert 1 row data.\n");
    // free memeory
    return EXECUTE_SUCCESS;    
}

