#ifndef LOTTERY_H
#define LOTTERY_H

#include <QDialog>

namespace Ui {
class Lottery;
}

class Lottery : public QDialog
{
    Q_OBJECT

public:
    explicit Lottery(QWidget *parent = nullptr);
    ~Lottery();
    int getWonAmount();
signals:
    void sigGameOver(int);

private:
    Ui::Lottery *ui;
    QVector<QVector<QPushButton*>> buttons;
    QVector<int> guesses;
    QVector<int> winningNums;
    int wonAmount;
private slots:
    void numberGuessed();
};

#endif // LOTTERY_H
