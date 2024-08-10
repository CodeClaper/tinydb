/*
 * ========================================= The Spin Lock Module =======================================================
 * TinydDb support tow ways of lock, spin lock and wrlock. Spin lock is exclusieve lock, and wrlock is shared for all read 
 * operation threads, and exclusieve if including write operation thread.
 * When try to get a contended spin lock, delay for a while using usleep and then try again. 
 * This routine is known as Test-and-Set(TAS).
 * ======================================================================================================================
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
