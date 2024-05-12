#define _GNU_SOURCE

#include "./grep_utility.h"
#include <string.h>
#include "./regex_list.h"

struct grep_settings parse_grep_options(int argc, char* argv[]) {
  struct grep_settings grep = {0};
  arguments args = {0};
  int opt = 0;
  char* pattern = {'\0'};
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
  uint16_t cflags = REG_BASIC | (args.match_icase ? REG_ICASE : 0);
  regex_t regex;

  reti = regcomp(&regex, pattern, cflags);
  if (reti) {
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    err_exit(1, msgbuf);
  }

  return regex;
}

void regex_row_search(char* row, struct grep_settings grep_sett, char* filepath,
                      size_t* count_match, size_t* row_number) {
  int reti = 0;
  struct array_list* list = grep_sett.patterns;
  arguments args = grep_sett.options;
  regmatch_t match;

  for (int i = 0; i < list->len; ++i) {
    *row_number += 1;
    reti = regexec(&list->regex[i], row, 0, NULL, 0);
    
    if (args.out_invert == (reti ^ 0)) {
      *count_match += 1;
      if (args.count_matches || grep_sett.options.list_files) {
        continue;
      }
      if (args.file_count == MULTIPLE_FILE && args.filename_option == false) {
        printf("%s:", filepath);
      }
      if (args.out_line) {
        printf("%d:", *row_number);
      }
      printf("%s", row);
    }
  }
}

void regex_row_search_with_o(char* row, struct grep_settings grep_sett, char* filepath,
                      size_t* count_match, size_t* row_number, size_t n) {
  int reti = 0;
  struct array_list* list = grep_sett.patterns;
  arguments args = grep_sett.options;
  regmatch_t match;

  for (int i = 0; i < list->len; ++i) {
    *row_number += 1;
    do {
      reti = regexec(&list->regex[i], row, grep_sett.options.only_matching,
                    &match, 0);

      if (args.out_invert == (reti ^ 0)) {
        *count_match += 1;
        printf("%d\n", match);
        //printf("%.*s\n", (int)(match.rm_eo - match.rm_so), &row[match.rm_so]);
        //strncpy(&row[match.rm_eo], &row[match.rm_eo], n -);
      }
    } while(args.out_invert == (reti ^ 0));
  }
}

void regex_run(FILE* fp, char* filepath, struct grep_settings sett) {
  char* row = NULL;
  size_t len = 0;
  size_t n;
  size_t count_match = 0;
  size_t row_number = 0;

  char end_char;
  while (n = getline(&row, &len, fp) != EOF) {
    if (sett.options.only_matching) {
      regex_row_search_with_o(row, sett, filepath, &count_match, &row_number, n);
    } else {
      regex_row_search(row, sett, filepath, &count_match, &row_number);
    }
    end_char = row[n - 1];
  }

  if (sett.options.list_files) {
    printf("%s", filepath);
  }
  if (sett.options.count_matches) {
    if (sett.options.list_files == false &&
        sett.options.file_count == MULTIPLE_FILE &&
        sett.options.filename_option == false) {
      printf("%s", filepath);
    }
    if (sett.options.filename_option == false &&
        (sett.options.file_count == MULTIPLE_FILE ||
         (sett.options.file_count == ONE_FILE && sett.options.list_files))) {
      printf(":");
    }
    printf("%d", count_match);
  }
  if (end_char != '\n') {
    printf("\n");
  }
  if (row) free(row);
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