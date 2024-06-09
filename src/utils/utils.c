#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>
#include "utils.h"
#include "mmu.h"

/* left trim*/
char *ltrim(char *s) {
    while(isspace(*s)) s++;
    return s;
}

/* right trim */
char *rtrim(char *s) {
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

/* trim */
char *trim(char *s) {
    return rtrim(ltrim(s)); 
}

/* Check if a string contains substring.*/
bool contains(char* str, char *substr) {
    if (!str || !substr)
        return false;
    char *s = strstr(str, substr);
    return s != NULL;
}

/* Check if a file has prefix. */
bool startwith(char *str, char *prefix) {
    if (!str || !prefix)
        return false;
    ssize_t str_len = strlen(str);
    ssize_t pre_size = strlen(prefix);
    if (pre_size > str_len)
        return false;
    return strncmp(str, prefix, pre_size) == 0;
}

/* check if a file has suffix. */
bool endwith(char *str, char *suffix) {
    if (!str || !suffix)
        return false;
    ssize_t str_len = strlen(str);
    ssize_t suffix_size = strlen(suffix);
    if (suffix_size > str_len)
        return false;
    return strcmp(str + str_len - suffix_size, suffix) == 0;
}

/* substring */
char *substr(char *str, uint32_t start, uint32_t end) {
    if (!str)
        return NULL;
    ssize_t str_size = strlen(str);
    if (start >= str_size || end >= str_size)
        return NULL;
    char *substr = db_malloc(end - start + 1, "string");
    uint index = 0;
    for (uint32_t i = 0; i <str_size; i++) {
        if (start <= i && i <= end) {
            *(substr + index) = *(str + i);
            index++;
        }
    }
    *(substr + index) = '\0';
    return substr;
}

/* replace */
char *replace(char *str, char *old_str, char *new_str) {
    if (!str || !old_str)
        return NULL;
    ssize_t str_size = strlen(str);
    ssize_t old_size = strlen(old_str);
    if (old_size > str_size)
        return NULL;
    if (new_str == NULL)
        new_str = "";
    ssize_t new_size = strlen(new_str);
    uint32_t index;
    char *repl = db_malloc(str_size - old_size + new_size + 1, "string");
    for (index = 0; index < str_size; index++) {
        char *temp = db_malloc(old_size + 1, "string");
        memcpy(temp, str + index, old_size);
        if (strcmp(temp, old_str) == 0) {
            memcpy(repl + index , new_str, new_size); 
            strcpy(repl + index + new_size, str + index + old_size);
            *(repl + str_size - old_size + new_size) = '\0';
            db_free(temp);
            return repl;
        }
        db_free(temp);
        *(repl+index) = *(str+index);
    }
    db_free(repl);
    return NULL;
}

/* Check if empty string. */
bool is_empty(char *s) {
    if (s == NULL) 
        return true;
    size_t size = strlen(s);
    if (size == 0)
        return true;
    for(int i = 0; i < size; i++) {
        if (*(s + i) != ' ')
            return false;
    }
    return true;
}

/* Format String and return. */
char *format(char *format, ...) {
    char message[BUFF_SIZE];
    va_list ap;
    va_start(ap, format);
    vsprintf(message, format, ap);
    char *ret = db_strdup(message);
    va_end(ap);
    return ret;
}

/* Check if two strings are equal. 
 * Any of strings is NULL, return false. */
bool streq(char *str1, char *str2) {
    return str1 && str2 && strcmp(str1, str2) == 0;
}

/* Check if two strings are equal, 
 * if both are null, also return true. */
bool streq_or_null(char *str1, char *str2) {
    if (str1 && str2)
        return strcmp(str1, str2) == 0;
    else if (!str1 && !str2)
        return true;
    else
        return false;
}

/* Check if string is empty.
 * Empty means string is NULL or "".
 * */
bool strempty(char *str) {
    return str == NULL || strlen(str) == 0;
}

/* Return if pointer is NULL. */
bool is_null(void *ptr) {
    return ptr == NULL;
}

/* Convert int32 to string. */
char *itos(int32_t val) {
    char *str = db_malloc(MAX_INT_STR_LENGTH, "string");
    sprintf(str, "%d", val);
    return str;
}

/* Convert long to string. */
char *ltos(int64_t val) {
    char *str = db_malloc(MAX_LONG_STR_LENGTH, "string");
    sprintf(str, "%ld", val);
    return str;
}

/* Covnert bool to string. */
char *btos(bool val) {
    char *str = db_malloc(MAX_BOOL_STR_LENGTH, "string");
    sprintf(str, val ? "true" : "false");
    return str;
}

/* Convert float to string. */
char *ftos(float val) {
    char *str = db_malloc(MAX_FLOAT_STR_LENGTH, "string");
    sprintf(str, "%f", val);
    return str;
}

/* Convert float to string. */
char *dtos(double val) {
    char *str = db_malloc(MAX_DOUBLE_STR_LENGTH, "string");
    sprintf(str, "%lf", val);
    return str;
}

/* Convert time to string. */
char *ttos(time_t val, char *frmt) {
    char temp[90];
    char *str = db_malloc(MAX_TIMESTAMP_STR_LENGTH, "string");
    struct tm *tmp_time = localtime(&val);
    strftime(temp, sizeof(temp), frmt, tmp_time);
    sprintf(str, "%s", temp);
    return str;
}


/**********************************************************************/
/* Get a line from a socket, whether the line ends in a newline,
 * carriage return, or a CRLF combination.  Terminates the string read
 * with a null character.  If no newline indicator is found before the
 * end of the buffer, the string is terminated with a null.  If any of
 * the above three line terminators is read, the last character of the
 * string will be a linefeed and the string will be terminated with a
 * null character.
 * Parameters: the socket descriptor
 *             the buffer to save the data in
 *             the size of the buffer
 * Returns: the number of bytes stored (excluding null) */
/**********************************************************************/
int get_line(int sock, char *buf, int size) {
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            if (c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';

    return(i);
}
