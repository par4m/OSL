#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  char buffer[128];

  int nread;
  nread = read(0, buffer, 128);
  if (nread == -1) {
    write(1, "An Error occured", 200);
  }
}
