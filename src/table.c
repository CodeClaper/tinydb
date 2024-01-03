#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "table.h"
#include "mmu.h"
#include "cache.h"
#include "common.h"
#include "asserts.h"
#include "utils.h"
#include "meta.h"
#include "misc.h"
#include "node.h"
#include "pager.h"
#include "log.h"
#include "index.h"
#include "ret.h"

/* Get table list. */
TableList *get_table_list() {

    TableList *table_list = db_malloc2(sizeof(TableList), "TableList");
    table_list->count = 0;
    table_list->table_name_list = db_malloc2(0, "table_list.table_name_list");

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(conf->data_dir)) ==NULL) 
        fatals("System error, not found directory: ", conf->data_dir); 
    else {
        while((entry = readdir(dir)) != NULL) {
            if (entry->d_type == 8 && endwith(entry->d_name, ".dbt")) {
                table_list->table_name_list[table_list->count] = replace(entry->d_name, ".dbt", "");
                table_list->count++;
            }
        }
        closedir(dir);
    }
    return table_list;
}

/* Get table file path. */
static char *table_file_path(char *table_name) {
    if (table_name == NULL) {
        fprintf(stderr, "Inner error, table name can`t be NULL.\n");
        exit(EXIT_FAILURE);
    }
    int len = strlen(conf->data_dir) + strlen(table_name) + strlen(".dbt") + 1;
    char *file_path = db_malloc2(len, "String value");
    sprintf(file_path, "%s%s%s", conf->data_dir, table_name, ".dbt");
    return file_path;
}

/* Check table file if exist 
 * Return true if exist or false if not exist. */
static bool table_file_exist(char *table_file_path) {
    struct stat buffer;
    return (stat(table_file_path, &buffer) == 0);
}

/* Check if table exists. */
bool check_table_exist(char *table_name) {
    char *file_path = table_file_path(table_name);
    bool ret = table_file_exist(file_path);
    db_free(file_path);
    return ret;
}

/* Create a new table. */
void create_table(MetaTable *meta_table, DBResult *result) {
    if (meta_table == NULL) {
        error_result(result, EXECUTE_TABLE_CREATE_FAIL, "Try to create table fail.");
        return;
    }
    char *file_path = table_file_path(meta_table->table_name);
    if (table_file_exist(file_path)) {
        error_result(result, EXECUTE_TABLE_CREATE_FAIL, "Table '%s' already exists. \n", meta_table->table_name);
        return;
    }
    int descr = open(file_path, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
    if (descr == -1) {
        error_result(result, EXECUTE_OPEN_DATABASE_FAIL, "Open database file '%s' fail.\n", file_path);
        return;
    }
    void *root_node = db_malloc2(PAGE_SIZE, "PAGE NODE");

    /* initialize root node */
    initial_leaf_node(root_node, true);

    /* set meta column */
    set_column_size(root_node, meta_table->column_size);
    
    /* assignment */
    int i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = (MetaColumn *)(meta_table->meta_column[i]);
        void *destination = serialize_meta_column(meta_column);
        set_meta_column(root_node, destination, i);
    }

    /* flush to disk. */
    lseek(descr, 0, SEEK_SET);
    ssize_t w_size = write(descr, root_node, PAGE_SIZE);
    if (w_size == -1) {
        error_result(result, EXECUTE_RW_DATABASE_FAIL, "Write table meta info error and errno %d.\n", errno);
        return;
    }
    
    /* close desription. */
    close(descr);

    /* free memory*/
    db_free(file_path);
    db_free(root_node);

    success_result(result, "Table '%s' created successfully.", meta_table->table_name);
}

/* Open a table file. */
Table *open_table(char *table_name) {

    /* Check valid. */
    assert_not_null(table_name, "Table name must be supported.\n");

    /* Firstly try to get in cache. */
    Table *cache_table = find_cache_table(table_name);
    if (cache_table)
        return cache_table;

    /* Cache missing, get from disk. */
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
        db_free(file_path);
        return NULL;
    }
    Table *table = db_malloc2(sizeof(Table), "Table");
    Pager *pager = open_pager(file_path);
    if (pager == NULL) 
        return NULL;
    table->pager = pager;
    table->root_page_num = 0; // Define root page is first page.
    if (pager->size == 0) {
        // New db file and initialize page 0 as leaf node.
        void *root_node = get_page(pager, 0);
        initial_leaf_node(root_node, true);
    }
    table->meta_table = get_meta_table(table, table_name);
    add_cache_table(table); /* add cache */
    db_free(file_path);
    return table;
}

/* Define cursor when meet leaf node. */
static Cursor *define_cursor_leaf_node(Table *table, void *leaf_node, uint32_t page_num, void *key) {
    Cursor *cursor = db_malloc2(sizeof(Cursor), "Cursor");
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
    void *child_node = get_page(table->pager, child_page_num);
    
    switch(get_node_type(child_node)) {
        case LEAF_NODE:
            return define_cursor_leaf_node(table, child_node, child_page_num, key);
        case INTERNAL_NODE:
            return define_cursor_internal_node(table, child_node, key);
    }
}

/* Define cursor. */
Cursor *define_cursor(Table *table, void *key) {
    void *root_node = get_page(table->pager, table->root_page_num);
    switch(get_node_type(root_node)) {
        case LEAF_NODE:
            return define_cursor_leaf_node(table, root_node, table->root_page_num, key);
        case INTERNAL_NODE:
            return define_cursor_internal_node(table, root_node, key);
    }
}

/* Delete an existed table. */
void drop_table(char *table_name, DBResult *result) {
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
        error_result(result, EXECUTE_TABLE_NOT_EXIST_FAIL, stderr, "Table '%s' not exists. \n", table_name);
        db_free(file_path);
        return;
    }
    if (remove(file_path) == 0) {
        success_result(result, "Table '%s' deleted success.\n", table_name);
        db_free(file_path);
        return;
    }
    error_result(result, EXECUTE_TABLE_DROP_FAIL, "Table '%s' deleted fail, error : %d", table_name, errno);
    db_free(file_path);
}
