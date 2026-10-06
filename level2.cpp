#include <iostream>
#include "level2.h"

using namespace std;

void level2Intro()
{
    cout << "\n====================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "              LEVEL 2\n";
    cout << "====================================\n";

    cout << "\nCharacters available:\n";
    cout << "1. Blaze  - Fire\n";
    cout << "2. Splash - Water\n";

    cout << "\nObjective:\n";
    cout << "Use fire and water abilities to overcome\n";
    cout << "the obstacles in Level 2.\n";
}

void level2Start()
{
    level2Intro();

    int choice;

    cout << "\nChoose your character: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nBlaze enters Level 2!\n";
        cout << "Ability: Fire\n";
        cout << "Blaze uses fire to destroy the obstacle.\n";
    }
    else if (choice == 2)
    {
        cout << "\nSplash enters Level 2!\n";
        cout << "Ability: Water\n";
        cout << "Splash uses water to overcome the obstacle.\n";
    }
    else
    {
        cout << "\nInvalid choice!\n";
        return;
    }

    cout << "\nLevel 2 completed successfully!\n";
}

