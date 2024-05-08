#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

int main() {
    int n = 0;
    FILE * file = fopen("a.txt", "r");
    char line[] = "fospdaijfoshellodiajf\nasdfsdafhello";
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "hello", REG_EXTENDED);
    if (reti) {
        exit(EXIT_FAILURE);
    }

    reti = regexec(&regex, line, 0, NULL, 0);
    printf("%s", line);

    regfree(&regex);
}
