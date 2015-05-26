#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wczytaj.h"
#include "opcjerys.h"
#include "QAction"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbwczytaj->setToolTip("pokazuje opcje wczytywania");
    ui->pushButton->setToolTip("teraz czytasz opcje do przycisku opcje");
    ui->pushButton_2->setToolTip("teraz czytasz opcje do przycisku licz");
    ui->pushButton_3->setToolTip("teraz czytasz opcje do przycisku wyjsce");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbwczytaj_clicked()
{
    wczytaj wcz;
    wcz.setModal(true);
    wcz.exec();
}

void MainWindow::on_pushButton_clicked()
{
    opcjerys rys;
    rys.setModal(true);
    rys.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}

void MainWindow::on_pbwczytaj_pressed()
{

}
