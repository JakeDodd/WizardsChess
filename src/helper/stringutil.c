#include "stringutil.h"
#include <stdlib.h>
#include <string.h>

void prepend(char *buf, char *s, int len) {
  int length = strlen(buf);
  char *new = realloc(s, length + len);
  if (new == NULL)
    return;
  memcpy(&new[len], buf, length);
  buf = new;
}
