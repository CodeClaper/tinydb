#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

/* left trim*/
char *ltrim(char *s);

/* right trim */
char *rtrim(char *s);

/* trim */
char *trim(char *s);

/* Check if a string contains substring.*/
bool contains(char* str, char *substr);

/* Check if a file has prefix. */
bool startwith(char *str, char *prefix);

/* Check if a file has suffix. */
bool endwith(char *str, char *suffix);

/* substring */
char *substr(char *str, uint32_t start, uint32_t end);

/* replace */
char *replace(char *str, char *old_str, char *new_str);

/* Check if empty string. */
bool is_empty(char *s);

/* Format String and return. */
char *format(char *format, ...);

/* Check both string if equal. */
bool streq(char *str1, char *str2);

/* Check both string if equal, 
 * if both is null, also return true. */
bool streq_or_null(char *str1, char *str2);

/* Get line from socket. */
int get_line(int sock, char *buf, int size);
