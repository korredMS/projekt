#ifndef DBPROXY_H
#define DBPROXY_H

#include <QtSql>

#include <QObject>

class DBProxy : public QObject
{
    Q_OBJECT
public:
    // klasy i enumeracje pomocnicze
    enum StawkaVAT {
        VAT0,
        VAT3 = 3,
        VAT7 = 7,
        VAT14 = 14,
        VAT22 = 22
    };

    enum StatusZamowienia {
        Oczekujace,
        Anulowane,
        Zrealizowane
    };

    enum Posada {
        Kierownik,
        Sprzedawca,
        Magazynier
    };

    enum Potwierdzenie {
        PotwierdzenieParagon,
        PotwierdzenieFaktura
    };

    struct Hurtownia {
        Hurtownia( const QString &nazwa, const QString &regon, const QString &ulica, const QString &miejscowosc,
                   const QString &kodPocztowy, const QString &telefon, const QString &fax, const QString &email,
                   float upust = 0, unsigned int id = 0 ) {
            this->nazwa = nazwa;
            this->REGON = regon;
            this->ulica = ulica;
            this->miejscowosc = miejscowosc;
            this->kodPocztowy = kodPocztowy;
            this->telefon = telefon;
            this->fax = fax;
            this->email = email;
            this->id = id;
            this->upust = upust;
        }

        QString nazwa, REGON, ulica, miejscowosc, kodPocztowy, telefon, fax, email;
        float upust;
        unsigned int id;
    };

    struct Sklep : public Hurtownia {
        Sklep( const QString &nazwa, const QString &regon, const QString &ulica,
               const QString &miejscowosc, const QString &kodPocztowy, const QString &telefon,
               const QString &fax, const QString &email, const QString &login,
               const QString &haslo, float upust = 0, unsigned int id = 0 )
                   : Hurtownia( nazwa, regon, ulica, miejscowosc, kodPocztowy, telefon, fax,
                                email, upust, id ) {
            this->login = login;
            this->haslo = haslo;
        }

        QString login, haslo;
    };

    struct Towar {
        Towar( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
               StawkaVAT vat, unsigned int id = 0 ) {
            this->nazwa = nazwa;
            this->opis = opis;
            this->ilosc = ilosc;
            this->cena = cena;
            this->vat = vat;
            this->id = id;
        }

        QString nazwa, opis;
        size_t ilosc;
        float cena;
        StawkaVAT vat;
        unsigned int id;
    };

    struct TowarHurtownia : public Towar {
        TowarHurtownia( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
                        StawkaVAT vat, unsigned int id = 0 )
                            : Towar( nazwa, opis, ilosc, cena, vat, id )
        {
        }
    };

    struct TowarSklep : public Towar {
        TowarSklep( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
                    StawkaVAT vat, float cenaZakupu, unsigned int id = 0 )
                            : Towar( nazwa, opis, ilosc, cena, vat, id )
        {
            this->cenaZakupu = cenaZakupu;
        }
        float cenaZakupu;
    };

    struct Pozycja {
        Pozycja( unsigned int idTowaru, size_t ilosc, unsigned int id = 0 ) {
            this->idTowaru = idTowaru;
            this->ilosc = ilosc;
            this->id = id;
        }

        unsigned int id, idTowaru;
        size_t ilosc;
    };

    struct PozycjaZamowienia : public Pozycja {
        PozycjaZamowienia( unsigned int idTowaru, size_t ilosc, unsigned int idZamowienia,
                           unsigned int id = 0 )
                               : Pozycja( idTowaru, ilosc, id ) {
            this->idZamowienia = idZamowienia;
        }

        unsigned int idZamowienia;
    };

    struct PozycjaSprzedazy : public Pozycja {
        PozycjaSprzedazy( unsigned int idTowaru, size_t ilosc, unsigned int idSprzedazy,
                          float cena, StawkaVAT vat, unsigned int id = 0 )
                               : Pozycja( idTowaru, ilosc, id ) {
            this->idSprzedazy = idSprzedazy;
            this->cena = cena;
            this->vat = vat;
        }

        unsigned int idSprzedazy;
        float cena;
        StawkaVAT vat;
    };

    struct Transakcja {
        Transakcja( const QDate dataRealizacji = QDate(), float upust = 0.0,
                    StatusZamowienia status = Oczekujace, unsigned int id = 0 ) {
            this->dataRealizacji = dataRealizacji;
            this->upust = upust;
            this->status = status;
            this->id = id;
        }

        unsigned int id;
        QDate dataRealizacji;
        float upust;
        StatusZamowienia status;
    };

    struct ZamowienieHurtownia : public Transakcja {
        ZamowienieHurtownia( unsigned int idSklepu, const QDate dataZlozenia,
                             const QString &nrFaktury, const QDate dataRealizacji = QDate(), float upust = 0.0,
                             StatusZamowienia status = Oczekujace, unsigned int id = 0 )
                                 : Transakcja( dataRealizacji, upust, status, id ) {
            this->idSklepu = idSklepu;
            this->dataZlozenia = dataZlozenia;
            this->nrFaktury = nrFaktury;
        }

        unsigned int idSklepu;
        QDate dataZlozenia;
        QString nrFaktury;
    };

