#include "utils.h"
#include "mem.h"

// check if a file has suffix.
bool endwith(char *str, char *suffix) {
    if (!str || !suffix)
        return false;
    ssize_t str_len = strlen(str);
    ssize_t suffix_size = strlen(suffix);
    if (suffix_size > str_len)
        return false;
    return strcmp(str + str_len - suffix_size, suffix) == 0;
}

// substring
char *substr(char *str, uint32_t start, uint32_t end) {
    if (!str)
        return NULL;
    ssize_t str_size = strlen(str);
    if (start >= str_size || end >= str_size)
        return NULL;
    char *substr = db_malloc(end - start + 1);
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

// replace
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
    char *repl = db_malloc(str_size - old_size + new_size + 1);
    for (index = 0; index < str_size; index++) {
        char *temp = db_malloc(old_size + 1);
        memcpy(temp, str + index, old_size);
        if (strcmp(temp, old_str) == 0) {
            memcpy(repl + index , new_str, new_size); 
            strcpy(repl + index + new_size, str + index + old_size);
            *(repl + str_size - old_size + new_size) = '\0';
            free(temp);
            return repl;
        }
        free(temp);
        *(repl+index) = *(str+index);
    }
    free(repl);
    return NULL;
}

