#ifndef GRID_H
#define GRID_H

#include "Character.h"

class Grid
{
private:
    static const int ROWS = 10;
    static const int COLS = 14;

    int level[ROWS][COLS];

public:
    Grid();

    void display(Character* character);

    bool moveCharacter(Character& character, char direction);

    bool collectKey(Character& character);

    bool reachedExit(Character& character);

    int getTile(int row, int col);

    void useAbility(Character& character);
};

#endif
