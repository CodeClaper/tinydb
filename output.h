#include "data.h"

//Get key value pair string.
char *get_key_value_pair_str(char *key, void *value, DataType data_type);

//Print out
void print_out(Output *out, char *word, uint32_t *buff_size);

//Genetate output.
void put_select_result(Output *out_put, SelectResult *select_result, QueryParam *query_param);
