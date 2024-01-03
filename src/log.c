#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "log.h"
#include "session.h"
#include "mmu.h"
#include "lock.h"
#include "data.h"
#include "defs.h"
#include "misc.h"

static char* LOG_LEVEL_NAME_LIST[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR" };

/* Get system time by format. */
static char* get_sys_time(char *format) {
    char *sys_time = db_malloc2(BUFF_SIZE, "String");
    time_t t_now;
    struct tm *tm_now;
    time(&t_now);
    tm_now = localtime(&t_now);
    strftime(sys_time, BUFF_SIZE, format, tm_now);
    return sys_time;
}

/* Flush log message to disk. */
static void flush_log(char* msg) {
    char log_path[BUFF_SIZE];
    char *sys_date = get_sys_time("%Y-%m-%d");
    sprintf(log_path, "%s%s.%s", conf->log_dir, sys_date, "log");
    FILE *file;
    file = fopen(log_path, "a");
    if (file == NULL) {
        fprintf(stderr, "Try to open log file '%s' error, errno %d. \n", log_path, errno);
        exit(1);
    }
    fputs(msg, file);
    fclose(file);
    db_free(sys_date);
}

/* Db log. */
static void db_log(char *msg, LogLevel level) {

    /* Only print higher level log. */
    if (level >= conf->log_level) {
        char *sys_time = get_sys_time("%Y-%m-%d %H:%M:%S");
        char buff[BUFF_SIZE];
        sprintf(buff, "[%s][%ld][%s]:\t%s\n", sys_time, pthread_self(), LOG_LEVEL_NAME_LIST[level], msg);
        fprintf(stdout, "%s", buff);
        flush_log(buff);
        db_free(sys_time);
    }
}

/* Db log for error level. */
void db_error(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    db_log(buff, ERROR_LEVLE);
    va_end(ap);
}

/* Db log for warn level. */
void db_warn(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    db_log(buff, WARN_LEVEL);
    va_end(ap);
}

/* Db log for info level. */
void db_info(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    db_log(buff, INFO_LEVEL);
    va_end(ap);
}

/* Db log for debug level. */
void db_debug(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    db_log(buff, DEBUG_LEVEL);
    va_end(ap);
}

/* Db log for trace level. */
void db_trace(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    db_log(buff, TRACE_LEVEL);
    va_end(ap);
}
