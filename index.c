#include "index.h"
#include <stdint.h>

// get key by column type
uint32_t define_key(void *value, MetaColumn *meta_column) {
    switch(meta_column->column_type) {
        case T_BOOL:
        case T_FLOAT:
        case T_DOUBLE:
        case T_INT:
            return *((uint32_t *) value);
        case T_CHAR:
            return (uint32_t)(*((char *)value) - 'A');
        case T_STRING:
            return atoi((char *) value);
        case T_DATE:
        case T_TIMESTAMP:
            break;
    }
    return -1;
}
//Get meta column of primary key.
MetaColumn *get_primary_key_meta_column(MetaTable *meta_table) {
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (meta_column->is_primary)
            return meta_column;
    }
    return NULL; //may be return system built-in primary key, but now, return null temporiarily.
}
