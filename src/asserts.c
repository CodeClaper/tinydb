#include "asserts.h"

/* The assert module support some common determination of whether the condition is established. */

/* Assert condition is true. */
void assert_true(bool condition, char *format, ...) {
    if (!condition) {
        va_list ap;
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
        exit(1);
    }
}

/* Assert condition is false. */
void assert_false(bool condition, char *format, ...) {
    if (condition) {
        va_list ap;
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
        exit(1);
    }
}

/* Assert expression not null. */
void assert_not_null(void *express, char *format, ...) {
    if (!express) {
        va_list ap;
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
        exit(1);
    }
}

/* Assert expression not null. */
void assert_null(void *express, char *format, ...) {
    if (express) {
        va_list ap;
        va_start(ap, format);
        vfprintf(stderr, format, ap);
        va_end(ap);
        exit(1);
    }
}
