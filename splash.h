#ifndef SPLASH_H
#define SPLASH_H

#include "Character.h"

class Splash : public Character
{
public:
    Splash();

    void useAbility() override;
};

#endif
