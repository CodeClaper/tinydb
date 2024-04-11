#include <errno.h>
#include <pthread.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"
#include "mmu.h"
#include "defs.h"
#include "free.h"
#include "data.h"
#include "defs.h"
#include "timer.h"
#include "xlog.h"
#include "trans.h"
#include "asserts.h"

/* Log Level names */
static char* LOG_LEVEL_NAME_LIST[] = { "TRACE", "DEBUG", "INFO", "SUCCS", "WARN", "ERROR", "TATAL", "PANIC" };

/* Lock */
static pthread_mutex_t mutex;

/* LogTable Buffer. */
static LogTable *ltable;


/* Initialise Log */
void init_log() {
    ltable = instance(LogTable);
    ltable->head = NULL;
    ltable->tail = NULL;
    ltable->size = 0;

    /* Initialise tmux. */
    pthread_mutex_init(&mutex, NULL);
}

/* Seach current pthread LogEntry. 
 * Return NULL if not found. */
static LogEntry *search_log_entry() {
    int64_t tid = pthread_self();
    LogEntry *current = ltable->head;
    while (current) {
        if (current->tid == tid)
            break;
        current = current->next;
    }
    return current;
}

/* Generate new LogEntry*/
static LogEntry *new_log_entry(char *msg) {
    LogEntry *entry = instance(LogEntry);
    entry->message = db_strdup(msg);
    entry->tid = pthread_self();
    entry->next = NULL;
    return entry;
}

/* Register new LogEntry. */
static void register_log_entry(LogEntry *entry) {
    pthread_mutex_lock(&mutex);

    if (ltable->size == 0) {
        ltable->head = entry;
        ltable->tail = entry;
        ltable->size++;
    } else {
        ltable->tail->next = entry;
        ltable->tail = entry;
        ltable->size++;
    }

    /* Unlock */
    pthread_mutex_unlock(&mutex);
}

static void destroy_log_entry() {
    assert_true(ltable->size > 0, "Log table error.");
    
    /*Lock*/
    pthread_mutex_lock(&mutex);

    int64_t tid = pthread_self();
    LogEntry *current = ltable->head;
    LogEntry *prev = ltable->head;
    
    /* Maybe is head. */
    if (current->tid == tid) {
        ltable->head = ltable->head->next;
        
        /* When size is one, head and tail all become NULL. */
        if (ltable->size == 1) 
            ltable->tail = ltable->head;

        free_log_entry(current);        
        ltable->size--;
    } else {
        /* Loop to check. */
        for (;current != NULL; prev = current, current = current->next) {
            if (current->tid == tid) {
                /* If tail, tail end back. */
                if (current == ltable->tail) 
                    ltable->tail = prev;

                prev->next = current->next;
                free_log_entry(current);
                ltable->size--;
                break;
            }
        }
    }

    /* Unlock */
    pthread_mutex_unlock(&mutex);
}

/* Store log message. */
static void store_log_msg(char *msg) {
    LogEntry *entry = search_log_entry();
    if (entry) {
        /* If aleady exists LogEntry, replace message, keep the latest message. */
        char *old_msg = entry->message;
        entry->message = db_strdup(msg);
        db_free(old_msg);
    } else 
        register_log_entry(new_log_entry(msg));
}

/* Get log message. */
char *get_log_msg() {
    char *msg = NULL;
    LogEntry *entry = search_log_entry();
    if (entry) {
        msg = db_strdup(entry->message); 
        destroy_log_entry();
    }
    return msg;
}

/* Get system time by format. */
static char* get_sys_time(char *format) {
    time_t t_now;
    struct tm *tm_now;
    time(&t_now);
    return format_time(format, t_now);
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
void db_log(LogLevel lev, char *format, ...) {

    /* Combinate message. */
    char message[BUFF_SIZE];
    va_list ap;
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    /* Only print higher level log. */
    if (lev >= conf->log_level) {
        char *sys_time = get_sys_time("%Y-%m-%d %H:%M:%S");
        char buff[BUFF_SIZE * 2];
        sprintf(buff, "[%s][%ld][%s]:\t%s\n", sys_time, pthread_self(), LOG_LEVEL_NAME_LIST[lev], message);
        fprintf(stdout, "%s", buff);
        flush_log(buff);
        db_free(sys_time);
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
        case WARN:
            store_log_msg(message);
            break;
        case ERROR:
            store_log_msg(message);
            /* Auto rollback*/
            if (conf->auto_rollback) {
                TransactionHandle *transaction = find_transaction();
                if (transaction && !transaction->auto_commit)
                    execute_roll_back();
            }
            /* Stop the process, goto stmt. */
            longjmp(errEnv, 1);
            break;
        case SYS_ERROR:
            store_log_msg(message);
            /* Stop the process, goto stmt. */
            longjmp(errEnv, 1);
            break;
        case FATAL:
        case PANIC:
            exit(1);
        default:
            break;
    }
}

