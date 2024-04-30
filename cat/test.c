#include <stdio.h>

void printbits(unsigned char v) {
  //   for (; v; v >>= 1) putchar('0' + (v % 2));
  for (int i = 7; i >= 0; --i) putchar((1 << i & v) ? '1' : '0');
  //   while (v) {
  // putchar('0' + (v % 2));
  // v >>= 1;
  //   }
}

int main(int argc, char const *argv[]) {
  int flags = 5;
  printbits((flags >> 2) & 1);

  return 0;
}
