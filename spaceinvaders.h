#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <spaceinvadersparts.h>

class SpaceInvaders : public QGraphicsView
{
    Q_OBJECT
public:
    SpaceInvaders(QSize screenSize, QWidget* parent = nullptr);

    void run();
    void checkPoints();
protected:
    void keyPressEvent(QKeyEvent* event) override;
public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseScore();
    void onDecreaseHealth();
    void onGameOver();
signals:
    void sigGameOver();
private:
    CannonPart* _cannon = nullptr;
    PointsPart* _points = nullptr;
    QSize _screenSize;
    QTimer* alienTimer = nullptr;
};

#endif // SPACEINVADERS_H
