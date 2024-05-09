#include <regex.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/error.h"

struct array_list {
  regex_t* regex;
  uint16_t len;
  uint16_t cap;
};

void init_list(struct array_list* list) {
  list = malloc(sizeof(struct array_list));
  list->regex = malloc(sizeof(regex_t));
}

void push_data(struct array_list* list, regex_t regex_data) {
  u_int16_t length = list->len;
  u_int16_t capacity = list->cap;

  ++length;
  if (length >= capacity) {
    const uint16_t N = 1024;

    if (capacity <= N) {
      capacity += capacity / 4;
    } else {
      capacity *= 2;
    }
  }

  regex_t* regex = list->regex;
  regex = realloc(regex, sizeof(regex_t) * capacity);
  if (!regex) err_sys("");

  list->len = length;
  list->cap = capacity;
  regex[length] = regex_data;
}

void free_list(struct array_list* list) {
  while (list++) regfree(list->regex);
  if (list) free(list);
}
