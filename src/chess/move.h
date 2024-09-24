#ifndef Move_h
#define Move_h

#include <stdint.h>
#include <stdio.h>

/**
 * We store the information for a move in 16 bits
 * bit 0-5: origination square
 * bit 6-11: destination square
 * bit 12-13: special moves: promotion 0, en passant 1, castling 2
 * bit 14-15: promotion piece type knight 0, queen 1 <-- this doesnt allow for
 * promotion to either bishop or rook, have to think about that
 * **/
typedef uint16_t Move;
typedef struct MoveList {
  int len;
  Move *moves;
} MoveList;

void append_move(Move *move, MoveList *move_list);
MoveList generate_move_list(char *moves);
void print_move_list(MoveList movelist);

#endif
