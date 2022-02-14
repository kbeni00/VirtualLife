#include "actions.h"
#include "ui_actions.h"

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose" << "Buy a pet" << "Choose a new hobby" << "Commit a crime" << "Go shopping" << "Go to a casino" << "Visit a doctor" << "Buy lottery" << "Meditate" << "Go to a theatre" << "Go on a date" << "Go to a party" << "Play a game");
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
    }
}
