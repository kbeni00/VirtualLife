#include "initialdata.h"
#include "ui_initialdata.h"

InitialData::InitialData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialData)
{
    ui->setupUi(this);
    QStringList list = (QStringList() << "Choose" << "Male" << "Female");
    ui->gender_cb->addItems(list);
    connect(this, SIGNAL(accepted()), this, SLOT(handleEnd()));
}

InitialData::~InitialData()
{
    delete ui;
}

QString InitialData::getSelectedName()
{
    return selectedName;
}

QString InitialData::getSelectedGender()
{
    return selectedGender;
}

void InitialData::handleEnd(){
    selectedName =  ui->nameval->displayText();
    selectedGender = ui->gender_cb->currentText();
}
