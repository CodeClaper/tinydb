/***************************** Shared Memory Module *****************************************
 * Auth:        JerryZhou
 * Created:     2024/09/09
 * Modify:      2024/09/09
 * Locataion:   src/memory/lomem.c
 * 
*********************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "lomem.h"
#include "utils.h"
#include "log.h"

static LoMemHeader *lomrd = NULL;

/* Create Local Memory. */
static void create_local_memory() {
    
    LoMemHeader init_lmhdr;

    void *ptr = malloc(INIT_LOMEM_SIZE);

    if (is_null(ptr))
        db_log(PANIC, "Out of local memory.");

    bzero(ptr, INIT_LOMEM_SIZE);

    /* Init header.*/
    init_lmhdr.total_size = INIT_LOMEM_SIZE;
    init_lmhdr.offset = sizeof(LoMemHeader);

    memcpy(ptr, &init_lmhdr, sizeof(LoMemHeader));

    lomrd = ptr;
}


static void *lomem_alloc_inner(size_t size) {
    void *ptr;

    Assert(lomrd);

    size_t current_offset = lomrd->offset + size;
    if (current_offset <= lomrd->total_size)
    {
        ptr = (void *) ((char *) lomrd + lomrd->offset);
        lomrd->offset = current_offset;
    }
    else
        ptr = NULL;

    return ptr;
}

void *lomem_alloc(size_t size) {
    
    if (is_null(lomrd))
        create_local_memory();

    void *ptr = lomem_alloc_inner(size);
    if (is_null(ptr))
        db_log(ERROR, "Out of local memory");
    return ptr;
}



/* Destroy Local Memory. */
void destroy_local_memory() {

    Assert(lomrd);

    free(lomrd);

    lomrd = NULL;
}
