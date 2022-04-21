#ifndef CRAWLINGGAME_H
#define CRAWLINGGAME_H


#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <crawlinggameparts.h>
#include <QSize>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

class CrawlingGame : public QGraphicsView
{
    Q_OBJECT
public:
    CrawlingGame(QSize screenSize, QString difficulty, QWidget* parent = nullptr);
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
    void handleCollision();
    void onMilkTick();
signals:
    void sigGameOver(bool,QString);
private:
    QSize _screenSize;
    BabyPart* _baby = nullptr;
    CrawlingPointsPart* _points = nullptr;
    QTimer* toySpawnTimer = nullptr;
    QTimer* milkSpeedTimer = nullptr;
    bool isWonGame;
    int scoreToReach;
    int maxHealth;
    int babySpeed;
    int toySpeed;
    int toySpawnSpeed;
    bool isGameOver = false;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    QString _difficulty;
};


#endif // CRAWLINGGAME_H
