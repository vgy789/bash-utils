#ifndef GREP_UTILITY_H
#define GREP_UTILITY_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/error.h"
#include "./regex_list.h"
#include "grep_utility.h"

#define SYNOPSIS \
  "usage: s21_grep [-cehilnosv] [-e pattern] [-f file] [file ...]"

enum { maxline = 4096 };

typedef struct {
  bool pattern_e;       /* e + */
  bool match_icase;     /* i + */
  bool out_invert;      /* v */
  bool count_matches;   /* c + */
  bool list_files;      /* l */
  bool out_line;        /* n */
  bool filename_option; /* h */
  bool suppress_errors; /* s + */
  bool patterns_file;   /* f */
  bool only_matching;   /* o */
} arguments;

static char const short_options[] = "ce:f:hilnosv";

static struct option const long_options[] = {
    {"regexp", required_argument, NULL, 'e'},
    {"file", required_argument, NULL, 'f'},
    {"ignore-case", no_argument, NULL, 'i'},         // match_icase
    {"invert-match", no_argument, NULL, 'v'},        // out_invert
    {"count", no_argument, NULL, 'c'},               // count_matches
    {"files-with-matches", no_argument, NULL, 'l'},  // list_files
    {"line-number", no_argument, NULL, 'n'},         // out_line
    {"no-filename", no_argument, NULL, 'h'},         // filename_option
    {"no-messages", no_argument, NULL, 's'},         // suppress_errors
    {"only-matching", no_argument, NULL, 'o'},       // only_matching
    {NULL, 0, NULL, 0}};

struct grep_settings {
  struct array_list* patterns;
  arguments options;
};

void regex_run(FILE* fp, struct grep_settings grep_sett);
struct grep_settings parse_grep_options(int argc, char* argv[]);
regex_t compile_expression(const char* pattern, arguments args);

#endif  // GREP_UTILITY_H
