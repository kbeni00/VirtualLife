#include "lottery.h"
#include "ui_lottery.h"
#include "QPushButton"
#include "QSignalMapper"
#include "QMessageBox"
#include "QRandomGenerator"

Lottery::Lottery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lottery)
{
    ui->setupUi(this);
    //Fill with 90 pushbuttons, check the help on the left, set size, put it in a new coloumn, 2D
    int num = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 10; j++){
            //do it with i,j instead of num
            QPushButton *button = new QPushButton(QString::number(++num), this);
            ui->gridLayout->addWidget(button,i,j);
            connect (button, SIGNAL(clicked()), this, SLOT(numberGuessed())) ;
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
    senderButton->setEnabled(false);
    guesses.push_back(senderButton->text().toInt());
    if(guesses.size() == 5){
        //show guessed nums, result, price
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
                                QString::number(winningNums[4]) + ", " +
                                "\n Your score: " +
                                QString::number(correctlyGuessedNums) +
                                "\\" +
                                QString::number(winningNums.size()) +
                                "\n Your reward: " +
                                QString::number(prices[correctlyGuessedNums]);
        msg.setText(resultMessage);
        msg.exec();
        wonAmount = prices[correctlyGuessedNums];
        this->close();
    }
}


