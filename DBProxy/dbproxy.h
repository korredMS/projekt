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

    enum Relacja {
        Rowne, Wieksze, WiekszeRowne, Mniejsze, MniejszeRowne, Zawiera
    };

    struct Rekord {
        Rekord( const QString &tabela, unsigned int id = 0 )
        {
            this->id = id;
            this->tabela = tabela;
        }

        unsigned int id;

        QString tabela;

        // pozniej statycznie
        static QStringList polaEnum;
        static QStringList polaUInt;
        static QStringList polaFloat;
        static QStringList polaQDate;
    };

    struct HurtowniaProto {
        HurtowniaProto( const QString &nazwa, const QString &regon, const QString &ulica, const QString &miejscowosc,
                   const QString &kodPocztowy, const QString &telefon, const QString &fax, const QString &email,
                   float upust = 0 )
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

    struct Hurtownia : public HurtowniaProto, Rekord {
        Hurtownia( const QString &nazwa, const QString &regon, const QString &ulica, const QString &miejscowosc,
                   const QString &kodPocztowy, const QString &telefon, const QString &fax, const QString &email,
                   float upust = 0, unsigned int id = 0 )
                       : HurtowniaProto( nazwa, regon, ulica, miejscowosc, kodPocztowy, telefon, fax, email, upust ),
                         Rekord( "Hurtownia",
                                 id )
        {}

        Hurtownia( const QSqlQuery &query )
            : HurtowniaProto( query.value( 2 ).toString(), query.value( 1 ).toString(),
                              query.value( 4 ).toString(), query.value( 5 ).toString(),
                              query.value( 6 ), query.value( 7 ), query.value( 8 ), query.value( 9 ),
                              query.value( 3 ) ),
              Rekord( "Hurtownia",
                      query.value( 0 ) )
        {
            this->id = query.value( 0 );
            this->regon = query.value( 1 );
            this->nazwa = query.value( 2 );
            this->upust = query.value( 3 );
            this->ulica = query.value( 4 );
            this->miejscowosc = query.value( 5 );
            this->kodPocztowy = query.value( 6 );
            this->telefon = query.value( 7 );
            this->fax = query.value( 8 );
            this->email = query.value( 9 );
        }

        static QString tabela;
        static QStringList polaBazy;
        QString nazwa, REGON, ulica, miejscowosc, kodPocztowy, telefon, fax, email;
        float upust;

        enum PoleBazy {
            Id, Regon, Nazwa, Upust, Ulica, Miejscowosc, KodPocztowy, Telefon, Fax, Email
        };
    };

    struct Sklep : public HurtowniaProto, Rekord {
        Sklep( const QString &nazwa, const QString &regon, const QString &ulica,
               const QString &miejscowosc, const QString &kodPocztowy, const QString &telefon,
               const QString &fax, const QString &email, const QString &login,
               const QString &haslo, float upust = 0, unsigned int id = 0 )
                   : HurtowniaProto( nazwa, regon, ulica, miejscowosc, kodPocztowy, telefon, fax,
                                     email, upust ),
                     Rekord( "Sklep",
                             id )
        {
            this->login = login;
            this->haslo = haslo;
        }

        static QString tabela;
        static QStringList polaBazy;
        QString login, haslo;

        enum PoleBazy {
            Id, Regon, Nazwa, Upust, Login, Haslo, Ulica, Miejscowosc, KodPocztowy, Telefon, Fax, Email
        };
    };

    struct Towar {
        Towar( const QString &nazwa, const QString &opis, size_t ilosc, float cena, StawkaVAT vat )
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

    struct TowarHurtownia : public Towar, Rekord {
        TowarHurtownia( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
                        StawkaVAT vat, unsigned int id = 0 )
                            : Towar( nazwa, opis, ilosc, cena, vat ),
                              Rekord( "Towar",
                                      id )
        {}

        static QString tabela;
        static QStringList polaBazy;

        enum PoleBazy {
            Id, Nazwa, Opis, Cena, Ilosc, VAT
        };
    };

    struct TowarSklep : public Towar, Rekord {
        TowarSklep( const QString &nazwa, const QString &opis, size_t ilosc, float cena,
                    StawkaVAT vat, float cenaZakupu, unsigned int idKategorii, unsigned int id = 0 )
                            : Towar( nazwa, opis, ilosc, cena, vat ),
                              Rekord( "Towar", id )
        {
            this->cenaZakupu = cenaZakupu;
            this->idKategorii = idKategorii;
        }

        static QString tabela;
        static QStringList polaBazy;
        float cenaZakupu;
        unsigned int idKategorii;

        enum PoleBazy {
            Id, Nazwa, Opis, Cena, Ilosc, VAT, CenaZakupu
        };
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

        static QString tabela;
        static QStringList polaBazy;
        unsigned int idZamowienia;

        enum PoleBazy {
            Id, IdZamowienia, IdTowaru, Ilosc
        };
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

        static QString tabela;
        static QStringList polaBazy;
        unsigned int idSprzedazy;
        float cena;
        StawkaVAT vat;

        enum PoleBazy {
            Id, IdSprzedazy, IdTowaru, Ilosc, Cena, VAT
        };
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

        static QString tabela;
        static QStringList polaBazy;
        unsigned int idSklepu;
        QDate dataZlozenia;
        QString nrFaktury;

        enum PoleBazy {
            Id, IdSklepu, DataZlozenia, DataRealizacji, Upust, Status, NrFaktury
        };
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

        static QString tabela;
        static QStringList polaBazy;
        unsigned int idPracownika, idHurtowni;
        QDate dataZlozenia;
        QString nrFaktury;

        enum PoleBazy {
            Id, IdHurtowni, DataZlozenia, DataRealizacji, Status, NrFaktury, IdPracownika
        };
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

        static QString tabela;
        static QStringList polaBazy;
        Potwierdzenie potwierdzenie;
        QString nrParagonu;
        unsigned int idFaktury, idKlienta, idPracownika;

        enum PoleBazy {
            Id, DataRealizacji, Status, PotwierdzeniePole, NrParagonu, IdFaktury, IdKlienta, IdPracownika
        };
    };

    struct Faktura : public Rekord {
        Faktura( const QString &nr, unsigned int id = 0 )
            : Rekord( "Faktura", id )
        {
            this->nr = nr;
        }

        static QString tabela;
        static QStringList polaBazy;
        QString nr;

        enum PoleBazy {
            Id, NrFaktury
        };
    };

    struct Kategoria : public Rekord {
        Kategoria( const QString &nazwa, unsigned int id = 0 )
            : Rekord( "Kategoria", id )
        {
            this->nazwa = nazwa;
        }

        static QString tabela;
        static QStringList polaBazy;
        QString nazwa;

        enum PoleBazy {
            Id, Nazwa
        };
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

        static QString tabela;
        static QStringList polaBazy;
        QString regon;

        enum PoleBazy {
            Id, Regon, Ulica, Miejscowosc, KodPocztowy, Telefon, Nazwa
        };
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

        static QString tabela;
        static QStringList polaBazy;
        QString pesel, nip, login, haslo;
        Posada posada;
        QDate dataZatrudnienia;
        float stawka;

        enum PoleBazy {
            Id, Nazwisko, Pesel, Nip, PosadaPole, DataZatrudnienia, Stawka, Ulica, Miejscowosc, KodPocztowy, Telefon, Email
        };
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

    template< typename T > QList< T > pobierz() {
        return pobierz< T >( QMap< typename T::PoleBazy, QVariant >() );
    }

    template< typename T > QList< T > pobierz( const QMap< typename T::PoleBazy, QVariant > &filtr,
                                               Relacja relacja = Rowne )
    {
        QString queryString = QString( "SELECT " + T::polaBazy.join( ", " ) + " FROM %1" )
                              .arg( T::tabela );

        if( !filtr.empty() ) {
            queryString += " WHERE ";

            typename QMap< typename T::PoleBazy, QVariant >::const_iterator it = filtr.begin();
            for( it = filtr.begin(); it != filtr.end(); ++it ) {
                QString poleStr = T::polaBazy[ it.key() ];
                QVariant wartosc = it.value();

                queryString += poleStr;
                queryString += relacjaNaString( relacja );

                if( Rekord::polaUInt.contains( poleStr ) )
                    queryString += liczbaNaString( wartosc.toUInt() );

                else if( Rekord::polaFloat.contains( poleStr ) )
                    queryString += liczbaNaString( wartosc.toFloat() );

                else if( Rekord::polaQDate.contains( poleStr ) )
                    queryString += nawiasy( dataNaString( wartosc.toDate() ) );

                else if( Rekord::polaEnum.contains( poleStr ) ) {
                    if( poleStr == "vat" )
                        queryString += nawiasy( vatNaString( wartosc.value< StawkaVAT >() ) );

                    if( poleStr == "status" )
                        queryString += nawiasy( statusNaString( wartosc.value< StatusZamowienia >() ) );

                    if( poleStr == "potwierdzenie" )
                        queryString += nawiasy( potwierdzenieNaString( wartosc.value< Potwierdzenie >() ) );

                    if( poleStr == "posada" )
                        queryString += nawiasy( posadaNaString( wartosc.value< Posada >() ) );
                }

                else
                    queryString += nawiasy( wartosc.toString() );
            }
        }
        queryString += ";";

        QSqlQuery query( db );

        QList< T > lista;
        if( query.exec( queryString ) ) {
            while( query.next() ) {
                lista.append( T( query ) );
            }
        }

        return lista;
    }

signals:
    void bladDodawaniaRekordu();
    void log( QString str );

public slots:

private:
    QString dataNaString( const QDate &data );
    QVariant execQuery( const QString &query );
    QString liczbaNaString( double liczba );
    QString nawiasy( const QString &string );
    QString posadaNaString( Posada posada );
    QString potwierdzenieNaString( Potwierdzenie potwierdzenie );
    QString relacjaNaString( Relacja relacja );
    QString statusNaString( StatusZamowienia status );
    void usunRekord( const Rekord *rekord );
    QString vatNaString( StawkaVAT vat );

    QSqlDatabase db;

    // zarz±dzie maszyn± stanu zwi±zan± z kontrol± b³êdów przy dodawaniu
    // rekordów do bazy danych
    bool dodawanie;
    bool mBladDodawaniaRekordu;
    QList< Rekord* > aktualnieDodawaneRekordy;

private slots:
    void debug( QString str );
};

Q_DECLARE_METATYPE( DBProxy::Posada );
Q_DECLARE_METATYPE( DBProxy::Potwierdzenie );
Q_DECLARE_METATYPE( DBProxy::StatusZamowienia );
Q_DECLARE_METATYPE( DBProxy::StawkaVAT );

#endif // DBPROXY_H
