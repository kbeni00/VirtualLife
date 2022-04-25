#include "lottery.h"
#include "ui_lottery.h"
#include "QPushButton"
#include "QSignalMapper"
#include "QMessageBox"
#include "QRandomGenerator"
#include <QtAlgorithms>

Lottery::Lottery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lottery)
{
    ui->setupUi(this);
    int num = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 10; j++){
            QPushButton *button = new QPushButton(QString::number(++num), this);
            ui->gridLayout->addWidget(button,i,j);
            connect(button, &QPushButton::clicked, this, &Lottery::numberGuessed);
        }
    }
}

Lottery::~Lottery()
{
    delete ui;
}

int Lottery::getWonAmount()
{
    return wonAmount;
}

void Lottery::numberGuessed()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    senderButton->hide();
    guesses.push_back(senderButton->text().toInt());
    if(guesses.size() == 5){
        while(winningNums.size() != 5){
            int winningNum = QRandomGenerator::global()->generate()%90+1;
            if(!winningNums.contains(winningNum)){
                winningNums.push_back(winningNum);
            }
        }

        int correctlyGuessedNums = 0;

        for(int i = 0; i < guesses.size(); i++){
            if(winningNums.contains(guesses[i])){
                correctlyGuessedNums++;
            }
        }
        QVector<int> prices;
        for(int i = 0; i < 5; i++){
            prices.push_back(i*10000);
        }
        wonAmount = prices[correctlyGuessedNums];

        std::sort(guesses.begin(),guesses.end());
        std::sort(winningNums.begin(), winningNums.end());


        QMessageBox msg;
        QString resultMessage = " You guessed these numbers: " +
                                QString::number(guesses[0]) + ", " +
                                QString::number(guesses[1]) + ", " +
                                QString::number(guesses[2]) + ", " +
                                QString::number(guesses[3]) + ", " +
                                QString::number(guesses[4]) +
                                "\n These are the winning numbers: " +
                                QString::number(winningNums[0]) + ", " +
                                QString::number(winningNums[1]) + ", " +
                                QString::number(winningNums[2]) + ", " +
                                QString::number(winningNums[3]) + ", " +
                                QString::number(winningNums[4]) +
                                "\n Your score: " +
                                QString::number(correctlyGuessedNums) +
                                "\\" +
                                QString::number(winningNums.size()) +
                                "\n Your reward: " +
                                QString::number(prices[correctlyGuessedNums]);
        msg.setText(resultMessage);
        msg.exec();
        this->close();
        emit sigGameOver(wonAmount);
    }
}


