#include <cstdint>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "tetris.h"
#include "coordinate.h"
#include "tetrisblock.h"
#include "keyboard.h"
#include "map.h"
#include "common.h"
#include "adaptmap.h"


#define GAME_MAP_START_X    ((uint32_t)0)
#define GAME_MAP_START_Y    ((uint32_t)0)
#define GAME_MAP_LENGTH     ((uint32_t)16)
#define GAME_MAP_HEIGHT     ((uint32_t)30)

/* 2: wall */
#define MAIN_MAP_LENGTH     ((uint32_t)(GAME_MAP_LENGTH + 2 + 16 ))
#define MAIN_MAP_HEIGHT     ((uint32_t)(GAME_MAP_HEIGHT + 2 ))

#define INFO_MAP_START_X    ((uint32_t)(GAME_MAP_LENGTH + 2))
#define INFO_MAP_START_Y    ((uint32_t)(MAIN_MAP_HEIGHT / 2))
#define INFO_MAP_LENGTH     ((uint32_t)(MAIN_MAP_LENGTH - INFO_MAP_START_X ))
#define INFO_MAP_HEIGHT     ((uint32_t)(MAIN_MAP_HEIGHT - INFO_MAP_START_Y ))

#define BLOCK_MOVE_FUNC(def_scope, def_funcName, def_moveDo, def_moveFailedDo) \
    uint32_t def_scope::def_funcName(void) { \
        this->FreeMap(); \
        (def_moveDo); \
        uint32_t takeFlag = this->TakeMap(); \
        if (takeFlag != Map::OK) { \
            if (takeFlag == Map::OVER_LOAD) this->FreeMap(); \
            (def_moveFailedDo); \
            this->TakeMap(); \
        } \
        return takeFlag; \
    }

BlockInMap::BlockInMap(Map *map, int x, int y) : pos(x, y) {
    this->inThisMap = map;
    this->block = TetrisBlock::GetRandomBlock();
    this->TakeMap();
}

BlockInMap::~BlockInMap() {
    delete this->block;
}

uint32_t BlockInMap::TakeMap(void) {
    uint32_t takeSta = this->inThisMap->TakePos(this->pos, this->block->GetCurrentShape(), this->block->color, this->block->pedding);
    uint32_t temp = takeSta;
    if (takeSta == Map::OVER_LOAD) { /* deal with block on top lines */
        for (auto cell : this->block->GetCurrentShape().coors) {
            int curX = cell.x + this->pos.x;
            int curY = cell.y + this->pos.y;
            if (curX < 0 || curX >= GAME_MAP_LENGTH) return takeSta;
            else if (curY < 0) temp = Map::OK;
        }
        return temp;
    }
    return takeSta;
}

uint32_t BlockInMap::FreeMap(void) {
    return this->inThisMap->FreePos(this->pos, this->block->GetCurrentShape());
}

BLOCK_MOVE_FUNC(BlockInMap, GoUp, this->block->Change(), this->block->ChangeBak())

BLOCK_MOVE_FUNC(BlockInMap, GoDown, this->pos.y += 1, this->pos.y -= 1)

BLOCK_MOVE_FUNC(BlockInMap, GoLeft, this->pos.x -= 1, this->pos.x += 1)

BLOCK_MOVE_FUNC(BlockInMap, GoRight, this->pos.x += 1, this->pos.x -= 1)

bool BlockInMap::IsPosVaild(void) {
    for (auto cell : this->block->GetCurrentShape().coors) {
        if ((this->pos.x + cell.x < 0) || (this->pos.y + cell.y < 0)) return false;
    }
    return true;
}


void TetrisGame::StartGame(void) {
    /* create main window */
    TetrisMainMap *mainMap = new TetrisMainMap(MAIN_MAP_LENGTH, MAIN_MAP_HEIGHT);
    if (mainMap == nullptr) {
        std::cout << "create main window failed!" << std::endl;
        return ;
    }
    
    /* create game window */
    Coordinate gameMapStart(GAME_MAP_START_X, GAME_MAP_START_Y);
    TetrisGameMap *gameMap = mainMap->SpiltTetrisGameMapWithWall(gameMapStart, GAME_MAP_LENGTH, GAME_MAP_HEIGHT);
    if (gameMap == nullptr) {
        std::cout << "create game window failed!" << std::endl;
        delete mainMap;
        return ;
    }

    /* create score infomation window */
    std::string scoreStr("Score: ");
    Coordinate infoMapStart(INFO_MAP_START_X, INFO_MAP_START_Y);
    Coordinate scoreStrStart(0, INFO_MAP_START_Y);
    Coordinate scoreMapStart(scoreStr.size(), INFO_MAP_START_Y);
    Map *infoMap = mainMap->SpiltSubMap(infoMapStart, INFO_MAP_LENGTH, INFO_MAP_HEIGHT);
    if (infoMap == nullptr) {
        std::cout << "create info window failed!" << std::endl;
        delete gameMap;
        delete mainMap;
        return ;
    }
    infoMap->PrintString(scoreStrStart, scoreStr);
    infoMap->PrintString(scoreMapStart, std::to_string(0));

    /* get keyboard */
    Keyboard *keyboard = Keyboard::GetInstance();

    /* update time and speed */
    const int refreshTime = 100 * 1000; /* refresh time 100ms */
    int autoDownMaxTime = 10; /* 10 * refreshTime = 1s */
    int speed = 0; /* block auto down time, bigger -> faster */
    int autoDownTime = autoDownMaxTime - speed;
    int score = 0;
    int count = 0;

    BlockInMap *block = new BlockInMap(gameMap, GAME_MAP_LENGTH / 2, 0);
    
    /* game start */
    while (1) {
        if (count++ % autoDownTime == 0) { /* auto down */
            if (block->GoDown() != Map::OK) {
                int onceScore = gameMap->ClearLine();
                score += onceScore * onceScore;
                speed = score / 10;
                speed = (speed >= autoDownMaxTime) ? (autoDownMaxTime - 1) : speed;
                autoDownTime = autoDownMaxTime - speed;
                infoMap->PrintString(scoreMapStart, std::to_string(score));
                if (block->IsPosVaild() != true) {
                    delete block;
                    break;
                }
                delete block;
                block = new BlockInMap(gameMap, GAME_MAP_LENGTH / 2, 0);
            }
        }
        int data = keyboard->GetInput();
        switch (data) {
            case UP : block->GoUp(); break;
            case DOWN : autoDownTime = 1; break;
            case LEFT : block->GoLeft(); break;
            case RIGHT : block->GoRight(); break;
            case KEEP: break;
        }
        system("clear");
        mainMap->Show();
        usleep(refreshTime);
    }

    /* game over */
    Coordinate gameOver(0, GAME_MAP_HEIGHT / 2);
    gameMap->PrintString(gameOver, "game over!", Map::COLOR_RED);
    system("clear");
    mainMap->Show();

    delete gameMap;
    delete mainMap;
    delete keyboard;
    return ;
}

