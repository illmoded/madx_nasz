#include "dodaj.h"
#include "ui_dodaj.h"

Dodaj::Dodaj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dodaj)
{
    ui->setupUi(this);
}

Dodaj::~Dodaj()
{
    delete ui;
}

void Dodaj::on_buttonBox_accepted()
{
    this->close();
}

void Dodaj::on_buttonBox_rejected()
{
    this->close();
}
