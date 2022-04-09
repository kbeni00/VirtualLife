#ifndef VIRTUALLIFEMODEL_H
#define VIRTUALLIFEMODEL_H

#include <QObject>
#include "character.h"
#include "virtuallifedataaccess.h"
#include <QString>

class VirtualLifeModel : public QObject
{
    Q_OBJECT
private:
    Character* currentCharacter;
    QString name;
    QVector<Character*> characters;
    QVector<Character*> savedCharacters;
    VirtualLifeDataAccess dataAccess;
public:
    explicit VirtualLifeModel(QObject *parent = nullptr);
    void newGame();
    bool isGameOver();
    void performAction();
    void initializeData();
    Character* getCurrentCharacter();
    QVector<Character*> getCharacters();
    void setCharacters(QVector<Character*> &characters);
    QString getName();
    void setName(QString);
    bool loadGame(QString);
    bool saveGame();
    void read(const QJsonObject &json,QString);
    void write(QJsonObject &json);
    QVector<QString> getNamesInDatabase();
    void setCurrentCharacter(Character*);
    QVector<Character*> getSavedCharacters();
    void setSavedCharacters(QVector<Character*> &characters);
signals:
    void sigReadError();
};

#endif // VIRTUALLIFEMODEL_H
