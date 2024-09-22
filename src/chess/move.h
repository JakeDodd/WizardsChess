
#include <stdint.h>
#include <stdio.h>

/**
 * We store the information for a move in 16 bits
 * bit 0-5: origination square
 * bit 6-11: destination square
 * bit
 * **/
typedef int16_t Move;
typedef struct MoveList {
  int len;
  Move *moves;
} MoveList;

void append_move(Move *move, MoveList *move_list);
