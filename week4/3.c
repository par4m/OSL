
#include <stdio.h>

int main() {
  int num = 123;
  float fnum = 456.78;
  char c = 'A';
  char str[] = "Hello";

  printf("Integer: %d\n", num);
  printf("Float: %.2f\n", fnum);
  printf("Character: %c\n", c);
  printf("String: %s\n", str);
  printf("Hexadecimal: %x\n", num);
  printf("Octal: %o\n", num);
  printf("Pointer: %p\n", (void *)&num);

  return 0;
}
