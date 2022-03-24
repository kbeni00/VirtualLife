#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <QWidget>
#include <QPushButton>
#include "character.h"

namespace Ui {
class MemoryCard;
}

class MemoryCard : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryCard(QWidget *parent = nullptr);
    ~MemoryCard();
    void setImage(QPushButton*,QString);


private:
    Ui::MemoryCard *ui;
    Character* character;
    QVector<QString> icons;
    QString firstGuess = "";
    QString secondGuess = "";
    QPushButton* firstButton;
    QPushButton* secondButton;
    int firstPos;
    int secondPos;
    QTimer* cardFlipTimer;
    int matchesFound = 0;
    int allMatches = 4;
private slots:
    void cardClicked();
    void flipBack();
signals:
    void sigGameOver();
};

#endif // MEMORYCARD_H