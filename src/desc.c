#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "desc.h"
#include "mmu.h"
#include "misc.h"
#include "table.h"
#include "meta.h"
#include "copy.h"
#include "session.h"
#include "ret.h"

/*Get table name.*/
static char *get_table_name(DescribeNode *describe_node) {
    return describe_node->table_name;
}

static MapList *gen_describe_result(MetaTable *meta_table) {

    MapList *map_list = db_malloc2(sizeof(MapList), "MapList");
    map_list->size = meta_table->column_size;
    map_list->data = db_malloc2(sizeof(Map *) * map_list->size, "MapList.data");

    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];

        Map *map = db_malloc2(sizeof(Map), "Map");
        map->size = 4;
        map->body = db_malloc2(sizeof(KeyValue *) * map->size, "Map.body");

        /* filed */
        KeyValue *key_value_field = db_malloc2(sizeof(KeyValue), "KeyValue");
        key_value_field->key = strdup("field");
        key_value_field->value = strdup(meta_column->column_name);
        key_value_field->data_type = T_STRING;
        map->body[0] = key_value_field;

        /* type */
        KeyValue *key_value_type = db_malloc2(sizeof(KeyValue), "KeyValue");
        key_value_type->key = strdup("type");
        key_value_type->value = data_type_name(meta_column->column_type);
        key_value_type->data_type = T_STRING;
        map->body[1] = key_value_type;

        /* primary key */
        KeyValue *key_value_key = db_malloc2(sizeof(KeyValue), "KeyValue");
        key_value_key->key = strdup("primary_key");
        key_value_key->value = copy_value(&meta_column->is_primary, T_BOOL, NULL);
        key_value_key->data_type = T_BOOL;
        map->body[2] = key_value_key;

        /* primary key */
        KeyValue *key_value_size = db_malloc2(sizeof(KeyValue), "KeyValue");
        key_value_size->key = strdup("size");
        key_value_size->value = copy_value(&meta_column->column_length, T_INT, NULL);
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
        error_result(result, EXECUTE_TABLE_OPEN_FAIL, "Try to open table '%s' fail.", table_name);
        return;
    }

    MapList *map_list = gen_describe_result(table->meta_table);
    success_result(result, "Describe executed successfully.");
    result->data = map_list;
}
