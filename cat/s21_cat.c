#include <stdint.h>
#include <stdio.h>

#include "./error.h"
#include "./options_process.h"
#include "./platform.h"

int main(int argc, char* argv[]) {
  FILE* file;
  uint16_t flags;

  if (argc == 1) {
    simple_cat();
    exit(0);
  }
  if ((flags = get_options(argc, argv)) == 0) {
    err_synopsis();
    exit(1);
  }
  if ((file = fopen(argv[argc - 1], "r")) == NULL) {
    err_sys("%s: %s", argv[0], argv[argc - 1]);
  }

  exec_options(flags);
  // print_file();
  fclose(file);

  exit(0);
}
