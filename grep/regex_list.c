#include "regex_list.h"

struct array_list* init_list() {
  struct array_list* list = malloc(sizeof(struct array_list));
  list->len = 0;
  list->cap = 12;
  list->regex = malloc(sizeof(regex_t) * list->cap);
  return list;
}

void push_data(struct array_list* list, regex_t regex_data) {
  uint16_t length = list->len;
  uint16_t capacity = list->cap;

  ++length;
  if (length > capacity) {
    capacity = capacity * 3 / 2;
    list->regex = realloc(list->regex, sizeof(regex_t) * capacity);
    if (!list->regex) {
      err_sys("memory error");
    }
    list->cap = capacity;
  }
  list->regex[length - 1] = regex_data;
  list->len = length;
}

void free_list(struct array_list* list) {
  if (list) {
    for (size_t i = 0; i < list->len; i++) {
      regfree(&list->regex[i]);
    }
    free(list->regex);
    free(list);
  }
}
