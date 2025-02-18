#include "grep_utility.h"

struct grep_settings parse_grep_options(int argc, char* argv[]) {
  struct grep_settings grep = {0};
  arguments args = {0};
  int opt = 0;
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
        args.pattern_f = true;
        break;
      case 'o':
        args.only_matching = true;
        break;
      case '?':
        err_quit(SYNOPSIS);
    }
  }

  if (args.pattern_e || args.pattern_f) {
    optind = 1;
    // grep [-e pattern] [-e pattern] [-e pattern] [file?]
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) !=
           -1) {
      if (opt == 'e') {
        pattern = optarg;
        regex = compile_expression(pattern, args);
        push_data(grep.patterns, regex);
      }
      if (opt == 'f') {
        // grep [-t file] [file?]
        FILE* fp = NULL;
        if (!file_readopen(&fp, optarg, args)) {
          exit(1);
        }

        char* row = NULL;
        size_t len = 0;
        ssize_t n = 0;
        while ((n = getline(&row, &len, fp)) != EOF) {
          if (row[n - 1] == '\n') {
            row[n - 1] = '\0';
          }
          pattern = row;
          regex = compile_expression(pattern, args);
          push_data(grep.patterns, regex);
        }
        free(row);
        fclose(fp);
      }
    }
  } else if (optind < argc) {
    // grep [pattern] [file?]
    pattern = argv[optind];
    regex = compile_expression(pattern, args);
    push_data(grep.patterns, regex);
    ++optind;
    args.pattern_e = true;
  }

  if (optind + 1 < argc) {
    args.file_count = MULTIPLE_FILE;
  } else if (optind < argc) {
    args.file_count = ONE_FILE;
  } else {
    args.file_count = NO_FILE;
  }

  grep.options = args;
  return grep;
}

regex_t compile_expression(const char* pattern, arguments args) {
  int reti = 0;
  char msgbuf[128] = {'\0'};

  uint16_t cflags = 0;
  if (args.match_icase) {
    cflags |= REG_ICASE;
  }
  regex_t regex;

  reti = regcomp(&regex, pattern, cflags);
  if (reti) {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    err_exit(1, msgbuf);
  }

  return regex;
}

void regex_row_search(const char* row, struct grep_settings grep_sett,
                      const char* filepath, size_t* count_match,
                      size_t* row_number) {
  int reti = 0;
  struct array_list* list = grep_sett.patterns;
  arguments args = grep_sett.options;

  for (int i = 0; i < list->len; ++i) {
    *row_number += 1;
    reti = regexec(&list->regex[i], row, 0, NULL, 0);

    if (args.out_invert != (reti ^ 0)) {
      continue;
    }
    *count_match += 1;
    if (args.count_matches || grep_sett.options.list_files) {
      continue;
    }
    if (args.file_count == MULTIPLE_FILE && args.filename_option == false) {
      printf("%s:", filepath);
    }
    if (args.out_line) {
      printf("%ld:", *row_number);
    }
    printf("%s\n", row);
  }
}

void regex_row_search_with_o(const char* row, struct grep_settings grep_sett,
                             const char* filepath, size_t* count_match,
                             size_t* row_number) {
  int reti = 0;
  struct array_list* list = grep_sett.patterns;
  arguments args = grep_sett.options;
  regmatch_t pmatch[1];
  regoff_t len;

  for (size_t i = 0; i < list->len; ++i) {
    bool row_flag = false;
    *row_number += 1;

    while (true) {
      reti = regexec(&list->regex[i], row, 1, pmatch, 0);
      if (args.out_invert != (reti ^ 0)) {
        break;
      }

      len = pmatch[0].rm_eo - pmatch[0].rm_so;
      if (!(args.count_matches || grep_sett.options.list_files)) {
        printf("%.*s\n", (int)len, row + pmatch[0].rm_so);
      }

      row += pmatch[0].rm_eo;

      if (row_flag == false) {
        row_flag = true;
        *count_match += 1;
      }
      if (args.count_matches || grep_sett.options.list_files) {
        continue;
      }
      if (args.file_count == MULTIPLE_FILE && args.filename_option == false) {
        printf("%s:", filepath);
      }
      if (args.out_line) {
        printf("%ld:", *row_number);
      }
    }
  }
}

void regex_run(FILE* fp, char* filepath, struct grep_settings sett) {
  char* row = NULL;
  size_t len = 0;
  int n;
  size_t count_match = 0;
  size_t row_number = 0;

  while ((n = getline(&row, &len, fp)) != EOF) {
    if (row[n - 1] == '\n') {
      row[n - 1] = '\0';
    }

    const bool o_flag =
        (sett.options.only_matching && !sett.options.out_invert);
    if (o_flag) {
      regex_row_search_with_o(row, sett, filepath, &count_match, &row_number);
    } else {
      regex_row_search(row, sett, filepath, &count_match, &row_number);
    }
  }

  if (sett.options.list_files && count_match > 0) {
    printf("%s\n", filepath);
  }

  if (sett.options.count_matches) {
    if (!sett.options.list_files && sett.options.file_count == MULTIPLE_FILE &&
        !sett.options.filename_option) {
      printf("%s", filepath);
    }
    if (!sett.options.filename_option &&
        (sett.options.file_count == MULTIPLE_FILE ||
         (sett.options.file_count == ONE_FILE && sett.options.list_files))) {
      printf(":");
    }
    printf("%ld\n", count_match);
  }
  if (row) {
    free(row);
  }
}

void simple_grep(struct grep_settings grep_sett) {
  int n = 0;
  int buf[maxline] = {'\0'};

  while ((n = read(STDIN_FILENO, buf, maxline)) != 0) {
    regex_run(stdin, "", grep_sett);
    if (write(STDOUT_FILENO, buf, n) != n) {
      err_sys("input error");
    }
  }
  if (n == -1) {
    err_sys("read error");
  }
}

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
