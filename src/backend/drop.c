#include "data.h"
#include "check.h"
#include "table.h"
#include "log.h"
#include "utils.h"

/* Execute drop table statment.*/
void exec_drop_table_statement(char *table_name, DBResult *result) { 
    if (check_drop_table(table_name) && drop_table(table_name)) {
        result->success = true;
        result->rows = 0;
        result->message = format("Table '%s' droped successfully.", table_name);
        db_log(SUCCESS, "Table '%s' droped successfully.", table_name);
    }
}
