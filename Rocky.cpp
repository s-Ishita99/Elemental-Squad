#include "Rocky.h"
#include <iostream>

using namespace std;

Rocky::Rocky()
    : Character("Rocky", "Strength",
                "Push boulders and clear heavy obstacles")
{
}

void Rocky::useAbility()
{
    cout << "Rocky uses Strength!" << endl;
    cout << "Rocky can push boulders and clear heavy obstacles."
         << endl;
}
