#ifndef GREP_UTILITY_H
#define GREP_UTILITY_H

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../common/error.h"

#define SYNOPSIS "usage: s21_grep [-cehilnosv] [-e pattern] [-f file] [file ...]"

static char const short_options[] = "ce:f:hilnosv";

enum {maxline = 4096};

static struct option const long_options[] = {
    {"regexp", required_argument, NULL, 'e'},
    {"file", required_argument, NULL, 'f'},
    {"ignore-case", no_argument, NULL, 'i'},        // match_icase
    {"invert-match", no_argument, NULL, 'v'},       // out_invert
    {"count", no_argument, NULL, 'c'},              // count_matches
    {"files-with-matches", no_argument, NULL, 'l'}, // list_files
    {"line-number", no_argument, NULL, 'n'},        // out_line
    {"no-filename", no_argument, NULL, 'h'},        //filename_option
    {"no-messages", no_argument, NULL, 's'},        // suppress_errors
    {"only-matching", no_argument, NULL, 'o'},      // only_matching
    {NULL, 0, NULL, 0}};

struct arguments {
    bool match_icase;
    bool out_invert;
    bool count_matches;
    bool list_files;
    bool out_line;
    bool filename_option;
    bool suppress_errors;
    bool only_matching;
} args;

void exec_options(uint16_t, FILE*);
uint16_t get_options(int, char**);

#endif  // GREP_UTILITY_H
