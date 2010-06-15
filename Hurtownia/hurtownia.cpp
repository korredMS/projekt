#include "hurtownia.h"
#include "ui_hurtownia.h"
#include "edycjasklep.h"
#include "edycjatowar.h"
#include "edycjakategoria.h"
#include "szczegolyzamowienia.h"

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

/************************** OBS£UGA OKNA HURTOWNI **************************/

void OknoHurtownia::on_koniecButton_clicked()
{

    unsigned int ret = QMessageBox::question( this, "Uwaga", "<Center>Czy na pewno chcesz opuœciæ aplikacjê?</CENTER>",
                                              QMessageBox::Yes | QMessageBox::No );
    if ( ret & QMessageBox::Yes ){
        this->close();
    }
}



/************************** OBS£UGA SKLEPÓW **************************/

void OknoHurtownia::pobierzSklepy() // wyœwietlanie sklepów
{
    modelSklepy.clear();
    sklep = db.pobierz< DBProxy::Sklep >();

    for ( int i = 0; i < sklep.length() ; i++)
    {
        Sklep towar = sklep.at( i );

        modelSklepy.setItem( i, 0, new QStandardItem (sklep[i].nazwa ));
        modelSklepy.setItem( i, 1, new QStandardItem (sklep[i].REGON));
        modelSklepy.setItem( i, 2, new QStandardItem (DBProxy::liczbaNaString(sklep[i].upust)));
        modelSklepy.setItem( i, 3, new QStandardItem (sklep[i].ulica));
        modelSklepy.setItem( i, 4, new QStandardItem (sklep[i].miejscowosc));
        modelSklepy.setItem( i, 5, new QStandardItem (sklep[i].kodPocztowy));
        modelSklepy.setItem( i, 6, new QStandardItem (sklep[i].telefon));
        modelSklepy.setItem( i, 7, new QStandardItem (sklep[i].fax));
        modelSklepy.setItem( i, 8, new QStandardItem (sklep[i].email));
        modelSklepy.setItem( i, 9, new QStandardItem (sklep[i].login));
        modelSklepy.setItem( i, 10, new QStandardItem (sklep[i].haslo));
    }


    modelSklepy.setHeaderData( 0, Qt::Horizontal, "Nazwa" );
    modelSklepy.setHeaderData( 1, Qt::Horizontal, "Regon" );
    modelSklepy.setHeaderData( 2, Qt::Horizontal, "Upust" );
    modelSklepy.setHeaderData( 3, Qt::Horizontal, "Ulica" );
    modelSklepy.setHeaderData( 4, Qt::Horizontal, "Miejscowoœæ" );
    modelSklepy.setHeaderData( 5, Qt::Horizontal, "Kod Pocztowy" );
    modelSklepy.setHeaderData( 6, Qt::Horizontal, "Telefon" );
    modelSklepy.setHeaderData( 7, Qt::Horizontal, "Fax" );
    modelSklepy.setHeaderData( 8, Qt::Horizontal, "Email" );
    modelSklepy.setHeaderData( 9, Qt::Horizontal, "Login" );
    modelSklepy.setHeaderData( 10, Qt::Horizontal, "Has³o" );

    ui->tableListaSklepow->setModel( &modelSklepy);

    ui->tableListaSklepow->setColumnWidth( 0, 80 );
    ui->tableListaSklepow->setColumnWidth( 1, 50 );
    ui->tableListaSklepow->setColumnWidth( 2, 20 );
    ui->tableListaSklepow->setColumnWidth( 3, 80 );
    ui->tableListaSklepow->setColumnWidth( 4, 80 );
    ui->tableListaSklepow->setColumnWidth( 5, 20 );
    ui->tableListaSklepow->setColumnWidth( 6, 20 );
    ui->tableListaSklepow->setColumnWidth( 7, 20 );
    ui->tableListaSklepow->setColumnWidth( 8, 50 );
    ui->tableListaSklepow->setColumnWidth( 9, 50 );
    ui->tableListaSklepow->setColumnWidth( 10, 50 );
    ui->tableListaSklepow->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableListaSklepow->resizeColumnsToContents();
   // ui->tableListaSklepow->selectRow(0);
    ui->modyfikujButton->setEnabled( false );
    ui->usunButton->setEnabled(false);

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
    unsigned int ret = QMessageBox::question( this, "Uwaga", "<CENTER>Czy na pewno chcesz usun¹æ wybrany sklep z bazy danych?</CENTER>",
                                              QMessageBox::Yes | QMessageBox::No );
    if ( ret & QMessageBox::Yes ){
        if(db.usunRekord( &sklep.at(idxSklepu)) ){        //sprawdŸ czy usun¹³!
        sklep.removeAt(idxSklepu);
        modelSklepy.removeRow( idxSklepu , QModelIndex() );
        pobierzSklepy();
        return;
    }else{
        QMessageBox::information( this, "Uwaga","<CENTER>Nie mo¿na usun¹æ towaru bed¹cego czêœci¹ zamówienia</CENTER>",QMessageBox::Ok );
        return;
    }

    }
    
    if ( ret & QMessageBox::No ){
        pobierzSklepy();
        return;
    }
}

