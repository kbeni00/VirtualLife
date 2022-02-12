#include "actions.h"
#include "ui_actions.h"

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose" << "Buy a pet" << "Choose a new hobby" << "Commit a crime" << "Go shopping" << "Go to a casino" << "Visit a doctor" << "Buy lottery" << "Meditate" << "Go to a theatre" << "Go on a date" << "Go to a party");
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

void Actions::handleEnd()
{
    selectedAction = ui->actions_cb->currentText();
}
