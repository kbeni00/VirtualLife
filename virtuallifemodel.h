#ifndef VIRTUALLIFEMODEL_H
#define VIRTUALLIFEMODEL_H

#include <QObject>
#include "character.h"

class VirtualLifeModel : public QObject
{
    Q_OBJECT
private:
    Character* currentCharacter;
    QString name;
    QVector<Character*> characters;
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
    bool loadGame();
    bool saveGame() const;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
signals:

};

#endif // VIRTUALLIFEMODEL_H
