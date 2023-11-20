#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "mem.h"

//Check if empty string.
bool is_empty(char *s) {
    if (s == NULL) return true;
    size_t size = strlen(s);
    if (size == 0)
        return true;
    for(int i = 0; i < size; i++) {
        if (*(s + i) != ' ')
            return false;
    }
    return true;
}
