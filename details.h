#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>
//#include "virtuallifemodel.h"

namespace Ui {
class Details;
}

class Details : public QDialog
{
    Q_OBJECT

public:
    explicit Details(QWidget *parent = nullptr);
    ~Details();
private:
    Ui::Details *ui;
//    VirtualLifeModel* model;
};

#endif // DETAILS_H
