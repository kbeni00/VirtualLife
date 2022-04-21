#ifndef ACTIONS_H
#define ACTIONS_H

#include <QDialog>
#include "lottery.h"
#include "spaceinvaders.h"
#include "memorycard.h"
#include "huntinggame.h"
#include "difficulty.h"
#include "whackamole.h"
#include "crawlinggame.h"

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
    void handleWhackAMoleEnd(bool);
    void handleCrawlingGameEnd(bool);
signals:
    void sigSpaceInvadersEnd(bool);
    void sigMemoryEnd();
    void sigPoliceJobEnd(bool);
    void sigHuntingGameEnd(bool);
    void sigLotteryEnd(int);
    void sigWhackAMoleEnd(bool);
    void sigCrawlingGameEnd(bool);
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
    HuntingGame* huntingGame;
    WhackAMole* whackamole;
    CrawlingGame* crawlingGame;
    Difficulty* difficulty;


};

#endif // ACTIONS_H
