#pragma once
#ifndef Constants_h
#define Constants_h

#include <stdbool.h>
#include <stdint.h>

#define max(x, y) (((x) >= (y)) ? (x) : (y))

extern const char *startpos;
extern const char *startstate;

enum pieceType { NO_PIECE_TYPE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum piece {
  NO_PIECE,
  W_PAWN,
  W_KNIGHT,
  W_BISHOP,
  W_ROOK,
  W_QUEEN,
  W_KING,
  B_PAWN,
  B_KNIGHT,
  B_BISHOP,
  B_ROOK,
  B_QUEEN,
  B_KING,
  ALL_PIECES,
  PIECE_NB
};

enum rank { R1 = 0, R2, R3, R4, R5, R6, R7, R8 };

enum file { FA = 0, FB, FC, FD, FE, FF, FG, FH };

enum Square {
  A1,
  B1,
  C1,
  D1,
  E1,
  F1,
  G1,
  H1,
  A2,
  B2,
  C2,
  D2,
  E2,
  F2,
  G2,
  H2,
  A3,
  B3,
  C3,
  D3,
  E3,
  F3,
  G3,
  H3,
  A4,
  B4,
  C4,
  D4,
  E4,
  F4,
  G4,
  H4,
  A5,
  B5,
  C5,
  D5,
  E5,
  F5,
  G5,
  H5,
  A6,
  B6,
  C6,
  D6,
  E6,
  F6,
  G6,
  H6,
  A7,
  B7,
  C7,
  D7,
  E7,
  F7,
  G7,
  H7,
  A8,
  B8,
  C8,
  D8,
  E8,
  F8,
  G8,
  H8
};

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

typedef unsigned long Bitboard;

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

#endif // !Constants_h
