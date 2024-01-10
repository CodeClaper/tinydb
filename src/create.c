/*
 *====================== Create Module =================================
 * Create Module supports ways to create a table.
 *======================================================================
 * */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "create.h"
#include "data.h"
#include "common.h"
#include "table.h"
#include "mmu.h"
#include "misc.h"
#include "meta.h"
#include "session.h"
#include "check.h"
#include "copy.h"
#include "log.h"
#include "ret.h"

/* System reserved columns. */
MetaColumn SYS_RESERVED_COLUMNS[] = {
    { CREATED_XID_COLUMN_NAME, T_LONG, "",  sizeof(int64_t), false, true },
    { EXPIRED_XID_COLUMN_NAME, T_LONG, "",  sizeof(int64_t), false, true }
}; 

/* System reserved columns length. */
#define SYS_RESERVED_COLUMNS_LENGHT sizeof(SYS_RESERVED_COLUMNS) / sizeof(SYS_RESERVED_COLUMNS[0])

/* Get column size. */
static uint32_t get_column_size(CreateTableNode *create_table_node) {
    return create_table_node->column_def_set_node->size;
}

/* Calculate meta column length. 
 * If define data len, use defined data length.
 * Otherwise, use system default data length.
 * */
static uint32_t calc_column_len(ColumnDefNode *column_def_node) {
    return column_def_node->is_define_len ? column_def_node->data_len : default_data_len(column_def_node->data_type);
}

/* Check if priamry key column. */
static bool if_primary_key_column(CreateTableNode *create_table_node, char *column_name) {
    
    /* Firstly, find in primary key node. */
    PrimaryKeyNode *primary_key_node = create_table_node->primary_key_node;
    if (primary_key_node) {
        if (strcmp(primary_key_node->column->column_name, column_name) == 0)
            return true;
    }
    
    /* Secondly, find in column define. */
    ColumnDefSetNode *column_def_set_node = create_table_node->column_def_set_node;
    for (uint32_t i = 0; i < column_def_set_node->size; i++) {
        ColumnDefNode *column_def_node = *(column_def_set_node->column_defs + i);
        if (column_def_node->is_primary && strcmp(column_def_node->column->column_name, column_name) == 0)
            return true;
    }

    return false;
}

/* Get meta column. */
static MetaColumn *gen_meta_column(CreateTableNode *create_table_node, int index, DBResult *result) {

    MetaColumn *meta_column = db_malloc(sizeof(MetaColumn), SDT_META_COLUMN);
    ColumnDefNode *column_def_node = *(create_table_node->column_def_set_node->column_defs + index);
    strcpy(meta_column->column_name, column_def_node->column->column_name); 
    meta_column->column_type = column_def_node->data_type;
    meta_column->is_primary = if_primary_key_column(create_table_node, meta_column->column_name);
    meta_column->column_length = calc_column_len(column_def_node);
    
    /* Special handling Reference. */
    if (meta_column->column_type == T_REFERENCE) {
        Table *table = open_table(column_def_node->table_name);
        if (table)
            strcpy(meta_column->table_name, column_def_node->table_name);
        else {
            error_result(result, EXECUTE_TABLE_OPEN_FAIL, "Table '%s' not exists.", column_def_node->table_name);
            return NULL;
        }
    }

    return meta_column;
}

/* Copy system meta column. */
MetaColumn *copy_sys_meta_column(char *table_name, int index) {
    MetaColumn *meta_column = db_malloc(sizeof(MetaColumn), SDT_META_COLUMN);
    MetaColumn sys_reserved_column = SYS_RESERVED_COLUMNS[index];

    /* Copy each field. */
    meta_column->is_primary = sys_reserved_column.is_primary;
    meta_column->column_type = sys_reserved_column.column_type;
    meta_column->column_length = sys_reserved_column.column_length;
    meta_column->sys_reserved = sys_reserved_column.sys_reserved;
    strcpy(meta_column->table_name, table_name);
    strcpy(meta_column->column_name, sys_reserved_column.column_name);

    return meta_column;
}


/* Generate meta table by create table node. */
static MetaTable *gen_meta_table(CreateTableNode *crete_table_node, DBResult *result) {
    MetaTable *meta_table = db_malloc(sizeof(MetaTable), SDT_META_TABLE);
    meta_table->table_name = db_strdup(crete_table_node->table_name);
    meta_table->column_size = get_column_size(crete_table_node);
    if (meta_table->column_size > MAX_COLUMN_SIZE) {
        error_result(result, EXECUTE_EXCEEDED_MAX_COLUMN ,"Column number exceed maxinum number: %d ", MAX_COLUMN_SIZE);
        return NULL;
    }

    /* User define. */
    int i, j; 
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = gen_meta_column(crete_table_node, i, result);
        if (meta_column == NULL) 
            return NULL;
        meta_table->meta_column[i] = meta_column;
    }

    /* System define. */
    for (j = i; j < SYS_RESERVED_COLUMNS_LENGHT + i; j++) {
        meta_table->meta_column[j] = copy_sys_meta_column(meta_table->table_name, (j - i));
        meta_table->column_size++;
    }
    return meta_table;
}

/* Execute create table statement. */
void exec_create_table_statement(CreateTableNode *create_table_node, DBResult *result) {

    /* Check valid. */
    if (!check_create_table_node(create_table_node, result)) return;

    MetaTable *meta_table = gen_meta_table(create_table_node, result);
    if (meta_table == NULL) return;

    create_table(meta_table, result);

    db_free(meta_table);
}
