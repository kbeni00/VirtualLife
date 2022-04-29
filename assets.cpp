#include "assets.h"
#include "ui_assets.h"

Assets::Assets(QVector<QString> items, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Assets)
{
    ui->setupUi(this);
    for(QString item : items){
        qDebug() << item;
        QLabel *img = new QLabel();
        img->setPixmap(QPixmap(item).scaled(300,300));
        if(item.contains("Car")){
            ui->carsLayout->addWidget(img);
        } else if(item.contains("House")){
            ui->housesLayout->addWidget(img);
        }

    }
}

Assets::~Assets()
{
    delete ui;
}
