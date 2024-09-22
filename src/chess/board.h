#include "constants.h"

typedef unsigned long Bitboard;

extern const Bitboard RANKS[8];
extern const Bitboard FILES[8];

void initBoard(char *fen, char *moves);
Bitboard get_all_pieces();
