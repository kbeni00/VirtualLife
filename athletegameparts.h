#ifndef ATHLETEGAMEPARTS_H
#define ATHLETEGAMEPARTS_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class AthletePart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit AthletePart(QGraphicsItem *parent = nullptr);
    void jump();
    QSize const athleteSize = QSize(200,200);
    QPropertyAnimation* getJumpUpAnim() const;
    QPropertyAnimation* getJumpDownAnim() const;
    qreal y() const;
    bool isJumping() const;
    void fall();

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

public slots:
    void setY(qreal y);

private:
    QTimer* _timer;
    bool _isJumping;
    QPixmap jumpPixmap;
    QPropertyAnimation *jumpUpAnim, *jumpDownAnim;
    qreal _y;
    qreal jumpHeight;

};

////////////////////////////////////////////////////

class ObstaclePart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ObstaclePart(int,QGraphicsItem *parent = nullptr);
    QSize const obstacleSize = QSize(200,200);
signals:
    void sigGameOver(bool);
    void sigDecreaseHealth();
public slots:
    void onMove();
private:
    int _obstacleSpeed;

};

//////////////////////////////////////////////////////

class CoinPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CoinPart(int,QGraphicsItem *parent = nullptr);
    QSize const coinSize = QSize(100,100);
signals:
    void sigIncreaseScore();
public slots:
    void onMove();

};

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
