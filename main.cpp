#include "virtuallifeview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VirtualLifeView w;
    w.show();
    return a.exec();
}
