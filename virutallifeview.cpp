#include "virutallifeview.h"
#include "ui_virutallifeview.h"

VirutalLifeView::VirutalLifeView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VirutalLifeView)
{
    ui->setupUi(this);
    model = new VirtualLifeModel();
    updatePlayer();
}

VirutalLifeView::~VirutalLifeView()
{
    delete ui;
}

void VirutalLifeView::updatePlayer()
{
    ui->healthval->setText(QString::number(model->getCharacter()->getHealth()));
    ui->intelligenceval->setText(QString::number(model->getCharacter()->getIntelligence()));
    ui->moodval->setText(QString::number(model->getCharacter()->getMood()));
    ui->ageval->setText(QString::number(model->getCharacter()->getAge()));
    ui->wealthval->setText(QString::number(model->getCharacter()->getWealth()));
    ui->nameval->setText(model->getCharacter()->getName());
    ui->stageval->setText(model->getCharacter()->getStage());
    ui->genderval->setText(model->getCharacter()->getGender());
}

void VirutalLifeView::on__start_clicked()
{
    initialData = new InitialData();
    initialData->show();
    initialData->exec();
    QString name = initialData->getSelectedName();
    model->getCharacter()->setName(name);
    QString gender = initialData->getSelectedGender();
    model->getCharacter()->setGender(gender);
    updatePlayer();
    ui->_start->hide();
    ui->_actions->setEnabled(true);
    ui->_age->setEnabled(true);
    ui->_assets->setEnabled(true);
    ui->_details->setEnabled(true);
    ui->_loadgame->setEnabled(true);
    ui->_relationships->setEnabled(true);
    ui->_savegame->setEnabled(true);

}


void VirutalLifeView::on__age_clicked()
{
    model->getCharacter()->setAge(model->getCharacter()->getAge()+1);
    updatePlayer();
}

