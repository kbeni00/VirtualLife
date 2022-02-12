#ifndef RELATIONSHIPS_H
#define RELATIONSHIPS_H

#include <QDialog>

namespace Ui {
class Relationships;
}

class Relationships : public QDialog
{
    Q_OBJECT

public:
    explicit Relationships(QWidget *parent = nullptr);
    ~Relationships();

private:
    Ui::Relationships *ui;
};

#endif // RELATIONSHIPS_H
