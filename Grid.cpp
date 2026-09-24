#include <iostream>
#include "Grid.h"

using namespace std;

Grid::Grid()
{
    initialize();
}

void Grid::initialize()
{
    int level[10][14] =
    {
        {0,0,1,0,0,0,0,1,0,0,0,0,0,0},
        {0,1,0,1,1,0,0,3,1,0,1,1,1,1},
        {0,0,0,1,1,0,0,3,1,0,0,0,0,0},
        {0,0,0,2,0,0,0,3,1,0,0,0,0,0},
        {0,0,0,1,1,1,0,3,0,0,0,1,1,1},
        {0,0,0,1,0,0,0,1,0,0,4,0,0,1},
        {0,0,0,1,0,1,0,1,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,1,1,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,1,0,1,1},
        {0,0,0,0,0,0,0,1,0,0,0,0,0,5}
    };

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            grid[row][col] = level[row][col];
        }
    }
}

int Grid::getTile(int row, int col) const
{
    if (row >= 0 && row < ROWS &&
        col >= 0 && col < COLS)
    {
        return grid[row][col];
    }

    return -1;
}

void Grid::display() const
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            cout << grid[row][col] << " ";
        }

        cout << endl;
    }
}
