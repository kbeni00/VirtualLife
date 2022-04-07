#include "policejobparts.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QVector>

PoliceCarPart::PoliceCarPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/policejob/policecar.png");
    setPixmap(pixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RobberCarPart::RobberCarPart(QGraphicsItem *parent)
{
    int value = QRandomGenerator::global()->bounded(100);
    if(value > 50){
        QPixmap pixmap(":/policejob/robbercar1.png");
        setPixmap(pixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
    } else{
        QPixmap pixmap(":/policejob/robbercar2.png");
        setPixmap(pixmap.scaled(QSize(100,100), Qt::KeepAspectRatio));
    }
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RobberCarPart::onMove);
    timer->start(1);

}

void RobberCarPart::onMove()
{
//    QList<QPoint> endPositions {(50,50),(50,1000),(1850,50),(1850,1000)};
    const QVector<int> xEndPositions {50,1850};
    const QVector<int> yEndPositions {50,1000};
//    double xEndPosition = xEndPositions.at(QRandomGenerator::global()->bounded(xEndPositions.size()));
//    double yEndPosition = yEndPositions.at(QRandomGenerator::global()->bounded(yEndPositions.size()));
    double xEndPosition = 1850;
    double yEndPosition = 50;
    qDebug() << xEndPositions << yEndPositions << QRandomGenerator::global()->bounded(xEndPositions.size()) << QRandomGenerator::global()->bounded(yEndPositions.size());

    setPos(x() * (1.0 - 0.0001) + xEndPosition * 0.0001, y() * (1.0 - 0.0001) + yEndPosition * 0.0001);
    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

    bool gameRunning = true;

    for(auto const item : lstCollidingItem){
        PoliceCarPart* policeCar = dynamic_cast<PoliceCarPart*>(item);
        if(policeCar != nullptr){
            scene()->removeItem(this);

            emit sigIncreaseScore();

            delete this;
            return;
        }
    }

    if(gameRunning){
        if(pos().y() >= (scene()->height() - gPoliceCarSize.height())){
            scene()->removeItem(this);
            emit sigDecreaseHealth();
            delete this;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//BulletPart::BulletPart(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
//{
//    QPixmap pixmap(":/spaceinvaders/RedBullet.png");
//    setPixmap(pixmap.scaled(QSize(40,40), Qt::KeepAspectRatio));
//    QTimer* timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &BulletPart::onMove);
//    timer->start(gBulletSpeed);
//}

//void BulletPart::onMove()
//{
//    QList<QGraphicsItem*> lstCollidingItem = collidingItems();

//    for(auto const item : lstCollidingItem){
//        AlienPart* alien = dynamic_cast<AlienPart*>(item);
//        if (alien != nullptr) {
//            scene()->removeItem(alien);
//            scene()->removeItem(this);

//            emit sigIncreaseScore();

//            delete alien;
//            delete this;
//            return;
//        }
//    }
//    setPos(x(),y() - 10);

//    if(pos().y() < 0){
//        scene()->removeItem(this);
//        emit sigDecreaseScore();
//        delete this;
//    }
//}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////


TextPart::TextPart(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    updateMetrics(_nHealth,_nScore);
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 24));
}

void TextPart::updateMetrics(int health, int score)
{
    setPlainText(QString("Health : ") + QString::number(health) + "\n"
                 + QString("Score: ") + QString::number(score)
                 + QString("/") + QString::number(gMaxScore));
}


void TextPart::increaseScore()
{
    _nScore += 1;
    updateMetrics(_nHealth,_nScore);
}

void TextPart::decreaseScore()
{
    _nScore -= 1;
    updateMetrics(_nHealth,_nScore);
}

void TextPart::decreaseHealth()
{
    _nHealth--;
    updateMetrics(_nHealth,_nScore);
}

int TextPart::getHealth() const
{
    return _nHealth;
}

int TextPart::getScore() const
{
    return _nScore;
}

void TextPart::reset()
{
    _nScore = 0;
    _nHealth = gCarHealth;
}
