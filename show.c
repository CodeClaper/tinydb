#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "output.h"
#include "misc.h"
#include "utils.h"
#include "show.h"

// gen table list.
TableList *gen_table_list() {
    DIR *dir;
    struct dirent *entry;
    TableList *table_list = malloc(sizeof(TableList));
    if (table_list == NULL)
       MALLOC_ERROR;
    table_list->table_name_list = malloc(0);
    table_list->count = 0;
    if ((dir = opendir(data_dir)) ==NULL) {
        fatals("System error, not found '%d' dir", data_dir); 
    } else {
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
void print_show_table(TableList *table_list, Output *out) {
    uint32_t i;
    print_data(out, strdup("["));
    for (i = 0; i < table_list->count; i++) {
        char *table_name = *(table_list->table_name_list + i);
        print_data_s(out, "\"%s\"", table_name);
        if (i < table_list->count -1)
            print_data(out, strdup(", "));
    } 
    print_data(out, strdup("]"));
}

