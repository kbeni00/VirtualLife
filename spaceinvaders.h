#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <spaceinvadersparts.h>
#include <QSize>

class SpaceInvaders : public QGraphicsView
{
    Q_OBJECT
public:
    SpaceInvaders(QSize screenSize, QString difficulty, QWidget* parent = nullptr);
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
    bool isWonGame;
    int scoreToReach;
    int maxHealth;
    int alienSpeed;
    int alienSpawnSpeed;
};

#endif // SPACEINVADERS_H
