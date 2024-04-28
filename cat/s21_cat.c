#include <options.h>
#include <stdio.h>

#include "../error.h"

#if defined(__APPLE__)
#define OS MAC
#elif defined(__unix__) | defined(linux)
#define OS UNIX
#endif

#define MAC_SYNOPSIS "usage: s21_cat [-benstv] file"
#define UNIX_SYNOPSIS \
  "usage: s21_cat [-bensTv] [--number-nonblank] [--number] \
[--squeeze-blank] file"

void err_synopsis() {
#if OS == MAC
  err_msg(MAC_SYNOPSIS);
#elif OS == UNIX
  err_msg(UNIX_SYNOPSIS);
#endif
}

int main(int argc, char* argv[]) {
  FILE* file;
  int flag;
  int ch;

  if (argc < 2) {
    err_synopsis();
    exit(1);
  }

  while ((ch = getopt_long(argc, argv, "bevnst", longopts, NULL)) != EOF) {
    switch (ch) {
      case 'b':
        flag = 0b1;
        break;
      case 'e':
        flag = 0b10;
        break;
      case 'v':
        flag = 0b100;
        break;
      case 'n':
        flag = 0b1000;
        break;
      case 's':
        flag = 0b10000;
        break;
      case 't':
        flag = 0b100000;
        break;
      default:
        err_synopsis();
        exit(1);
    }
  }

  if ((file = fopen(argv[argc - 1], "r")) == NULL) {
    err_sys("%s: %s", argv[0], argv[argc - 1]);
  }

  return 0;
}
