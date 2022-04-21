#include "actions.h"
#include "ui_actions.h"
#include <QMessageBox>

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose" << "Crawling Game" << "Hunting Game" << "Whack-A-Mole" << "Memory Card" << "Space Invaders" << "Buy lottery");
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
    } else if(selectedAction == "Whack-A-Mole"){
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            whackamole = new WhackAMole(qApp->screens()[0]->size(),difficulty->selectedDifficulty);
            whackamole->setWindowModality(Qt::ApplicationModal);
            whackamole->showFullScreen();
            whackamole->run();
            connect(whackamole, &WhackAMole::sigGameOver, this, &Actions::handleWhackAMoleEnd);
        }
    } else if(selectedAction == "Crawling Game"){
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            crawlingGame = new CrawlingGame(qApp->screens()[0]->size(),difficulty->selectedDifficulty);
            crawlingGame->setWindowModality(Qt::ApplicationModal);
            crawlingGame->showFullScreen();
            crawlingGame->run();
            connect(crawlingGame, &CrawlingGame::sigGameOver, this, &Actions::handleCrawlingGameEnd);
        }
    }
}

void Actions::handleLotteryEnd(int wonAmount)
{
    emit sigLotteryEnd(wonAmount);
}

void Actions::handleWhackAMoleEnd(bool wonGame)
{
    emit sigWhackAMoleEnd(wonGame);

}

void Actions::handleCrawlingGameEnd(bool wonGame)
{
    emit sigCrawlingGameEnd(wonGame);
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


