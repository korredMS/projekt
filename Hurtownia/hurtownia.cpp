#include "hurtownia.h"
#include "ui_hurtownia.h"
#include "edycjasklep.h"
#include "edycjatowar.h"
#include "edycjakategoria.h"

using namespace DBProxyNS;

OknoHurtownia::OknoHurtownia(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Hurtownia),
        db(this,"localhost","Hurtownia","root","")
{
    
    ui->setupUi(this);
    db.polacz();
    pobierzSklepy();
    pobierzTowary();
    pobierzKategorie();
    pobierzZamowienia();
    
}

OknoHurtownia::~OknoHurtownia()
{
    delete ui;
}

void OknoHurtownia::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/* OBS£UGA SKLEPÓW */


void OknoHurtownia::pobierzSklepy() // wyœwietlanie sklepów
{
    modelSklepy.clear();
    sklep = db.pobierz< DBProxy::Sklep >();

    for ( int i = 0; i < sklep.length() ; i++)
    {
        Sklep towar = sklep.at( i );
        modelSklepy.setItem( i, 0, new QStandardItem (DBProxy::liczbaNaString(sklep[i].id)) );
        modelSklepy.setItem( i, 1, new QStandardItem (sklep[i].nazwa ));
        modelSklepy.setItem( i, 2, new QStandardItem (sklep[i].REGON));
        modelSklepy.setItem( i, 3, new QStandardItem (DBProxy::liczbaNaString(sklep[i].upust)));
        modelSklepy.setItem( i, 4, new QStandardItem (sklep[i].ulica));
        modelSklepy.setItem( i, 5, new QStandardItem (sklep[i].miejscowosc));
        modelSklepy.setItem( i, 6, new QStandardItem (sklep[i].kodPocztowy));
        modelSklepy.setItem( i, 7, new QStandardItem (sklep[i].telefon));
        modelSklepy.setItem( i, 8, new QStandardItem (sklep[i].fax));
        modelSklepy.setItem( i, 9, new QStandardItem (sklep[i].email));
        modelSklepy.setItem( i, 10, new QStandardItem (sklep[i].login));
        modelSklepy.setItem( i, 11, new QStandardItem (sklep[i].haslo));
    }

    modelSklepy.setHeaderData( 0, Qt::Horizontal, "ID" );
    modelSklepy.setHeaderData( 1, Qt::Horizontal, "Nazwa" );
    modelSklepy.setHeaderData( 2, Qt::Horizontal, "Regon" );
    modelSklepy.setHeaderData( 3, Qt::Horizontal, "Upust" );
    modelSklepy.setHeaderData( 4, Qt::Horizontal, "Ulica" );
    modelSklepy.setHeaderData( 5, Qt::Horizontal, "Miejscowoœæ" );
    modelSklepy.setHeaderData( 6, Qt::Horizontal, "Kod Pocztowy" );
    modelSklepy.setHeaderData( 7, Qt::Horizontal, "Telefon" );
    modelSklepy.setHeaderData( 8, Qt::Horizontal, "Fax" );
    modelSklepy.setHeaderData( 9, Qt::Horizontal, "Email" );
    modelSklepy.setHeaderData( 10, Qt::Horizontal, "Login" );
    modelSklepy.setHeaderData( 11, Qt::Horizontal, "Has³o" );

    ui->tableListaSklepow->setModel( &modelSklepy);
    ui->tableListaSklepow->setColumnWidth( 0, 20 );
    ui->tableListaSklepow->setColumnWidth( 1, 80 );
    ui->tableListaSklepow->setColumnWidth( 2, 50 );
    ui->tableListaSklepow->setColumnWidth( 3, 20 );
    ui->tableListaSklepow->setColumnWidth( 4, 80 );
    ui->tableListaSklepow->setColumnWidth( 5, 80 );
    ui->tableListaSklepow->setColumnWidth( 6, 20 );
    ui->tableListaSklepow->setColumnWidth( 7, 20 );
    ui->tableListaSklepow->setColumnWidth( 8, 20 );
    ui->tableListaSklepow->setColumnWidth( 9, 50 );
    ui->tableListaSklepow->setColumnWidth( 10, 50 );
    ui->tableListaSklepow->setColumnWidth( 11, 50 );
    ui->tableListaSklepow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableListaSklepow->resizeColumnsToContents();

}

void OknoHurtownia::on_dodajButton_clicked()
{
    EdycjaSklep *edycja = new EdycjaSklep(this,db);
    connect(edycja, SIGNAL(odswiezTabeleSklepu()), this, SLOT(pobierzSklepy()));
    edycja->show();
}

void OknoHurtownia::on_tableListaSklepow_clicked(QModelIndex index)
{
    idxSklepu = index.row();
    ui->tableListaSklepow->selectRow( idxSklepu);
    ui->modyfikujButton->setEnabled( true );
    ui->usunButton->setEnabled(true);
}

