#include "edycjasklep.h"
#include "ui_edycjasklep.h"

using namespace DBProxyNS;

EdycjaSklep::EdycjaSklep(QWidget *parent, DBProxy &adb, DBProxy::Sklep *asklep, bool dodajeNowy ) :
        QDialog(parent),
        ui(new Ui::EdycjaSklep),
        db( adb ),
        mSklep( asklep ),
        dodaje( dodajeNowy )
{
    ui->setupUi(this);
    connect(ui->zapiszButton,SIGNAL(clicked()),this,SLOT(zapiszClicked()));
    setWindowTitle(tr("Edycja sklepu"));

    if( !dodaje ) {
        ui->nazwaEdit->setText( asklep->nazwa );
        ui->regonEdit->setText( asklep->REGON);
        ui->ulicaEdit->setText( asklep->ulica);
        ui->miejscowoscEdit->setText( asklep->miejscowosc);
        ui->kodPocztowyEdit->setText( asklep->kodPocztowy);
        ui->telefonEdit->setText( asklep->telefon);
        ui->faxEdit->setText( asklep->fax);
        ui->emailEdit->setText( asklep->email);
        ui->upustEdit->setText( QString::number(asklep-> upust));
        ui->loginEdit->setText( asklep->login);
        ui->hasloEdit->setText( asklep->haslo);
        ui->zapiszButton->setText("Modyfikuj");
    }

}

EdycjaSklep::~EdycjaSklep()
{
    delete ui;
}

void EdycjaSklep::changeEvent(QEvent *e)
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
void EdycjaSklep::zapiszClicked()
{
    if(ui->nazwaEdit->text().isEmpty()){
        QMessageBox::critical(this,"Dodanie sklepu","Niepowodzenie",QMessageBox::Ok);
        return;
    }

    unsigned int sukces;
    DBProxy::Sklep sklep( ui->nazwaEdit->text(),
                          ui->regonEdit->text(),
                          ui->ulicaEdit->text(),
                          ui->miejscowoscEdit->text(),
                          ui->kodPocztowyEdit->text(),
                          ui->telefonEdit->text(),
                          ui->faxEdit->text(),
                          ui->emailEdit->text(),
                          ui->upustEdit->text(),
                          ui->loginEdit->text(),
                          ui->hasloEdit->text().toFloat() );
    if( dodaje ) {
        sukces = db.dodaj( sklep );// wpisanie nowego

    } else {        
        sklep.id = mSklep->id; // edycja
        sukces = db.uaktualnij( sklep ); //dodanie nowego lub zaktualizowanie starego rekordu
    }

    if( sukces && dodaje)
        QMessageBox::information( this, "Dodanie sklepu", "Dodano sklep " + ui->nazwaEdit->text(), QMessageBox::Ok);
    else if( sukces )
        QMessageBox::information( this, "Modyfikacja sklepu", "Uaktualniono sklep " + ui->nazwaEdit->text(), QMessageBox::Ok);


    czyscUi();
    emit odswiezTabeleSklepu();
    this->close();
}

void EdycjaSklep::czyscUi()
{
    ui->nazwaEdit->clear();
    ui->regonEdit->clear();
    ui->ulicaEdit->clear();
    ui->miejscowoscEdit->clear();
    ui->kodPocztowyEdit->clear();
    ui->telefonEdit->clear();
    ui->faxEdit->clear();
    ui->emailEdit->clear();
    ui->loginEdit->clear();
    ui->hasloEdit->clear();
}



void EdycjaSklep::on_anulujButton_clicked()
{
    this->close();
}

void EdycjaSklep::on_buttonWyczyscS_clicked()
{
    czyscUi();
}
