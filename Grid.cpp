#include "Grid.h"
#include <iostream>

using namespace std;


Grid::Grid()
{
    int temp[10][14] =
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

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            level[i][j] = temp[i][j];
        }
    }
}


// ============================================
// GET TILE
// ============================================

int Grid::getTile(int row, int col)
{
    if(row < 0 || row >= ROWS ||
       col < 0 || col >= COLS)
    {
        return -1;
    }

    return level[row][col];
}


// ============================================
// DISPLAY GRID
// ============================================

void Grid::display(Character* character)
{
    cout << "\n";

    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            // Character position
            if(character != nullptr &&
               character->getX() == col &&
               character->getY() == row)
            {
                cout << " C ";
            }
            else
            {
                switch(level[row][col])
                {
                    case 0:
                        cout << " . ";
                        break;

                    case 1:
                        cout << " # ";
                        break;

                    case 2:
                        cout << " B ";
                        break;

                    case 3:
                        cout << " G ";
                        break;

                    case 4:
                        cout << " K ";
                        break;

                    case 5:
                        cout << " E ";
                        break;

                    default:
                        cout << " ? ";
                }
            }
        }

        cout << endl;
    }

    cout << "\n";
}


// ============================================
// MOVE CHARACTER
// ============================================

bool Grid::moveCharacter(Character& character, char direction)
{
    int oldX = character.getX();
    int oldY = character.getY();

    int newX = oldX;
    int newY = oldY;


    // Determine new position

    if(direction == 'w' || direction == 'W')
    {
        newY--;
    }
    else if(direction == 's' || direction == 'S')
    {
        newY++;
    }
    else if(direction == 'a' || direction == 'A')
    {
        newX--;
    }
    else if(direction == 'd' || direction == 'D')
    {
        newX++;
    }
    else
    {
        return false;
    }


    int tile = getTile(newY, newX);


    // Outside grid

    if(tile == -1)
    {
        cout << "You cannot move outside the grid.\n";
        return false;
    }


    // Wall

    if(tile == 1)
    {
        cout << "There is a wall there!\n";
        return false;
    }


    // ============================================
    // BOULDER
    // ============================================

    if(tile == 2)
    {
        // Only Rocky can push

        if(character.getName() != "Rocky")
        {
            cout << "Only Rocky can push the boulder!\n";
            return false;
        }


        int boulderNewX = newX;
        int boulderNewY = newY;


        if(direction == 'w' || direction == 'W')
        {
            boulderNewY--;
        }
        else if(direction == 's' || direction == 'S')
        {
            boulderNewY++;
        }
        else if(direction == 'a' || direction == 'A')
        {
            boulderNewX--;
        }
        else if(direction == 'd' || direction == 'D')
        {
            boulderNewX++;
        }


        int boulderDestination =
            getTile(boulderNewY, boulderNewX);


        // Boulder cannot leave map

        if(boulderDestination == -1)
        {
            cout << "The boulder cannot be pushed outside the grid!\n";
            return false;
        }


        // Boulder cannot be pushed into wall

        if(boulderDestination == 1)
        {
            cout << "The boulder cannot be pushed there!\n";
            return false;
        }


        // Boulder cannot be pushed into another boulder

        if(boulderDestination == 2)
        {
            cout << "Another boulder is blocking the way!\n";
            return false;
        }


        // Push boulder

        level[newY][newX] = 0;

        level[boulderNewY][boulderNewX] = 2;

        character.setPosition(newX, newY);

        cout << "Rocky pushed the boulder!\n";

        return true;
    }


    // ============================================
    // GAP
    // ============================================

    if(tile == 3)
    {
        if(character.getName() != "Sprinty")
        {
            cout << "Only Sprinty can cross the gap!\n";
            return false;
        }

        character.setPosition(newX, newY);

        cout << "Sprinty crossed the gap!\n";

        return true;
    }


    // ============================================
    // NORMAL FLOOR / KEY / EXIT
    // ============================================

    character.setPosition(newX, newY);

    return true;
}


// ============================================
// COLLECT KEY
// ============================================

bool Grid::collectKey(Character& character)
{
    int x = character.getX();
    int y = character.getY();


    if(level[y][x] == 4)
    {
        level[y][x] = 0;

        cout << "\n*** KEY COLLECTED! ***\n";

        return true;
    }

    return false;
}


// ============================================
// EXIT
// ============================================

bool Grid::reachedExit(Character& character)
{
    int x = character.getX();
    int y = character.getY();

    if(level[y][x] == 5)
    {
        return true;
    }

    return false;
}


// ============================================
// CHARACTER ABILITY
// ============================================

void Grid::useAbility(Character& character)
{
    character.useAbility();
}
