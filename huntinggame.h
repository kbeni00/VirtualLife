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
    void onIncreaseScore();
    void onGameOver(bool);
    void handleExitButton();
signals:
    void sigGameOver(bool);
private:
    QSize _screenSize;
    HuntingPointsPart* _points = nullptr;
    QTimer* turkeySpawnTimer = nullptr;
};

#endif // HUNTINGGAME_H