void OknoHurtownia::on_modyfikujButton_clicked()
{
    int wiersz = ui->tableListaSklepow->currentIndex().row();
    EdycjaSklep *edycja = new EdycjaSklep(this,db, &sklep[wiersz], false);
    connect(edycja, SIGNAL(odswiezTabeleSklepu()), this, SLOT(pobierzSklepy()));
    edycja->show();
}

/**************************  OBS£UGA TOWARÓW **************************/

void OknoHurtownia::pobierzTowary()       //wyœwietlenie  towarow
{
    modelTowary.clear();
    towaryH = db.pobierz< DBProxy::TowarHurtownia >();

    for (int i = 0; i < towaryH.length(); i++) {

        modelTowary.setItem( i, 0, new QStandardItem( db.pobierz< DBProxy::Kategoria >(DBProxy::Kategoria::Id, DBProxy::Filtr(towaryH[i].idKategorii ) ).first().nazwa ) );
        modelTowary.setItem( i, 1, new QStandardItem( towaryH[i].nazwa ) );
        modelTowary.setItem( i, 2, new QStandardItem( towaryH[i].opis ) );
        modelTowary.setItem( i, 3, new QStandardItem( DBProxy::liczbaNaString( towaryH[i].cena ) ) );
        modelTowary.setItem( i, 4, new QStandardItem( DBProxy::liczbaNaString( towaryH[i].ilosc ) ) );
        modelTowary.setItem( i, 5, new QStandardItem( QString::number( towaryH[i].vat ) + "%"  ) );

    }


    modelTowary.setHeaderData( 0, Qt::Horizontal, "Kategoria" );
    modelTowary.setHeaderData( 1, Qt::Horizontal, "Nazwa" );
    modelTowary.setHeaderData( 2, Qt::Horizontal, "Opis" );
    modelTowary.setHeaderData( 3, Qt::Horizontal, "Cena" );
    modelTowary.setHeaderData( 4, Qt::Horizontal, "Iloœæ" );
    modelTowary.setHeaderData( 5, Qt::Horizontal, "VAT" );


    ui->tableListaTowarow->setModel( &modelTowary );

    ui->tableListaTowarow->setColumnWidth( 0, 100 );
    ui->tableListaTowarow->setColumnWidth( 1, 100 );
    ui->tableListaTowarow->setColumnWidth( 2, 115 );
    ui->tableListaTowarow->setColumnWidth( 3, 40 );
    ui->tableListaTowarow->setColumnWidth( 4, 35 );
    ui->tableListaTowarow->setColumnWidth( 5, 40 );
    ui->tableListaTowarow->setEditTriggers( QAbstractItemView::NoEditTriggers);
    ui->buttonModyfikujTowar->setEnabled( false );
    ui->buttonUsunTowar->setEnabled(false);
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

void OknoHurtownia::on_buttonUsunTowar_clicked()    // usuwa z listy i z bazy
{

    towaryH = db.pobierz< DBProxy::TowarHurtownia >();
    int idxTowaru = ui->tableListaTowarow->currentIndex().row();

    unsigned int ret = QMessageBox::question( this, "Uwaga", "<CENTER>Czy na pewno chcesz usun¹æ ?</CENTER>" + towaryH[ idxTowaru].nazwa,
                                              QMessageBox::Yes | QMessageBox::No );


    if ( ret & QMessageBox::Yes ){
        if(!db.usunRekord( &towaryH.at( idxTowaru ) )){

            QMessageBox::warning( this, "Uwaga","<CENTER>Nie mo¿na usun¹æ towaru bed¹cego czêœci¹ zamówienia</CENTER>",QMessageBox::Ok );

            pobierzTowary();
            return;

        }else {

            towaryH.removeAt(idxTowaru);
            modelTowary.removeRow( idxTowaru , QModelIndex() );
            QMessageBox::information(this, "Uwaga","<CENTER>Towar zosta³ usuniêty</CENTER>",QMessageBox::Ok  );
            pobierzTowary();

            return;
        }
    }

    if ( ret & QMessageBox::No ){
        pobierzZamowienia();
        pobierzTowary();
        return;
    }
}

void OknoHurtownia::on_buttonModyfikujTowar_clicked()
{
    int wiersz = ui->tableListaTowarow->currentIndex().row();
    EdycjaTowar *edycjaTowar = new EdycjaTowar(this, db, &towaryH[wiersz], false);
    connect(edycjaTowar, SIGNAL(odswiezTabeleTowarow()), this, SLOT(pobierzTowary()));
    edycjaTowar->show();
}

/*************************  OBS£UGA KATEGORII *************************/

void OknoHurtownia::pobierzKategorie()   {
    modelKategorie.clear();
    kH = db.pobierz< DBProxy::Kategoria >();

    for (int i = 0; i < kH.size(); i++) {
        modelKategorie.setItem( i, 0, new QStandardItem( kH[i].nazwa ) );
        modelKategorie.setItem( i, 1, new QStandardItem( DBProxy::liczbaNaString( kH[i].id ) ) );

    }
        modelKategorie.setHeaderData( 0, Qt::Horizontal, "Kategoria" );
        modelKategorie.setHeaderData( 1, Qt::Horizontal, "Id kategorii" );

    ui->tableListakategorii->setModel( &modelKategorie );
    ui->tableListakategorii->setColumnWidth( 0, 100 );
    ui->tableListakategorii->setColumnWidth( 1, 80 );
    ui->tableListakategorii->setEditTriggers( QAbstractItemView::NoEditTriggers);
    ui->buttonModyfikujKat->setEnabled( false );
    ui->buttonUsunKat->setEnabled(false);
}

void OknoHurtownia::on_buttonDodajKat_clicked()
{
    EdycjaKategoria *kategoria = new EdycjaKategoria(this,db);
    connect(kategoria, SIGNAL(odswiezTabeleKategoria()), this, SLOT(pobierzKategorie()));
    kategoria->show();

}

void OknoHurtownia::on_tableListakategorii_clicked(QModelIndex index)
{
    idxKategori = index.row();
    ui->tableListakategorii->selectRow( idxKategori);
    ui->buttonModyfikujKat->setEnabled( true );
    ui->buttonUsunKat->setEnabled(true);
}

void OknoHurtownia::on_buttonUsunKat_clicked()
{

    kH = db.pobierz< DBProxy::Kategoria >();
    int wiersz = ui->tableListakategorii->currentIndex().row();
    unsigned int ret = QMessageBox::question( this, "Uwaga", "<CENTER>Czy na pewno chcesz usun¹æ ?</CENTER>" + kH[ wiersz].nazwa,
                                              QMessageBox::Yes | QMessageBox::No );


    if ( ret & QMessageBox::Yes ){
        if(!db.usunRekord( &kH.at( wiersz ) )){

            QMessageBox::warning( this, "Uwaga","<CENTER>Nie mo¿na usun¹æ kategorii,<BR> do której przypisany jeste towar</CENTER>",QMessageBox::Ok );
            pobierzKategorie();
            pobierzZamowienia();
            return;

        }else {

            kH.removeAt(wiersz);
            modelKategorie.removeRow( wiersz , QModelIndex() );
            QMessageBox::information(this, "Uwaga","<CENTER>Kategoria zosta³a usuniêta</CENTER>",QMessageBox::Ok  );
            pobierzKategorie();
            pobierzZamowienia();
            pobierzTowary();
            return;
        }
    }

    if ( ret & QMessageBox::No ){
        pobierzKategorie();
        pobierzZamowienia();
        pobierzTowary();
        return;
    }


}

void OknoHurtownia::on_buttonModyfikujKat_clicked()
{
    int wiersz = ui->tableListakategorii->currentIndex().row();
    EdycjaKategoria *kategoria = new EdycjaKategoria(this, db, &kH[wiersz], false);
    connect(kategoria, SIGNAL(odswiezTabeleKategoria()), this, SLOT(pobierzKategorie()));
    connect(kategoria, SIGNAL(odswiezTabelaTowarow()), this, SLOT(pobierzTowary()));
    kategoria->show();
}


/************************* OBS£UGA ZAMÓWIEÑ **************************/

void OknoHurtownia::pobierzZamowienia()       //lista zamowien
{
    modelZamowienia.clear();
    zamowienieH = db.pobierz< DBProxy::ZamowienieHurtownia >();

    for (int i = 0; i < zamowienieH.size(); i++) {

        modelZamowienia.setItem( i, 0, new QStandardItem( zamowienieH[i].nrFaktury ) );
        modelZamowienia.setItem( i, 1, new QStandardItem( DBProxy::dataNaString( zamowienieH[i].dataZlozenia ) ) ); //rzutowanie nie dzia³a
        modelZamowienia.setItem( i, 2, new QStandardItem( DBProxy::dataNaString( zamowienieH[i].dataRealizacji ) ) );//rzutowanie nie dzia³a
        modelZamowienia.setItem( i, 3, new QStandardItem( DBProxy::liczbaNaString( zamowienieH[i].upust ) ) );//rzutowanie nie dzia³a
        modelZamowienia.setItem( i, 4, new QStandardItem( DBProxy::statusNaString( zamowienieH[i].status ) ) );//rzutowanie nie dzia³a

    }


    modelZamowienia.setHeaderData( 0, Qt::Horizontal, "Nr faktury" );
    modelZamowienia.setHeaderData( 1, Qt::Horizontal, "Data z³o¿enia" );
    modelZamowienia.setHeaderData( 2, Qt::Horizontal, "Data realizacji" );
    modelZamowienia.setHeaderData( 3, Qt::Horizontal, "Upust" );
    modelZamowienia.setHeaderData( 4, Qt::Horizontal, "Status" );

    ui->tableZamowienia->setModel( &modelZamowienia );
    ui->tableZamowienia->setColumnWidth( 0, 90 );
    ui->tableZamowienia->setColumnWidth( 1, 100 );
    ui->tableZamowienia->setColumnWidth( 2, 100 );
    ui->tableZamowienia->setColumnWidth( 3, 50 );
    ui->tableZamowienia->setColumnWidth( 4, 85 );
    ui->tableZamowienia->setEditTriggers( QAbstractItemView::NoEditTriggers);

    ui->buttonRealizujZamowieni->setEnabled(false);
    ui->buttonAnulujZamowienie->setEnabled(false);
    ui->szczegolyButton->setEnabled(false);
}

void OknoHurtownia::on_tableZamowienia_clicked(QModelIndex index)
{
    idxZamowienia = index.row();
    ui->tableZamowienia->selectRow( idxZamowienia);
    ui->buttonRealizujZamowieni->setEnabled(true);
    ui->buttonAnulujZamowienie->setEnabled(true);
    ui->szczegolyButton->setEnabled(true);

}

void OknoHurtownia::on_buttonRealizujZamowieni_clicked()
{
    int wiersz = ui->tableZamowienia->currentIndex().row();
    ZamowienieHurtownia &zamowienie = zamowienieH[ wiersz ];

    modelPozycjeZamowienia.clear();
    pozycjeZamowienia = db.pobierz <DBProxy::PozycjaZamowienia>();
    modelTowary.clear();
    towaryH = db.pobierz< DBProxy::TowarHurtownia >();
    bool sprawdz = false;

    if( zamowienie.status == DBProxy::Oczekujace ) {
    for( int i = 0 ; i < pozycjeZamowienia.length() ; ++i)
        if(pozycjeZamowienia[i].idZamowienia == zamowienie.id)
            for( int j = 0 ; j < towaryH.length() ; ++j)
                if(pozycjeZamowienia[i].idTowaru  == towaryH[j].id)
                    if( pozycjeZamowienia[i].ilosc > towaryH[j].ilosc)
                        sprawdz = true;



    if(!sprawdz){
        {
            zamowienie.status = DBProxy::DoRealizacji;
            zamowienie.dataRealizacji = QDate::currentDate();
            db.uaktualnij( zamowienie );
        }
        for( int i = 0 ; i < pozycjeZamowienia.length() ; ++i)
            if(pozycjeZamowienia[i].idZamowienia == zamowienie.id)
                for( int j = 0 ; j < towaryH.length() ; ++j)
                    if(pozycjeZamowienia[i].idTowaru  == towaryH[j].id)
                        if( pozycjeZamowienia[i].ilosc <= towaryH[j].ilosc){    //zamówienie zawiera nie ca³kowit¹ iloœc towaru
            towaryH[j].ilosc = towaryH[j].ilosc - pozycjeZamowienia[i].ilosc;
            db.uaktualnij( towaryH.at(j) );
        }

        QString nrFaktury;
        QDate data = QDate::currentDate();

        nrFaktury += DBProxy::liczbaNaString(zamowienie.id) +  "/" + DBProxy::liczbaNaString (data.day()) + "/" + DBProxy::liczbaNaString(data.month() )+ "/" + DBProxy::liczbaNaString(data.year()) ;

        zamowienie.nrFaktury =  nrFaktury;
        db.uaktualnij(zamowienie);
        qDebug( ) << nrFaktury;
        qDebug() << zamowienie.nrFaktury;


        QMessageBox::information( this, "Komunikat","<CENTER>Zamówienie przyjete do realizacji</CENTER>", QMessageBox::Yes  );
        pobierzZamowienia();
        pobierzTowary();
    }
    else {
        QMessageBox::information( this, "Komunikat","<CENTER>Zamówienie nie moze byc zrealizowane - <BR>brak towarow w bazie hurtowni</CENTER>", QMessageBox::Yes  );
        zamowienie.status = DBProxy::Anulowane;
        zamowienie.dataRealizacji = QDate::currentDate();
        db.uaktualnij( zamowienie );
        pobierzZamowienia();
    }
}
pobierzZamowienia();
}

void OknoHurtownia::on_buttonAnulujZamowienie_clicked()
{
    int wiersz = ui->tableZamowienia->currentIndex().row();
    ZamowienieHurtownia &zamowienie = zamowienieH[ wiersz ];

    if( zamowienie.status == DBProxy::Oczekujace ) {
        zamowienie.status = DBProxy::Anulowane;
        zamowienie.dataRealizacji = QDate::currentDate();
        db.uaktualnij( zamowienie );
        
    }

    pobierzZamowienia();
}

void OknoHurtownia::pobierzSzczegoly(){

    {
        modelPozycjeZamowienia.clear();
        pozycjeZamowienia = db.pobierz< DBProxy::PozycjaZamowienia >();

        for (int i = 0; i < zamowienieH.size(); i++) {
            modelPozycjeZamowienia.setItem( i, 0, new QStandardItem( DBProxy::liczbaNaString( pozycjeZamowienia[i].idZamowienia ) ) );
            modelPozycjeZamowienia.setItem( i, 1, new QStandardItem( DBProxy::liczbaNaString( pozycjeZamowienia[i].idTowaru ) ) );
            modelPozycjeZamowienia.setItem( i, 2, new QStandardItem(  pozycjeZamowienia[i].ilosc  ) );

        }

        modelPozycjeZamowienia.setHeaderData( 0, Qt::Horizontal, "Id Zamówienia" );
        modelPozycjeZamowienia.setHeaderData( 1, Qt::Horizontal, "Id Towaru" );
        modelPozycjeZamowienia.setHeaderData( 2, Qt::Horizontal, "IloœŸ" );


        ui->tableZamowienia->setModel( &modelPozycjeZamowienia );
        ui->tableZamowienia->setColumnWidth( 0, 50 );
        ui->tableZamowienia->setColumnWidth( 1, 50 );
        ui->tableZamowienia->setColumnWidth( 2, 30 );


    }

}

void OknoHurtownia::on_szczegolyButton_clicked()
{

    int wiersz = ui->tableZamowienia->currentIndex().row();
    SzczegolyZamowienia *pozZamowienia = new SzczegolyZamowienia(this,db, &zamowienieH[wiersz]);

    pozZamowienia ->show();

}

void OknoHurtownia::on_odswiezButton_clicked()
{
    pobierzZamowienia();
}




