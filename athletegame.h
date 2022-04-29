#ifndef ATHLETEGAME_H
#define ATHLETEGAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <athletegameparts.h>
#include <QSize>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QRandomGenerator>

class AthleteGame : public QGraphicsView
{
    Q_OBJECT
public:
    AthleteGame(QSize screenSize, QString difficulty, QWidget* parent = nullptr);
    void run();
    void checkPoints();
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
public slots:
    void onCreateEnemy();
    void onIncreaseScore();
    void onDecreaseScore();
    void onDecreaseHealth();
    void onGameOver(bool);
    void handleExitButton();
signals:
    void sigGameOver(bool,QString);
private:
    QSize _screenSize;
    AthletePart* _athlete = nullptr;
    AthletePointsPart* _points = nullptr;
    QTimer* obstacleTimer = nullptr;
    bool isWonGame;
    int scoreToReach;
    int maxHealth;
    int obstacleSpeed;
    int obstacleSpawnSpeed;
    bool isGameOver = false;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    QString _difficulty;
    bool finishedNormally = false;
};

#endif // ATHLETEGAME_H
