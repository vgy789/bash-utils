#include "platform.h"

void errcat_synopsis(void) {
#ifdef MAC
  err_msg(MAC_SYNOPSIS);
  exit(EXIT_FAILURE);
#elif defined(LINUX)
  err_msg(LINUX_SYNOPSIS);
  exit(EXIT_FAILURE);
#endif
}