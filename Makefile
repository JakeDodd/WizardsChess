
WizardsChess: src/engine.c 
	$(CC) src/engine.c src/chess/board.c src/chess/constants.c -o wizardschess -g -Wall -Wextra -pedantic
