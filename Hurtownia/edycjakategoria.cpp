#include "edycjakategoria.h"
#include "ui_edycjakategoria.h"

using namespace DBProxyNS;

EdycjaKategoria::EdycjaKategoria(QWidget *parent,DBProxy &adb) :
    QDialog(parent),
    ui(new Ui::EdycjaKategoria),
    db( adb )
{
    ui->setupUi(this);
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
     DBProxy::Kategoria kategoria( ui->lineNazwaKat->text() );

     if(ui->lineNazwaKat->text().isEmpty()){
         QMessageBox::critical(this,"Dodanie sklepu","Niepowodzenie",QMessageBox::Ok);
     }else{
         unsigned int id = db.dodaj( kategoria );
         QMessageBox::information( this, "Dodanie sklepu", "Dodano kategoriê " + ui->lineNazwaKat->text() , QMessageBox::Ok);
         qDebug() << id;
     }

     czyscUi();

}
void EdycjaKategoria::czyscUi()
{
     ui->lineNazwaKat->clear();
}
