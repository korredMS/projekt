#include "szczegolyzamowienia.h"
#include "ui_szczegolyzamowienia.h"


using namespace DBProxyNS;

SzczegolyZamowienia::SzczegolyZamowienia(QWidget *parent,DBProxy &adb, ZamowienieHurtownia * aZamowienie) :
    QDialog(parent),
    ui(new Ui::SzczegolyZamowienia),
    db( adb ),
    mZamowienie( aZamowienie)
{
    ui->setupUi(this);
    setWindowTitle(tr("Szczególy zamówienia"));

    pobierzSzczegoly();
}

SzczegolyZamowienia::~SzczegolyZamowienia()
{
    delete ui;
}

void SzczegolyZamowienia::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SzczegolyZamowienia::on_szczegolyZamowienaWrocButton_clicked()
{
    this->close();
}

void SzczegolyZamowienia::pobierzSzczegoly(){

    {
        modelPozycjeZamowienia.clear();
        QList <PozycjaZamowienia>  pozycjeZamowienia = db.pobierz< DBProxy::PozycjaZamowienia >( PozycjaZamowienia::IdZamowienia,
                                                                                                 Filtr( mZamowienie->id ) );
        QList <ZamowienieHurtownia> zamowienieH = db.pobierz < ZamowienieHurtownia> (ZamowienieHurtownia::Id, Filtr( mZamowienie->id));

        double razemNetto = 0;
        double razemBrutto = 0;
        int iloscTowarow = 0;
        for (int i = 0; i < pozycjeZamowienia.size(); i++) {
            TowarHurtownia towar = db.pobierz< TowarHurtownia >( TowarHurtownia::Id, Filtr( pozycjeZamowienia[i].idTowaru )).first();
            double upust = zamowienieH[mZamowienie->Id].upust * 0.01;
            razemNetto += towar.cena * pozycjeZamowienia[i].ilosc;
            razemBrutto += (towar.cena + (towar.cena * (towar.vat * 0.01))) * pozycjeZamowienia[i].ilosc;
            iloscTowarow += pozycjeZamowienia[i].ilosc;

            modelPozycjeZamowienia.setItem( i, 0, new QStandardItem( DBProxy::liczbaNaString( pozycjeZamowienia[i].idZamowienia ) ) );
            modelPozycjeZamowienia.setItem( i, 1, new QStandardItem( towar.nazwa ));
            modelPozycjeZamowienia.setItem( i, 2, new QStandardItem( towar.opis ) );
            modelPozycjeZamowienia.setItem( i, 3, new QStandardItem( DBProxy::liczbaNaString( towar.cena ) ) );
            modelPozycjeZamowienia.setItem( i, 4, new QStandardItem( DBProxy::liczbaNaString( pozycjeZamowienia[i].ilosc) ) );
            modelPozycjeZamowienia.setItem( i, 5, new QStandardItem( QString::number( towar.vat ) + "%"  ) );
            modelPozycjeZamowienia.setItem( i, 6, new QStandardItem( DBProxy::liczbaNaString(upust)));
            modelPozycjeZamowienia.setItem( i, 7, new QStandardItem( DBProxy::liczbaNaString((towar.cena - (towar.cena * upust)) * pozycjeZamowienia[i].ilosc)));
        }

        modelPozycjeZamowienia.setHeaderData( 0, Qt::Horizontal, "Id Zamówienia" );
        modelPozycjeZamowienia.setHeaderData( 1, Qt::Horizontal, "Nazwa" );
        modelPozycjeZamowienia.setHeaderData( 2, Qt::Horizontal, "Opis" );
        modelPozycjeZamowienia.setHeaderData( 3, Qt::Horizontal, "Cena" );
        modelPozycjeZamowienia.setHeaderData( 4, Qt::Horizontal, "Iloœæ" );
        modelPozycjeZamowienia.setHeaderData( 5, Qt::Horizontal, "VAT" );
        modelPozycjeZamowienia.setHeaderData( 6, Qt::Horizontal, "Upust" );
        modelPozycjeZamowienia.setHeaderData( 7, Qt::Horizontal, "Kwota" );

        ui->tableListaSzczegoly->setModel( &modelPozycjeZamowienia );
        ui->tableListaSzczegoly->setColumnWidth( 0, 70 );
        ui->tableListaSzczegoly->setColumnWidth( 1, 100 );
        ui->tableListaSzczegoly->setColumnWidth( 2, 115 );
        ui->tableListaSzczegoly->setColumnWidth( 3, 40 );
        ui->tableListaSzczegoly->setColumnWidth( 4, 35 );
        ui->tableListaSzczegoly->setColumnWidth( 5, 40 );
        ui->tableListaSzczegoly->setColumnWidth( 6, 40 );
        ui->tableListaSzczegoly->setColumnWidth( 7, 40 );
        ui->tableListaSzczegoly->setEditTriggers( QAbstractItemView::NoEditTriggers);

        ui->nettoEdit->setText(DBProxy::liczbaNaString(razemNetto));
        ui->bruttoEdit->setText(DBProxy::liczbaNaString(razemBrutto));
        ui->podatekEdit->setText(DBProxy::liczbaNaString(razemBrutto - razemNetto));;
        ui->iloscTowarowEdit->setText(DBProxy::liczbaNaString(iloscTowarow));
        ui->dataZlozeniaEdit->setText(DBProxy::dataNaString ( zamowienieH[mZamowienie->Id].dataZlozenia));
        ui->dataRalizacjiEdit->setText(DBProxy::dataNaString ( zamowienieH[mZamowienie->Id].dataRealizacji));
        ui->statusEdit->setText(DBProxy::statusNaString( zamowienieH[mZamowienie->Id].status));
        ui->nrFakturyEdit->setText(zamowienieH[mZamowienie->Id].nrFaktury);
    }

}
