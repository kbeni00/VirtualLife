#ifndef HUNTINGGAME_H
#define HUNTINGGAME_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <huntinggameparts.h>


//TODO: timerrel működjön
class HuntingGame : public QGraphicsView
{
    Q_OBJECT
public:
    HuntingGame(QSize screenSize, QWidget* parent = nullptr);
    void run();
    void checkPoints();
public slots:
    void onCreateEnemy();
    void onUpdateScore(bool);
    void onGameOver(bool);
    void handleExitButton();
    void onGameOverTimerUp();
signals:
    void sigGameOver(bool);
private:
    QSize _screenSize;
    HuntingPointsPart* _points = nullptr;
    QTimer* turkeySpawnTimer = nullptr;
    QTimer* gameOverTimer = nullptr;
};

#endif // HUNTINGGAME_H
