#include "data.h"

// convert from select node to select param
QueryParam *convert_query_param(SelectNode *select_node);

// generate select reuslt.
SelectResult *gen_select_result(QueryParam *query_param);
//Get value from value item node.
void *get_value_from_value_item_node(ValueItemNode *value_item_node, DataType meta_data_type);

// print select result using beauty format.
void print_select_result_beauty(SelectResult *select_result);

// print select result using plain format.
void print_select_result_plain(SelectResult *select_result, QueryParam *query_param);

// print select result plain format.
void print_select_result_count(SelectResult *select_result);

//Genetate output.
void put_select_result(SelectResult *select_result, QueryParam *query_param, Output *out_put);

//Query with condition
SelectResult *query_with_condition(QueryParam *query_param);
