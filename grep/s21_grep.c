#include <stdint.h>
#include <stdio.h>

#include "../common/error.h"
#include "./grep_utility.h"
#include "./regex_list.h"

int main(int argc, char* argv[]) {
  FILE* fp = NULL;
  struct grep_settings grep_sett = {0};
  grep_sett = parse_grep_options(argc, argv);

  const bool nofile_haspattern =
      grep_sett.options.is_file == false &&
      (grep_sett.options.pattern_e || grep_sett.options.pattern_f);
  if (nofile_haspattern) {
    simple_grep(grep_sett);
  }

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
