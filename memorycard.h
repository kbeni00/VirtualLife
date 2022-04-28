#ifndef MEMORYCARD_H
#define MEMORYCARD_H

#include <QWidget>
#include <QPushButton>
#include "character.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>


namespace Ui {
class MemoryCard;
}

class MemoryCard : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryCard(QString difficulty, QWidget *parent = nullptr);
    ~MemoryCard();
    void setImage(QPushButton*,QString);

protected:
//    void closeEvent(QCloseEvent* event) override;

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
    int allMatches;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    QString _difficulty;
    bool finishedNormally = false;

private slots:
    void cardClicked();
    void flipBack();
    void on_giveUpButton_clicked();

signals:
    void sigGameOver(QString);
};

#endif // MEMORYCARD_H
