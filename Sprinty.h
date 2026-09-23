#ifndef SPRINTY_H
#define SPRINTY_H

#include "Character.h"

class Sprinty : public Character
{
public:
    Sprinty();

    void useAbility() override;
};

#endif
