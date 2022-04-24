#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include <QDialog>
#include "character.h"

namespace Ui {
class Achievements;
}

class Achievements : public QDialog
{
    Q_OBJECT

public:
    explicit Achievements(Character*,QWidget *parent = nullptr);
    ~Achievements();

private:
    Ui::Achievements *ui;
};

#endif // ACHIEVEMENTS_H
