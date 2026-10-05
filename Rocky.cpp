#include "Rocky.h"
#include <iostream>

using namespace std;

Rocky::Rocky()
    : Character("Rocky", "Strength", "Push boulders", 0, 0)
{
}

void Rocky::useAbility()
{
    cout << "Rocky uses Strength! He can push boulders." << endl;
}
