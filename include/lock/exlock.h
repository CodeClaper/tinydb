#include "spinlock.h"

typedef struct ExLockEntry {
    volatile s_lock lock;   /* The lock. */
    volatile int64_t tid;    /* The thread id that acquiring the lock.*/
}ExLockEntry;

/* Init exclusive lock. */
void init_exlock(ExLockEntry *lock_entry);

/* Acqure the exclusive lock. */
void acquire_exlock(ExLockEntry *lock_entry);

/* Release the exclusive lock. */
void release_exlock(ExLockEntry *lock_entry);

/* Wait for exlock released. */
void wait_for_exlock(ExLockEntry *lock_entry);
