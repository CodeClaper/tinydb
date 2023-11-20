#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session.h"
#include "log.h"
#include "data.h"

/*Log for error level*/
void log_error(char *s) {
    int len = strlen(s) + 1;
    char buff[len];
    sprintf(buff, "%s\n", s);
    db_send(buff);    
}

/*Log for error level with string format.*/
void log_error_s(char *format, char *s) {
    int len = strlen(format) + strlen(s);
    char buff[len];
    sprintf(buff, format, s);
    log_error(buff);
}

/*Log for error level with two strings format*/
void log_error_s_s(char *format, char *s1, char *s2) {
    int len = strlen(format) + strlen(s1) + strlen(s2);
    char buff[len];
    sprintf(buff, format, s1, s2);
    log_error(buff);
}

/*Log for error level with a int string format*/
void log_error_d(char *format, int val) {
    int len = strlen(format) + 20;
    char buff[len];
    sprintf(buff, format, val);
    log_error(buff);
}

/*Log for error level with a float string format*/
void log_error_f(char *format, float val) {
    int len = strlen(format) + 20;
    char buff[len];
    sprintf(buff, format, val);
    log_error(buff);
}
