#!/bin/bash

cd ~/repos/c/WizardsChess/test/chess
echo `pwd`

executable=test-init-board-startpos

gcc "boardtest.c" "../../src/chess/board.c" "../../src/chess/constants.c" "../../src/chess/move.c" -o $executable -g -Wall -Wextra -pedantic

./$executable

#rm $executable
