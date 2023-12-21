#include <stdint.h>
#include <string.h>
#include "data.h"
#include "mmu.h"

/* Generate new refer. */
Refer *new_refer(char *table_name, uint32_t page_num, uint32_t cell_num) {
    Refer *refer = db_malloc2(sizeof(Refer), "Refer");
    strcpy(refer->table_name, table_name);
    refer->page_num = page_num;
    refer->cell_num = cell_num;
    return refer;
}

/* Convert to refer from cursor. */
Refer *convert_refer(Cursor *cursor) {
    if (cursor == NULL) return NULL;
    
    /* Generate new refer. */
    Refer *refer = db_malloc2(sizeof(Refer), "Refer");
    strcpy(refer->table_name, cursor->table->meta_table->table_name);
    refer->page_num = cursor->page_num;
    refer->cell_num = cursor->cell_num;
    return refer;
}

