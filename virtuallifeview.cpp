#include "virtuallifeview.h"
#include "ui_virtuallifeview.h"
#include "QMessageBox"

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
        model->getCharacter()->setName(name);
        model->getCharacter()->setGender(gender);
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
        if(model->getCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/babyboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/babygirl.png").scaled(830,500,Qt::KeepAspectRatio));

        }
    }

}

void VirtualLifeView::on__age_clicked()
{
    model->getCharacter()->setAge(model->getCharacter()->getAge()+1);
    updateCharacter();
    if(model->getCharacter()->getAge() == 6){
        if(model->getCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/childboy.png").scaled(830,500,Qt::KeepAspectRatio));
            //update stage
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/childgirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }

    }
    else if(model->getCharacter()->getAge() == 13){
        if(model->getCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/teenageboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/teenagegirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
    }
    else if(model->getCharacter()->getAge() == 20){
        if(model->getCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/adultmale.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/adultfemale.png").scaled(830,500,Qt::KeepAspectRatio));
        }

    }
    else if(model->getCharacter()->getAge() == 50){
        if(model->getCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/elderman.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/elderwoman.png").scaled(830,500,Qt::KeepAspectRatio));
        }
    }
}

//!!!!!!!!!!!!!!!!!!!!!!!!! messagebox formok helyett???, v miért crashel a form !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, mi az a QAction(s)
void VirtualLifeView::on__details_clicked()
{
    QMessageBox msg;
    QString details =
            " Name: " + model->getCharacter()->getName() +
            "\n Gender: " + model->getCharacter()->getGender() +
            "\n Stage: " + model->getCharacter()->getStage() +
            "\n Age: " + QString::number(model->getCharacter()->getAge()) +
            "\n Mood: " + QString::number(model->getCharacter()->getMood()) +
            "\n Intelligence: " + QString::number(model->getCharacter()->getIntelligence()) +
            "\n Health: " + QString::number(model->getCharacter()->getHealth()) +
            "\n Wealth: " + QString::number(model->getCharacter()->getWealth());
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
        model->getCharacter()->setWealth(model->getCharacter()->getWealth() + 10000);
        ui->wealthval->setText(QString::number(model->getCharacter()->getWealth()));
    }
}

void VirtualLifeView::handleMemoryEnd()
{
    model->getCharacter()->setWealth(model->getCharacter()->getWealth() + 10000);
    ui->wealthval->setText(QString::number(model->getCharacter()->getWealth()));
}

