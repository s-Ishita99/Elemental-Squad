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

int Character::getX()
{
    return x;
}

int Character::getY()
{
    return y;
}

void Character::moveUp()
{
    y--;
}

void Character::moveDown()
{
    y++;
}

void Character::moveLeft()
{
    x--;
}

void Character::moveRight()
{
    x++;
}

Character::~Character()
{
}
