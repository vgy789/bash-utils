#ifndef _OPTIONS_H
#define _OPTIONS_H

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
  show_ends = 1 << 6,
  show_tabs = 1 << 7,
  is_filename = 1 << 10,
};

uint16_t get_options(int, char**);
uint16_t set_option(uint16_t target, uint16_t flags, _Bool status);
void exec_options(uint16_t, FILE*);
_Bool exec_squeeze_blank(char ch, FILE* file);
void character_process(char* line, u_int16_t flags, FILE* file);
_Bool get_option(uint16_t option, uint16_t flags);
void simple_cat(uint16_t flags);
//_Bool exec_number_nonblank(char* line, _Bool reset);
char exec_show_nonprinting(char ch);
_Bool exec_number(_Bool reset_flag, char ch, FILE* file);
void exec_show_ends(int ch);
_Bool exec_number_nonblank(_Bool reset_flag, char ch, FILE* file);

// static void insert_str(char* dest, const char* str, const char* substr,
// size_t pos);

#endif  // _OPTIONS_PROCESSING_H
