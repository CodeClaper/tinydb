/***************************** Local memory Mangager ****************************************** 
 * Auth:            JerryZhou 
 * Created:         2024/11/16 
 * Modify:          2024/11/16
 * Locataion:       src/memory/lodmem.c
 * Description:     This is the implement of mem for local memory.
 *********************************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lomgr.h"
#include "utils.h"
#include "mctx.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Alloc for local. */
void *lodalloc(size_t size) {
    void *ptr;
    pthread_mutex_lock(&mutex);
    ptr = MemoryContextAlloc(size);
    Assert(ptr != NULL);
    memset(ptr, 0, size);
    pthread_mutex_unlock(&mutex);
    return ptr;
}

/* Free for local. */
void lofree(void *ptr) {
     MemoryContextFree(ptr);
}

/* Realloc for local. */
void *lodrealloc(void *ptr, size_t size) {
    void *newptr = NULL;
    pthread_mutex_lock(&mutex);
    newptr = MemoryContextRealloc(ptr, size);
    pthread_mutex_unlock(&mutex);
    return newptr;
}

/* Strdup for local. */
char *lodstrdup(char *str) {
    char *newStr = NULL;
    if (is_null(str))
        return newStr;
    pthread_mutex_lock(&mutex);
    newStr = MemoryContextStrdup(str);
    pthread_mutex_unlock(&mutex);
    return newStr;
}
