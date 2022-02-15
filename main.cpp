#include "virtuallifeview.h"

#include <QApplication>
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //set the app style sheet
    QFile styleSheetFile(":/characterImages/SpyBot.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);

    VirtualLifeView w;
    w.show();
    return a.exec();
}
