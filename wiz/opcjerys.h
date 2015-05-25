#ifndef OPCJERYS_H
#define OPCJERYS_H

#include <QDialog>

namespace Ui {
class opcjerys;
}

class opcjerys : public QDialog
{
    Q_OBJECT

public:
    explicit opcjerys(QWidget *parent = 0);
    ~opcjerys();

private slots:
    void on_pushButton_clicked();

private:
    Ui::opcjerys *ui;
};

#endif // OPCJERYS_H
