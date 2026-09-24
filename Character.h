#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

class Character
{
protected:
    string name;
    string ability;
    string task;

    int x;
    int y;

public:
    Character(string n, string a, string t, int startX, int startY);

    virtual void useAbility() = 0;

    string getName();

    int getX();
    int getY();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    virtual ~Character();
};

#endif
