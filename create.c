#include <string.h>
#include "create.h"
#include "common.h"
#include "misc.h"
#include "meta.h"
#include "log.h"

static char *get_table_name(CreateTableNode *create_table_node) {
    return create_table_node->table_name->name;
}

static uint32_t get_column_size(CreateTableNode *create_table_node) {
    return create_table_node->column_def_set_node->column_size;
}

static bool if_primary_key_column(CreateTableNode *create_table_node, char *column_name) {
    PrimaryKeyNode *primary_key_node = create_table_node->primary_key_node;
    if (primary_key_node == NULL) // if not set primary key
        return false;
    if (strcmp(primary_key_node->primary_key_column->name, column_name) == 0)
        return true;
    return false;
}

static MetaColumn *get_meta_column(CreateTableNode *create_table_node, uint32_t index) {
    MetaColumn *meta_column = malloc(sizeof(MetaColumn));
    if (meta_column == NULL)
        MALLOC_ERROR;
    memset(meta_column, 0, sizeof(MetaColumn));
    ColumnDefNode *column_def_node = *(create_table_node->column_def_set_node->column_def + index);
    strcpy(meta_column->column_name, strdup(column_def_node->column_name->name)); 
    meta_column->column_type = column_def_node->column_type->data_type;
    meta_column->is_primary = if_primary_key_column(create_table_node, meta_column->column_name);
    meta_column->column_length = column_type_length(meta_column->column_type);
    return meta_column;
}

// generate meta table by create table node
MetaTable *gen_meta_table(CreateTableNode *crete_table_node) {
    MetaTable *meta_table = malloc(sizeof(MetaTable));
    if (meta_table == NULL)
        MALLOC_ERROR;
    memset(meta_table, 0, sizeof(MetaTable));
    meta_table->table_name = get_table_name(crete_table_node);
    meta_table->column_size = get_column_size(crete_table_node);
    if (meta_table->column_size > MAX_COLUMN_SIZE) {
        log_error_d("Column number exceed maxinum number: %d ", MAX_COLUMN_SIZE);
        return NULL;
    }
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        meta_table->meta_column[i] = get_meta_column(crete_table_node, i);
    }
    return meta_table;
}
