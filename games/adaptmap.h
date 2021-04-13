#ifndef __MINE_ADAPTMAP_H
#define __MINE_ADAPTMAP_H

#include "map.h"


class TetrisGameMap : public SubMap {
public:
    TetrisGameMap(std::vector<Cell*> &parentCells, Coordinate &pos, int len, int high) : SubMap(parentCells, pos, len, high) {}
    int ClearLine(void);
};

class TetrisMainMap : public MainMap {
public:
    TetrisMainMap(int len, int high) : MainMap(len, high) {}
    TetrisGameMap* SpiltTetrisGameMapWithWall(Coordinate &pos, int len, int high, int wallColor = COLOR_NONE, int padding = '.');
};

#endif
