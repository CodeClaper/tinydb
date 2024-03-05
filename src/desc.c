#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "desc.h"
#include "mmu.h"
#include "table.h"
#include "meta.h"
#include "copy.h"
#include "session.h"
#include "ret.h"
#include "log.h"

/*Get table name.*/
static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->table_name;
}

/* Calculate meta column length. Notice, T_STRING data has added on extra char. */
static uint32_t calc_meta_column_len(MetaColumn *meta_column) {
    if (meta_column->column_type == T_STRING)
        return meta_column->column_length - 1;
    else 
        return meta_column->column_length;
}

/* Generate DescribeResult. */
static MapList *gen_describe_result(MetaTable *meta_table) {

    MapList *map_list = db_malloc(sizeof(MapList), SDT_MAP_LIST);
    map_list->size = meta_table->column_size;
    map_list->data = db_malloc(sizeof(Map *) * map_list->size, SDT_POINTER);

    int i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        Map *map = db_malloc(sizeof(Map), SDT_MAP);
        map->size = 4;
        map->body = db_malloc(sizeof(KeyValue *) * map->size, SDT_POINTER);

        /* filed */
        KeyValue *key_value_field = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value_field->key = db_strdup("field");
        key_value_field->value = db_strdup(meta_column->column_name);
        key_value_field->data_type = T_STRING;
        map->body[0] = key_value_field;

        /* type */
        KeyValue *key_value_type = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value_type->key = db_strdup("type");
        key_value_type->value = db_strdup(DATA_TYPE_NAMES[meta_column->column_type]);
        key_value_type->data_type = T_STRING;
        map->body[1] = key_value_type;

        /* primary key */
        KeyValue *key_value_key = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value_key->key = db_strdup("primary_key");
        key_value_key->value = copy_value(&meta_column->is_primary, T_BOOL);
        key_value_key->data_type = T_BOOL;
        map->body[2] = key_value_key;

        /* primary key */
        KeyValue *key_value_size = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);
        key_value_size->key = db_strdup("size");
        uint32_t column_length = calc_meta_column_len(meta_column);
        key_value_size->value = copy_value(&column_length, T_INT);
        key_value_size->data_type = T_INT;
        map->body[3] = key_value_size;

        map_list->data[i] = map;
    }

    return map_list;
}

/* Execute describe statment. */
void exec_describe_statement(DescribeNode *describe_node, DBResult *result) {
    char *table_name = get_table_name(describe_node); 
    Table *table = open_table(table_name);
    if (table == NULL) {
        db_log(ERROR, "Table '%s' not exist.", table_name);
        return;
    }

    MapList *map_list = gen_describe_result(table->meta_table);
    
    /* Success resule. */
    result->success = true;
    result->data = map_list;
    db_log(SUCCESS, "Describe executed successfully.");
}
