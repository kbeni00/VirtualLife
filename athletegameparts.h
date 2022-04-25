#ifndef ATHLETEGAMEPARTS_H
#define ATHLETEGAMEPARTS_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

class AthletePart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit AthletePart(QGraphicsItem *parent = nullptr);
    void shoot();
    QSize const athleteSize = QSize(100,100);

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

};

////////////////////////////////////////////////////

class ObstaclePart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ObstaclePart(int,QGraphicsItem *parent = nullptr);
    QSize const obstacleSize = QSize(100,100);
signals:
    void sigGameOver(bool);
    void sigDecreaseHealth();
public slots:
    void onMove();
private:
    int _obstacleSpeed;

};

//////////////////////////////////////////////////////

//class BulletPart : public QObject, public QGraphicsPixmapItem
//{
//    Q_OBJECT
//public:
//    BulletPart(QGraphicsItem *parent = nullptr);
//signals:
//    void sigIncreaseScore();
//    void sigDecreaseScore();
//public slots:
//    void onMove();
//private:
//    int _bulletSpeed = 5;

//};

////////////////////////////////////////////////////

class AthletePointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    AthletePointsPart(int,int,QGraphicsItem *parent = nullptr);
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


#endif // ATHLETEGAMEPARTS_H
