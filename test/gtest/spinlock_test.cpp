#include "gtest/gtest.h"

extern "C" {
#include "include/spinlock.h"
}

static s_lock lock = SPIN_UN_LOCKED_STATUS;

TEST(spinlock, ok) {
    ASSERT_EQ(1, 1);
}
