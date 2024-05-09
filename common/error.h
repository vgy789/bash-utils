#ifndef ERROR_H
#define ERROR_H

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err_doit(int, int, const char*, va_list);
void err_sys(const char*, ...);
void err_exit(int, const char*, ...);
void err_quit(const char*, ...);
void err_msg(const char*, ...);

#endif  // ERROR_H
