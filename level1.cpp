
#include <iostream>
#include "level1.h"

using namespace std;

void level1Intro()
{
    cout << "\n====================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "              LEVEL 1\n";
    cout << "====================================\n";

    cout << "\nCharacters available:\n";
    cout << "1. Rocky  - Strength\n";
    cout << "2. Sprinty - Agility\n";

    cout << "\nObjective:\n";
    cout << "Complete the first stage by using the\n";
    cout << "strength and agility abilities.\n";
}

void level1Start()
{
    level1Intro();

    int choice;

    cout << "\nChoose your character: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nRocky enters Level 1!\n";
        cout << "Ability: Strength\n";
        cout << "Rocky breaks the obstacle using strength.\n";
    }
    else if (choice == 2)
    {
        cout << "\nSprinty enters Level 1!\n";
        cout << "Ability: Agility\n";
        cout << "Sprinty quickly crosses the obstacle.\n";
    }
    else
    {
        cout << "\nInvalid choice!\n";
        return;
    }

    cout << "\nLevel 1 completed successfully!\n";
}

