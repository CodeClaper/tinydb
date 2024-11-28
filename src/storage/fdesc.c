#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "fdesc.h"
#include "data.h"
#include "mmgr.h"
#include "table.h"
#include "utils.h"
#include "log.h"

/* FDescEntry cache. */
static List *F_DESC_LIST = NIL;

/* Initilise fdesc. */
void init_fdesc() {
    F_DESC_LIST = create_list(NODE_VOID);
}

/* Find file descriptor in F_DESC_LIST. 
 * Return file descriptor or -1 if not found.
 * */
static int find_fdesc(char *table_name) {
    Assert(F_DESC_LIST != NIL);
    
    ListCell *lc;
    foreach(lc, F_DESC_LIST) {
        FDescEntry *entry = lfirst(lc);
        if (streq(entry->table_name, table_name))
            return entry->desc;
    }

    return -1;
}


/* Register fdesc. */
static void register_fdesc(char *table_name, int desc) {
    Assert(F_DESC_LIST != NIL);

    /* Switch to CACHE_MEMORY_CONTEXT. */
    MemoryContext oldcontext = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    FDescEntry *entry = instance(FDescEntry);
    entry->desc = desc;
    strcpy(entry->table_name, table_name);
    append_list(F_DESC_LIST, entry);

    /* Recover the MemoryContext. */
    MemoryContextSwitchTo(oldcontext);
}

/* Unregister fdesc. */
void unregister_fdesc(char *table_name) {
    Assert(!is_empty(table_name));

    /* Switch to CACHE_MEMORY_CONTEXT. */
    MemoryContext oldcontext = CURRENT_MEMORY_CONTEXT;
    MemoryContextSwitchTo(CACHE_MEMORY_CONTEXT);

    ListCell *lc;
    foreach(lc, F_DESC_LIST) {
        FDescEntry *entry = lfirst(lc);
        if (streq(entry->table_name, table_name)) {
            list_delete(F_DESC_LIST, entry);
            break;
        }
    }

    /* Recover the MemoryContext. */
    MemoryContextSwitchTo(oldcontext);
}


/* Load file descriptor. 
 * Notice, if file desc not register, need close it manually.
 * */
int load_file_desc(char *file_path) {
    int desc= open(file_path, O_RDWR, S_IRUSR | S_IWUSR);
    if (desc == -1) 
        db_log(
            PANIC,
            "Open table file %d fail: %s.", 
            file_path, 
            strerror(errno)
        );
    return desc;
}

/* Get file descriptor. */
int get_file_desc(char *table_name) {
    Assert(!is_empty(table_name));

    /* Fistly find in F_DESC_LIST. */
    int desc = find_fdesc(table_name);

    /* If missing cache.*/
    if (desc == -1) {
        char *file_path = table_file_path(table_name);
        desc = load_file_desc(file_path);
        register_fdesc(table_name, desc);
    }

    return desc;
}

