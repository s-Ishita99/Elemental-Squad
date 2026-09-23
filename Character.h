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

public:
    Character(string n, string a, string t);

    virtual void useAbility() = 0;

    string getName();

    virtual ~Character();
};

#endif
