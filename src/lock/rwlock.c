/* 
 *====================================RWLock Manager ==============================================================
 *
 * RWLock manager provides a synchronization mechanism for concurrency scenes. 
 * TinyDb supports two level lock, table level lock and row level lock.
 * Besides, TinyDb supports two mode lock, read (shared) mode and write (exclusive) mode.
 * An exclusive or write lock gives a thread exclusive access for writing to the specified part of the file. 
 * While a write lock is in place, no other thread can lock that part of the file.
 * A shared or read lock prohibits any other thread from requesting a write lock on the specified part of the file. 
 * However, other thread can request read locks. 
 *=================================================================================================================
 * */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <rwlock.h>
#include "data.h"
#include "asserts.h"
#include "mmu.h"
#include "meta.h"
#include "pager.h"
#include "ltree.h"
#include "copy.h"
#include "free.h"
#include "refer.h"
#include "log.h"


volatile static LockTable *ltable; /* Store lock handle list. */

/* Initialise lock. */
void init_lock() {

    /* Initialise lock handle table. */
    ltable = instance(LockTable);
    ltable->head = NULL;
    ltable->tail = NULL;
    ltable->size = 0;
}

/* Compare two refer equals.
 * Three conditions: same table, same page and same cell. */
static bool compare(Refer *r1, Refer *r2) {
    return strcmp(r1->table_name, r2->table_name) == 0
            && r1->page_num == r2->page_num
            && r1->cell_num == r2->cell_num;
}


/* Register lock handle. */
static void register_lock_handle(LockHandle *lock_handle) {
    if (ltable->size == 0) {
        ltable->head = lock_handle;
        ltable->tail = lock_handle;
    } else {
        ltable->tail->next = lock_handle;
        ltable->tail = lock_handle;
    }
    ltable->size++;
}

/* Destroy lock handle. 
 * When lock handle has more than one thread in use, just decrease
 * When in use num is 1, destroy the lock handle. */
static bool destroy_lock_handle(LockHandle *lock_handle) {

    /* Destroy only when there is no thread in use. */
    if (lock_handle->shared > 1) {
        lock_handle->shared--;
        return true;
    }

    /* Maybe head. */
    if (ltable->head == lock_handle) {
        ltable->head = ltable->head->next;
        /* When size is 1, head and tail all become null. */
        if (ltable->size == 1)
            ltable->tail = ltable->head;
        ltable->size--;
        
        /* Destroy lock. */
        pthread_rwlock_destroy(&lock_handle->lock);
        /* Free memory. */
        lock_handle->next = NULL;
        free_lock_handle(lock_handle);
        return true;
    }

    /* current, previous lock handle. */
    LockHandle *current, *prev;
    current = ltable->head; 
    prev = ltable->head;

    /* Loop to check. */
    for (current = ltable->head ;current != NULL; prev = current, current = current->next) {
        if (current == lock_handle) {
            /* If current is tail, tail end back. */
            if (ltable->tail == current)
                ltable->tail = prev;
            /* Skip current*/
            prev->next = current->next; 
            ltable->size--;
            /* Destroy lock. */
            pthread_rwlock_destroy(&lock_handle->lock);
            /* Free memory. */
            current->next = NULL;
            free_lock_handle(current);
            return true;
        }
    }
    return false;
}

/* Generate new lock handle. */
static LockHandle *new_lock_handle(Refer *refer) {
    LockHandle *lock_handle = instance(LockHandle);
    memset(lock_handle, 0, sizeof(LockHandle));
    lock_handle->refer = copy_refer(refer);
    lock_handle->next = NULL;
    lock_handle->shared = 1;
    /* Register new lock handle. */
    register_lock_handle(lock_handle);
    return lock_handle;
}

/* Find lock handle. 
 * If fail, then generate new one. */
static LockHandle *find_lock_handle(Refer *refer) {

    /* Firstly, try to find in ltable. */
    LockHandle *current;
    for (current = ltable->head; current != NULL; current = current->next) {
        if (compare(refer, current->refer)) {
            current->shared++;
            return current;
        }
    }

    /* If cache missing, generate new one. */
    return new_lock_handle(refer);
}

/* Db read row level read mode or write lock. */
LockHandle *db_row_lock(Refer *refer, LockMode lock_mode) {

    int ret;

    /* Get the lock handle. */
    LockHandle *lock_handle = find_lock_handle(refer);

    switch(lock_mode) {
        case RD_MODE:
            ret = pthread_rwlock_rdlock(&lock_handle->lock);
            break;
        case WR_MODE:
            ret = pthread_rwlock_wrlock(&lock_handle->lock);
            break;
        default:
            db_log(ERROR, "Unknown Lock Mode.");
            break;
    }


    /* Check lock result. */
    assert_true(ret == 0, "Row lock error return %d, errno is %d and error message: %s", ret, errno, strerror(errno));

    return lock_handle;
}


/* Db read row level read mode or write lock. */
LockHandle *db_row_lock2(Cursor *cursor, LockMode lock_mode) { 
    Refer *refer = convert_refer(cursor);
    LockHandle *lock_handle = db_row_lock(refer, lock_mode);
    free_refer(refer);
    return lock_handle;
}

/* Db read row level unlock. */
void db_unlock(LockHandle *lock_handle) {

    /* Check not null. */
    assert_not_null(lock_handle, "Lock handle not allow to be null.\n");
    
    /* Unlock and check result. */
    assert_true(pthread_rwlock_unlock(&lock_handle->lock) == 0, "Unlock error, errno is %d and error message:  %s.\n", errno, strerror(errno));

    /* Destroy lock handle and check result. */
    assert_true(destroy_lock_handle(lock_handle), "Destroy lock handle fail.\n");
}

