#include <stdbool.h>
#include "data.h"

/* Initialise table cache. */
void init_table_cache();

/* Save table cache. */
void save_table_cache(Table *table);

/* find out if exists table in caceh. */
bool exist_table_in_cache(char *table_name);

/* Find cache table by name, retrurn null if not exist. */
Table *find_table_cache(char *table_name);

/* Remove table cache. */
void remove_table_cache(char *table_name);
