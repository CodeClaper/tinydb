/****************************** The memory manager *****************************************
 * Auth:        JerryZhou
 * Created:     2024/08/14
 * Modify:      2024/08/14
 * Locataion:   src/memory/mem.c
 * Description: The memory manager is the abstract for local memory and share memory manager.
*********************************************************************************************/
#include <pthread.h>
#include "mmgr.h"
#include "shmgr.h"
#include "lomgr.h"

/*
 * Current Memory Type.
 */
static MemType type = MEM_LOCAL;

/*
 * Current MemMode. 
 */
static MemMode mode = MM_NORMAL;

/*
 * Recorder which use in parallel compute mode.
 */
static MemTypeRecord recorders[100];

/*
 * Workers Size.
 */
static int workerSize;


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


void StartParallelComputeMode(pthread_t workers[], int workerNum) {
    mode = MM_PARALLEL_COMPUTE;
    for (int i = 0; i < workerNum; i++) {
        recorders[i].type = MEM_LOCAL;
        recorders[i].worker = &workers[i];
    }
    workerSize = workerNum;
}

void EndParallelComputeMode() {
    mode = MM_NORMAL;
}

static MemTypeRecord *FindRecord() {
    Assert(mode == MM_PARALLEL_COMPUTE);
    for (int i = 0; i < workerSize; i++) {
        MemTypeRecord *recorder = &recorders[i];
        if (*recorder->worker == pthread_self())
            return recorder;
    }
    return NULL;
}

static MemType FindType() {
    switch (mode) {
        case MM_NORMAL:
            return type;
        case MM_PARALLEL_COMPUTE: {
            MemTypeRecord *recorder = FindRecord();
            Assert(recorder);
            return recorder->type;
        }
        default: {
            perror("Unknown MemMode");
            exit(1);
        }
    }
}

/* Swith Shared Memory. */
inline void switch_shared() {
    switch (mode) {
        case MM_NORMAL: {
            type = MEM_SHARED;
            break;
        }
        case MM_PARALLEL_COMPUTE: {
            MemTypeRecord *recorder = FindRecord();
            Assert(recorder);
            recorder->type = MEM_SHARED;
            break;
        }
        default: {
            perror("Unknown MemMode");
            exit(1);
        }
    }
}

/* Switch Local Memory. */
inline void switch_local() {
    switch (mode) {
        case MM_NORMAL: {
            type = MEM_LOCAL;
            break;
        }
        case MM_PARALLEL_COMPUTE: {
            MemTypeRecord *recorder = FindRecord();
            Assert(recorder);
            recorder->type = MEM_LOCAL;
            break;
        }
        default: {
            perror("Unknown MemMode");
            exit(1);
        }
    }
}


bool in_shared_memory() {
    return FindType() == MEM_SHARED;
}

bool in_local_memory() {
    return FindType() == MEM_LOCAL;
}

/* Allocate memory. */
inline void *dalloc(size_t size) {
    return mem_methods[FindType()].dalloc(size);
}

/* Free memory. */
inline void dfree(void *ptr) {
    mem_methods[FindType()].dfree(ptr);
}

/* Reallocate memory. */
inline void *drealloc(void *ptr, size_t size) {
    return mem_methods[FindType()].drealloc(ptr, size);
}

/* Strdup. */
inline char *dstrdup(char *str) {
    return mem_methods[FindType()].dstrdup(str);
}
