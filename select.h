#include "data.h"

// convert from select node to select param
QueryParam *convert_query_param(SelectNode *select_node);

// generate select reuslt.
SelectResult *gen_select_result(QueryParam *query_param);

// print select result using beauty format.
void print_select_result_beauty(SelectResult *select_result);

// print select result using plain format.
void print_select_result_plain(SelectResult *select_result, QueryParam *query_param);

// print select result plain format.
void print_select_result_count(SelectResult *select_result);
