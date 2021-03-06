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
#include "doctor.h"
#include "athletegame.h"
#include <QComboBox>
#include <QMessageBox>

namespace Ui {
class Actions;
}

class Actions : public QDialog
{
    Q_OBJECT

private slots:
    void handleEnd();
    void handleSpaceInvadersEnd(bool,QString);
    void handleMemoryEnd(QString);
    void handleHuntingGameEnd(bool,QString);
    void handleLotteryEnd(int);
    void handleWhackAMoleEnd(bool,QString);
    void handleCrawlingGameEnd(bool,QString);
    void handleDoctorEnd(QString);
    void handleAthleteGameEnd(bool, QString);
signals:
    void sigSpaceInvadersEnd(bool,QString);
    void sigMemoryEnd(QString);
    void sigHuntingGameEnd(bool,QString);
    void sigLotteryEnd(int);
    void sigWhackAMoleEnd(bool,QString);
    void sigCrawlingGameEnd(bool,QString);
    void sigDoctorEnd(QString);
    void sigAthleteGameEnd(bool,QString);
public:
    explicit Actions(QWidget *parent = nullptr);
    ~Actions();
    QString getSelectedAction();
    int getLotteryResult();
    void addAction(QString);
    QComboBox* getComboBox();

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
    Doctor* doctor;
    AthleteGame* athleteGame;
    QString selectedDifficulty;


};

#endif // ACTIONS_H
