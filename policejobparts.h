#ifndef POLICEJOBPARTS_H
#define POLICEJOBPARTS_H


#include "policejobsettings.h"

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class PoliceCarPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PoliceCarPart(QGraphicsItem *parent = nullptr);
signals:
    void sigIncreaseScore();
    void sigDecreaseScore();
//public slots:
//    void onMove();

};

////////////////////////////////////////////////////

class RobberCarPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    RobberCarPart(QGraphicsItem *parent = nullptr);
signals:
    void sigGameOver(bool);
    void sigDecreaseHealth();
    void sigIncreaseScore();
public slots:
    void onMove();

};

////////////////////////////////////////////////////


class TextPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    TextPart(QGraphicsItem *parent = nullptr);
    void increaseScore();
    void decreaseScore();
    void decreaseHealth();

    int getHealth() const;
    int getScore() const;

    void reset();
    void updateMetrics(int, int);

private:
    int _nHealth = gCarHealth;
    int _nScore = 0;
};

#endif // POLICEJOBPARTS_H
