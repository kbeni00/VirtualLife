#include "huntinggame.h"
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
HuntingGame::HuntingGame(QSize screenSize, QString difficulty, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{
    if(difficulty == "Easy"){
        turkeySpeed = 1800;
        turkeysToHunt = 10;
        gameTime = 90000;

    } else if(difficulty == "Medium"){
        turkeySpeed = 1250;
        turkeysToHunt = 15;
        gameTime = 90000;
    } else{
        turkeySpeed = 900;
        turkeysToHunt = 20;
        gameTime = 90000;
    }
    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/huntinggame/huntingbg2.png")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameOverTimer = new QTimer();
    gameOverTimer->start(gameTime);
    connect(gameOverTimer,&QTimer::timeout, this, &HuntingGame::onGameOverTimerUp);

//    QPixmap p = QPixmap(":/huntinggame/crossair.png");
//    QCursor c = QCursor(p, 0, 0);
//    setCursor(c);
//    setStyleSheet("border-style:none");

}

void HuntingGame::run()
{
    scene()->clear();
    _points = new HuntingPointsPart(gameTime, turkeysToHunt);
    scene()->addItem(_points);
    turkeySpawnTimer = new QTimer(this);
    turkeySpawnTimer->start(turkeySpeed);
    connect(turkeySpawnTimer, &QTimer::timeout, this, &HuntingGame::onCreateEnemy);
}

void HuntingGame::checkPoints()
{
    if(_points->getScore() < 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == turkeysToHunt){
        _points->reset();
        onGameOver(true);
    }

}

void HuntingGame::onCreateEnemy()
{
    TurkeyPart* turkey = new TurkeyPart(turkeySpeed);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int posX = QRandomGenerator::global()->bounded(screenGeometry.width()-turkey->turkeySize.width());
    int posY = QRandomGenerator::global()->bounded(screenGeometry.height()-turkey->turkeySize.height());

    turkey->setPos(posX,posY);
    turkey->setFlag((QGraphicsItem::ItemIsFocusable));


    scene()->addItem(turkey);
    connect(turkey, &TurkeyPart::sigGameOver, this, &HuntingGame::onGameOver);
    connect(turkey, &TurkeyPart::sigUpdateScore, this, &HuntingGame::onUpdateScore);
    qDebug() << "creating turkey";
}

void HuntingGame::onUpdateScore(bool res)
{
    TurkeyPart* turkey = dynamic_cast<TurkeyPart*>(QObject::sender());
    scene()->removeItem(turkey);
    delete turkey;
    if(res){
        _points->increaseScore();
        checkPoints();
    }
}

void HuntingGame::onGameOver(bool wonGame)
{
    turkeySpawnTimer->stop();
    gameOverTimer->stop();
    _points->hide();
//    delete turkeySpawnTimer;
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
    connect(exitButton, &QPushButton::clicked ,this, &HuntingGame::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
    //    QGroupBox* groupBox = new QGroupBox();
    //    QFormLayout* layout = new QFormLayout();
    //    layout->addRow(new QLabel("asdasd"));
    //    layout->addRow(exitButton);
    //    groupBox->setLayout(layout);
    isGameWon = wonGame;
}

void HuntingGame::handleExitButton()
{
    this->close();
    emit sigGameOver(isGameWon);
}

void HuntingGame::onGameOverTimerUp()
{
    onGameOver(false);
}
