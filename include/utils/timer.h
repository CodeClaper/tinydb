#include "data.h"

/* Time Level. */
typedef enum { SECOND, MILLISECOND, MICROSECOND, NANOSECOND } TIME_LEVEL;

/* Get current system timestamp.
 * Supports four time level, SECOND, MILLISECOND, MICROSECOND, NANOSECOND. */
int64_t get_current_sys_time(TIME_LEVEL time_level);

/* Get system time for ms level. 
 * Supports four time level, SECOND, MILLISECOND, MICROSECOND, NANOSECOND. */
char *get_current_sys_time2(TIME_LEVEL level);


/* Get system time by format. */
char* get_sys_time(char *format);


/* Format time. */
char *format_time(char *format, time_t t);

/* Time span. */
double time_span(struct timeval end_time, struct timeval start_time);
