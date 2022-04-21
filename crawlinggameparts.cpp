#include "crawlinggameparts.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QApplication>

BabyPart::BabyPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/crawlinggame/crawlingbaby.png");
    setPixmap(pixmap.scaled(babySize, Qt::KeepAspectRatio));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ToyPart::ToyPart(int toySpeed, QGraphicsItem *parent)
{
    int prob = QRandomGenerator::global()->bounded(101);
    if(prob < 20){
        QPixmap pixmap(":/crawlinggame/shakeyToy.png");
        setPixmap(pixmap.scaled(toySize, Qt::KeepAspectRatio));
    } else if(prob < 40){
        QPixmap pixmap(":/crawlinggame/shapesToy.png");
        setPixmap(pixmap.scaled(toySize, Qt::KeepAspectRatio));
    } else if(prob < 60){
        QPixmap pixmap(":/crawlinggame/stackingToy.png");
        setPixmap(pixmap.scaled(toySize, Qt::KeepAspectRatio));
    } else if(prob < 80){
        QPixmap pixmap(":/crawlinggame/teddyToy.png");
        setPixmap(pixmap.scaled(toySize, Qt::KeepAspectRatio));
    } else{
        QPixmap pixmap(":/crawlinggame/milkBottle.png");
        setPixmap(pixmap.scaled(toySize, Qt::KeepAspectRatio));
        isMilkBottle = true;
    }
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ToyPart::onMove);
    timer->start(1);

}

void ToyPart::onMove()
{
    QScreen *screen = QApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int width = screenGeometry.width();
    if(x() >= width-toySize.width()){
        isMovingRight = false;
    } else if(x() <= 50){
        isMovingRight = true;
    }
    if(isMovingRight){
        setPos(x() + 0.2, y());
    } else{
        setPos(x() - 0.2, y());
    }



    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    bool gameRunning = true;

    for(auto const item : lstCollidingItem){
        BabyPart* baby = dynamic_cast<BabyPart*>(item);
        if(isMilkBottle){
            emit sigCollidedWithMilkBottle();
        }
        if(baby != nullptr){
            scene()->removeItem(this);

            emit sigIncreaseScore();

            delete this;
            return;
        }
    }

    if(gameRunning){
        if(pos().y() >= (scene()->height() - toySize.height())){
            scene()->removeItem(this);
            emit sigDecreaseHealth();
            delete this;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////


CrawlingPointsPart::CrawlingPointsPart(int maxHealth, int scoreToReach, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    _health = maxHealth;
    _scoreToReach = scoreToReach;

    updateMetrics(_health,_score);
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

void CrawlingPointsPart::updateMetrics(int health, int score)
{
    setPlainText(QString("Health : ") + QString::number(health) + "\n"
                 + QString("Score: ") + QString::number(score)
                 + QString("/") + QString::number(_scoreToReach));
}


void CrawlingPointsPart::increaseScore()
{
    _score += 1;
    updateMetrics(_health,_score);
}

void CrawlingPointsPart::decreaseScore()
{
    _score -= 1;
    updateMetrics(_health,_score);
}

void CrawlingPointsPart::decreaseHealth()
{
    _health--;
    updateMetrics(_health,_score);
}

int CrawlingPointsPart::getHealth() const
{
    return _health;
}

int CrawlingPointsPart::getScore() const
{
    return _score;
}

void CrawlingPointsPart::reset()
{
    _score = 0;
    _health = 0;
}
