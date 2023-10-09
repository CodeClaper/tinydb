#include "input.h"
#include <stdlib.h>
#include <string.h>

InputBuffer *read_input() {
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    ssize_t bytes_read = getline(&(input_buffer->input), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0) {
      printf("Error reading input\n");
      exit(EXIT_FAILURE);
    }
    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->input[bytes_read - 1] = 0;
    char *temp = input_buffer->input;
    char *old = temp;
    size_t size = strlen(temp);
    for(uint i = 0; i < size; i++) {
        char c = old[i];
        if (c == ' ') {
            temp++;
            input_buffer->input_length--;
        } else {
            break;
        }
    }
    input_buffer->input = strdup(temp);
    free(old);
    return input_buffer;
}

//Check if empty string.
bool is_empty(char *s) {
    size_t size = strlen(s);
    if (size == 0)
        return true;
    for(int i = 0; i < size; i++) {
        if (*(s + i) != ' ')
            return false;
    }
    return true;
}
