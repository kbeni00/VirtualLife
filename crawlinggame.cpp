#include "crawlinggame.h"
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

CrawlingGame::CrawlingGame(QSize screenSize, QString difficulty, QWidget *parent) : QGraphicsView(parent),_screenSize(screenSize)
{
    mediaPlayer = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    audioOutput->setVolume(50);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/crawlinggame/resources/sounds/crawlinggamemusic.mp3"));
    mediaPlayer->play();
    _difficulty = difficulty;
    if(difficulty == "Easy"){
        scoreToReach = 2;
        maxHealth = 5;
        toySpawnSpeed = 2000;

    } else if(difficulty == "Medium"){
        scoreToReach = 30;
        maxHealth = 4;
        toySpawnSpeed = 1650;
    } else{
        scoreToReach = 40;
        maxHealth = 3;
        toySpawnSpeed = 1300;
    }
    babySpeed = 20;
    QGraphicsScene* scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0,0,_screenSize.width(),_screenSize.height());
    setBackgroundBrush(QBrush(QImage(":/crawlinggame/resources/crawlinggame/citybg.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

void CrawlingGame::run()
{
    scene()->clear();
    setCursor(Qt::BlankCursor);

    _baby = new BabyPart();

    _baby->setPos(_screenSize.width()/2, _screenSize.height() - _baby->babySize.height());
    _baby->setFlag((QGraphicsItem::ItemIsFocusable));
    _baby->setFocus();
    scene()->addItem(_baby);

    connect(_baby, &BabyPart::sigIncreaseScore, this, &CrawlingGame::onIncreaseScore);
    connect(_baby, &BabyPart::sigDecreaseScore, this, &CrawlingGame::onDecreaseHealth);

    _points = new CrawlingPointsPart(maxHealth,scoreToReach);
    scene()->addItem(_points);

    toySpawnTimer = new QTimer(this);
    toySpawnTimer->start(5000);
    connect(toySpawnTimer, &QTimer::timeout, this, &CrawlingGame::onCreateEnemy);
}

void CrawlingGame::checkPoints()
{
    if(_points->getScore() < 0 || _points->getHealth() <= 0){
        _points->reset();
        onGameOver(false);
    } else if(_points->getScore() == scoreToReach && _points->getHealth() > 0){
        _points->reset();
        onGameOver(true);
    }
}

void CrawlingGame::keyPressEvent(QKeyEvent *event)
{
    qDebug() << babySpeed;
    if(_baby == nullptr) return;
    switch(event->key()){
    case Qt::Key_Left:
        if(!isGameOver && _baby->pos().x() > 0){

            _baby->setPos(_baby->x() - babySpeed, _baby->y());
            _baby->setRotation(-90);
        }
        break;
    case Qt::Key_Right:
        if(!isGameOver && (_baby->pos().x() + _baby->babySize.width()) < _screenSize.width()){

            _baby->setPos(_baby->x() + babySpeed, _baby->y());
            _baby->setRotation(90);
        }
        break;
    case Qt::Key_Up:
        if(!isGameOver && _baby->pos().y() > 0){

            _baby->setPos(_baby->x(), _baby->y() - babySpeed);
            _baby->setRotation(0);
        }
        break;
    case Qt::Key_Down:
        if(!isGameOver && (_baby->pos().y() + _baby->babySize.height()) < _screenSize.height()){

            _baby->setPos(_baby->x(), _baby->y() + babySpeed);
            _baby->setRotation(-180);
        }
        break;
    }
}

void CrawlingGame::onCreateEnemy()
{
    QScreen *screen = QApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int posX = QRandomGenerator::global()->bounded(screenGeometry.width()-_baby->babySize.width());
    int posY = QRandomGenerator::global()->bounded(screenGeometry.height()-_baby->babySize.height());
    ToyPart* toy = new ToyPart(toySpeed);
    toy->setPos(posX,posY);

    scene()->addItem(toy);
    connect(toy, &ToyPart::sigGameOver, this, &CrawlingGame::onGameOver);
    connect(toy, &ToyPart::sigDecreaseHealth, this, &CrawlingGame::onDecreaseHealth);
    connect(toy, &ToyPart::sigIncreaseScore, this, &CrawlingGame::onIncreaseScore);
    connect(toy, &ToyPart::sigCollidedWithMilkBottle, this, &CrawlingGame::handleCollision);
}

void CrawlingGame::onIncreaseScore()
{
    _points->increaseScore();
    checkPoints();
}

void CrawlingGame::onDecreaseScore()
{
    _points->decreaseScore();
    checkPoints();
}

void CrawlingGame::onDecreaseHealth()
{
    _points->decreaseHealth();
    checkPoints();
}

void CrawlingGame::onGameOver(bool wonGame)
{
    isGameOver = true;
    toySpawnTimer->stop();
//    milkSpeedTimer->stop();
    //    delete toysSpawnTimer;
    delete _baby;
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
    connect(exitButton, &QPushButton::clicked ,this, &CrawlingGame::handleExitButton);
    QGraphicsProxyWidget* widgetItem = scene()->addWidget(exitButton);
    widgetItem->setPos(width()/2,height()/2+20);
    //    QGroupBox* groupBox = new QGroupBox();
    //    QFormLayout* layout = new QFormLayout();
    //    layout->addRow(new QLabel("asdasd"));
    //    layout->addRow(exitButton);
    //    groupBox->setLayout(layout);
    isWonGame = wonGame;
}

void CrawlingGame::handleExitButton()
{
    mediaPlayer->stop();
    this->close();
    emit sigGameOver(isWonGame,_difficulty);

}

void CrawlingGame::handleCollision()
{
    babySpeed = 30;
    milkSpeedTimer = new QTimer(this);
    milkSpeedTimer->start(1000);
    connect(toySpawnTimer, &QTimer::timeout, this, &CrawlingGame::onMilkTick);

}

void CrawlingGame::onMilkTick()
{
    babySpeed = 20;
    milkSpeedTimer->stop();
}
