#include <errno.h>
#include <pthread.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <strings.h>
#include <unistd.h>
#include "log.h"
#include "mem.h"
#include "defs.h"
#include "free.h"
#include "data.h"
#include "defs.h"
#include "timer.h"
#include "xlog.h"
#include "trans.h"
#include "asserts.h"

/* Log Level names */
static char* LOG_LEVEL_NAME_LIST[] = { "TRACE", "DEBUG", "INFO", "SUCCS", "WARN", "ERROR", "SYSERR", "TATAL", "PANIC" };

static char CurrentMessage[BUFF_SIZE] = {};

/* Save message to stack. */
static void save_stack_message(char *msg) {
    Assert(strlen(msg) < BUFF_SIZE);
    bzero(CurrentMessage, BUFF_SIZE);
    memcpy(CurrentMessage, msg, strlen(msg));
}


/* Get stack message. */
char *get_stack_message() {
    return CurrentMessage;
}


/* Flush log message to disk. */
static void flush_log(char* msg) {
    char log_path[BUFF_SIZE];
    char *sys_date = get_sys_time("%Y-%m-%d");
    sprintf(log_path, "%s%s.%s", conf->log_dir, sys_date, "log");
    FILE *file;
    file = fopen(log_path, "a");
    if (file == NULL) {
        fprintf(stderr, "Try to open log file '%s', error info: %s. \n", log_path, strerror(errno));
        exit(1);
    }
    fputs(msg, file);
    fclose(file);
    dfree(sys_date);
}

/* Db log. */
void db_log(LogLevel lev, char *format, ...) {

    /* Combinate message. */
    char message[BUFF_SIZE];
    va_list ap;
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    /* Only print higher level log. */
    if (lev >= conf->log_level) {
        char *sys_time = get_current_sys_time2(MICROSECOND);
        char buff[BUFF_SIZE * 2];
        sprintf(buff, "[%s][%d][%s]:\t%s\n", sys_time, getpid(), LOG_LEVEL_NAME_LIST[lev], message);
        fprintf(stdout, "%s", buff);
        flush_log(buff);
        dfree(sys_time);
    }

    /* According to LogLevel, there are diffent treatments. 
     * SUCCESS: statement exeucted successfully.
     * WARN:    for unexpected messages.
     * ERROR:   for expected error, abort current transaction, return to known state.
     * FATAL:   abort session.
     * PANIC:   for unexpected error, caused by system error, take down the server.
     * */
    switch(lev) {
        case SUCCESS:
        case WARN: {
            save_stack_message(message);
            break;
        }
        case ERROR: {

            /* Save message to stack. */
            save_stack_message(message);

            /* Auto rollback*/
            auto_rollback_transaction();

            /* Stop the process, goto stmt. */
            longjmp(errEnv, 1);
            break;
        }
        case SYS_ERROR: {

            /* Save message to stack. */
            save_stack_message(message);

            /* Stop the process, goto stmt. */
            longjmp(errEnv, 1);
            break;
        }
        case FATAL:
        case PANIC: {

            /* Save message to stack. */
            save_stack_message("System inner error.");

            exit(EXIT_FAILURE);
        }
        default:
            break;
    }
}

