#include "whackamole.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>
#include <QApplication>
#include <QGraphicsItem>


//TODO: Difficulty levels alter the speed of the aliens -> new window which has a settings, start, exit button
WhackAMole::WhackAMole(QSize screenSize, QString difficulty, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{
//    mediaPlayer = new QMediaPlayer;
//    audioOutput = new QAudioOutput;
//    audioOutput->setVolume(50);
//    mediaPlayer->setAudioOutput(audioOutput);
//    mediaPlayer->setSource(QUrl("qrc:/whackamole/whackamolemusic.mp3"));
//    mediaPlayer->play();

    _difficulty = difficulty;
    if(difficulty == "Easy"){
        moleSpeed = 1800;
        molesToHit = 10;
        gameTime = 90000;

    } else if(difficulty == "Medium"){
        moleSpeed = 1250;
        molesToHit = 15;
        gameTime = 90000;
    } else{
        moleSpeed = 900;
        molesToHit = 20;
        gameTime = 90000;
    }
    QGraphicsScene* scene = new QGraphicsScene();
    scene->installEventFilter(this);
    setScene(scene);
    QScreen *pscreen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = pscreen->geometry();
    scene->setSceneRect(0,0,screenGeometry.width(),screenGeometry.height());
    setBackgroundBrush(QBrush(QImage(":/whackamole/whackamolebg2.png").scaled(QSize(_screenSize.width(),_screenSize.height()))));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameOverTimer = new QTimer();
    gameOverTimer->start(gameTime);
    connect(gameOverTimer,&QTimer::timeout, this, &WhackAMole::onGameOverTimerUp);

//        QPixmap p = QPixmap(":/whackamole/hammer.png");
//        QCursor c = QCursor(p, -400, -200);
//        setCursor(c);
//        setStyleSheet("border-style:none");

    holeCoordinates.push_back(QPointF(146,332));
    holeCoordinates.push_back(QPointF(534,334));
    holeCoordinates.push_back(QPointF(901,327));
    holeCoordinates.push_back(QPointF(1261,335));
    holeCoordinates.push_back(QPointF(152,501));
    holeCoordinates.push_back(QPointF(543,502));
    holeCoordinates.push_back(QPointF(907,500));
    holeCoordinates.push_back(QPointF(1286,503));
    holeCoordinates.push_back(QPointF(162,682));
    holeCoordinates.push_back(QPointF(549,673));
    holeCoordinates.push_back(QPointF(893,673));
    holeCoordinates.push_back(QPointF(1301,670));
}

void WhackAMole::run()
{
    scene()->clear();
    _points = new MolePointsPart(gameTime, molesToHit);
    scene()->addItem(_points);
    moleSpawnTimer = new QTimer(this);
    moleSpawnTimer->start(moleSpeed);
    connect(moleSpawnTimer, &QTimer::timeout, this, &WhackAMole::onCreateEnemy);
}

void WhackAMole::checkPoints()
{
    if(_points->getScore() < 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == molesToHit){
        _points->reset();
        onGameOver(true);
    }

}

void WhackAMole::onCreateEnemy()
{
    MolePart* mole = new MolePart(moleSpeed);
    int pos = QRandomGenerator::global()->bounded(holeCoordinates.size());
    QPointF point = holeCoordinates.at(pos);
    point.setX(point.x() - 100);
    point.setY(point.y() - 120);
    mole->setPos(point);
    mole->setFlag((QGraphicsItem::ItemIsFocusable));


    scene()->addItem(mole);
    connect(mole, &MolePart::sigGameOver, this, &WhackAMole::onGameOver);
    connect(mole, &MolePart::sigUpdateScore, this, &WhackAMole::onUpdateScore);
}

void WhackAMole::onUpdateScore(bool res)
{
    MolePart* mole = dynamic_cast<MolePart*>(QObject::sender());
    scene()->removeItem(mole);
    delete mole;
    if(res){
        _points->increaseScore();
        checkPoints();
    }
}

void WhackAMole::onGameOver(bool wonGame)
{
    moleSpawnTimer->stop();
    gameOverTimer->stop();
    _points->hide();
    //    delete moleSpawnTimer;
    //    delete _points;
    //    scene()->clear();
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
    connect(exitButton, &QPushButton::clicked ,this, &WhackAMole::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
    //    QGroupBox* groupBox = new QGroupBox();
    //    QFormLayout* layout = new QFormLayout();
    //    layout->addRow(new QLabel("asdasd"));
    //    layout->addRow(exitButton);
    //    groupBox->setLayout(layout);
    isGameWon = wonGame;
}

void WhackAMole::handleExitButton()
{
//    mediaPlayer->stop();
    this->close();
    emit sigGameOver(isGameWon, _difficulty);
}

void WhackAMole::onGameOverTimerUp()
{
    onGameOver(false);
}
