#include "character.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

Character::Character(QObject *parent)
    : QObject{parent}
{
    health = 50;
    needs = 50;
    intelligence = 0;
    mood = 0;
    name = "-";
    stage = "-";
    gender = "-";
    age = 0;
    wealth = 10000000;


}

int Character::getHealth() const
{
    return health;
}

void Character::setHealth(int value)
{
    health = value;
}

int Character::getNeeds()
{
    return needs;
}

void Character::setNeeds(int value)
{
    needs = value;
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

QVector<QString> Character::getAssets()
{
    return assets;
}

void Character::addAsset(QString name)
{
    assets.push_back(name);
}

bool Character::getHasHouse(){
    return hasHouse;
}

void Character::setHasHouse(bool boughtAHouse){
    hasHouse = boughtAHouse;
}

bool Character::getHasCar(){
    return hasCar;
}

void Character::setHasCar(bool boughtACar){
    hasCar = boughtACar;
}

int Character::getFoodsTried()
{
    return foodsTried;
}

void Character::increaseFoodsTried(int x)
{
    foodsTried += x;
}

QVector<bool> Character::getEasyGamesPlayed()
{
    return easyGamesPlayed;
}

QVector<bool> Character::getMediumGamesPlayed()
{
    return mediumGamesPlayed;
}

QVector<bool> Character::getHardGamesPlayed()
{
    return hardGamesPlayed;
}

void Character::increaseEasyGamesPlayed(int x)
{
    qDebug() << "character debug: " << x;
    easyGamesPlayed[x] = true;
}

void Character::increaseMediumGamesPlayed(int x)
{
    mediumGamesPlayed[x] = true;
}

void Character::increaseHardGamesPlayed(int x)
{
    hardGamesPlayed[x] = true;
}

void Character::read(const QJsonObject &json)
{
    name = json["name"].toString();
    health = json["health"].toInt();
    needs = json["needs"].toInt();
    intelligence = json["intelligence"].toInt();
    mood = json["mood"].toInt();
    name = json["name"].toString();
    stage = json["stage"].toString();
    age = json["age"].toInt();
    wealth = json["wealth"].toInt();
    gender = json["gender"].toString();
    hasHouse = json["hasHouse"].toBool();
    hasCar = json["hasCar"].toBool();
    foodsTried = json["foodsTried"].toInt();
    QJsonArray easyGames = json["easyGames"].toArray();
    easyGamesPlayed.clear();
    mediumGamesPlayed.clear();
    hardGamesPlayed.clear();
    for(int i = 0; i < easyGames.size(); i++){
        easyGamesPlayed.push_back(easyGames.at(i).toBool());
    }

    QJsonArray mediumGames = json["mediumGames"].toArray();
    for(int i = 0; i < mediumGames.size(); i++){
        mediumGamesPlayed.push_back(mediumGames.at(i).toBool());
    }

    QJsonArray hardGames = json["hardGames"].toArray();
    for(int i = 0; i < hardGames.size(); i++){
        hardGamesPlayed.push_back(hardGames.at(i).toBool());
    }
    QJsonArray assetsArray = json["assets"].toArray();
    for(int i = 0; i < assetsArray.size(); i++){
        assets.push_back(assetsArray.at(i).toString());
    }

}

void Character::write(QJsonObject &json) const
{
    json["health"] = health;
    json["needs"] = needs;
    json["intelligence"] = intelligence;
    json["mood"] = mood;
    json["name"] = name;
    json["stage"] = stage;
    json["age"] = age;
    json["wealth"] = wealth;
    json["gender"] = gender;
    json["hasHouse"] = hasHouse;
    json["hasCar"] = hasCar;
    json["foodsTried"] = foodsTried;
    QJsonArray easyGames;
    for(int i = 0; i < easyGamesPlayed.size(); i++){
        QJsonValue val(easyGamesPlayed.at(i));
        easyGames.append(val);
    }
    json["easyGames"] = easyGames;

    QJsonArray mediumGames;
    for(int i = 0; i < mediumGamesPlayed.size(); i++){
        QJsonValue val(mediumGamesPlayed.at(i));
        mediumGames.append(val);
    }

    json["mediumGames"] = mediumGames;


    QJsonArray hardGames;
    for(int i = 0; i < hardGamesPlayed.size(); i++){
        QJsonValue val(hardGamesPlayed.at(i));
        hardGames.append(val);
    }

    json["hardGames"] = hardGames;


    QJsonArray assetsArray;
    for(int i = 0; i < assets.size(); i++){
        QJsonValue val(assets.at(i));
        assetsArray.append(val);
    }
    json["assets"] = assetsArray;


}
