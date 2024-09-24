#include "constants.h"
#include "move.h"
#include <stdbool.h>

typedef unsigned long Bitboard;

extern const Bitboard RANKS[8];
extern const Bitboard FILES[8];

typedef struct CastleRights {
  bool W_OO;
  bool W_OOO;
  bool B_OOO;
  bool B_OO;
} CastleRights;

typedef struct GameState {
  bool white_to_move;
  MoveList move_list;
  CastleRights castle_rights;
  enum Square en_passant_target;
} GameState;

// Bitboard related functions

void init_board(char *fen, char *gamestate);
void clear_piece_bitboards();
Bitboard get_all_pieces();
Bitboard square_bb(enum Square s);

// Square related functions

enum Square sq_str(char *str);

// Game State related functions

void init_game_state(char *gs_str);
void print_game_state();
