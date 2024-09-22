
#include "chess/board.h"
#include "helper/binaryutil.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
  printf("BINARY:\n" ULL_BINARY_FORMAT,
         ULL_TO_BINARY(RANK1 | RANK2 | RANK7 | RANK8));
  /*
  char *command;
  while (scanf("%s", command)) {
    if (!strcmp(command, "position")) {
      printf("%s", "yes");
    } else {
      printf("%s", "no");
    }
  }
  return 0;
  */
}
