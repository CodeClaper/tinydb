#include "data.h"

// init mem
void init_mem();

// system level mallocate
void *sys_malloc(size_t size);

// system level reallocate
void *sys_realloc(void *ptr, size_t size);

// database level  mallocate.
void *db_malloc(size_t size);

// database level mallocate.
void *db_malloc2(size_t size, char *data_type_name);

// database level reallocate
void *db_realloc(void *ptr, size_t size);

// database level mememory free.
void db_free(void *ptr);

// databese level mememory size.
size_t db_memesize();
