#ifndef WCZYTAJ_H
#define WCZYTAJ_H

#include <QDialog>
#include <QWidget>
#include <QTableView>
#include <QFileDialog>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QTextStream>
#include <QString>
#include "magnesy.h"

namespace Ui {
class wczytaj;
}

class wczytaj : public QDialog
{
    Q_OBJECT

public:
    explicit wczytaj(QWidget *parent = 0);
    ~wczytaj();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_BTNshow_clicked();

    void on_BTNrevert_clicked();

private:
    Ui::wczytaj *ui;
};

#endif // WCZYTAJ_H
