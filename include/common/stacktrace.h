#include <execinfo.h>
#include <signal.h>
#include "log.h"

#ifndef STACKTRACE_H
#define STACKTRACE_H

/* Log the stacktrace. */
static void print_stacktrace() {
    void *array[10];
    size_t size = backtrace(array, 10);
    char **ret = backtrace_symbols(array, size);
	if(ret == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}
    for (int i = 0; i < size; i++) {
        db_log(SYS_ERROR, "\t%s", ret[i]);
    }
    free(ret); 
}

static void handler(int sig) {
	switch(sig) {
		case SIGABRT:
			db_log(SYS_ERROR, "Caught SIGABRT: usually caused by an abort() or assert().");
			break;
		case SIGFPE:
			db_log(SYS_ERROR, "Caught SIGFPE: arithmetic exception, such as divide by zero.");
			break;
		case SIGILL:
			db_log(SYS_ERROR, "Caught SIGILL: illegal instruction.");
			break;
		case SIGINT:
			db_log(SYS_ERROR, "Caught SIGINT: interactive attention signal, probably a ctrl+c.");
			break;
		case SIGSEGV:
			db_log(SYS_ERROR, "Caught SIGSEGV: segfault.");
			break;
		case SIGTERM:
		default:
			db_log(SYS_ERROR, "Caught SIGTERM: a termination request was sent to the program.");
			break;
	}
    print_stacktrace();
    exit(EXIT_FAILURE);
}

/* Set signal handler. */
static void set_signal_handler() {
	signal(SIGABRT, handler);
	signal(SIGFPE,  handler);
	signal(SIGILL,  handler);
	signal(SIGINT,  handler);
	signal(SIGSEGV, handler);
	signal(SIGTERM, handler);
}

#endif
