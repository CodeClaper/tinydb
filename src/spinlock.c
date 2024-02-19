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


/* Acquire spin lock, if fail, it will block. */
void spinLockAcquire(s_lock *lock) {

    while (*lock) {
        usleep(DEFAULT_SPIN_INTERVAL);
    }

    *lock = SPIN_LOCKED_STATUS;
}

/* Release spin lock. */
void spinLockRelease(s_lock *lock) {
    *lock = SPIN_UN_LOCKED_STATUS;
}
