#include "purchase.h"
#include "ui_purchase.h"


//TODO: linked list qvector helyett, hogy mikor rányomsz a gombra akk a prev v a next kelljen
Purchase::Purchase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Purchase)
{
    ui->setupUi(this);
    QDirIterator itc(":/purchase/collectibles/resources/purchase/", QDirIterator::Subdirectories);
    while (itc.hasNext()) {
        QString fileName =  itc.next();
        Purchase::Thingy newthingy;
        newthingy.name = fileName;
        if(newthingy.name == ":/purchase/collectibles/resources/purchase/expensiveCar.png"){
            newthingy.price = 200000;
        } else if(newthingy.name == ":/purchase/collectibles/resources/purchase/normalCar.png"){
            newthingy.price = 50000;
        } else if(newthingy.name == ":/purchase/collectibles/resources/purchase/cheapCar.png"){
            newthingy.price = 30000;
        } else if(newthingy.name == ":/purchase/collectibles/resources/purchase/expensiveHouse.png"){
            newthingy.price = 500000;
        } else if(newthingy.name == ":/purchase/collectibles/resources/purchase/normalHouse.png"){
            newthingy.price = 300000;
        } else if(newthingy.name == ":/purchase/collectibles/resources/purchase/cheapHouse.png"){
            newthingy.price = 75000;
        }
        collectibles.push_back(newthingy);

    }

    QDirIterator itf(":/purchase/needs/resources/purchase/", QDirIterator::Subdirectories);
    while (itf.hasNext()) {
        QString fileName =  itf.next();
        Purchase::Thingy newthingy;
        newthingy.name = fileName;
        if(newthingy.name == ":/purchase/needs/resources/purchase/fastfood.png"){
            newthingy.price = 4000;
        } else if(newthingy.name == ":/purchase/needs/resources/purchase/fruits.png"){
            newthingy.price = 10000;
        } else if(newthingy.name == ":/purchase/needs/resources/purchase/pancakes.png"){
            newthingy.price = 3000;
        } else if(newthingy.name == ":/purchase/needs/resources/purchase/pizza.png"){
            newthingy.price = 5000;
        } else if(newthingy.name == ":/purchase/needs/resources/purchase/prime.png"){
            newthingy.price = 20000;
        }
        else if(newthingy.name == ":/purchase/needs/resources/purchase/sushi.png"){
            newthingy.price = 6000;
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
                QPixmap pixmap(collectibles.at(j).name);
                label->setPixmap(pixmap.scaled(300,300));
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
                QPixmap pixmap(needs.at(j).name);
                label->setPixmap(pixmap.scaled(300,300));
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

void Purchase::handleClick()
{
    QPushButton* sender = dynamic_cast<QPushButton*>(QObject::sender());
    for(int i = 0; i < collectibles.size(); i++){
        if(collectibles.at(i).price == sender->text().toInt()){
            qDebug() << "asd+" + collectibles.at(i).name;
            emit sigBoughtItem(collectibles.at(i).name,collectibles.at(i).price);
        }
    }

    for(int i = 0; i < needs.size(); i++){
        if(needs.at(i).price == sender->text().toInt()){
            emit sigBoughtItem(needs.at(i).name,needs.at(i).price);
        }
    }
}

void Purchase::on_collectiblesLeftButton_clicked()
{
    QLayoutItem *item = ui->collectiblesLayout->itemAtPosition(1,2);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    int i = 0;
    while(i < collectibles.size() && collectibles.at(i).price != lastPrice){
        i++;
    }
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
        QPixmap pixmapThree(collectibles.at(0).name);
        picThree->setPixmap(pixmapThree.scaled(300,300));
        priceThree->setText(QString::number(collectibles.at(0).price));
    } else{
        priceThree->setText(QString::number(collectibles.at(i+1).price));
        QPixmap pixmapThree(collectibles.at(i+1).name);
        picThree->setPixmap(pixmapThree.scaled(300,300));
    }
}

void Purchase::on_collectiblesRightButton_clicked()
{
    QLayoutItem *item = ui->collectiblesLayout->itemAtPosition(1,0);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    int i = 0;
    while(i < collectibles.size() && collectibles.at(i).price != lastPrice){
        i++;
    }

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
        QPixmap pixmapOne(collectibles.at(collectibles.size()-1).name);
        picOne->setPixmap(pixmapOne.scaled(300,300));
        priceOne->setText(QString::number(collectibles.at(collectibles.size()-1).price));
    } else{
        priceOne->setText(QString::number(collectibles.at(i-1).price));
        QPixmap pixmapOne(collectibles.at(i-1).name);
        picOne->setPixmap(pixmapOne.scaled(300,300));
    }
}

void Purchase::on_needsLeftButton_clicked()
{
    QLayoutItem *item = ui->needsLayout->itemAtPosition(1,2);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    int i = 0;
    while(i < needs.size() && needs.at(i).price != lastPrice){
        i++;
    }
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
        QPixmap pixmapThree(needs.at(0).name);
        picThree->setPixmap(pixmapThree.scaled(300,300));
        priceThree->setText(QString::number(needs.at(0).price));
    } else{
        priceThree->setText(QString::number(needs.at(i+1).price));
        QPixmap pixmapThree(needs.at(i+1).name);
        picThree->setPixmap(pixmapThree.scaled(300,300));
    }
}

void Purchase::on_needsRightButton_clicked()
{
    QLayoutItem *item = ui->needsLayout->itemAtPosition(1,0);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    int lastPrice =  button->text().toInt();
    int i = 0;
    while(i < needs.size() && needs.at(i).price != lastPrice){
        i++;
    }
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
        QPixmap pixmapOne(needs.at(needs.size()-1).name);
        picOne->setPixmap(pixmapOne.scaled(300,300));
        priceOne->setText(QString::number(needs.at(needs.size()-1).price));
    } else{
        priceOne->setText(QString::number(needs.at(i-1).price));
        QPixmap pixmapOne(needs.at(i-1).name);
        picOne->setPixmap(pixmapOne.scaled(300,300));
    }
}

void Purchase::on_helpButton_clicked()
{
    QMessageBox msg;
    QString details =
        "Pancakes: 1 health, 2 needs\nFast Food: 1 health, 4 needs\nPizza: 2 health 6 needs\nFruits: 5 health 3 needs\n"
        "Sushi: 5 health 5 needs\nPrime: 15 health 7 needs";
    msg.setText(details);
    msg.exec();
}

