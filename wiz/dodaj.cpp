#include "dodaj.h"
#include "ui_dodaj.h"

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
