#include "data.h"

/* Initialise table buffer. */
void init_table_buffer();

/* Find table in table buffer. */
Table *find_table_buffer(char *table_name);

/* Remove TableBufferEntry. */
bool remove_table_buffer(); 

/* Clear table buffer. */
void clear_table_buffer(char *table_name);
