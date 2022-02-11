#ifndef VIRUTALLIFEVIEW_H
#define VIRUTALLIFEVIEW_H

#include <QMainWindow>
#include "virtuallifemodel.h"
#include "initialdata.h"
#include "details.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VirutalLifeView; }
QT_END_NAMESPACE

class VirutalLifeView : public QMainWindow
{
    Q_OBJECT

public:
    VirutalLifeView(QWidget *parent = nullptr);
    ~VirutalLifeView();
    void updatePlayer();

private slots:
    void on__start_clicked();

    void on__age_clicked();

private:
    Ui::VirutalLifeView* ui;
    InitialData* initialData;
    Details* details;
    VirtualLifeModel* model;
};
#endif // VIRUTALLIFEVIEW_H
