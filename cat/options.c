#include "./options.h"

uint16_t get_options(int argc, char* argv[]) {
  char ch;
  uint16_t flag = number_nonblank;

  while ((ch = getopt_long(argc, argv, "bevnst", longopts, NULL)) != EOF) {
    switch (ch) {
      case 'b':
        flag |= number_nonblank;
        break;
      case 'e':
        flag |= show_ends_nonprinting;
        break;
      case 'v':
        flag = show_nonprinting;
        break;
      case 'n':
        flag = number;
        break;
      case 's':
        flag = squeeze_blank;
        break;
      case 't':
        flag |= show_tabs_nonprinting;
        break;
      case 'E':
        flag |= show_ends;
        break;
      case 'T':
        flag |= show_tabs;
        break;
      case '?':
        err_synopsis();
        flag = 0;
        // default:
        //   err_synopsis();
        //   flag = 0;
    }
  }
  return flag;
}