#include "virtuallifeview.h"
#include "ui_virtuallifeview.h"
#include "QMessageBox"
#include <QJsonObject>
#include <QJsonArray>
#include <QInputDialog>
#include <QDir>
#include <QRandomGenerator>
#include <QThread>

//TODO: egyszer beolvansi a neveket egy tömbbe és utána onnan kiszedni a neveket, nem a fájlból olvasni mindig

VirtualLifeView::VirtualLifeView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VirtualLifeView)
{
    ui->setupUi(this);
    ui->textBrowser->append("To begin, click on the Start Game button.");
    model = new VirtualLifeModel();
    ui->health->setHidden(true);
    ui->healthval->setHidden(true);
    ui->needs->setHidden(true);
    ui->needsval->setHidden(true);
    initEvents();
}

VirtualLifeView::~VirtualLifeView()
{
    delete ui;
}

void VirtualLifeView::initEvents(){
    allEvents.push_back(*new VirtualLifeView::EventDetails("You broke your arm. You lose 10 health points.", -10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You got electrocuted while messing with the outlet. You lose 15 health points.", -15));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You had an argument with one of your friends. You lose 10 mood points.", -10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You got kidnapped but managed to escape. You lose 30 mood points.", -30));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You fell down the stairs today. You lose 10 health points.", -10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You lost your phone. You lose 10 mood points.", -10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You had an argument with one of your family members at dinner. You lose 5 mood points.",-5));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You got a compliment from a random person on the street. You gain 5 mood points.", 5));
    allEvents.push_back(*new VirtualLifeView::EventDetails("Your crush gave you an ice cream. You gain 10 mood points.", 10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You got a flower from one of your friends. You gain 10 mood points.", 10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You found a four-leaf clover. You gain 5 mood points.", 5));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You got a negative covid test. You gain 20 mood points.", 20));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You saw a double rainbow while walking home. You gain 5 mood points.", 5));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You saw a shooting star. You gain 10 mood points.", 10));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You woke up on the right side of the bed today. You gain 2 mood points.", 5));
    allEvents.push_back(*new VirtualLifeView::EventDetails("Your six pack is starting to show. You gain 5 mood points.", 5));
    allEvents.push_back(*new VirtualLifeView::EventDetails("You got selected for an all expenses paid tour around the world. You gain 50 mood points.", 50));
}

void VirtualLifeView::changeStage(){
    QString stage;
    if(model->getCurrentCharacter()->getAge() >= 25){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/adultmale.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/adultfemale.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        ui->health->setHidden(false);
        ui->healthval->setHidden(false);
        ui->needs->setHidden(false);
        ui->needsval->setHidden(false);
        ui->textBrowser->append("You are now an adult.");

        QMessageBox msg;
        msg.setText("You are an adult! Make sure neither your health nor your needs reach 0, otherwise the it's game over!");
        msg.exec();
        stage = "Adult";

    }
    else if(model->getCurrentCharacter()->getAge() >= 13){
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/teenageboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/teenagegirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        ui->health->setHidden(true);
        ui->healthval->setHidden(true);
        ui->needs->setHidden(true);
        ui->needsval->setHidden(true);
        ui->textBrowser->append("You are now a teenager.");
        stage = "Teenager";

    }
    else{
        if(model->getCurrentCharacter()->getGender() == "Male"){
            ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/babyboy.png").scaled(830,500,Qt::KeepAspectRatio));
        } else{
            ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/babygirl.png").scaled(830,500,Qt::KeepAspectRatio));
        }
        ui->health->setHidden(true);
        ui->healthval->setHidden(true);
        ui->needs->setHidden(true);
        ui->needsval->setHidden(true);
        ui->textBrowser->append("You are a baby. Collect intelligence, mood points with actions to advance to the next stage.");
        stage = "Baby";
    }
    model->getCurrentCharacter()->setStage(stage);
}

