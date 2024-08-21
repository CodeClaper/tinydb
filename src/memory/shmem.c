/***************************** Shared Memory Module *****************************************
 * Auth:        JerryZhou
 * Created:     2024/08/13
 * Modify:      2024/08/13
 * Locataion:   src/memory/shmem.c
 * Description: The shared memory manager is a component of IPC (Inter process commnuication).
 * 
*********************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include "shmem.h"
#include "spinlock.h"
#include "utils.h"
#include "log.h"

static ShmemHeader *shmrd;

static s_lock lock;

static void *BaseEnd;
static void *BaseStart;

#define SHMEM_SIZE 1024 * 1024 * 1024 * 1  // shared memory 1GB. 

static void create_shmem();

/* Init the shared memory. */
void init_shmem() {
    init_spin_lock(&lock);
    create_shmem();
    BaseStart = shmrd;
    BaseEnd = shmrd + shmrd->total_size;
}

/* Create Shmem. */
static void create_shmem() {
    ShmemHeader init_shmrd;
    void *shm_ptr = mmap(NULL, SHMEM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if (shm_ptr == MAP_FAILED) 
        db_log(PANIC, "Try to create shared memory fail.");
    bzero(shm_ptr, SHMEM_SIZE);
        
    /* Init. */
    init_shmrd.total_size = SHMEM_SIZE;
    init_shmrd.offset = sizeof(ShmemHeader);
    
    memcpy(shm_ptr, &init_shmrd, sizeof(ShmemHeader));
    shmrd = shm_ptr;
}

/* Allocate memory in Shmem for inner.. */
static void *shmem_alloc_inner(size_t size) {
    void *ptr;

    Assert(shmrd);

    acquire_spin_lock(&lock);

    size_t current_offset = shmrd->offset + size;
    if (current_offset <= shmrd->total_size) 
    {
        ptr = shmrd + shmrd->offset;   
        shmrd->offset += size;
    }
    else 
        ptr = NULL;

    release_spin_lock(&lock);

    return ptr;
}

/* Allocate memory in Shmem. */
void *shmem_alloc(size_t size) {
    void *ptr = shmem_alloc_inner(size);
    if (is_null(ptr))
        db_log(ERROR, "Out of shared memory.");
    return ptr;
}

/* Check if addess is valid shared memory. */
bool shmem_addr_valid(void *ptr) {
    return (ptr >= BaseStart) && (ptr < BaseEnd);
}
