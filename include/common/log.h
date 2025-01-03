#include "data.h"

#define panic(...) (db_log(PANIC, __VA_ARGS__))

/* Get stack message. */
char *get_stack_message();

/* DB Log. */
void db_log(LogLevel level, char *format, ...);

