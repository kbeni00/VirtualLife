#include "details.h"
#include "ui_details.h"
#include "QString"

Details::Details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Details)
{
    ui->setupUi(this);
//    ui->ageval->setText(QString::number(model->getCharacter()->getAge()));
//    ui->intelligenceval->setText(QString::number(model->getCharacter()->getIntelligence()));
//    ui->healthval->setText(QString::number(model->getCharacter()->getHealth()));
//    ui->genderval->setText(model->getCharacter()->getGender());
//    ui->moodval->setText(QString::number(model->getCharacter()->getMood()));
//    ui->nameval->setText(model->getCharacter()->getName());
}

Details::~Details()
{
    delete ui;
}
