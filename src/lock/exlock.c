/****************************** The Exclusive Lock ***************************
 * Auth:        JerryZhou
 * Created:     2024/08/10
 * Modify:      2024/08/10
 * Locataion:   src/lock/exlock.c
 * Description: The exclusive lock is a lock which only allowed one thread 
 * acuqires the lock. Ohters threads will wail unitil releasing the lock.
******************************************************************************/

#include <pthread.h>
#include <stdint.h>
#include "spinlock.h"
#include "exlock.h"

/* Init exclusive lock. */
void init_exlock(ExLockEntry *lock_entry) {
    Assert(lock_entry);
    lock_entry->tid = 0;
    spin_lock_init(&lock_entry->lock);
}

/* Acqure the exclusive lock. */
void acquire_exlock(ExLockEntry *lock_entry) {
    Assert(lock_entry);
    int64_t current_tid = pthread_self();
    /* If current thread is the one that aleary 
     * acuqiring the lock, return.*/
    if (current_tid == lock_entry->tid)
        return;
    spin_lock_acquire(&lock_entry->lock);
    lock_entry->tid = current_tid;
}

/* Release the exclusive lock. */
void release_exlock(ExLockEntry *lock_entry) {
    Assert(lock_entry);
    int64_t current_tid = pthread_self();
    /* Only the thread that has acuqired the lock can release the lock.*/
    if (current_tid != lock_entry->tid)
        return;
    spin_lock_release(&lock_entry->lock);
    lock_entry->tid = 0;
}

/* Wait for exlock released. */
void wait_for_exlock(ExLockEntry *lock_entry) {
    Assert(lock_entry);
    int64_t current_tid = pthread_self();
    /* If current thread is the one that aleary 
     * acuqiring the lock, return.*/
    if (current_tid == lock_entry->tid)
        return;
    spin_lock_wait_for(&lock_entry->lock);
}

