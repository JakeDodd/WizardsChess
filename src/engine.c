
#include "chess/board.h"
#include "chess/constants.h"
#include "helper/binaryutil.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  pthread_t *search_thread = malloc(sizeof(pthread_t));
  char *command = malloc(512 * sizeof(char));
  while (1) {
    fgets(command, 512, stdin);
    char *token = strtok(command, " ");
    if (strcmp(token, "position") == 0) {
      char *fen = strtok(NULL, " ");
      if (strcmp(fen, "startpos"))
        strcpy(fen, startpos);
      initBoard(fen, command);
    } else {
      printf("%s", "no");
    }
  }
  return 0;
}
