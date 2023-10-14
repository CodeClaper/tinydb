#include "data.h"
#include "defs.h"
#include <dirent.h>
#include <stdio.h>

typedef struct {
    char **table_name_list;
    uint32_t count;
}TableList;

// gen table list.
TableList *gen_table_list();

// print show table.
void print_show_table(TableList *table_list, Output *out);
