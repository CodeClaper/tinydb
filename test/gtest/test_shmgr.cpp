#include "gtest/gtest.h"
#include <cstring>

extern "C" {
#include "shmgr.h"
#include "data.h"
}

/* Test for create list. */
TEST(list, ShFreeIndex) {
    int index1 = ShFreeIndex(7);
    int index2 = ShFreeIndex(9);
    int index3 = ShFreeIndex(SHM_ALLOC_LIMIT);
    int index4 = ShFreeIndex(1 << (3 + 4 - 1));
    int index5 = ShFreeIndex(1 << (3 + 4 + 1));
    int index6 = ShFreeIndex((1 << (3 + 12)) - 1);
    int index7 = ShFreeIndex((1 << (3 + 12)) + 1);
    ASSERT_EQ(index1, 0);
    ASSERT_EQ(index2, 1);
    ASSERT_EQ(index3, 23);
    ASSERT_EQ(index4, 3);
    ASSERT_EQ(index5, 5);
    ASSERT_EQ(index6, 12);
    ASSERT_EQ(index7, 13);
}
