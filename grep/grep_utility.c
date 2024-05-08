#include "./grep_utility.h"

arguments get_options(int argc, char* argv[]) {
  int opt;
  arguments args;

  while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
    switch (opt) {
    case 'e':
    // args.e = optarg;
      args.pattern = optarg;
      break;
    case 'f':
      // fp = fopen (optarg, "r");
      break;
    case 'i':
      args.match_icase = true;
      break;
    case 'v':
      args.out_invert = true;
      break;
    case 'c':
      args.count_matches = true;
      break;
    case 'l':
      args.list_files = true;
      break;
    case 'n':
      args.out_line = true;
      break;
    case 'h':
      args.filename_option = true;
      break;
    case 's':
      args.suppress_errors = true;
      break;
    case 'o':
      args.only_matching = true;
      break;
    case '?':
      err_sys(SYNOPSIS);
    }
  }

  if (optind < argc) {
    // fp * fp = fopen(path, "r");
  }

  return args;
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; ++i) {
    putchar(line[i]);
  }

}

void process_line() {

}

void process_file(arguments arg, char* path, regex_t regex) {
  FILE * fp = fopen(path, "r");
  if (fp == NULL) {
  if(!arg.s) perror(path);
  // err_sys("%s: %s", argv[0], argv[i]);
  exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  read = getline(&line, &memlen, fp);

  while (read != EOF) {
    read = getline(&line, &memlen, fp);
  }
  
  free(line);
  fclose(fp);
}

void exec_options(arguments, fp*) {
  int n = getline();
  while (n != EOF)
  {
    /* code */
  }
  
}
