#include <iostream>
#include "level3.h"

using namespace std;

void level3Intro()
{
    cout << "\n====================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "              LEVEL 3\n";
    cout << "====================================\n";

    cout << "\nAll characters are available:\n";
    cout << "1. Rocky  - Strength\n";
    cout << "2. Sprinty - Agility\n";
    cout << "3. Blaze  - Fire\n";
    cout << "4. Splash - Water\n";

    cout << "\nObjective:\n";
    cout << "Use the abilities of the complete Elemental\n";
    cout << "Squad to complete the final level.\n";
}

void level3Start()
{
    level3Intro();

    int choice;

    cout << "\nChoose your character: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            cout << "\nRocky joins the final battle!\n";
            cout << "Ability: Strength\n";
            cout << "Rocky destroys heavy obstacles.\n";
            break;

        case 2:
            cout << "\nSprinty joins the final battle!\n";
            cout << "Ability: Agility\n";
            cout << "Sprinty quickly avoids obstacles.\n";
            break;

        case 3:
            cout << "\nBlaze joins the final battle!\n";
            cout << "Ability: Fire\n";
            cout << "Blaze burns dangerous obstacles.\n";
            break;

        case 4:
            cout << "\nSplash joins the final battle!\n";
            cout << "Ability: Water\n";
            cout << "Splash uses water to overcome obstacles.\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
            return;
    }

    cout << "\n====================================\n";
    cout << "       LEVEL 3 COMPLETED!\n";
    cout << "       ELEMENTAL SQUAD WINS!\n";
    cout << "====================================\n";
}

