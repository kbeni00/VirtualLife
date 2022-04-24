#include "whackamoleparts.h"
#include "qapplication.h"
#include "qpushbutton.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>

MolePart::MolePart(int moleSpeed, QGraphicsItem *parent)
{
    QPixmap pixmap(":/whackamole/resources/whackamole/mole.png");
    setPixmap(pixmap.scaled(moleSize, Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MolePart::onMove);
    timer->start(moleSpeed);
}


void MolePart::onMove()
{
    emit sigUpdateScore(false);
}

void MolePart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigUpdateScore(true);
}

MolePointsPart::MolePointsPart(int gameTime, int molesToHit, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    _molesToHit  = molesToHit;
    updateMetrics();
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
    timeLeftTimer = new QTimer();
    timeLeftTimer->start(gameTime);
    QPushButton* surrender = new QPushButton();
    surrender->setText("Give up");
    QTimer* refreshTimer = new QTimer();
    refreshTimer->start(1000);
    connect(refreshTimer, &QTimer::timeout, this, &MolePointsPart::updateMetrics);
}


void MolePointsPart::updateMetrics()
{
    if(timeLeftTimer != nullptr){
        int timeLeft = timeLeftTimer->remainingTime()/1000;
        setPlainText(QString("Time left : ") + QString::number(timeLeft) + "\n"
                     + QString("Score: ") + QString::number(_score)
                     + QString("/") + QString::number(_molesToHit));
    }

}

void MolePointsPart::increaseScore()
{
    _score++;
    updateMetrics();
}


int MolePointsPart::getScore() const
{
    return _score;
}

void MolePointsPart::reset()
{
    _score = 0;
}

