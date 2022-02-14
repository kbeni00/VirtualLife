#include "virtuallifemodel.h"
#include <QRandomGenerator>

VirtualLifeModel::VirtualLifeModel(QObject *parent)
    : QObject{parent}
{
    newGame();
}

void VirtualLifeModel::newGame()
{
    character = new Character();
}

Character* VirtualLifeModel::getCharacter()
{
    return character;
}


void  VirtualLifeModel::initializeData()
{
    character->setHealth(QRandomGenerator::global()->generate()%100+1);
    character->setIntelligence(QRandomGenerator::global()->generate()%100+1);
    character->setMood(QRandomGenerator::global()->generate()%100+1);
    QString stage = "Baby";
    character->setStage(stage);

}
