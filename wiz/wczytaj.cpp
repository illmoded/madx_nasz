#include "wczytaj.h"
#include "ui_wczytaj.h"
#include "dodaj.h"



wczytaj::wczytaj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wczytaj)
{
    ui->setupUi(this);
}

wczytaj::~wczytaj()
{
    delete ui;
}

void wczytaj::on_pushButton_5_clicked()
{
    this->close();
}

void wczytaj::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "",tr("TextFiles (*.cpp)"));
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream in(&file);
    while (!in.atEnd()){
        QString line = in.readLine();
        QStringList fields = line.split(".");
        QTextStream cout(stdout);
        cout << line<<endl;
    }

}

void wczytaj::on_pushButton_2_clicked()
{
    dodaj dod;
    dod.setModal(true);
    dod.exec();
}
