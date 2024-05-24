#include "qsort.h"
#include "list.h"
#include <stdlib.h>

/* Qsort for list. */
void list_qsort(List *list, list_sort_comparator comparator) {
	typedef int (*qsort_comparator) (const void *a, const void *b);
    qsort(list->elements, list->size, sizeof(ListCell), (qsort_comparator)comparator);
}
