#include "virtuallifeview.h"
#include "ui_virtuallifeview.h"
#include "QMessageBox"

VirtualLifeView::VirtualLifeView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VirtualLifeView)
{
    ui->setupUi(this);
    model = new VirtualLifeModel();
    updateCharacter();
}

VirtualLifeView::~VirtualLifeView()
{
    delete ui;
}

void VirtualLifeView::updateCharacter()
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

void VirtualLifeView::changeImage()
{
//switch case a karakter életkorára, QImage v vmi hasonló privát adattagként
}

void VirtualLifeView::on__start_clicked()
{
    initialData = new InitialData();
    initialData->show();
    initialData->exec();
    bool isValidName = initialData->getSelectedName() != "";
    bool isValidGender = initialData->getSelectedGender() != "Choose";
    QMessageBox msg;
    if(!isValidName){
        msg.setText("Please enter a valid name!");
        msg.exec();
        initialData->close();
    } else if(!isValidGender){
        msg.setText("Please choose a valid gender (either Male or Female)!");
        msg.exec();
        initialData->close();
    } else{
        QString name = initialData->getSelectedName();
        model->getCharacter()->setName(name);
        QString gender = initialData->getSelectedGender();
        model->getCharacter()->setGender(gender);
        updateCharacter();
        ui->_start->hide();
        ui->_actions->setEnabled(true);
        ui->_age->setEnabled(true);
        ui->_assets->setEnabled(true);
        ui->_details->setEnabled(true);
        ui->_loadgame->setEnabled(true);
        ui->_relationships->setEnabled(true);
        ui->_savegame->setEnabled(true);
    }

}

void VirtualLifeView::on__age_clicked()
{
    model->getCharacter()->setAge(model->getCharacter()->getAge()+1);
    updateCharacter();
    changeImage();
    ui->progressBar->setValue(model->getCharacter()->getAge());
}

//!!!!!!!!!!!!!!!!!!!!!!!!! messagebox formok helyett???, v miért crashel a form !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, mi az a QAction(s)
void VirtualLifeView::on__details_clicked()
{
    QMessageBox msg;
    QString details =
            "Name: " + model->getCharacter()->getName() +
            "\n Gender: " + model->getCharacter()->getGender() +
            "\n Age: " + QString::number(model->getCharacter()->getAge()) +
            "\n Mood: " + QString::number(model->getCharacter()->getMood()) +
            "\n Intelligence: " + QString::number(model->getCharacter()->getIntelligence()) +
            "\n Health: " + QString::number(model->getCharacter()->getHealth()) +
            "\n Wealth: " + QString::number(model->getCharacter()->getWealth());
    msg.setText(details);
    msg.exec();
//    details = new Details();
//    details->show();
//    details->exec();

}

