#include <QApplication>

#include "dbproxy.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    DBProxy db( NULL, "localhost", "Sklep", "root", "inutero" );
    db.polacz();

    DBProxy::Kategoria kategoria( "kategoria" );
    unsigned int idKategorii = db.dodajKategorie( kategoria );

    DBProxy::TowarSklep towar( "myszki", "myszki", 1, 1, DBProxy::VAT3, 1, 1);
    db.dodajTowarSklep( towar );

    return app.exec();
}
