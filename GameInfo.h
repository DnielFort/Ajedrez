#ifndef GameInfo_h
#define GameInfo_h
#include <vector>
#include "ChessPosition.hpp"

struct Direction {
    int dirX;
    int dirY;
};

const int NUM_COLS = 8;
const int NUM_ROWS = 8;


typedef vector<ChessPosition> VecOfPositions;

#endif /* GameInfo_h */
