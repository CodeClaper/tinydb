/**
 *========================================The Table Lock Module =================================
 * This module supports the table-level lock mechanism which depends on spinlock at the bottom layer.
 * The table-level lock is an exclusive lock which means only one thread could acquire the table at 
 * the time. 
 * Ony DDL statements will try to acquire the lock and call the function <try_acquire_table>,
 * Other DML or DQL statements just need to check the table if locked.
 *===============================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tablelock.h"
#include "utils.h"
#include "mmu.h"
#include "mem.h"

/* The list stores TableLockEntity. */
static List *lock_list;

/* Initiliaze the table lock. */
void init_table_lock() {
    switch_shared();
    lock_list = create_list(NODE_VOID);
    switch_local();
}

/* Find TableLockEntity in list.
 * Return NULL if not found. */
static TableLockEntity *find_lock_entry(char *table_name) {
    ListCell *lc;
    foreach (lc, lock_list) {
        TableLockEntity *current = lfirst(lc);
        if (streq(current->table_name, table_name))
            return current;
    }
    return NULL;
}

/* Register TableLockEntity. */
static void register_lock_entry(char *table_name) {
    switch_shared();

    TableLockEntity *new_one = instance(TableLockEntity);
    strcpy(new_one->table_name, table_name);
    new_one->entry_lock = instance(ExLockEntry);
    init_exlock(new_one->entry_lock);
    acquire_exlock(new_one->entry_lock);
    append_list(lock_list, new_one);

    switch_local();
}

/* Check table if locked. 
 * Firstly, find TableLockEntity in list and check if exist. 
 * If there is not TableLockEntity, just return, 
 * otherwise, try to acqurie the lock. 
 * */
void check_table_locked(char *table_name) {
    Assert(!is_empty(table_name));
    TableLockEntity *lock_entry = find_lock_entry(table_name);
    if (lock_entry) {

        printf("wait for table %s\n", table_name);

        /* Try to check exlock if unlolocked, maybe block here when locked. */
        wait_for_exlock(lock_entry->entry_lock);   
    }
}

/* Try to acquire the table. 
 * First, find TableLockEntity and if not exists, register one.
 * Second, try to acquire the table lock.
 * After acquired the lock, wait unitl there is no other threads manipulating the table. 
 * At the end, acquire the table successfully and exclusively.
 * */
void try_acquire_table(char *table_name) {
    TableLockEntity *lock_entry = find_lock_entry(table_name);
    if (is_null(lock_entry)) {
        register_lock_entry(table_name);
        lock_entry = find_lock_entry(table_name);
    }
    
    /* Make sure TableLockEntity exists. */
    Assert(lock_entry);
    
    /* Try acquire exclusive lock, maybe block here. */
    acquire_exlock(lock_entry->entry_lock);
}

/* Try to release the table. */
void try_release_table(char *table_name) {

    TableLockEntity *lock_entry = find_lock_entry(table_name);

    /* Make sure exists. */
    assert_not_null(lock_entry, "Not found lock entry.");

    /* Release lock. */
    release_exlock(lock_entry->entry_lock);
}

