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
