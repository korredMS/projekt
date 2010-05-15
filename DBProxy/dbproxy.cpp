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
QStringList DBProxy::Pracownik::polaBazy = QString( "id, nazwa, pesel, nip, posada, dataZatrudnienia, stawka, ulica, miejscowosc, kodPocztowy, telefon, email, haslo" ).split( ", " );

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

QString DBProxy::dataNaString(const QDate &data)
{
    return data.toString( Qt::ISODate );
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

DBProxy::StatusZamowienia DBProxy::stringNaStatus(const QString &string)
{
    if( string == "Oczekujace" )
        return Oczekujace;

    if( string == "Anulowane" )
        return Anulowane;

    if( string == "Zrealizowane" )
        return Zrealizowane;

    // domyœlnie
    return Oczekujace;
}

DBProxy::Potwierdzenie DBProxy::stringNaPotwierdzenie(const QString &string)
{
    if( string == "Paragon" )
        return PotwierdzenieParagon;

    if( string == "Faktura" )
        return PotwierdzenieFaktura;

    // domyœlnie
    return PotwierdzenieFaktura;
}
