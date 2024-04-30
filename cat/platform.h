#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "error.h"

#if defined(__APPLE__)
#define OS MAC
#elif defined(linux)  // defined(__unix__) |
#define OS LINUX
#endif

#define MAC_SYNOPSIS "usage: s21_cat [-benstv] file"
#define LINUX_SYNOPSIS \
  "usage: s21_cat [-bensTv] [--number-nonblank] [--number] \
[--squeeze-blank] file"

void err_synopsis(void);

#endif  // _PLATFORM_H
