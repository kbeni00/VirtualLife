#include "relationships.h"
#include "ui_relationships.h"

Relationships::Relationships(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Relationships)
{
    ui->setupUi(this);
}

Relationships::~Relationships()
{
    delete ui;
}
