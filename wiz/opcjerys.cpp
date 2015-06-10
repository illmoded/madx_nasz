#include "opcjerys.h"
#include "ui_opcjerys.h"

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
    QVector<double> id, x, px, y, py, pz , E;
    QVector<double> t1, t2;
    double a, b, c, d, e, f, g;
    std::fstream plik("output.txt",std::fstream::in);
    while(plik >> a >> b >> c >> d >> e >> f >> g){
        id.push_back(a);
        x.push_back(b);
        px.push_back(c);
        y.push_back(d);
        py.push_back(e);
        pz.push_back(f);
        E.push_back(g);
    }
    plik.close();

    int i = ui->comboBox->currentIndex();
    int j = ui->comboBox_2->currentIndex();
    {
        if(i==0) t1=id;
        if(i==1) t1=x;
        if(i==2) t1=px;
        if(i==3) t1=y;
        if(i==4) t1=py;
        if(i==5) t1=pz;
        if(i==6) t1=E;

        if(j==0) t2=id;
        if(j==1) t2=x;
        if(j==2) t2=px;
        if(j==3) t2=y;
        if(j==4) t2=py;
        if(j==5) t2=pz;
        if(j==6) t2=E;
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QColor(255,0,0,255));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 3));

    ui->widget->graph(0)->setData(t1, t2);
    ui->widget->xAxis->setLabel(ui->comboBox->itemText(i));
    ui->widget->yAxis->setLabel(ui->comboBox_2->itemText(j));
    ui->widget->graph(0)->rescaleAxes();

    if(i==1 && j==3){
        ui->widget->xAxis->setRange(-0.002, 0.002);
        ui->widget->yAxis->setRange(-0.002, 0.002);
    }

    ui->widget->replot();
}

void opcjerys::on_CBlogx_clicked()
{
    if(ui->CBlogx->isChecked()){
        ui->widget->xAxis->setScaleType(QCPAxis::stLogarithmic);
        ui->widget->xAxis->setScaleLogBase(10);
        ui->widget->xAxis->setNumberFormat("eb");
        ui->widget->xAxis->setNumberPrecision(0);
    }
    else{
        ui->widget->xAxis->setScaleType(QCPAxis::stLinear);
        ui->widget->xAxis->setNumberFormat("g");
        ui->widget->xAxis->setNumberPrecision(4);
    }
    opcjerys::on_BTNdraw_clicked();
}

void opcjerys::on_CBlogy_clicked()
{
    if(ui->CBlogy->isChecked()){
        ui->widget->yAxis->setScaleType(QCPAxis::stLogarithmic);
        ui->widget->yAxis->setScaleLogBase(10);
        ui->widget->yAxis->setNumberFormat("eb");
        ui->widget->yAxis->setNumberPrecision(0);
    }
    else{
        ui->widget->yAxis->setScaleType(QCPAxis::stLinear);
        ui->widget->yAxis->setNumberFormat("g");
        ui->widget->yAxis->setNumberPrecision(4);
    }
    opcjerys::on_BTNdraw_clicked();
}

void opcjerys::on_comboBox_activated(int index)
{
    opcjerys::on_BTNdraw_clicked();
}

void opcjerys::on_comboBox_2_activated(int index)
{
    opcjerys::on_BTNdraw_clicked();
}

void opcjerys::on_BTNsave_clicked()
{
    QString str = ui->comboBox->currentText() + ui->comboBox_2->currentText();
    double w = 1024;
    double h = 1024;
    if(ui->RBpng->isChecked()){
        ui->widget->savePng(str, w, h);
    }
    if(ui->RBpdf->isChecked()){
        ui->widget->savePdf(str, w, h);
    }
}
