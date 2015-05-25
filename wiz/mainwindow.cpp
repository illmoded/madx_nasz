#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wczytaj.h"

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
