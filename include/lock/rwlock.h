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
} RWLockEntry;

/* Init the rwlock. */
void init_rwlock(RWLockEntry *lock_entry);

/* Acuqire the rwlock. */
void acquire_rwlock(RWLockEntry *lock_entry, RWLockMode mode);

/* Release the rwlock. */
void release_rwlock(RWLockEntry *lock_entry);

#endif
