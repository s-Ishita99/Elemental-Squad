
#ifndef GRID3_H
#define GRID3_H

#include <string>
using namespace std;

class Grid3
{
public:
    static const int ROWS = 10;
    static const int COLS = 14;

    string tiles[ROWS][COLS];

    Grid3();
    void createMap();
};

#endif
