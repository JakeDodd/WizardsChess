#include "board.h"
#include "constants.h"
#include "move.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  gs = (GameState *)calloc(1, sizeof(GameState));
  clear_piece_bitboards();
  short rank = R8;
  short file = FA;
  do {
    switch (*fen) {
    case 'r':
      gs->board[BLACK][ROOK] |= (RANKS[rank] & FILES[file]);
      break;
    case 'n':
      gs->board[BLACK][KNIGHT] |= (RANKS[rank] & FILES[file]);
      break;
    case 'b':
      gs->board[BLACK][BISHOP] |= (RANKS[rank] & FILES[file]);
      break;
    case 'k':
      gs->board[BLACK][KING] |= (RANKS[rank] & FILES[file]);
      break;
    case 'q':
      gs->board[BLACK][QUEEN] |= (RANKS[rank] & FILES[file]);
      break;
    case 'p':
      gs->board[BLACK][PAWN] |= (RANKS[rank] & FILES[file]);
      break;
    case 'R':
      gs->board[WHITE][ROOK] |= (RANKS[rank] & FILES[file]);
      break;
    case 'N':
      gs->board[WHITE][KNIGHT] |= (RANKS[rank] & FILES[file]);
      break;
    case 'B':
      gs->board[WHITE][BISHOP] |= (RANKS[rank] & FILES[file]);
      break;
    case 'K':
      gs->board[WHITE][KING] |= (RANKS[rank] & FILES[file]);
      break;
    case 'Q':
      gs->board[WHITE][QUEEN] |= (RANKS[rank] & FILES[file]);
      break;
    case 'P':
      gs->board[WHITE][PAWN] |= (RANKS[rank] & FILES[file]);
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

  print_board();
  init_game_state(gamestate);
}

// Section for Bitboard related functions

void print_board() {
  char *ascii_board = (char *)calloc(1000, sizeof(char));
  strcat(ascii_board, "+---+---+---+---+---+---+---+---+\n");
  for (int rank = R8; rank >= 0; rank--) {
    for (int file = FH; file >= 0; file--) {
      enum Square sq = rank * 8 + file;
      char piece = get_piece(sq);
      char ascii_piece[4] = "|   ";
      ascii_piece[2] = piece;
      strcat(ascii_board, ascii_piece);
    }
    strcat(ascii_board, "|\n+---+---+---+---+---+---+---+---+\n");
  }
  printf("%s", ascii_board);
  free(ascii_board);
}

char get_piece(enum Square sq) {
  char p = ' ';
  for (int color = 0; color < COLORS; color++) {
    for (int piece = 0; piece < PIECES; piece++) {
      if (square_bb(sq) & gs->board[color][piece]) {
        switch (piece) {
        case PAWN:
          p = color == WHITE ? 'P' : 'p';
          break;
        case KNIGHT:
          p = color == WHITE ? 'N' : 'n';
          break;
        case BISHOP:
          p = color == WHITE ? 'B' : 'b';
          break;
        case ROOK:
          p = color == WHITE ? 'R' : 'r';
          break;
        case QUEEN:
          p = color == WHITE ? 'Q' : 'q';
          break;
        case KING:
          p = color == WHITE ? 'K' : 'k';
          break;
        default:
          break;
        }
      }
    }
  }
  return p;
}

void clear_piece_bitboards() {
  for (int p = 0; p < PIECES; p++) {
    for (int c = 0; c < COLORS; c++) {
      gs->board[c][p] = 0ULL;
    }
  }
}

Bitboard get_all_pieces() {
  Bitboard all = gs->board[WHITE][PAWN] | gs->board[WHITE][KNIGHT] |
                 gs->board[WHITE][BISHOP] | gs->board[WHITE][ROOK] |
                 gs->board[WHITE][QUEEN] | gs->board[WHITE][KING] |
                 gs->board[BLACK][PAWN] | gs->board[BLACK][KNIGHT] |
                 gs->board[BLACK][BISHOP] | gs->board[BLACK][ROOK] |
                 gs->board[BLACK][QUEEN] | gs->board[BLACK][KING];
  return all;
}

Bitboard square_bb(enum Square s) { return (1ULL << s); }

enum Square sq_str(char *str) {
  return ((*str - 96) + ((*(str + 1) - '1') * 8));
}

enum Square pop_lsb(Bitboard *b) {
  enum Square s = lsb(*b);
  *b &= *b - 1;
  return s;
}

enum Square lsb(Bitboard b) {
  // This only works on GNU
  // Will not work on Windows!!
  return __builtin_ctzll(b);
}

enum file to_file(enum Square s) { return s & 7; }

enum rank to_rank(enum Square s) { return s >> 3; }

// Section for GameState related functions

void init_game_state(char *gs_str) {
  char *cp = malloc(strlen(gs_str));
  strcpy(cp, gs_str);

  char *to_move = strtok(cp, " ");
  char *castling = strtok(NULL, " ");
  char *en_passant = strtok(NULL, " ");

  char *move_tok = strtok(NULL, " ");
  char *moves = strtok(NULL, "");

  assert(strcmp(move_tok, "moves") == 0);

  gs->turn_to_move = *to_move == 'w' ? WHITE : BLACK;
  gs->castle_rights.B_OO = strstr(castling, "k") != NULL;
  gs->castle_rights.B_OOO = strstr(castling, "q") != NULL;
  gs->castle_rights.W_OO = strstr(castling, "K") != NULL;
  gs->castle_rights.W_OOO = strstr(castling, "Q") != NULL;
  gs->en_passant_target = *en_passant == '-' ? 0 : sq_str(en_passant);
  gs->move_list = parse_move_list(moves);
  print_game_state();
}

void print_game_state() {
  printf("Turn to move is: %s\n",
         gs->turn_to_move == WHITE ? "white" : "black");
  printf("Black can castle: %s %s\n", gs->castle_rights.B_OO ? "k" : "",
         gs->castle_rights.B_OOO ? "q" : "");
  printf("White can castle: %s %s\n", gs->castle_rights.W_OO ? "k" : "",
         gs->castle_rights.W_OOO ? "q" : "");
  printf("The en passant target is: %d\n", gs->en_passant_target);
}
