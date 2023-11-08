#include "data.h"

/*Log for error level*/
void log_error(char *msg);

/*Log for error level with string format.*/
void log_error_s(char *format, char *s);

/*Log for error level with two strings format*/
void log_error_s_s(char *format, char *s1, char *s2);

/*Log for error level with a int string format*/
void log_error_d(char *format, int i);

/*Log for error level with a float string format*/
void log_error_f(char *format, float val);
