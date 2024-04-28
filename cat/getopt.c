#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int ch;

  static struct option longopts[] = {
      {"--number-nonblank", no_argument, NULL, 'b'},
      {NULL, no_argument, NULL, 'e'},
      {NULL, no_argument, NULL, 'v'},
      {NULL, no_argument, NULL, 'b'},
      {NULL, no_argument, NULL, 's'},
      {NULL, no_argument, NULL, 't'},
      {NULL, 0, NULL, 0}};

  while ((ch = getopt_long(argc, argv, "bevnst", longopts, NULL)) != EOF) {
    switch (ch) {
      case 'b':
        printf("b");
        break;
      case 'e':
        printf("e");
        break;
      case 'v':
        printf("v");
        break;
      case 'n':
        printf("n");
        break;
      case 's':
        printf("s");
        break;
      case 't':
        printf("t");
        break;
      default:
    }
  }
}
