#include "gtest/gtest.h"
#include <setjmp.h>

extern "C" {
#include "data.h"
#include "shmem.h"
#include "mem.h"
#include "mmu.h"
#include "log.h"
#include "session.h"
#include "trans.h"
#include "xlog.h"
#include "cache.h"
#include "buffer.h"
#include "conf.h"
#include "refer.h"
}
Conf *conf; /* Conf */
jmp_buf errEnv; /* jmp_buf for error. */


/* DB Start. */
static void db_start() {

    /* Initialise shmem. */
    init_shmem();

    /* Initialise memory manager unit. */
    init_mmu();

    /* Initialise memory manger. */
    init_mem();

    /* Initialise transaction. */
    init_trans();

    /* Initialise xlog. */
    init_xlog();

    /* Initialise table cache. */
    init_table_cache();

    /* Initialise table buffer. */
    init_table_buffer();

    /* Initialise refer. */
    init_refer();

    /* Load configuration. */
    conf = load_conf();
}

int main(int argc, char **argv) {
    db_start();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
