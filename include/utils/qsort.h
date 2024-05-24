#include "list.h"

typedef int (*list_sort_comparator) (const ListCell *lc1, const ListCell *lc2);

/* Comparator for int list order by asc. */
inline static int list_int_sort_comparator(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_int(lc1) - lfirst_int(lc2);
}

/* Comparator for int list order by desc. */
inline static int list_int_sort_comparator_desc(const ListCell *lc1, const ListCell *lc2) {
    return  lfirst_int(lc2) - lfirst_int(lc1);
}

/* Qsort for list. */
extern void list_qsort(List *list, list_sort_comparator comparator);
