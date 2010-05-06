#include <QApplication>

#include "dbproxy.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    DBProxy db( NULL, "localhost", "Sklep", "root", "" );
    db.polacz();
//
//    QMap< DBProxy::Hurtownia::PoleBazy, QVariant > filtr;
//    filtr.insert( DBProxy::Hurtownia::Id, 7 );
//    QList< DBProxy::Hurtownia > hurtownie = db.pobierz< DBProxy::Hurtownia >( filtr );
//    qDebug() << hurtownie[0].nazwa;
//    qDebug() << hurtownie[ 0 ].tabela;
//    qDebug() << hurtownie[ 0 ].upust;
//    qDebug() << hurtownie[ 0 ].id;

//    QList< DBProxy::TowarSklep > towary = db.pobierz< DBProxy::TowarSklep >();

    QList< DBProxy::Pracownik > pracownicy = db.pobierz< DBProxy::Pracownik >();


    return app.exec();
}
