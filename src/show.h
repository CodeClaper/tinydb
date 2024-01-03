#include <dirent.h>
#include <stdio.h>
#include "data.h"
#include "defs.h"

/* Get table list. */
TableList *get_table_list();

/* Execute show statement.*/
void exec_show_statement(ShowNode *show_node, DBResult *result);
