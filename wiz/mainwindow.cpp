#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wczytaj.h"
#include "opcjerys.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
