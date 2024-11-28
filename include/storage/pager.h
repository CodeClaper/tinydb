#include <stdint.h>
#include "data.h"

/* Open Pager */
Pager *open_pager(char *table_name);

/* Get page of a pager by page number. */
void *get_page(char *table_name, Pager *pager, uint32_t page_num);

/* Flush page to disk. */
void flush_page(char *table_name, Pager *pager, uint32_t page_num);

/* Flush all to disk. */
void flush(char *table_name);
