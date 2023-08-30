#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "common.h"
#include "table.h"
#include "node.h"
#include "pager.h"
#include "misc.h"
#include "node.h"
#include "meta.h"

// Get table file path.
static char *table_file_path(char *table_name) {
#ifdef DEBUG
    printf("TABLE NAME: %s\n", table_name);
#endif
    if (table_name == NULL) {
        fprintf(stderr, "Inner error, table name can`t be NULL.\n");
        exit(EXIT_FAILURE);
    }
    int len = strlen(data_dir) + strlen(table_name) + strlen(".dbt") + 1;
    char *file_path = malloc(len);
    memset(file_path, 0, len);
    sprintf(file_path, "%s%s%s", data_dir, table_name, ".dbt");
    return file_path;
}

// Check table file if exist
// Return 1 if exist or 0 if not exist.
static int table_file_exist(char *table_file_path) {
  int exist_descr = open(table_file_path, O_RDONLY, S_IRUSR);
  close(exist_descr);
  return exist_descr > -1 ? 1 : 0;
}

// Create a new table.
ExecuteResult create_table(MetaTable *meta_table) {
  if (meta_table == NULL) {
     fprintf(stderr, "meta table can`t be NULL. \n");
     exit(EXIT_FAILURE);
  }
  char *file_path = table_file_path(meta_table->table_name);
  if (table_file_exist(file_path)) {
    fprintf(stderr, "Table '%s' already exists. \n", meta_table->table_name);
    return EXECUTE_TABLE_CREATE_FAIL;
  }
  int descr = open(file_path, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
  if (descr == -1) {
    fprintf(stderr, "Create table '%s' fail.\n", meta_table->table_name);
    return EXECUTE_TABLE_CREATE_FAIL;
  }
  void *root_node = malloc(PAGE_SIZE);
  if (root_node == NULL)
        MALLOC_ERROR;
  memset(root_node, 0, PAGE_SIZE);
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
      fatald("Write table meta info error and errno", errno);
  }
  free(file_path);
  close(descr);
  printf("Table '%s' created success.\n", meta_table->table_name);
  for (uint32_t i = 0; i < meta_table->column_size; i++) {
    free(meta_table->meta_column[i]);
  }
  free(meta_table);
  free(root_node);
  return EXECUTE_SUCCESS;
}

// Open a table file.
Table *open_table(char *table_name) {
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
        fprintf(stderr, "Table '%s' not exists. \n", table_name);
        return NULL;
    }
    Table *table = malloc(sizeof(Table));
    if (NULL == table) {
        table = malloc(sizeof(Table));
        if (NULL == table)
          MALLOC_ERROR;
    }
    Pager *pager = open_pager(file_path);
    if (NULL == pager) {
        return NULL; 
    }
    table->pager = pager;
    table->root_page_num = 0; // Define root page is first page.
    if (pager->num_page == 0) {
        // New db file and initialize page 0 as leaf node.
        void *root_node = get_page(pager, 0);
        initial_leaf_node(root_node, true); 
    }
    table->meta_table = get_meta_table(table, table_name);
    free(file_path);
    return table;
}

static Cursor *define_cursor_leaf_node(Table *table, void *leaf_node, uint32_t page_num, uint32_t key) {
    Cursor *cursor = malloc(sizeof(Cursor));
    if (NULL == cursor)
        MALLOC_ERROR;
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);
    uint32_t row_length = calc_table_row_length(table);
    cursor->table = table;
    cursor->page_num = page_num;
    cursor->cell_num = get_leaf_node_cell_index(leaf_node, key, cell_num, row_length); 
    return cursor;
}

static Cursor *deine_cursor_internal_node(Table *table, void *internal_node, uint32_t key) {
    uint keys_num = get_internal_node_keys_num(internal_node);
    uint child_page_num = get_internal_node_cell_child_page_num(internal_node, key, keys_num);
    void *child_node = get_page(table->pager, child_page_num);
    if (get_node_type(child_node) == LEAF_NODE) {
        return define_cursor_leaf_node(table, child_node, child_page_num, key);
    } else {
        return deine_cursor_internal_node(table, child_node, key);
    }
}

// Deine cursor throngth table and key
// Cursor can help us quickly find table、page、row
Cursor *define_cursor(Table *table, uint32_t key) {
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
  free(file_path);
  fprintf(stderr, "Table '%s' deleted fail, error : %d", table_name, errno);
  return EXECUTE_TABLE_DROP_FAIL;
}
