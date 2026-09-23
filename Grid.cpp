#include "Grid.h"

Grid::Grid()
{
    initialize();
}

void Grid::initialize()
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            grid[row][col] = 0;
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
