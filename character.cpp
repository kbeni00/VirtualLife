#include "character.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

Character::Character(QObject *parent)
    : QObject{parent}
{
    health = 0;
    needs = 0;
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

QVector<QString> Character::getRelationships()
{
    return relationships;
}

QVector<QString> Character::getAssets()
{
    return assets;
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
    QJsonArray relationshipsArray = json["relationships"].toArray();
    for(int i = 0; i < relationshipsArray.size(); i++){
        relationships.push_back(relationshipsArray.at(i).toString());
    }
    QJsonArray assetsArray = json["assets"].toArray();
    for(int i = 0; i < assetsArray.size(); i++){
        relationships.push_back(assetsArray.at(i).toString());
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
    QJsonArray relationshipsArray;
    for(int i = 0; i < relationships.size(); i++){
        QJsonValue val(relationships.at(i));
        relationshipsArray.append(val);
    }
    json["relationships"] = relationshipsArray;
    QJsonArray assetsArray;
    for(int i = 0; i < assets.size(); i++){
        QJsonValue val(assets.at(i));
        assetsArray.append(val);
    }
    json["assets"] = assetsArray;


}
