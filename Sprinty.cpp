#include "Sprinty.h"
#include <iostream>

using namespace std;

Sprinty::Sprinty()
    : Character("Sprinty", "Agility",
                "Cross gaps and handle agility-based obstacles")
{
}

void Sprinty::useAbility()
{
    cout << "Sprinty uses Agility!" << endl;
    cout << "Sprinty can cross gaps and handle agility-based obstacles."
         << endl;
}