void VirtualLifeView::updateCharacter()
{
    ui->healthval->setText(QString::number(model->getCurrentCharacter()->getHealth()));
    ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
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
    initialData->setWindowModality(Qt::ApplicationModal);
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
                ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/babyboy.png").scaled(830,500,Qt::KeepAspectRatio));
            } else{
                ui->presetimage->setPixmap(QPixmap(":/characterImages/resources/characters/babygirl.png").scaled(830,500,Qt::KeepAspectRatio));

            }
            ui->textBrowser->append("The game has started.");

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
    int intelligenceReq;
    int moodReq;
    if(model->getCurrentCharacter()->getStage() == "Baby"){
        intelligenceReq = 50;
        moodReq = 30;
    } else{
        intelligenceReq = 100;
        moodReq = 60;
    }
    if(model->getCurrentCharacter()->getIntelligence() >= intelligenceReq && model->getCurrentCharacter()->getMood() >= moodReq){
        model->getCurrentCharacter()->setAge(model->getCurrentCharacter()->getAge()+13);
    } else{
        QMessageBox msg;

        QString message = "You are not ready to advance to the next stage! You need "
                          + QString::number(intelligenceReq) + " intelligence points and "
                          + QString::number(moodReq) + " mood points to advance.";
        msg.setText(message);
        msg.exec();
    }

    changeStage();
    updateCharacter();
    if(model->getCurrentCharacter()->getStage() == "Adult"){
        ui->_age->setEnabled(false);
    }
}


void VirtualLifeView::on__actions_clicked()
{
    actions = new Actions();
    if(model->getCurrentCharacter()->getStage() == "Baby"){
        actions->addAction("Crawling Game");
        actions->addAction("Memory Card Game");

    } else if(model->getCurrentCharacter()->getStage() == "Teenager"){
        actions->addAction("Memory Card Game");
        actions->addAction("Space Invaders");
        actions->addAction("Whack-A-Mole");

    } else{
        actions->addAction("Memory Card Game");
        actions->addAction("Space Invaders");
        actions->addAction("Whack-A-Mole");
        actions->addAction("Hunting Game");
        actions->addAction("Athlete Game");
        actions->addAction("Buy lottery");
        actions->addAction("Go to a doctor");
    }
    actions->setWindowModality(Qt::ApplicationModal);
    actions->exec();

    connect(actions, &Actions::sigDoctorEnd, this, &VirtualLifeView::handleDoctorEnd);
    connect(actions, &Actions::sigLotteryEnd, this, &VirtualLifeView::handleLotteryEnd);
    connect(actions, &Actions::sigSpaceInvadersEnd, this, &VirtualLifeView::handleSpaceInvadersEnd);
    connect(actions, &Actions::sigMemoryEnd, this, &VirtualLifeView::handleMemoryEnd);
    connect(actions, &Actions::sigHuntingGameEnd, this, &VirtualLifeView::handleHuntingGameEnd);
    connect(actions, &Actions::sigWhackAMoleEnd, this, &VirtualLifeView::handleWhackAMoleEnd);
    connect(actions, &Actions::sigCrawlingGameEnd, this, &VirtualLifeView::handleCrawlingGameEnd);
}


void VirtualLifeView::on__purchase_clicked()
{
    purchase = new Purchase();
    connect(purchase,&Purchase::sigBoughtItem,this,&VirtualLifeView::handleBoughtItem);
    purchase->setWindowModality(Qt::ApplicationModal);
    purchase->exec();

}

void VirtualLifeView::on__assets_clicked()
{
    assets = new Assets(model->getCurrentCharacter()->getAssets());
    assets->show();
    assets->setWindowModality(Qt::ApplicationModal);
    assets->exec();

}

void VirtualLifeView::handleSpaceInvadersEnd(bool wonGame, QString difficulty)
{
    if(wonGame){
        if(model->getCurrentCharacter()->getStage() == "Teenager"){
            if(difficulty == "Easy"){
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
                model->getCurrentCharacter()->increaseEasyGamesPlayed(2);
            } else if(difficulty == "Medium"){
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
                model->getCurrentCharacter()->increaseMediumGamesPlayed(2);
            } else{
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
                model->getCurrentCharacter()->increaseHardGamesPlayed(2);
            }
        } else{
            if(difficulty == "Easy"){
                model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 5000);
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 3);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 3);
                model->getCurrentCharacter()->increaseEasyGamesPlayed(2);
            } else if(difficulty == "Medium"){
                model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
                model->getCurrentCharacter()->increaseMediumGamesPlayed(2);
            } else{
                model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 20000);
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
                model->getCurrentCharacter()->increaseHardGamesPlayed(2);
            }
            model->getCurrentCharacter()->setNeeds(qMax(model->getCurrentCharacter()->getNeeds() - 5,0));
            ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
        }
        ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
        ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
        ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
        ui->textBrowser->append("You won a Space Invaders game on " + difficulty + " difficulty. Your rewards have been added to your character.");

    } else{
        ui->textBrowser->append("You lost a Space Invaders game on " + difficulty + " difficulty.");

    }


    generateRandomEvent();

}

