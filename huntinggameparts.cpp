#include "huntinggameparts.h"
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
    timer->start(1);
}

void TurkeyPart::onMove()
{
    //TODO: ezen javítani h ne menjen ki a képből
    if(x() >= 1400){
        isMovingRight = false;
    } else if(x() <= 50){
        isMovingRight = true;
    }
    if(isMovingRight){
        setPos(x() + 0.05, y());
    } else{
        setPos(x() - 0.05, y());
    }
}

HuntingPointsPart::HuntingPointsPart(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    updateMetrics(_nHealth,_nScore);
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}


void TurkeyPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigIncreaseScore();
}

void HuntingPointsPart::updateMetrics(int health, int score)
{
    setPlainText(QString("Health : ") + QString::number(health) + "\n"
                 + QString("Score: ") + QString::number(score)
                 + QString("/") + QString::number(gTurkeysHunted));
}

void HuntingPointsPart::increaseScore()
{
    _nScore += 1;
    updateMetrics(_nHealth,_nScore);
}

void HuntingPointsPart::decreaseScore()
{
    _nScore -= 1;
    updateMetrics(_nHealth,_nScore);
}

void HuntingPointsPart::decreaseHealth()
{
    _nHealth--;
    updateMetrics(_nHealth,_nScore);
}

int HuntingPointsPart::getHealth() const
{
    return _nHealth;
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

