#include "Character.h"

Character::Character(string n, string a, string t, int startX, int startY)
{
    name = n;
    ability = a;
    task = t;

    x = startX;
    y = startY;
}

string Character::getName()
{
    return name;
}

string Character::getAbility()
{
    return ability;
}

string Character::getTask()
{
    return task;
}

int Character::getX()
{
    return x;
}

int Character::getY()
{
    return y;
}

void Character::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

Character::~Character()
{
}
