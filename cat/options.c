#include <options.h>

while ((ch = getopt_long(argc, argv, "bevnst", longopts, NULL)) != EOF) {
  switch (ch) {
    case 'b':
      printf("b");
      break;
    case 'e':
      printf("e");
      break;
    case 'v':
      printf("v");
      break;
    case 'n':
      printf("n");
      break;
    case 's':
      printf("s");
      break;
    case 't':
      printf("t");
      break;
    default:
      err_synopsis();
      exit(1);
  }
}