    struct ZamowienieSklep : public Transakcja {
        ZamowienieSklep( unsigned int idHurtowni, unsigned int idPracownika, const QDate dataZlozenia,
                         const QString &nrFaktury, const QDate dataRealizacji = QDate(), float upust = 0.0,
                         StatusZamowienia status = Oczekujace, unsigned int id = 0 )
            : Transakcja( dataRealizacji, upust, status, id ) {
            this->idHurtowni = idHurtowni;
            this->idPracownika = idPracownika;
            this->nrFaktury = nrFaktury;
            this->dataZlozenia = dataZlozenia;
        }
        unsigned int idPracownika, idHurtowni;
        QDate dataZlozenia;
        QString nrFaktury;
    };

    struct Sprzedaz : public Transakcja {
        Sprzedaz( unsigned int idPracownika, unsigned int idKlienta, unsigned int idFaktury,
                  const QString &nrParagonu, Potwierdzenie potwierdzenie,
                  const QDate dataRealizacji = QDate(), float upust = 0.0,
                  StatusZamowienia status = Oczekujace, unsigned int id = 0 )
            : Transakcja( dataRealizacji, upust, status, id ) {
            this->potwierdzenie = potwierdzenie;
            this->nrParagonu = nrParagonu;
            this->idFaktury = idFaktury;
            this->idKlienta = idKlienta;
            this->idPracownika = idPracownika;
        }

        Potwierdzenie potwierdzenie;
        QString nrParagonu;
        unsigned int idFaktury, idKlienta, idPracownika;
    };

    struct Faktura {
        Faktura( const QString &nr, unsigned int id = 0 ) {
            this->nr = nr;
            this->id = id;
        }

        unsigned int id;
        QString nr;
    };

    struct Kategoria {
        Kategoria( const QString &nazwa, unsigned int id = 0 ) {
            this->nazwa = nazwa;
            this->id = id;
        }

        unsigned int id;
        QString nazwa;
    };

    struct Czlowiek {
        Czlowiek( const QString &nazwa, const QString &ulica, const QString &miejscowosc,
                  const QString &kodPocztowy, const QString &telefon, const QString &email,
                  unsigned int id = 0 ) {
            this->nazwa = nazwa;
            this->ulica = ulica;
            this->miejscowosc = miejscowosc;
            this->kodPocztowy = kodPocztowy;
            this->telefon = telefon;
            this->email = email;
            this->id = id;
        }

        unsigned int id;
        QString nazwa, ulica, miejscowosc, kodPocztowy, telefon, email;
    };

    struct Klient : public Czlowiek {
        Klient( const QString &regon, const QString &nazwa, const QString &ulica, const QString &miejscowosc,
                const QString &kodPocztowy, const QString &telefon, const QString &email,
                unsigned int id = 0 )
                    : Czlowiek( nazwa, ulica, miejscowosc, kodPocztowy, telefon, email, id ) {
            this->regon = regon;
        }

        QString regon;
    };

    struct Pracownik : public Czlowiek {
        Pracownik( const QString &pesel, const QString &nip, const QString &nazwa,
                   Posada posada, const QDate dataZatrudnienia, float stawka,
                   const QString &ulica, const QString &miejscowosc,
                   const QString &kodPocztowy, const QString &telefon, const QString &email,
                   const QString &login, const QString &haslo,
                   unsigned int id = 0 )
                    : Czlowiek( nazwa, ulica, miejscowosc, kodPocztowy, telefon, email, id ) {
            this->pesel = pesel,
            this->nip = nip;
            this->nazwa = nazwa;
            this->posada = posada;
            this->dataZatrudnienia = dataZatrudnienia;
            this->stawka = stawka;
            this->login = login;
            this->haslo = haslo;
        }

        QString pesel, nip, login, haslo;
        Posada posada;
        QDate dataZatrudnienia;
        float stawka;
    };

    // deklaracja klasy
    explicit DBProxy( QObject *parent, const QString &host, const QString &dbName,
                      const QString &login, const QString &pass);

    bool polacz();

    QSqlDatabase baza() {
        return db;
    }

    bool dodajFakture( const Faktura &faktura );
    bool dodajHurtownie( const Hurtownia &hurtownia );
    bool dodajKategorie( const Kategoria &kategoria );
    bool dodajKlienta( const Klient &klient );
    bool dodajPozycjeSprzedazy( const PozycjaSprzedazy &pozycja );
    bool dodajPozycjeZamowienia( const PozycjaZamowienia &pozycja );
    bool dodajPracownika( const Pracownik &pracownik );
    bool dodajSklep( const Sklep &sklep );
    bool dodajSprzedaz( const Sprzedaz &sprzedaz );
    bool dodajTowarHurtownia( const TowarHurtownia &towar );
    bool dodajTowarSklep( const TowarSklep &towar );
    bool dodajZamowienieHurtownia( const ZamowienieHurtownia &zamowienie );
    bool dodajZamowienieSklep( const ZamowienieSklep &zamowienie );

signals:
    void log( QString str );

public slots:

private:
    QString dataNaString( const QDate &data );
    bool execQuery( const QString &query );
    QString liczbaNaString( double liczba );
    QString nawiasy( const QString &string );
    QString posadaNaString( Posada posada );
    QString potwierdzenieNaString( Potwierdzenie potwierdzenie );
    QString statusNaString( StatusZamowienia status );

    QSqlDatabase db;

private slots:
    void debug( QString str );
};

#endif // DBPROXY_H
