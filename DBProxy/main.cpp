#include <QApplication>

#include "dbproxy.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    DBProxy db( NULL, "localhost", "Hurtownia", "root", "inutero" );
    db.polacz();

    DBProxy::TowarHurtownia towar( "asdfg towar", "opis", 333, 34.4, DBProxy::VAT0 );
    db.dodajTowarHurtownia( towar );

    return app.exec();
}
