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
#include "meta.h"
#include "session.h"
#include "asserts.h"
#include "utils.h"
#include "check.h"
#include "copy.h"
#include "free.h"
#include "log.h"
#include "ret.h"

/* System reserved columns. */
MetaColumn SYS_RESERVED_COLUMNS[] = {
    { SYS_RESERVED_ID_COLUMN_NAME, T_LONG, "",  sizeof(int64_t), false, false, false, true },
    { CREATED_XID_COLUMN_NAME, T_LONG, "",  sizeof(int64_t), false, false, false, true },
    { EXPIRED_XID_COLUMN_NAME, T_LONG, "",  sizeof(int64_t), false, false, false, true }
}; 

/* System reserved columns length. */
#define SYS_RESERVED_COLUMNS_LENGTH sizeof(SYS_RESERVED_COLUMNS) / sizeof(SYS_RESERVED_COLUMNS[0])

/* Calculate meta column length. 
 * If define data len, use defined data length, note that, T_STRING & T_VARCHAR data length will add 1 for '0' as end.
 * Otherwise, use system default data length.
 * */
static uint32_t calc_column_len(DataTypeNode *data_type) {
    uint32_t column_length = 0;
    switch (data_type->type) {
        case T_VARCHAR: {
            column_length = data_type->len;
            /* Increase for reserving a char of '0' as end of string. */
            column_length++;
            break;
        }
        case T_STRING: {
            column_length = default_data_len(data_type->type);
            /* Increase for reserving a char of '0' as end of string. */
            column_length++;
            break;
        }
        default: {
            column_length = default_data_len(data_type->type);
            break;
        }
    }
    return column_length;
}

/* Column Operation. */
static void operate_column(MetaColumn *meta_column, ColumnDefOptNodeList *column_def_opt_list) {
    if (!column_def_opt_list) 
        return;
    uint32_t i;
    for (i = 0; i < column_def_opt_list->size; i++) {
        ColumnDefOptNode *column_def_opt = column_def_opt_list->set[i];
        switch (column_def_opt->opt_type) {
            case OPT_NOT_NULL:
                meta_column->not_null = true;
                break;
            case OPT_UNIQUE:
                meta_column->is_unique = true;
                break;
            case OPT_PRIMARY_KEY:
                meta_column->is_primary = true;
                break;
            case OPT_DEFAULT_VALUE:
            case OPT_DEFAULT_NULL:
            case OPT_CHECK_CONDITION:
            case OPT_REFERENECS:
                db_log(ERROR, "Not support thus column def operation yet");
                break;
        }
    }
}

/* Combine user-level column. */
MetaColumn *combine_user_meta_column(ColumnDefNode *column_def, char *table_name) {
    MetaColumn *meta_column = instance(MetaColumn);

    /* Base info. */
    strcpy(meta_column->column_name, column_def->column->column);
    meta_column->is_primary = false;
    meta_column->is_unique = false;
    meta_column->not_null = false;
    meta_column->column_type = column_def->data_type->type;
    meta_column->sys_reserved = false;
    meta_column->column_length = calc_column_len(column_def->data_type);

    /* Special handling Reference. */
    if (column_def->data_type->type == T_REFERENCE) {
        Table *sub_table = open_table(column_def->data_type->table_name);
        if (sub_table) 
            strcpy(meta_column->table_name, column_def->data_type->table_name);
        else 
            db_log(ERROR, "Table '%s' not exists.", column_def->data_type->table_name);
    }

    /* Operate column. */
    operate_column(meta_column, column_def->column_def_opt_list);

    return meta_column;
}

/* Combine sys-level column. */
MetaColumn *combine_sys_meta_column(char *table_name, int index) {
    MetaColumn *meta_column = instance(MetaColumn);
    memcpy(meta_column, SYS_RESERVED_COLUMNS + index, sizeof(MetaColumn));
    return meta_column;
}

/* Get column def size in create table statement. */
static uint32_t get_column_def_size(CreateTableNode *create_table_node) {
    uint32_t size = 0;
    uint32_t i;
    for (i = 0; i < create_table_node->base_table_element_commalist->size; i++) {
        BaseTableElementNode *base_table_element = create_table_node->base_table_element_commalist->set[i];
        if (base_table_element->type == TELE_COLUMN_DEF)
            size++;
    }
    return size;
}

