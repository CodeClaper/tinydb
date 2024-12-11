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

#include "rwlock.h"

/* Init the rwlock. */
void InitRwlock(RWLockEntry *lock_entry);

/* Acuqire the rwlock. */
void AcquireRwlock(RWLockEntry *lock_entry);

/* Release the rwlock. */
void ReleaseRwlock(RWLockEntry *lock_entry);

/* Wait for the rwlock. */
void WaitForRwlock(RWLockEntry *lock_entry);



