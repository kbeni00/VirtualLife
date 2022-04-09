#include "virtuallifeview.h"
#include "ui_virtuallifeview.h"
#include "QMessageBox"
#include <QJsonObject>
#include <QJsonArray>
#include <QInputDialog>
#include <QDir>

//TODO: egyszer beolvansi a neveket egy tömbbe és utána onnan kiszedni a neveket, nem a fájlból olvasni mindig

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

void VirtualLifeView::changeStage(){
    QString stage;
    if(model->getCurrentCharacter()->getAge() >= 50){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/elderman.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/elderwoman.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        stage = "Elder";
    }
    else if(model->getCurrentCharacter()->getAge() >= 20){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/adultmale.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/adultfemale.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        stage = "Adult";

    }
    else if(model->getCurrentCharacter()->getAge() >= 13){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/teenageboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/teenagegirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        stage = "Teenage";

    }
    else if(model->getCurrentCharacter()->getAge() >= 6){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/childboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/childgirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        stage = "Child";

    }
    else{
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/babyboy.png").scaled(830,500,Qt::KeepAspectRatio));
            //update stage
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/babygirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        stage = "Baby";
    }
    model->getCurrentCharacter()->setStage(stage);
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

bool VirtualLifeView::on__start_clicked()
{
    QVector<QString> names = model->getNamesInDatabase();
    initialData = new InitialData();
    initialData->show();
    int dialogCode = initialData->exec();
    if(dialogCode == QDialog::Accepted){
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
        } else if(names.contains(initialData->getSelectedName())){
            msg.setText("A character with that name already exists!");
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
            for(int i = 0; i < ui->verticalLayout_2->count(); i++){
                QPushButton * button = qobject_cast<QPushButton*>(ui->verticalLayout_2->itemAt(i)->widget());
                if(button){
                    button->setEnabled(true);
                } else{
                    qWarning() << "PushButton cannot be set to enabled.";
                }
            }
            if(model->getCurrentCharacter()->getGender() == "Male"){
                ui->presetimage->setPixmap(QPixmap(":/characterImages/babyboy.png").scaled(830,500,Qt::KeepAspectRatio));
            } else{
                ui->presetimage->setPixmap(QPixmap(":/characterImages/babygirl.png").scaled(830,500,Qt::KeepAspectRatio));

            }
            return true;
        }
    } else{
        QMessageBox msg;
        msg.setText("You need to click on OK if you want to create a character!");
        msg.exec();
    }
    return false;


}

void VirtualLifeView::on__age_clicked()
{
    model->getCurrentCharacter()->setAge(model->getCurrentCharacter()->getAge()+1);
    updateCharacter();
    changeStage();
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
    connect(model, &VirtualLifeModel::sigReadError, this, &VirtualLifeView::handleReadError);
    bool ok;
    QString name = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Character name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    QVector<QString> names = model->getNamesInDatabase();
    if(names.contains(name)){
        if (ok && !name.isEmpty() && model->loadGame(name)){
            updateCharacter();
            changeStage();
        }
    } else{
        for(Character* character : model->getCharacters()){
            if(character->getName() == name){
                model->setCurrentCharacter(character);
                ui->healthval->setText(QString::number(character->getHealth()));
                ui->intelligenceval->setText(QString::number(character->getIntelligence()));
                ui->moodval->setText(QString::number(character->getMood()));
                ui->ageval->setText(QString::number(character->getAge()));
                ui->wealthval->setText(QString::number(character->getWealth()));
                ui->nameval->setText(character->getName());
                ui->stageval->setText(character->getStage());
                ui->genderval->setText(character->getGender());
                changeStage();
            }
        }
    }
}

void VirtualLifeView::on__newcharacter_clicked()
{
    initialData = new InitialData();
    initialData->show();
    int dialogCode = initialData->exec();
    if(dialogCode == QDialog::Accepted){
        bool isValidName = initialData->getSelectedName() != "";
        bool isValidGender = initialData->getSelectedGender() != "Choose";
        bool nameAlreadyExists = false;
        int i = 0;
        while(i < model->getCharacters().size() && !nameAlreadyExists){
            nameAlreadyExists = model->getCharacters().at(i)->getName() == initialData->getSelectedName();
            i++;
        }
        QVector<QString> names = model->getNamesInDatabase();
        nameAlreadyExists = names.contains(initialData->getSelectedName()) && !nameAlreadyExists;
        QMessageBox msg;
        if(!isValidName){
            msg.setText("Please enter a valid name!");
            msg.exec();
            initialData->close();
        } else if(!isValidGender){
            msg.setText("Please choose a valid gender (either Male or Female)!");
            msg.exec();
            initialData->close();
        } else if( nameAlreadyExists){
            msg.setText("A character with that name already exists!");
            msg.exec();
            initialData->close();
        } else{
            QString name = initialData->getSelectedName();
            QString gender = initialData->getSelectedGender();
            model->newGame();
            model->getCurrentCharacter()->setName(name);
            model->getCurrentCharacter()->setGender(gender);
            model->initializeData();
            updateCharacter();
            changeStage();
        }
    } else{
        QMessageBox msg;
        msg.setText("You need to click on OK if you want to create a character!");
        msg.exec();
    }
}

void VirtualLifeView::handleReadError()
{
    QMessageBox msg;
    QString details = "The specified name cannot be found in the database.";
    msg.setText(details);
    msg.exec();
}

void VirtualLifeView::on__characters_clicked()
{
    QMessageBox msg;
    QString details = "Unsaved characters: \n";
    for(int i = 0; i < model->getCharacters().size(); i++){
        details += model->getCharacters().at(i)->getName() + "\n";
    }
    details += "Saved characters:\n";
    for(Character* character : model->getSavedCharacters()){
        details += character->getName() + "\n";
    }
    msg.setText(details);
    msg.exec();
}

