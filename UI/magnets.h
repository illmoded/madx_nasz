#ifndef MAGNETS_H
#define MAGNETS_H

#include <QWidget>
#include <QTableView>
#include <QFileDialog>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QTextStream>
#include <QString>

namespace Ui {
class Magnets;
}

class Magnets : public QWidget
{
    Q_OBJECT

public:
    explicit Magnets(QWidget *parent = 0);
    ~Magnets();

private slots:


    void on_BtnOpen_clicked();

private:
    Ui::Magnets *ui2;
    QStandardItemModel *model;
};

#endif // MAGNETS_H
