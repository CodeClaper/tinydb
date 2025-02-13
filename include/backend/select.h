#include "data.h"

typedef enum ROW_HANDLER_ARG_TYPE {
    ARG_NULL = 1,
    ARG_LIMIT_CLAUSE_NODE,
    ARG_ASSIGNMENT_LIST,
    ARG_REFER_UPDATE_ENTITY
} ROW_HANDLER_ARG_TYPE;

/* Function pointer about row handler */
typedef void (*ROW_HANDLER)(Row *, SelectResult *select_result, Table *table, ROW_HANDLER_ARG_TYPE type,void *arg);


/* Count number of row, used in the sql function count() */
void count_row(Row *row, SelectResult *select_result, Table *table, ROW_HANDLER_ARG_TYPE type, void *arg);


/* Select row data. */
void select_row(Row *row, SelectResult *select_result, Table *table, ROW_HANDLER_ARG_TYPE type, void *arg);


/* Define row by refer. 
 * Return row not matter if it is deleted.
 * */
Row *define_row(Refer *refer);

/* Define row by refer. 
 * Return undelted row, return NULL if deleted.
 * */
Row *define_visible_row(Refer *refer);


/* Query with condition. */
void query_with_condition(ConditionNode *condition, SelectResult *select_result, ROW_HANDLER row_handler, ROW_HANDLER_ARG_TYPE type, void *arg);


/* Execute select statement. */
void exec_select_statement(SelectNode *select_node, DBResult *result);

