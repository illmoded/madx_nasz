#include "sdialog.h"
#include "ui_sdialog.h"
#include "dodaj.h"

sDialog::sDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sDialog)
{
    ui->setupUi(this);
}

sDialog::~sDialog()
{
    delete ui;
}

void sDialog::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "",tr("TextFiles (*.txt)"));
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        QStringList fields = line.split(".");
        QTextStream cout(stdout);
        cout << line<<endl;
        //cout << endl;
    }

    file.close();
}

void sDialog::on_pushButton_3_clicked()
{
    Dodaj dodaj;
    dodaj.setModal(true);
    dodaj.exec();
}

void sDialog::on_pushButton_4_clicked()
{
    this->close();
}

void sDialog::on_pushButton_2_clicked()
{
    this->close();
}
