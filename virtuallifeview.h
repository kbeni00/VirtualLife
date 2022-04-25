#ifndef VIRTUALLIFEVIEW_H
#define VIRTUALLIFEVIEW_H

#include <QMainWindow>
#include "virtuallifemodel.h"
#include "initialdata.h"
#include "actions.h"
#include "purchase.h"
#include "assets.h"
#include "achievements.h"
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class VirtualLifeView; }
QT_END_NAMESPACE

class VirtualLifeView : public QMainWindow
{
    Q_OBJECT

public:
    struct EventDetails{
        QString description;
        int influence;
        EventDetails(QString d,int i){
            description = d;
            influence = i;
        }
    };
    VirtualLifeView(QWidget *parent = nullptr);
    ~VirtualLifeView();
    void updateCharacter();
    void changeStage();
    void generateRandomEvent();
    void initEvents();

private slots:
    bool on__start_clicked();

    void on__age_clicked();

    void on__actions_clicked();

    void on__purchase_clicked();

    void on__assets_clicked();

    void handleSpaceInvadersEnd(bool,QString);

    void handleMemoryEnd(QString);

    void on__savegame_clicked();

    void on__loadgame_clicked();

    void on__newcharacter_clicked();

    void handleReadError();

    void on__characters_clicked();

    void handleHuntingGameEnd(bool,QString);

    void handleLotteryEnd(int);

    void handleBoughtItem(QString,int);

    void handleWhackAMoleEnd(bool,QString);

    void handleCrawlingGameEnd(bool,QString);

    void on__achievements_clicked();

    void handleDoctorEnd(QString);

    void handleAthleteGameEnd(bool, QString);

private:
    Ui::VirtualLifeView* ui;
    InitialData* initialData;
    Actions* actions;
    Purchase* purchase;
    Assets* assets;
    Achievements* achievements;
    VirtualLifeModel* model;
    QVector<EventDetails> allEvents;
};
#endif // VIRTUALLIFEVIEW_H
