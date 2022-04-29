#include "spaceinvadersparts.h"

CannonPart::CannonPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/spaceinvaders/resources/spaceinvaders/spaceship.png");
    setPixmap(pixmap.scaled(cannonSize, Qt::KeepAspectRatio));
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

AlienPart::AlienPart(int alienSpeed, QGraphicsItem *parent)
{
    QPixmap pixmap(":/spaceinvaders/resources/spaceinvaders/RedAlien.png");
    setPixmap(pixmap.scaled(alienSize, Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AlienPart::onMove);
    timer->start(alienSpeed);

}

void AlienPart::onMove()
{
    setPos(x(),y() + 5);

    // collidingItems() contains a list of pointers to all items the alien, is colliding with
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    bool gameRunning = true;

    for(auto const item : lstCollidingItem){
        if(dynamic_cast<CannonPart*>(item)){
            emit sigGameOver(false);
            gameRunning = false;
            break;

        }
    }


    if(gameRunning){
        if(pos().y() >= (scene()->height() - alienSize.height())){
            scene()->removeItem(this);
            emit sigDecreaseHealth();
            delete this;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

BulletPart::BulletPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/spaceinvaders/resources/spaceinvaders/RedBullet.png");
    setPixmap(pixmap.scaled(QSize(40,40), Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BulletPart::onMove);
    timer->start(_bulletSpeed);
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


PointsPart::PointsPart(int maxHealth, int scoreToReach, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    _health = maxHealth;
    _scoreToReach = scoreToReach;

    updateMetrics(_health,_score);
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

void PointsPart::updateMetrics(int health, int score)
{
    setPlainText(QString("Health : ") + QString::number(health) + "\n"
                 + QString("Score: ") + QString::number(score)
                 + QString("/") + QString::number(_scoreToReach));
}


void PointsPart::increaseScore()
{
    _score += 1;
    updateMetrics(_health,_score);
}

void PointsPart::decreaseScore()
{
    _score -= 1;
    updateMetrics(_health,_score);
}

void PointsPart::decreaseHealth()
{
    _health--;
    updateMetrics(_health,_score);
}

int PointsPart::getHealth() const
{
    return _health;
}

int PointsPart::getScore() const
{
    return _score;
}

void PointsPart::reset()
{
    _score = 0;
    _health = 0;
}