void VirtualLifeView::handleMemoryEnd(QString difficulty)
{
    if(model->getCurrentCharacter()->getStage() == "Baby"){
        if(difficulty == "Easy"){
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
            model->getCurrentCharacter()->increaseEasyGamesPlayed(1);
        } else if(difficulty == "Medium"){
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
            model->getCurrentCharacter()->increaseMediumGamesPlayed(1);
        } else{
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 20);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 20);
            model->getCurrentCharacter()->increaseHardGamesPlayed(1);
        }
    } else if(model->getCurrentCharacter()->getStage() == "Teenager"){
        if(difficulty == "Easy"){
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
            model->getCurrentCharacter()->increaseEasyGamesPlayed(1);
        } else if(difficulty == "Medium"){
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
            model->getCurrentCharacter()->increaseMediumGamesPlayed(1);
        } else{
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
            model->getCurrentCharacter()->increaseHardGamesPlayed(1);
        }
    } else{
        if(difficulty == "Easy"){
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 5000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 3);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 3);
            model->getCurrentCharacter()->increaseEasyGamesPlayed(1);
        } else if(difficulty == "Medium"){
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
            model->getCurrentCharacter()->increaseMediumGamesPlayed(1);
        } else{
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 20000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
            model->getCurrentCharacter()->increaseHardGamesPlayed(1);
        }
        model->getCurrentCharacter()->setNeeds(qMax(model->getCurrentCharacter()->getNeeds() - 5,0));
        ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
    }
    ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
    ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
    ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));

    ui->textBrowser->append("You won a Memory Card game on " + difficulty + " difficulty. Your rewards have been added to your character.");



    generateRandomEvent();
}

void VirtualLifeView::handleHuntingGameEnd(bool wonGame, QString difficulty)
{
    if(wonGame){
        if(difficulty == "Easy"){
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 5000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
            model->getCurrentCharacter()->increaseEasyGamesPlayed(4);
        } else if(difficulty == "Medium"){
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
            model->getCurrentCharacter()->increaseMediumGamesPlayed(4);
        } else{
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 20000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
            model->getCurrentCharacter()->increaseHardGamesPlayed(4);
        }
        ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
        ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
        ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
        ui->textBrowser->append("You won a Hunting Game on " + difficulty + " difficulty. Your rewards have been added to your character.");

    } else{
        ui->textBrowser->append("You lost a Hunting Game on " + difficulty + " difficulty.");

    }
    if(model->getCurrentCharacter()->getStage() == "Adult"){

        model->getCurrentCharacter()->setNeeds(qMax(model->getCurrentCharacter()->getNeeds() - 5,0));
        ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
    }
    generateRandomEvent();

}


void VirtualLifeView::handleWhackAMoleEnd(bool wonGame, QString difficulty)
{
    if(wonGame){
        if(model->getCurrentCharacter()->getStage() == "Teenager"){
            if(difficulty == "Easy"){
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
                model->getCurrentCharacter()->increaseEasyGamesPlayed(3);
            } else if(difficulty == "Medium"){
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
                model->getCurrentCharacter()->increaseMediumGamesPlayed(3);
            } else{
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
                model->getCurrentCharacter()->increaseHardGamesPlayed(3);
            }
        } else{
            if(difficulty == "Easy"){
                model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 5000);
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 3);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 3);
                model->getCurrentCharacter()->increaseEasyGamesPlayed(3);
            } else if(difficulty == "Medium"){
                model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
                model->getCurrentCharacter()->increaseMediumGamesPlayed(3);
            } else{
                model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 20000);
                model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
                model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
                model->getCurrentCharacter()->increaseHardGamesPlayed(3);
            }
            model->getCurrentCharacter()->setNeeds(qMax(model->getCurrentCharacter()->getNeeds() - 5,0));
            ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
        }
        ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
        ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
        ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
        ui->textBrowser->append("You won a Whack-A-Mole game on " + difficulty + " difficulty. Your rewards have been added to your character.");

    } else{
        ui->textBrowser->append("You lost a Whack-A-Mole game on " + difficulty + " difficulty.");

    }
    generateRandomEvent();

}

