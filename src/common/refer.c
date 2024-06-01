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
#include <stdio.h>
#include <time.h>
#include "refer.h"
#include "data.h"
#include "table.h"
#include "mmu.h"
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

typedef struct {
    uint32_t size;
    Refer **list;
} UpdateReferLockContent;

static UpdateReferLockContent *update_refer_lock_content;

/* Check if a refer include in ReferUpdateEntity. */
static bool include_update_refer_lock(Refer *refer);

/* Init Refer. */
void init_refer() {
    update_refer_lock_content = instance(UpdateReferLockContent);
    update_refer_lock_content->list = db_malloc(0, "pointer");
    update_refer_lock_content->size = 0;
}

/* Add Refer to UpdateReferLockContent. */
void add_refer_update_lock(Refer *refer) {
    if (!include_update_refer_lock(refer)) {
        update_refer_lock_content->list = db_realloc(update_refer_lock_content->list, sizeof(Refer *) * (update_refer_lock_content->size + 1));
        update_refer_lock_content->list[update_refer_lock_content->size++] = copy_refer(refer);
    }
}

/* Free refer in UpdateReferLockContent. */
void free_refer_update_lock(Refer *refer) {
    Assert(update_refer_lock_content);
    uint32_t i, j;
    for (i = 0; i < update_refer_lock_content->size; i++) {
        Refer *current = update_refer_lock_content->list[i];
        if (refer_equals(refer, current)) {
            for (j = i; j < update_refer_lock_content->size; j++) {
                memcpy(update_refer_lock_content->list + j, update_refer_lock_content->list + j + 1, sizeof(Refer *));
            }
            memset(update_refer_lock_content->list + j, 0, sizeof(Refer *));

            free_refer(current);

            update_refer_lock_content->size--;
            update_refer_lock_content->list = db_realloc(update_refer_lock_content->list, sizeof(Refer *) * update_refer_lock_content->size);
            break;
        }
    }
}

/* Check if a refer include in ReferUpdateEntity. */
static bool include_update_refer_lock(Refer *refer) {
    Assert(update_refer_lock_content);
    uint32_t i;
    for (i = 0; i < update_refer_lock_content->size; i++) {
        Refer *current = update_refer_lock_content->list[i];
        if (refer_equals(refer, current))
            return true;
    }
    return false;
}

/* Generate new Refer. 
 * Note: if page_num is -1 and cell_num is -1 which means refer null. */
Refer *new_refer(char *table_name, int32_t page_num, int32_t cell_num) {
    Refer *refer = instance(Refer);
    strcpy(refer->table_name, table_name);
    refer->page_num = page_num;
    refer->cell_num = cell_num;
    return refer;
}

/* Generate new cursor. */
Cursor *new_cursor(Table *table, uint32_t page_num, uint32_t cell_num) {
    Cursor *cursor = instance(Cursor);
    cursor->table = table;
    cursor->page_num = page_num;
    cursor->cell_num = cell_num;
    return cursor;
}


/* Define cursor when meet leaf node. */
static Cursor *define_cursor_leaf_node(Table *table, void *leaf_node, uint32_t page_num, void *key) {
    Cursor *cursor = instance(Cursor);
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
    uint32_t keys_num = get_internal_node_keys_num(internal_node);
    uint32_t key_len = calc_primary_key_length(table);
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    uint32_t child_page_num = get_internal_node_cell_child_page_num(internal_node, key, keys_num, key_len, primary_meta_column->column_type);
    void *child_node = get_page(table->meta_table->table_name, table->pager, child_page_num);
    
    NodeType node_type = get_node_type(child_node);
    switch(node_type) {
        case LEAF_NODE:
            return define_cursor_leaf_node(table, child_node, child_page_num, key);
        case INTERNAL_NODE:
            return define_cursor_internal_node(table, child_node, key);
        default:
            UNEXPECTED_VALUE(node_type);
            return NULL;
    }
}

