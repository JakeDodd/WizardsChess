
#include "chess/board.h"
#include "chess/constants.h"
#include "helper/binaryutil.h"
#include "helper/stringutil.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *wait(void *vptr) {
  sleep(10);

  printf("Done\n");
  return 0;
}

int main() {
  pthread_t search_thread;
  char *command = malloc(512 * sizeof(char));
  while (1) {
    fgets(command, 512, stdin);
    char *token = strtok(command, " ");
    if (strcmp(token, "quit") == 0) {
      return EXIT_SUCCESS;
    } else if (strcmp(token, "uci") == 0) {
      printf("uciok\n");
    } else if (strcmp(token, "ucinewgame") == 0) {
      printf("you still need to implement this jake\n");
    } else if (strcmp(token, "isready") == 0) {
      printf("I think this response needs to wait on running threads\n");
      printf("readyok\n");
    } else if (strcmp(token, "stop") == 0) {
      printf("You still need to implement this jake: ask the engine to stop "
             "calculating and return its best move so far\n");
    } else if (strcmp(token, "go") == 0) {
      printf("you still need to implement this jake\n");
    } else if (strcmp(token, "position") == 0) {
      char *fen = strtok(NULL, " ");
      char *fenstring = malloc(512 * sizeof(char));
      strcpy(fenstring, fen);
      char *gamestate = malloc(512 * sizeof(char));
      char *gs = strtok(NULL, "\0");
      if (strcmp(fenstring, "startpos") == 0) {
        strcpy(fenstring, startpos);
        strcpy(gamestate, startstate);
      }
      strcat(gamestate, gs);
      init_board(fenstring, gamestate);
    } else {
      int err = pthread_create(&search_thread, NULL, wait, NULL);
      printf("I dont support your command yet loser\n");
    }
  }
  return 0;
}
