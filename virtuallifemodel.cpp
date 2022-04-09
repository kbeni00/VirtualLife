#include "virtuallifemodel.h"
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include <QCborMap>

VirtualLifeModel::VirtualLifeModel(QObject *parent)
    : QObject{parent}
{
    newGame();
    if(!dataAccess.loadGame(name,savedCharacters,currentCharacter)) emit sigReadError();

}

void VirtualLifeModel::newGame()
{
    qDebug() << "pushembby";
    currentCharacter = new Character();
    characters.push_back(currentCharacter);
}

Character* VirtualLifeModel::getCurrentCharacter()
{
    return currentCharacter;
}

void VirtualLifeModel::setCurrentCharacter(Character* character){
    currentCharacter = character;
}


void  VirtualLifeModel::initializeData()
{
    currentCharacter->setHealth(QRandomGenerator::global()->generate()%100+1);
    currentCharacter->setIntelligence(QRandomGenerator::global()->generate()%100+1);
    currentCharacter->setMood(QRandomGenerator::global()->generate()%100+1);
    QString stage = "Baby";
    currentCharacter->setStage(stage);
}

QVector<Character*> VirtualLifeModel::getCharacters()
{
    return characters;
}

void VirtualLifeModel::setCharacters(QVector<Character *> &characters)
{
    this->characters = characters;
}

QVector<Character*> VirtualLifeModel::getSavedCharacters()
{
    return savedCharacters;
}

void VirtualLifeModel::setSavedCharacters(QVector<Character*> &characters)
{
    savedCharacters = characters;
}

QString VirtualLifeModel::getName()
{
    return name;
}

void VirtualLifeModel::setName(QString characterName)
{
    name = characterName;
}

bool VirtualLifeModel::loadGame(QString name)
{
    if(!dataAccess.loadGame(name,savedCharacters,currentCharacter)) emit sigReadError();

    return true;
}

bool VirtualLifeModel::saveGame()
{
    for(Character* character : characters){
        savedCharacters.push_back(character);
    }
    characters.clear();
    return dataAccess.saveGame(savedCharacters);
}

QVector<QString> VirtualLifeModel::getNamesInDatabase(){

    return dataAccess.getNamesInDatabase();
}
