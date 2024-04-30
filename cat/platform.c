#include "platform.h"

void err_synopsis(void) {
#if OS == MAC
  err_msg(MAC_SYNOPSIS);
#elif OS == LINUX
  err_msg(LINUX_SYNOPSIS);
#endif
}