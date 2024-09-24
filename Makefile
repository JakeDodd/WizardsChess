CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic

WizardsChess: src/engine.o src/chess/board.o src/chess/constants.o
	$(CC) src/engine.o src/chess/board.o src/chess/constants.o -o wizardschess
