#include <fcntl.h>
#include <stdint.h>
#include "spinlock.h"

#ifndef RWLOCK_H
#define RWLOCK_H

/* Rwlock mode. */
typedef enum RWLockMode {
    RW_INIT,
    RW_READERS,
    RW_WRITER
} RWLockMode;

/* Rwlock Entry. */
typedef struct RWLockEntry {
    RWLockMode mode;                /* Rwlock mode. */
    volatile uint32_t readernum;    /* The number of readers. */
    s_lock glock;                   /* Global lock. */
    s_lock rlock;                   /* Reader lock to make sure reader numer atomically increases or descreases.*/
    pid_t  pid;                     /* The process acquring the lock. */
} RWLockEntry;

#define IS_READERS_LOCK(entry) \
        (entry->mode == RW_READERS)

#define IS_WRITER_LOCK(entry) \
        (entry->mode == RW_WRITER)

/* Init the rwlock. */
void init_rwlock(RWLockEntry *lock_entry);

/* Acuqire the rwlock. */
void acquire_rwlock(RWLockEntry *lock_entry, RWLockMode mode);

/* Release the rwlock. */
void release_rwlock(RWLockEntry *lock_entry);

/* Degrade the rwlock. */
void degrade_rwlock(RWLockEntry *lock_entry);

#endif
