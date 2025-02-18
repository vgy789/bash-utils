#include <stdint.h>
#include <stdio.h>

#include "../common/error.h"
#include "cat_utility.h"

void process_file(char* path, uint16_t flags) {
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    err_msg("%s: %s", "s21_cat", path);
    return;
  }

  exec_options(flags, file);
  fclose(file);
}

int main(int argc, char* argv[]) {
  uint16_t flags = 0;
  flags = get_options(argc, argv);

  int option_result = get_option(is_file, flags);
  if (option_result == 0) {
    simple_cat(flags);
    exit(EXIT_SUCCESS);
  }

  for (int i = optind; i < argc; ++i) {
    process_file(argv[i], flags);
  }

  exit(EXIT_SUCCESS);
}
