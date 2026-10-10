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

void displayGrid()
{
    cout << "\nLives: " << lives;
    cout << "\nCharacter: "
         << (currentCharacter == 'C' ? "Blaze" : "Splash");
    cout << "\nPotion: " << (hasPotion ? "Collected" : "Not collected");
    cout << "\nTorch: " << (torchLit ? "Lit" : "Unlit");
    cout << "\n\n";

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == playerRow && j == playerCol)
                cout << currentCharacter << ' ';
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
            cout << "\nBlaze must collect the potion!\n";
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
            cout << "\nCollect the potion first!\n";
        }
        else if (!torchLit)
        {
            torchLit = true;
            cout << "\nTorch lit! The cave is now accessible.\n";
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

    // Cave markers block entry only while the torch is unlit.
    if (!torchLit && grid2[nr][nc] == 'V')
    {
        cout << "\nThe cave is too dark! Light the torch first.\n";
        return;
    }

    // Splash can pass through fire. Blaze cannot.
    if (grid2[nr][nc] == 'F' && currentCharacter == 'C')
    {
        cout << "\nBlaze cannot pass through fire!\n";
        return;
    }

    // Splash can pass through water. Blaze cannot.
    if (grid2[nr][nc] == 'W' && currentCharacter == 'C')
    {
        cout << "\nBlaze cannot pass through water!\n";
        return;
    }

    // Blaze handles ice; Splash loses a life on ice.
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
            cout << "\nSplash slipped on the ice! Lives left: "
                 << lives << '\n';

            if (lives <= 0)
                gameOver = true;

            return;
        }
    }

    // Exit is usable only after lighting the torch.
    if (grid2[nr][nc] == 'E')
    {
        if (torchLit)
        {
            playerRow = nr;
            playerCol = nc;
            levelWon = true;
            cout << "\nLevel 2 completed!\n";
        }
        else
        {
            cout << "\nThe exit is locked! Light the torch first.\n";
        }

        return;
    }

    playerRow = nr;
    playerCol = nc;

    // Blaze automatically collects the potion.
    if (grid2[playerRow][playerCol] == 'P' &&
        currentCharacter == 'C')
    {
        hasPotion = true;
        grid2[playerRow][playerCol] = '.';
        cout << "\nBlaze collected the potion!\n";
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

        if (choice == 'w' || choice == 'W')
            movePlayer(-1, 0);
        else if (choice == 's' || choice == 'S')
            movePlayer(1, 0);
        else if (choice == 'a' || choice == 'A')
            movePlayer(0, -1);
        else if (choice == 'd' || choice == 'D')
            movePlayer(0, 1);
        else if (choice == '1')
            currentCharacter = 'C';
        else if (choice == '2')
            currentCharacter = 'S';
        else if (choice == 'e' || choice == 'E')
            interact();
        else if (choice == 'q' || choice == 'Q')
        {
            gameOver = true;
            cout << "\nLeaving Level 2.\n";
        }
        else
        {
            cout << "\nInvalid input!\n";
        }
    }

    return levelWon;
}
