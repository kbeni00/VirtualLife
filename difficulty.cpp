#include "difficulty.h"
#include "ui_difficulty.h"

Difficulty::Difficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Difficulty)
{
    ui->setupUi(this);
    connect(this, &QDialog::accepted, this, &Difficulty::handleEnd);


}

Difficulty::~Difficulty()
{
    delete ui;
}

void Difficulty::handleEnd()
{
    selectedDifficulty = ui->comboBox->currentText();
}
