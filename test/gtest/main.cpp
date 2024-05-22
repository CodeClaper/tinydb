#include "gtest/gtest.h"
#include <setjmp.h>

extern "C" {
#include "data.h"
}
Conf *conf; /* Conf */
jmp_buf errEnv; /* jmp_buf for error. */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
