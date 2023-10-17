//Log init
void log_init();

//Error
void log_error(char *msg);

//Error for string format
void log_error_s(char *format, char *s);

//Error for string format
void log_error_s_s(char *format, char *s1, char *s2);

//Error for int format
void log_error_d(char *format, int i);

//Get current error.
char *get_current_error();

//Clear error
void clear_error();
