#ifndef LICZENIE_H
#define LICZENIE_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class liczenie;
}

class liczenie : public QDialog
{
    Q_OBJECT

public:
    explicit liczenie(QWidget *parent = 0);
    ~liczenie();

private slots:
    void on_BTNclose_clicked();

    void on_BTNcompute_clicked();

    void pokaz_magnesy();

    void on_BTNgenerate_clicked();

    void on_BTNload_clicked();

private:
    Ui::liczenie *ui;
};

#endif // LICZENIE_H
