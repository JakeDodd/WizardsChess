#include "../../src/chess/move.h"
#include <time.h>

void test_generate_knight_moves() {
  MoveList moves;
  moves.len = 0;
  moves.moves = NULL;

  Bitboard enemy_or_empty = 0xFFFFFFFFFFFF0000ULL;
  Bitboard w_knights = 0x0000000000000042ULL;

  generate_pseudo_legal_knight_moves(1, enemy_or_empty, w_knights, &moves);
}

int main() { test_generate_knight_moves(); }
