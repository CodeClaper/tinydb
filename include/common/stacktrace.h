#include <execinfo.h>
#include <signal.h>
#include "defs.h"
#include "log.h"

#ifndef STACKTRACE_H
#define STACKTRACE_H

/* Print stacktrace with addr2line. 
 * Return 1 if success, otherwise return 0.
 * */
static int print_stacktrace_addr2line(const void *addr) {
	char addr2line_cmd[512] = {0};
    sprintf(addr2line_cmd,"addr2line -f -e %.256s %p", program_name, addr); 

	FILE *fp;
	char outLine1[1035];
	char outLine2[1035];

	/* Open the command for reading. */
	fp = popen(addr2line_cmd, "r");
	if (fp == NULL)
		return 0;
    
	while (fgets(outLine1, sizeof(outLine1)-1, fp) != NULL) {
		//if we have a pair of lines
		if(fgets(outLine2, sizeof(outLine2)-1, fp) != NULL) {
			//if symbols are readable
			if(outLine2[0] != '?') {
				//only let func name in outLine1
				int i;
				for(i = 0; i < 1035; ++i) {
					if(outLine1[i] == '\r' || outLine1[i] == '\n') {
						outLine1[i] = '\0';
						break;
					}
				}

				//don't display the whole path
				int lastSlashPos=0;
				
				for(i = 0; i < 1035; ++i) {
					if(outLine2[i] == '\0')
						break;
					if(outLine2[i] == '/')
						lastSlashPos = i+1;
				}
				db_log(SYS_ERROR, "%p in %s at %s", addr, outLine1, outLine2+lastSlashPos);
			} else {
				pclose(fp);
				return 0;
			}
		} else {
			pclose(fp);
			return 0;
		}
	}

	/* close */
	pclose(fp);
    return 1;
}

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
        /* Firstly use addr2line print stacktrace. 
         * If fail, print raw stacktrace. */
        if (print_stacktrace_addr2line(array[i]) == 0)
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

static void mock_crash() {
    char *ptr = NULL;
    *ptr = 'a';
}

#endif