void OknoHurtownia::on_usunButton_clicked() // sprawdziæ czy dzia³a ( bedzie usuwaæ z lisy ale nie z bazy)
{
    unsigned int ret = QMessageBox::question( this, "Uwaga", "Czy na pewno chcesz usun¹æ wybrany sklep z bazy danych?",
                                              QMessageBox::Yes | QMessageBox::No );
    if ( ret & QMessageBox::Yes ){
        db.usunRekord( &sklep.at(idxSklepu) );

        //sprawdŸ czy usun¹³!
        sklep.removeAt(idxSklepu);
        modelSklepy.removeRow( idxSklepu , QModelIndex() );
        
    }
    
    if ( ret & QMessageBox::No )
        return;
}

void OknoHurtownia::on_modyfikujButton_clicked() // dokoñczyc
{
    int wiersz = ui->tableListaSklepow->currentIndex().row();
    EdycjaSklep *edycja = new EdycjaSklep(this,db, &sklep[wiersz], false);
    connect(edycja, SIGNAL(odswiezTabeleSklepu()), this, SLOT(pobierzSklepy()));
    edycja->show();
}

/* OBS£UGA TOWARÓW */

void OknoHurtownia::pobierzTowary()       //wyœwietlenie  towarow
{
    modelTowary.clear();
    towaryH = db.pobierz< DBProxy::TowarHurtownia >();

    for (int i = 0; i < towaryH.length(); i++) {
        modelTowary.setItem( i, 0, new QStandardItem( DBProxy::liczbaNaString( towaryH[i].id ) ) );
        modelTowary.setItem( i, 1, new QStandardItem( db.pobierz< DBProxy::Kategoria >(DBProxy::Kategoria::Id, DBProxy::Filtr(towaryH[i].idKategorii ) ).first().nazwa ) );
        modelTowary.setItem( i, 2, new QStandardItem( towaryH[i].nazwa ) );
        modelTowary.setItem( i, 3, new QStandardItem( towaryH[i].opis ) );
        modelTowary.setItem( i, 4, new QStandardItem( DBProxy::liczbaNaString( towaryH[i].cena ) ) );
        modelTowary.setItem( i, 5, new QStandardItem( DBProxy::liczbaNaString( towaryH[i].ilosc ) ) );
        modelTowary.setItem( i, 6, new QStandardItem( QString::number( towaryH[i].vat ) + "%"  ) );

    }

    modelTowary.setHeaderData( 0, Qt::Horizontal, "Id" );
    modelTowary.setHeaderData( 1, Qt::Horizontal, "Kategoria" );
    modelTowary.setHeaderData( 2, Qt::Horizontal, "Nazwa" );
    modelTowary.setHeaderData( 3, Qt::Horizontal, "Opis" );
    modelTowary.setHeaderData( 4, Qt::Horizontal, "Cena" );
    modelTowary.setHeaderData( 5, Qt::Horizontal, "Iloœæ" );
    modelTowary.setHeaderData( 6, Qt::Horizontal, "VAT" );


    ui->tableListaTowarow->setModel( &modelTowary );
    ui->tableListaTowarow->setColumnWidth( 0, 30 );
    ui->tableListaTowarow->setColumnWidth( 1, 100 );
    ui->tableListaTowarow->setColumnWidth( 2, 100 );
    ui->tableListaTowarow->setColumnWidth( 3, 115 );
    ui->tableListaTowarow->setColumnWidth( 4, 40 );
    ui->tableListaTowarow->setColumnWidth( 5, 35 );
    ui->tableListaTowarow->setColumnWidth( 6, 40 );
    ui->tableListaTowarow->setEditTriggers( QAbstractItemView::NoEditTriggers);
}


void OknoHurtownia::on_buttonDodajTowar_clicked()
{
    EdycjaTowar *edycjaTowar = new EdycjaTowar(this,db);
    connect( edycjaTowar, SIGNAL(odswiezTabeleTowarow()), this, SLOT(pobierzTowary()));
    edycjaTowar->show();
}

void OknoHurtownia::on_tableListaTowarow_clicked(QModelIndex index)
{
    ui->buttonModyfikujTowar->setEnabled( true );
    ui->buttonUsunTowar->setEnabled(true);
}

void OknoHurtownia::on_buttonUsunTowar_clicked()    // usuwa z listy ale nie usuwa z bazy
{
    unsigned int ret = QMessageBox::question( this, "Uwaga", "Czy na pewno chcesz usun¹æ wybrany sklep z bazy danych?",
                                              QMessageBox::Yes | QMessageBox::No );
    int idxTowaru = ui->tableListaTowarow->currentIndex().row();
    if ( ret & QMessageBox::Yes ){
        db.usunRekord( &towaryH.at( idxTowaru ) );

        towaryH.removeAt(idxTowaru);
        modelTowary.removeRow( idxTowaru , QModelIndex() );

        pobierzTowary();
    }

    if ( ret & QMessageBox::No )
        return;
}

/* OBS£UGA KATEGORII */

