#include "Splash.h"
#include <iostream>

using namespace std;

Splash::Splash()
    : Character("Splash", "Water",
                "Extinguish fire and handle water-based obstacles")
{
}

void Splash::useAbility()
{
    cout << "Splash uses Water!" << endl;
    cout << "Splash can extinguish fire and handle water-based obstacles."
         << endl;
}
