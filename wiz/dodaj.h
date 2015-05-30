#ifndef DODAJ_H
#define DODAJ_H

#include <QDialog>

namespace Ui {
class dodaj;
}

class dodaj : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj(QWidget *parent = 0);
    ~dodaj();

private slots:
    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_BTNappend_clicked();

    void on_BTNsave_clicked();

    void on_BTNdiscard_clicked();

private:
    Ui::dodaj *ui;
};

#endif // DODAJ_H
