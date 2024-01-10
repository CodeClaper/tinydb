#include "data.h"

/* Generate new cursor. */
Cursor *new_cursor(Table *table, uint32_t page_num, uint32_t cell_num);

/* Convert to refer from cursor. */
Refer *convert_refer(Cursor *cursor);

/* Check if refer null. 
 * If page number is -1 and cell number is -1, it means refer null. */
bool refer_null(Refer *refer);

/* Update Refer. */
void update_refer(char *table_name, int32_t old_page_num, int32_t old_cell_num, int32_t new_page_num, int32_t new_cell_num);