void VirtualLifeView::handleCrawlingGameEnd(bool wonGame, QString difficulty)
{
    if(wonGame){
        if(difficulty == "Easy"){
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
            model->getCurrentCharacter()->increaseEasyGamesPlayed(0);
        } else if(difficulty == "Medium"){
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
            model->getCurrentCharacter()->increaseMediumGamesPlayed(0);
        } else{
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
            model->getCurrentCharacter()->increaseHardGamesPlayed(0);
        }
        ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
        ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
        ui->textBrowser->append("You won a Crawling Game on " + difficulty + " difficulty. Your rewards have been added to your character.");
    } else{
        ui->textBrowser->append("You lost a Crawling Game on " + difficulty + " difficulty.");

    }
    generateRandomEvent();
}
void VirtualLifeView::handleLotteryEnd(int wonAmount)
{
    model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + wonAmount);
    ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
    ui->textBrowser->append("You won " + QString::number(wonAmount) + " on the lottery.");

    generateRandomEvent();
}

void VirtualLifeView::handleBoughtItem(QString itemName, int itemPrice)
{
    if(itemName.contains("sushi")){
        model->getCurrentCharacter()->setHealth(model->getCurrentCharacter()->getHealth() + 5);
        model->getCurrentCharacter()->setNeeds(model->getCurrentCharacter()->getNeeds() + 5);
        model->getCurrentCharacter()->increaseFoodsTried(1);
    } else if(itemName.contains("pizza")){
        model->getCurrentCharacter()->setHealth(model->getCurrentCharacter()->getHealth() + 2);
        model->getCurrentCharacter()->setNeeds(model->getCurrentCharacter()->getNeeds() + 6);
        model->getCurrentCharacter()->increaseFoodsTried(1);
    } else if(itemName.contains("fruits")){
        model->getCurrentCharacter()->setHealth(model->getCurrentCharacter()->getHealth() + 5);
        model->getCurrentCharacter()->setNeeds(model->getCurrentCharacter()->getNeeds() + 3);
        model->getCurrentCharacter()->increaseFoodsTried(1);
    } else if(itemName.contains("fastfood")){
        model->getCurrentCharacter()->setHealth(model->getCurrentCharacter()->getHealth() + 1);
        model->getCurrentCharacter()->setNeeds(model->getCurrentCharacter()->getNeeds() + 4);
        model->getCurrentCharacter()->increaseFoodsTried(1);
    } else if(itemName.contains("pancakes")){
        model->getCurrentCharacter()->setHealth(model->getCurrentCharacter()->getHealth() + 1);
        model->getCurrentCharacter()->setNeeds(model->getCurrentCharacter()->getNeeds() + 2);
        model->getCurrentCharacter()->increaseFoodsTried(1);
    } else if(itemName.contains("prime")){
        model->getCurrentCharacter()->setHealth(model->getCurrentCharacter()->getHealth() + 15);
        model->getCurrentCharacter()->setNeeds(model->getCurrentCharacter()->getNeeds() + 7);
        model->getCurrentCharacter()->increaseFoodsTried(1);
    }

    int posSlash = itemName.lastIndexOf(QChar('/')) + 1;
    QMessageBox msg;
    QString details;

    if(model->getCurrentCharacter()->getWealth() >= itemPrice){
        model->getCurrentCharacter()->addAsset(itemName);
        itemName.remove(0,posSlash);
        itemName.chop(4);
        model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth()-itemPrice);
        details = "You bought a(n) " + itemName;
        if(itemName.contains("House")){
            model->getCurrentCharacter()->setHasHouse(true);
        } else if(itemName.contains("Car")){
            model->getCurrentCharacter()->setHasCar(true);
        }
    } else{
        itemName.remove(0,posSlash);
        itemName.chop(4);
        details = "You don't have enough money to buy a(n) " + itemName;
    }
    ui->textBrowser->append("You bought a(n) " + itemName + " for " + QString::number(itemPrice));

    msg.setText(details);
    msg.exec();

    updateCharacter();
}

void VirtualLifeView::on__savegame_clicked()
{
    QMessageBox msg;
    QString details = (model->saveGame()) ? "Successfully saved the game!" : "Failed to save the game!";
    msg.setText(details);
    msg.exec();

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
    ui->textBrowser->append("You loaded a new character.");

}

void VirtualLifeView::handleReadError()
{
    QMessageBox msg;
    QString details = "The specified name cannot be found in the database.";
    msg.setText(details);
    msg.exec();
    ui->textBrowser->append("The specified name cannot be found in the database.");

}

