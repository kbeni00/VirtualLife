#ifndef VIRTUALLIFEVIEW_H
#define VIRTUALLIFEVIEW_H

#include <QMainWindow>
#include "virtuallifemodel.h"
#include "initialdata.h"
#include "details.h"
#include "actions.h"
#include "relationships.h"
#include "assets.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VirtualLifeView; }
QT_END_NAMESPACE

class VirtualLifeView : public QMainWindow
{
    Q_OBJECT

public:
    VirtualLifeView(QWidget *parent = nullptr);
    ~VirtualLifeView();
    void updateCharacter();
    void changeStage();

private slots:
    bool on__start_clicked();

    void on__age_clicked();

    void on__details_clicked();

    void on__actions_clicked();

    void on__relationships_clicked();

    void on__assets_clicked();

    void handleSpaceInvadersEnd(bool);

    void handleMemoryEnd();

    void handlePoliceJobEnd(bool);

    void on__savegame_clicked();

    void on__loadgame_clicked();

    void on__newcharacter_clicked();

    void handleReadError();

    void on__characters_clicked();

private:
    Ui::VirtualLifeView* ui;
    InitialData* initialData;
    Details* details;
    Actions* actions;
    Relationships* relationships;
    Assets* assets;
    VirtualLifeModel* model;
};
#endif // VIRTUALLIFEVIEW_H
