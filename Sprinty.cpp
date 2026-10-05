#include "Sprinty.h"
#include <iostream>

using namespace std;

Sprinty::Sprinty()
    : Character("Sprinty", "Agility", "Cross gaps", 1, 0)
{
}

void Sprinty::useAbility()
{
    cout << "Sprinty uses Agility! She can cross gaps." << endl;
}
