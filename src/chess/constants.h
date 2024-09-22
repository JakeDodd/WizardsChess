#ifndef Constants_h
#define Constants_h

extern const char *startpos;

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

#endif // !Constants_h
