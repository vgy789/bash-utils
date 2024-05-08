#include <stdint.h>
#include <stdio.h>

#include "./grep_utility.h"
#include "../common/error.h"

int main(int argc, char* argv[]) {
  FILE* file = NULL;
  arguments args;

  args = get_options(argc, argv);

  for (int i = optind; i < argc; ++i) {
    file = fopen(argv[i], "r");
    if (file == NULL) {
      // завершается при первом ненайденном файле. не ищет в других при мультифайловости
      err_sys("%s: %s", argv[0], argv[i]);
    }

    exec_options(args, file);
    fclose(file);
  }

  exit(EXIT_SUCCESS);
}
