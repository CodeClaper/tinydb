#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "session.h"
#include "log.h"
#include "data.h"

/* Db log for error level. */
void db_error(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char buff[BUFF_SIZE];
    vsprintf(buff, format, ap);
    db_send(buff);    
    va_end(ap);
}
