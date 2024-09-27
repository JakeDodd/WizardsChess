#include "move.h"
#include "board.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_move(Move *move, MoveList *move_list) {
  Move *new_moves = realloc(move_list->moves, move_list->len + 1);
  if (new_moves == NULL)
    return;
  new_moves[move_list->len] = *move;
  move_list->moves = new_moves;
  move_list->len += 1;
}

MoveList parse_move_list(char *moves) {
  char *cpy = malloc(512 * sizeof(char));
  strcpy(cpy, moves);

  MoveList movelist;
  movelist.len = 0;
  movelist.moves = NULL;
  char *m = strtok(cpy, " ");
  do {
    uint16_t src = sq_str(m);
    uint16_t dest = sq_str(m + 2);
    Move move = src | (dest << 6);
    append_move(&move, &movelist);
  } while ((m = strtok(NULL, " ")) != NULL);
  return movelist;
}

void print_move_list(MoveList movelist) {
  for (int i = 0; i < movelist.len; i++) {
    printf("src sq: %d\n", *(movelist.moves + i) & 0x003F);
    printf("dest sq: %d\n", *(movelist.moves + i) >> 6);
  }
}
