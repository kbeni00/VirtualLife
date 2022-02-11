#ifndef VIRTUALLIFEMODEL_H
#define VIRTUALLIFEMODEL_H

#include <QObject>
#include "character.h"

class VirtualLifeModel : public QObject
{
    Q_OBJECT
private:
    Character* character;
public:
    explicit VirtualLifeModel(QObject *parent = nullptr);
    void newGame();
    bool isGameOver();
    void performAction();
    Character* getCharacter();
signals:

};

#endif // VIRTUALLIFEMODEL_H
