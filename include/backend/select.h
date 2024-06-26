#include "data.h"

/* Function pointer about row handler */
typedef void (*ROW_HANDLER)(Row *, SelectResult *select_result, Table *table, void *arg);

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name);

/* Count number of row, used in the sql function count() */
void count_row(Row *row, SelectResult *select_result, Table *table, void *arg);

/* Select row data. */
void select_row(Row *row, SelectResult *select_result, Table *table, void *arg);

/* Define row by refer. 
 * Return row not matter if it is deleted.
 * */
Row *define_row(Refer *refer);

/* Define row by refer. 
 * Return undelted row, return NULL if deleted.
 * */
Row *define_visible_row(Refer *refer);

/* Query with condition. */
void query_with_condition(ConditionNode *condition, SelectResult *select_result, ROW_HANDLER row_handler, void *arg);


/* Execute select statement. */
void exec_select_statement(SelectNode *select_node, DBResult *result);

