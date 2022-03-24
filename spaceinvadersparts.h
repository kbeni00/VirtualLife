#ifndef SPACEINVADERSPARTS_H
#define SPACEINVADERSPARTS_H

#include "spaceinvaderssettings.h"

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class CannonPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit CannonPart(QGraphicsItem *parent = nullptr);
    void shoot();

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

};

////////////////////////////////////////////////////

class AlienPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AlienPart(QGraphicsItem *parent = nullptr);
signals:
    void sigGameOver();
    void sigDecreaseHealth();
public slots:
    void onMove();

};

////////////////////////////////////////////////////

class BulletPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BulletPart(QGraphicsItem *parent = nullptr);
signals:
    void sigIncreaseScore();
    void sigDecreaseScore();
public slots:
    void onMove();

};

////////////////////////////////////////////////////

class PointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    PointsPart(QGraphicsItem *parent = nullptr);
    void increaseScore();
    void decreaseScore();
    void decreaseHealth();

    int getHealth() const;
    int getScore() const;

    void reset();
    void updateMetrics(int, int);

private:
    int _nHealth = gMaxHealth;
    int _nScore = 0;
};

#endif // SPACEINVADERSPARTS_H
