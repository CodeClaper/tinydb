#include <string.h>
#include <time.h>
#include "list.h"
#include "data.h"

#ifndef Q_SORT_H
#define Q_SORT_H

typedef int (*list_sort_comparator) (const ListCell *lc1, const ListCell *lc2);

/* Comparator for int list order by asc. */
static inline int list_int_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_int(lc1) - lfirst_int(lc2);
}

/* Comparator for int list order by desc. */
static inline int list_int_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_int(lc2) - lfirst_int(lc1);
}

static inline int list_bool_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_bool(lc1) - lfirst_bool(lc2);
}

static inline int list_bool_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return lfirst_bool(lc2) - lfirst_bool(lc1);
}

static inline int list_char_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return (*(char *)lfirst(lc1)) -  (*(char *)lfirst(lc2));
}

static inline int list_char_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return (*(char *)lfirst(lc2)) -  (*(char *)lfirst(lc1));
}

static inline int list_varchar_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return strcmp((char *) lfirst(lc1), (char *) lfirst(lc2));
}

static inline int list_varchar_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return strcmp((char *) lfirst(lc2), (char *) lfirst(lc1));
}

static inline int list_float_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_float(lc1) - lfirst_float(lc2);
}

static inline int list_float_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_float(lc2) - lfirst_float(lc1);
}

static inline int list_double_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_double(lc1) - lfirst_double(lc2);
}

static inline int list_double_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_double(lc2) - lfirst_double(lc1);
}

static inline int list_date_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return (*(time_t *)lfirst(lc1)) -  (*(time_t *)lfirst(lc2));
}

static inline int list_date_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return (*(time_t *)lfirst(lc2)) -  (*(time_t *)lfirst(lc1));
}

static inline int list_tiemstamp_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return (*(time_t *)lfirst(lc1)) -  (*(time_t *)lfirst(lc2));
}

static inline int list_tiemstamp_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return (*(time_t *)lfirst(lc2)) -  (*(time_t *)lfirst(lc1));
}

static inline list_sort_comparator implement_list_sort_comparator(DataType type) {
    switch (type) {
        case T_BOOL:
            return list_bool_sort_comparator;
        case T_CHAR:
            return list_char_sort_comparator;
        case T_VARCHAR:
        case T_STRING:
            return list_varchar_sort_comparator;
        case T_INT:
            return list_int_sort_comparator;
        case T_LONG:
            return list_int_sort_comparator;
        case T_DOUBLE:
            return list_double_sort_comparator;
        case T_FLOAT:
            return list_float_sort_comparator;
        case T_DATE:
            return list_date_sort_comparator;
        case T_TIMESTAMP:
            return list_tiemstamp_sort_comparator;
        default:
            UNEXPECTED_VALUE(type);
    }
}

/* Qsort for list. */
extern void list_qsort(List *list, list_sort_comparator comparator);

#endif
