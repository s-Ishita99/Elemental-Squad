#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"
#include "Rocky.h"
#include "Sprinty.h"
#include "blaze.h"
#include "splash.h"
#include "Grid.h"

class Level
{
private:
    int levelNumber;

    Character* characters[4];
    int characterCount;

    Grid grid;

public:
    // Constructor
    Level(int level);

    // Destructor
    ~Level();

    // Sets characters according to level
    void setupLevel();

    // Checks whether a character is available
    bool isAllowedCharacter(int choice);

    // Returns selected character
    Character* getCharacter(int choice);

    // Returns number of characters in level
    int getCharacterCount();

    // Returns current level number
    int getLevelNumber();
};

#endif