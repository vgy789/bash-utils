#include "platform.h"

#define LINUX
void errcat_synopsis(void) {
#ifdef MAC
  err_sys(MAC_SYNOPSIS);
#elif defined(LINUX)
  err_sys(LINUX_SYNOPSIS);
#endif
}