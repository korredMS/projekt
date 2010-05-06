#include "dbproxy.h"

QStringList DBProxy::Hurtownia::polaBazy = QString( "id, regon, nazwa, upust, ulica, miejscowosc, kodPocztowy, telefon, fax, email" ).split( ", ");
QStringList DBProxy::Sklep::polaBazy = QString( "id, regon, nazwa, upust, login, haslo, ulica, miejscowosc, kodPocztowy, telefon, fax, email" ).split( ", " );
QStringList DBProxy::TowarHurtownia::polaBazy = QString( "id, nazwa, opis, cena, ilosc, vat" ).split( ", " );
QStringList DBProxy::TowarSklep::polaBazy = QString( "id, nazwa, opis, cena, ilosc, idKategorii, vat, cenaZakupu" ).split( ", " );
QStringList DBProxy::PozycjaZamowienia::polaBazy = QString( "id, idZamowienia, idTowaru, ilosc" ).split( ", " );
QStringList DBProxy::PozycjaSprzedazy::polaBazy = QString( "id, idSprzedazy, idTowaru, ilosc, cena, vat" ).split( ", " );
QStringList DBProxy::ZamowienieHurtownia::polaBazy = QString( "id, idSklepu, dataZlozenia, dataRealizacji, upust, status, nrFaktury" ).split( ", " );
QStringList DBProxy::ZamowienieSklep::polaBazy = QString( "id, idHurtowni, dataZlozenia, dataRealizacji, status, nrFaktury, idPracownika" ).split( ", " );
QStringList DBProxy::Sprzedaz::polaBazy = QString( "id, dataRealizacji, status, potwierdzenie, nrParagonu, idFaktury, idKlienta, idPracownika" ).split( ", " );
QStringList DBProxy::Faktura::polaBazy = QString( "id, nrFaktury" ).split( ", " );
QStringList DBProxy::Kategoria::polaBazy = QString( "id, nazwa" ).split( ", " );
QStringList DBProxy::Klient::polaBazy = QString( "id, regon, ulica, miejscowosc, kodPocztowy, telefon, nazwa" ).split( ", " );
QStringList DBProxy::Pracownik::polaBazy = QString( "id, nazwa, pesel, nip, posada, dataZatrudnienia, stawka, ulica, miejscowosc, kodPocztowy, telefon, email" ).split( ", " );

QStringList DBProxy::Rekord::polaUInt = QStringList() << "id" << "ilosc" << "idKategorii" << "idZamowienia"
                                                      << "idTowaru" << "idSprzedazy" << "idSklepu" << "idHurtowni"
                                                      << "idPracownika" << "idKlienta";
QStringList DBProxy::Rekord::polaQDate = QStringList() << "dataZlozenia" << "dataRealizacji";
QStringList DBProxy::Rekord::polaFloat = QStringList() << "upust" << "cena" << "cenaZakupu";
QStringList DBProxy::Rekord::polaEnum = QStringList() << "vat" << "status" << "potwierdzenie" << "posada";

QString DBProxy::Hurtownia::tabela = "Hurtownia";
QString DBProxy::Sklep::tabela = "Sklep";
QString DBProxy::TowarHurtownia::tabela = "Towar";
QString DBProxy::TowarSklep::tabela = "Towar";
QString DBProxy::PozycjaZamowienia::tabela = "Pozycja_zamowienia";
QString DBProxy::PozycjaSprzedazy::tabela = "Pozycja_sprzedazy";
QString DBProxy::ZamowienieHurtownia::tabela = "Zamowienie";
QString DBProxy::ZamowienieSklep::tabela = "Zamowienie";
QString DBProxy::Sprzedaz::tabela = "Sprzedaz";
QString DBProxy::Faktura::tabela = "Faktura";
QString DBProxy::Kategoria::tabela = "Kategoria";
QString DBProxy::Klient::tabela = "Klient";
QString DBProxy::Pracownik::tabela = "Pracownik";

DBProxy::DBProxy(QObject *parent, const QString &host, const QString &dbName,
                 const QString &login, const QString &pass) :
    QObject(parent),
    dodawanie( false ),
    mBladDodawaniaRekordu( false )
{
    db = QSqlDatabase::addDatabase( "QMYSQL", dbName );
    db.setHostName( host );
    db.setDatabaseName( dbName );
    db.setUserName( login );
    db.setPassword( pass );

    connect( this, SIGNAL(log(QString)), this, SLOT(debug(QString)));
}

