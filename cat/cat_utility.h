#ifndef CAT_UTILITY_H
#define CAT_UTILITY_H

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/error.h"

#if defined(__APPLE__)
#define SYNOPSIS \
  "usage: s21_cat [-bevnst] [--number-nonblank] [--number] [file ...]"
static char const short_options[] = "bevnst";
#elif defined(__linux__)
#include <unistd.h>

#define SYNOPSIS \
  "usage: s21_cat [-bEevnsTt] [--number-nonblank] [--number] \
[--squeeze-blank] [file ...]"
static char const short_options[] = "bEevnsTt";
#endif

enum { maxline = 4096 };

enum flag {
  number_nonblank = 1,       /* -b */
  show_nonprinting = 1 << 2, /* -v */
  number = 1 << 3,           /* -n */
  squeeze_blank = 1 << 4,    /* -s */
  show_ends = 1 << 5,        /* -E */
  show_tabs = 1 << 6,        /* -T */
  is_filename = 1 << 10,
};

static struct option const long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"show-ends-nonprinting", no_argument, NULL, 'e'},
    {"show-nonprinting", no_argument, NULL, 'v'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-tabs-nonprinting", no_argument, NULL, 't'},
    {"show-ends", no_argument, NULL, 'E'},  // LINUX
    {"show-tabs", no_argument, NULL, 'T'},  // LINUX
    {NULL, 0, NULL, 0}};

void exec_options(uint16_t, FILE*);
uint16_t get_options(int, char**);
_Bool get_option(uint16_t option, uint16_t flags);
uint16_t set_option(uint16_t target, uint16_t flags, _Bool status);

void simple_cat(uint16_t flags);

_Bool exec_number(_Bool reset_flag, char ch, FILE* fp);
char exec_nonprinting(char ch);
void exec_ends(int ch);
_Bool exec_number_nonblank(_Bool reset_flag, char ch, FILE* fp);
_Bool exec_squeeze_blank(char ch, FILE* fp);

#endif  // CAT_UTILITY_H
