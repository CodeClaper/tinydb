#include "input.h"

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read = getline(&(input_buffer->input), &(input_buffer->buffer_length), stdin);
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->input[bytes_read - 1] = 0;
}
