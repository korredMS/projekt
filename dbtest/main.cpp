#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->addLibraryPath( "/usr/lib64/qt4/plugins/sqldrivers" );
    MainWindow w;
    w.show();
    return a.exec();
}
