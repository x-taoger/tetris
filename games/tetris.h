#ifndef __MINE_TETRIS_H
#define __MINE_TETRIS_H

#include "coordinate.h"
#include "map.h"
#include "tetrisblock.h"

class BlockInMap {
private:
    Map *inThisMap;
public:
    Coordinate pos;
    TetrisBlock *block;
    BlockInMap(Map *map, int x, int y);
    ~BlockInMap();
    uint32_t TakeMap(void);
    uint32_t FreeMap(void);
    uint32_t GoUp(void);
    uint32_t GoDown(void);
    uint32_t GoLeft(void);
    uint32_t GoRight(void);
    bool IsPosVaild(void);
};


class TetrisGame {
public:
    void StartGame(void);
};

#endif
