#include <QtGui/QApplication>
#include "hurtownia.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("ISO 8859-2"));
    OknoHurtownia w;
    w.show();
    return a.exec();
}
