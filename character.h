#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <string>

class Character : public QObject
{
    Q_OBJECT
private:
    int health;
    int needs;
    int intelligence;
    int mood;
    QString name;
    QString stage;
    int age;
    int wealth;
    QString gender;
    QVector<QString> assets;
    bool hasHouse = false;
    bool hasCar = false;
    int foodsTried;
    QVector<bool> easyGamesPlayed = {false,false,false,false,false};
    QVector<bool> mediumGamesPlayed = {false,false,false,false,false};
    QVector<bool> hardGamesPlayed = {false,false,false,false,false};

public:
    explicit Character(QObject *parent = nullptr);
    int getHealth() const;
    void setHealth(int value);
    int getNeeds();
    void setNeeds(int value);
    int getIntelligence() const;
    void setIntelligence(int value);
    int getMood() const;
    void setMood(int value);
    QString getName() const;
    void setName(QString &value);
    QString getStage() const;
    void setStage(QString &value);
    int getAge() const;
    void setAge(int value);
    int getWealth() const;
    void setWealth(int value);
    QString getGender();
    void setGender(QString &value);
    bool hasEnoughMoney(int value);
    QVector<QString> getAssets();
    void addAsset(QString);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool getHasHouse();
    void setHasHouse(bool);
    bool getHasCar();
    void setHasCar(bool);
    int getFoodsTried();
    void increaseFoodsTried(int);
    QVector<bool> getEasyGamesPlayed();
    void increaseEasyGamesPlayed(int);
    QVector<bool> getMediumGamesPlayed();
    void increaseMediumGamesPlayed(int);
    QVector<bool> getHardGamesPlayed();
    void increaseHardGamesPlayed(int);

signals:

};

#endif // CHARACTER_H
