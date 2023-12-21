#include "data.h"

/* Generate new refer. */
Refer *new_refer(char *table_name, uint32_t page_num, uint32_t cell_num);

/* Convert to refer from cursor. */
Refer *convert_refer(Cursor *cursor);
