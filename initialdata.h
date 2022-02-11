#ifndef INITIALDATA_H
#define INITIALDATA_H

#include <QDialog>

namespace Ui {
class InitialData;
}

class InitialData : public QDialog
{
    Q_OBJECT

private slots:
    void handleEnd();
public:
    explicit InitialData(QWidget *parent = nullptr);
    ~InitialData();
    QString getSelectedName();
    QString getSelectedGender();

private:
    Ui::InitialData *ui;
    QString selectedName;
    QString selectedGender;
};


#endif // INITIALDATA_H
