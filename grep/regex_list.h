#ifndef REGEX_LIST_H
#define REGEX_LIST_H

#include <regex.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/error.h"

struct array_list {
  regex_t* regex;
  uint16_t len;
  uint16_t cap;
};

struct array_list* init_list();
void push_data(struct array_list* list, regex_t regex_data);
void free_list(struct array_list* list);

#endif  // REGEX_LIST_H