void VirtualLifeView::on__newcharacter_clicked()
{
    initialData = new InitialData();
    initialData->setWindowModality(Qt::ApplicationModal);
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
            ui->textBrowser->append("You created a new character.");
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

void VirtualLifeView::generateRandomEvent()
{
    if(allEvents.size() > 0){
        int prob = QRandomGenerator::global()->bounded(101);
        if(prob < 40){
            int index = QRandomGenerator::global()->bounded(allEvents.size());
            QMessageBox msg;
            msg.setText(allEvents.at(index).description);
            msg.exec();
            ui->textBrowser->append(allEvents.at(index).description);

            if(allEvents.at(index).description.contains("health")){
                int newHealth = (model->getCurrentCharacter()->getHealth() + allEvents.at(index).influence > 0) ?
                                    qMax(model->getCurrentCharacter()->getHealth() + allEvents.at(index).influence,0) : 0;
                model->getCurrentCharacter()->setHealth(newHealth);
                ui->healthval->setText(QString::number(model->getCurrentCharacter()->getHealth()));
            } else if(allEvents.at(index).description.contains("needs")){
                int newNeeds = (model->getCurrentCharacter()->getNeeds() + allEvents.at(index).influence > 0) ?
                                   qMax(model->getCurrentCharacter()->getNeeds() + allEvents.at(index).influence,0) : 0;
                model->getCurrentCharacter()->setNeeds(newNeeds);
                ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
            } else if(allEvents.at(index).description.contains("mood")){
                int newMood = (model->getCurrentCharacter()->getMood() + allEvents.at(index).influence > 0) ?
                                  qMax(model->getCurrentCharacter()->getMood() + allEvents.at(index).influence,0) : 0;
                model->getCurrentCharacter()->setMood(newMood);
                ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
            } else if(allEvents.at(index).description.contains("intelligence")){
                int newIntelligence = (model->getCurrentCharacter()->getIntelligence() + allEvents.at(index).influence > 0) ?
                                          qMax(model->getCurrentCharacter()->getIntelligence() + allEvents.at(index).influence,0) : 0;
                model->getCurrentCharacter()->setIntelligence(newIntelligence);
                ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
            }
            allEvents.removeAt(index);
            updateCharacter();
        }
    }
}


void VirtualLifeView::on__achievements_clicked()
{
    achievements = new Achievements(model->getCurrentCharacter());
    achievements->setWindowModality(Qt::ApplicationModal);
    achievements->exec();
}

void VirtualLifeView::handleDoctorEnd(QString selectedDoc)
{
    if(selectedDoc == "GP"){
        model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() - 12000);
        model->getCurrentCharacter()->setHealth(qMin(model->getCurrentCharacter()->getHealth() + 10,100));
    } else if(selectedDoc == "Psychologist"){
        model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() - 20000);
        model->getCurrentCharacter()->setHealth(qMin(model->getCurrentCharacter()->getHealth() + 20,100));

    } else{
        model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() - 35000);
        model->getCurrentCharacter()->setHealth(qMin(model->getCurrentCharacter()->getHealth() + 50,100));
    }
    ui->healthval->setText(QString::number(model->getCurrentCharacter()->getHealth()));
    ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
    ui->textBrowser->append("You went to a " + selectedDoc + ". Your health points have been updated.");
}

void VirtualLifeView::handleAthleteGameEnd(bool wonGame, QString difficulty)
{
    if(wonGame){
        if(difficulty == "Easy"){
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 5000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 5);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 5);
            model->getCurrentCharacter()->increaseEasyGamesPlayed(5);
        } else if(difficulty == "Medium"){
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 10000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 10);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 10);
            model->getCurrentCharacter()->increaseMediumGamesPlayed(5);
        } else{
            model->getCurrentCharacter()->setWealth(model->getCurrentCharacter()->getWealth() + 20000);
            model->getCurrentCharacter()->setIntelligence(model->getCurrentCharacter()->getIntelligence() + 15);
            model->getCurrentCharacter()->setMood(model->getCurrentCharacter()->getMood() + 15);
            model->getCurrentCharacter()->increaseHardGamesPlayed(5);
        }
        ui->wealthval->setText(QString::number(model->getCurrentCharacter()->getWealth()));
        ui->intelligenceval->setText(QString::number(model->getCurrentCharacter()->getIntelligence()));
        ui->moodval->setText(QString::number(model->getCurrentCharacter()->getMood()));
        ui->textBrowser->append("You won a Hunting Game on " + difficulty + " difficulty. Your rewards have been added to your character.");

    } else{
        ui->textBrowser->append("You lost a Hunting Game on " + difficulty + " difficulty.");

    }
    if(model->getCurrentCharacter()->getStage() == "Adult"){

        model->getCurrentCharacter()->setNeeds(qMax(model->getCurrentCharacter()->getNeeds() - 5,0));
        ui->needsval->setText(QString::number(model->getCurrentCharacter()->getNeeds()));
    }
    generateRandomEvent();
}
