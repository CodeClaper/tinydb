#include "data.h"

#define panic(...) (db_log(PANIC, __VA_ARGS__))

/* Get stack message. */
char *get_stack_message();

/* Get current log file desc. */
int get_current_log_fdesc();

/* DB Log. */
void db_log(LogLevel level, char *format, ...);

