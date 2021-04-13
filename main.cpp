#include <stdio.h>
#include "map.h"
#include "common.h"
#include "tetris.h"


void StartGame(void) {
    TetrisGame *game = new TetrisGame();
    game->StartGame();
}

int main(int argc, char *argv[]) {
    StartGame();
    return 0;
}
