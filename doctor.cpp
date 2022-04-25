#include "doctor.h"
#include "ui_doctor.h"

Doctor::Doctor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
    connect(this, &QDialog::accepted, [=](){emit sigDoctorSelected(ui->doctorsCB->currentText());});
}

Doctor::~Doctor()
{
    delete ui;
}
