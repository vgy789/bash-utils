#include <getopt.h>
#ifndef _OPTIONS_H
#define _OPTIONS_H

static struct option longopts[] = {
    {"--number-nonblank", no_argument, NULL, 'b'},
    {NULL, no_argument, NULL, 'e'},
    {NULL, no_argument, NULL, 'v'},
    {"--number", no_argument, NULL, 'n'},
    {"--squeeze-blank", no_argument, NULL, 's'},
    {NULL, no_argument, NULL, 't'},
    {NULL, no_argument, NULL, 'E'},  // UNIX
    {NULL, no_argument, NULL, 'T'},  // UNIX
    {NULL, 0, NULL, 0}};

#endif  //_OPTIONS_H