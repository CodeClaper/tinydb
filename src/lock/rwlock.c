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

static int GetCurrentPid() {
    return getpid();
}

/* Init the rwlock. */
void InitRWlock(RWLockEntry *lock_entry) {
    lock_entry->mode = RW_INIT;
    lock_entry->pids = create_list(NODE_INT);
    init_spin_lock(&lock_entry->glock);
    init_spin_lock(&lock_entry->slock);
    init_spin_lock(&lock_entry->rlock);
    init_spin_lock(&lock_entry->plock);
}

/* Atomically increase the readernum. */
static void AtomicAppendPid(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->plock);
    switch_shared();

    if(len_list(lock_entry->pids) >= 8)
        GetCurrentPid();
    append_list_int(lock_entry->pids, GetCurrentPid());

    switch_local();
    release_spin_lock(&lock_entry->plock);
}

/* Atomically decrease the readernum. */
static void AtomicRemovePid(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->plock);
    switch_shared();

    list_delete_int_first(lock_entry->pids, GetCurrentPid());

    switch_local();
    release_spin_lock(&lock_entry->plock);
}

/* The condition to release rlock. .*/
static inline bool ReleaseRlockCondition(RWLockEntry *lock_entry) {
    return list_empty(lock_entry->pids);
}

/* The reenter condition.
 * Condition includes:
 * (1) only exists one process acuqires the glock. 
 * (2) the last one process is current process. 
 * */
static inline bool ReenterCondition(RWLockEntry *lock_entry) {
    return list_all_int(lock_entry->pids, GetCurrentPid());
}

/* Try acquire rwlock with reenter condition. */
void AcquireRWLockInner(RWLockEntry *lock_entry) {
    if (lock_entry->glock == SPIN_UN_LOCKED_STATUS)
        Assert(list_empty(lock_entry->pids));
    while (lock_entry->glock) {
        if (ReenterCondition(lock_entry)) 
            break;
        usleep(DEFAULT_SPIN_INTERVAL);
    }
    lock_entry->glock = SPIN_LOCKED_STATUS;
}

/* Try to release rwlock.*/
static inline void ReleaseRWLockInner(RWLockEntry *lock_entry) {
    lock_entry->glock = SPIN_UN_LOCKED_STATUS;
}

/* Acuqire the rwlock. */
void AcquireRWlock(RWLockEntry *lock_entry, RWLockMode mode) {
    Assert(mode != RW_INIT);
    acquire_spin_lock(&lock_entry->slock);
    switch (lock_entry->mode) {
        case RW_INIT: {
            Assert(ReleaseRlockCondition(lock_entry));
            AcquireRWLockInner(lock_entry);
            AtomicAppendPid(lock_entry);
            lock_entry->mode = mode;
            Assert(len_list(lock_entry->pids) == 1);
            break;
        }
        case RW_READERS: {
            Assert(lock_entry->glock == SPIN_LOCKED_STATUS);
            /* If RW_READERS mode, the lock entry is shared. 
             * Just append the current reader process pid .*/
            if (mode == RW_READERS) 
                AtomicAppendPid(lock_entry);
            /* If RW_WRITER mode, we firstly check if current process is the only one who acuqires the glock.
             * If yes, same process reenter and just change the lock mode. If not, acuqire the glock. */
            else if (mode == RW_WRITER) {
                AcquireRWLockInner(lock_entry);
                lock_entry->mode = RW_WRITER;
                AtomicAppendPid(lock_entry);
            }
            break;
        }
        case RW_WRITER: {
            Assert(lock_entry->glock == SPIN_LOCKED_STATUS);
            /* At most one process acuqires the glock in RW_WRITER mode. */
            AcquireRWLockInner(lock_entry);
            lock_entry->mode = mode;
            AtomicAppendPid(lock_entry);
            break;
        }
    }
    release_spin_lock(&lock_entry->slock);
}

/* Release the rwlock. 
 * For reader lock, only the readernum equal zero, it will really release the lock.
 * */
void ReleaseRWlock(RWLockEntry *lock_entry) {
    Assert(NOT_INIT_LOCK(lock_entry));
    Assert(lock_entry->glock == SPIN_LOCKED_STATUS);
    acquire_spin_lock(&lock_entry->rlock);
    switch (lock_entry->mode) {
        case RW_READERS: {
            AtomicRemovePid(lock_entry);
            if (ReleaseRlockCondition(lock_entry)) {
                ReleaseRWLockInner(lock_entry);
                lock_entry->mode = RW_INIT;
            }
            break;
        }
        case RW_WRITER: {
            AtomicRemovePid(lock_entry);
            if (list_empty(lock_entry->pids))
                lock_entry->mode = RW_INIT;
            else
                lock_entry->mode = RW_READERS;
            break;
        }
        default:
            break;
    }
    release_spin_lock(&lock_entry->rlock);
}
