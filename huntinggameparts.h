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
    void sigUpdateScore(bool);
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
    int getScore() const;
    void reset();
    void updateMetrics();

private:
    int _nHealth = gTurkeysHunted;
    int _nScore = 0;
    QTimer* timeLeftTimer = nullptr;
};

#endif // HUNTINGGAMEPARTS_H
