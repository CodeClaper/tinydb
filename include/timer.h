#include "data.h"

/* Time Level. */
typedef enum { SECOND, MILLISECOND, MICROSECOND, NANOSECOND } TIME_LEVEL;

/* Get current system timestamp.
 * Supports four time level, SECOND, MILLISECOND, MICROSECOND, NANOSECOND. */
int64_t get_current_sys_time(TIME_LEVEL time_level);

/* Format time. */
char *format_time(char *format, time_t t);
