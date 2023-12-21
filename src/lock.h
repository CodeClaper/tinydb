#include "data.h"

/* Initialise lock. */
void init_lock();

/* Db read row level read mode or write lock. */
LockState *db_row_lock(Refer *refer, LockMode lock_mode);

/* File unlock. */
void db_unlock(LockState *lock_state);
