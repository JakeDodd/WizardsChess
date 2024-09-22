#include "constants.h"
#include "move.h"
#include <stdbool.h>

typedef unsigned long Bitboard;

extern const Bitboard RANKS[8];
extern const Bitboard FILES[8];

void init_board(char *fen, char *moves);
void clear_piece_bitboards();
Bitboard get_all_pieces();

typedef struct GameState {
  bool white_to_move;
  MoveList move_list;
} GameState;
