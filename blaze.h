#ifndef BLAZE_H
#define BLAZE_H

#include "Character.h"

class Blaze : public Character
{
public:
    Blaze();

    void useAbility() override;
};

#endif
