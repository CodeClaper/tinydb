/******************************************* The Spin Lock Module *********************************************************
 * Auth:        JerryZhou
 * Created:     2024/01/24
 * Modify:      2024/01/24
 * Locataion:   src/memory/shmem.c
 * Description: The spin lock is the foundation of the locking mechanism
 * When waiting for a contented spin lock, we loop for a while and then try again. 
 * This routine is also known as Test-and-Set(TAS).
 ***************************************************************************************************************************
 * */

#include <unistd.h>
#include "spinlock.h"

/* Init spin lock. */
void init_spin_lock(volatile s_lock *lock) {
    *lock = SPIN_UN_LOCKED_STATUS;
}

/* Acquire spin lock, if fail, it will block. */
void acquire_spin_lock(volatile s_lock *lock) {

    while (*lock) {
        usleep(DEFAULT_SPIN_INTERVAL);
    }

    *lock = SPIN_LOCKED_STATUS;
}

/* Release spin lock. */
void release_spin_lock(volatile s_lock *lock) {
    *lock = SPIN_UN_LOCKED_STATUS;
}

/* Wait for spin lock released. */
void wait_for_spin_lock(volatile s_lock *lock) {
    while (*lock) {
        usleep(DEFAULT_SPIN_INTERVAL);
    }
}
