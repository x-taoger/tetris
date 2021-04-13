#ifndef __MINE_MAP_H
#define __MINE_MAP_H

#include <vector>
#include <string>
#include <cstdint>
#include "coordinate.h"
#include "common.h"

struct Cell {
    Cell(bool a = false, int b = 0, int c = ' ') : takeFlag(a), color(b), padding(c) {}
    bool takeFlag;
    int color;
    int padding;
};

class Map {
protected:
    int length;
    int height;
    std::vector<Cell*> allCell;
public:
    /* todo : take and free pos should take/give sem */
    uint32_t TakePos(Coordinate &position, Coordinates &relativePos, int color = 0, int padding = 0);
    uint32_t FreePos(Coordinate &position, Coordinates &relativepos);
    uint32_t PrintString(Coordinate &position, std::string str, int color = 0);
    virtual void Show(void) {} /* only main map can show */
    Map* SpiltSubMap(Coordinate &pos, int len, int high);
    uint32_t PaintTheCloseWall(Coordinate &pos, int len, int high, int color, int padding);
    enum e_cellCtrl {OK = 0, OVER_LOAD = 1, NO_FREE = 2};
    enum e_color {
        COLOR_NONE = 0, 
        COLOR_BLACK, 
        COLOR_RED, 
        COLOR_GREEN,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_PURPLE,
        COLOR_DEEP_GREEN,
        COLOR_WHITE,
        COLOR_NUM
    };
    std::string colorStr[COLOR_NUM] = {
        "\033[0m",
        "\033[0;30m",
        "\033[0;31m",
        "\033[0;32m",
        "\033[0;33m",
        "\033[0;34m",
        "\033[0;35m",
        "\033[0;36m",
        "\033[0;37m",
    };
};


class SubMap : public Map {
public:
    SubMap(std::vector<Cell*> &parentCells, Coordinate &pos, int len, int high);
};

class MainMap : public Map {
public:
    MainMap(int len, int high);
    ~MainMap();
    void Show(void);
};

#endif
