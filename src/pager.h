#include "data.h"
//Open Pager
Pager *open_pager(char *table_file_path);
// Get page of a pager by page number.
void *get_page(Pager *pager, int page_num);
// flush page to disk
void flush_page(Pager *pager, uint32_t page_num);
