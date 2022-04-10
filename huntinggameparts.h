#ifndef HUNTINGGAMEPARTS_H
#define HUNTINGGAMEPARTS_H

#include "huntinggamesettings.h"
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class TurkeyPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TurkeyPart(QGraphicsItem *parent = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void sigGameOver(bool);
    void sigIncreaseScore();
public slots:
    void onMove();
private:
    bool isMovingRight = true;


};

////////////////////////////////////////////////////

class HuntingPointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    HuntingPointsPart(QGraphicsItem *parent = nullptr);
    void increaseScore();
    void decreaseScore();
    void decreaseHealth();

    int getHealth() const;
    int getScore() const;

    void reset();
    void updateMetrics(int, int);

private:
    int _nHealth = gTurkeysHunted;
    int _nScore = 0;
};

#endif // HUNTINGGAMEPARTS_H
