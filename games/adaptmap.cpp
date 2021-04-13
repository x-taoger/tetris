#include "adaptmap.h"

/* class static value */


/* static value */


/* private function */

/* public function */

int TetrisGameMap::ClearLine(void) {
    std::vector<int> clearLineIdxs;

    for (int y = this->height - 1; y >= 0; --y) {
        int x;
        Cell *cell = this->allCell.at(y);
        for (x = 0; x < this->length; ++x) {
            if (!cell[x].takeFlag) break;
        }
        if (x == this->length) {
            clearLineIdxs.push_back(y);
        }
    }

    if (clearLineIdxs.size() == 0) return 0;
    
    std::vector<int> keepLine;
    int clearIdx = 0;
    for (int y = this->height - 1; y >= 0; --y) {
        if (y == clearLineIdxs.at(clearIdx)) {
            if (clearIdx < clearLineIdxs.size() - 1) clearIdx += 1;
            continue;
        }
        keepLine.push_back(y);
    }
    Cell *cell = new Cell();
    for (int y = this->height - 1, keepIdx = 0; y >= 0; --y) {
        if (keepIdx >= keepLine.size()) {
            for (int x = 0; x < this->length; ++x) {
                this->allCell.at(y)[x].takeFlag = cell->takeFlag;
                this->allCell.at(y)[x].color = cell->color;
                this->allCell.at(y)[x].padding = cell->padding;
            }
        } else {
            for (int x = 0; x < this->length; ++x) {
                this->allCell.at(y)[x].takeFlag = this->allCell.at(keepLine.at(keepIdx))[x].takeFlag;
                this->allCell.at(y)[x].color = this->allCell.at(keepLine.at(keepIdx))[x].color;
                this->allCell.at(y)[x].padding = this->allCell.at(keepLine.at(keepIdx))[x].padding;
            }
            keepIdx += 1;
        }
    }
    delete cell;
    return clearLineIdxs.size();
}

TetrisGameMap* TetrisMainMap::SpiltTetrisGameMapWithWall(Coordinate &pos, int len, int high, int wallColor, int padding) {
    const int wallThickness = 1;
    const int wallNum = 2;
    const int posWallAdd = wallThickness * wallNum;
    if (pos.x < 0 || pos.y < 0 || len < 0 || high < 0) {
        return nullptr;
    }
    if ((pos.x + len + posWallAdd > this->length) || (pos.y + high + posWallAdd > this->height)) {
        return nullptr;
    }
    this->PaintTheCloseWall(pos, len + posWallAdd, high + posWallAdd, wallColor, padding);
    Coordinate subValidPos(pos.x + wallThickness, pos.y + wallThickness);
    TetrisGameMap *subMap = new TetrisGameMap(this->allCell, subValidPos, len, high);
    return subMap;
}
