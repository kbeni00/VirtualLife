#include "character.h"

Character::Character(QObject *parent)
    : QObject{parent}
{
    health = 0;
    intelligence = 0;
    mood = 0;
    name = "-";
    stage = "-";
    gender = "-";
    age = 0;
    wealth = 0;

}

int Character::getHealth() const
{
    return health;
}

void Character::setHealth(int value)
{
    health = value;
}

int Character::getIntelligence() const
{
    return intelligence;
}

void Character::setIntelligence(int value)
{
    intelligence = value;
}
int Character::getMood() const
{
    return mood;
}

void Character::setMood(int value)
{
    mood = value;
}
QString Character::getName() const
{
    return name;
}

void Character::setName(QString &value)
{
    name = value;
}

QString Character::getStage() const
{
    return stage;
}

void Character::setStage(QString &value)
{
    stage = value;
}

int Character::getAge() const
{
    return age;
}

void Character::setAge(int value)
{
    age = value;
}

int Character::getWealth() const
{
    return wealth;
}

void Character::setWealth(int value)
{
    wealth = value;
}

QString Character::getGender()
{
    return gender;
}

void Character::setGender(QString &value)
{
    gender = value;
}
bool Character::hasEnoughMoney(int value)
{
 return value<=wealth;
}
