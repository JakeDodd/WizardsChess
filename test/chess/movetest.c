#include "../../src/chess/move.h"
#include "../../src/chess/constants.h"
#include "../../src/helper/binaryutil.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_generate_move_list() { generate_move_list("e2e4 e7e5"); }

int main() { test_generate_move_list(); }
