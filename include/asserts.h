#include <stdbool.h>

/* Assert condition is true. */
void assert_true(bool condition, char *format, ...);

/* Assert condition is false. */
void assert_false(bool condition, char *format, ...);

/* Assert expression not null. */
void assert_not_null(void *express, char *format, ...);

/* Assert expression not null. */
void assert_null(void *express, char *format, ...);
