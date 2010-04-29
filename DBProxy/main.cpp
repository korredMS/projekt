#include <QApplication>

#include "dbproxy.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    DBProxy db( NULL, "localhost", "Sklep", "root", "inutero" );
    db.polacz();

    QMap< DBProxy::Hurtownia::PoleBazy, QVariant > filtr;
    filtr.insert( DBProxy::Hurtownia::Id, 5 );
    QList< DBProxy::Hurtownia > hurtownie = db.pobierz< DBProxy::Hurtownia >( filtr );

    QList< DBProxy::TowarSklep > towary = db.pobierz< DBProxy::TowarSklep >();

    return app.exec();
}
