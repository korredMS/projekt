#include "edycjakategoria.h"
#include "ui_edycjakategoria.h"

using namespace DBProxyNS;

EdycjaKategoria::EdycjaKategoria(QWidget *parent,DBProxy &adb, DBProxy::Kategoria *akategoria, bool dodajeNowy) :
    QDialog(parent),
    ui(new Ui::EdycjaKategoria),
    db( adb ),
    mKategoria ( akategoria),
    dodajeK (dodajeNowy)
{
    ui->setupUi(this);

    if (!dodajeK){
        ui->lineNazwaKat->setText( akategoria->nazwa);
        ui->buttonDodajKategoria->setText("Modyfikuj");
    }
}

EdycjaKategoria::~EdycjaKategoria()
{
    delete ui;
}

void EdycjaKategoria::changeEvent(QEvent *e)
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

void EdycjaKategoria::on_buttonAnulujKategoria_clicked()
{
    this->close();
}

void EdycjaKategoria::on_buttonDodajKategoria_clicked()
{

    if(ui->lineNazwaKat->text().isEmpty()){
        QMessageBox::critical(this,"Dodanie sklepu","Niepowodzenie",QMessageBox::Ok);
        return;
    }

    unsigned int sukces;
     DBProxy::Kategoria kategoria( ui->lineNazwaKat->text() );

     if( dodajeK ) {
         sukces = db.dodaj( kategoria );// wpisanie nowego

     } else {
         kategoria.id = mKategoria->id; // edycja
         sukces = db.uaktualnij( kategoria ); //dodanie nowego lub zaktualizowanie starego rekordu
     }

     if( sukces && dodajeK)
         QMessageBox::information( this, "Dodanie kategorii", "Dodano kategorie " + ui->lineNazwaKat->text(), QMessageBox::Ok);
     else if( sukces )
         QMessageBox::information( this, "Modyfikacja sklepu", "Uaktualniono kategorie " + ui->lineNazwaKat->text(), QMessageBox::Ok);

     czyscUi();
     emit odswiezTabeleKategoria();
     emit odswiezTabelaTowarow();
     this->close();

}
void EdycjaKategoria::czyscUi()
{
     ui->lineNazwaKat->clear();
}
