#include <stdint.h>
#include "data.h"


/* Init Pager*/
void InitPager();

/* Get the page size. */
Size GetPageSize(char *table_name);

/* Get next unused page num. */
uint32_t GetNextUnusedPageNum(Table *table);
