#include <iostream>
#include <limits>
#include "level1.h"
#include "Grid.h"
#include "Rocky.h"
#include "Sprinty.h"

using namespace std;

char readCommand()
{
    char choice;
    cin >> choice;

    // Handle arrow-key escape sequences on a terminal
    if(choice == 27)
    {
        char bracket, arrow;

        cin.get(bracket);
        cin.get(arrow);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(bracket == '[')
        {
            if(arrow == 'A') return 'w';  // Up
            if(arrow == 'B') return 's';  // Down
            if(arrow == 'D') return 'a';  // Left
            if(arrow == 'C') return 'd';  // Right
        }

        return '?';
    }

    return choice;
}

void level1Intro()
{
    cout << "\n====================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "              LEVEL 1\n";
    cout << "====================================\n";

    cout << "\nCharacters available:\n";
    cout << "1. Rocky   - Push boulders\n";
    cout << "2. Sprinty - Cross gaps\n";

    cout << "\nObjective: Collect the key and reach the exit.\n";

    cout << "\nCONTROLS:\n";
    cout << "W / Up Arrow    - Move up\n";
    cout << "S / Down Arrow  - Move down\n";
    cout << "A / Left Arrow  - Move left\n";
    cout << "D / Right Arrow - Move right\n";
    cout << "1               - Switch to Rocky\n";
    cout << "2               - Switch to Sprinty\n";
    cout << "E               - Use ability\n";
    cout << "R               - Restart level\n";
    cout << "Q               - Quit level\n";
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
    int characterChoice;

    level1Intro();

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
        cout << "\n------------------------------------\n";
        cout << "Character: " << current->getName() << '\n';
        cout << "Moves: " << moves << '\n';
        cout << "Key: " << (hasKey ? "Collected" : "Not collected") << '\n';

        // Keep controls visible during gameplay
        cout << "Controls: WASD/Arrows | 1 Rocky | 2 Sprinty"
             << " | E Ability | R Restart | Q Quit\n";

        grid.display(current);

        cout << "Enter command: ";
        choice = readCommand();

        if(choice == 'q' || choice == 'Q')
        {
            cout << "Leaving Level 1.\n";
            return;
        }

        if(choice == '1')
        {
            if(current != &rocky)
            {
                rocky.setPosition(current->getX(), current->getY());
                current = &rocky;
            }

            continue;
        }

        if(choice == '2')
        {
            if(current != &sprinty)
            {
                sprinty.setPosition(current->getX(), current->getY());
                current = &sprinty;
            }

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

            current = (characterChoice == 1) ? &rocky : &sprinty;
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

                cout << "The exit is locked! Find the key first.\n";
            }
        }
    }
}
