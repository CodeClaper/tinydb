#include <stdbool.h>

#ifdef DEBUG
#include "assert.h"
#define Assert(condition) assert(condition)
#else
#define Assert(condition) ((void)true)
#endif

/* Assert condition is true. */
void assert_true(bool condition, char *format, ...);

/* Assert condition is false. */
void assert_false(bool condition, char *format, ...);

/* Assert expression not null. */
void assert_not_null(void *express, char *format, ...);

/* Assert expression not null. */
void assert_null(void *express, char *format, ...);
