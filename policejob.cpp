#include "policejob.h"
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
#include <QUuid>
#include <math.h>

//TODO: Timer alapján legyen vége a játéknak, random spawnoljon egy +5mp cuccli amit fel lehet venni
//TODO: add nitro?
//TODO: Difficulty levels alter the speed of the aliens -> new window which has a settings, start, exit button
//TODO: Increased intelligence based on difficulty -> Very easy, easy, medium, hard, impossible
//TODO: improve game over method
PoliceJob::PoliceJob(QSize screenSize, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{

    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/PoliceJob/PoliceJobBg.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void PoliceJob::run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    _policeCar = new PoliceCarPart();

    _policeCar->setPos(_screenSize.width()/2, _screenSize.height() - gPoliceCarSize.height());
    _policeCar->setFlag((QGraphicsItem::ItemIsFocusable));
    _policeCar->setFocus();
    scene()->addItem(_policeCar);

    //itt írd át
    connect(_policeCar, &PoliceCarPart::sigIncreaseScore, this, &PoliceJob::onIncreaseScore);
    connect(_policeCar, &PoliceCarPart::sigDecreaseScore, this, &PoliceJob::onDecreaseHealth);

    _points = new TextPart();
    scene()->addItem(_points);

    robberTimer = new QTimer(this);
    //change based on difficulty
    robberTimer->start(5000);
    connect(robberTimer, &QTimer::timeout, this, &PoliceJob::onCreateEnemy);
}

void PoliceJob::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == gMaxScore && _points->getHealth() > 0){
        _points->reset();
        onGameOver(true);
    }

}

void PoliceJob::keyPressEvent(QKeyEvent *event)
{
    if(_policeCar == nullptr) return;
    switch(event->key()){
    case Qt::Key_Left:
        if(_policeCar->pos().x() > 0) _policeCar->setPos(_policeCar->x() - 20, _policeCar->y());
        break;
    case Qt::Key_Right:
        if(_policeCar->pos().x() < _screenSize.width()) _policeCar->setPos(_policeCar->x() + 20, _policeCar->y());
        break;
    case Qt::Key_Up:
        if(_policeCar->pos().y() > 0) _policeCar->setPos(_policeCar->x(), _policeCar->y() - 20);
        break;
    case Qt::Key_Down:
        if(_policeCar->pos().y() < _screenSize.height()) _policeCar->setPos(_policeCar->x(), _policeCar->y() + 20);
        break;
    }

}

void PoliceJob::onCreateEnemy()
{
    int xpos = rand() % _screenSize.width();
    int ypos = rand() % _screenSize.height();
    RobberCarPart* alien = new RobberCarPart();
    alien->setPos(xpos,abs(ypos-400));

    scene()->addItem(alien);
    connect(alien, &RobberCarPart::sigGameOver, this, &PoliceJob::onGameOver);
    connect(alien, &RobberCarPart::sigDecreaseHealth, this, &PoliceJob::onDecreaseHealth);
}

void PoliceJob::onIncreaseScore()
{
    _points->increaseScore();
    checkPoints();
}

void PoliceJob::onDecreaseScore()
{
    _points->decreaseScore();
    checkPoints();
}

void PoliceJob::onDecreaseHealth()
{
    _points->decreaseHealth();
    checkPoints();
}

void PoliceJob::onGameOver(bool wonGame)
{
    robberTimer->stop();
    delete robberTimer;
    delete _policeCar;
    delete _points;
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
    connect(exitButton, &QPushButton::clicked ,this, &PoliceJob::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
    emit sigGameOver(wonGame);
}

void PoliceJob::handleExitButton()
{
    this->close();
}
