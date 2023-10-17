#include "data.h"

// get key by column type
uint32_t define_key(void *value, MetaColumn *meta_column);

//Get meta column of primary key.
MetaColumn *get_primary_key_meta_column(MetaTable *meta_table);
