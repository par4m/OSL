
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1

int main(int argc, char *argv[]) {
  if (argc != 3) {
    write(2, "Usage: ./filecopy <source> <destination>\n", 42);
    exit(1);
  }

  int src_fd = open(argv[1], O_RDONLY);
  if (src_fd < 0) {
    write(2, "Error opening source file\n", 26);
    exit(1);
  }

  int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (dest_fd < 0) {
    write(2, "Error opening destination file\n", 31);
    close(src_fd);
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;
  while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
    if (write(dest_fd, buffer, bytes_read) != bytes_read) {
      write(2, "Error writing to destination file\n", 34);
      close(src_fd);
      close(dest_fd);
      exit(1);
    }
  }

  if (bytes_read < 0) {
    write(2, "Error reading from source file\n", 31);
  }

  close(src_fd);
  close(dest_fd);
  exit(0);
}
