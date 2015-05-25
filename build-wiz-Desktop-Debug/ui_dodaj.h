/********************************************************************************
** Form generated from reading UI file 'dodaj.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DODAJ_H
#define UI_DODAJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_dodaj
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;

    void setupUi(QDialog *dodaj)
    {
        if (dodaj->objectName().isEmpty())
            dodaj->setObjectName(QStringLiteral("dodaj"));
        dodaj->resize(515, 281);
        buttonBox = new QDialogButtonBox(dodaj);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(80, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(dodaj);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 50, 113, 23));
        lineEdit_2 = new QLineEdit(dodaj);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(20, 110, 113, 23));
        comboBox = new QComboBox(dodaj);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(30, 170, 91, 23));
        label = new QLabel(dodaj);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 71, 16));
        label_2 = new QLabel(dodaj);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 80, 71, 16));
        label_3 = new QLabel(dodaj);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 10, 111, 16));
        label_4 = new QLabel(dodaj);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 140, 59, 15));
        groupBox = new QGroupBox(dodaj);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(210, 30, 171, 71));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(10, 20, 100, 21));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 50, 100, 21));
        groupBox_2 = new QGroupBox(dodaj);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(210, 110, 161, 71));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(10, 20, 100, 21));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(10, 50, 100, 21));

        retranslateUi(dodaj);
        QObject::connect(buttonBox, SIGNAL(accepted()), dodaj, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dodaj, SLOT(reject()));

        QMetaObject::connectSlotsByName(dodaj);
    } // setupUi

    void retranslateUi(QDialog *dodaj)
    {
        dodaj->setWindowTitle(QApplication::translate("dodaj", "Dialog", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("dodaj", "W\305\202\304\205czony", 0)
         << QApplication::translate("dodaj", "Wy\305\202\304\205czony", 0)
        );
        label->setText(QApplication::translate("dodaj", "Odleg\305\202o\305\233\304\207", 0));
        label_2->setText(QApplication::translate("dodaj", "Moc", 0));
        label_3->setText(QApplication::translate("dodaj", "Rodzaj magnesu", 0));
        label_4->setText(QApplication::translate("dodaj", "Status", 0));
        groupBox->setTitle(QApplication::translate("dodaj", "GroupBox", 0));
        radioButton->setText(QApplication::translate("dodaj", "typ 1", 0));
        radioButton_2->setText(QApplication::translate("dodaj", "typ 2", 0));
        groupBox_2->setTitle(QApplication::translate("dodaj", "GroupBox", 0));
        radioButton_3->setText(QApplication::translate("dodaj", "roz", 0));
        radioButton_4->setText(QApplication::translate("dodaj", "sku", 0));
    } // retranslateUi

};

namespace Ui {
    class dodaj: public Ui_dodaj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DODAJ_H
