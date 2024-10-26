#include "../../src/chess/board.h"
#include "../../src/chess/constants.h"
#include "../../src/chess/move.h"
#include "../../src/helper/binaryutil.h"

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Bitboard start = 0xFFFF00000000FFFFULL;
Bitboard custom = 0xBFF720080804F7FDULL;

void test_init_board_startpos() {
  char *moves = "w KQkq - moves e2e4 e7e5";
  char *fen = malloc(512 * sizeof(char));
  strcpy(fen, startpos);
  init_board(fen, moves);
  Bitboard all = get_all_pieces();

  assert(all == start);
}

void test_init_board_custom() {
  char *game_state = "w KQkq - moves g1f3 b8c6";
  char *fen = "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R";
  init_board(fen, game_state);
  Bitboard all = get_all_pieces();

  assert(all == custom);
}

int main() {
  test_init_board_startpos();
  test_init_board_custom();
}
