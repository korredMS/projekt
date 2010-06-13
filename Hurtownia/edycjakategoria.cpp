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
    setWindowTitle(tr("Dodawanie kategorii"));

    if (!dodajeK){
        ui->lineNazwaKat->setText( akategoria->nazwa);
        ui->buttonDodajKategoria->setText("Aktualizuj");
        setWindowTitle(tr("Aktualizacja kategorii"));
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
        QMessageBox::critical(this,"Dodanie sklepu","</CENTER>Niepowodzenie</CENTER>",QMessageBox::Ok);
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
         QMessageBox::information( this, "<CENTER>Dodanie kategorii", "Dodano kategorie</CENTER> " + ui->lineNazwaKat->text(), QMessageBox::Ok);
     else if( sukces )
         QMessageBox::information( this, "Modyfikacja sklepu", "<CENTER>Uaktualniono kategorie</CENTER> " + ui->lineNazwaKat->text(), QMessageBox::Ok);

     czyscUi();
     emit odswiezTabeleKategoria();
     emit odswiezTabelaTowarow();
     this->close();

}
void EdycjaKategoria::czyscUi()
{
     ui->lineNazwaKat->clear();
}
