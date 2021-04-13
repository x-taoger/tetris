#include <string>
#include <iostream>
#include <cassert>
#include "map.h"
#include "coordinate.h"
#include "common.h"

/* class static value */


/* static value */


/* private function */


/* public function */

uint32_t Map::TakePos(Coordinate &position, Coordinates &relativePos, int color, int padding) {
    int baseX = position.x;
    int baseY = position.y;
    int posIdx = 0;
    uint32_t takeSta = Map::OK;

    for (posIdx = 0; posIdx < relativePos.coors.size(); ++posIdx) {
        int curX = relativePos.coors.at(posIdx).x + baseX;
        int curY = relativePos.coors.at(posIdx).y + baseY;
        if (curX >= this->length || curX < 0 || curY >= this->height || curY < 0) {
            takeSta = Map::OVER_LOAD;
            continue;
        }
        this->allCell.at(curY);
        if (this->allCell.at(curY)[curX].takeFlag) {
            takeSta = Map::NO_FREE;
            break;
        }
        this->allCell.at(curY)[curX].takeFlag = true;
        this->allCell.at(curY)[curX].color = color;
        this->allCell.at(curY)[curX].padding = padding;
    }

    if (takeSta == Map::NO_FREE) {
        for (posIdx -= 1; posIdx >= 0; --posIdx) {
            int curX = relativePos.coors.at(posIdx).x + baseX;
            int curY = relativePos.coors.at(posIdx).y + baseY;
            if (curX >= this->length || curX < 0 || curY >= this->height || curY < 0) {
                continue;
            }
            this->allCell.at(curY)[curX].takeFlag = false;
        }
    }

    return takeSta;
}

uint32_t Map::FreePos(Coordinate &position, Coordinates &relativePos) {
    int baseX = position.x;
    int baseY = position.y;
    uint32_t freeSta = Map::OK;

    for (auto pos : relativePos.coors) {
        int curX = baseX + pos.x;
        int curY = baseY + pos.y;
        if (curX >= this->length || curX < 0 || curY >= this->height || curY < 0) {
            freeSta |= Map::OVER_LOAD;
            continue;
        }
        this->allCell.at(curY)[curX].takeFlag = false;
    }

    return freeSta;
}

uint32_t Map::PrintString(Coordinate &position, std::string str, int color) {
    int curX = position.x;
    int curY = position.y;
    for (auto chr : str) {
        if (curX >= this->length) {
            curX = 0;
            curY += 1;
        }
        if (curY >= this->height) {
            curY = 0;
        }
        this->allCell.at(curY)[curX].takeFlag = true;
        this->allCell.at(curY)[curX].padding = chr;
        this->allCell.at(curY)[curX].color = color;
        curX += 1;
    }
    return Map::OK;
}

Map* Map::SpiltSubMap(Coordinate &pos, int len, int high) {
    if (pos.x < 0 || pos.y < 0 || len < 0 || high < 0) {
        return nullptr;
    }
    if (pos.x + len > this->length || pos.y + high > this->height) {
        return nullptr;
    }
    Coordinate subValidPos(pos.x, pos.y);
    SubMap *subMap = new SubMap(this->allCell, subValidPos, len, high);
    return subMap;
}

/* todo : wall thickness can be set */
uint32_t Map::PaintTheCloseWall(Coordinate &pos, int len, int high, int color, int padding) {
    const int wallThickness = 1;
    if (pos.x < 0 || pos.y < 0 || len < 0 || high < 0) {
        return Map::OVER_LOAD;
    }
    if (pos.x + len > this->length || pos.y + high > this->height) {
        return Map::OVER_LOAD;
    }
    Coordinate peakLeftUp(pos.x, pos.y);
    Coordinate peakRightUp(pos.x + len - wallThickness, pos.y);
    Coordinate peakLeftDown(pos.x, pos.y + high - wallThickness);
    Coordinates lineUpDown;
    Coordinates lineLeftRight;
    for (int loop = 0; loop < len; ++loop) {
        lineUpDown.coors.push_back(Coordinate{loop, 0});
    }
    for (int loop = wallThickness; loop < high - wallThickness; ++loop) {
        lineLeftRight.coors.push_back(Coordinate{0, loop});
    }
    uint32_t takeSta = Map::OK;
    takeSta |= this->TakePos(peakLeftUp, lineUpDown, color, padding);
    takeSta |= this->TakePos(peakLeftDown, lineUpDown, color, padding);
    takeSta |= this->TakePos(peakLeftUp, lineLeftRight, color, padding);
    takeSta |= this->TakePos(peakRightUp, lineLeftRight, color, padding);

    return takeSta;
}

MainMap::MainMap(int len, int high) {
    this->length = len;
    this->height = high;
    for (int y = 0; y < this->height; ++y) {
        Cell *line = new Cell[this->length];
        this->allCell.push_back(line);
    }
}

MainMap::~MainMap(void) {
    for (int y = this->height - 1; y >= 0; --y) {
        delete []this->allCell.at(y);
    }
}

void MainMap::Show(void) {
    std::string display;
    e_color lastColor = COLOR_NONE;
    for (auto line : this->allCell) {
        for (int x = 0; x < this->length; ++x) {
            Cell *cell = &line[x];
            if (!cell->takeFlag) {
                display.push_back(' ');
                continue;
            }
            if (cell->color != lastColor && cell->color < COLOR_NUM) {
                lastColor = (e_color)cell->color;
                display += this->colorStr[lastColor];
            }
            display.push_back(cell->padding);
        }
        display.push_back('\n');
    }
    display += this->colorStr[COLOR_NONE];
    std::cout << display << std::endl;
}

SubMap::SubMap(std::vector<Cell*> &parentCells, Coordinate &pos, int len, int high) {
    this->length = len;
    this->height = high;
    for (int y = 0; y < high; ++y) {
        this->allCell.push_back(&parentCells.at(pos.y + y)[pos.x]);
    }
}

