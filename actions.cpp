#include "actions.h"
#include "ui_actions.h"
#include <QMessageBox>

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose");
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

QComboBox* Actions::getComboBox(){
    return ui->actions_cb;
}

void Actions::addAction(QString actionName)
{
    ui->actions_cb->addItem(actionName);
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
        QMessageBox msg;
        QString details = "In this game your goal is to shoot the alien invaders before they reach the bottom of the screen.\n"
                          "You can move sideways with the left and right arrow buttons and shoot with the space bar.\n"
                          "If an alien reaches the bottom of the screen, you lose 1 health, if it touches the ship, the game is over.\n"
                          "Harder difficulties give you more points, money.";
        msg.setText(details);
        msg.exec();
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            spaceInvaders = new SpaceInvaders(qApp->screens()[0]->size(), difficulty->selectedDifficulty);
            spaceInvaders->setWindowModality(Qt::ApplicationModal);
            spaceInvaders->showFullScreen();
            spaceInvaders->run();
            connect(spaceInvaders, &SpaceInvaders::sigGameOver, this, &Actions::handleSpaceInvadersEnd);
        }
    } else if(selectedAction == "Memory Card Game"){
        QMessageBox msg;
        QString details = "In this game your goal is to find the pairs of all the cards.\n"
                          "You can flip a card face-up by clicking on it.\n"
                          "Once two cards that make a pair have been flipped, they remain flipped face-up.\n"
                          "In case the two flipped cards are not a pair, they both flip back face-down.\n"
                          "Harder difficulties give you more points, money.";
        msg.setText(details);
        msg.exec();
        difficulty = new Difficulty();
        int res = difficulty->exec();
        if(res == QDialog::Accepted){
            memoryCard = new MemoryCard(difficulty->selectedDifficulty);
            memoryCard->setWindowModality(Qt::ApplicationModal);
            memoryCard->show();
            connect(memoryCard, &MemoryCard::sigGameOver, this, &Actions::handleMemoryEnd);
        }
    } else if(selectedAction == "Hunting Game"){
        QMessageBox msg;
        QString details = "In this game your goal is to hunt turkeys before the time runs out.\n"
                          "You can shoot turkeys by aiming at them with the crossair and clicking on them.\n"
                          "Harder difficulties give you more points, money.";
        msg.setText(details);
        msg.exec();
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
        QMessageBox msg;
        QString details = "In this game your goal is to hit the moles before they disappear.\n"
                          "You can hit a mole by clicking on it.\n"
                          "Harder difficulties give you more points, money.";
        msg.setText(details);
        msg.exec();
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
        QMessageBox msg;
        QString details = "In this game your goal is to collect toys.\n"
                          "You can move around the map with the arrow buttons.\n"
                          "Picking up the milk bottle boost your speed temporarily.\n"
                          "Harder difficulties give you more points, money.";
        msg.setText(details);
        msg.exec();
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

void Actions::handleWhackAMoleEnd(bool wonGame, QString difficulty)
{
    emit sigWhackAMoleEnd(wonGame, difficulty);

}

void Actions::handleCrawlingGameEnd(bool wonGame, QString difficulty)
{
    emit sigCrawlingGameEnd(wonGame, difficulty);
}

void Actions::handleSpaceInvadersEnd(bool wonGame, QString difficulty)
{
    emit sigSpaceInvadersEnd(wonGame, difficulty);
}

void Actions::handleMemoryEnd(QString difficulty)
{
    emit sigMemoryEnd(difficulty);
}


void Actions::handleHuntingGameEnd(bool wonGame, QString difficulty)
{
    emit sigHuntingGameEnd(wonGame, difficulty);
}
