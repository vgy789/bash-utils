#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "error.h"

#if defined(__APPLE__) || defined(__MACH__)
#define MAC
#elif defined(__linux__) || defined(linux) || defined(__linux)
#define LINUX
#endif

#define MAC_SYNOPSIS "usage: s21_cat [-bevnst] file"
#define LINUX_SYNOPSIS \
  "usage: s21_cat [-bevnstET] [--number-nonblank] [--number] \
[--squeeze-blank] file"

void errcat_synopsis(void);

#endif  // _PLATFORM_H
