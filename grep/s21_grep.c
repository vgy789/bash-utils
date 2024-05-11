#include <stdint.h>
#include <stdio.h>

#include "../common/error.h"
#include "./grep_utility.h"
#include "./regex_list.h"

int main(int argc, char* argv[]) {
  struct grep_settings grep_sett = {0};
  grep_sett = parse_grep_options(argc, argv);

  const bool has_pattern =
      (grep_sett.options.pattern_e || grep_sett.options.pattern_f);
  const bool file_exists = grep_sett.options.file_count;
  if (has_pattern && !file_exists) {
    simple_grep(grep_sett);
  }
  if (!has_pattern && !file_exists) {
    err_quit(SYNOPSIS);
  }

  for (int i = optind; i < argc; ++i) {
    char* path = argv[i];
    FILE* fp = NULL;
    if (!file_readopen(&fp, path, grep_sett.options)) {
      continue;
    }

    regex_run(fp, path, grep_sett);
    fclose(fp);
  }

  free_list(grep_sett.patterns);
  // exit(EXIT_SUCCESS);
}
