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

/* replace once */
char *replace_once(char *str, char *old_str, char *new_str);

/* Replace all. */
char *replace_all(char *str, char *old_str, char *new_str);

/* Check if empty string. */
bool is_empty(char *s);

/* Format String and return. */
char *format(char *format, ...);

/* Check both string if equal. */
bool streq(char *str1, char *str2);

/* Check both string if equal, 
 * if both is null, also return true. */
bool streq_or_null(char *str1, char *str2);

/* Return if pointer is NULL. */
bool is_null(void *ptr);

/* Convert int32 to string. */
char *itos(int32_t val);

/* Convert long to string. */
char *ltos(int64_t val);

/* Covnert bool to string. */
char *btos(bool val);

/* Convert float to string. */
char *ftos(float val);

/* Convert float to string. */
char *dtos(double val);

/* Convert time to string. */
char *ttos(time_t val, char *frmt);


/* Convert String value to int32_t value.
 * return 1 if success.
 * return 0 if not valid number.
 * return -1 if overflow.
 * */
int stoi32(char *val,  int32_t *ret);


/* Convert String value to int64 value.
 * return 1 if success.
 * return 0 if not valid number.
 * return -1 if overflow.
 * */
int stoi64(char *val,  int64_t *ret);


/* Get line from socket. */
int get_line(int sock, char *buf, int size);
