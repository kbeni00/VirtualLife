#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>

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
};

#endif // DETAILS_H
