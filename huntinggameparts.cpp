#include "huntinggameparts.h"

TurkeyPart::TurkeyPart(int turkeySpeed, QGraphicsItem *parent)
{
    QPixmap pixmap(":/huntinggame/resources/huntinggame/turkey.png");
    setPixmap(pixmap.scaled(turkeySize, Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TurkeyPart::onMove);
    timer->start(turkeySpeed);
}

void TurkeyPart::onMove()
{
    emit sigUpdateScore(false);
}

void TurkeyPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigUpdateScore(true);
}

HuntingPointsPart::HuntingPointsPart(int gameTime, int turkeysToHunt, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    _turkeysToHunt  = turkeysToHunt;
    updateMetrics();
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
    timeLeftTimer = new QTimer();
    timeLeftTimer->start(gameTime);
    QTimer* refreshTimer = new QTimer();
    refreshTimer->start(1000);
    connect(refreshTimer, &QTimer::timeout, this, &HuntingPointsPart::updateMetrics);
}


void HuntingPointsPart::updateMetrics()
{
    if(timeLeftTimer != nullptr){
        int timeLeft = timeLeftTimer->remainingTime()/1000;
        setPlainText(QString("Time left : ") + QString::number(timeLeft) + "\n"
                     + QString("Score: ") + QString::number(_score)
                     + QString("/") + QString::number(_turkeysToHunt));
    }

}

void HuntingPointsPart::increaseScore()
{
    _score++;
    updateMetrics();
}


int HuntingPointsPart::getScore() const
{
    return _score;
}

void HuntingPointsPart::reset()
{
    _score = 0;
}