bool DBProxy::polacz()
{
    if( db.open() )
        return true;

    emit log( db.lastError().text() );
    return false;
}

unsigned int DBProxy::dodajTowarHurtownia(const TowarHurtownia &towar )
{
    QString queryString = QString( "INSERT INTO Towar (id, nazwa, opis, cena, ilosc, vat)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5);" )
            .arg( nawiasy( towar.nazwa ) )
            .arg( nawiasy( towar.opis ) )
            .arg( liczbaNaString( towar.cena ) )
            .arg( liczbaNaString( towar.ilosc ) )
            .arg( nawiasy( liczbaNaString( towar.vat ) ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajTowarSklep(const TowarSklep &towar)
{
    QString queryString = QString( "INSERT INTO Towar (id, Nazwa, opis, cena, ilosc, idKategorii, stawkaVAT, cenaZakupu)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6, %7);" )
            .arg( nawiasy( towar.nazwa ) )
            .arg( nawiasy( towar.opis ) )
            .arg( liczbaNaString( towar.cena ) )
            .arg( liczbaNaString( towar.ilosc ) )
            .arg( liczbaNaString( towar.idKategorii ) )
            .arg( nawiasy( liczbaNaString( towar.vat ) ) )
            .arg( liczbaNaString( towar.cenaZakupu ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajSklep(const Sklep &sklep)
{
    QString queryString = QString( "INSERT INTO Sklep (id, regon, nazwa, upust, login, haslo,"
                                   "ulica, miejscowosc, kodPocztowy, telefon, fax, email)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11);" )
            .arg( nawiasy( sklep.REGON ) )
            .arg( nawiasy( sklep.nazwa ) )
            .arg( liczbaNaString( sklep.upust ) )
            .arg( nawiasy( sklep.login ) )
            .arg( nawiasy( sklep.haslo ) )
            .arg( nawiasy( sklep.ulica ) )
            .arg( nawiasy( sklep.miejscowosc ) )
            .arg( nawiasy( sklep.kodPocztowy ) )
            .arg( nawiasy( sklep.telefon ) )
            .arg( nawiasy( sklep.fax ) )
            .arg( nawiasy( sklep.email ) );

    return execQuery( queryString ).toUInt();
}

QVariant DBProxy::execQuery(const QString &queryString, QSqlQuery *argQuery )
{
    if( dodawanie && mBladDodawaniaRekordu )
        return 0;

    QSqlQuery *query = argQuery;
    if( !query )
        query = new QSqlQuery( db );

    if( !query->exec( queryString ) ) {
        emit log( query->lastError().text() );

        if( dodawanie ) {
            mBladDodawaniaRekordu = true;
            emit bladDodawaniaRekordu();    // czy przekazywac cos?
        }

        if( query->isSelect() )
            return false;

        return 0;
    }

    if( query->isSelect() ) {
        if( !argQuery )
            delete query;

        return true;

    } else {
        unsigned int id = query->lastInsertId().toUInt();

        if( !argQuery )
            delete query;

        return id;
    }
}

QString DBProxy::nawiasy(const QString &string)
{
    return "'" + string + "'";
}

QString DBProxy::liczbaNaString(double liczba)
{
    return QString::number( liczba );
}

unsigned int DBProxy::dodajZamowienieHurtownia(const ZamowienieHurtownia &zamowienie) {
    QString queryString = QString( "INSERT INTO Zamowienie (id, idSklepu, dataZlozenia, dataRealizacji, upust, status,"
                                   "nrFaktury)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6);" )
            .arg( liczbaNaString( zamowienie.idSklepu ) )
            .arg( nawiasy( dataNaString( zamowienie.dataZlozenia ) ) )
            .arg( nawiasy( dataNaString( zamowienie.dataRealizacji ) ) )
            .arg( liczbaNaString( zamowienie.upust ) )
            .arg( nawiasy( statusNaString( zamowienie.status) ) )
            .arg( nawiasy( zamowienie.nrFaktury ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajZamowienieSklep(const ZamowienieSklep &zamowienie) {
    QString queryString = QString( "INSERT INTO Zamowienie (id, idHurtowni, dataZlozenia, dataRealizacji, status,"
                                   "nrFaktury, idPracownika)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6);" )
            .arg( liczbaNaString( zamowienie.idHurtowni ) )
            .arg( nawiasy( dataNaString( zamowienie.dataZlozenia ) ) )
            .arg( nawiasy( dataNaString( zamowienie.dataRealizacji ) ) )
            .arg( nawiasy( statusNaString( zamowienie.status ) ) )
            .arg( nawiasy( zamowienie.nrFaktury ) )
            .arg( liczbaNaString( zamowienie.idPracownika ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajPozycjeZamowienia(const PozycjaZamowienia &pozycja)
{
    QString queryString = QString( "INSERT INTO Pozycja_zamowienia (id, idZamowienia, idTowaru, ilosc)"
                                   "VALUES (NULL, %1, %2, %3);" )
            .arg( liczbaNaString( pozycja.idZamowienia ) )
            .arg( liczbaNaString( pozycja.idTowaru ) )
            .arg( liczbaNaString( pozycja.ilosc ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajPozycjeSprzedazy(const PozycjaSprzedazy &pozycja)
{
    QString queryString = QString( "INSERT INTO PozycjaSprzedazy (id, idSprzedazy, idTowaru, ilosc, cena, stawkaVAT)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5);" )
            .arg( liczbaNaString( pozycja.idSprzedazy ) )
            .arg( liczbaNaString( pozycja.idTowaru ) )
            .arg( liczbaNaString( pozycja.ilosc ) )
            .arg( liczbaNaString( pozycja.cena ) )
            .arg( liczbaNaString( pozycja.vat ) );

    return execQuery( queryString ).toUInt();
}

QString DBProxy::statusNaString(StatusZamowienia status)
{
    switch( status ) {
        case Oczekujace:    return "Oczekujace";
        case Anulowane:     return "Anulowane";
        case Zrealizowane:  return "Zrealizowane";
        default:            return QString();
    }
}

QString DBProxy::posadaNaString(Posada posada)
{
    switch( posada ) {
        case Kierownik:     return "Kierownik";
        case Sprzedawca:    return "Sprzedawca";
        case Magazynier:    return "Magazynier";
        default:            return QString();
    }
}

unsigned int DBProxy::dodajFakture(const Faktura &faktura)
{
    QString queryString = QString( "INSERT INTO Faktura (id, nrFaktury)"
                                   "VALUES (NULL, %1);" )
            .arg( nawiasy( faktura.nr ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajKategorie(const Kategoria &kategoria)
{
    QString queryString = QString( "INSERT INTO Kategoria (id, nazwa)"
                                   "VALUES (NULL, %1);" )
            .arg( nawiasy( kategoria.nazwa ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajHurtownie(const Hurtownia &hurtownia)
{
    QString queryString = QString( "INSERT INTO Hurtownia (id, regon, nazwa, upust,"
                                   "ulica, miejscowosc, kodPocztowy, telefon, fax, email)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6, %7, %8, %9);" )
            .arg( nawiasy( hurtownia.REGON ) )
            .arg( nawiasy( hurtownia.nazwa ) )
            .arg( liczbaNaString( hurtownia.upust ) )
            .arg( nawiasy( hurtownia.ulica ) )
            .arg( nawiasy( hurtownia.miejscowosc ) )
            .arg( nawiasy( hurtownia.kodPocztowy ) )
            .arg( nawiasy( hurtownia.telefon ) )
            .arg( nawiasy( hurtownia.fax ) )
            .arg( nawiasy( hurtownia.email ) );

    return execQuery( queryString ).toUInt();
}

unsigned int DBProxy::dodajPracownika(const Pracownik &pracownik)
{
    QString queryString = QString( "INSERT INTO Pracownik (id, nazwisko, PESEL, NIP,"
                                   "posada, dataZatrudnienia, stawka, ulica, miejscowosc, kodPocztowy,"
                                   "telefon, email)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11);" )
            .arg( nawiasy( pracownik.nazwa ) )
            .arg( nawiasy( pracownik.pesel ) )
            .arg( nawiasy( pracownik.nip ) )
            .arg( nawiasy( posadaNaString( pracownik.posada ) ) )
            .arg( nawiasy( dataNaString( pracownik.dataZatrudnienia ) ) )
            .arg( liczbaNaString( pracownik.stawka ) )
            .arg( nawiasy( pracownik.ulica ) )
            .arg( nawiasy( pracownik.miejscowosc ) )
            .arg( nawiasy( pracownik.kodPocztowy ) )
            .arg( nawiasy( pracownik.telefon ) )
            .arg( nawiasy( pracownik.email ) );

    return execQuery( queryString ).toUInt();
}

QString DBProxy::dataNaString(const QDate &data)
{
    return data.toString( Qt::ISODate );
}

unsigned int DBProxy::dodajKlienta(const Klient &klient)
{
    QString queryString = QString( "INSERT INTO Klient (id, regon, ulica, miejscowosc,"
                                   "kodPocztowy, telefon, nazwa)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6);" )
            .arg( nawiasy( klient.regon ) )
            .arg( nawiasy( klient.ulica ) )
            .arg( nawiasy( klient.miejscowosc ) )
            .arg( nawiasy( klient.kodPocztowy ) )
            .arg( nawiasy( klient.telefon ) )
            .arg( nawiasy( klient.nazwa ) );

    return execQuery( queryString ).toUInt();
}


unsigned int DBProxy::dodajSprzedaz(const Sprzedaz &sprzedaz) {
    QString queryString = QString( "INSERT INTO Sprzedaz (id, dataRealizacji, status, potwierdzenie, nrParagonu,"
                                   "idFaktury, idKlienta, idPracownika)"
                                   "VALUES (NULL, %1, %2, %3, %4, %5, %6, %7);" )
            .arg( nawiasy( dataNaString( sprzedaz.dataRealizacji ) ) )
            .arg( nawiasy( statusNaString( sprzedaz.status ) ) )
            .arg( nawiasy( potwierdzenieNaString( sprzedaz.potwierdzenie ) ) )
            .arg( nawiasy( sprzedaz.nrParagonu ) )
            .arg( liczbaNaString( sprzedaz.idFaktury ) )
            .arg( liczbaNaString( sprzedaz.idKlienta ) )
            .arg( liczbaNaString( sprzedaz.idPracownika ) );

    return execQuery( queryString ).toUInt();
}

QString DBProxy::potwierdzenieNaString(Potwierdzenie potwierdzenie)
{
    switch( potwierdzenie ) {
        case PotwierdzenieParagon:  return "Paragon";
        case PotwierdzenieFaktura:  return "Faktura";
        default:                    return QString();
    }
}

void DBProxy::debug(QString str)
{
    qDebug() << str;
}

void DBProxy::rozpocznijDodawanie()
{
    dodawanie = true;
    mBladDodawaniaRekordu = false;
}

void DBProxy::zakonczDodawanie()
{
    dodawanie = false;

    foreach( Rekord *rekord, aktualnieDodawaneRekordy ) {
        usunRekord( rekord );
    }

    aktualnieDodawaneRekordy.clear();
}

void DBProxy::usunRekord(const Rekord *rekord)
{
    QString queryString = QString( "DELETE FROM %1 WHERE id=%2;" )
                          .arg( rekord->tabela )
                          .arg( rekord->id );
    execQuery( queryString );
}

QString DBProxy::vatNaString(StawkaVAT vat)
{
    switch( vat ) {
        case VAT0:  return "VAT0";
        case VAT3:  return "VAT3";
        case VAT7:  return "VAT7";
        case VAT14:  return "VAT14";
        case VAT22:  return "VAT22";
    }

    return QString();
}

QString DBProxy::relacjaNaString( DBProxy::Relacja relacja){
    switch( relacja ) {
        case Rowne:         return " = ";
        case Wieksze:       return " > ";
        case WiekszeRowne:  return " >= ";
        case Mniejsze:      return " < ";
        case MniejszeRowne: return " <= ";
        case Zawiera:       return " LIKE ";
        default:            return " = ";
    }
}

DBProxy::StawkaVAT DBProxy::stringNaVat(const QString &string)
{
    if( string == "VAT0" )
        return VAT0;

    // domyœlnie
    return VAT0;
}

DBProxy::Posada DBProxy::stringNaPosade(const QString &string)
{
    if( string == "Kierownik" )
        return Kierownik;

    if( string == "Sprzedawca" )
        return Sprzedawca;

    if( string == "Magazynier" )
        return Magazynier;

    // domyœlnie
    return Sprzedawca;
}
