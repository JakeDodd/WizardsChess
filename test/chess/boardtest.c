#include "../../src/chess/board.h"
#include "../../src/chess/constants.h"
#include "../../src/helper/binaryutil.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Bitboard start = 0xFFFF00000000FFFFULL;
extern Bitboard piece_bitboards[];

void test_init_board_startpos() {
  char *moves = "";
  char *fen = malloc(512 * sizeof(char));
  strcpy(fen, startpos);
  initBoard(fen, moves);
  printf("White Pawns:\n" ULL_BINARY_FORMAT,
         ULL_TO_BINARY(piece_bitboards[W_PAWN]));
  printf("White Rooks:\n" ULL_BINARY_FORMAT,
         ULL_TO_BINARY(piece_bitboards[W_ROOK]));
  printf("All Pieces:\n" ULL_BINARY_FORMAT,
         ULL_TO_BINARY(piece_bitboards[ALL_PIECES]));
  assert(piece_bitboards[ALL_PIECES] == start);
}

int main() { test_init_board_startpos(); }
