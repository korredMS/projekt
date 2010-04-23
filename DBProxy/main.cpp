#include <QApplication>

#include "dbproxy.h"

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    DBProxy db( NULL, "localhost", "hurtownia", "root", "" );
    db.polacz();

    DBProxy::TowarHurtownia towar;
    towar.nazwa = "testowy produkt";
    towar.cena = 666;
    towar.ilosc = 100;
    towar.opis = "opis";
    towar.vat = DBProxy::VAT0;

    db.dodajTowarHurtownia( towar );

    DBProxy::ZamowienieHurtownia zamowienie;
    zamowienie.dataZlozenia = QDate::currentDate();
    zamowienie.idSklepu = 1;

//    db.dodajZamowienieHurtownia( zamowienie );

    DBProxy::Sklep sklep;
    sklep.nazwa = "super duper mart";

//    db.dodajSklep( sklep );

    DBProxy::PozycjaZamowienia pozycja;
    pozycja.idZamowienia = 2;
    pozycja.idTowaru = 1;
    pozycja.ilosc = 33;

//    db.dodajPozycjeZamowienia( pozycja );

    return app.exec();
}
