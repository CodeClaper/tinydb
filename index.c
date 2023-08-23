#include "index.h"
#include <stdint.h>

// get key by column type
uint32_t define_key(void *value, MetaColumn *meta_column) {
    switch(meta_column->column_type) {
        case BIT:
        case FLOAT:
        case DOUBLE:
        case INT:
            return *((uint32_t *) value);
        case CHAR:
            return (uint32_t)(*((char *)value) - 'A');
        case VARCHAR:
            return atoi((char *) value);
        case DATE:
        case TIMESTAMP:
            break;

    }
    return -1;
}
