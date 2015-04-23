#include "magnets.h"
#include "ui_magnets.h"

Magnets::Magnets(QWidget *parent) :
    QWidget(parent),
    ui2(new Ui::Magnets)
{
    ui2->setupUi(this);


    int rows, columns;
    rows = 7;
    columns = 4;
    model = new QStandardItemModel(rows,columns);
    ui2->tableView->setModel(model);

    for(int row=0; row<rows; row++)
    {
        for(int column=0; column<columns; column++)
        {
            QModelIndex index=model->index(row,column,QModelIndex());
            model->setHorizontalHeaderItem(0, new QStandardItem(QString("Placement")));
            model->setHorizontalHeaderItem(1, new QStandardItem(QString("Size")));
            model->setHorizontalHeaderItem(2, new QStandardItem(QString("Induction")));
            model->setHorizontalHeaderItem(3, new QStandardItem(QString("Moment")));
            model->setData(index,0);
        }
    }
}

Magnets::~Magnets()
{
    delete ui2;
}




void Magnets::on_BtnOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"), "",tr("TextFiles (*.txt)"));
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QFile contents = file.readAll();
}

