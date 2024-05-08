#ifndef GREP_UTILITY_H
#define GREP_UTILITY_H

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

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

typedef struct {
    char* pattern;
    bool match_icase;       /* i */
    bool out_invert;        /* v */
    bool count_matches;     /* c */
    bool list_files;        /* l */
    bool out_line;          /* n */
    bool filename_option;   /* h */
    bool suppress_errors;   /* s */
    bool only_matching;     /* o */
} arguments;

void exec_options(arguments, FILE*);
arguments get_options(int, char**);

#endif  // GREP_UTILITY_H
