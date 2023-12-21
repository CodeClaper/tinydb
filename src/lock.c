#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "data.h"
#include "asserts.h"
#include "mmu.h"
#include "node.h"
#include "meta.h"
#include "pager.h"
#include "node.h"
#include "copy.h"
#include "free.h"

/* 
 *====================================Lock Manager ==============================================================
 *
 * Lock manager provides a synchronization mechanism for concurrency scenes. 
 * TinyDb supports two level lock, table level lock and row level lock.
 * Besides, TinyDb supports two mode lock, read (shared) mode and write (exclusive) mode.
 * An exclusive or write lock gives a thread exclusive access for writing to the specified part of the file. 
 * While a write lock is in place, no other thread can lock that part of the file.
 * A shared or read lock prohibits any other thread from requesting a write lock on the specified part of the file. 
 * However, other thread can request read locks. 
 *=================================================================================================================
 * */

volatile static LockTable *ltable; /* Store lock state list. */

/* Initialise lock. */
void init_lock() {

    /* Initialise lock state table. */
    ltable = db_malloc2(sizeof(LockTable), "LockTable");
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


/* Register lock state. */
static void register_lock_state(LockState *lock_state) {
    if (ltable->size == 0) {
        ltable->head = lock_state;
        ltable->tail = lock_state;
    } else {
        ltable->tail->next = lock_state;
        ltable->tail = lock_state;
    }
    ltable->size++;
}

/* Destroy lock state. 
 * When lock state has more than one thread in use, just decrease
 * When in use num is 1, destroy the lock state. */
static bool destroy_lock_state(LockState *lock_state) {
    

    /* Destroy only when there is no thread in use. */
    if (lock_state->in_use > 1) {
        lock_state->in_use--;
        return true;
    }

    /* Maybe head. */
    if (ltable->head == lock_state) {
        ltable->head = ltable->head->next;
        /* When size is 1, head and tail all becomes null. */
        if (ltable->size == 1)
            ltable->tail = ltable->head;
        ltable->size--;
        
        /* Destroy lock. */
        pthread_rwlock_destroy(&lock_state->lock);
        /* Free memory. */
        lock_state->next = NULL;
        free_lock_state(lock_state);
        return true;
    }

    /* current, previous lock state. */
    LockState *current, *prev;
    current = ltable->head; 
    prev = ltable->head;

    /* Loop to check. */
    while(current != NULL) {
        if (current == lock_state) {
            /* If current is tail, tail end back. */
            if (ltable->tail == current)
                ltable->tail = prev;
            /* Skip current*/
            prev->next = current->next; 
            ltable->size--;
            /* Destroy lock. */
            pthread_rwlock_destroy(&lock_state->lock);
            /* Free memory. */
            current->next = NULL;
            free_lock_state(current);
            return true;
        }
        prev = current; 
        current = current->next;
    }
    return false;
}

/* Generate new lock state. */
static LockState *new_lock_state(Refer *refer) {
    LockState *lock_state = db_malloc2(sizeof(LockState), "LockState");
    memset(lock_state, 0, sizeof(LockState));
    lock_state->refer = copy_refer(refer);
    lock_state->next = NULL;
    lock_state->in_use = 1;
    /* register new lock state. */
    register_lock_state(lock_state);
    return lock_state;
}

/* Find lock state. 
 * If fail, then generate new one. */
static LockState *find_lock_state(Refer *refer) {

    /* Firstly, try to find in ltable. */
    LockState *current;
    for (current = ltable->head; current != NULL; current = current->next) {
        if (compare(refer, current->refer)) {
            current->in_use++;
            return current;
        }
    }

    /* If cache missing, generate new one. */
    return new_lock_state(refer);
}

/* Db read row level read mode or write lock. */
LockState *db_row_lock(Refer *refer, LockMode lock_mode) {

    int ret;

    /* Get the lock state. */
    LockState *lock_state = find_lock_state(refer);

    switch(lock_mode) {
        case RD_MODE:
            ret = pthread_rwlock_rdlock(&lock_state->lock);
            break;
        case WR_MODE:
            ret = pthread_rwlock_wrlock(&lock_state->lock);
            break;
    }

    /* Check lock result. */
    assert_true(ret == 0, "Row lock error, errno is %d and error message: %s", errno, strerror(errno));

    return lock_state;
}

/* Db read row level unlock. */
void db_unlock(LockState *lock_state) {

    /* Check not null. */
    assert_not_null(lock_state, "Lock state not allow to be null.\n");
    
    /* Unlock and check result. */
    assert_true(pthread_rwlock_unlock(&lock_state->lock) == 0, "Unlock error, errno is %d and error message:  %s.\n", errno, strerror(errno));

    /* Destroy lock state and check result. */
    assert_true(destroy_lock_state(lock_state), "Destroy lock state fail.\n");
}

