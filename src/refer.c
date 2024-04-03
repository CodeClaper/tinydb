/**
 * ============================================================ Refer Manger ============================================================================
 * The Refer Manager works around the refer. TinyDb supports REFERENCE data type which help you use other table as column data type. 
 * In fact it is a pointer. And, TinyDb recommands Refer instead of Join.
 * Refer has more effecitve on DQL operation than Join. If you know the position of data in disk, you can immediately
 * get the data, but if you just have the relationship of tables on columns, you need traverse all data to find out the data satisfied the relationship.
 * Everything has a cost. Refer is good at DQL operation, but has much thing to at DML operation.
 * When inserting or modifying a row, the refer maybe will change and tinydb must manager the changes, this is what the Refer Manager to do. 
 * ======================================================================================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "refer.h"
#include "data.h"
#include "table.h"
#include "mmu.h"'
#include "copy.h"
#include "free.h"
#include "select.h"
#include "meta.h"
#include "index.h"
#include "ltree.h"
#include "xlog.h"
#include "pager.h"
#include "utils.h"
#include "asserts.h"
#include "log.h"

/* Generate new Refer. 
 * Note: if page_num is -1 and cell_num is -1 which means refer null. */
Refer *new_refer(char *table_name, int32_t page_num, int32_t cell_num) {
    Refer *refer = db_malloc(sizeof(Refer), SDT_REFER);
    strcpy(refer->table_name, table_name);
    refer->page_num = page_num;
    refer->cell_num = cell_num;
    return refer;
}

/* Generate new cursor. */
Cursor *new_cursor(Table *table, uint32_t page_num, uint32_t cell_num) {
    Cursor *cursor = db_malloc(sizeof(Cursor), SDT_CURSOR);
    cursor->table = table;
    cursor->page_num = page_num;
    cursor->cell_num = cell_num;
    return cursor;
}


/* Define cursor when meet leaf node. */
static Cursor *define_cursor_leaf_node(Table *table, void *leaf_node, uint32_t page_num, void *key) {
    Cursor *cursor = db_malloc(sizeof(Cursor), SDT_CURSOR);
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t row_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);
    cursor->table = table;
    cursor->page_num = page_num;
    cursor->cell_num = get_leaf_node_cell_index(leaf_node, key, cell_num, key_len, row_len, primary_meta_column->column_type);
    return cursor;
}

/* Define cursor when meet internal node. */
static Cursor *define_cursor_internal_node(Table *table, void *internal_node, void *key) {
    uint keys_num = get_internal_node_keys_num(internal_node);
    uint32_t key_len = calc_primary_key_length(table);
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    uint32_t child_page_num = get_internal_node_cell_child_page_num(internal_node, key, keys_num, key_len, primary_meta_column->column_type);
    void *child_node = get_page(table->meta_table->table_name, table->pager, child_page_num);
    
    switch(get_node_type(child_node)) {
        case LEAF_NODE:
            return define_cursor_leaf_node(table, child_node, child_page_num, key);
        case INTERNAL_NODE:
            return define_cursor_internal_node(table, child_node, key);
    }
}

/* Define Cursor. */
Cursor *define_cursor(Table *table, void *key) {
    assert_not_null(key, "Input key can`t be NULL");
    void *root_node = get_page(table->meta_table->table_name, table->pager, table->root_page_num);
    switch(get_node_type(root_node)) {
        case LEAF_NODE:
            return define_cursor_leaf_node(table, root_node, table->root_page_num, key);
        case INTERNAL_NODE:
            return define_cursor_internal_node(table, root_node, key);
        default:
            db_log(PANIC, "Unknown node type occured in <define_cursor>.");
    }
}

/* Define Refer */
Refer *define_refer(Row *row) {
    Table *table = open_table(row->table_name);
    Cursor *cursor = define_cursor(table, row->key);
    Refer *refer = convert_refer(cursor);
    free_cursor(cursor);
    return refer;
}

/* Fetch Refer. 
 * If found no one or many one, return NULL.  */
Refer *fetch_refer(MetaColumn *meta_column, ConditionNode *condition_node) {
    /* Make a fake QueryParam. */
    Table *table = open_table(meta_column->table_name);

    /* Make a new SelectResult. */
    SelectResult *select_result = new_select_result(meta_column->table_name);

    query_with_condition(condition_node, select_result, select_row, NULL);

    Refer *refer = NULL;
    if (select_result->row_size > 1) {
        db_log(ERROR, "Expected to one reference, but found %d, maybe you can use 'in' as for array.", select_result->row_size);
        return NULL;
    }
    else if (select_result->row_size == 1) {
        /* Take the first row as refered. Maybe row size should be one, but now there is no check. */
        Row *row = select_result->rows[0];
        refer = define_refer(row);
    }
    free_select_result(select_result);

    return refer;
}

/* Check if refer null. 
 * If page number is -1 and cell number is -1, it means refer null. */
bool refer_null(Refer *refer) {
    return refer->page_num == -1 && refer->cell_num == -1;
}

/* Make a NULL Refer. */
Refer *make_null_refer() {
    Refer *refer = db_malloc(sizeof(Refer), SDT_REFER);
    refer->page_num = -1;
    refer->cell_num = -1;
    return refer;
}

