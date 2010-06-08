#include "edycjatowar.h"
#include "ui_edycjatowar.h"

using namespace DBProxyNS;


EdycjaTowar::EdycjaTowar(QWidget *parent, DBProxy &adb,DBProxy::TowarHurtownia *atowar, bool dodajeNowyT) :
        QDialog(parent),
        ui(new Ui::EdycjaTowar),
        db( adb ),
        mTowar( atowar),
        dodajeT(dodajeNowyT)
{
    ui->setupUi(this);

    if( !dodajeT ) {
            ui->lineNazwaT->setText( atowar->nazwa );
            ui->lineOpisT->setText( atowar->opis );
            ui->lineIloscT->setText(  QString::number (atowar->ilosc) );
            ui->lineCenaT->setText( QString::number (atowar->cena) );
            ui->lineVatT->setText( QString::number (atowar->vat));
            ui->lineIdKategorT->setText( QString::number (atowar->idKategorii) );
            ui->buttonDodajT->setText("Modyfikuj");
        }
}

EdycjaTowar::~EdycjaTowar()
{
    delete ui;
}

void EdycjaTowar::changeEvent(QEvent *e)
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


void EdycjaTowar::on_buttonAnulujT_clicked()
{
    this->close();
}

void EdycjaTowar::on_buttonDodajT_clicked()
{
    if(ui->lineNazwaT->text().isEmpty()){
        QMessageBox::critical(this,"Dodanie Towaru","Niepowodzenie",QMessageBox::Ok);
    return;
    }
    unsigned int sukces;
    DBProxy::TowarHurtownia towar( ui->lineNazwaT->text(),
                                   ui->lineOpisT->text(),
                                   ui->lineIloscT->text().toUInt(),
                                   ui->lineCenaT->text().toFloat(),
                                   (DBProxy::StawkaVAT)ui->lineVatT->text().toInt(),
                                   ui->lineIdKategorT->text().toUInt() );
    if( dodajeT ) {
        sukces = db.dodaj( towar );// wpisanie nowego

    } else {

        towar.id = mTowar->id; // edycja
        sukces = db.uaktualnij( towar ); //dodanie nowego lub zaktualizowanie starego rekordu
    }

    if( sukces && dodajeT)
        QMessageBox::information( this, "Dodanie towaru", "Dodano towar " + ui->lineNazwaT->text(), QMessageBox::Ok);
    else if( sukces )
        QMessageBox::information( this, "Modyfikacja towaru", "Uaktualniono towar " + ui->lineNazwaT->text(), QMessageBox::Ok);
        
        

    czyscUi();
    emit odswiezTabeleTowarow(); // odœwierzenie tabeli
    this->close();


}
void EdycjaTowar::czyscUi()
{
    ui->lineNazwaT->clear();
    ui->lineOpisT->clear();
    ui->lineIloscT->clear();
    ui->lineCenaT->clear();
    ui->lineVatT->clear();
    ui->lineIdKategorT->clear();


}

void EdycjaTowar::on_buttonWyczyscT_clicked()
{
    czyscUi();
}
