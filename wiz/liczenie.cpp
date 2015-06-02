#include "liczenie.h"
#include "ui_liczenie.h"
#include "global.h"
#include "generate.h"
#include <thread>

const double l = 204.0;
const double r = 0.002;

std::vector<proton> proton_vec;

liczenie::liczenie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::liczenie)
{
    ui->setupUi(this);
    liczenie::pokaz_magnesy();
}

liczenie::~liczenie()
{
    delete ui;
}

void liczenie::on_BTNclose_clicked()
{
    this->close();
}

void liczenie::on_BTNcompute_clicked()
{
    int rdzenie;
    rdzenie=(int)std::thread::hardware_concurrency();
    if (rdzenie==0) //czyli że nie wykrywa
    {
        rdzenie=2;
    }

    remove("output.txt");
    ifstream plik("input.txt",ios::in);
    proton_vec=wczytajprotony(plik);
    plik.close();

    std::vector<proton> proton_tab[rdzenie];
    int I=proton_vec.size()/rdzenie;
    for(int i = 0; i < rdzenie; i++){
        std::vector<proton>::const_iterator first = proton_vec.begin()+i*I;
        std::vector<proton>::const_iterator last = proton_vec.begin()+(i+1)*I;
        std::vector<proton> proton_temp(first, last);
        proton_tab[i] = proton_temp;
        proton_temp.clear();
    }

    std::thread thr[rdzenie];
    for (int i = 0; i < rdzenie; i++)
    {
        thr[i]=std::thread(oblicz, magnes_vec, proton_tab[i], l, r);
    }

    for (int i = 0; i < rdzenie; i++)
    {
        thr[i].join();
    }
}

void liczenie::pokaz_magnesy()
{
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
    ui->tableWidget->setRowCount(0);
    int I=magnes_vec.size();
    for(int i=0; i<I; i++){
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setData(Qt::EditRole, magnes_vec[i]->GetPolozenie());
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setData(Qt::EditRole, magnes_vec[i]->GetDlugosc());
        ui->tableWidget->setItem(i,1,item2);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setData(Qt::EditRole, magnes_vec[i]->GetIndukcja());
        ui->tableWidget->setItem(i,2,item3);
        QTableWidgetItem *item4 = new QTableWidgetItem(QString::fromStdString(magnes_vec[i]->Kto()));
        ui->tableWidget->setItem(i,3,item4);
    }
    ui->tableWidget->sortItems(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void liczenie::on_BTNgenerate_clicked()
{
    int ile = ui->LEparnum->text().toInt();
    if(ile==0) ile = 10000;
    gen(ile);
}

void liczenie::on_BTNload_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Otwórz"), "",tr("Pliki cząstek (*.txt)"));
    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    ifstream plik(filename.toUtf8().constData(),ios::in);
    proton_vec = wczytajprotony(plik);
    plik.close();
}
