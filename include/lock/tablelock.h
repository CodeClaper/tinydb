#include "exlock.h"

/* TableLockEntity. */
typedef struct TableLockEntity {
    char table_name[MAX_TABLE_NAME_LEN];
    ExLockEntry *entry_lock;
} TableLockEntity;

/* Initiliaze the table lock. */
void init_table_lock();

/* Check table if locked. */
void check_table_locked(char *table_name);

/* Try to acqurie the table. */
void try_acquire_table(char *table_name);

/* Try to release the table. */
void try_release_table(char *table_name);
    
