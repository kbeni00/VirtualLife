#ifndef PURCHASE_H
#define PURCHASE_H

#include <QDialog>
#include <QMessageBox>
#include <QDirIterator>

namespace Ui {
class Purchase;
}

class Purchase : public QDialog
{
    Q_OBJECT

public:
    struct Thingy{
        QString name;
        int price;
    };
    explicit Purchase(QWidget *parent = nullptr);
    ~Purchase();
    void setImage(QPushButton* button, QPixmap pixmap);
signals:
    void sigBoughtItem(QString,int);

private slots:
    void on_collectiblesRightButton_clicked();

    void on_needsRightButton_clicked();

    void on_needsLeftButton_clicked();

    void on_collectiblesLeftButton_clicked();

    void handleClick();

    void on_helpButton_clicked();

private:
    Ui::Purchase *ui;
    QVector<Thingy> collectibles;
    QVector<Thingy> needs;
};

#endif // PURCHASE_H