void OknoHurtownia::pobierzKategorie()   {
    modelKategorie.clear();
    kH = db.pobierz< DBProxy::Kategoria >();

    for (int i = 0; i < kH.size(); i++) {
        modelKategorie.setItem( i, 0, new QStandardItem( DBProxy::liczbaNaString( kH[i].id ) ) );
        modelKategorie.setItem( i, 1, new QStandardItem( kH[i].nazwa ) ); //Tutaj coœ siê pierdzieli

    }
    modelKategorie.setHeaderData( 0, Qt::Horizontal, "Id" );
    modelKategorie.setHeaderData( 1, Qt::Horizontal, "Kategoria" );

    ui->tableListakategorii->setModel( &modelKategorie );
    ui->tableListakategorii->setColumnWidth( 0, 30 );
    ui->tableListakategorii->setColumnWidth( 1, 100 );
    ui->tableListakategorii->setEditTriggers( QAbstractItemView::NoEditTriggers);
}

void OknoHurtownia::on_buttonDodajKat_clicked()
{
    EdycjaKategoria *kategoria = new EdycjaKategoria(this,db);
    kategoria->show();

}

void OknoHurtownia::on_tableListakategorii_clicked(QModelIndex index)
{
    idxKategori = index.row();
    ui->tableListakategorii->selectRow( idxKategori);
    ui->buttonModyfikujKat->setEnabled( true );
    ui->buttonUsunKat->setEnabled(true);
}



/* OBS£UGA ZAMÓWIEÑ */

void OknoHurtownia::pobierzZamowienia()       //lista zamowien
{
    modelZamowienia.clear();
    zamowienieH = db.pobierz< DBProxy::ZamowienieHurtownia >();

    for (int i = 0; i < zamowienieH.size(); i++) {
        modelZamowienia.setItem( i, 0, new QStandardItem( DBProxy::liczbaNaString( zamowienieH[i].id ) ) );
        modelZamowienia.setItem( i, 1, new QStandardItem( zamowienieH[i].nrFaktury ) );
        modelZamowienia.setItem( i, 2, new QStandardItem( DBProxy::dataNaString( zamowienieH[i].dataZlozenia ) ) ); //rzutowanie nie dzia³a
        modelZamowienia.setItem( i, 3, new QStandardItem( DBProxy::dataNaString( zamowienieH[i].dataRealizacji ) ) );//rzutowanie nie dzia³a
        modelZamowienia.setItem( i, 4, new QStandardItem( DBProxy::liczbaNaString( zamowienieH[i].upust ) ) );//rzutowanie nie dzia³a
        modelZamowienia.setItem( i, 5, new QStandardItem( DBProxy::statusNaString( zamowienieH[i].status ) ) );//rzutowanie nie dzia³a

    }

    modelZamowienia.setHeaderData( 0, Qt::Horizontal, "Id" );
    modelZamowienia.setHeaderData( 1, Qt::Horizontal, "Nr faktury" );
    modelZamowienia.setHeaderData( 2, Qt::Horizontal, "Data z³o¿enia" );
    modelZamowienia.setHeaderData( 3, Qt::Horizontal, "Data realizacji" );
    modelZamowienia.setHeaderData( 4, Qt::Horizontal, "Upust" );
    modelZamowienia.setHeaderData( 5, Qt::Horizontal, "Status" );

    ui->tableZamowienia->setModel( &modelZamowienia );
    ui->tableZamowienia->setColumnWidth( 0, 50 );
    ui->tableZamowienia->setColumnWidth( 1, 90 );
    ui->tableZamowienia->setColumnWidth( 2, 100 );
    ui->tableZamowienia->setColumnWidth( 3, 100 );
    ui->tableZamowienia->setColumnWidth( 4, 50 );
    ui->tableZamowienia->setColumnWidth( 5, 85 );
    ui->tableZamowienia->setEditTriggers( QAbstractItemView::NoEditTriggers);


}



void OknoHurtownia::on_tableZamowienia_clicked(QModelIndex index)
{
    idxZamowienia = index.row();
    ui->tableZamowienia->selectRow( idxZamowienia);
    ui->buttonRealizujZamowieni->setEnabled(true);
    ui->buttonAnulujZamowienie->setEnabled(true);

}

void OknoHurtownia::on_buttonRealizujZamowieni_clicked()
{
    int wiersz = ui->tableZamowienia->currentIndex().row();
    ZamowienieHurtownia &zamowienie = zamowienieH[ wiersz ];

    if( zamowienie.status == DBProxy::Oczekujace ) {
        zamowienie.status = DBProxy::DoRealizacji;
        db.uaktualnij( zamowienie );
    }

    pobierzZamowienia();
}

void OknoHurtownia::on_buttonAnulujZamowienie_clicked()
{
    int wiersz = ui->tableZamowienia->currentIndex().row();
    ZamowienieHurtownia &zamowienie = zamowienieH[ wiersz ];

    if( zamowienie.status == DBProxy::Oczekujace ) {
        zamowienie.status = DBProxy::Anulowane;
        db.uaktualnij( zamowienie );
    }

    pobierzZamowienia();
}





