#include "widget.h"
#include "ui_widget.h"
#include "ui_display.h"
#include "magnets.h"
#include "sdialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_BtnDisplay_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_BtnDrawing_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void Widget::on_BtnBack1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::on_BtnBack2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void Widget::on_pushButton_clicked()
{
    sDialog dialogs;
    dialogs.setModal(true);
    dialogs.exec();
}
