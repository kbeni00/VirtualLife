#ifndef ACTIONS_H
#define ACTIONS_H

#include <QDialog>
#include "lottery.h"

namespace Ui {
class Actions;
}

class Actions : public QDialog
{
    Q_OBJECT

private slots:

    void handleEnd();

public:
    explicit Actions(QWidget *parent = nullptr);
    ~Actions();
    QString getSelectedAction();
    int getLotteryResult();

private:
    Ui::Actions *ui;
    QString selectedAction;
    Lottery* lottery;
    int lotteryResult;
};

#endif // ACTIONS_H
