#include "board.h"
#include "constants.h"

const Bitboard RANK1 = 0xFF;
const Bitboard RANK2 = RANK1 << (8 * 1);
const Bitboard RANK3 = RANK1 << (8 * 2);
const Bitboard RANK4 = RANK1 << (8 * 3);
const Bitboard RANK5 = RANK1 << (8 * 4);
const Bitboard RANK6 = RANK1 << (8 * 5);
const Bitboard RANK7 = RANK1 << (8 * 6);
const Bitboard RANK8 = RANK1 << (8 * 7);

static Bitboard piece_bitboards[PIECE_NB];
static char **moves;

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
void initBoard(char *fen, char **moves) {}
