#include <stdint.h>
#include <stdio.h>

#include "../common/error.h"
#include "./cat_utility.h"

int main(int argc, char* argv[]) {
  FILE* file = NULL;
  uint16_t flags = 0;

  flags = get_options(argc, argv);

  if (get_option(is_file, flags) == 0) {
    simple_cat(flags);
    exit(EXIT_SUCCESS);
  }

  for (int i = optind; i < argc; ++i) {
    file = fopen(argv[i], "r");
    if (file == NULL) {
      err_msg("%s: %s", argv[0], argv[i]);
      continue;
    }

    exec_options(flags, file);
    fclose(file);
  }

  exit(EXIT_SUCCESS);
}
