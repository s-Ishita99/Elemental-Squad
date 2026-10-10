#include <iostream>
#include "grid2.h"

using namespace std;

int playerRow, playerCol;
int lives;
char currentCharacter;

bool hasPotion;
bool torchLit;
bool gameOver;
bool levelWon;

// Check whether a position is inside the cave
bool isCaveTile(int row, int col)
{
    // Rows 8-10, columns 11-14 (1-based)
    return row >= 7 && row <= 9 &&
           col >= 10 && col <= 13;
}

void displayGrid()
{
    cout << "\nLives: " << lives;
    cout << "\nCharacter: "
         << (currentCharacter == 'C' ? "Blaze" : "Splash");
    cout << "\nPotion: "
         << (hasPotion ? "Collected" : "Not collected");
    cout << "\nTorch: "
         << (torchLit ? "Lit" : "Unlit");

    cout << "\n\n";

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == playerRow && j == playerCol)
                cout << currentCharacter << ' ';
            else if (grid2[i][j] == 'P' && hasPotion)
                cout << ". ";
            else if (grid2[i][j] == 'T' && torchLit)
                cout << "T ";
            else
                cout << grid2[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << "\nControls: W/A/S/D = Move, 1 = Blaze, 2 = Splash";
    cout << "\nE = Interact, Q = Quit\n";
}

void interact()
{
    if (grid2[playerRow][playerCol] == 'P')
    {
        if (currentCharacter == 'C')
        {
            hasPotion = true;
            grid2[playerRow][playerCol] = '.';
            cout << "\nBlaze collected the potion!\n";
        }
        else
        {
            cout << "\nSwitch to Blaze to collect the potion!\n";
        }
    }
    else if (grid2[playerRow][playerCol] == 'T')
    {
        if (currentCharacter != 'C')
        {
            cout << "\nOnly Blaze can light the torch!\n";
        }
        else if (!hasPotion)
        {
            cout << "\nCollect the potion before lighting the torch!\n";
        }
        else if (!torchLit)
        {
            torchLit = true;
            cout << "\nBlaze lit the torch! The cave is now accessible.\n";
        }
        else
        {
            cout << "\nThe torch is already lit!\n";
        }
    }
    else
    {
        cout << "\nNothing to interact with here.\n";
    }
}

void movePlayer(int dr, int dc)
{
    int nr = playerRow + dr;
    int nc = playerCol + dc;

    if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS)
        return;

    if (grid2[nr][nc] == '#')
    {
        cout << "\nA wall blocks the way!\n";
        return;
    }

    // Do not allow entering the cave before lighting the torch
    if (!torchLit && isCaveTile(nr, nc))
    {
        cout << "\nThe cave is too dark! Collect the potion and light the torch first.\n";
        return;
    }

    if (grid2[nr][nc] == 'W' && currentCharacter == 'C')
    {
        lives--;
        cout << "\nBlaze cannot cross water! One life lost.\n";

        if (lives <= 0)
        {
            gameOver = true;
            cout << "\nGAME OVER!\n";
        }
        return;
    }

    if (grid2[nr][nc] == 'I')
    {
        if (currentCharacter == 'C')
        {
            grid2[nr][nc] = '.';
            cout << "\nBlaze melted the ice!\n";
        }
        else
        {
            lives--;
            cout << "\nSplash cannot cross the ice! One life lost.\n";

            if (lives <= 0)
            {
                gameOver = true;
                cout << "\nGAME OVER!\n";
            }
            return;
        }
    }

    if (grid2[nr][nc] == 'E')
    {
        if (torchLit)
        {
            playerRow = nr;
            playerCol = nc;
            levelWon = true;
            cout << "\nCongratulations! You completed Level 2!\n";
        }
        else
        {
            cout << "\nThe exit is locked! Light the torch first.\n";
        }
        return;
    }

    // Move onto the next tile
    playerRow = nr;
    playerCol = nc;

    // Collect the potion automatically when Blaze steps on it
    if (grid2[playerRow][playerCol] == 'P')
    {
        if (currentCharacter == 'C')
        {
            hasPotion = true;
            grid2[playerRow][playerCol] = '.';
            cout << "\nBlaze collected the potion!\n";
        }
        else
        {
            cout << "\nSwitch to Blaze to collect the potion!\n";
        }
    }
}

bool level2Start()
{
    playerRow = 0;
    playerCol = 0;

    lives = 3;
    currentCharacter = 'C';

    hasPotion = false;
    torchLit = false;
    gameOver = false;
    levelWon = false;

    char choice;

    while (!gameOver && !levelWon)
    {
        displayGrid();

        cout << "\nEnter move or action: ";
        cin >> choice;

        if (choice == 'q' || choice == 'Q')
            break;

        if (choice == '1')
        {
            currentCharacter = 'C';
            cout << "\nSwitched to Blaze.\n";
        }
        else if (choice == '2')
        {
            currentCharacter = 'S';
            cout << "\nSwitched to Splash.\n";
        }
        else if (choice == 'e' || choice == 'E')
        {
            interact();
        }
        else if (choice == 'w' || choice == 'W')
        {
            movePlayer(-1, 0);
        }
        else if (choice == 's' || choice == 'S')
        {
            movePlayer(1, 0);
        }
        else if (choice == 'a' || choice == 'A')
        {
            movePlayer(0, -1);
        }
        else if (choice == 'd' || choice == 'D')
        {
            movePlayer(0, 1);
        }
    }

    return levelWon;
}
