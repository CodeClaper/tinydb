#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "table.h"
#include "mem.h"
#include "cache.h"
#include "common.h"
#include "meta.h"
#include "misc.h"
#include "node.h"
#include "pager.h"
#include "log.h"
#include "index.h"

// Get table file path.
static char *table_file_path(char *table_name) {
  if (table_name == NULL) {
        fprintf(stderr, "Inner error, table name can`t be NULL.\n");
        exit(EXIT_FAILURE);
  }
  int len = strlen(data_dir) + strlen(table_name) + strlen(".dbt") + 1;
  char *file_path = db_malloc2(len, "String value");
  sprintf(file_path, "%s%s%s", data_dir, table_name, ".dbt");
  return file_path;
}

// Check table file if exist
// Return true if exist or false if not exist.
static bool table_file_exist(char *table_file_path) {
  struct stat buffer;
  return (stat(table_file_path, &buffer) == 0);
}

// Create a new table.
ExecuteResult create_table(MetaTable *meta_table) {
    if (meta_table == NULL)
        return EXECUTE_TABLE_CREATE_FAIL;
    char *file_path = table_file_path(meta_table->table_name);
    if (table_file_exist(file_path)) {
        log_error_s("Table '%s' already exists. \n", meta_table->table_name);
        return EXECUTE_TABLE_CREATE_FAIL;
    }
    int descr = open(file_path, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
    if (descr == -1) {
        log_error_s("Open database file '%s' fail.\n", file_path);
        return EXECUTE_TABLE_CREATE_FAIL;
    }
    void *root_node = db_malloc2(PAGE_SIZE, "PAGE NODE");
    // initialize root node
    initial_leaf_node(root_node, true);
    // set meta column
    set_column_size(root_node, meta_table->column_size);
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = (MetaColumn *)(meta_table->meta_column[i]);
        void *destination = serialize_meta_column(meta_column);
        set_meta_column(root_node, destination, i);
    }
    lseek(descr, 0, SEEK_SET);
    ssize_t w_size = write(descr, root_node, PAGE_SIZE);
    if (w_size == -1) {
        log_error_d("Write table meta info error and errno %d", errno);
        return EXECUTE_TABLE_CREATE_FAIL;
    }
    db_free(file_path);
    close(descr);
    db_free(root_node);
    return EXECUTE_SUCCESS;
}

// Open a table file.
Table *open_table(char *table_name) {
    Table *cache_table = find_cache_table(table_name);
    if (cache_table)
          return cache_table;
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
          log_error_s( "Table '%s' not exists.", table_name);
          db_free(file_path);
          return NULL;
    }
    Table *table = db_malloc2(sizeof(Table), "Table");
    Pager *pager = open_pager(file_path);
    if (NULL == pager) 
          return NULL;
    table->pager = pager;
    table->root_page_num = 0; // Define root page is first page.
    if (pager->num_page == 0) {
        // New db file and initialize page 0 as leaf node.
        void *root_node = get_page(pager, 0);
        initial_leaf_node(root_node, true);
    }
    table->meta_table = get_meta_table(table, table_name);
    add_cache_table(table);
    db_free(file_path);
    return table;
}

static Cursor *define_cursor_leaf_node(Table *table, void *leaf_node,
                                       uint32_t page_num, void *key) {
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

static Cursor *deine_cursor_internal_node(Table *table, void *internal_node, void *key) {
  uint keys_num = get_internal_node_keys_num(internal_node);
  uint32_t key_len = calc_primary_key_length(table);
  MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
  uint child_page_num = get_internal_node_cell_child_page_num(internal_node, key, keys_num, key_len, primary_meta_column->column_type);
  void *child_node = get_page(table->pager, child_page_num);
  if (get_node_type(child_node) == LEAF_NODE) {
    return define_cursor_leaf_node(table, child_node, child_page_num, key);
  } else {
    return deine_cursor_internal_node(table, child_node, key);
  }
}

// Deine cursor throngth table and key
// Cursor can help us quickly find table, page and row.
Cursor *define_cursor(Table *table, void *key) {
  void *root_node = get_page(table->pager, table->root_page_num);
  if (get_node_type(root_node) == LEAF_NODE) {
    // it means only root node as leaf node
    return define_cursor_leaf_node(table, root_node, table->root_page_num, key);
  } else {
    // it means root node as internal node
    return deine_cursor_internal_node(table, root_node, key);
  }
}

// Delete an existed table.
ExecuteResult drop_table(char *table_name) {
  char *file_path = table_file_path(table_name);
  if (!table_file_exist(file_path)) {
        fprintf(stderr, "Table '%s' not exists. \n", table_name);
        return EXECUTE_TABLE_DROP_FAIL;
  }
  if (remove(file_path) == 0) {
        printf("Table '%s' deleted success.\n", table_name);
        return EXECUTE_SUCCESS;
  }
  db_free(file_path);
  fprintf(stderr, "Table '%s' deleted fail, error : %d", table_name, errno);
  return EXECUTE_TABLE_DROP_FAIL;
}
