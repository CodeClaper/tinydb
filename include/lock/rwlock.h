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
    s_lock glock;                   /* Global lock. */
    s_lock plock;                   /* Pids change lock to make sure pids append and delete atomically.*/
    List  *pids;                    /* Acuqire processes. */
} RWLockEntry;

#define NOT_INIT_LOCK(entry) \
        (entry->mode != RW_INIT)

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

#endif
