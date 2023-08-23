#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "common.h"
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "insert.h"
#include "index.h"

// get table name in select node.
static char *get_table_name(InsertNode *insert_node) {
    return insert_node->from_item_node->table->name;
}

static uint32_t get_column_size(InsertNode *insert_node, MetaTable *meta_table) {
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
        case VARCHAR:
            return value_item_node->s_value->name;
        case INT:
            return &(value_item_node->i_value->i_value);
        case BIT:
        case DOUBLE:
        case FLOAT:
        case DATE:
        case CHAR:
        case TIMESTAMP:
            fatal("not support type.");
    }
    return NULL;
}

// generate insert row
Row *generate_insert_row(InsertNode *insert_node) {
    Row *row = malloc(sizeof(Row));
    if (NULL == row) 
        MALLOC_ERROR;
    row->key = 12;
    row->table_name = get_table_name(insert_node);
    row->data = malloc(0);
    Table *table = open_table(row->table_name);
    if (table == NULL) {
        return NULL;
    }
    MetaTable *meta_table = table->meta_table;
    row->data_len = get_column_size(insert_node, meta_table);
    if (row->data_len != get_value_size(insert_node)) {
        fatal("Inner error, column num can`t match value num in insert node");
    }
    for(uint32_t i = 0; i < row->data_len; i++) {
        KeyValue *key_value = malloc(sizeof(KeyValue));
        key_value->key = get_column_name(insert_node, i, meta_table);
        MetaColumn *meta_column = get_meta_column_by_name(meta_table, key_value->key);
        if (meta_column == NULL) {
            fprintf(stderr, "Inner error, not find meta column info by name '%s'", key_value->key);
            exit(1);
        }
        key_value->value = get_column_value(insert_node, i, meta_column);
        if (meta_column->is_primary) {
            row->key = define_key(key_value->value, meta_column);
        }
        *(row->data + i)= key_value;
    }
    return row;
}
