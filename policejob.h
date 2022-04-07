#ifndef POLICEJOB_H
#define POLICEJOB_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <policejobparts.h>

class PoliceJob : public QGraphicsView
{
    Q_OBJECT
public:
    PoliceJob(QSize screenSize, QWidget* parent = nullptr);

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
    PoliceCarPart* _policeCar = nullptr;
    TextPart* _points = nullptr;
    QTimer* robberTimer = nullptr;
};

#endif // POLICEJOB_H
