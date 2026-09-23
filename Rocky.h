#ifndef ROCKY_H
#define ROCKY_H

#include "Character.h"

class Rocky : public Character
{
public:
    Rocky();

    void useAbility() override;
};

#endif
