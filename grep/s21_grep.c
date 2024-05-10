#include <stdint.h>
#include <stdio.h>

#include "../common/error.h"
#include "./grep_utility.h"
#include "./regex_list.h"

bool file_readopen(FILE** fp, char* path, arguments args) {
  *fp = fopen(path, "r");
  if (*fp == NULL) {
    if (args.suppress_errors == false) {
      err_sysmsg("s21_grep: %s", path);
    }
    return 0;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  FILE* fp = NULL;
  struct grep_settings grep_sett = {0};
  grep_sett = parse_grep_options(argc, argv);

  for (int i = optind; i < argc; ++i) {
    char* path = argv[i];
    FILE* fp = NULL;
    if (!file_readopen(&fp, path, grep_sett.options)) {
      continue;
    }

    regex_run(fp, grep_sett);
    fclose(fp);
  }

  free_list(grep_sett.patterns);
  // exit(EXIT_SUCCESS);
}
