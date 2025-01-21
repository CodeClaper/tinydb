#include <stdint.h>
#include "data.h"

/* Open Pager */
Pager *open_pager(char *table_name);

/* Get page of a pager by page number. */
void *get_page(char *table_name, Pager *pager, uint32_t page_num);

/* Make page dirty. 
 * This function will not flush page to disk, 
 * just make page dirty. */
void make_page_dirty(char *table_name, Pager *pager, uint32_t page_num);

/* Flush all to disk. */
void flush(char *table_name);
