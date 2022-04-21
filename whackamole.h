#ifndef WHACKAMOLE_H
#define WHACKAMOLE_H


#include <QPointer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <whackamoleparts.h>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

class WhackAMole : public QGraphicsView
{
    Q_OBJECT
public:
    WhackAMole(QSize screenSize, QString difficulty, QWidget* parent = nullptr);
    void run();
    void checkPoints();
public slots:
    void onCreateEnemy();
    void onUpdateScore(bool);
    void onGameOver(bool);
    void handleExitButton();
    void onGameOverTimerUp();
signals:
    void sigGameOver(bool,QString);
private:
    QSize _screenSize;
    MolePointsPart* _points = nullptr;
    QTimer* moleSpawnTimer = nullptr;
    QTimer* gameOverTimer = nullptr;
    bool isGameWon;
    int moleSpeed;
    int molesToHit;
    int gameTime;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    QVector<QPointF> holeCoordinates;
    QString _difficulty;
};


#endif // WHACKAMOLE_H