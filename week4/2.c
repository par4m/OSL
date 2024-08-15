#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void print_error(const char *msg) { write(2, msg, strlen(msg)); }

void wait_for_key() {
  char c;
  write(1, "\n--More--", 9);
  read(0, &c, 1);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_error("Usage: ./more <file1> <file2> ...\n");
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  int line_count = 0;

  for (int i = 1; i < argc; i++) {
    int fd = open(argv[i], O_RDONLY);
    if (fd < 0) {
      print_error("Error opening file\n");
      continue;
    }

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
      for (ssize_t j = 0; j < bytes_read; j++) {
        if (buffer[j] == '\n') {
          line_count++;
          if (line_count >= 20) {
            wait_for_key();
            line_count = 0;
          }
        }
        write(1, &buffer[j], 1);
      }
    }

    if (bytes_read < 0) {
      print_error("Error reading file\n");
    }

    close(fd);
  }

  exit(0);
}
