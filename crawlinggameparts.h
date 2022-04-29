#ifndef CRAWLINGGAMEPARTS_H
#define CRAWLINGGAMEPARTS_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QApplication>

class BabyPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit BabyPart(QGraphicsItem *parent = nullptr);
    void shoot();
    QSize const babySize = QSize(100,100);

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

};

////////////////////////////////////////////////////

class ToyPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ToyPart(int,QGraphicsItem *parent = nullptr);
    QSize const toySize = QSize(100,100);
signals:
    void sigGameOver(bool);
    void sigDecreaseHealth();
    void sigIncreaseScore();
    void sigCollidedWithMilkBottle();
public slots:
    void onMove();
private:
    int _toySpeed;
    bool isMovingRight = true;
    bool isMilkBottle = false;

};

////////////////////////////////////////////////////

class CrawlingPointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    CrawlingPointsPart(int,int,QGraphicsItem *parent = nullptr);
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


#endif // CRAWLINGGAMEPARTS_H
