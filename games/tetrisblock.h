#ifndef __MINE_TETRISBLOCK_H
#define __MINE_TETRISBLOCK_H

#include <vector>
#include "coordinate.h"
#include "map.h"


class TetrisBlock {
protected:
    std::vector<Coordinates> allShape;
    int shapeNum;
    int shapeIdx;
public:
    TetrisBlock() : shapeNum(0), shapeIdx(0), color(Map::COLOR_NONE), pedding('O') {}
    void Change(void);
    void ChangeBak(void);
    static TetrisBlock* GetRandomBlock(void);
    Coordinates& GetCurrentShape();
    int color;
    int pedding;
};

#define SHAPE_ADD_ONE() do { \
        this->shapeNum += 1; \
        this->allShape.push_back(Coordinates()); \
    } while (0)

#define CURRENT_SHAPE_ADD_POS(_x, _y) do { \
        this->allShape.at(this->shapeNum - 1).coors.push_back(Coordinate((_x), (_y))); \
    } while (0)

class Square : public TetrisBlock {
public:
    Square() : TetrisBlock() {
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* OO */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* XO */
        CURRENT_SHAPE_ADD_POS(1, -1);
        CURRENT_SHAPE_ADD_POS(1,  0);
    }
};

class Line : public TetrisBlock {
public:
    Line() : TetrisBlock() {
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* O */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* O */
        CURRENT_SHAPE_ADD_POS(0, -2);                       /* O */
        CURRENT_SHAPE_ADD_POS(0, -3);                       /* X */

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* XOOO */
        CURRENT_SHAPE_ADD_POS(1,  0);
        CURRENT_SHAPE_ADD_POS(2,  0);
        CURRENT_SHAPE_ADD_POS(3,  0);
    }
};

class Block_Z : public TetrisBlock {
public:
    Block_Z() : TetrisBlock() {
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* OO  */
        CURRENT_SHAPE_ADD_POS(-1,-1);                       /*  XO */
        CURRENT_SHAPE_ADD_POS(0, -1);
        CURRENT_SHAPE_ADD_POS(1,  0);

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(1, -1);                       /* XO */
        CURRENT_SHAPE_ADD_POS(1,  0);                       /* O  */
        CURRENT_SHAPE_ADD_POS(0,  1);
    }
};

class Block_N : public TetrisBlock {
public:
    Block_N() : TetrisBlock() {
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /*  OO */
        CURRENT_SHAPE_ADD_POS(1, -1);                       /* OX  */
        CURRENT_SHAPE_ADD_POS(0, -1);
        CURRENT_SHAPE_ADD_POS(-1, 0);

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* O  */
        CURRENT_SHAPE_ADD_POS(-1,-1);                       /* OX */
        CURRENT_SHAPE_ADD_POS(-1, 0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(0,  1);
    }
};

class Block_T : public TetrisBlock {
public:
    Block_T() : TetrisBlock() {
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /*  O  */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* OXO */
        CURRENT_SHAPE_ADD_POS(-1, 0);
        CURRENT_SHAPE_ADD_POS(1,  0);

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* OX */
        CURRENT_SHAPE_ADD_POS(-1, 0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(0,  1);

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* OXO */
        CURRENT_SHAPE_ADD_POS(-1, 0);                       /*  O  */
        CURRENT_SHAPE_ADD_POS(1,  0);
        CURRENT_SHAPE_ADD_POS(0,  1);
        
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* O  */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* XO */
        CURRENT_SHAPE_ADD_POS(1,  0);                       /* O  */
        CURRENT_SHAPE_ADD_POS(0,  1);
    }
};

class Block_J : public TetrisBlock {
public:
    Block_J() : TetrisBlock() {        
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(-1, 0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* OX */
        CURRENT_SHAPE_ADD_POS(0, -2);
        
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* OOX */
        CURRENT_SHAPE_ADD_POS(-2, 0);                       /*   O */
        CURRENT_SHAPE_ADD_POS(-1, 0);
        CURRENT_SHAPE_ADD_POS(0,  1);

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* XO */
        CURRENT_SHAPE_ADD_POS(1,  0);                       /* O  */
        CURRENT_SHAPE_ADD_POS(0,  1);                       /* O  */
        CURRENT_SHAPE_ADD_POS(0,  2);
        
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* O   */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /* XOO */
        CURRENT_SHAPE_ADD_POS(1,  0);
        CURRENT_SHAPE_ADD_POS(2,  0);
    }
};


class Block_L : public TetrisBlock {
public:
    Block_L() : TetrisBlock() {
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /*  O  */
        CURRENT_SHAPE_ADD_POS(0, -1);                       /*  O  */
        CURRENT_SHAPE_ADD_POS(0, -2);                       /*  XO */
        CURRENT_SHAPE_ADD_POS(1,  0);
        
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                        /*   O */
        CURRENT_SHAPE_ADD_POS(0, -1);                        /* OOX */
        CURRENT_SHAPE_ADD_POS(-1, 0);
        CURRENT_SHAPE_ADD_POS(-2, 0);

        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* OX */
        CURRENT_SHAPE_ADD_POS(-1, 0);                       /*  O */
        CURRENT_SHAPE_ADD_POS(0,  1);                       /*  O */
        CURRENT_SHAPE_ADD_POS(0,  2);
        
        SHAPE_ADD_ONE();
        CURRENT_SHAPE_ADD_POS(0,  0);                       /* XOO */
        CURRENT_SHAPE_ADD_POS(1,  0);                       /* O   */
        CURRENT_SHAPE_ADD_POS(2,  0);
        CURRENT_SHAPE_ADD_POS(0,  1);
    }
};


#endif

