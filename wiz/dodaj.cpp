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
