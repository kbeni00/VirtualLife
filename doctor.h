#ifndef DOCTOR_H
#define DOCTOR_H

#include <QDialog>

namespace Ui {
class Doctor;
}

class Doctor : public QDialog
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr);
    ~Doctor();
signals:
    void sigDoctorSelected(QString);

private:
    Ui::Doctor *ui;
};

#endif // DOCTOR_H
