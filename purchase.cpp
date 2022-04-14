#include "purchase.h"
#include "ui_purchase.h"
#include <QString>
#include <QDirIterator>
#include <QPushButton>
#include <QLayoutItem>

//TODO: form layout, ahol eleve van 6 label (3 cucc és 3 ár), csinűlsz structot, amiben van egy string, egy int, mindegyik resource imageből csinálsz egy structot,
//amiben a Qstring a file name, az int pedig az ár, QVectorban structot tárolsz, betöltöt az első 3-at.
//TODO: linked list qvector helyett, hogy mikor rányomsz a gombra akk a prev v a next kelljen
Purchase::Purchase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Purchase)
{
    ui->setupUi(this);
    QDirIterator itc(":/purchase/collectibles", QDirIterator::Subdirectories);
    while (itc.hasNext()) {
        QString fileName =  itc.next();
        int pos = fileName.lastIndexOf(QChar('/')) + 1;
        Purchase::Thingy newthingy;
        newthingy.name = fileName.remove(0,pos);
        if(newthingy.name == "expensiveCar.png"){
            newthingy.price = 200000;
        } else if(newthingy.name == "normalCar.png"){
            newthingy.price = 50000;
        } else if(newthingy.name == "cheapCar.png"){
            newthingy.price = 10000;
        } else if(newthingy.name == "expensiveHouse.png"){
            newthingy.price = 500000;
        } else if(newthingy.name == "normalHouse.png"){
            newthingy.price = 100000;
        } else if(newthingy.name == "cheapHouse.png"){
            newthingy.price = 75000;
        }
        collectibles.push_back(newthingy);

    }

    QDirIterator itf(":/purchase/needs", QDirIterator::Subdirectories);
    while (itf.hasNext()) {
        QString fileName =  itf.next();
        int pos = fileName.lastIndexOf(QChar('/')) + 1;
        Purchase::Thingy newthingy;
        newthingy.name = fileName.remove(0,pos);
        if(newthingy.name == "fastfood.png"){
            newthingy.price = 5000;
        } else if(newthingy.name == "fruits.png"){
            newthingy.price = 10000;
        } else if(newthingy.name == "pancakes.png"){
            newthingy.price = 3000;
        } else if(newthingy.name == "pizza.png"){
            newthingy.price = 6500;
        } else if(newthingy.name == "prime.png"){
            //fills needs completely
            newthingy.price = 50000;
        }
        else if(newthingy.name == "sushi.png"){
            //fills needs completely
            newthingy.price = 4000;
        }
        needs.push_back(newthingy);
    }

    for(int i = 0; i < ui->collectiblesLayout->rowCount(); i++){
        for(int j = 0; j < ui->collectiblesLayout->columnCount(); j++){
            QLayoutItem *item = ui->collectiblesLayout->itemAtPosition(i,j);
            if(!item || !item->widget()){
                continue;
            }
            if(i == 0){
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                QPixmap pixmap(":/purchase/collectibles/" + collectibles.at(j).name);
                label->setPixmap(pixmap.scaled(100,100));
            } else{
                QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                button->setText(QString::number(collectibles.at(j).price));
                connect(button,&QPushButton::clicked,this,&Purchase::handleClick);
            }
        }

    }

    for(int i = 0; i < ui->needsLayout->rowCount(); i++){
        for(int j = 0; j < ui->needsLayout->columnCount(); j++){
            QLayoutItem *item = ui->needsLayout->itemAtPosition(i,j);
            if(!item || !item->widget()){
                continue;
            }
            if(i == 0){
                QLabel* label = qobject_cast<QLabel*>(item->widget());
                QPixmap pixmap(":/purchase/needs/" + needs.at(j).name);
                label->setPixmap(pixmap.scaled(100,100));
            } else{
                QPushButton* button = qobject_cast<QPushButton*>(item->widget());
                button->setText(QString::number(needs.at(j).price));
                connect(button,&QPushButton::clicked,this,&Purchase::handleClick);

            }
        }

    }
}

Purchase::~Purchase()
{
    delete ui;
}

