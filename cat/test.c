#include <stdio.h>

int main() {
  char* line = NULL;
  size_t len = 0;
  ssize_t n;

  FILE* file;
  file = fopen("./test/case1.txt", "r");

  while ((n = getline(&line, &len, file)) != -1) {
    while (*line != '\n' || *line != EOF) {
      char ch = *line;
      char* data;
      if (ch >= 0 && ch <= 31) {
        sprintf(data, "^%c", ch + '@');
        puts(data, line);
      }
      if (ch == 127) {
        sprintf(data, "^?");
        fputs(data, line);
      }
      if (ch >= 128 && ch <= 159) {
        sprintf(data, "M-^%c", ch + '@');
        fputs(data, line);
      }
      if (ch >= 160 && ch <= 254) {
        sprintf(data, "M-%c", ch + ' ');
        fputs(data, line);
      }
      if (ch == 255) {
        sprintf(data, "M-^?", file);
        fputs(data, line);
      }
      sprintf(data, "%c", ch);
      fputs(data, line);
      ++line;
    }

    // fwrite(line, n, 1, stdout);
  }

  fclose(file);
}