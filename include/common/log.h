#include "data.h"

#define panic(...) (db_log(PANIC, __VA_ARGS__))

/* Log. */
void db_log(LogLevel lev, char *format, ...);

/* Get log message. */
char *get_log_msg();
