#pragma once
#ifndef Move_h
#define Move_h

#include "constants.h"

void append_move(Move move, MoveList *move_list);
MoveList parse_move_list(char *moves);
void print_move_list(MoveList movelist);

// Move generation functions
void generate_pseudo_legal_pawn_moves(GameState *gs, Bitboard empty_or_enemy,
                                      Bitboard pawns, MoveList *moves);

void generate_pseudo_legal_knight_moves(Bitboard empty_or_enemy,
                                        Bitboard knights, MoveList *moves);

void generate_pseudo_legal_king_moves(Bitboard empty_or_enemy, Bitboard king,
                                      MoveList *moves);

#endif
