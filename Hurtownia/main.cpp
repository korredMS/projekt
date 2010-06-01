#include <QtGui/QApplication>
#include "hurtownia.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OknoHurtownia w;
    w.show();
    return a.exec();
}
