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
#include "free.h"
#include "cache.h"
#include "buffer.h"
#include "common.h"
#include "asserts.h"
#include "utils.h"
#include "meta.h"
#include "ltree.h"
#include "pager.h"
#include "log.h"
#include "tablelock.h"
#include "index.h"

/* Get table list. */
List *get_table_list() {

    List *list = create_list(NODE_STRING);

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(conf->data_dir)) == NULL) {
        db_log(PANIC, "System error, not found directory: ", conf->data_dir); 
    }
    else {
        while((entry = readdir(dir)) != NULL) {
            if (entry->d_type == 8 && endwith(entry->d_name, ".dbt")) {
                append_list(list, replace_once(entry->d_name, ".dbt", ""));
            }
        }
        closedir(dir);
    }
    return list;
}

/* Get table file path. */
char *table_file_path(char *table_name) {
    if (table_name == NULL) {
        fprintf(stderr, "Inner error, table name can`t be NULL.\n");
        exit(EXIT_FAILURE);
    }
    int len = strlen(conf->data_dir) + strlen(table_name) + strlen(".dbt") + 1;
    char *file_path = db_malloc(len, "string");
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
bool create_table(MetaTable *meta_table) {
    if (meta_table == NULL) {
        db_log(ERROR, "Try to create table fail.");
        return false;
    }
    char *file_path = table_file_path(meta_table->table_name);
    if (table_file_exist(file_path)) {
        db_log(ERROR, "Table '%s' already exists. \n", meta_table->table_name);
        db_free(file_path);
        return false;
    }
    int descr = open(file_path, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
    if (descr == -1) {
        db_log(ERROR, "Open database file '%s' fail.\n", file_path);
        db_free(file_path);
        return false;
    }
    void *root_node = db_malloc(PAGE_SIZE, "pointer");

    uint32_t default_value_len = calc_table_row_length2(meta_table);

    /* Initialize root node */
    initial_leaf_node(root_node, default_value_len, true);

    /* Set meta column */
    set_column_size(root_node, meta_table->all_column_size);
    
    /* Get default value cell. */
    void *default_value_dest = get_default_value_cell(root_node);

    /* Serialize */
    uint32_t offset = 0;
    uint32_t i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = (MetaColumn *)(meta_table->meta_column[i]);
        void *destination = serialize_meta_column(meta_column);
        set_meta_column(root_node, destination, i);
        if (meta_column->default_value_type == DEFAULT_VALUE)
            memcpy(default_value_dest + offset, meta_column->default_value, meta_column->column_length);
        else
            memset(default_value_dest + offset, 0, meta_column->column_length);
        offset += meta_column->column_length;
    }

    /* Flush to disk. */
    lseek(descr, 0, SEEK_SET);
    ssize_t w_size = write(descr, root_node, PAGE_SIZE);
    if (w_size == -1) {
        db_log(ERROR, "Write table meta info error and errno %d.\n", errno);
        db_free(file_path);
        db_free(root_node);
        return false;
    }
    
    /* Close desription. */
    close(descr);

    /* Free memory. */
    db_free(file_path);
    db_free(root_node);

    return true;
}

/* Get Column Position. */
static int get_column_position(MetaTable *meta_table, ColumnPositionDef *pos) {
    
    /* If not ColumnPositionDef, append column at last. */
    if (is_null(pos))
        return meta_table->column_size;

    int i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *current = meta_table->meta_column[i];
        if (streq(current->column_name, pos->column)) {
            switch (pos->type) {
                case POS_BEFORE:
                    return i;
                case POS_AFTER:
                    return i + 1;
            }
        }
    }
    db_log(ERROR, "Column '%s' not exists in table '%s'.", pos->column, meta_table->table_name);
    return -1;
}

/* Add new MetaColumn to table.
 * This function is actually bottom-level routine for alter-table-add-column action.
 * */
bool add_new_meta_column(char *table_name, MetaColumn *new_meta_column, ColumnPositionDef *pos) {
    Table *table = open_table(table_name);
    MetaTable *meta_table = table->meta_table;
    int index = get_column_position(meta_table, pos);
    append_new_column(table->root_page_num, table, new_meta_column, index);
    flush(table_name);
    return true;
}

/* Open a table file. 
 * Return Table or NULL if not exists. */
Table *open_table(char *table_name) {

    /* Check valid. */
    Assert(table_name);

    /* Check table if locked, if locked, block here until acquire the table. */
    check_table_locked(table_name);

    /* Firstly, try to find in buffer. */
    Table *mtable = find_table_buffer(table_name);
    if (mtable)
        return mtable;

    /* Memory missing, get from disk. */
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
        db_free(file_path);
        return NULL;
    }
    
    /* Combine table. */
    Table *table = instance(Table);
    Pager *pager = open_pager(file_path);
    if (pager == NULL) {
        free_table(table);
        db_free(file_path);
        return NULL;
    }

    /* Define root page is first page. */
    table->root_page_num = 0; 
    table->pager = pager;

    table->meta_table = gen_meta_table(table, table_name);

    if (pager->size == 0) {
        /* New db file and initialize page 0 as leaf node. */
        void *root_node = get_page(table_name, pager, 0);
        uint32_t value_len = calc_table_row_length(table);
        initial_leaf_node(root_node, value_len, true);
    }


    /* Save table cache. */
    save_table_cache(table);
    
    /* Free memory. */
    db_free(file_path);

    /* Only return buffer table to keep same table pointer in same thread. */
    return find_table_buffer(table_name);
}


/* Drop an existed table. */
bool drop_table(char *table_name) {

    /* Check if exist the table. */
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
        db_free(file_path);
        return false;
    }

    /* Disk remove. */
    if (remove(file_path) == 0) {
        db_free(file_path);
        /* Remove table cache. */
        remove_table_cache(table_name);
        /* Remove table buffer. */
        remove_table_buffer(table_name);
        return true;
    }

    db_free(file_path);
    db_log(ERROR, "Table '%s' deleted fail, error : %d", table_name, errno);

    return false;
}
