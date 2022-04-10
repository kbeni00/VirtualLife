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
    void onGameOver(bool);
    void handleExitButton();
signals:
    void sigGameOver(bool);
private:
    QSize _screenSize;
    CannonPart* _cannon = nullptr;
    PointsPart* _points = nullptr;
    QTimer* alienTimer = nullptr;
};

#endif // SPACEINVADERS_H
