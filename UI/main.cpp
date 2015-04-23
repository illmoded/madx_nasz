#include "widget.h"
#include "magnets.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Magnets mf;
    mf.show();
    return a.exec();
}