void Purchase::on_collectiblesLeftButton_clicked()
{
    QLayoutItem *item = ui->collectiblesLayout->itemAtPosition(1,2);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    for(int i = 0; i < collectibles.size(); i++){
        if(collectibles.at(i).price == lastPrice){
            QLayoutItem *itemOne = ui->collectiblesLayout->itemAtPosition(1,0);
            QPushButton* priceOne = qobject_cast<QPushButton*>(itemOne->widget());
            QLayoutItem *itemTwo = ui->collectiblesLayout->itemAtPosition(1,1);
            QPushButton* priceTwo = qobject_cast<QPushButton*>(itemTwo->widget());
            QLayoutItem *itemThree = ui->collectiblesLayout->itemAtPosition(1,2);
            QPushButton* priceThree = qobject_cast<QPushButton*>(itemThree->widget());
            QLayoutItem *itemFour = ui->collectiblesLayout->itemAtPosition(0,0);
            QLabel* picOne = qobject_cast<QLabel*>(itemFour->widget());
            QLayoutItem *itemFive = ui->collectiblesLayout->itemAtPosition(0,1);
            QLabel* picTwo = qobject_cast<QLabel*>(itemFive->widget());
            QLayoutItem *itemSix = ui->collectiblesLayout->itemAtPosition(0,2);
            QLabel* picThree = qobject_cast<QLabel*>(itemSix->widget());

            priceOne->setText(priceTwo->text());
            picOne->setPixmap(picTwo->pixmap());
            priceTwo->setText(priceThree->text());
            picTwo->setPixmap(picThree->pixmap());
            if(i == collectibles.size()-1){
                QPixmap pixmapThree(":/purchase/collectibles/" + collectibles.at(0).name);
                picThree->setPixmap(pixmapThree.scaled(100,100));
                priceThree->setText(QString::number(collectibles.at(0).price));
            } else{
                priceThree->setText(QString::number(collectibles.at(i+1).price));
                QPixmap pixmapThree(":/purchase/collectibles/" + collectibles.at(i+1).name);
                picThree->setPixmap(pixmapThree.scaled(100,100));
            }


        }
    }
}

void Purchase::handleClick()
{
    QPushButton* sender = dynamic_cast<QPushButton*>(QObject::sender());
    for(int i = 0; i < collectibles.size(); i++){
        if(collectibles.at(i).price == sender->text().toInt()){
            emit sigBoughtItem(collectibles.at(i).name,collectibles.at(i).price);
            qDebug() << "asdasd0";
        }
    }

    for(int i = 0; i < needs.size(); i++){
        if(needs.at(i).price == sender->text().toInt()){
            emit sigBoughtItem(needs.at(i).name,needs.at(i).price);
            qDebug() << "asdasdasdasd1";
        }
    }

}

void Purchase::on_collectiblesRightButton_clicked()
{
    QLayoutItem *item = ui->collectiblesLayout->itemAtPosition(1,0);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    for(int i = 0; i < collectibles.size(); i++){
        if(collectibles.at(i).price == lastPrice){
            QLayoutItem *itemOne = ui->collectiblesLayout->itemAtPosition(1,0);
            QPushButton* priceOne = qobject_cast<QPushButton*>(itemOne->widget());
            QLayoutItem *itemTwo = ui->collectiblesLayout->itemAtPosition(1,1);
            QPushButton* priceTwo = qobject_cast<QPushButton*>(itemTwo->widget());
            QLayoutItem *itemThree = ui->collectiblesLayout->itemAtPosition(1,2);
            QPushButton* priceThree = qobject_cast<QPushButton*>(itemThree->widget());
            QLayoutItem *itemFour = ui->collectiblesLayout->itemAtPosition(0,0);
            QLabel* picOne = qobject_cast<QLabel*>(itemFour->widget());
            QLayoutItem *itemFive = ui->collectiblesLayout->itemAtPosition(0,1);
            QLabel* picTwo = qobject_cast<QLabel*>(itemFive->widget());
            QLayoutItem *itemSix = ui->collectiblesLayout->itemAtPosition(0,2);
            QLabel* picThree = qobject_cast<QLabel*>(itemSix->widget());

            priceThree->setText(priceTwo->text());
            picThree->setPixmap(picTwo->pixmap());
            priceTwo->setText(priceOne->text());
            picTwo->setPixmap(picOne->pixmap());
            if(i == 0){
                QPixmap pixmapOne(":/purchase/collectibles/" + collectibles.at(collectibles.size()-1).name);
                picOne->setPixmap(pixmapOne.scaled(100,100));
                priceOne->setText(QString::number(collectibles.at(collectibles.size()-1).price));
            } else{
                priceOne->setText(QString::number(collectibles.at(i-1).price));
                QPixmap pixmapOne(":/purchase/collectibles/" + collectibles.at(i-1).name);
                picOne->setPixmap(pixmapOne.scaled(100,100));
            }
        }
    }

}



