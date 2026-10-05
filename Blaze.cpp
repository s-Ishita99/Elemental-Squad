#include "blaze.h"
#include <iostream>

using namespace std;

Blaze::Blaze()
    : Character("Blaze", "Fire", "Melt ice and light torches", 0, 0)
{
}

void Blaze::useAbility()
{
    cout << "Blaze uses Fire!" << endl;
}
