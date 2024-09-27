CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic
DEPS = src/engine.h src/chess/board.h src/chess/constants.h src/chess/move.h src/helper/stringutil.h
OBJ = src/engine.o src/chess/board.o src/chess/constants.o src/chess/move.o src/helper/stringutil.o

BDIR=build

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/wizardschess: $(OBJ)
	if [ ! -d build ]; then mkdir build; fi
	$(CC) $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm $(OBJ)
