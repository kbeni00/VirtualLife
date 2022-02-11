#include "virtuallifemodel.h"

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
