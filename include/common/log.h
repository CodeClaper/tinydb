#include "data.h"

#define panic(...) (db_log(PANIC, __VA_ARGS__))


/* Get stack message. */
char *get_stack_message();

/* Log. */
void db_log(LogLevel lev, char *format, ...);

