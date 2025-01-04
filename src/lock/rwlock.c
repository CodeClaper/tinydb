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
#include <stdatomic.h>
#include "rwlock.h"
#include "mmgr.h"
#include "list.h"

static inline int GetCurrentPid() {
    return getpid();
}

/* Init the rwlock. */
void InitRWlock(RWLockEntry *lock_entry) {
    lock_entry->mode = RW_INIT;
    lock_entry->owner = create_list(NODE_INT);
    init_spin_lock(&lock_entry->content_lock);
    init_spin_lock(&lock_entry->sync_lock);
}

/* Atomically increase the readernum. */
static void AtomicAppendPid(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->sync_lock);
    switch_shared();
    append_list_int(lock_entry->owner, GetCurrentPid());
    switch_local();
    release_spin_lock(&lock_entry->sync_lock);
}

/* Atomically decrease the readernum. */
static void AtomicRemovePid(RWLockEntry *lock_entry) {
    switch_shared();
    list_delete_int_first(lock_entry->owner, GetCurrentPid());
    switch_local();
}

/* The condition to release rlock. .*/
static inline bool ReleaseRlockCondition(RWLockEntry *lock_entry) {
    return list_empty(lock_entry->owner);
}

/* The reenter condition.
 * Reenter condition includes:
 * (1) All process in owner is the same process. 
 * (2) RWLock in RWLockMode mode, and the request also RWLockMode lock. 
 * */
static inline bool ReenterCondition(RWLockEntry *lock_entry, Pid curpid, RWLockMode mode) {
    return list_all_int(lock_entry->owner, curpid) || 
            (lock_entry->mode == RW_READERS && mode == RW_READERS);
}

/* Try acquire rwlock with reenter condition. */
static void AcquireRWLockInner(RWLockEntry *lock_entry, RWLockMode mode) {
    if (UN_LOCKED(lock_entry->content_lock))
        Assert(list_empty(lock_entry->owner));
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
    __sync_synchronize();
    lock_entry->mode = mode;
}

/* Try to release rwlock.*/
static inline void ReleaseRWLockInner(RWLockEntry *lock_entry) {
    /* Tell the c compiler and the CPU to not move loads or stores
     * past this point, to ensure that all the stores in the critical
     * section are visible to other CPUs before the  lock is released,
     * and that load in the critical seciton occrur strictly before
     * the lock is released. */
	__sync_synchronize();

    /* Release the lock, equivalent to lock_entry->content_lock = 0. 
     * This code does`t use a C assignment, since the C standard implies
     * that an assignment might be implemented with multiple store instructions. */
    __sync_lock_release(&lock_entry->content_lock);

    /* Notice block processor. */
    NOTICE();
}

/* Acuqire the rwlock. */
void AcquireRWlock(RWLockEntry *lock_entry, RWLockMode mode) {
    Assert(mode != RW_INIT);
    AcquireRWLockInner(lock_entry, mode); 
    AtomicAppendPid(lock_entry);
}

/* Release the rwlock. */
void ReleaseRWlock(RWLockEntry *lock_entry) {
    Assert(NOT_INIT_LOCK(lock_entry));
    Assert(LOCKED(lock_entry->content_lock));
    acquire_spin_lock(&lock_entry->sync_lock);
    AtomicRemovePid(lock_entry);
    lock_entry->mode = list_empty(lock_entry->owner) 
                ? RW_INIT 
                : RW_READERS;
    release_spin_lock(&lock_entry->sync_lock);
}
