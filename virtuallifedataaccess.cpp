#include "virtuallifedataaccess.h"
#include <QDir>
#include <QMessageBox>

VirtualLifeDataAccess::VirtualLifeDataAccess()
{
}

void VirtualLifeDataAccess::read(const QJsonObject &json, QString selectedCharacterName,QVector<Character*> &characters, Character* &currentCharacter)
{
    bool found = false;
    readError = false;
    if (json.contains("characters") && json["characters"].isArray()) {
        QJsonArray charactersArray = json["characters"].toArray();
        characters.clear();
        characters.reserve(charactersArray.size());
        for (int i = 0; i < charactersArray.size(); ++i) {
            QJsonObject characterObject = charactersArray[i].toObject();
            Character* character = new Character();
            character->read(characterObject);
            characters.push_back(character);
            if(character->getName() == selectedCharacterName){
                currentCharacter = character;
                found = true;
            }
        }
    }
    if(found == false && !selectedCharacterName.isEmpty()){
        characters.clear();
        readError = true;
    }
}

QVector<QString> VirtualLifeDataAccess::getNamesInDatabase(){
    QVector<QString> names;
    QFile loadFile(QStringLiteral("save.json"));
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return names;
    }
    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    if (loadDoc.object().contains("characters") && loadDoc.object()["characters"].isArray()) {
        QJsonArray charactersArray = loadDoc.object()["characters"].toArray();
        for (int i = 0; i < charactersArray.size(); ++i) {
            QJsonObject characterObject = charactersArray[i].toObject();
            Character* character = new Character();
            character->read(characterObject);
            names.push_back(character->getName());
        }
    } else{
        return names;
    }
    return names;
}


void VirtualLifeDataAccess::write(QJsonObject &json, QVector<Character*> &characters)
{
    QVector<QString> names = getNamesInDatabase();
    QJsonArray charactersArray;
    for (const Character* character : characters) {
        QJsonObject characterObject;
        character->write(characterObject);
        charactersArray.append(characterObject);
    }
    for (const QString &name : names){
        charactersArray.append(name);
    }
    json["characters"] = charactersArray;

}

bool VirtualLifeDataAccess::loadGame(QString name, QVector<Character*> &characters, Character* &currentCharacter)
{
    QDir dir;
    QString path = dir.absolutePath(); //location of the file, assuming in application dir
    path.append("/save.json");
    QFile loadFile(path);


    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object(), name, characters,currentCharacter);

    if(readError){
        qWarning("No such character in the database.");
    }
    return true;
}

bool VirtualLifeDataAccess::saveGame(QVector<Character*> &characters)
{
    QDir dir;
    QString path = dir.absolutePath(); //location of the file, assuming in application dir
    path.append("/save.json");
    QFile saveFile(path);


    if (!saveFile.open(QIODevice::ReadWrite)) {
        return false;
    }
    QJsonObject gameObject;
    write(gameObject,characters);
    saveFile.write(QJsonDocument(gameObject).toJson());

    saveFile.close();

    return true;
}
