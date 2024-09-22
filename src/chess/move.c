#include "move.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void append_move(Move *move, MoveList *move_list) {
  Move *new_moves = realloc(move_list->moves, 1);
  if (new_moves == NULL)
    return;
  memcpy(&new_moves[move_list->len], move, 1);
  move_list->moves = new_moves;
  move_list->len += 1;
}
