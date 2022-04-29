#ifndef WHACKAMOLEPARTS_H
#define WHACKAMOLEPARTS_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>


class MolePart : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MolePart(int,QGraphicsItem *parent = nullptr);
    QSize const moleSize = QSize(200,200);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void sigGameOver(bool);
    void sigUpdateScore(bool);
public slots:
    void onMove();


};

////////////////////////////////////////////////////

class MolePointsPart : public QGraphicsTextItem
{
    Q_OBJECT
public:
    MolePointsPart(int,int,QGraphicsItem *parent = nullptr);
    void increaseScore();
    int getScore() const;
    void reset();
    void updateMetrics();

private:
    int _health = 0;
    int _score = 0;
    int _gameTime;
    int _molesToHit;
    QTimer* timeLeftTimer = nullptr;
};

#endif // WHACKAMOLEPARTS_H
