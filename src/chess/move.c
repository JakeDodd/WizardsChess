#include "move.h"
#include "../helper/binaryutil.h"
#include "board.h"
#include "constants.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int knightmoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};
const int kingmoves[] = {-9, -8, -7, -1, 1, 7, 8, 9};
const int pawnmoves[] = {7, 8, 9, 16};

void append_move(Move move, MoveList *move_list) {
  Move *new_moves = realloc(move_list->moves, move_list->len + 1);
  if (new_moves == NULL)
    return;
  new_moves[move_list->len] = move;
  move_list->moves = new_moves;
  move_list->len += 1;
}

Bitboard valid_move(enum Square from, int move) {
  int dest = from + move;
  return (dest >= A1 && dest <= H8) &&
                 max(abs((int)(to_rank(dest) - to_rank(from))),
                     abs((int)(to_file(dest) - to_file(from)))) <= 2
             ? square_bb(dest)
             : 0;
}

Move create_move(enum Square from, enum Square to) { return to << 6 | from; }

void generate_pseudo_legal_pawn_moves(GameState *gs, Bitboard pawns,
                                      Bitboard empty_or_enemy,
                                      MoveList *moves) {
  enum rank second_r = gs->turn_to_move == WHITE ? R2 : R7;
  int direction = gs->turn_to_move == WHITE ? 1 : -1;
  Bitboard pawns_on_two = RANKS[second_r] & pawns;
  pawns = pawns_on_two ^ pawns;
  while (pawns) {
    enum Square from = pop_lsb(&pawns);
    Bitboard attacks = 0;
    for (int i = 0; i < 3; i++) {
      attacks |= 0;
    }
  }
}

void generate_pseudo_legal_knight_moves(Bitboard empty_or_emeny,
                                        Bitboard knights, MoveList *moves) {
  while (knights) {
    enum Square from = pop_lsb(&knights);
    Bitboard attacks = 0;
    for (int i = 0; i < 8; i++) {
      attacks |= valid_move(from, knightmoves[i]);
    }
    attacks &= empty_or_emeny;
    while (attacks) {
      enum Square to = pop_lsb(&attacks);
      append_move(create_move(from, to), moves);
    }
  }
  printf("knight moves %d\n", moves->len);
}

void generate_pseudo_legal_king_moves(Bitboard empty_or_enemy, Bitboard king,
                                      MoveList *moves) {
  enum Square from = pop_lsb(&king);
  Bitboard attacks = 0;
  for (int i = 0; i < 8; i++) {
    attacks |= valid_move(from, kingmoves[i]);
  }
  attacks &= empty_or_enemy;
  while (attacks) {
    enum Square to = pop_lsb(&attacks);
    append_move(create_move(from, to), moves);
  }
  printf("king moves %d\n", moves->len);
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
    append_move(move, &movelist);
  } while ((m = strtok(NULL, " ")) != NULL);
  print_move_list(movelist);
  return movelist;
}

void print_move_list(MoveList movelist) {
  for (int i = 0; i < movelist.len; i++) {
    int src = *(movelist.moves + i) & 0x003F;
    int dest = *(movelist.moves + i) >> 6;
    printf("%c%c%c%c\n", src % 8 + 97, src / 8 + 48, dest % 9 + 97,
           dest / 8 + 48);
    printf("src sq: %d\n", *(movelist.moves + i) & 0x003F);
    printf("dest sq: %d\n", *(movelist.moves + i) >> 6);
  }
}

/*
 *
 * 57 58 59 60 61 62 63 64
 * 49 50 51 52 53 54 55 56
 * 41 42 43 44 45 46 47 48
 * 33 34 35 36 37 38 39 40
 * 25 26 27 28 29 30 31 32
 * 17 18 19 20 21 22 23 24
 *  9 10 11 12 13 14 15 16
 *  1  2  3  4  5  6  7  8
 *
 * 000000
 *
 *
 *
 * */
