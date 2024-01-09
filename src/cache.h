#include "data.h"

/* Initialise table cache. */
void init_table_cache();

/* Add cache table. */
void add_table_cache(Table *table);

/* Find cache table by name, retrurn null if not exist. */
Table *find_table_cache(char *table_name);

/* Remove table cache. */
void *remove_table_cache(char *table_name);
