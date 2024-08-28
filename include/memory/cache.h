#include "data.h"
#include <stdbool.h>

/* Initialise table cache. */
void init_table_cache();

/* Save table cache. */
void save_table_cache(Table *table);

/* Find cache table by name, retrurn null if not exist. */
Table *find_table_cache(char *table_name);

/* Remove table cache. */
void remove_table_cache(char *table_name);

/* Synchronous page data. */
bool sync_page(char *table_name, uint32_t page_num, void *page);

/* Synchronous page size. */
bool sync_page_size(char *table_name, uint32_t page_size);
