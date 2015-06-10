#ifndef OPCJERYS_H
#define OPCJERYS_H

#include <QDialog>
#include <fstream>
#include "qcustomplot.h"

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

    void on_BTNdraw_clicked();

    void on_CBlogx_clicked();

    void on_CBlogy_clicked();

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

    void on_BTNsave_clicked();

private:
    Ui::opcjerys *ui;
};

#endif // OPCJERYS_H
