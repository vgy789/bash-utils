#define _GNU_SOURCE
#include "./grep_utility.h"

#include "./regex_list.h"

struct grep_settings parse_grep_options(int argc, char* argv[]) {
  struct grep_settings grep = {0};
  arguments args = {0};
  int opt;
  char* pattern;
  regex_t regex;

  grep.patterns = init_list();

  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'e':
        args.pattern_e = true;
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
      case 'f':
        args.patterns_file = true;
        break;
      case 'o':
        args.only_matching = true;
        break;
      case '?':
        err_sys(SYNOPSIS);
    }
  }
  grep.options = args;

  if (args.pattern_e) {
    optind = 1;
    // grep -e pattern -e pattern -e pattern file
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
           -1) {
      if (opt == 'e') {
        printf("%s", optarg);
        pattern = optarg;
        regex = compile_expression(pattern, args);
        push_data(grep.patterns, regex);
      }
    }
  } else {
    printf("here");
    // grep pattern file
    if (optind < argc) {
      pattern = argv[optind];
      regex = compile_expression(pattern, args);
      push_data(grep.patterns, regex);
      ++optind;
    } else {
      err_exit(1, SYNOPSIS);
    }
  }

  return grep;
}

regex_t compile_expression(const char* pattern, arguments args) {
  int reti;
  char msgbuf[128];
  uint16_t cflags = REG_BASIC | (args.match_icase ? REG_ICASE : 0);
  regex_t regex;

  reti = regcomp(&regex, pattern, cflags);
  if (reti) {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    err_exit(1, msgbuf);
  }

  return regex;
}

void regex_run(FILE* fp, struct grep_settings grep_sett) {
  int reti;
  size_t count_match;
  arguments args = grep_sett.options;
  struct array_list* list = grep_sett.patterns;
  const uint16_t count_patterns = list->len;

  size_t row_number;
  char* row = NULL;
  size_t len;
  while (getline(&row, &len, fp) != EOF) {
    for (int i = 0; i < count_patterns; ++i) {
      ++row_number;
      reti = regexec(&list->regex[i], row, 0, NULL, 0);
      // кажется это не инвертирование, а бред. Но для просто букав работает
      if (args.out_invert == false ? reti == 0 : reti != 0) {
        ++count_match;
        if (args.count_matches == false) {
          if (args.out_line) printf("%d:", row_number);
          printf("%s", row);
        }
      }
    }
  }
  free(row);
  if (args.count_matches) printf("%d", count_match);
}

void process_file(arguments arg, char* path, regex_t regex) {}
