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
    QVector<double> id, x, px, y, py, pz , E, pT;
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
        pT.push_back(sqrt(c*c+e*e));
    }
    plik.close();

    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QColor(255,0,0,255));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 3));

    int i = ui->comboBox->currentIndex();
    int j = ui->comboBox_2->currentIndex();
    {
        switch (i) {
        case 0:
            t1=id;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i));
            break;
        case 1:
            t1=x;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [mm]");
            break;
        case 2:
            t1=px;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [GeV]");
            break;
        case 3:
            t1=y;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [mm]");
            break;
        case 4:
            t1=py;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [Gev]");
            break;
        case 5:
            t1=pz;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [GeV]");
            break;
        case 6:
            t1=E;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [GeV]");
            break;
        case 7:
            t1=pT;
            ui->widget->xAxis->setLabel(ui->comboBox->itemText(i)+" [Gev]");
            break;
        default:
            break;
        }

        switch (j) {
        case 0:
            t2=id;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j));
            break;
        case 1:
            t2=x;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [mm]");
            break;
        case 2:
            t2=px;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [GeV]");
            break;
        case 3:
            t2=y;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [mm]");
            break;
        case 4:
            t2=py;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [Gev]");
            break;
        case 5:
            t2=pz;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [GeV]");
            break;
        case 6:
            t2=E;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [GeV]");
            break;
        case 7:
            t2=pT;
            ui->widget->yAxis->setLabel(ui->comboBox->itemText(j)+" [Gev]");
            break;
        default:
            break;
        }
    }

    ui->widget->graph(0)->setData(t1, t2);
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
