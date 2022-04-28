#include "achievements.h"
#include "ui_achievements.h"
#include <QtAlgorithms>

Achievements::Achievements(Character* character, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Achievements)
{
    ui->setupUi(this);

    if(character->getHasCar()){
        ui->firstCar->setPixmap(QPixmap(":/achievements/resources/achievements/carAchievement.png"));
    }
    if(character->getHasHouse()){
        ui->firstHouse->setPixmap(QPixmap(":/achievements/resources/achievements/houseAchievement.png"));
    }
    if(character->getIntelligence() >= 150){
        ui->highIntelligence->setPixmap(QPixmap(":/achievements/resources/achievements/intelligenceAchievement.png"));
    }
    if(character->getMood() >= 150){
        ui->highMood->setPixmap(QPixmap(":/achievements/resources/achievements/needsAchievement.png"));
    }
    if(character->getWealth() >= 100000){
        ui->highWealth->setPixmap(QPixmap(":/achievements/resources/achievements/wealthAchievement.png"));
    }

    for(bool res : character->getEasyGamesPlayed()){
        qDebug() << res;
    }

//    bool hasAllCollectibles = false;


//    if(hasAllCars && hasAllHouses){
//        ui->allCollectibles->setPixmap(QPixmap(":/achievements/resources/achievements/collectiblesAchievement.png"));
//    }
    if(character->getFoodsTried() == 6){
        ui->allFoods->setPixmap(QPixmap(":/achievements/resources/achievements/foodAchievement.png"));
    }
    if(!character->getEasyGamesPlayed().contains(false)){
        ui->allEasy->setPixmap(QPixmap(":/achievements/resources/achievements/easyAchievement.png"));
    }
    if(!character->getMediumGamesPlayed().contains(false)){
        ui->allMedium->setPixmap(QPixmap(":/achievements/resources/achievements/mediumAchievement.png"));
    }
    if(!character->getHardGamesPlayed().contains(false)){
        ui->allHard->setPixmap(QPixmap(":/achievements/resources/achievements/hardAchievement.png"));
    }
    //fix model so it cant go past 100
    if(character->getHealth() == 100 && character->getNeeds() == 100){
        ui->maxNeeds->setPixmap(QPixmap(":/achievements/resources/achievements/healthAchievement.png"));
    }

}

Achievements::~Achievements()
{
    delete ui;
}
