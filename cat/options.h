#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>

enum flag {
  number_nonblank = 1 << 0,
  show_ends_nonprinting = 1 << 1,
  show_nonprinting = 1 << 2,
  number = 1 << 3,
  squeeze_blank = 1 << 4,
  show_tabs_nonprinting = 1 << 5,
  show_ends = 1 << 6,
  show_tabs = 1 << 7,
};

static struct option longopts[] = {
    {"--number-nonblank", no_argument, NULL, 'b'},
    {"--show-ends-nonprinting", no_argument, NULL, 'e'},
    {"--show-nonprinting", no_argument, NULL, 'v'},
    {"--number", no_argument, NULL, 'n'},
    {"--squeeze-blank", no_argument, NULL, 's'},
    {"--show-tabs-nonprinting", no_argument, NULL, 't'},
    {"--show-ends", no_argument, NULL, 'E'},  // UNIX
    {"--show-tabs", no_argument, NULL, 'T'},  // UNIX
    {NULL, 0, NULL, 0}};

#endif  // _OPTIONS_H