#include "spaceinvaders.h"
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

//TODO: Difficulty levels alter the speed of the aliens -> new window which has a settings, start, exit button
//TODO: Increased intelligence based on difficulty -> Very easy, easy, medium, hard, impossible
//TODO: improve game over method
SpaceInvaders::SpaceInvaders(QSize screenSize, QString difficulty, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{
    if(difficulty == "Easy"){
        scoreToReach = 10;
        maxHealth = 5;
        alienSpeed = 75;
        alienSpawnSpeed = 2000;

    } else if(difficulty == "Medium"){
        scoreToReach = 15;
        maxHealth = 4;
        alienSpeed = 55;
        alienSpawnSpeed = 1650;
    } else{
        scoreToReach = 20;
        maxHealth = 3;
        alienSpeed = 35;
        alienSpawnSpeed = 1300;
    }
    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/spaceinvaders/background.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void SpaceInvaders::run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    _cannon = new CannonPart();

    _cannon->setPos(_screenSize.width()/2, _screenSize.height() - _cannon->cannonSize.height());
    _cannon->setFlag((QGraphicsItem::ItemIsFocusable));
    _cannon->setFocus();
    scene()->addItem(_cannon);

    connect(_cannon, &CannonPart::sigIncreaseScore, this, &SpaceInvaders::onIncreaseScore);
    connect(_cannon, &CannonPart::sigDecreaseScore, this, &SpaceInvaders::onDecreaseHealth);

    _points = new PointsPart(maxHealth,scoreToReach);
    scene()->addItem(_points);

    alienTimer = new QTimer(this);
    alienTimer->start(alienSpawnSpeed);
    connect(alienTimer, &QTimer::timeout, this, &SpaceInvaders::onCreateEnemy);
}

void SpaceInvaders::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == scoreToReach && _points->getHealth() > 0){
        _points->reset();
        onGameOver(true);
    }
}

void SpaceInvaders::keyPressEvent(QKeyEvent *event)
{
    if(_cannon == nullptr) return;
    switch(event->key()){
        case Qt::Key_Left:
            if(_cannon->pos().x() > 0) _cannon->setPos(_cannon->x() - 20, _cannon->y());
            break;
        case Qt::Key_Right:
            if((_cannon->pos().x() + _cannon->cannonSize.width()) < _screenSize.width()) _cannon->setPos(_cannon->x() + 20, _cannon->y());
            break;
        case Qt::Key_Space:
            _cannon->shoot();
            break;
   }
}

void SpaceInvaders::onCreateEnemy()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int posX = QRandomGenerator::global()->bounded(screenGeometry.width()-_cannon->cannonSize.width());
    AlienPart* alien = new AlienPart(alienSpeed);
    alien->setPos(posX,0);

    scene()->addItem(alien);
    connect(alien, &AlienPart::sigGameOver, this, &SpaceInvaders::onGameOver);
    connect(alien, &AlienPart::sigDecreaseHealth, this, &SpaceInvaders::onDecreaseHealth);
}

void SpaceInvaders::onIncreaseScore()
{
    _points->increaseScore();
    checkPoints();
}

void SpaceInvaders::onDecreaseScore()
{
    _points->decreaseScore();
    checkPoints();
}

void SpaceInvaders::onDecreaseHealth()
{
    _points->decreaseHealth();
    checkPoints();
}

void SpaceInvaders::onGameOver(bool wonGame)
{
    alienTimer->stop();
//    delete alienTimer;
//    delete _cannon;
//    delete _points;
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
    connect(exitButton, &QPushButton::clicked ,this, &SpaceInvaders::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
//    QGroupBox* groupBox = new QGroupBox();
//    QFormLayout* layout = new QFormLayout();
//    layout->addRow(new QLabel("asdasd"));
//    layout->addRow(exitButton);
//    groupBox->setLayout(layout);
    isWonGame = wonGame;
}

void SpaceInvaders::handleExitButton()
{
    this->close();
    emit sigGameOver(isWonGame);

}
