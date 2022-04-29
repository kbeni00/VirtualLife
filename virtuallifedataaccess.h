#ifndef VIRTUALLIFEDATAACCESS_H
#define VIRTUALLIFEDATAACCESS_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "character.h"
#include <QFileDialog>

class VirtualLifeDataAccess
{
public:
    explicit VirtualLifeDataAccess();

    bool loadGame(QString name, QVector<Character*> &characters, Character* &currentCharacter);
    bool saveGame(QVector<Character*> &characters);
    void read(const QJsonObject &json, QString selectedCharacter,QVector<Character*> &characters, Character* &currentCharacter);
    void writeNamesInDB(QJsonObject &json, QVector<QString>);
    void write(QJsonObject &json, QVector<Character*> &characters);
    bool readError;
    QVector<QString> getNamesInDatabase();

};

#endif // VIRTUALLIFEDATAACCESS_H