/* Generate new ReferUpdateEntity. */
static ReferUpdateEntity *new_refer_update_entity(Refer *old_refer, Refer *new_refer) {
    ReferUpdateEntity *refer_update_entity = db_malloc(sizeof(ReferUpdateEntity), SDT_REFER_UPDATE_ENTITY);
    refer_update_entity->old_refer = old_refer;
    refer_update_entity->new_refer = new_refer;
}

/* Convert to refer from cursor. */
Refer *convert_refer(Cursor *cursor) {
    if (cursor == NULL) 
        return NULL;
    /* Generate new refer. */
    Refer *refer = db_malloc(sizeof(Refer), SDT_REFER);
    strcpy(refer->table_name, cursor->table->meta_table->table_name);
    refer->page_num = cursor->page_num;
    refer->cell_num = cursor->cell_num;

    return refer;
}

/* Convert to Cursor from Refer. */
Cursor *convert_cursor(Refer *refer) {
    if (refer == NULL)
        return NULL;
    Table *table = open_table(refer->table_name);

    return new_cursor(table, refer->page_num, refer->cell_num);
}

/* Check if table has column refer to. */
static bool if_table_refer_to(char *table_name, char *refer_table_name) {
    Table *table = open_table(table_name);
    assert_not_null(table, "Table '%s' not exist. ", refer_table_name);
    MetaTable *meta_table = table->meta_table;

    int i;
    for(i = 0; i < meta_table->column_size; i++) {
        MetaColumn *current_meta_column = meta_table->meta_column[i];
        if (current_meta_column->column_type == T_REFERENCE && strcmp(current_meta_column->table_name, refer_table_name) == 0)
            return true;
    }

    return false;
}

/* Check if refer equals. */
bool refer_equals(Refer *refer1, Refer *refer2) {
    return streq(refer1->table_name, refer2->table_name)
            && refer1->page_num == refer2->page_num 
            && refer1->cell_num == refer2->cell_num;
}

/* Check if cursor equals. */
bool cursor_equals(Cursor *cursor1, Cursor * cursor2) {
    return streq(cursor1->table->meta_table->table_name, cursor2->table->meta_table->table_name)
            && cursor1->page_num == cursor2->page_num 
            && cursor1->cell_num == cursor2->cell_num;
}

/* Update row key value. */
static void update_key_value_refer(Row *row, MetaColumn *meta_column, Cursor *cursor, ReferUpdateEntity *refer_update_entity) {
    
    bool flag = false;
    for (uint32_t i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];
        if (key_value->data_type == T_REFERENCE 
            && strcmp(key_value->key, meta_column->column_name) == 0
            && refer_equals(key_value->value, refer_update_entity->old_refer)) {
                /* Check if refer equals. */
                key_value->value = copy_refer(refer_update_entity->new_refer);
                flag = true;
        }
    }
    if (flag)
        update_row_data(row, cursor);
}


/* Update row refer. */
static void update_row_refer(Row *row, SelectResult *select_result, Table *table, void *arg) {

    assert_not_null(arg, "Illegal parameter input at <update_row_refer>");

    /* ReferUpdateEntity */
    ReferUpdateEntity *refer_update_entity = (ReferUpdateEntity *) arg;

    /* Curosr */
    Cursor *cursor = define_cursor(table, row->key);

    /* MetaTable */
    MetaTable *meta_table = table->meta_table;

    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (meta_column->column_type == T_REFERENCE && strcmp(meta_column->table_name, refer_update_entity->old_refer->table_name) == 0) {
            update_key_value_refer(row, meta_column, cursor, refer_update_entity);
        }
    }
}

/* Update table refer. */
static void update_table_refer(char *table_name, ReferUpdateEntity *refer_update_entity) {

    Table *table = open_table(table_name);

    /* Query with condition, and delete satisfied condition row. */
    SelectResult *select_result = new_select_result(table_name);

    /* Traverse rows to update refer. */
    query_with_condition(NULL, select_result, update_row_refer, refer_update_entity);
    
    free_select_result(select_result);
}


/* Update Refer 
 * When referenct target be changed (updated or deleted), 
 * must to update row reference value which pointer to it. */
void update_refer(char *table_name, int32_t old_page_num, int32_t old_cell_num, 
                  int32_t new_page_num, int32_t new_cell_num) {
   
    Refer *old_one = new_refer(table_name, old_page_num, old_cell_num);
    Refer *new_one = new_refer(table_name, new_page_num, new_cell_num);
    ReferUpdateEntity *refer_update_entity = new_refer_update_entity(old_one, new_one);
    
    TableList *table_list = get_table_list();

    /* Update table refer. */
    uint32_t i;
    for (i = 0; i < table_list->count; i++) {
        char *curent_table_name = table_list->table_name_list[i];
        if (if_table_refer_to(curent_table_name, table_name)) 
            update_table_refer(curent_table_name, refer_update_entity);
    }

    /* Update Xlog. */
    update_xlog_entry_refer(refer_update_entity);

    /* Free memory. */
    free_refer_update_entity(refer_update_entity);
}
