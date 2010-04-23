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

    struct Rekord {
        Rekord( const QString &tabela, unsigned int id = 0 ) {
            this->id = id;
            this->tabela = tabela;
        }

        unsigned int id;
        QString tabela;
    };

    struct Hurtownia : public Rekord {
        Hurtownia( const QString &nazwa, const QString &regon, const QString &ulica, const QString &miejscowosc,
                   const QString &kodPocztowy, const QString &telefon, const QString &fax, const QString &email,
                   float upust = 0, unsigned int id = 0 )
                       : Rekord( "Hurtownia", id )
        {
            this->nazwa = nazwa;
            this->REGON = regon;
            this->ulica = ulica;
            this->miejscowosc = miejscowosc;
            this->kodPocztowy = kodPocztowy;
            this->telefon = telefon;
            this->fax = fax;
            this->email = email;
            this->upust = upust;
        }

        QString nazwa, REGON, ulica, miejscowosc, kodPocztowy, telefon, fax, email;
        float upust;
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

    struct Towar : public Rekord {
        Towar( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
               StawkaVAT vat, unsigned int id = 0 )
                   : Rekord( "Towar", id )
        {
            this->nazwa = nazwa;
            this->opis = opis;
            this->ilosc = ilosc;
            this->cena = cena;
            this->vat = vat;
        }

        QString nazwa, opis;
        size_t ilosc;
        float cena;
        StawkaVAT vat;
    };

    struct TowarHurtownia : public Towar {
        TowarHurtownia( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
                        StawkaVAT vat, unsigned int id = 0 )
                            : Towar( nazwa, opis, ilosc, cena, vat, id )
        {}
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
        Pozycja( unsigned int idTowaru, size_t ilosc )
        {
            this->idTowaru = idTowaru;
            this->ilosc = ilosc;
        }

        unsigned int idTowaru;
        size_t ilosc;
    };

    struct PozycjaZamowienia : public Pozycja, Rekord {
        PozycjaZamowienia( unsigned int idTowaru, size_t ilosc, unsigned int idZamowienia,
                           unsigned int id = 0 )
                               : Pozycja( idTowaru, ilosc ),
                                 Rekord( "Pozycja_zamowienia", id )
        {
            this->idZamowienia = idZamowienia;
        }

        unsigned int idZamowienia;
    };

    struct PozycjaSprzedazy : public Pozycja, Rekord {
        PozycjaSprzedazy( unsigned int idTowaru, size_t ilosc, unsigned int idSprzedazy,
                          float cena, StawkaVAT vat, unsigned int id = 0 )
                               : Pozycja( idTowaru, ilosc ),
                                 Rekord( "Pozycja_sprzedazy", id )
        {
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
                    StatusZamowienia status = Oczekujace )
        {
            this->dataRealizacji = dataRealizacji;
            this->upust = upust;
            this->status = status;
        }

        QDate dataRealizacji;
        float upust;
        StatusZamowienia status;
    };

    struct ZamowienieHurtownia : public Transakcja, Rekord {
        ZamowienieHurtownia( unsigned int idSklepu, const QDate dataZlozenia,
                             const QString &nrFaktury, const QDate dataRealizacji = QDate(), float upust = 0.0,
                             StatusZamowienia status = Oczekujace, unsigned int id = 0 )
                                 : Transakcja( dataRealizacji, upust, status ),
                                   Rekord( "Zamowienie", id )
        {
            this->idSklepu = idSklepu;
            this->dataZlozenia = dataZlozenia;
            this->nrFaktury = nrFaktury;
        }

        unsigned int idSklepu;
        QDate dataZlozenia;
        QString nrFaktury;
    };

    struct ZamowienieSklep : public Transakcja, Rekord {
        ZamowienieSklep( unsigned int idHurtowni, unsigned int idPracownika, const QDate dataZlozenia,
                         const QString &nrFaktury, const QDate dataRealizacji = QDate(), float upust = 0.0,
                         StatusZamowienia status = Oczekujace, unsigned int id = 0 )
            : Transakcja( dataRealizacji, upust, status ),
              Rekord( "Zamowienie", id )
        {
            this->idHurtowni = idHurtowni;
            this->idPracownika = idPracownika;
            this->nrFaktury = nrFaktury;
            this->dataZlozenia = dataZlozenia;
        }

        unsigned int idPracownika, idHurtowni;
        QDate dataZlozenia;
        QString nrFaktury;
    };

    struct Sprzedaz : public Transakcja, Rekord {
        Sprzedaz( unsigned int idPracownika, unsigned int idKlienta, unsigned int idFaktury,
                  const QString &nrParagonu, Potwierdzenie potwierdzenie,
                  const QDate dataRealizacji = QDate(), float upust = 0.0,
                  StatusZamowienia status = Oczekujace, unsigned int id = 0 )
            : Transakcja( dataRealizacji, upust, status ),
              Rekord( "Sprzedaz", id )
        {
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

    struct Faktura : public Rekord {
        Faktura( const QString &nr, unsigned int id = 0 )
            : Rekord( "Faktura", id )
        {
            this->nr = nr;
        }

        QString nr;
    };

    struct Kategoria : public Rekord {
        Kategoria( const QString &nazwa, unsigned int id = 0 )
            : Rekord( "Kategoria", id )
        {
            this->nazwa = nazwa;
        }

        QString nazwa;
    };

    struct Czlowiek {
        Czlowiek( const QString &nazwa, const QString &ulica, const QString &miejscowosc,
                  const QString &kodPocztowy, const QString &telefon, const QString &email )
        {
            this->nazwa = nazwa;
            this->ulica = ulica;
            this->miejscowosc = miejscowosc;
            this->kodPocztowy = kodPocztowy;
            this->telefon = telefon;
            this->email = email;
        }

        QString nazwa, ulica, miejscowosc, kodPocztowy, telefon, email;
    };

    struct Klient : public Czlowiek, Rekord {
        Klient( const QString &regon, const QString &nazwa, const QString &ulica, const QString &miejscowosc,
                const QString &kodPocztowy, const QString &telefon, const QString &email,
                unsigned int id = 0 )
                    : Czlowiek( nazwa, ulica, miejscowosc, kodPocztowy, telefon, email ),
                      Rekord( "Klient", id )
        {
            this->regon = regon;
        }

        QString regon;
    };

    struct Pracownik : public Czlowiek, Rekord {
        Pracownik( const QString &pesel, const QString &nip, const QString &nazwa,
                   Posada posada, const QDate dataZatrudnienia, float stawka,
                   const QString &ulica, const QString &miejscowosc,
                   const QString &kodPocztowy, const QString &telefon, const QString &email,
                   const QString &login, const QString &haslo,
                   unsigned int id = 0 )
                    : Czlowiek( nazwa, ulica, miejscowosc, kodPocztowy, telefon, email ),
                      Rekord( "Pracownik", id )
        {
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

    // deklaracja metod
    explicit DBProxy( QObject *parent, const QString &host, const QString &dbName,
                      const QString &login, const QString &pass);

    bool polacz();

    void rozpocznijDodawanie();
    void zakonczDodawanie();

    unsigned int dodajFakture( const Faktura &faktura );
    unsigned int dodajHurtownie( const Hurtownia &hurtownia );
    unsigned int dodajKategorie( const Kategoria &kategoria );
    unsigned int dodajKlienta( const Klient &klient );
    unsigned int dodajPozycjeSprzedazy( const PozycjaSprzedazy &pozycja );
    unsigned int dodajPozycjeZamowienia( const PozycjaZamowienia &pozycja );
    unsigned int dodajPracownika( const Pracownik &pracownik );
    unsigned int dodajSklep( const Sklep &sklep );
    unsigned int dodajSprzedaz( const Sprzedaz &sprzedaz );
    unsigned int dodajTowarHurtownia( const TowarHurtownia &towar );
    unsigned int dodajTowarSklep( const TowarSklep &towar );
    unsigned int dodajZamowienieHurtownia( const ZamowienieHurtownia &zamowienie );
    unsigned int dodajZamowienieSklep( const ZamowienieSklep &zamowienie );

signals:
    void bladDodawaniaRekordu();
    void log( QString str );

public slots:

private:
    QString dataNaString( const QDate &data );
    unsigned int execQuery( const QString &query );
    QString liczbaNaString( double liczba );
    QString nawiasy( const QString &string );
    QString posadaNaString( Posada posada );
    QString potwierdzenieNaString( Potwierdzenie potwierdzenie );
    QString statusNaString( StatusZamowienia status );
    void usunRekord( const Rekord *rekord );

    QSqlDatabase db;

    // zarz±dzie maszyn± stanu zwi±zan± z kontrol± b³êdów przy dodawaniu
    // rekordów do bazy danych
    bool dodawanie;
    bool mBladDodawaniaRekordu;
    QList< Rekord* > aktualnieDodawaneRekordy;

private slots:
    void debug( QString str );
};

#endif // DBPROXY_H
