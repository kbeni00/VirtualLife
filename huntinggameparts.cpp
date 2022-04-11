#include "huntinggameparts.h"
#include "qapplication.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>

TurkeyPart::TurkeyPart(QGraphicsItem *parent)
{
    QPixmap pixmap(":/huntinggame/turkey.png");
    setPixmap(pixmap.scaled(gTurkeySize, Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TurkeyPart::onMove);
    timer->start(500);
}

void TurkeyPart::onMove()
{
    //TODO: ezen javítani h ne menjen ki a képből
//    QScreen *screen = QGuiApplication::primaryScreen();
//    QRect  screenGeometry = screen->geometry();
//    int width = screenGeometry.width();
//    if(x() >= width-gTurkeySize.width()){
//        isMovingRight = false;
//    } else if(x() <= 50){
//        isMovingRight = true;
//    }
//    if(isMovingRight){
//        setPos(x() + 1, y());
//    } else{
//        setPos(x() - 1, y());
//    }
    emit sigUpdateScore(false);
}

void TurkeyPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigUpdateScore(true);
}

HuntingPointsPart::HuntingPointsPart(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    updateMetrics();
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
    timeLeftTimer = new QTimer();
    timeLeftTimer->start(20000);
    QTimer* refreshTimer = new QTimer();
    refreshTimer->start(1000);
    connect(refreshTimer, &QTimer::timeout, this, &HuntingPointsPart::updateMetrics);
}


void HuntingPointsPart::updateMetrics()
{
    if(timeLeftTimer != nullptr){
        int timeLeft = timeLeftTimer->remainingTime()/1000;
        setPlainText(QString("Time left : ") + QString::number(timeLeft) + "\n"
                     + QString("Score: ") + QString::number(_nScore)
                     + QString("/") + QString::number(gTurkeysHunted));
    }

}

void HuntingPointsPart::increaseScore()
{
    _nScore++;
    updateMetrics();
}


int HuntingPointsPart::getScore() const
{
    return _nScore;
}

void HuntingPointsPart::reset()
{
    _nScore = 0;
    _nHealth = gPlayerHealth;
}

