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
        QList< PozycjaZamowienia > pozycjeZamowienia = db.pobierz< DBProxy::PozycjaZamowienia >( PozycjaZamowienia::IdZamowienia,
                                                                                                 Filtr( mZamowienie->id ) );

        for (int i = 0; i < pozycjeZamowienia.size(); i++) {
            TowarHurtownia towar = db.pobierz< TowarHurtownia >( TowarHurtownia::Id, Filtr( pozycjeZamowienia[i].idTowaru )).first();
            modelPozycjeZamowienia.setItem( i, 0, new QStandardItem( DBProxy::liczbaNaString( pozycjeZamowienia[i].idZamowienia ) ) );
            modelPozycjeZamowienia.setItem( i, 1, new QStandardItem( towar.nazwa ));
            modelPozycjeZamowienia.setItem( i, 2, new QStandardItem( towar.opis ) );
            modelPozycjeZamowienia.setItem( i, 3, new QStandardItem( DBProxy::liczbaNaString( towar.cena ) ) );
            modelPozycjeZamowienia.setItem( i, 4, new QStandardItem( DBProxy::liczbaNaString( towar.ilosc ) ) );
            modelPozycjeZamowienia.setItem( i, 5, new QStandardItem( QString::number( towar.vat ) + "%"  ) );
        }

        modelPozycjeZamowienia.setHeaderData( 0, Qt::Horizontal, "Id Zamówienia" );
        modelPozycjeZamowienia.setHeaderData( 1, Qt::Horizontal, "Nazwa" );
        modelPozycjeZamowienia.setHeaderData( 2, Qt::Horizontal, "Opis" );
        modelPozycjeZamowienia.setHeaderData( 3, Qt::Horizontal, "Cena" );
        modelPozycjeZamowienia.setHeaderData( 4, Qt::Horizontal, "Iloœæ" );
        modelPozycjeZamowienia.setHeaderData( 5, Qt::Horizontal, "VAT" );



        ui->tableListaSzczegoly->setModel( &modelPozycjeZamowienia );
        ui->tableListaSzczegoly->setColumnWidth( 0, 70 );
        ui->tableListaSzczegoly->setColumnWidth( 1, 100 );
        ui->tableListaSzczegoly->setColumnWidth( 2, 115 );
        ui->tableListaSzczegoly->setColumnWidth( 3, 40 );
        ui->tableListaSzczegoly->setColumnWidth( 4, 35 );
        ui->tableListaSzczegoly->setColumnWidth( 5, 40 );
        ui->tableListaSzczegoly->setEditTriggers( QAbstractItemView::NoEditTriggers);

    }

}
