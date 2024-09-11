#include "data.h"

typedef struct FDescEntry{
    int  desc;                              /* Table file descriptor. */
    char table_name[MAX_TABLE_NAME_LEN];    /* Table Name */
} FDescEntry;


/* Initilise fdesc. */
void init_fdesc();

/* Load file descriptor. */
int load_file_desc(char *file_path);

/* Get file descriptor. */
int get_file_desc(char *table_name);
