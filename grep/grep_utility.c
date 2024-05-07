#include "./grep_utility.h"

uint16_t get_options(int argc, char* argv[]) {
  int opt;

  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
    switch (opt) {
    case 'e':
      // optarg
      break;
    case 'f':
      // fp = fopen (optarg, "r");
      break;
    case 'i':
      args.match_icase = true;
      break;
    case 'v':
      args.out_invert = true;
      break;
    case 'c':
      args.count_matches = true;
      break;
    case 'l':
      args.list_files = true;
      break;
    case 'n':
      args.out_line = true;
      break;
    case 'h':
      args.filename_option = true;
      break;
    case 's':
      args.suppress_errors = true;
      break;
    case 'o':
      args.only_matching = true;
      break;
    case '?':
      err_sys(SYNOPSIS);
    }
  }
}
