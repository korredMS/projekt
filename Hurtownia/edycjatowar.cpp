#include "edycjatowar.h"
#include "ui_edycjatowar.h"




EdycjaTowar::EdycjaTowar(QWidget *parent, DBProxy &adb) :
        QDialog(parent),
        ui(new Ui::EdycjaTowar),
        db( adb )

{
    ui->setupUi(this);
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
    DBProxy::TowarHurtownia towar( ui->lineNazwaT->text(),
                                   ui->lineOpisT->text(),
                                   ui->lineIloscT->text().toUInt(),
                                   ui->lineCenaT->text().toFloat(),
                                   (DBProxy::StawkaVAT)ui->lineVatT->text().toInt(),
                                   ui->lineIdKategorT->text().toUInt() );
    
    
    if(ui->lineNazwaT->text().isEmpty()){
        QMessageBox::critical(this,"Dodanie Towaru","Niepowodzenie",QMessageBox::Ok);
    }else{
        unsigned int id = db.dodaj( towar );
        if( id )
            QMessageBox::information( this, "Dodanie Towaru", "Dodano Towar " + ui->lineNazwaT->text() , QMessageBox::Ok);
        else
            QMessageBox::information( this, "Dodanie Towaru", "Dodawanie towaru " + ui->lineNazwaT->text() + " nie powiod³o siê.", QMessageBox::Ok);
        qDebug() << id;
        
    }
    czyscUi();
    emit odswiezTabeleTowarow(); // odœwierzenie tabeli



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
