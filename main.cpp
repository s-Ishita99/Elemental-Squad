
#include <iostream>

#include "level1.h"
#include "level2.h"
#include "level3.h"

using namespace std;

int main()
{
    int choice;

    do
    {
        cout << "\n";
        cout << "=====================================\n";
        cout << "          ELEMENTAL SQUAD\n";
        cout << "=====================================\n";
        cout << "1. Level 1 - The Beginning\n";
        cout << "2. Level 2 - The Dark Cave\n";
        cout << "3. Level 3 - The Four Trials\n";
        cout << "0. Exit Game\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                level1Intro();
                level1Start();
                break;

            case 2:
                level2Start();
                break;

            case 3:
                level3Start();
                break;

            case 0:
                cout << "\nThank you for playing Elemental Squad!\n";
                cout << "See you again!\n";
                break;

            default:
                cout << "\nInvalid choice! Please select 0, 1, 2, or 3.\n";
        }

    } while (choice != 0);

    return 0;
}
