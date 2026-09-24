#pragma once

class Grid
{
private:
    static const int ROWS = 10;
    static const int COLS = 14;

    int grid[ROWS][COLS];

public:
    Grid();

    void initialize();
    int getTile(int row, int col) const;
void display() const;
};
