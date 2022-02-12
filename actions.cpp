#include "actions.h"
#include "ui_actions.h"

Actions::Actions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Actions)
{
    ui->setupUi(this);
}

Actions::~Actions()
{
    delete ui;
}
