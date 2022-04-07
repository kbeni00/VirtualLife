#ifndef ACTIONS_H
#define ACTIONS_H

#include <QDialog>
#include "lottery.h"
#include "spaceinvaders.h"
#include "memorycard.h"
#include "policejob.h"

enum Difficulty{
    VeryEasy, Easy, Medium, Hard, VeryHard, Impossible
};
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
signals:
    void sigSpaceInvadersEnd(bool);
    void sigMemoryEnd();
    void sigPoliceJobEnd(bool);
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
    int lotteryResult;
    Difficulty difficulty;

};

#endif // ACTIONS_H
