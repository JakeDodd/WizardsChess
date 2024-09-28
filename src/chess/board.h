#pragma once
#ifndef Board_h
#define Board_h

#include "../helper/binaryutil.h"
#include "constants.h"

extern const Bitboard RANKS[8];
extern const Bitboard FILES[8];

// Bitboard related functions

void init_board(char *fen, char *gamestate);
void clear_piece_bitboards();
Bitboard get_all_pieces();
Bitboard square_bb(enum Square s);

// Square related functions

enum Square sq_str(char *str);
enum Square lsb(Bitboard b);
enum Square pop_lsb(Bitboard *b);
enum file to_file(enum Square s);
enum rank to_rank(enum Square s);

// Game State related functions

void init_game_state(char *gs_str);
void print_game_state();

#endif // !Board_h
