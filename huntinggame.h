#ifndef HUNTINGGAME_H
#define HUNTINGGAME_H

#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <huntinggameparts.h>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>


class HuntingGame : public QGraphicsView
{
    Q_OBJECT
public:
    HuntingGame(QSize screenSize, QString difficulty, QWidget* parent = nullptr);
    void run();
    void checkPoints();
protected:
    void closeEvent(QCloseEvent* event) override;
public slots:
    void onCreateEnemy();
    void onUpdateScore(bool);
    void onGameOver(bool);
    void handleExitButton();
    void onGameOverTimerUp();
    void handleSurrender();
signals:
    void sigGameOver(bool,QString);
private:
    QSize _screenSize;
    HuntingPointsPart* _points = nullptr;
    QTimer* turkeySpawnTimer = nullptr;
    QTimer* gameOverTimer = nullptr;
    bool isGameWon;
    int turkeySpeed;
    int turkeysToHunt;
    int gameTime;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    QString _difficulty;
    bool finishedNormally = false;

};

#endif // HUNTINGGAME_H
