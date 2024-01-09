#include "data.h"


/* Generate new refer. */
Refer *new_refer(char *table_name, uint32_t page_num, uint32_t cell_num);

/* Generate new cursor. */
Cursor *new_cursor(Table *table, uint32_t page_num, uint32_t cell_num);

/* Convert to refer from cursor. */
Refer *convert_refer(Cursor *cursor);

/* Update Refer. */
void update_refer(char *table_name, uint32_t old_page_num, uint32_t old_cell_num, uint32_t new_page_num, uint32_t new_cell_num);
