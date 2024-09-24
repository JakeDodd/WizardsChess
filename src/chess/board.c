#include "board.h"
#include "../helper/binaryutil.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Bitboard piece_bitboards[PIECE_NB];
GameState *gs;

const Bitboard RANKS[8] = {0xFFULL,
                           0xFFULL << (8 * 1),
                           0xFFULL << (8 * 2),
                           0xFFULL << (8 * 3),
                           0xFFULL << (8 * 4),
                           0xFFULL << (8 * 5),
                           0xFFULL << (8 * 6),
                           0xFFULL << (8 * 7)};

const Bitboard FILES[8] = {
    0x8080808080808080ULL,      0x8080808080808080ULL >> 1,
    0x8080808080808080ULL >> 2, 0x8080808080808080ULL >> 3,
    0x8080808080808080ULL >> 4, 0x8080808080808080ULL >> 5,
    0x8080808080808080ULL >> 6, 0x8080808080808080ULL >> 7};

/* *
 * example fen string based on standard chess start position:
 * rnbpkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w AHah -
 * lower case letters denote black pieces, while uppercase denotes white
 * numbers indicate the number of empty squares until the next piece
 * order starts from the top left of the board, each string ending with a /
 * represents a rank, starting with rank 8. each rank starts with the A file
 *
 * the next character denotes which players turn it is to move
 *
 * AHah indicates that both players can castle with both the A and H rooks
 * again, lowercase for black and uppercase for white
 *
 * - indicates that there is no en passant target (if there is, the target
 * square for the capture will be in place of the -
 *
 * Note: this example fen string will never be sent, instead if the position
 * is the standard chess start position "startpos" will be sent in place
 * of the fen string
 * */
void init_board(char *fen, char *gamestate) {
  clear_piece_bitboards();
  short rank = R8;
  short file = FA;
  do {
    switch (*fen) {
    case 'r':
      piece_bitboards[B_ROOK] |= (RANKS[rank] & FILES[file]);
      break;
    case 'n':
      piece_bitboards[B_KNIGHT] |= (RANKS[rank] & FILES[file]);
      break;
    case 'b':
      piece_bitboards[B_BISHOP] |= (RANKS[rank] & FILES[file]);
      break;
    case 'k':
      piece_bitboards[B_KING] |= (RANKS[rank] & FILES[file]);
      break;
    case 'q':
      piece_bitboards[B_QUEEN] |= (RANKS[rank] & FILES[file]);
      break;
    case 'p':
      piece_bitboards[B_PAWN] |= (RANKS[rank] & FILES[file]);
      break;
    case 'R':
      piece_bitboards[W_ROOK] |= (RANKS[rank] & FILES[file]);
      break;
    case 'N':
      piece_bitboards[W_KNIGHT] |= (RANKS[rank] & FILES[file]);
      break;
    case 'B':
      piece_bitboards[W_BISHOP] |= (RANKS[rank] & FILES[file]);
      break;
    case 'K':
      piece_bitboards[W_KING] |= (RANKS[rank] & FILES[file]);
      break;
    case 'Q':
      piece_bitboards[W_QUEEN] |= (RANKS[rank] & FILES[file]);
      break;
    case 'P':
      piece_bitboards[W_PAWN] |= (RANKS[rank] & FILES[file]);
      break;
    case '/':
      rank--;
      file = FA - 1;
      break;
    default:
      break;
    }

    if (*fen > 47 && *fen < 57) {
      file += *fen - '0';
    } else {
      file++;
    }
  } while (*fen++);
  piece_bitboards[ALL_PIECES] = get_all_pieces();
  init_game_state(gamestate);
}

// Section for Bitboard related functions

Bitboard get_all_pieces() {
  Bitboard all_pieces = 0;
  for (int i = NO_PIECE; i < ALL_PIECES; i++)
    all_pieces |= piece_bitboards[i];
  return all_pieces;
}

void clear_piece_bitboards() {
  for (int i = 0; i < PIECE_NB; i++) {
    piece_bitboards[i] = 0ULL;
  }
}

Bitboard square_bb(enum Square s) { return (1ULL << s); }

enum Square sq_str(char *str) {
  return 0x80ULL >> (*str - 97) << (8 * (*(str + 1) - '1'));
}

// Section for GameState related functions
void init_game_state(char *gs_str) {
  char *cp = malloc(strlen(gs_str));
  strcpy(cp, gs_str);

  char *to_move = strtok(cp, " ");
  char *castling = strtok(NULL, " ");
  char *en_passant = strtok(NULL, " ");

  char *move_tok = strtok(NULL, " ");
  char *moves = strtok(NULL, "");

  gs = (GameState *)malloc(sizeof(GameState));
  gs->white_to_move = *to_move == 'w';
  gs->castle_rights.B_OO = strstr(castling, "k") != NULL;
  gs->castle_rights.B_OOO = strstr(castling, "q") != NULL;
  gs->castle_rights.W_OO = strstr(castling, "K") != NULL;
  gs->castle_rights.W_OOO = strstr(castling, "Q") != NULL;
  gs->en_passant_target = *en_passant == '-' ? 0 : sq_str(en_passant);
  gs->move_list = generate_move_list(moves);
}
