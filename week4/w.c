#include <stdlib.h>
#include <unistd.h>

int main() {
  if ((write(1, "here is some data that is more than 18 \n", 18)) < 18) {
    write(2, "A write error has occured on the file descriptor 1\n", 46);
  }

  exit(0);
}
