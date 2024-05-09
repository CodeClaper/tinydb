#include "data.h"

#define instance(_type_)  ((_type_ *) db_malloc(sizeof(_type_), #_type_))

/* Initialise mem */
void init_mmu();

/* System level mallocate */
void *sys_malloc(size_t size);

/* System level reallocate. */
void *sys_realloc(void *ptr, size_t size);

/* System level free. */
void sys_free(void *ptr);

/* Database level mallocate. */
void *db_malloc(size_t size, char *stype);

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
