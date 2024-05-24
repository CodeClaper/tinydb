#include "gtest/gtest.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
#include "list.h"
#include "qsort.h"
}

/* Test for sort int list asc. */
TEST(qsort, int_sort_asc) {
    List *list = create_list(NODE_INT);

    int i;
    for (i = 0; i < 100; i++) {
        int r = rand() % 100;
        append_list(list, &r);
    }

    list_qsort(list, list_int_sort_comparator);

    ListCell *prev = NULL;
    ListCell *lc;
    foreach (lc, list) {
        if (prev != NULL)
            ASSERT_LE(lfirst_int(prev), lfirst_int(lc));
        prev = (lc);
    }
}


/* Test for sort int list asc. */
TEST(qsort, int_sort_desc) {
    List *list = create_list(NODE_INT);

    int i;
    for (i = 0; i < 100; i++) {
        int r = rand() % 100;
        append_list(list, &r);
    }

    list_qsort(list, list_int_sort_comparator_desc);

    ListCell *prev = NULL;
    ListCell *lc;
    foreach (lc, list) {
        if (prev != NULL)
            ASSERT_GE(lfirst_int(prev), lfirst_int(lc));
        prev = (lc);
    }
}
