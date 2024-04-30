#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "./error.h"
#include "./platform.h"

#define MAXLINE 4096

enum flag {
  number_nonblank = 1,
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
    {"--show-ends", no_argument, NULL, 'E'},  // LINUX
    {"--show-tabs", no_argument, NULL, 'T'},  // LINUX
    {NULL, 0, NULL, 0}};

uint16_t get_options(int, char**);
void exec_options(uint16_t, FILE *);

uint16_t set_flag(uint16_t, uint16_t);
uint16_t unset_flag(uint16_t, uint16_t);

void simple_cat(void);
void b();
void e();
void v();
void n();
void s();
void t();
void E();
void T();

#endif  // _OPTIONS_PROCESSING_H
