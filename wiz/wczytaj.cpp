#include "wczytaj.h"
#include "ui_wczytaj.h"
#include "QToolTip"
#include "global.h"

std::vector<magnes_ptr> magnes_temp; //tymczasowa lista magnesów
std::vector<magnes_ptr> magnes_load; // magnesy wczytane, nie zapisane
// magnes_vec to magnesy zapiane, obiekt globalny, nie chciało mi się szukać jak inaczej przekazywać

double l = 204.;

wczytaj::wczytaj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wczytaj)
{
    ui->setupUi(this);
    magnes_load=magnes_vec;
    wczytaj::on_BTNshow_clicked();

    ui->tableWidget->horizontalHeaderItem(0)->setToolTip("Położenie w zakresie od 0 do 204 [m]");
    ui->tableWidget->horizontalHeaderItem(1)->setToolTip("Długość magnesu [m]");
    ui->tableWidget->horizontalHeaderItem(2)->setToolTip("Indukcja pola [T]");
    ui->tableWidget->horizontalHeaderItem(3)->setToolTip("Rodzaj magnesu [DU, DD, KX, KY]");
}

wczytaj::~wczytaj()
{
    delete ui;
}

void wczytaj::on_pushButton_5_clicked() // wyjście
{
    this->close();
}

void wczytaj::on_pushButton_clicked() // wczytanie z pliku
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Otwórz"), "",tr("Pliki magnesów (*.mag)"));
//    QFile file(filename);
//    file.open(QIODevice::ReadWrite);

    ifstream plik(filename.toUtf8().constData(),ios::in);
    magnes_temp = wczytajmagnesy(plik);
    magnes_load = vappend(magnes_load, magnes_temp);
    magnes_temp.clear();
    plik.close();

    wczytaj::on_BTNshow_clicked();
    ui->statusbar->setText("Wczytano magnesy z pliku.");
}

void wczytaj::on_pushButton_2_clicked() //dodanie pojedynczego
{
    wczytaj::on_BTNshow_clicked();
    int i=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(i);

    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setData(Qt::EditRole, 0);
    ui->tableWidget->setItem(i,0,item1);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setData(Qt::EditRole, 0);
    ui->tableWidget->setItem(i,1,item2);
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setData(Qt::EditRole, 0);
    ui->tableWidget->setItem(i,2,item3);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString::fromStdString("M"));
    ui->tableWidget->setItem(i,3,item4);

    ui->statusbar->setText("Dodano magnes.");
}

void wczytaj::on_pushButton_4_clicked() // czyszczenie wszystkich
{
    magnes_vec.clear();
    magnes_load.clear();
    wczytaj::on_BTNshow_clicked();
    ui->statusbar->setText("Wyczyszczono wszystkie zapisane magnesy.");
}

void wczytaj::on_pushButton_3_clicked() // zapis
{
    magnes_load.clear();
    double pol, dl, in;
    std::string m;
    for(int i=0; i<ui->tableWidget->rowCount(); i++){
        pol=ui->tableWidget->item(i,0)->text().toDouble();
        dl=ui->tableWidget->item(i,1)->text().toDouble();
        in=ui->tableWidget->item(i,2)->text().toDouble();
        m=ui->tableWidget->item(i,3)->text().toUtf8().constData();
        if((m=="DU" || m=="DD" || m=="KX" || m=="KY") && dl!=0 && in!=0 && pol<l){
            magnes_temp=wczytajjeden(pol, dl, in, m);
            magnes_load=vappend(magnes_load,magnes_temp);
            magnes_temp.clear();
        }
    }
    magnes_vec=magnes_load;
    magnes_load.clear();
    this->close();
}

void wczytaj::on_BTNshow_clicked() // wypisz magnesy zapisane
{
    ui->statusbar->setText("Odświeżam...");
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
    ui->tableWidget->setRowCount(0);
    int I=magnes_load.size();
    for(int i=0; i<I; i++){
        ui->tableWidget->insertRow(i);
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setData(Qt::EditRole, magnes_load[i]->GetPolozenie());
        ui->tableWidget->setItem(i,0,item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setData(Qt::EditRole, magnes_load[i]->GetDlugosc());
        ui->tableWidget->setItem(i,1,item2);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setData(Qt::EditRole, magnes_load[i]->GetIndukcja());
        ui->tableWidget->setItem(i,2,item3);
        QTableWidgetItem *item4 = new QTableWidgetItem;
        item4->setText(QString::fromStdString(magnes_load[i]->Kto()));
        ui->tableWidget->setItem(i,3,item4);
    }
    ui->tableWidget->sortItems(0);
}

void wczytaj::on_BTNrevert_clicked()
{
    magnes_load.clear();
    magnes_load=magnes_vec;
    wczytaj::on_BTNshow_clicked();
    ui->statusbar->setText("Przywrócono zapisane magnesy.");
}
