#include "Blaze.h"
#include <iostream>

using namespace std;

Blaze::Blaze()
    : Character("Blaze", "Fire",
                "Melt ice and light torches")
{
}

void Blaze::useAbility()
{
    cout << "Blaze uses Fire!" << endl;
    cout << "Blaze can melt ice and light torches."
         << endl;
}
