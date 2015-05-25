#ifndef DODAJ_H
#define DODAJ_H

#include <QDialog>

namespace Ui {
class Dodaj;
}

class Dodaj : public QDialog
{
    Q_OBJECT

public:
    explicit Dodaj(QWidget *parent = 0);
    ~Dodaj();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dodaj *ui;
};

#endif // DODAJ_H
