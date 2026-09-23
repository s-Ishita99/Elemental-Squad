#include <iostream>
#include <string>
using namespace std;

// Base Character Class
class Character
{
protected:
    string name;
    string ability;
    string task;

public:
    Character(string n, string a, string t)
    {
        name = n;
        ability = a;
        task = t;
    }

    virtual void useAbility() = 0;

    void display()
    {
        cout << name << " - "
             << ability << " - "
             << task << endl;
    }

    string getName()
    {
        return name;
    }

    virtual ~Character() {}
};


// Rocky
class Rocky : public Character
{
public:
    Rocky() : Character(
        "Rocky",
        "Strength",
        "Push boulders and clear heavy obstacles")
    {
    }

    void useAbility() override
    {
        cout << "Rocky uses Strength!" << endl;
        cout << "He can push boulders and clear heavy obstacles."
             << endl;
    }
};


// Sprinty
class Sprinty : public Character
{
public:
    Sprinty() : Character(
        "Sprinty",
        "Agility",
        "Cross gaps and handle agility-based obstacles")
    {
    }

    void useAbility() override
    {
        cout << "Sprinty uses Agility!" << endl;
        cout << "Sprinty can cross gaps and handle agility-based obstacles."
             << endl;
    }
};


// Blaze
class Blaze : public Character
{
public:
    Blaze() : Character(
        "Blaze",
        "Fire",
        "Melt ice and light torches")
    {
    }

    void useAbility() override
    {
        cout << "Blaze uses Fire!" << endl;
        cout << "Blaze can melt ice and light torches."
             << endl;
    }
};


// Splash
class Splash : public Character
{
public:
    Splash() : Character(
        "Splash",
        "Water",
        "Extinguish fire and handle water-based obstacles")
    {
    }

    void useAbility() override
    {
        cout << "Splash uses Water!" << endl;
        cout << "Splash can extinguish fire and handle water-based obstacles."
             << endl;
    }
};


// Character Menu
void showMenu()
{
    cout << "\n============================================\n";
    cout << "              ELEMENTAL SQUAD\n";
    cout << "============================================\n";

    cout << "1. Rocky   - Strength - Push boulders\n";
    cout << "2. Sprinty - Agility  - Cross gaps\n";
    cout << "3. Blaze   - Fire     - Melt ice / Light torches\n";
    cout << "4. Splash  - Water    - Extinguish fire\n";

    cout << "5. Exit\n";

    cout << "============================================\n";
}


int main()
{
    // Create character objects
    Rocky rocky;
    Sprinty sprinty;
    Blaze blaze;
    Splash splash;

    // Initially Rocky is active
    Character* currentCharacter = &rocky;

    int choice;

    cout << "Welcome to Elemental Squad!\n";

    do
    {
        showMenu();

        cout << "Enter character number: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                currentCharacter = &rocky;
                break;

            case 2:
                currentCharacter = &sprinty;
                break;

            case 3:
                currentCharacter = &blaze;
                break;

            case 4:
                currentCharacter = &splash;
                break;

            case 5:
                cout << "\nExiting Elemental Squad...\n";
                break;

            default:
                cout << "\nInvalid choice! Please select 1-5.\n";
                continue;
        }

        if(choice >= 1 && choice <= 4)
        {
            cout << "\n--------------------------------------------\n";
            cout << "Character switched to: "
                 << currentCharacter->getName() << endl;

            currentCharacter->useAbility();

            cout << "--------------------------------------------\n";
        }

    } while(choice != 5);

    return 0;
}
