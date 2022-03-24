#include "spaceinvadersparts.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>

CannonPart::CannonPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/spaceinvaders/RedCannon.png");
    setPixmap(pixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
}

void CannonPart::shoot()
{
    BulletPart* bullet = new BulletPart();
    connect(bullet, &BulletPart::sigIncreaseScore, this, &CannonPart::sigIncreaseScore);
    connect(bullet, &BulletPart::sigDecreaseScore, this, &CannonPart::sigDecreaseScore);

    //+30 a hajó mérete miatt, hogy középről jöjjön ki
    bullet->setPos(x() + 30, y() - 10);
    scene()->addItem(bullet);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AlienPart::AlienPart(QGraphicsItem *parent)
{
    QPixmap pixmap(":/spaceinvaders/RedAlien.png");
    setPixmap(pixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AlienPart::onMove);
    timer->start(gAlienSpeed);

}

void AlienPart::onMove()
{
    setPos(x(),y() + 5);

    // collidingItems() contains a list of pointers to all items the bullet is colliding with
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    for(auto const item : lstCollidingItem){
        if(dynamic_cast<CannonPart*>(item)){
            emit sigGameOver();

        }
    }

    if(pos().y() >= (scene()->height() - gCannonSize.height())){
        scene()->removeItem(this);
        emit sigDecreaseHealth();
        qDebug() << "Alien tulment";
        delete this;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

BulletPart::BulletPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/spaceinvaders/RedBullet.png");
    setPixmap(pixmap.scaled(QSize(40,40), Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BulletPart::onMove);
    timer->start(gBulletSpeed);
}

void BulletPart::onMove()
{
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    for(auto const item : lstCollidingItem){
        AlienPart* alien = dynamic_cast<AlienPart*>(item);
        if (alien != nullptr) {
            scene()->removeItem(alien);
            scene()->removeItem(this);

            emit sigIncreaseScore();

            delete alien;
            delete this;
            return;
        }
    }
    setPos(x(),y() - 10);

    if(pos().y() < 0){
        scene()->removeItem(this);
        emit sigDecreaseScore();
        delete this;
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////


PointsPart::PointsPart(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    updateMetrics(_nHealth,_nScore);
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

void PointsPart::updateMetrics(int health, int score){
    setPlainText(QString("Health : ") + QString::number(health) + "\n"
                 + QString("Score: ") + QString::number(score));
}


void PointsPart::increaseScore()
{
    _nScore += 1;
    updateMetrics(_nHealth,_nScore);
}

void PointsPart::decreaseScore()
{
    _nScore -= 1;
    updateMetrics(_nHealth,_nScore);
}

void PointsPart::decreaseHealth()
{
    _nHealth--;
    updateMetrics(_nHealth,_nScore);
}

int PointsPart::getHealth() const
{
    return _nHealth;
}

int PointsPart::getScore() const
{
    return _nScore;
}

void PointsPart::reset()
{
    _nScore = 0;
    _nHealth = gMaxHealth;
}