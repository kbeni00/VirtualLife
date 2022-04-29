#ifndef WHACKAMOLE_H
#define WHACKAMOLE_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <whackamoleparts.h>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>

class WhackAMole : public QGraphicsView
{
    Q_OBJECT
public:
    WhackAMole(QSize screenSize, QString difficulty, QWidget* parent = nullptr);
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
    bool finishedNormally = false;

};


#endif // WHACKAMOLE_H
