
#!/bin/bash

cd ~/repos/c/WizardsChess/test/chess
echo `pwd`

executable=test-generate-knight-moves

gcc "generate-knight-moves-test.c" "../../src/chess/move.c" "../../src/chess/constants.c" "../../src/chess/board.c" -o $executable -g -Wall -Wextra -pedantic

./$executable

#rm $executable
