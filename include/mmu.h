#include "data.h"

/* Initialise mem */
void init_mem();

/* System level mallocate */
void *sys_malloc(size_t size);

/* System level reallocate. */
void *sys_realloc(void *ptr, size_t size);

/* Database level mallocate. */
void *db_malloc(size_t size, SysDataType stype);

/* Database level reallocate */
void *db_realloc(void *ptr, size_t size);

/* Database level db_strdup. */
char *db_strdup(char *str);

/* Database level mememory free. */
void db_free(void *ptr);

/* Databese level mememory size. */
size_t db_memesize();

/* Get mtable capacity. */
uint32_t mtable_capacity();

/* Get metable used num. */
uint32_t mentry_num();
