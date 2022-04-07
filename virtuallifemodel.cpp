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
}

void VirtualLifeModel::newGame()
{
    currentCharacter = new Character();
    characters.push_back(currentCharacter);
    setName(currentCharacter->getName());

}

Character* VirtualLifeModel::getCurrentCharacter()
{
    return currentCharacter;
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

QString VirtualLifeModel::getName()
{
    return name;
}

void VirtualLifeModel::setName(QString characterName)
{
    name = characterName;
}

void VirtualLifeModel::read(const QJsonObject &json)
{
    if (json.contains("currentName") && json["currentName"].isString())
        name = json["name"].toString();

    if (json.contains("characters") && json["characters"].isArray()) {
        QJsonArray charactersArray = json["characters"].toArray();
        characters.clear();
        characters.reserve(charactersArray.size());
        for (int i = 0; i < charactersArray.size(); ++i) {
            QJsonObject characterObject = charactersArray[i].toObject();
            Character* character = new Character();
            character->read(characterObject);
            characters.push_back(character);
        }
    }
    currentCharacter = characters.last();
}

void VirtualLifeModel::write(QJsonObject &json) const
{
    json["currentName"] = name;
    QJsonArray charactersArray;
    for (const Character* character : characters) {
        QJsonObject characterObject;
        character->write(characterObject);
        charactersArray.append(characterObject);
    }
    json["characters"] = charactersArray;

}

bool VirtualLifeModel::loadGame()
{
    QFile loadFile(QStringLiteral("save.json"));


    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    //Qmessagebox h betöltött
    return true;
}

bool VirtualLifeModel::saveGame() const
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    saveFile.write(QJsonDocument(gameObject).toJson());

    return true;
}
