/********************************************************************************
** Form generated from reading UI file 'wczytaj.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WCZYTAJ_H
#define UI_WCZYTAJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_wczytaj
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QDialog *wczytaj)
    {
        if (wczytaj->objectName().isEmpty())
            wczytaj->setObjectName(QStringLiteral("wczytaj"));
        wczytaj->resize(591, 343);
        pushButton = new QPushButton(wczytaj);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(480, 20, 80, 23));
        pushButton_2 = new QPushButton(wczytaj);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(480, 50, 80, 23));
        pushButton_3 = new QPushButton(wczytaj);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(480, 80, 80, 23));
        pushButton_4 = new QPushButton(wczytaj);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(480, 110, 80, 23));
        pushButton_5 = new QPushButton(wczytaj);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(480, 140, 80, 23));

        retranslateUi(wczytaj);

        QMetaObject::connectSlotsByName(wczytaj);
    } // setupUi

    void retranslateUi(QDialog *wczytaj)
    {
        wczytaj->setWindowTitle(QApplication::translate("wczytaj", "Dialog", 0));
        pushButton->setText(QApplication::translate("wczytaj", "Przegl\304\205daj", 0));
        pushButton_2->setText(QApplication::translate("wczytaj", "Dodaj", 0));
        pushButton_3->setText(QApplication::translate("wczytaj", "Zapisz", 0));
        pushButton_4->setText(QApplication::translate("wczytaj", "Wyczy\305\233\304\207", 0));
        pushButton_5->setText(QApplication::translate("wczytaj", "Wyjd\305\272", 0));
    } // retranslateUi

};

namespace Ui {
    class wczytaj: public Ui_wczytaj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WCZYTAJ_H
