#ifndef ASSETS_H
#define ASSETS_H

#include <QDialog>

namespace Ui {
class Assets;
}

class Assets : public QDialog
{
    Q_OBJECT

public:
    explicit Assets(QWidget *parent = nullptr);
    ~Assets();

private:
    Ui::Assets *ui;
};

#endif // ASSETS_H
