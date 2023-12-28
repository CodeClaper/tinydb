/**
* ======================================== Timer =======================================================
* The timer module supports some funcitons about time, like get_current_sys_time(TIME_LEVEL time_level).
* ======================================================================================================
*/

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "timer.h"
#include "data.h"
#include "log.h"

/* Get current system timestamp.
 * Return current system timestamp, and -1 if fail.
 * Supports four time level, SECOND, MILLISECOND, MICROSECOND, NANOSECOND. */
int64_t get_current_sys_time(TIME_LEVEL time_level) {

    int64_t value;
    char time_str[32];
    struct timespec tv;
    if (clock_gettime(CLOCK_REALTIME, &tv)) {
        db_error("Generate next xid error.\n");
        return -1;
    }

    switch(time_level) {
        case SECOND:
            value = tv.tv_sec;
        case MILLISECOND:
            sprintf(time_str, "%ld.%.3ld", tv.tv_sec, tv.tv_nsec / 1000000);
            value = round(atof(time_str) * 1e3);
            break;
        case MICROSECOND:
            sprintf(time_str, "%ld.%.6ld", tv.tv_sec, tv.tv_nsec / 1000);
            value = round(atof(time_str) * 1e6);
            break;
        case NANOSECOND:
            sprintf(time_str, "%ld.%.9ld", tv.tv_sec, tv.tv_nsec);
            value = round(atof(time_str) * 1e9);
            break;
    }
    return value;
}