/* Define Cursor. */
Cursor *define_cursor(Table *table, void *key) {
    assert_not_null(key, "Input key can`t be NULL");
    void *root_node = get_page(table->meta_table->table_name, table->pager, table->root_page_num);
    NodeType node_type = get_node_type(root_node);
    switch(node_type) {
        case LEAF_NODE:
            return define_cursor_leaf_node(table, root_node, table->root_page_num, key);
        case INTERNAL_NODE:
            return define_cursor_internal_node(table, root_node, key);
        default:
            UNEXPECTED_VALUE(node_type);
            return NULL;
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

    /* Make a new SelectResult. */
    SelectResult *select_result = new_select_result(meta_column->table_name);

    query_with_condition(condition_node, select_result, select_row, NULL);

    Refer *refer = NULL;
    uint32_t row_size = len_list(select_result->rows);
    if (row_size > 1) {
        db_log(ERROR, "Expected to one reference, but found %d, maybe you can use 'in' as for array.", select_result->row_size);
        return NULL;
    }
    else if (row_size == 1) {
        /* Take the first row as refered. Maybe row size should be one, but now there is no check. */
        Row *row = lfirst(first_cell(select_result->rows));
        refer = define_refer(row);
    }
    free_select_result(select_result);

    return refer;
}

/* Check if refer null. 
 * If page number is -1 and cell number is -1, it means refer null. */
bool refer_null(Refer *refer) {
    return refer->page_num == -1 
        && refer->cell_num == -1;
}

/* Make a NULL Refer. */
Refer *make_null_refer() {
    Refer *refer = instance(Refer);
    refer->page_num = -1;
    refer->cell_num = -1;
    return refer;
}

/* Generate new ReferUpdateEntity. */
ReferUpdateEntity *new_refer_update_entity(Refer *old_refer, Refer *new_refer) {
    ReferUpdateEntity *refer_update_entity = instance(ReferUpdateEntity);
    refer_update_entity->old_refer = old_refer;
    refer_update_entity->new_refer = new_refer;
    return refer_update_entity;
}

/* Convert to refer from cursor. */
Refer *convert_refer(Cursor *cursor) {
    if (cursor == NULL) 
        return NULL;

    /* Generate new refer. */
    Refer *refer = instance(Refer);
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
static bool if_related_table(char *table_name, char *refer_table_name) {
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

/* Update single key value refer. */
static bool update_single_key_value_refer(KeyValue *key_value, ReferUpdateEntity *refer_update_entity) {
    if (refer_equals(key_value->value, refer_update_entity->old_refer)) {
        free_refer(key_value->value);
        key_value->value = copy_refer(refer_update_entity->new_refer);
        return true;
    }
    return false;
}

/* Update array key value refer. */
static bool update_array_key_value_refer(KeyValue *key_value, ReferUpdateEntity *refer_update_entity) {
    ArrayValue *array_value = (ArrayValue *)key_value->value;
    bool flag = false;
    uint32_t i;
    for (i = 0; i < array_value->size; i++) {
        if (refer_equals(array_value->set[i], refer_update_entity->old_refer)) {
            free_refer(array_value->set[i]);
            array_value->set[i] = copy_refer(refer_update_entity->new_refer);
            flag = true;
        }
    }
    return flag;
}

/* Update row key value. */
static void update_key_value_refer(Row *row, MetaColumn *meta_column, Cursor *cursor, ReferUpdateEntity *refer_update_entity) {
    
    bool flag = false;

    ListCell *lc;
    foreach (lc, row->data) {
        KeyValue *key_value = lfirst(lc);
        if (key_value->data_type == T_REFERENCE 
            && streq(key_value->key, meta_column->column_name)) {
                if (key_value->is_array) {
                    if (update_array_key_value_refer(key_value, refer_update_entity))
                        flag = true;
                } else {
                    if (update_single_key_value_refer(key_value, refer_update_entity))
                        flag = true;
                }
        }
    }
    
    /* If satisfied above conditions, update the row. */
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

    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (meta_column->column_type == T_REFERENCE 
            && streq(meta_column->table_name, refer_update_entity->old_refer->table_name)) 
                update_key_value_refer(row, meta_column, cursor, refer_update_entity);
    }
}

/* Update table refer. */
static void update_table_refer(char *table_name, ReferUpdateEntity *refer_update_entity) {

    /* Skip update locked refer. */
    if (include_update_refer_lock(refer_update_entity->old_refer))
        return;

    /* Query with condition, and delete satisfied condition row. */
    SelectResult *select_result = new_select_result(table_name);

    /* Traverse rows to update refer. */
    query_with_condition(NULL, select_result, update_row_refer, refer_update_entity);
    
    free_select_result(select_result);
}

/* Update releated tables reference. */
void update_related_tables_refer(ReferUpdateEntity *refer_update_entity) {

    List *table_list = get_table_list();
    /* Update table refer. */
    ListCell *lc;
    foreach (lc, table_list) {
        char *curent_table_name = lfirst(lc);
        if (if_related_table(curent_table_name, refer_update_entity->old_refer->table_name)) 
            update_table_refer(curent_table_name, refer_update_entity);
    }

    free_list_deep(table_list);
}


/* Update Refer 
 * When referenct target be changed (updated or deleted), 
 * must to update row reference value which pointer to it. */
void update_refer(char *table_name, int32_t old_page_num, int32_t old_cell_num, 
                  int32_t new_page_num, int32_t new_cell_num) {
   
    Refer *old_one = new_refer(table_name, old_page_num, old_cell_num);
    Refer *new_one = new_refer(table_name, new_page_num, new_cell_num);
    ReferUpdateEntity *refer_update_entity = new_refer_update_entity(old_one, new_one);
   
    /* Update related tables. */
    update_related_tables_refer(refer_update_entity);

    /* Update Xlog. */
    update_xlog_entry_refer(refer_update_entity);

    /* Free memory. */
    free_refer_update_entity(refer_update_entity);
}
