#include "./file_process.h"

#define MAXLINE 4096

void cat(void) {
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

void b() {}
void e() {}
void v() {}
void n() {}
void s() {}
void t() {}
void E() {}
void T() {}

void flag_process(u_int16_t flags) {
  if ((flags >> 0) & 1 == 1) {
    b();
  }
  if ((flags >> 1) & 1 == 1) {
    e();
  }
  if ((flags >> 2) & 1 == 1) {
    v();
  }
  if ((flags >> 3) & 1 == 1) {
    n();
  }
  if ((flags >> 3) & 1 == 1) {
    s();
  }
  if ((flags >> 3) & 1 == 1) {
    t();
  }
  if ((flags >> 3) & 1 == 1) {
    E();
  }
  if ((flags >> 3) & 1 == 1) {
    T();
  }
}
