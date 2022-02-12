#ifndef ACTIONS_H
#define ACTIONS_H

#include <QDialog>

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

private:
    Ui::Actions *ui;
    QString selectedAction;
};

#endif // ACTIONS_H
