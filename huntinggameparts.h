#ifndef HUNTINGGAMEPARTS_H
#define HUNTINGGAMEPARTS_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


class TurkeyPart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TurkeyPart(int,QGraphicsItem *parent = nullptr);
    QSize const turkeySize = QSize(200,200);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void sigGameOver(bool);
    void sigUpdateScore(bool);
public slots:
    void onMove();


};

////////////////////////////////////////////////////

class HuntingPointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    HuntingPointsPart(int,int,QGraphicsItem *parent = nullptr);
    void increaseScore();
    int getScore() const;
    void reset();
    void updateMetrics();

private:
    int _health = 0;
    int _score = 0;
    int _gameTime;
    int _turkeysToHunt;
    QTimer* timeLeftTimer = nullptr;
};

#endif // HUNTINGGAMEPARTS_H
