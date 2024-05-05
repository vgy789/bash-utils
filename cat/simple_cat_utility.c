#include "./simple_cat_utility.h"
#define VOID (512)

uint16_t get_options(int argc, char* argv[]) {
  char ch;
  uint16_t flags = 0;
  struct option longopts[] = {
      {"--number-nonblank", no_argument, NULL, 'b'},
      {"--show-ends-nonprinting", no_argument, NULL, 'e'},
      {"--show-nonprinting", no_argument, NULL, 'v'},
      {"--number", no_argument, NULL, 'n'},
      {"--squeeze-blank", no_argument, NULL, 's'},
      {"--show-tabs-nonprinting", no_argument, NULL, 't'},
      {"--show-ends", no_argument, NULL, 'E'},  // LINUX
      {"--show-tabs", no_argument, NULL, 'T'},  // LINUX
      {NULL, 0, NULL, 0}};
#ifdef MAC
  while ((ch = getopt_long(argc, argv, "bevnst", longopts, NULL)) != -1) {
#endif  // MAC
#ifdef LINUX
    while ((ch = getopt_long(argc, argv, "bevnstET", longopts, NULL)) != -1) {
#endif  // LINUX
      switch (ch) {
        case 'b':
          flags = set_option(number_nonblank, flags, 1);
          break;
        case 'e':
          flags = set_option(show_ends, flags, 1);
          flags = set_option(show_nonprinting, flags, 1);
          break;
        case 'v':
          flags = set_option(show_nonprinting, flags, 1);
          break;
        case 'n':
          flags = set_option(number, flags, 1);
          break;
        case 's':
          flags = set_option(squeeze_blank, flags, 1);
          break;
        case 't':
          flags = set_option(show_tabs, flags, 1);
          flags = set_option(show_nonprinting, flags, 1);
          break;
        case 'E':
          flags = set_option(show_ends, flags, 1);
          break;
        case 'T':
          flags = set_option(show_tabs, flags, 1);
          break;
        case '?':
          errcat_synopsis();
      }
    }

    if (optind < argc) {
      flags = set_option(is_filename, flags, 1);
    }

    return flags;
  }

  _Bool is_eof(FILE * file) {
    _Bool eof;

    if ((eof = (fgetc(file)) != EOF)) {
      fseek(file, -1, SEEK_CUR);
    }
    return eof;
  }

  void exec_options(uint16_t flags, FILE * file) {
    _Bool flag_numreset;
#ifdef LINUX
    flag_numreset = 0;
#endif  // LINUX
#ifdef MAC
    flag_numreset = 1;
#endif  // MAC
    char* line = calloc(4096, sizeof(char));
    if (line == NULL) {
      err_sys("sega");
    }

    size_t len;
    ssize_t n;

    n = getline(&line, &len, file);
    while (n != EOF) {
      if (get_option(squeeze_blank, flags)) {
        if (exec_squeeze_blank(line[0], file) == 1) {
          continue;
        }
      }
      if (get_option(number_nonblank, flags)) {
        flags = set_option(number, flags, 0);
        exec_number_nonblank(line, flag_numreset);
      }
      if (get_option(number, flags)) {
        exec_number(flag_numreset);
      }
      flag_numreset = 0;
      size_t i = 0;

      for (; line[i] != '\n'; ++i) {
        char ch = line[i];

        if (get_option(show_nonprinting, flags)) {
          ch = exec_nonprinting(ch);
        }
        if (get_option(show_tabs, flags)) {
          if (ch == '\t') {
            putchar('^');
            putchar('I');
            continue;
          }
        }

        putchar(ch);
      }
      if (get_option(show_ends, flags)) {
        if (line[i] == '\n') {
          putchar('$');
        }
      }
      putchar(line[i]);
      n = getline(&line, &len, file);
    }
    free(line);
  }

  _Bool get_option(uint16_t option, uint16_t flags) {
    return (flags & option) == option;
  }

  uint16_t set_option(uint16_t target, uint16_t flags, _Bool status) {
    if (status == 1) {
      flags |= target;
    } else {
      flags &= ~target;
    }

    return flags;
  }

  void simple_cat(uint16_t flags) {
    int n = 0;
    int buf[MAXLINE];

    exec_options(flags, stdin);
    while ((n = read(STDIN_FILENO, buf, MAXLINE)) != 0) {
      exec_options(flags, stdin);
      if (write(STDOUT_FILENO, buf, n) != n) {
        err_sys("input error");
      }
    }
    if (n == -1) {
      err_sys("read error");
    }
  }

  _Bool exec_squeeze_blank(char ch, FILE* file) {
    char next_char;
    _Bool contin;

    if ((next_char = fgetc(file)) != EOF) {
      contin = (ch == '\n' && next_char == '\n');
      fseek(file, -1, SEEK_CUR);
    }
    return contin;
  }

  void exec_number_nonblank(char* line, _Bool reset_flag) {
    static uint32_t line_count = 0;
    if (reset_flag) line_count = 0;

    if (line[0] != '\n') {
      ++line_count;
      printf("%6d\t", line_count);
    }
  }

  void exec_number(_Bool reset_flag) {
    static uint32_t line_count = 0;
    if (reset_flag) line_count = 0;

    ++line_count;
    printf("%6d\t", line_count);
  }

  char exec_nonprinting(char ch) {
    if ((ch >= 0 && ch < 9) || (ch > 10 && ch <= 31)) {
      printf("^");
      ch += '@';
    }
    if (ch == 127) {
      printf("M-^");
      ch = '?';
    }
    if (ch <= -97) {
      printf("M-^");
      ch += 128 + '@';
    }
#ifdef LINUX
    if (ch >= -96 && ch <= -2) {
      printf("M-");
      ch += 96 + ' ';
    }
    if (ch == -1) {
      printf("M-^");
      ch = '?';
    }
#endif  // LINUX
    return ch;
  }
