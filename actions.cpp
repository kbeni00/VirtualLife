#include "actions.h"
#include "ui_actions.h"
#include <QMessageBox>

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose" << "Hunting Game" << "Police Job" << "Memory Card" << "Space Invaders" << "Buy lottery");
    ui->actions_cb->addItems(list);
    connect(this, &QDialog::accepted, this, &Actions::handleEnd);
}

Actions::~Actions()
{
    delete ui;
}

QString Actions::getSelectedAction()
{
    return selectedAction;
}


void Actions::handleEnd()
{
    //switch case for QString
    selectedAction = ui->actions_cb->currentText();
    if(selectedAction == "Buy lottery"){
        lottery = new Lottery();
        connect(lottery, &Lottery::sigGameOver, this, &Actions::handleLotteryEnd);
        lottery->setWindowModality(Qt::ApplicationModal);
        lottery->show();
    } else if(selectedAction == "Space Invaders"){
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            spaceInvaders = new SpaceInvaders(qApp->screens()[0]->size(), difficulty->selectedDifficulty);
            spaceInvaders->setWindowModality(Qt::ApplicationModal);
            spaceInvaders->showFullScreen();
            spaceInvaders->run();
            connect(spaceInvaders, &SpaceInvaders::sigGameOver, this, &Actions::handleSpaceInvadersEnd);
        }
    } else if(selectedAction == "Memory Card"){
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            memoryCard = new MemoryCard(difficulty->selectedDifficulty);
            memoryCard->setWindowModality(Qt::ApplicationModal);
            memoryCard->show();
            connect(memoryCard, &MemoryCard::sigGameOver, this, &Actions::handleMemoryEnd);
        }
    } else if(selectedAction == "Police Job"){
        policeJob = new PoliceJob(qApp->screens()[0]->size());
        policeJob->showFullScreen();
        policeJob->run();
        connect(policeJob, &PoliceJob::sigGameOver, this, &Actions::handlePoliceJobEnd);
    } else if(selectedAction == "Hunting Game"){
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            huntingGame = new HuntingGame(qApp->screens()[0]->size(),difficulty->selectedDifficulty);
            huntingGame->setWindowModality(Qt::ApplicationModal);
            huntingGame->showFullScreen();
            huntingGame->run();
            connect(huntingGame, &HuntingGame::sigGameOver, this, &Actions::handleHuntingGameEnd);
        }
    }
}

void Actions::handleLotteryEnd(int wonAmount)
{
    qDebug() << "actions lottery";
    emit sigLotteryEnd(wonAmount);
}

void Actions::handleSpaceInvadersEnd(bool wonGame)
{
    emit sigSpaceInvadersEnd(wonGame);
}

void Actions::handleMemoryEnd()
{
    emit sigMemoryEnd();
}

void Actions::handlePoliceJobEnd(bool wonGame)
{
    emit sigSpaceInvadersEnd(wonGame);
}

void Actions::handleHuntingGameEnd(bool wonGame)
{
    emit sigHuntingGameEnd(wonGame);
}


