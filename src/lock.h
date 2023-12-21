#include "data.h"

/* Initialise lock. */
void init_lock();

/* Db read row level read mode or write lock. */
LockHandle *db_row_lock(Refer *refer, LockMode lock_mode);

/* Unlock. */
void db_unlock(LockHandle *lock_handle);
