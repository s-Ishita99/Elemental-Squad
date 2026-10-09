
#include <iostream>

#include "Rocky.h"
#include "Sprinty.h"
#include "blaze.h"
#include "splash.h"
#include "Grid.h"

using namespace std;

int main()
{
    Rocky rocky;
    Sprinty sprinty;
    Blaze blaze;
    Splash splash;

    Grid level1;

    Character* currentCharacter = &rocky;

    bool hasKey = false;
    int moves = 0;
    char choice;

    cout << "\n============================================\n";
    cout << "          ELEMENTAL SQUAD\n";
    cout << "               LEVEL 1\n";
    cout << "============================================\n";

    cout << "\nCharacters:\n";
    cout << "1 - Rocky   : Push boulders\n";
    cout << "2 - Sprinty : Cross gaps\n";

    cout << "\nControls:\n";
    cout << "W - Up       | S - Down\n";
    cout << "A - Left     | D - Right\n";
    cout << "1 - Rocky    | 2 - Sprinty\n";
    cout << "E - Ability  | Q - Quit\n";

    while(true)
    {
        cout << "\n--------------------------------------------\n";
        cout << "Current Character: "
             << currentCharacter->getName() << '\n';

        cout << "Position: ("
             << currentCharacter->getX() << ", "
             << currentCharacter->getY() << ")\n";

        cout << "Moves: " << moves << '\n';

        cout << "Key: "
             << (hasKey ? "COLLECTED" : "NOT COLLECTED")
             << '\n';

        cout << "Controls: WASD | 1/2 Switch | E Ability | Q Quit\n";

        level1.display(currentCharacter);

        cout << "Enter command: ";
        cin >> choice;

        if(choice == 'q' || choice == 'Q')
        {
            cout << "\nExiting game...\n";
            break;
        }

        // Switch to Rocky while preserving the current position
        if(choice == '1')
        {
            if(currentCharacter != &rocky)
            {
                rocky.setPosition(
                    currentCharacter->getX(),
                    currentCharacter->getY()
                );

                currentCharacter = &rocky;
            }

            cout << "\nSwitched to Rocky.\n";
            continue;
        }

        // Switch to Sprinty while preserving the current position
        if(choice == '2')
        {
            if(currentCharacter != &sprinty)
            {
                sprinty.setPosition(
                    currentCharacter->getX(),
                    currentCharacter->getY()
                );

                currentCharacter = &sprinty;
            }

            cout << "\nSwitched to Sprinty.\n";
            continue;
        }

        if(choice == 'e' || choice == 'E')
        {
            level1.useAbility(*currentCharacter);
            continue;
        }

        if(choice == 'w' || choice == 'W' ||
           choice == 'a' || choice == 'A' ||
           choice == 's' || choice == 'S' ||
           choice == 'd' || choice == 'D')
        {
            bool moved =
                level1.moveCharacter(*currentCharacter, choice);

            if(moved)
            {
                moves++;

                if(level1.collectKey(*currentCharacter))
                    hasKey = true;

                if(level1.reachedExit(*currentCharacter))
                {
                    if(hasKey)
                    {
                        cout << "\n============================================\n";
                        cout << "           LEVEL 1 COMPLETED!\n";
                        cout << "============================================\n";
                        cout << "Total moves: " << moves << '\n';
                        break;
                    }
                    else
                    {
                        cout << "\nThe exit is locked!\n";
                        cout << "Collect the key first.\n";
                    }
                }
            }

            continue;
        }

        cout << "\nInvalid command! Use WASD, 1, 2, E or Q.\n";
    }

    return 0;
}
