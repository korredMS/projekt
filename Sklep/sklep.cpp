#include "sklep.h"
#include "ui_sklep.h"

Sklep::Sklep(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sklep),
    baza( NULL, "localhost", "Sklep", "root", "inutero" )
{
    ui->setupUi(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("ISO8859-2"));

    if( !baza.polacz() )
        qDebug() << "sru";


}

Sklep::~Sklep()
{
    delete ui;
}

void Sklep::changeEvent(QEvent *e)
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

void Sklep::on_comboBox_currentIndexChanged( QString posada )
{
    posadaLogowanie = posada;
    if( posada == "wybierz" ){
        ui->listWidget->clear();
        return;
    }

    QMultiMap< DBProxy::Pracownik::PoleBazy, DBProxy::Filtr > filtr;
    filtr.insert( DBProxy::Pracownik::PosadaPole, DBProxy::Filtr( DBProxy::stringNaPosade( posada ) ) );
    pracownicy = baza.pobierz< DBProxy::Pracownik >( filtr );

    ui->listWidget->clear();
    foreach( DBProxy::Pracownik pracownik, pracownicy ) {
        ui->listWidget->addItem( new QListWidgetItem( pracownik.nazwa ) );

    }
}

void Sklep::on_pushButton_clicked()
{
    QString wpisaneHaslo = ui->lineEdit->text();

    if ( osobaLogowanie == "")
        QMessageBox::information( this, "!", "Musisz wybraæ pracownika", QMessageBox::Ok );

    if ( wpisaneHaslo == "")
        QMessageBox::information(  this, "!", "Musisz wprowadziæ has³o", QMessageBox::Ok );

    else {

        bool czyHasloPoprawne;
        foreach( DBProxy::Pracownik pracownik, pracownicy ) {
                    if ( ( pracownik.nazwa == osobaLogowanie ) && ( pracownik.haslo == wpisaneHaslo ) ){
                        czyHasloPoprawne = true;

                        break;
                    }
        }

        if ( czyHasloPoprawne ){

            delete ui->widget;

            if ( posadaLogowanie == "Kierownik" ){
                QWidget *kierownik = new Kierownik( this );
                ui->centralWidget->layout()->addWidget( kierownik );
            }
            else if ( posadaLogowanie == "Sprzedawca" ){
                QWidget *sprzedawca = new Sprzedawca( this );
                ui->centralWidget->layout()->addWidget( sprzedawca );
            }
            else
            {
                QWidget *zamawiajacy = new Zamawiajacy( this );
                ui->centralWidget->layout()->addWidget( zamawiajacy );
            }
        }

        else
           QMessageBox::information( this, "!", "Wprowadzono b³êdne has³o", QMessageBox::Ok );
    }
}


void Sklep::on_listWidget_itemClicked(QListWidgetItem* item)
{
    osobaLogowanie = item->text();
}
