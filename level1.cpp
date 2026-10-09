#include <iostream>
#include "level1.h"
#include "Grid.h"
#include "Rocky.h"
#include "Sprinty.h"

using namespace std;

void level1Intro()
{
    cout << "\n====================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "              LEVEL 1\n";
    cout << "====================================\n";

    cout << "\nCharacters available:\n";
    cout << "1. Rocky   - Push boulders\n";
    cout << "2. Sprinty - Cross gaps\n";

    cout << "\nObjective:\n";
    cout << "Collect the key and reach the exit.\n";

    cout << "\nControls:\n";
    cout << "W/A/S/D - Move\n";
    cout << "1/2     - Switch character\n";
    cout << "E       - Use ability\n";
    cout << "R       - Restart level\n";
    cout << "Q       - Quit\n";
}

void level1Start()
{
    Rocky rocky;
    Sprinty sprinty;
    Grid grid;

    Character* current = nullptr;
    bool hasKey = false;
    int moves = 0;
    char choice;

    level1Intro();

    int characterChoice;

    do
    {
        cout << "\nChoose your starting character (1 or 2): ";
        cin >> characterChoice;
    }
    while(characterChoice != 1 && characterChoice != 2);

    if(characterChoice == 1)
        current = &rocky;
    else
        current = &sprinty;

    while(true)
    {
        cout << "\nCurrent character: "
             << current->getName() << '\n';

        cout << "Moves: " << moves << '\n';
        cout << "Key: " << (hasKey ? "Collected" : "Not collected")
             << '\n';

        grid.display(current);

        cout << "Enter command: ";
        cin >> choice;

        if(choice == 'q' || choice == 'Q')
        {
            cout << "Leaving Level 1.\n";
            return;
        }

        if(choice == '1')
        {
            current = &rocky;
            continue;
        }

        if(choice == '2')
        {
            current = &sprinty;
            continue;
        }

        if(choice == 'e' || choice == 'E')
        {
            grid.useAbility(*current);
            continue;
        }

        if(choice == 'r' || choice == 'R')
        {
            rocky = Rocky();
            sprinty = Sprinty();
            grid = Grid();

            current = &rocky;
            hasKey = false;
            moves = 0;

            cout << "Level 1 restarted.\n";
            continue;
        }

        bool moved = grid.moveCharacter(*current, choice);

        if(moved)
        {
            moves++;

            if(grid.collectKey(*current))
                hasKey = true;

            if(grid.reachedExit(*current))
            {
                if(hasKey)
                {
                    cout << "\n====================================\n";
                    cout << "       LEVEL 1 COMPLETED!\n";
                    cout << "====================================\n";
                    cout << "Total moves: " << moves << '\n';
                    return;
                }
                else
                {
                    cout << "The exit is locked! Find the key first.\n";
                }
            }
        }
    }
}
