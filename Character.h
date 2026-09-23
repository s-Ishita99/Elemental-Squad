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
