#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "intpr.h"
#include "opr.h"
#include "log.h"

/*Equal operation (=).*/
bool equal(void *source, void *target, DataType data_type) {
    if (source == NULL && target == NULL) 
        return true;
    else if (source != NULL && target == NULL) 
        return false;
    else if (source == NULL && target != NULL)
        return false;
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
        case T_TIMESTAMP:
            return *(time_t *)source == *(time_t *)target;
        case T_DATE:
            return *(time_t *)source == *(time_t *)target;
    }
    return false;
}

/* Not equal operation. (!=)*/
bool not_equal(void *source, void *target, DataType data_type) {
    if (source == NULL && target == NULL) 
        return false;
    else if (source != NULL && target == NULL) 
        return true;
    else if (source == NULL && target != NULL)
        return true;
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
        case T_TIMESTAMP:
            return *(time_t *)source != *(time_t *)target;
        case T_DATE:
            return *(time_t *)source != *(time_t *)target;
    }
    return false;
}

/* Not equal operation. (>) */
bool greater(void *source, void *target, DataType data_type) {
    if (source == NULL && target == NULL) 
        return false;
    else if (source != NULL && target == NULL) 
        return true;
    else if (source == NULL && target != NULL)
        return false;
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
        case T_TIMESTAMP:
            return *(time_t *)source > *(time_t *)target;
        case T_BOOL:
            return *(bool *)source > *(bool *)target;
        case T_DATE:
            return *(time_t *)source > *(time_t *)target;
    }
    return false;
}

/* Not equal operation. (>=) */
bool greater_equal(void *source, void *target, DataType data_type) {
    if (source == NULL && target == NULL) 
        return true;
    else if (source != NULL && target == NULL) 
        return true;
    else if (source == NULL && target != NULL)
        return false;
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
        case T_TIMESTAMP:
            return *(time_t *)source >= *(time_t *)target;
        case T_BOOL:
            return *(bool *)source >= *(bool *)target;
        case T_DATE:
            return *(time_t *)source >= *(time_t *)target;
    }
    return false;
}

/* Not equal operation. (<) */
bool less(void *source, void *target, DataType data_type) {
    if (source == NULL && target == NULL) 
        return false;
    else if (source != NULL && target == NULL) 
        return false;
    else if (source == NULL && target != NULL)
        return true;
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
        case T_TIMESTAMP:
            return *(time_t *)source < *(time_t *)target;
        case T_BOOL:
            return *(bool *)source < *(bool *)target;
        case T_DATE:
            return *(time_t *)source < *(time_t *)target;
    }
    return false;
}

/* Not equal operation. (<=) */
bool less_equal(void *source, void *target, DataType data_type) {
    if (source == NULL && target == NULL) 
        return true;
    else if (source != NULL && target == NULL) 
        return false;
    else if (source == NULL && target != NULL)
        return true;
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
        case T_TIMESTAMP:
            return *(time_t *)source <= *(time_t *)target;
        case T_BOOL:
            return *(bool *)source <= *(bool *)target;
        case T_DATE:
            return *(time_t *)source <= *(time_t *)target;
    }
    return false;
}

/* Eval, now supported operation: 
 * EQ NE GT GE LT LE 
 * */
bool eval(OprType op_type, void *source, void *target, DataType data_type) {
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
            db_log(PANIC, "Not supported operation type");
        default:
            return false;
    }
}
