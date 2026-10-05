#include "splash.h"
#include <iostream>

using namespace std;

Splash::Splash()
    : Character("Splash", "Water", "Extinguish fire", 1, 0)
{
}

void Splash::useAbility()
{
    cout << "Splash uses Water!" << endl;
}
