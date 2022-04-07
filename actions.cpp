#include "actions.h"
#include "ui_actions.h"
#include <QMessageBox>

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose" << "Police Job" << "Memory Card" << "Space Invaders" << "Buy lottery");
    ui->actions_cb->addItems(list);
    connect(this, SIGNAL(accepted()), this, SLOT(handleEnd()));
}

Actions::~Actions()
{
    delete ui;
}

QString Actions::getSelectedAction()
{
    return selectedAction;
}

int Actions::getLotteryResult()
{
    return lotteryResult;
}


void Actions::handleEnd()
{
    //switch case for QString
    selectedAction = ui->actions_cb->currentText();
    if(selectedAction == "Buy lottery"){
        lottery = new Lottery();
        lottery->show();
        lottery->exec();
        lotteryResult = lottery->getWonAmount();
    } else if(selectedAction == "Space Invaders"){
        //QDialog
        //QWizardPage
        spaceInvaders = new SpaceInvaders(qApp->screens()[0]->size());
        spaceInvaders->showFullScreen();
        spaceInvaders->run();
        connect(spaceInvaders, &SpaceInvaders::sigGameOver, this, &Actions::handleSpaceInvadersEnd);
    } else if(selectedAction == "Memory Card"){
//        QDialog dialog(this);
//        dialog.exec();
        memoryCard = new MemoryCard();
        memoryCard->show();
        connect(memoryCard, &MemoryCard::sigGameOver, this, &Actions::handleMemoryEnd);
    } else if(selectedAction == "Police Job"){
        policeJob = new PoliceJob(qApp->screens()[0]->size());
        policeJob->showFullScreen();
        policeJob->run();
        connect(policeJob, &PoliceJob::sigGameOver, this, &Actions::handlePoliceJobEnd);


    }
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
