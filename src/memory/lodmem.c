/***************************** Local memory Module ****************************************** 
 * Auth:            JerryZhou 
 * Created:         2024/11/16 
 * Modify:          2024/11/16
 * Locataion:       src/memory/lodmem.c
 * Description:     This is the implement of mem for local memory.
 *********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "lodmem.h"
#include "utils.h"

/* Alloc for local. */
void *lodalloc(size_t size) {
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

/* Free for local. */
void lofree(void *ptr) {
    free(ptr);
}

/* Realloc for local. */
void *lodrealloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

/* Strdup for local. */
char *lodstrdup(char *str) {
    if (is_null(str))
        return NULL;
    return strdup(str);
}
