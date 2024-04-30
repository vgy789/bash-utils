#include <stdint.h>
#include <stdio.h>

#include "./error.h"
#include "./file_process.h"

#if defined(__APPLE__)
#define OS MAC
#elif defined(__unix__) | defined(linux)
#define OS UNIX
#endif

#define MAC_SYNOPSIS "usage: s21_cat [-benstv] file"
#define UNIX_SYNOPSIS \
  "usage: s21_cat [-bensTv] [--number-nonblank] [--number] \
[--squeeze-blank] file"

int main(int argc, char* argv[]) {
  FILE* file;
  uint16_t flags;

  if (argc == 1) {
    cat();
    exit(0);
  }

  if ((flags = get_options(argc, argv) == 0)) {
    exit(1);
  }

  if ((file = fopen(argv[argc - 1], "r")) == NULL) {
    err_sys("%s: %s", argv[0], argv[argc - 1]);
  }

    return 0;
}

void err_synopsis() {
#if OS == MAC
  err_msg(MAC_SYNOPSIS);
#elif OS == UNIX
  err_msg(UNIX_SYNOPSIS);
#endif
}