#include "data.h"

/* Get data type name. */
char *data_type_name(DataType data_type);

/*Get key value pair string. */
char *get_key_value_pair_str(char *key, void *value, DataType data_type);

/* Default data length. */
uint32_t default_data_len(DataType column_type);

/* Calculate the length of table row. */
uint32_t calc_table_row_length(Table *table);

/* Calculate primary key lenght. if not exist primary key , return -1; */
uint32_t calc_primary_key_length(Table *table);

/* Get table meta info. */
MetaTable *get_meta_table(Table *table, char *table_name);

/* Get meta column info by column name. */
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name);

/* Get all meta column info by column name including system reserved column. */
MetaColumn *get_all_meta_column_by_name(MetaTable *meta_table, char *name);
