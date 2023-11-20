#include "data.h"

// get data type name.
char *data_type_name(DataType data_type);

/*Get key value pair string.*/
char *get_key_value_pair_str(char *key, void *value, DataType data_type);

// column type length
uint32_t column_type_length(DataType column_type);

// calculate the length of table row
uint32_t calc_table_row_length(Table *table);

//calculate primary key lenght. if not exist primary key , return -1;
uint32_t calc_primary_key_length(Table *table);

// get table meta info
MetaTable *get_meta_table(Table *table, char *table_name);

// get meta column info by column name.
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name);