/* Operate table about unique-key columns/ */
static void operate_table_unique(MetaTable *meta_table, ColumnDefNameCommalist *commalist) {
    uint32_t i;
    for (i = 0; i < commalist->size; i++) {
        ColumnDefName *column_def_name = commalist->set[i];
        MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_def_name->column);
        meta_column->is_unique = true;
        break; /* Not support mult-columns as unique key. */
    }
}

/* Operate table abount primary-key columns */
static void operate_table_primary_key(MetaTable *meta_table, ColumnDefNameCommalist *commalist) {
    uint32_t i;
    for (i = 0; i < commalist->size; i++) {
        ColumnDefName *column_def_name = commalist->set[i];
        MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_def_name->column);
        meta_column->is_primary = true;
        break; /* Not support mult-columns as primary key. */
    }
}

/* Operate table contraint. */
static void table_operate_contraint(MetaTable *meta_table, TableContraintDefNode *table_contraint) {
    switch (table_contraint->type) {
        case TCONTRAINT_UNIQUE:
            operate_table_unique(meta_table, table_contraint->column_commalist);
            break;
        case TCONTRAINT_PRIMARY_KEY: 
            operate_table_primary_key(meta_table, table_contraint->column_commalist);
            break;
        case TCONTRAINT_FOREIGN_KEY:
        case TCONTRAINT_CHECK:
            db_log(ERROR, "Not support table contraint yet.");
            break;
    }
}

/* Handler user-level none define primary key 
 * In this case, use system reserved column 'sys_id' as primary key.
 * */
void handler_user_none_priamry_key(MetaTable *meta_table) {
    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (meta_column->is_primary)
            return;
    }
    
    MetaColumn *sys_id_column = get_all_meta_column_by_name(meta_table, SYS_RESERVED_ID_COLUMN_NAME);
    Assert(sys_id_column);
    sys_id_column->is_primary = true;
}

/* Combine meta table by create table node. */
static MetaTable *combine_meta_table(CreateTableNode *create_table_node) {

    MetaTable *meta_table = instance(MetaTable);

    meta_table->table_name = db_strdup(create_table_node->table_name);
    meta_table->column_size = get_column_def_size(create_table_node); 
    meta_table->all_column_size = meta_table->column_size + SYS_RESERVED_COLUMNS_LENGTH;
    meta_table->meta_column = db_malloc(sizeof(MetaColumn *) * meta_table->all_column_size, "pointer");

    /* User-level defination. */
    uint32_t i, j;
    for (i = 0, j = 0; i < create_table_node->base_table_element_commalist->size; i++) {
        BaseTableElementNode *base_table_element = create_table_node->base_table_element_commalist->set[i];
        switch (base_table_element->type) {
            case TELE_COLUMN_DEF:
                meta_table->meta_column[j++] = combine_user_meta_column(base_table_element->column_def, create_table_node->table_name);
                break;
            case TELE_TABLE_CONTRAINT_DEF:
                table_operate_contraint(meta_table, base_table_element->table_contraint_def);
                break;
        }
    }

    /* System-level defination. */
    uint32_t k;
    for (k = j; k < meta_table->all_column_size; k++) {
        meta_table->meta_column[k] = combine_sys_meta_column(meta_table->table_name, (k - j));
    }
    
    /* Handler if user not define priamry key. */
    handler_user_none_priamry_key(meta_table);
    
    return meta_table;
}

/* Execute create table statement. */
void exec_create_table_statement(CreateTableNode *create_table_node, DBResult *result) {

    /* Check valid. */
    if (!check_create_table_node(create_table_node)) 
        return;

    /* Combine MetaTable. */
    MetaTable *meta_table = combine_meta_table(create_table_node);
    if (meta_table == NULL) 
        return;

    /* Create table. */
    if (create_table(meta_table, result)) {
        result->success = true;
        result->rows = 0;
        result->message = format("Table '%s' created successfully.", create_table_node->table_name);
        db_log(SUCCESS, "Table '%s' created successfully.", create_table_node->table_name);
    }

    free_meta_table(meta_table);
}
