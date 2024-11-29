/******************************************* The Spin Lock Module *********************************************************
 * Auth:        JerryZhou
 * Created:     2024/01/24
 * Modify:      2024/01/24
 * Locataion:   src/memory/shmem.c
 * Description: TinydDb support tow ways of lock, spin lock and wrlock. 
 * Spin lock is an exclusieve lock, and wrlock is shared for all read operation threads, 
 * and exclusieve if including write operation thread. The current thread try to acquire a contended spin lock, 
 * and block for a while using usleep if fail, and then try again until success. This routine is known as Test-and-Set(TAS).
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
