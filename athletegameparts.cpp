#include "athletegameparts.h"

AthletePart::AthletePart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/athletegame/resources/athletegame/runner.png");
    setPixmap(pixmap.scaled(athleteSize, Qt::KeepAspectRatio));

    _isJumping = false;
    jumpUpAnim = new QPropertyAnimation(this,"y",this);
    jumpDownAnim = new QPropertyAnimation(this,"y",this);
    jumpHeight = 500;
}

void AthletePart::setY(qreal y)
{
    moveBy(0,y-_y);
    _y = y;
}

bool AthletePart::isJumping() const
{
    return _isJumping;
}

void AthletePart::jump()
{
    _isJumping = true;
    jumpUpAnim->setStartValue(y());
    jumpUpAnim->setEndValue(y() - jumpHeight);
    jumpUpAnim->setEasingCurve(QEasingCurve::OutQuad);
    jumpUpAnim->setDuration(350);
    jumpUpAnim->start();
    connect(jumpUpAnim, &QPropertyAnimation::finished, [this](){
        this->fall();
    });
}

void AthletePart::fall()
{
    jumpDownAnim->setStartValue(y());
    jumpDownAnim->setEndValue(y() + jumpHeight);
    jumpDownAnim->setEasingCurve(QEasingCurve::InQuad);
    jumpDownAnim->setDuration(350);
    jumpDownAnim->start();
    connect(jumpDownAnim, &QPropertyAnimation::finished, [this](){
        this->_isJumping = false;
    });
}

qreal AthletePart::y() const
{
    return _y;
}

QPropertyAnimation *AthletePart::getJumpUpAnim() const
{
    return jumpUpAnim;
}

QPropertyAnimation *AthletePart::getJumpDownAnim() const
{
    return jumpDownAnim;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ObstaclePart::ObstaclePart(int obstacleSpeed, QGraphicsItem *parent)
{
    QPixmap pixmap(":/athletegame/resources/athletegame/hurdle.png");
    setPixmap(pixmap.scaled(obstacleSize, Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ObstaclePart::onMove);
    timer->start(obstacleSpeed);

}

void ObstaclePart::onMove()
{
    setPos(x()-5,y());

    // collidingItems() contains a list of pointers to all items the alien, is colliding with
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    for(auto const item : lstCollidingItem){
        if(dynamic_cast<AthletePart*>(item)){
            scene()->removeItem(this);
            emit sigDecreaseHealth();
            delete this;
            break;

        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CoinPart::CoinPart(int coinSpeed,QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPos(x(),y());
    QPixmap pixmap(":/athletegame/resources/athletegame/coin.png");
    setPixmap(pixmap.scaled(50,50,Qt::KeepAspectRatio));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CoinPart::onMove);
    timer->start(coinSpeed);
}

void CoinPart::onMove()
{
    setPos(x()-5,y());
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    for(auto const item : lstCollidingItem){
        AthletePart* athlete = dynamic_cast<AthletePart*>(item);
        if (athlete != nullptr) {
            scene()->removeItem(this);

            emit sigIncreaseScore();
            delete this;
            return;
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
