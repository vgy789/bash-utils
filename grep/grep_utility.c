#include "./grep_utility.h"

arguments get_options(int argc, char* argv[]) {
  int opt;
  arguments args = {0};

  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'e':
        // args.e = optarg;
        // args.pattern = optarg;

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

  if (optind < argc) {
    // fp * fp = fopen(path, "r");
  }

  return args;
}

bool exec_options(arguments args, FILE* fp) {
  const char* pattern;
  
  regex_t regex;
  int reti;
  char msgbuf[128];
  int cflags = REG_BASIC | (args.match_icase ? REG_ICASE : 0);

  reti = regcomp(&regex, pattern, cflags);
  if (reti) {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    err_msg(msgbuf);
    return 0;
  }

  ssize_t n;
  size_t linecap;
  size_t line_number = 0;
  char* line = NULL;
  size_t count_match = 0;

  n = getline(&line, &linecap, fp);
  while (n != EOF) {
    ++line_number;
    reti = regexec(&regex, line, 0, NULL, 0);
    if (args.out_invert == 0 ? reti == 0 : reti != 0) {
      ++count_match;
      if (args.count_matches == 0) {
        if (args.out_line) printf("%d:", line_number);
        printf("%s", line);
      }
    }

    n = getline(&line, &linecap, fp);
  }

  if (args.count_matches) printf("%d", count_match);
  regfree(&regex);
}

void process_file(arguments arg, char* path, regex_t regex) {}
