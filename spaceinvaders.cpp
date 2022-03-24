#include "spaceinvaders.h"
#include "qapplication.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QEventLoop>

//TODO: Difficulty levels alter the speed of the aliens -> new window which has a settings, start, exit button
//TODO: Increased intelligence based on difficulty -> Very easy, easy, medium, hard, impossible
//TODO: inform user abt the # of points they have to reach
//TODO: improve game over method
SpaceInvaders::SpaceInvaders(QSize screenSize, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{

    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/spaceinvaders/SpaceInvadersBg.jpg")));
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

    _cannon->setPos(_screenSize.width()/2, _screenSize.height() - gCannonSize.height());
    _cannon->setFlag((QGraphicsItem::ItemIsFocusable));
    _cannon->setFocus();
    scene()->addItem(_cannon);

    connect(_cannon, &CannonPart::sigIncreaseScore, this, &SpaceInvaders::onIncreaseScore);
    connect(_cannon, &CannonPart::sigDecreaseScore, this, &SpaceInvaders::onDecreaseHealth);

    _points = new PointsPart();
    scene()->addItem(_points);

    alienTimer = new QTimer(this);
    alienTimer->start(2000);
    connect(alienTimer, &QTimer::timeout, this, &SpaceInvaders::onCreateEnemy);
}

void delay(int n)
{
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void SpaceInvaders::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver();
    } else if(_points->getScore() >= 10 && _points->getHealth() > 0){
        _points->reset();
        onGameOver();
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
            if((_cannon->pos().x() + gCannonSize.width()) < _screenSize.width()) _cannon->setPos(_cannon->x() + 20, _cannon->y());
            break;
        case Qt::Key_Space:
            _cannon->shoot();
            break;
   }
}

void SpaceInvaders::onCreateEnemy()
{
    int pos = rand() % _screenSize.width();
    AlienPart* alien = new AlienPart();
    alien->setPos(pos,0);

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

void SpaceInvaders::onGameOver()
{
    sigGameOver();
    delete _cannon;
    delete _points;
    alienTimer->stop();
    delete alienTimer;
    scene()->clear();
    close();
}
