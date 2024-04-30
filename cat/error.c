#include "error.h"

#define MAXLINE 4096

void err_doit(int, int, const char*, va_list);

void err_sys(const char* fmt, ...) {
  va_list vl;
  va_start(vl, fmt);
  err_doit(1, errno, fmt, vl);
  va_end(vl);
  exit(1);
}

void err_exit(int error, const char* fmt, ...) {
  va_list vl;

  va_start(vl, fmt);
  err_doit(1, error, fmt, vl);
  va_end(vl);
  exit(1);
}

void err_quit(const char* fmt, ...) {
  va_list vl;

  va_start(vl, fmt);
  err_doit(0, 0, fmt, vl);
  va_end(vl);
  exit(1);
}

void err_msg(const char* fmt, ...) {
  va_list vl;

  va_start(vl, fmt);
  err_doit(0, 0, fmt, vl);
  va_end(vl);
}

void err_doit(int errnoflag, int error, const char* fmt, va_list vl) {
  char buf[MAXLINE];

  vsnprintf(buf, MAXLINE - 1, fmt, vl);
  if (errnoflag) {
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s",
             strerror(error));
  }
  strcat(buf, "\n");
  fflush(stdout);
  fputs(buf, stderr);
  fflush(NULL);
}
