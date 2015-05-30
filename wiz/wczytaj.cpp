#include "wczytaj.h"
#include "ui_wczytaj.h"
#include "dodaj.h"
#include "QToolTip"
#include "global.h"

std::vector<magnes_ptr> magnes_temp; //tymczasowa lista magnesów
std::vector<magnes_ptr> magnes_app; // magnesy wczytane, nie zapisane
// magnes_vec to magnesy zapiane, obiekt globalny, nie chciało mi się szukać jak inaczej przekazywać

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

void wczytaj::on_pushButton_5_clicked() // wyjście
{
    wypiszmagnesy(magnes_vec);
    this->close();
}

void wczytaj::on_pushButton_clicked() // wczytanie z pliku
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Otwórz"), "",tr("Pliki magnesów (*.mag)"));
    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    ifstream plik(filename.toUtf8().constData(),ios::in);
    magnes_temp = wczytajmagnesy(plik);
    magnes_app = vappend(magnes_app, magnes_temp);
    magnes_temp.clear();
    plik.close();

    wypiszmagnesy(magnes_app);
}

void wczytaj::on_pushButton_2_clicked() //dodanie pojedynczego
{
    dodaj dod;
    dod.setModal(true);
    dod.exec();
}

void wczytaj::on_pushButton_4_clicked() // czyszczenie wszystkich
{
    magnes_app.clear();
    magnes_vec.clear();
//    wypiszmagnesy(magnes_vec);
}

void wczytaj::on_pushButton_3_clicked() // zapis
{
    magnes_vec=vappend(magnes_vec,magnes_app);
    magnes_app.clear();
//    wypiszmagnesy(magnes_vec);
}

void wczytaj::on_BTNshow_clicked() // wypisz magnesy zapisane
{
    wypiszmagnesy(magnes_vec);
}
