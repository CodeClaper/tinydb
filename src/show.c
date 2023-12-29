#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "show.h"
#include "mmu.h"
#include "common.h"
#include "misc.h"
#include "utils.h"
#include "mmu.h"
#include "free.h"
#include "session.h"

#define KB_THRESHOLD 1024
#define MB_THRESHOLD 1024 * KB_THRESHOLD
#define GB_THRESHOLD 1024 * MB_THRESHOLD


/*Gen table list.*/
static TableList *gen_table_list() {
    DIR *dir;
    struct dirent *entry;
    TableList *table_list = db_malloc(sizeof(TableList));
    table_list->table_name_list = db_malloc(0);
    table_list->count = 0;
    if ((dir = opendir(conf->data_dir)) ==NULL) 
        fatals("System error, not found directory: ", conf->data_dir); 
    else {
        while((entry = readdir(dir)) != NULL) {
            if (entry->d_type == 8 && strstr(entry->d_name, ".dbt") != NULL) {
                table_list->table_name_list = realloc(table_list->table_name_list, sizeof(char *) * (table_list->count + 1));
                char *table_name = replace(entry->d_name, ".dbt", "");
                *(table_list->table_name_list + table_list->count) = table_name;
                table_list->count++;
            }
        }
        closedir(dir);
    }
    return table_list;
}

// print show table.
static void print_show_table(TableList *table_list) {
    uint32_t i;
    db_send("[");
    for (i = 0; i < table_list->count; i++) {
        char *table_name = *(table_list->table_name_list + i);
        db_send("\"%s\"", table_name);
        if (i < table_list->count -1)
            db_send(", ");
    } 
    db_send("]\n");
}

/* Execute show statement. */
void exec_show_statement(ShowNode *show_node, DBResult *result) {
    switch(show_node->type) {
        case SHOW_TABLES: {
            TableList *table_list = gen_table_list();
            print_show_table(table_list);
            free_table_list(table_list);
            break;
        }
        case SHOW_MEMORY: {
            db_send("{\"used_memeory\": %ld, \"mtable_capacity\": %d, \"mentry_num\": %d}\n", 
                    db_memesize(), mtable_capacity(), mentry_num()); 
            break;
        }
    }
}