void Purchase::on_needsLeftButton_clicked()
{
    QLayoutItem *item = ui->needsLayout->itemAtPosition(1,2);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    for(int i = 0; i < needs.size(); i++){
        if(needs.at(i).price == lastPrice){
            QLayoutItem *itemOne = ui->needsLayout->itemAtPosition(1,0);
            QPushButton* priceOne = qobject_cast<QPushButton*>(itemOne->widget());
            QLayoutItem *itemTwo = ui->needsLayout->itemAtPosition(1,1);
            QPushButton* priceTwo = qobject_cast<QPushButton*>(itemTwo->widget());
            QLayoutItem *itemThree = ui->needsLayout->itemAtPosition(1,2);
            QPushButton* priceThree = qobject_cast<QPushButton*>(itemThree->widget());
            QLayoutItem *itemFour = ui->needsLayout->itemAtPosition(0,0);
            QLabel* picOne = qobject_cast<QLabel*>(itemFour->widget());
            QLayoutItem *itemFive = ui->needsLayout->itemAtPosition(0,1);
            QLabel* picTwo = qobject_cast<QLabel*>(itemFive->widget());
            QLayoutItem *itemSix = ui->needsLayout->itemAtPosition(0,2);
            QLabel* picThree = qobject_cast<QLabel*>(itemSix->widget());

            priceOne->setText(priceTwo->text());
            picOne->setPixmap(picTwo->pixmap());
            priceTwo->setText(priceThree->text());
            picTwo->setPixmap(picThree->pixmap());
            if(i == needs.size()-1){
                QPixmap pixmapThree(":/purchase/needs/" + needs.at(0).name);
                picThree->setPixmap(pixmapThree.scaled(100,100));
                priceThree->setText(QString::number(needs.at(0).price));
            } else{
                priceThree->setText(QString::number(needs.at(i+1).price));
                QPixmap pixmapThree(":/purchase/needs/" + needs.at(i+1).name);
                picThree->setPixmap(pixmapThree.scaled(100,100));
            }
        }
    }
}

void Purchase::on_needsRightButton_clicked()
{
    QLayoutItem *item = ui->needsLayout->itemAtPosition(1,0);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    for(int i = 0; i < needs.size(); i++){
        if(needs.at(i).price == lastPrice){
            QLayoutItem *itemOne = ui->needsLayout->itemAtPosition(1,0);
            QPushButton* priceOne = qobject_cast<QPushButton*>(itemOne->widget());
            QLayoutItem *itemTwo = ui->needsLayout->itemAtPosition(1,1);
            QPushButton* priceTwo = qobject_cast<QPushButton*>(itemTwo->widget());
            QLayoutItem *itemThree = ui->needsLayout->itemAtPosition(1,2);
            QPushButton* priceThree = qobject_cast<QPushButton*>(itemThree->widget());
            QLayoutItem *itemFour = ui->needsLayout->itemAtPosition(0,0);
            QLabel* picOne = qobject_cast<QLabel*>(itemFour->widget());
            QLayoutItem *itemFive = ui->needsLayout->itemAtPosition(0,1);
            QLabel* picTwo = qobject_cast<QLabel*>(itemFive->widget());
            QLayoutItem *itemSix = ui->needsLayout->itemAtPosition(0,2);
            QLabel* picThree = qobject_cast<QLabel*>(itemSix->widget());

            priceThree->setText(priceTwo->text());
            picThree->setPixmap(picTwo->pixmap());
            priceTwo->setText(priceOne->text());
            picTwo->setPixmap(picOne->pixmap());
            if(i == 0){
                QPixmap pixmapOne(":/purchase/needs/" + needs.at(needs.size()-1).name);
                picOne->setPixmap(pixmapOne.scaled(100,100));
                priceOne->setText(QString::number(needs.at(needs.size()-1).price));
            } else{
                priceOne->setText(QString::number(needs.at(i-1).price));
                QPixmap pixmapOne(":/purchase/needs/" + needs.at(i-1).name);
                picOne->setPixmap(pixmapOne.scaled(100,100));
            }
        }
    }
}
