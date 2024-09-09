#include <stdint.h>
#include "data.h"

typedef struct FDescEntry{
    char table_name[MAX_TABLE_NAME_LEN];        /* Table Name */
    int file_descriptor;                        /* Table file descriptor. */
} FDescEntry;

/* Open Pager */
Pager *open_pager(char *table_file_path);

/* For mult-processor model, it will need reload the table file descriptor. */
void reload_file_descriptor(Pager *pager, char *table_name);

/* Get page of a pager by page number. */
void *get_page(char *table_name, Pager *pager, uint32_t page_num);

/* Flush page to disk. */
void flush_page(char *table_name, Pager *pager, uint32_t page_num);

/* Flush all to disk. */
void flush(char *table_name);
