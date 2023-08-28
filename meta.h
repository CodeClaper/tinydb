#include "data.h"

// column type length
uint32_t column_type_length(DataType column_type);
// calculate the length of table row
uint32_t calc_table_row_length(Table *table);
// get table meta info
MetaTable *get_meta_table(Table *table, char *table_name);
// get meta column info by column name.
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name);
