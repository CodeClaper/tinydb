#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "create.h"
#include "common.h"
#include "table.h"
#include "mmu.h"
#include "misc.h"
#include "meta.h"
#include "session.h"
#include "log.h"

//get table name.
static char *get_table_name(CreateTableNode *create_table_node) {
    return create_table_node->table_name;
}

//get column size
static uint32_t get_column_size(CreateTableNode *create_table_node) {
    return create_table_node->column_def_set_node->size;
}

//check if priamry key column.
static bool if_primary_key_column(CreateTableNode *create_table_node, char *column_name) {
    PrimaryKeyNode *primary_key_node = create_table_node->primary_key_node;
    if (primary_key_node) {
        if (strcmp(primary_key_node->column->column_name, column_name) == 0)
            return true;
    }
    ColumnDefSetNode *column_def_set_node = create_table_node->column_def_set_node;
    for (uint32_t i = 0; i < column_def_set_node->size; i++) {
        ColumnDefNode *column_def_node = *(column_def_set_node->column_defs + i);
        if (column_def_node->is_primary && strcmp(column_def_node->column->column_name, column_name))
            return true;
    }
    return false;
}

static MetaColumn *get_meta_column(CreateTableNode *create_table_node, uint32_t index) {
    MetaColumn *meta_column = db_malloc(sizeof(MetaColumn));
    ColumnDefNode *column_def_node = *(create_table_node->column_def_set_node->column_defs + index);
    strcpy(meta_column->column_name, strdup(column_def_node->column->column_name)); 
    meta_column->column_type = column_def_node->data_type;
    meta_column->is_primary = if_primary_key_column(create_table_node, meta_column->column_name);
    meta_column->column_length = column_type_length(meta_column->column_type);
    if (meta_column->column_type == T_REFERENCE) {
        Table *table = open_table(column_def_node->table_name);
        if (table)
            strcpy(meta_column->table_name, column_def_node->table_name);
        else 
            return NULL;
    }
    return meta_column;
}

// generate meta table by create table node
static MetaTable *gen_meta_table(CreateTableNode *crete_table_node) {
    MetaTable *meta_table = db_malloc(sizeof(MetaTable));
    meta_table->table_name = get_table_name(crete_table_node);
    meta_table->column_size = get_column_size(crete_table_node);
    if (meta_table->column_size > MAX_COLUMN_SIZE) {
        log_error_d("Column number exceed maxinum number: %d ", MAX_COLUMN_SIZE);
        return NULL;
    }
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = get_meta_column(crete_table_node, i);
        if (meta_column == NULL)
            return NULL;
        meta_table->meta_column[i] = meta_column;
    }
    return meta_table;
}

// execute create table statement.
ExecuteResult exec_create_table_statement(CreateTableNode *create_table_node) {
    char buff[1024];
    MetaTable *meta_table = gen_meta_table(create_table_node);
    if (meta_table == NULL)
        return EXECUTE_FAIL;
    ExecuteResult result = create_table(meta_table);
    if (result == EXECUTE_SUCCESS) {
        sprintf(buff, "Table %s created successfully\n", meta_table->table_name);
        db_send(buff); 
    }
    db_free(meta_table);
    return result;
}
