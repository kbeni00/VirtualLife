#ifndef ACTIONS_H
#define ACTIONS_H

#include <QDialog>
#include "lottery.h"
#include "spaceinvaders.h"
#include "memorycard.h"

namespace Ui {
class Actions;
}

class Actions : public QDialog
{
    Q_OBJECT

private slots:
    void handleEnd();
    void handleSpaceInvadersEnd(bool);
    void handleMemoryEnd();
signals:
    void sigSpaceInvadersEnd(bool);
    void sigMemoryEnd();
public:
    explicit Actions(QWidget *parent = nullptr);
    ~Actions();
    QString getSelectedAction();
    int getLotteryResult();

private:
    QString selectedAction;
    Ui::Actions *ui;
    Lottery* lottery;
    SpaceInvaders* spaceInvaders;
    MemoryCard* memoryCard;
    int lotteryResult;
};

#endif // ACTIONS_H
