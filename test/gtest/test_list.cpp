#include "gtest/gtest.h"

extern "C" {
#include "list.h"
}

/* Test for create list. */
TEST(list, create_list) {
    List *list = create_list(NODE_INT);
    ASSERT_NE(list, NIL);
    ASSERT_EQ(list->size, INIT_LIST_CELL_SIZE);
}
