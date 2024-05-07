#include "data.h"

#define panic(...) (db_log(PANIC, __VA_ARGS__))

/* Initialise Log */
void init_log();

/* Log. */
void db_log(LogLevel lev, char *format, ...);

/* Get log message. */
char *get_log_msg();
