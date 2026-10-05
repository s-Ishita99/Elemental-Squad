#include <iostream>

#include "Rocky.h"
#include "Sprinty.h"
#include "Blaze.h"
#include "Splash.h"
#include "Grid.h"

using namespace std;


// Character Menu
void showMenu()
{
    cout << "\n============================================\n";
    cout << "              ELEMENTAL SQUAD\n";
    cout << "============================================\n";

    cout << "1. Rocky   - Strength - Push boulders\n";
    cout << "2. Sprinty - Agility  - Cross gaps\n";
    cout << "3. Blaze   - Fire     - Melt ice / Light torches\n";
    cout << "4. Splash  - Water    - Extinguish fire\n";

    cout << "5. Exit\n";

    cout << "============================================\n";
}


int main()
{
    // Create character objects
    Rocky rocky;
    Sprinty sprinty;
    Blaze blaze;
    Splash splash;

    // Create Level 1 grid
    Grid level1;

    // Initially Rocky is active
    Character* currentCharacter = &rocky;

    int choice;

    cout << "Welcome to Elemental Squad!\n";

    do
    {
        showMenu();

        cout << "Enter character number: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                currentCharacter = &rocky;
                break;

            case 2:
                currentCharacter = &sprinty;
                break;

            case 3:
                currentCharacter = &blaze;
                break;

            case 4:
                currentCharacter = &splash;
                break;

            case 5:
                cout << "\nExiting Elemental Squad...\n";
                break;

            default:
                cout << "\nInvalid choice! Please select 1-5.\n";
                continue;
        }

        if(choice >= 1 && choice <= 4)
        {
            cout << "\n--------------------------------------------\n";

            cout << "Character switched to: "
                 << currentCharacter->getName() << endl;

            cout << "Position: ("
                 << currentCharacter->getX() << ", "
                 << currentCharacter->getY() << ")" << endl;

            currentCharacter->useAbility();

            cout << "--------------------------------------------\n";
        }

    } while(choice != 5);

    return 0;
}
