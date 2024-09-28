#include "stringutil.h"
#include <string.h>

void prepend(char *buf, char *s, int len) {
  int length = strlen(buf);
  memmove(buf + len, buf, length + 1);
  memcpy(buf, s, len);
}
