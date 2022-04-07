#include "virtuallifeview.h"
#include "ui_virtuallifeview.h"
#include "QMessageBox"
#include <QJsonObject>
#include <QJsonArray>

VirtualLifeView::VirtualLifeView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VirtualLifeView)
{
    ui->setupUi(this);
    model = new VirtualLifeModel();
}

VirtualLifeView::~VirtualLifeView()
{
    delete ui;
}

void VirtualLifeView::changeImage(){
    if(model->getCurrentCharacter()->getAge() >= 50){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/elderman.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/elderwoman.png").scaled(830,500,Qt::KeepAspectRatio));
        }
    }
    else if(model->getCurrentCharacter()->getAge() >= 20){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/adultmale.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/adultfemale.png").scaled(830,500,Qt::KeepAspectRatio));
        }

    }
    else if(model->getCurrentCharacter()->getAge() >= 13){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/teenageboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/teenagegirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
    }
    else if(model->getCurrentCharacter()->getAge() >= 6){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/childboy.png").scaled(830,500,Qt::KeepAspectRatio));
            //update stage
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/childgirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }

    }
}

void VirtualLifeView::updateCharacter()
{
    ui->healthval->setText(QString::number(model->getCurrentCharacter()->getHealth()));
    ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
    ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
    ui->ageval->setText(QString::number(model->getCurrentCharacter()->getAge()));
    ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
    ui->nameval->setText(model->getCurrentCharacter()->getName());
    ui->stageval->setText(model->getCurrentCharacter()->getStage());
    ui->genderval->setText(model->getCurrentCharacter()->getGender());
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
        QString gender = initialData->getSelectedGender();
        model->getCurrentCharacter()->setName(name);
        model->getCurrentCharacter()->setGender(gender);
        model->initializeData();
        updateCharacter();
        ui->_start->hide();
        ui->_actions->setEnabled(true);
        ui->_age->setEnabled(true);
        ui->_assets->setEnabled(true);
        ui->_details->setEnabled(true);
        ui->_loadgame->setEnabled(true);
        ui->_relationships->setEnabled(true);
        ui->_savegame->setEnabled(true);
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/babyboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/babygirl.png").scaled(830,500,Qt::KeepAspectRatio));

        }
    }

}

void VirtualLifeView::on__age_clicked()
{
    model->getCurrentCharacter()->setAge(model->getCurrentCharacter()->getAge()+1);
    updateCharacter();
    changeImage();
}

//!!!!!!!!!!!!!!!!!!!!!!!!! messagebox formok helyett???, v miért crashel a form !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, mi az a QAction(s)
void VirtualLifeView::on__details_clicked()
{
    QMessageBox msg;
    QString details =
            " Name: " + model->getCurrentCharacter()->getName() +
            "\n Gender: " + model->getCurrentCharacter()->getGender() +
            "\n Stage: " + model->getCurrentCharacter()->getStage() +
            "\n Age: " + QString::number(model->getCurrentCharacter()->getAge()) +
            "\n Mood: " + QString::number(model->getCurrentCharacter()->getMood()) +
            "\n Intelligence: " + QString::number(model->getCurrentCharacter()->getIntelligence()) +
            "\n Health: " + QString::number(model->getCurrentCharacter()->getHealth()) +
            "\n Wealth: " + QString::number(model->getCurrentCharacter()->getWealth());
    msg.setText(details);
    msg.exec();
}


void VirtualLifeView::on__actions_clicked()
{
    actions = new Actions();
    actions->show();
    actions->exec();
    connect(actions, &Actions::sigSpaceInvadersEnd, this, &VirtualLifeView::handleSpaceInvadersEnd);
    connect(actions, &Actions::sigMemoryEnd, this, &VirtualLifeView::handleMemoryEnd);
    updateCharacter();
}


void VirtualLifeView::on__relationships_clicked()
{
    relationships = new Relationships();
    relationships->show();
    relationships->exec();
}


void VirtualLifeView::on__assets_clicked()
{
    assets = new Assets();
    assets->show();
    assets->exec();
}

void VirtualLifeView::handleSpaceInvadersEnd(bool wonGame)
{
    if(wonGame){
        model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
        ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
    }
}

void VirtualLifeView::handleMemoryEnd()
{
    model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
    ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
}

void VirtualLifeView::handlePoliceJobEnd(bool wonGame)
{
    if(wonGame){
        model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
        ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
    }
}


void VirtualLifeView::on__savegame_clicked()
{
    model->saveGame();
}


void VirtualLifeView::on__loadgame_clicked()
{
    model->loadGame();
    for(int i = 0; i < model->getCharacters().size(); i++){
        qDebug() << model->getCharacters().at(i)->getName();
    }
    qDebug() << model->getCurrentCharacter()->getName();
    updateCharacter();
    qDebug() << model->getCurrentCharacter()->getAge();
    changeImage();
}
