#include "data.h"

/* Function pointer about row handler */
typedef void (*ROW_HANDLER)(Row *, SelectResult *select_result, Table *table, void *arg);

/* Generate new select result structure. */
SelectResult *new_select_result(char *table_name);

/* Count number of row, used in the sql function count(1) */
void count_row(Row *row, SelectResult *select_result, Table *table, void *arg);

/* Define row by refer. */
Row *define_row(Refer *refer);

/* Query with condition. */
void query_with_condition(QueryParam *query_param, SelectResult *select_result, ROW_HANDLER row_handler, void *arg);

/* Get value from value item node. */
void *get_value_from_value_item_node(ValueItemNode *value_item_node, DataType meta_data_type);

/* Execute select statement. */
ExecuteResult exec_select_statement(SelectNode *select_node);

