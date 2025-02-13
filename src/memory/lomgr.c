/***************************** Local memory Mangager ****************************************** 
 * Auth:            JerryZhou 
 * Created:         2024/11/16 
 * Modify:          2024/11/16
 * Locataion:       src/memory/lodmem.c
 * Description:     This is the implement of mem for local memory.
 *********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lomgr.h"
#include "utils.h"
#include "mctx.h"
#include "spinlock.h"

/*
 * Sync lock.
 */
static s_lock slock = SPIN_UN_LOCKED_STATUS;

/* Alloc for local. */
void *lodalloc(size_t size) {
    void *ptr;
    // acquire_spin_lock(&slock);
    ptr = MemoryContextAlloc(size);
    Assert(ptr != NULL);
    memset(ptr, 0, size);
    // release_spin_lock(&slock);
    return ptr;
}

/* Free for local. */
void lofree(void *ptr) {
    // acquire_spin_lock(&slock);
    MemoryContextFree(ptr);
    // release_spin_lock(&slock);
}

/* Realloc for local. */
void *lodrealloc(void *ptr, size_t size) {
    void *newptr = NULL;
    //acquire_spin_lock(&slock);
    newptr = MemoryContextRealloc(ptr, size);
    // release_spin_lock(&slock);
    return newptr;
}

/* Strdup for local. */
char *lodstrdup(char *str) {
    char *newStr = NULL;
    if (is_null(str))
        return newStr;
    // acquire_spin_lock(&slock);
    newStr = MemoryContextStrdup(str);
    //release_spin_lock(&slock);
    return newStr;
}
