#include "data.h"


/* Initialise Log */
void init_log();

/* Log. */
void db_log(LogLevel lev, char *format, ...);

/* Get log message. */
char *get_log_msg();
