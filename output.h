#include "data.h"

//Get key value pair string.
char *get_key_value_pair_str(char *key, void *value, DataType data_type);

//Print out data
void print_data(Output *out, char *word);

//Print out data
void print_data_s(Output *out, char *format, char *value);

//Print out data
void print_data_d(Output *out, char *format, int value);

//Print out message
void print_message(Output *out, char *word);
