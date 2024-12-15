/******************************************* The Readers-Writer Lock Module *********************************************************
 * Auth:        JerryZhou
 * Created:     2024/12/11
 * Modify:      2024/12/11
 * Locataion:   src/lock/rwlock.c
 * Description: The readers-writer lock module supports the locking mechanism for reading and writing operations 
 * in concurrent scenarios.
 *
 * -------------------
 * The readers-writer lock has these meanings:
 * (1) The readers lock is a shared lock, it allowed other process to read the locked content and not allowd 
 * other process to write the locked content.
 * (2) The writer lock is an exclusive lock, it neither allowes other process to read nor other process to write 
 * the lock content.
 ***************************************************************************************************************************
 * */

#include <stdbool.h>
#include <unistd.h>
#include "rwlock.h"
#include "mmgr.h"
#include "list.h"

/* Init the rwlock. */
void init_rwlock(RWLockEntry *lock_entry) {
    lock_entry->mode = RW_INIT;
    lock_entry->pids = create_list(NODE_INT);
    init_spin_lock(&lock_entry->glock);
    init_spin_lock(&lock_entry->plock);
}

/* Atomically increase the readernum. */
static void atomic_append_proc(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->plock);

    pid_t pid = getpid();
    if (!list_member_int(lock_entry->pids, pid))
        append_list_int(lock_entry->pids, pid);

    release_spin_lock(&lock_entry->plock);
}

/* Atomically decrease the readernum. */
static void atomic_remove_proc(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->plock);

    pid_t pid = getpid();
    list_delete_int(lock_entry->pids, pid);

    release_spin_lock(&lock_entry->plock);
}

/* If current process is the only one who acuqires the glock.*/
static inline bool only_acquire_glock(RWLockEntry *lock_entry) {
    return lock_entry->pids->size == 1 && list_member_int(lock_entry->pids, getpid());
}

/* If 'onbody' acuqires the glock.*/
static inline bool nobody_acquire_glock(RWLockEntry *lock_entry) {
    return list_empty(lock_entry->pids);
}

/* If only one process acuqires the lock. */
static inline bool only_one_proc(RWLockEntry *lock_entry) {
    return lock_entry->pids->size == 1;
}

/* Acuqire the rwlock. */
void acquire_rwlock(RWLockEntry *lock_entry, RWLockMode mode) {
    Assert(mode != RW_INIT);
    switch (lock_entry->mode) {
        case RW_INIT: {
            Assert(nobody_acquire_glock(lock_entry));
            acquire_spin_lock(&lock_entry->glock);
            lock_entry->mode = mode;
            atomic_append_proc(lock_entry);
            break;
        }
        case RW_READERS: {
            /* If RW_READERS mode, the lock entry is shared. 
             * Just append the current reader process.*/
            if (mode == RW_READERS) 
                atomic_append_proc(lock_entry);
            /* If RW_WRITER mode, we firstly check if current process is the only one who acuqires the glock.
             * If yes, just change the lock mode. If not, acuqire the glock. */
            else if (mode == RW_WRITER) {
                if (!only_acquire_glock(lock_entry)) {
                    acquire_spin_lock(&lock_entry->glock);
                    atomic_append_proc(lock_entry);
                }
                lock_entry->mode = mode;
            }
            break;
        }
        case RW_WRITER: {
            /* Allow the Reenterlock. */
            if (!only_acquire_glock(lock_entry)) {
                /* If other process, acquire glock. */
                acquire_spin_lock(&lock_entry->glock);
                lock_entry->mode = mode;
                atomic_append_proc(lock_entry);
            }
            break;
        }
    }
}

/* Release the rwlock. 
 * For reader lock, only the readernum equal zero, it will really release the lock.
 * */
void release_rwlock(RWLockEntry *lock_entry) {
    Assert(NOT_INIT_LOCK(lock_entry));
    switch (lock_entry->mode) {
        case RW_READERS: {
            atomic_remove_proc(lock_entry);
            if (nobody_acquire_glock(lock_entry))
                release_spin_lock(&lock_entry->glock);
            break;
        }
        case RW_WRITER: {
            atomic_remove_proc(lock_entry);
            release_spin_lock(&lock_entry->glock);
            break;
        }
        default:
            break;
    }
}
