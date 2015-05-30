#include "dodaj.h"
#include "ui_dodaj.h"
#include "global.h"

std::vector<magnes_ptr> magnes_t1;
std::vector<magnes_ptr> magnes_t2;

dodaj::dodaj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodaj)
{
    ui->setupUi(this);
}

dodaj::~dodaj()
{
    delete ui;
}

void dodaj::on_radioButton_clicked(bool checked)
{
    ui->groupBox_2->setDisabled(false);
}

void dodaj::on_radioButton_2_clicked(bool checked)
{
    ui->groupBox_2->setDisabled(true);
}

void dodaj::on_BTNappend_clicked() // Dodaj
{
    double l=ui->lineEdit->text().toDouble();
    double d=ui->lineEdit_2->text().toDouble();
    double i=ui->lineEdit_3->text().toDouble();
    double m;
    if(ui->radioButton->isChecked()) m=4;
    else if(ui->radioButton_2->isChecked()) m=2;
    magnes_t1=wczytajjeden(l, d, i, m);
    magnes_t2=vappend(magnes_t2,magnes_t1);
    magnes_t1.clear();
    m=0;
}

void dodaj::on_BTNsave_clicked() //Zapisz i wyjdź
{
    magnes_vec=vappend(magnes_vec,magnes_t2);
    magnes_t2.clear();
    this->close();
}

void dodaj::on_BTNdiscard_clicked() //Wyjdź bez zapisu
{
    this->close();
}
