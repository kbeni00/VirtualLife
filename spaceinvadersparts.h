#ifndef SPACEINVADERSPARTS_H
#define SPACEINVADERSPARTS_H

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
    QSize const cannonSize = QSize(100,100);

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

};

////////////////////////////////////////////////////

class AlienPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AlienPart(int,QGraphicsItem *parent = nullptr);
    QSize const alienSize = QSize(100,100);
signals:
    void sigGameOver(bool);
    void sigDecreaseHealth();
public slots:
    void onMove();
private:
    int _alienSpeed;

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
private:
    int _bulletSpeed = 5;

};

////////////////////////////////////////////////////

class PointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    PointsPart(int,int,QGraphicsItem *parent = nullptr);
    void increaseScore();
    void decreaseScore();
    void decreaseHealth();

    int getHealth() const;
    int getScore() const;

    void reset();
    void updateMetrics(int, int);

private:
    int _health = 0;
    int _score = 0;
    int _scoreToReach = 0;
};

#endif // SPACEINVADERSPARTS_H
