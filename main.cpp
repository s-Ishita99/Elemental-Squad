#include <iostream>

#include "Rocky.h"
#include "Sprinty.h"
#include "Blaze.h"
#include "Splash.h"
#include "Grid.h"

using namespace std;


int main()
{
    // ============================================
    // CREATE CHARACTERS
    // ============================================

    Rocky rocky;
    Sprinty sprinty;
    Blaze blaze;
    Splash splash;


    // ============================================
    // CREATE LEVEL 1 GRID
    // ============================================

    Grid level1;


    // Rocky is the starting character

    Character* currentCharacter = &rocky;


    // Key status

    bool hasKey = false;


    // User input

    char choice;


    cout << "\n";
    cout << "============================================\n";
    cout << "          ELEMENTAL SQUAD - LEVEL 1\n";
    cout << "============================================\n";

    cout << "\nCharacters:\n";
    cout << "1 - Rocky   : Push Boulders\n";
    cout << "2 - Sprinty : Cross Gaps\n";

    cout << "\nControls:\n";
    cout << "W - Up\n";
    cout << "S - Down\n";
    cout << "A - Left\n";
    cout << "D - Right\n";
    cout << "1 - Switch to Rocky\n";
    cout << "2 - Switch to Sprinty\n";
    cout << "E - Use Ability\n";
    cout << "Q - Quit\n";


    // ============================================
    // GAME LOOP
    // ============================================

    while(true)
    {
        cout << "\n--------------------------------------------\n";

        cout << "Current Character: "
             << currentCharacter->getName() << endl;

        cout << "Position: ("
             << currentCharacter->getX()
             << ", "
             << currentCharacter->getY()
             << ")" << endl;

        cout << "Key: ";

        if(hasKey)
        {
            cout << "COLLECTED";
        }
        else
        {
            cout << "NOT COLLECTED";
        }

        cout << "\n--------------------------------------------\n";


        // Display grid

        level1.display(currentCharacter);


        cout << "Enter command: ";
        cin >> choice;


        // ========================================
        // QUIT
        // ========================================

        if(choice == 'q' || choice == 'Q')
        {
            cout << "\nExiting game...\n";
            break;
        }


        // ========================================
        // CHARACTER SWITCH
        // ========================================

        if(choice == '1')
        {
            currentCharacter = &rocky;

            cout << "\nSwitched to Rocky.\n";

            continue;
        }


        if(choice == '2')
        {
            currentCharacter = &sprinty;

            cout << "\nSwitched to Sprinty.\n";

            continue;
        }


        // ========================================
        // ABILITY
        // ========================================

        if(choice == 'e' || choice == 'E')
        {
            level1.useAbility(*currentCharacter);

            continue;
        }


        // ========================================
        // MOVEMENT
        // ========================================

        if(choice == 'w' || choice == 'W' ||
           choice == 'a' || choice == 'A' ||
           choice == 's' || choice == 'S' ||
           choice == 'd' || choice == 'D')
        {
            bool moved =
                level1.moveCharacter(*currentCharacter, choice);


            if(moved)
            {
                // Check for key

                if(level1.collectKey(*currentCharacter))
                {
                    hasKey = true;
                }


                // Check exit

                if(level1.reachedExit(*currentCharacter))
                {
                    if(hasKey)
                    {
                        cout << "\n";
                        cout << "============================================\n";
                        cout << "          LEVEL 1 COMPLETED!\n";
                        cout << "============================================\n";

                        cout << "\nCongratulations!\n";
                        cout << "You collected the key and reached the exit.\n";

                        break;
                    }
                    else
                    {
                        cout << "\nThe exit is locked!\n";
                        cout << "You need the key first.\n";
                    }
                }
            }

            continue;
        }


        cout << "\nInvalid command!\n";
    }


    return 0;
}
