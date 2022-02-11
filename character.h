#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <string>

class Character : public QObject
{
    Q_OBJECT
private:
    int health;
    int intelligence;
    int mood;
    QString name;
    QString stage;
    int age;
    int wealth;
    QString gender;

public:
    explicit Character(QObject *parent = nullptr);
    int getHealth() const;
    void setHealth(int value);
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

signals:

};

#endif // CHARACTER_H
