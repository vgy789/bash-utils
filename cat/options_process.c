#include "./options_process.h"

uint16_t get_options(int argc, char* argv[]) {
  char ch;
  uint16_t flag = 0;

  while ((ch = getopt_long(argc, argv, "bevnstET", longopts, NULL)) != -1) {
    switch (ch) {
      case 'b':
        flag |= number_nonblank;
        break;
      case 'e':
        flag |= show_ends_nonprinting;
        break;
      case 'v':
        flag |= show_nonprinting;
        break;
      case 'n':
        flag |= number;
        break;
      case 's':
        flag |= squeeze_blank;
        break;
      case 't':
        flag |= show_tabs_nonprinting;
        break;
      case 'E':
        flag |= show_ends;
        break;
      case 'T':
        flag |= show_tabs;
        break;
      case '?':
        flag = 0;
        errcat_synopsis();
    }
  }
  return flag;
}

void exec_options(uint16_t flags, FILE* file) {
  char* line = calloc(4096, sizeof(char));
  if (line == NULL) {
    err_sys("line is long");
  }

  size_t len = 0;
  ssize_t n;
  int line_count = 0;
  _Bool prev = 0;

  while ((n = getline(&line, &len, file)) != -1) {
    if ((flags & squeeze_blank) == squeeze_blank) {
      s_exec(line);
    }
    if ((flags & number_nonblank) == number_nonblank) {
      flags = set_flag(number, flags, 0);
      b_exec(line, flags);
    }
    if ((flags & number) == number) {
      n_exec();
    }
#ifdef LINUX
    if ((flags & show_ends) == show_ends) {
      flags = set_flag(show_nonprinting, flags, 0);
      E();
    }
    if ((flags & show_tabs) == show_tabs) {
      flags = set_flag(show_nonprinting, flags, 0);
      T();
    }
#endif
    if ((flags & show_ends_nonprinting) == show_ends_nonprinting) {
      flags = set_flag(show_nonprinting, flags, 1);
      e();
    }
    if ((flags & show_tabs_nonprinting) == show_tabs_nonprinting) {
      flags = set_flag(show_nonprinting, flags, 1);
      t();
    }
    if ((flags & show_nonprinting) == show_nonprinting) {
      v_exec(line);
    }

    fwrite(line, n, 1, stdout);
  }
  free(line);
}

uint16_t set_flag(uint16_t target, uint16_t flags, _Bool status) {
  if (status == 1) {
    flags &= target;
  } else {
    flags &= ~target;
  }

  return flags;
}

void simple_cat(void) {
  int n = 0;
  int buf[MAXLINE];
  while ((n = read(STDIN_FILENO, buf, MAXLINE)) != 0) {
    if (write(STDOUT_FILENO, buf, n) != n) {
      err_sys("input error");
    }
  }
  if (n == -1) {
    err_sys("read error");
  }
}

void b_exec(char* line, uint16_t flags) {
  static uint32_t line_count = 0;

  if (line[0] != '\n') {
    ++line_count;
    printf("     %d\t", line_count);
  }
}

void e() {}

void v_exec(char* line) {}

// void v_exec(char* line) {
//   char result[4096] = {0};
//   char add_str[5];
//
//   for (size_t i = 0; line[i] != '\n' && line[i] != EOF; ++i) {
//     const size_t ch_pos = i + 1;
//     char ch = line[i];
//     if (ch >= 0 && ch <= 31) {
//       sprintf(add_str, "^%c", ch + '@');
//     }
//     if (ch == 127) {
//       sprintf(add_str, "^?");
//     }
//     if (ch >= 128 && ch <= 159) {
//       sprintf(add_str, "M-^%c", ch + '@');
//     }
// #ifdef LINUX
//     if (ch >= 160 && ch <= 254) {
//       sprintf(add_str, "M-%c", ch + ' ');
//     };
//     if (ch == 255) {
//       sprintf(add_str, "M-^?", ch + ' ');
//     }
// #endif
//     insert_str(result, line, add_str, ch_pos);
//   }
// }

void n_exec() {
  static uint32_t line_count = 0;

  ++line_count;
  printf("     %d\t", line_count);
}

void s_exec(char* line) {
  // _Bool this = (line[0] == '\n');
  // if (prev == 1 && this == 1) {
  //   prev = 0;
  //   continue;
  // }
  // prev = (line[0] == '\n');
}
void t() {}
void E() {}
void T() {}

static void insert_str(char* dest, const char* str, const char* substr,
                       size_t pos) {
  strncpy(dest, str, pos);
  dest[pos] = '\0';
  strcat(dest, substr);
  strcat(dest, str + pos);
}
