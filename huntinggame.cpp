#include "huntinggame.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>

//TODO: Difficulty levels alter the speed of the aliens -> new window which has a settings, start, exit button
//TODO: Increased intelligence based on difficulty -> Very easy, easy, medium, hard, impossible
//TODO: improve game over method
HuntingGame::HuntingGame(QSize screenSize, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{
    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/huntinggame/huntingbg2.png")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    QPixmap p = QPixmap(":/huntinggame/crossair.png");
//    QCursor c = QCursor(p, 0, 0);
//    setCursor(c);
    setStyleSheet("border-style:none");

}

void HuntingGame::run()
{
    scene()->clear();
    _points = new HuntingPointsPart();
    scene()->addItem(_points);

    turkeySpawnTimer = new QTimer(this);
    turkeySpawnTimer->start(1500);
    connect(turkeySpawnTimer, &QTimer::timeout, this, &HuntingGame::onCreateEnemy);
}

void HuntingGame::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == gTurkeysHunted && _points->getHealth() > 0){
        _points->reset();
        onGameOver(true);
    }

}

void HuntingGame::onCreateEnemy()
{
    TurkeyPart* turkey = new TurkeyPart();
    //TODO:ezen javítani h ne lógjon ki a képernyőből
    int posX = QRandomGenerator::global()->bounded(_screenSize.width());
    int posY = QRandomGenerator::global()->bounded(_screenSize.height());

    turkey->setPos(posX,posY);
    turkey->setFlag((QGraphicsItem::ItemIsFocusable));


    scene()->addItem(turkey);
    connect(turkey, &TurkeyPart::sigGameOver, this, &HuntingGame::onGameOver);
    connect(turkey, &TurkeyPart::sigIncreaseScore, this, &HuntingGame::onIncreaseScore);
}

void HuntingGame::onIncreaseScore()
{
    TurkeyPart* turkey = dynamic_cast<TurkeyPart*>(QObject::sender());
    scene()->removeItem(turkey);
    delete turkey;
    _points->increaseScore();
    checkPoints();
}

void HuntingGame::onGameOver(bool wonGame)
{
    turkeySpawnTimer->stop();
    delete turkeySpawnTimer;
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
    connect(exitButton, &QPushButton::clicked ,this, &HuntingGame::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
    //    QGroupBox* groupBox = new QGroupBox();
    //    QFormLayout* layout = new QFormLayout();
    //    layout->addRow(new QLabel("asdasd"));
    //    layout->addRow(exitButton);
    //    groupBox->setLayout(layout);
    emit sigGameOver(wonGame);
}

void HuntingGame::handleExitButton()
{
    this->close();
}
