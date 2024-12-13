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

#include <unistd.h>
#include "rwlock.h"
#include "mmgr.h"

/* Init the rwlock. */
void init_rwlock(RWLockEntry *lock_entry) {
    lock_entry->mode = RW_INIT;
    lock_entry->readernum = 0;
    lock_entry->pid = 0;
    init_spin_lock(&lock_entry->glock);
    init_spin_lock(&lock_entry->rlock);
}

/* Atomically increase the readernum. */
static void atomic_increase(RWLockEntry *lock_entry) {
    acquire_spin_lock(&lock_entry->rlock);
    lock_entry->readernum++;
    release_spin_lock(&lock_entry->rlock);
}

/* Atomically decrease the readernum. */
static void atomic_decrease(RWLockEntry *lock_entry) {
    Assert(lock_entry->readernum > 0);
    acquire_spin_lock(&lock_entry->rlock);
    lock_entry->readernum--;
    release_spin_lock(&lock_entry->rlock);
}

/* Acuqire the rwlock. */
void acquire_rwlock(RWLockEntry *lock_entry, RWLockMode mode) {

    Assert(mode != RW_INIT);

    switch (lock_entry->mode) {
        case RW_INIT: {
            Assert(lock_entry->readernum == 0);
            acquire_spin_lock(&lock_entry->glock);
            lock_entry->mode = mode;
            lock_entry->pid = getpid();
            if (mode == RW_READERS)
                atomic_increase(lock_entry);
            break;
        }
        case RW_READERS: {
            if (mode == RW_WRITER) {
                acquire_spin_lock(&lock_entry->glock);
                lock_entry->mode = mode;
                lock_entry->pid = getpid();
            } else if (mode == RW_READERS) {
                atomic_increase(lock_entry);
            }
            break;
        }
        case RW_WRITER: {
            /* Allow reenter. */
            if (lock_entry->pid == getpid())
                return;
            acquire_spin_lock(&lock_entry->glock);
            lock_entry->mode = mode;
            if (mode == RW_READERS)
                atomic_increase(lock_entry);
            break;
        }
    }
}

/* Release the rwlock. 
 * For reader lock, only the readernum equal zero, it will really release the lock.
 * */
void release_rwlock(RWLockEntry *lock_entry) {
    Assert(lock_entry->mode != RW_INIT);
    switch (lock_entry->mode) {
        case RW_READERS: {
            atomic_decrease(lock_entry);
            if (lock_entry->readernum == 0)
                release_spin_lock(&lock_entry->glock);
            break;
        }
        case RW_WRITER: {
            release_spin_lock(&lock_entry->glock);
            break;
        }
        default:
            break;
    }
}

/* Degrade the rwlock. 
 * Degrade means the writer process not release the lock,
 * rather than changing the mode to RW_READERS and still acquring the lock.
 * */
void degrade_rwlock(RWLockEntry *lock_entry) {
    Assert(IS_WRITER_LOCK(lock_entry));

    lock_entry->mode = RW_READERS;
    atomic_increase(lock_entry);
}

