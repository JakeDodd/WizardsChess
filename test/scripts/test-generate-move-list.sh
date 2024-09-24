#!/bin/bash

basedir=&(dirname "$0")
echo "$basedir"
cd ./test/chess

executable=test-generate-move-list

gcc "movetest.c" "../../src/chess/move.c" "../../src/chess/constants.c" -o $executable -g -Wall -Wextra -pedantic

./$executable

#
