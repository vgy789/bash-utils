#ifndef CAT_UTILITY_H
#define CAT_UTILITY_H

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./error.h"
#include "./platform.h"

#define MAXLINE 4096

enum flag {
  number_nonblank = 1,
  show_nonprinting = 1 << 2,
  number = 1 << 3,
  squeeze_blank = 1 << 4,
  show_ends = 1 << 5,
  show_tabs = 1 << 6,
  is_filename = 1 << 10,
};

void exec_options(uint16_t, FILE*);
uint16_t get_options(int, char**);
_Bool get_option(uint16_t option, uint16_t flags);
uint16_t set_option(uint16_t target, uint16_t flags, _Bool status);

void simple_cat(uint16_t flags);

_Bool exec_number(_Bool reset_flag, char ch, FILE* file);
char exec_nonprinting(char ch);
void exec_ends(int ch);
_Bool exec_number_nonblank(_Bool reset_flag, char ch, FILE* file);
_Bool exec_squeeze_blank(char ch, FILE* file);

#endif  // CAT_UTILITY_H
