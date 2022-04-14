#include "assets.h"
#include "ui_assets.h"

Assets::Assets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Assets)
{
    ui->setupUi(this);

}

Assets::~Assets()
{
    delete ui;
}
