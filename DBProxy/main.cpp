#include <QApplication>

#include "dbproxy.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    DBProxy db( NULL, "localhost", "hurtownia", "root", "" );
    db.polacz();


    return app.exec();
}
