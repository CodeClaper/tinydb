#include "common.h"
#include "misc.h"
#include "opr.h"
#include "./sql/intpr.h"
#include <string.h>

// Equal operation.
static bool equal(void *source, void *target, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
            return *(bool *)source == *(bool *)target;
        case T_CHAR:
            return *(char *)source == *(char *)target;
        case T_INT:
            return *(int32_t *)source == *(int32_t *)target;
        case T_STRING:
            return strcmp((char *)source, (char *)target) == 0;
        case T_DOUBLE:
            return *(double *)source == *(double *)target;
        case T_FLOAT:
            return *(float *)source == *(float *)target;
        case T_DATE:
        case T_TIMESTAMP:
            fatal("Not supported data type");
    }
    return false;
}

// Not equal operation.
static bool not_equal(void *source, void *target, DataType data_type) {
    switch(data_type) {
        case T_BOOL:
            return *(bool *)source != *(bool *)target;
        case T_CHAR:
            return *(char *)source != *(char *)target;
        case T_INT:
            return *(int32_t *)source != *(int32_t *)target;
        case T_STRING:
            return strcmp((char *)source, (char *)target) != 0;
        case T_DOUBLE:
            return *(double *)source != *(double *)target;
        case T_FLOAT:
            return *(float *)source != *(float *)target;
        case T_DATE:
        case T_TIMESTAMP:
            fatal("Not supported data type");
    }
    return false;
}

// Not equal operation.
static bool greater(void *source, void *target, DataType data_type) {
    switch(data_type) {
        case T_CHAR:
            return *(char *)source > *(char *)target;
        case T_INT:
            return *(int32_t *)source > *(int32_t *)target;
        case T_STRING:
            return strcmp((char *)source, (char *)target) > 0;
        case T_DOUBLE:
            return *(double *)source > *(double *)target;
        case T_FLOAT:
            return *(float *)source > *(float *)target;
        case T_BOOL:
        case T_DATE:
        case T_TIMESTAMP:
            fatal("not implement.");
    }
    return false;
}

// Not equal operation.
static bool greater_equal(void *source, void *target, DataType data_type) {
    switch(data_type) {
        case T_CHAR:
            return *(char *)source >= *(char *)target;
        case T_INT:
            return *(int32_t *)source >= *(int32_t *)target;
        case T_STRING:
            return strcmp((char *)source, (char *)target) >= 0;
        case T_DOUBLE:
            return *(double *)source >= *(double *)target;
        case T_FLOAT:
            return *(float *)source >= *(float *)target;
        case T_BOOL:
        case T_DATE:
        case T_TIMESTAMP:
            fatal("not implement.");
    }
    return false;
}

// Not equal operation.
static bool less(void *source, void *target, DataType data_type) {
    switch(data_type) {
        case T_CHAR:
            return *(char *)source < *(char *)target;
        case T_INT:
            return *(int32_t *)source < *(int32_t *)target;
        case T_STRING:
            return strcmp((char *)source, (char *)target) < 0;
        case T_DOUBLE:
            return *(double *)source < *(double *)target;
        case T_FLOAT:
            return *(float *)source < *(float *)target;
        case T_BOOL:
        case T_DATE:
        case T_TIMESTAMP:
            fatal("not implement.");
    }
    return false;
}

// Not equal operation.
static bool less_equal(void *source, void *target, DataType data_type) {
    switch(data_type) {
        case T_CHAR:
            return *(char *)source <= *(char *)target;
        case T_INT:
            return *(int32_t *)source <= *(int32_t *)target;
        case T_STRING:
            return strcmp((char *)source, (char *)target) <= 0;
        case T_DOUBLE:
            return *(double *)source <= *(double *)target;
        case T_FLOAT:
            return *(float *)source <= *(float *)target;
        case T_BOOL:
        case T_DATE:
        case T_TIMESTAMP:
            fatal("not implement.");
    }
    return false;
}

// Eval
bool eval(OpType op_type, void *source, void *target, DataType data_type) {
    switch(op_type) {
        case O_EQ:
            return equal(source, target, data_type);
        case O_NE:
            return not_equal(source, target, data_type);
        case O_GT:
            return greater(source, target, data_type);
        case O_GE:
            return greater_equal(source, target, data_type);
        case O_LT:
            return less(source, target, data_type);
        case O_LE:
            return less_equal(source, target, data_type);
        case O_IN:
        case O_LIKE:
            fatal("not supported operation type");
        default:
            return false;
    }
}
