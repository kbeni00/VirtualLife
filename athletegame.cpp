#include "athletegame.h"
#include "qapplication.h"
#include "qlabel.h"
#include "qtextdocument.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QEventLoop>
#include <QColor>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QRandomGenerator>

AthleteGame::AthleteGame(QSize screenSize, QString difficulty, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{
//    mediaPlayer = new QMediaPlayer;
//    audioOutput = new QAudioOutput;
//    audioOutput->setVolume(50);
//    mediaPlayer->setAudioOutput(audioOutput);
//    mediaPlayer->setSource(QUrl("qrc:/AthleteGame/resources/sounds/athletegamemusic.mp3"));
//    mediaPlayer->play();

    _difficulty = difficulty;
    if(difficulty == "Easy"){
        scoreToReach = 20;
        maxHealth = 5;
        obstacleSpeed = 75;
        obstacleSpawnSpeed = 2000;

    } else if(difficulty == "Medium"){
        scoreToReach = 30;
        maxHealth = 4;
        obstacleSpeed = 55;
        obstacleSpawnSpeed = 1650;
    } else{
        scoreToReach = 40;
        maxHealth = 3;
        obstacleSpeed = 35;
        obstacleSpawnSpeed = 1300;
    }
    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/athletegame/resources/athletegame/background.png")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void AthleteGame::run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    _athlete = new AthletePart();

    _athlete->setPos(0, _screenSize.height() - (_athlete->athleteSize.height() + 20));
    _athlete->setFlag((QGraphicsItem::ItemIsFocusable));
    _athlete->setFocus();
    scene()->addItem(_athlete);

    connect(_athlete, &AthletePart::sigIncreaseScore, this, &AthleteGame::onIncreaseScore);
    connect(_athlete, &AthletePart::sigDecreaseScore, this, &AthleteGame::onDecreaseHealth);

    _points = new AthletePointsPart(maxHealth,scoreToReach);
    scene()->addItem(_points);

    obstacleTimer = new QTimer(this);
    obstacleTimer->start(obstacleSpawnSpeed);
    connect(obstacleTimer, &QTimer::timeout, this, &AthleteGame::onCreateEnemy);
}

void AthleteGame::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == scoreToReach && _points->getHealth() > 0){
        _points->reset();
        onGameOver(true);
    }
}

void AthleteGame::keyPressEvent(QKeyEvent *event)
{
    if(_athlete == nullptr) return;
    switch(event->key()){
    case Qt::Key_Left:
        if(!isGameOver && _athlete->pos().x() > 0) _athlete->setPos(_athlete->x() - 20, _athlete->y());
        break;
    case Qt::Key_Right:
        if(!isGameOver && (_athlete->pos().x() + _athlete->athleteSize.width()) < _screenSize.width()) _athlete->setPos(_athlete->x() + 20, _athlete->y());
        break;
    case Qt::Key_Space:
        if(!isGameOver){
            _athlete->shoot();
        }
        break;
    }
}

void AthleteGame::onCreateEnemy()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int posX = QRandomGenerator::global()->bounded(screenGeometry.width()-_athlete->athleteSize.width());
    ObstaclePart* obstacle = new ObstaclePart(obstacleSpeed);
    obstacle->setPos(_screenSize.width(),_screenSize.height() - 120);

    scene()->addItem(obstacle);
    connect(obstacle, &ObstaclePart::sigGameOver, this, &AthleteGame::onGameOver);
    connect(obstacle, &ObstaclePart::sigDecreaseHealth, this, &AthleteGame::onDecreaseHealth);
}

void AthleteGame::onIncreaseScore()
{
    _points->increaseScore();
    checkPoints();
}

void AthleteGame::onDecreaseScore()
{
    _points->decreaseScore();
    checkPoints();
}

void AthleteGame::onDecreaseHealth()
{
    _points->decreaseHealth();
    checkPoints();
}

void AthleteGame::onGameOver(bool wonGame)
{
    isGameOver = true;
    obstacleTimer->stop();
    //    delete obstacleTimer;
    delete _athlete;
    delete _points;
    //potential mistake
    scene()->clear();
    setCursor(Qt::PointingHandCursor);
    QGraphicsTextItem* text = new QGraphicsTextItem();
    text->setDefaultTextColor(Qt::red);
    text->setFont(QFont("times", 48));
    if(wonGame){
        text->setPlainText("You won!");
    } else{
        text->setPlainText("You lost!");
    }
    text->setPos(width()/2-162,height()/2-100);
    scene()->addItem(text);
    QPushButton* exitButton = new QPushButton("Exit game");
    connect(exitButton, &QPushButton::clicked ,this, &AthleteGame::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
    //    QGroupBox* groupBox = new QGroupBox();
    //    QFormLayout* layout = new QFormLayout();
    //    layout->addRow(new QLabel("asdasd"));
    //    layout->addRow(exitButton);
    //    groupBox->setLayout(layout);
    isWonGame = wonGame;
}

void AthleteGame::handleExitButton()
{
//    mediaPlayer->stop();
    this->close();
    emit sigGameOver(isWonGame,_difficulty);

}

