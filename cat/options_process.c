#include "./options_process.h"

uint16_t get_options(int argc, char* argv[]) {
  char ch;
  uint16_t flag = number_nonblank;

  while ((ch = getopt_long(argc, argv, "bevnst", longopts, NULL)) != EOF) {
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
        err_synopsis();
        flag = 0;
        // default:
        //   err_synopsis();
        //   flag = 0;
    }
  }
  return flag;
}

void exec_options(u_int16_t flags) {
  if ((flags & squeeze_blank) == squeeze_blank) {
    s();
  }
  if ((flags & number_nonblank) == number_nonblank) {
    b();
    flags = unset_flag(number, flags);
  }
  if ((flags & number) == number) {
    n();
  }
#ifdef LINUX
  if ((flags & show_ends) == show_ends) {
    E();
    flags = unset_flag(show_nonprinting, flags);
  }
  if ((flags & show_tabs) == show_tabs) {
    T();
    flags = unset_flag(show_nonprinting, flags);
  }
#endif
  if ((flags & show_ends_nonprinting) == show_ends_nonprinting) {
    e();
    flags = set_flag(show_nonprinting, flags);
  }

  if ((flags & show_tabs_nonprinting) == show_tabs_nonprinting) {
    t();
    flags = set_flag(show_nonprinting, flags);
  }

  if ((flags & show_nonprinting) == show_nonprinting) {
    v();
  }
}

u_int16_t set_flag(u_int16_t target, u_int16_t flags) {
  flags &= target;
  return flags;
}

u_int16_t unset_flag(u_int16_t target, u_int16_t flags) {
  flags &= ~target;
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

void b() { printf(" b "); }
void e() { printf(" e "); }
void v() { printf(" v "); }
void n() { printf(" n "); }
void s() { printf(" s "); }
void t() { printf(" t "); }
void E() { printf(" E "); }
void T() { printf(" T "); }
