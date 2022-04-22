#include "memorycard.h"
#include "ui_memorycard.h"
#include <QRandomGenerator>
#include <QVector>
#include <QThread>
#include <QTimer>
#include <QMessageBox>

//shuffle the vector
MemoryCard::MemoryCard(QString difficulty, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryCard)
{
    ui->setupUi(this);
    mediaPlayer = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    audioOutput->setVolume(50);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/memorycards/resources/sounds/memorygamemusic.mp3"));
    mediaPlayer->play();
    QVector<QString> allIcons {"car","car","house", "house", "ship","ship","plane","plane"};

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            QPushButton *button = new QPushButton();

            button->setCheckable(true);
            int random = QRandomGenerator::global()->bounded(allIcons.size());
            icons.push_back(allIcons.at(random));
            allIcons.removeAt(random);

            setImage(button,":/memorycards/resources/memorygame/back.jpg");
            ui->cardsLayout->addWidget(button,i,j);

            connect(button, SIGNAL(clicked()), this, SLOT(cardClicked())) ;
        }
    }
}


MemoryCard::~MemoryCard()
{
    delete ui;
}

void MemoryCard::setImage(QPushButton* button, QString path)
{
    QPixmap pixmap(path);
    QIcon icon(pixmap);
    button->setIcon(icon);
    button->setIconSize(pixmap.rect().size());
    button->setFixedSize(pixmap.rect().size());
}

void MemoryCard::cardClicked()
{
    QPushButton* senderButton = dynamic_cast <QPushButton*> (QObject::sender());
    int index = ui->cardsLayout->indexOf(senderButton);
    if(!firstGuess.isEmpty() && !secondGuess.isEmpty()) return;
    QString path = ":/memorycards/" + icons.at(index);
    cardFlipTimer = new QTimer(this);
    connect(cardFlipTimer, &QTimer::timeout, this, &MemoryCard::flipBack);
    if(firstGuess == ""){
        setImage(senderButton, path);
        firstGuess = icons.at(index);
        firstButton = senderButton;
        firstPos = index;
    } else{
        if(firstPos == index) return;
        secondGuess = icons.at(index);
        secondButton = senderButton;
        secondPos = index;
        setImage(senderButton, path);
        if(firstGuess == secondGuess){
            if(++matchesFound == allMatches){
                QMessageBox msg;
                QString resultMessage = "Congratulations, you've found all the pairs!";
                msg.setText(resultMessage);
                msg.exec();
                mediaPlayer->stop();
                this->close();
                emit sigGameOver();
            }
            firstButton->setEnabled(false);
            secondButton->setEnabled(false);
            cardFlipTimer->start(5);
        } else{
            cardFlipTimer->start(1000);
        }
    }
}

void MemoryCard::flipBack()
{
    if(firstGuess != secondGuess){
        setImage(firstButton,":/memorycards/resources/memorygame/back.jpg");
        setImage(secondButton,":/memorycards/resources/memorygame/back.jpg");
    }
    firstButton = nullptr;
    secondButton = nullptr;
    firstGuess = "";
    secondGuess = "";
    cardFlipTimer->stop();
}
