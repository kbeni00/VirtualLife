#ifndef ACTIONS_H
#define ACTIONS_H

#include <QDialog>
#include "lottery.h"
#include "spaceinvaders.h"
#include "memorycard.h"
#include "policejob.h"
#include "huntinggame.h"
#include "difficulty.h"

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
    void handlePoliceJobEnd(bool);
    void handleHuntingGameEnd(bool);
    void handleLotteryEnd(int);
signals:
    void sigSpaceInvadersEnd(bool);
    void sigMemoryEnd();
    void sigPoliceJobEnd(bool);
    void sigHuntingGameEnd(bool);
    void sigLotteryEnd(int);
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
    PoliceJob* policeJob;
    HuntingGame* huntingGame;
    Difficulty* difficulty;


};

#endif // ACTIONS_H
