#include "spinlock.h"

/* Rwlock mode. */
typedef enum RWLockMode {
    RW_READERS,
    RW_WRITEER
} RWLockMode;

/* Rwlock Entry. */
typedef struct RWLockEntry {
    RWLockMode mode;        /* Rwlock mode. */
    volatile s_lock lock;   /* Spinlock. */
    volatile pid_t pid;     /* The process that acquires the lock. */
} RWLockEntry;

/* Init the rwlock. */
void InitRwlock(RWLockEntry *lock_entry);

/* Acuqire the rwlock. */
void AcquireRwlock(RWLockEntry *lock_entry);

/* Release the rwlock. */
void ReleaseRwlock(RWLockEntry *lock_entry);

/* Wait for the rwlock. */
void WaitForRwlock(RWLockEntry *lock_entry);


