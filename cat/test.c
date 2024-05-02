#include <stdio.h>
#include <string.h>

void insert_str(char* dest, const char* str, const char* substr, size_t pos) {
  strncpy(dest, str, pos - 1);
  dest[pos - 1] = '\0';
  strcat(dest, substr);
  strcat(dest, str + pos);
}

int main() {
  char ch = '8';
  const char* source = "abcdefg_lrmK__s\nadfsa";
  char result[4096] = {0};
  char add_str[3];

  sprintf(add_str, "^%c", '@');

  for (int i = 0; source[i] != '\n' && source[i] != EOF; ++i) {
    const size_t pos = i + 1;

    if (source[i] == 'K') {
      insert_str(result, source, add_str, pos);
    }
  }
  printf("%s", result);
}
