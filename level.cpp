#include "Level.h"


Level::Level(int level)
{
    levelNumber = level;
    characterCount = 0;

    // Initially no characters
    for (int i = 0; i < 4; i++)
    {
        characters[i] = NULL;
    }

    setupLevel();
}


void Level::setupLevel()
{
    // LEVEL 1
    // Rocky + Sprinty

    if (levelNumber == 1)
    {
        characters[0] = new Rocky();
        characters[1] = new Sprinty();

        characterCount = 2;
    }

    // LEVEL 2
    // Blaze + Splash

    else if (levelNumber == 2)
    {
        characters[0] = new Blaze();
        characters[1] = new Splash();

        characterCount = 2;
    }

    // LEVEL 3
    // All four characters

    else if (levelNumber == 3)
    {
        characters[0] = new Rocky();
        characters[1] = new Sprinty();
        characters[2] = new Blaze();
        characters[3] = new Splash();

        characterCount = 4;
    }
}


bool Level::isAllowedCharacter(int choice)
{
    if (choice >= 1 && choice <= characterCount)
    {
        return true;
    }

    return false;
}


Character* Level::getCharacter(int choice)
{
    if (isAllowedCharacter(choice))
    {
        return characters[choice - 1];
    }

    return NULL;
}


int Level::getCharacterCount()
{
    return characterCount;
}


int Level::getLevelNumber()
{
    return levelNumber;
}


Level::~Level()
{
    for (int i = 0; i < characterCount; i++)
    {
        delete characters[i];
    }
}