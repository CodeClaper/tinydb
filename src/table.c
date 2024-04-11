#include <stdbool.h>
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
#include "index.h"
#include "ret.h"
#include "check.h"

/* Get table list. */
TableList *get_table_list() {

    TableList *table_list = instance(TableList);
    table_list->count = 0;
    table_list->table_name_list = db_malloc(0, "pointer");

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(conf->data_dir)) == NULL) {
        db_log(PANIC, "System error, not found directory: ", conf->data_dir); 
    }
    else {
        while((entry = readdir(dir)) != NULL) {
            if (entry->d_type == 8 && endwith(entry->d_name, ".dbt")) {
                table_list->table_name_list = db_realloc(table_list->table_name_list, sizeof(char *) * (table_list->count + 1));
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
bool create_table(MetaTable *meta_table, DBResult *result) {
    if (meta_table == NULL) {
        db_log(ERROR, "Try to create table fail.");
        return false;
    }
    char *file_path = table_file_path(meta_table->table_name);
    if (table_file_exist(file_path)) {
        db_log(ERROR, "Table '%s' already exists. \n", meta_table->table_name);
        return false;
    }
    int descr = open(file_path, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
    if (descr == -1) {
        db_log(ERROR, "Open database file '%s' fail.\n", file_path);
        return false;
    }
    void *root_node = db_malloc(PAGE_SIZE, "pointer");

    /* initialize root node */
    initial_leaf_node(root_node, true);

    /* set meta column */
    set_column_size(root_node, meta_table->all_column_size);
    
    /* assignment */
    int i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = (MetaColumn *)(meta_table->meta_column[i]);
        void *destination = serialize_meta_column(meta_column);
        set_meta_column(root_node, destination, i);
    }

    /* flush to disk. */
    lseek(descr, 0, SEEK_SET);
    ssize_t w_size = write(descr, root_node, PAGE_SIZE);
    if (w_size == -1) {
        db_log(ERROR, "Write table meta info error and errno %d.\n", errno);
        return false;
    }
    
    /* close desription. */
    close(descr);

    /* free memory*/
    db_free(file_path);
    db_free(root_node);

    return true;
}

/* Open a table file. 
 * Return Table or NULL if not exists. */
Table *open_table(char *table_name) {

    /* Check valid. */
    if (table_name == NULL) {
        db_log(ERROR, "Table name must be supported.");
        return NULL;
    }

    /* Firstly, try to find in memory. */
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
    if (pager == NULL) 
        return NULL;
    table->pager = pager;

    /* Define root page is first page. */
    table->root_page_num = 0; 
    if (pager->size == 0) {
        /* New db file and initialize page 0 as leaf node. */
        void *root_node = get_page(table_name, pager, 0);
        initial_leaf_node(root_node, true);
    }

    table->meta_table = get_meta_table(table, table_name);

    /* Save table cache. */
    save_or_update_table_cache(table);
    
    /* Free memory. */
    db_free(file_path);

    /* Only return buffer table to keep same table pointer in same thread. */
    return find_table_buffer(table_name);
}


/* Drop an existed table. */
bool drop_table(char *table_name, DBResult *result) {
    /* Check if exist the table. */
    char *file_path = table_file_path(table_name);
    if (!table_file_exist(file_path)) {
        db_log(ERROR, "Table '%s' not exists.", table_name);
        db_free(file_path);
        return false;
    }
    /* Check if allowed to drop the table. */
    if (!check_drop_table(table_name))
        return false;

    /* Disk remove. */
    if (remove(file_path) == 0) {
        db_free(file_path);
        /* Remove table cache. */
        remove_table_cache(table_name);
        return true;
    }

    db_free(file_path);
    db_log(ERROR, "Table '%s' deleted fail, error : %d", table_name, errno);

    return false;
}
