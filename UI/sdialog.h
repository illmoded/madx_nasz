#ifndef SDIALOG_H
#define SDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class sDialog;
}

class sDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sDialog(QWidget *parent = 0);
    ~sDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::sDialog *ui;
};

#endif // SDIALOG_H
