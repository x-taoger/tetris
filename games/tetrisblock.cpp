#include "tetrisblock.h"
#include "common.h"


void TetrisBlock::Change(void) {
    this->shapeIdx += 1;
    if (this->shapeIdx >= this->shapeNum) this->shapeIdx = 0;
}

void TetrisBlock::ChangeBak(void) {
    this->shapeIdx -= 1;
    if (this->shapeIdx < 0) this->shapeIdx = this->shapeNum - 1;
}

Coordinates& TetrisBlock::GetCurrentShape() {
    return this->allShape.at(this->shapeIdx);
}

TetrisBlock* TetrisBlock::GetRandomBlock(void) {
    const int typeNum = 7;
    unsigned int random = Common::CommonGetRandomData(); /* todo : use C++ random */
    random %= typeNum;
    TetrisBlock *block = nullptr;
    switch (random) {
        case 0 : block = new Square(); break;
        case 1 : block = new Line(); break;
        case 2 : block = new Block_Z(); break;
        case 3 : block = new Block_N(); break;
        case 4 : block = new Block_T(); break;
        case 5 : block = new Block_J(); break;
        case 6 : 
        default : block = new Block_L(); break;
    }
    return block;
}