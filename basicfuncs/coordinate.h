#ifndef __COORDINATE_H
#define __COORDINATE_H

#include <vector>

struct Coordinate {
    Coordinate(int a, int b) : x(a), y(b) {}
    int x;
    int y;
};

struct Coordinates {
    std::vector<Coordinate> coors;
};




#endif
