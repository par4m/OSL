#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void print_error(const char *msg) { write(2, msg, strlen(msg)); }

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_error("Usage: ./grep <word> <filename>\n");
    exit(1);
  }

  const char *search_word = argv[1];
  const char *filename = argv[2];
  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    print_error("Error opening file\n");
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
    char *line_start = buffer;
    for (ssize_t i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n' || i == bytes_read - 1) {
        size_t line_length = &buffer[i] - line_start;
        if (strstr(line_start, search_word) != NULL) {
          write(1, line_start, line_length);
          write(1, "\n", 1);
        }
        line_start = &buffer[i + 1];
      }
    }
  }

  if (bytes_read < 0) {
    print_error("Error reading file\n");
  }

  close(fd);
  exit(0);
}
