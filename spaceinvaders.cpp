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

//TODO: Difficulty levels alter the speed of the aliens -> new window which has a settings, start, exit button
//TODO: Increased intelligence based on difficulty -> Very easy, easy, medium, hard, impossible
//TODO: improve game over method
SpaceInvaders::SpaceInvaders(QSize screenSize, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{

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

void SpaceInvaders::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == gScoreToReach && _points->getHealth() > 0){
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
            if((_cannon->pos().x() + gCannonSize.width()) < _screenSize.width()) _cannon->setPos(_cannon->x() + 20, _cannon->y());
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
    int width = screenGeometry.width();
    int pos = rand() % width-gCannonSize.width();
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

void SpaceInvaders::onGameOver(bool wonGame)
{
    alienTimer->stop();
    delete alienTimer;
    delete _cannon;
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
    connect(exitButton, &QPushButton::clicked ,this, &SpaceInvaders::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
//    QGroupBox* groupBox = new QGroupBox();
//    QFormLayout* layout = new QFormLayout();
//    layout->addRow(new QLabel("asdasd"));
//    layout->addRow(exitButton);
//    groupBox->setLayout(layout);
    emit sigGameOver(wonGame);
}

void SpaceInvaders::handleExitButton()
{
    this->close();
}
