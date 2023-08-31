#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "show.h"
#include "common.h"
#include "misc.h"
#include "utils.h"

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
#ifdef DEBUG
                printf("%s, on line: %d\n", table_name, __LINE__);
#endif
                *(table_list->table_name_list + table_list->count) = table_name;
                table_list->count++;
            }
        }
        closedir(dir);
    }
    return table_list;
}

// print show table.
void print_show_table(FILE *file, TableList *table_list) {
    uint32_t i;
    fprintf(file, "[");
    for (i = 0; i < table_list->count; i++) {
        char *table_name = *(table_list->table_name_list + i);
        fprintf(file, "\"%s\"", table_name);
        if (i < table_list->count -1)
            fprintf(file, ", ");
    } 
    fprintf(file, "]\n");
}

