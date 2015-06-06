#include "opcjerys.h"
#include "ui_opcjerys.h"
#include <iostream>

opcjerys::opcjerys(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::opcjerys)
{
    ui->setupUi(this);
}

opcjerys::~opcjerys()
{
    delete ui;
}

void opcjerys::on_pushButton_clicked()
{
    this->close();
}

void opcjerys::on_BTNdraw_clicked()
{
    QVector<double> x;
    QVector<double> y;
    double a, b, dum;
    std::fstream plik("output.txt",std::fstream::in);
    while(plik >> dum >> a >> dum >> b >> dum >> dum >> dum){
        x.push_back(a);
        y.push_back(b);
    }
    plik.close();

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QColor(255,0,0,255));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 3));

    ui->widget->graph(0)->setData(x, y);
    ui->widget->xAxis->setRange(-0.002, 0.002);
    ui->widget->xAxis->setVisible(false);
    ui->widget->yAxis->setRange(-0.002, 0.002);
    ui->widget->yAxis->setVisible(false);

    ui->widget->replot();
}
