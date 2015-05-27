#include "wczytaj.h"
#include "ui_wczytaj.h"
#include "dodaj.h"
#include "QToolTip"
#include "magnesy.h"

std::vector<magnes_ptr> magnes_vec;
std::vector<magnes_ptr> magnes_temp;

wczytaj::wczytaj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wczytaj)
{
    ui->setupUi(this);
    ui->pushButton->setToolTip("teraz czytasz opcje do przycisku wczytaj");
    ui->pushButton_2->setToolTip("teraz czytasz opcje do przycisku dodaj");
    ui->pushButton_3->setToolTip("teraz czytasz opcje do przycisku zapisz");
    ui->pushButton_4->setToolTip("teraz czytasz opcje do przycisku czysc");
    ui->pushButton_5->setToolTip("teraz czytasz opcje do przycisku wyjscie");
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
    QString filename = QFileDialog::getOpenFileName(this,tr("Otwórz"), "",tr("Pliki magnesów (*.mag)"));
    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    ifstream plik(filename.toUtf8().constData(),ios::in);
    magnes_temp = wczytajmagnesy(plik);
    magnes_vec = vappend(magnes_vec, magnes_temp);
    plik.close();

    wypiszmagnesy(magnes_vec);
}

void wczytaj::on_pushButton_2_clicked()
{
    dodaj dod;
    dod.setModal(true);
    dod.exec();
}

void wczytaj::on_pushButton_4_clicked()
{
    magnes_vec.clear();
    wypiszmagnesy(magnes_vec);
}
