#include "Character.h"

Character::Character(string n, string a, string t)
{
    name = n;
    ability = a;
    task = t;
}

string Character::getName()
{
    return name;
}

Character::~Character()
{
}
