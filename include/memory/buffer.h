#include "data.h"

/* Initialise table buffer. */
void init_table_buffer();

/* Find table in table buffer. */
Table *find_table_buffer(char *table_name);

/* Clear TableBufferEntry. */
bool clear_table_buffer(); 

/* Remove table buffer. */
void remove_table_buffer(char *table_name);
