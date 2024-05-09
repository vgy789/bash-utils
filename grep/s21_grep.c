#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>

#include "../common/error.h"
#include "./grep_utility.h"

int main(int argc, char* argv[]) {
  FILE* fp = NULL;
  arguments args;

  // list_init()
  args = get_options(argc, argv);
  if (args.pattern_contained == 0) {
    // читаем выражения из аргумента
    // push_data(compile(argv(optind)));
    ++optind;
  } else {
    // читаем выражения из файла
    // push_data(compile(argv(optind)));
  }
  for (int i = optind; i < argc; ++i) {
    fp = fopen(argv[i], "r");
    if (fp == NULL && args.suppress_errors == false) {
      err_msg("%s: %s", argv[0], argv[i]);
      continue;
    }
    // передайм лист в exec_options и запускаем поиск
    // if (!exec_options(args, fp)) {
    //   continue;
    // }
    fclose(fp);
  }

  exit(EXIT_SUCCESS);
}
