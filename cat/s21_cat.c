#include <stdint.h>
#include <stdio.h>

#include "./error.h"
#include "./options_process.h"
#include "./platform.h"

int main(int argc, char* argv[]) {
  FILE* file = NULL;
  uint16_t flags = 0;

  flags = get_options(argc, argv);

  if (get_option(is_filename, flags) == 0) {
    simple_cat(flags);
    exit(EXIT_SUCCESS);
  }

  for (int i = optind; i < argc; ++i) {
    if ((file = fopen(argv[i], "r")) == NULL) {
      err_sys("%s: %s", argv[0], argv[i]);
    }
    // if (optind < i) putchar('\n');

    exec_options(flags, file);
    fclose(file);
  }

  exit(EXIT_SUCCESS);
}
