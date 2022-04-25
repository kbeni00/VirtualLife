#include "athletegameparts.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>

AthletePart::AthletePart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/athletegame/resources/athletegame/runner.png");
    setPixmap(pixmap.scaled(athleteSize, Qt::KeepAspectRatio));
}

void AthletePart::shoot()
{
//    BulletPart* bullet = new BulletPart();
//    connect(bullet, &BulletPart::sigIncreaseScore, this, &CannonPart::sigIncreaseScore);
//    connect(bullet, &BulletPart::sigDecreaseScore, this, &CannonPart::sigDecreaseScore);

//    //+30 a hajó mérete miatt, hogy középről jöjjön ki
//    bullet->setPos(x() + 30, y() - 10);
//    scene()->addItem(bullet);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ObstaclePart::ObstaclePart(int athleteSpeed, QGraphicsItem *parent)
{
    QPixmap pixmap(":/athletegame/resources/athletegame/hurdle.png");
    setPixmap(pixmap.scaled(obstacleSize, Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ObstaclePart::onMove);
    timer->start(athleteSpeed);

}

void ObstaclePart::onMove()
{
    setPos(x()-5,y());

    // collidingItems() contains a list of pointers to all items the alien, is colliding with
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    bool gameRunning = true;

    for(auto const item : lstCollidingItem){
        if(dynamic_cast<AthletePart*>(item)){
            scene()->removeItem(this);
            emit sigDecreaseHealth();
            delete this;
            break;

        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////


AthletePointsPart::AthletePointsPart(int maxHealth, int scoreToReach, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    _health = maxHealth;
    _scoreToReach = scoreToReach;

    updateMetrics(_health,_score);
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

void AthletePointsPart::updateMetrics(int health, int score)
{
    setPlainText(QString("Health : ") + QString::number(health) + "\n"
                 + QString("Score: ") + QString::number(score)
                 + QString("/") + QString::number(_scoreToReach));
}


void AthletePointsPart::increaseScore()
{
    _score += 1;
    updateMetrics(_health,_score);
}

void AthletePointsPart::decreaseScore()
{
    _score -= 1;
    updateMetrics(_health,_score);
}

void AthletePointsPart::decreaseHealth()
{
    _health--;
    updateMetrics(_health,_score);
}

int AthletePointsPart::getHealth() const
{
    return _health;
}

int AthletePointsPart::getScore() const
{
    return _score;
}

void AthletePointsPart::reset()
{
    _score = 0;
    _health = 0;
}
