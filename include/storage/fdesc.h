#include "data.h"

typedef int FDesc;

/* 
 * FDescEntry.
 * Store the relation of fdesc and table.
 */
typedef struct FDescEntry {
    FDesc desc;                              /* Table file descriptor. */
    char  table_name[MAX_TABLE_NAME_LEN];    /* Table Name */
} FDescEntry;


/* Initilise fdesc. */
void init_fdesc();

/* Unregister fdesc. */
void unregister_fdesc(char *table_name);

/* Get file descriptor. 
 * Fistly find in F_DESC_LIST.
 * If missing, load file descriptor and register it. */
FDesc get_file_desc(char *table_name);
