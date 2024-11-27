/****************************** The memory manager *****************************************
 * Auth:        JerryZhou
 * Created:     2024/08/14
 * Modify:      2024/08/14
 * Locataion:   src/memory/mem.c
 * Description: The memory manager is the abstract for local memory and share memory manager.
*********************************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mmgr.h"
#include "shmgr.h"
#include "lomgr.h"
#include "list.h"
#include "spinlock.h"
#include "asserts.h"
#include "utils.h"

/*
 * Current Memory Type.
 */
static MemType type = MEM_LOCAL;

static MemMethods mem_methods[] = {
    /* Local. */
    [MEM_LOCAL].dalloc = lodalloc,
    [MEM_LOCAL].dfree = lofree,
    [MEM_LOCAL].drealloc = lodrealloc,
    [MEM_LOCAL].dstrdup = lodstrdup,
    /* Shared. */
    [MEM_SHARED].dalloc = shdalloc,
    [MEM_SHARED].dfree = shdfree,
    [MEM_SHARED].drealloc = shdrealloc,
    [MEM_SHARED].dstrdup = shdstrdup,
};

/* Swith Shared Memory. */
inline void switch_shared() {
    type = MEM_SHARED;
}

/* Switch Local Memory. */
inline void switch_local() {
    type = MEM_LOCAL;
}

/* Allocate memory. */
inline void *dalloc(size_t size) {
    return mem_methods[type].dalloc(size);
}

/* Free memory. */
inline void dfree(void *ptr) {
    mem_methods[type].dfree(ptr);
}

/* Reallocate memory. */
inline void *drealloc(void *ptr, size_t size) {
    return mem_methods[type].drealloc(ptr, size);
}

/* Strdup. */
inline char *dstrdup(char *str) {
    return mem_methods[type].dstrdup(str);
}
