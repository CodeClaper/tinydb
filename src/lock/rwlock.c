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
    init_spin_lock(&lock_entry->content_lock);
    init_spin_lock(&lock_entry->sync_acquire_lock);
    init_spin_lock(&lock_entry->sync_release_lock);
}

/* Atomically increase the readernum. */
static void AtomicAppendPid(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->sync_acquire_lock);
    switch_shared();
    append_list_int(lock_entry->pids, GetCurrentPid());
    switch_local();
    release_spin_lock(&lock_entry->sync_acquire_lock);
}

/* Atomically decrease the readernum. */
static void AtomicRemovePid(RWLockEntry *lock_entry) {
    switch_shared();
    list_delete_int_first(lock_entry->pids, GetCurrentPid());
    switch_local();
}

/* The condition to release rlock. .*/
static inline bool ReleaseRlockCondition(RWLockEntry *lock_entry) {
    return list_empty(lock_entry->pids);
}

/* The reenter condition.
 * Reenter condition includes:
 * (1) All process in pids is the current process. 
 * (2) RWLockMode in RWLockMode mode, and the request also RWLockMode. 
 * */
static inline bool ReenterCondition(RWLockEntry *lock_entry, Pid curpid, RWLockMode mode) {
    return list_all_int(lock_entry->pids, curpid) || 
            (lock_entry->mode == RW_READERS && mode == RW_READERS);
}

/* Try acquire rwlock with reenter condition. */
static void AcquireRWLockInner(RWLockEntry *lock_entry, RWLockMode mode) {
    if (lock_entry->content_lock == SPIN_UN_LOCKED_STATUS)
        Assert(list_empty(lock_entry->pids));
    Pid curpid = GetCurrentPid();
    while (__sync_lock_test_and_set(&lock_entry->content_lock, 1)) {
        while (lock_entry->content_lock) {
            if (ReenterCondition(lock_entry, curpid, mode)) 
                goto modify_mode;
            if (lock_spin(DEFAULT_SPIN_INTERVAL))
                lock_sleep(DEFAULT_SPIN_INTERVAL);
        }
    }
modify_mode:
    lock_entry->mode = mode;
}

/* Try to release rwlock.*/
static inline void ReleaseRWLockInner(RWLockEntry *lock_entry) {
	__sync_synchronize();
    lock_entry->content_lock = SPIN_UN_LOCKED_STATUS;
}

/* Acuqire the rwlock. */
void AcquireRWlock(RWLockEntry *lock_entry, RWLockMode mode) {
    Assert(mode != RW_INIT);
    AcquireRWLockInner(lock_entry, mode); 
    AtomicAppendPid(lock_entry);
}

/* Release the rwlock. 
 * For reader lock, only the readernum equal zero, it will really release the lock.
 * */
void ReleaseRWlock(RWLockEntry *lock_entry) {
    Assert(NOT_INIT_LOCK(lock_entry));
    Assert(lock_entry->content_lock == SPIN_LOCKED_STATUS);
    acquire_spin_lock(&lock_entry->sync_release_lock);
    AtomicRemovePid(lock_entry);
    if (list_empty(lock_entry->pids))
        lock_entry->mode = RW_INIT;
    else
        lock_entry->mode = RW_READERS;
    release_spin_lock(&lock_entry->sync_release_lock);
}
