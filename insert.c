#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include "common.h"
#include "misc.h"
#include "table.h"
#include "insert.h"

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

static void *get_column_value(InsertNode *insert_node, uint32_t index) {
    ValueItemNode* value_item_node = (ValueItemNode *)(insert_node->value_item_set_node->value_item_node + index);
    if (value_item_node->i_value != NULL)
        return value_item_node->i_value;
    else if (value_item_node->s_value != NULL) 
        return value_item_node->s_value;
    return NULL;
}

// generate insert row
Row *generate_insert_row(InsertNode *insert_node) {
    Row *row = malloc(sizeof(Row));
    if (NULL == row) 
        MALLOC_ERROR;
    row->id = 10 *random();
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
        key_value->value = get_column_value(insert_node, i);
        *(row->data + i)= key_value;
    }
    return row;
}
