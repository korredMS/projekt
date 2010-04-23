#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString host = QInputDialog::getText( this, "Host", "Podaj nazwê hosta z baz¹:" );
    QString login = QInputDialog::getText( this, "Login", "Podaj login:" );
    QString haslo = QInputDialog::getText( this, "Haslo", "Podaj haslo:", QLineEdit::Password );

    QString baza = "Hurtownia";
    QMessageBox::StandardButton button = QMessageBox::question( this, "Wybierz bazê.", "Czy chcesz po³±czyæ siê z baz± sklepu?",
                                                                QMessageBox::Yes | QMessageBox::No );

    ui->tabWidget->setTabEnabled( 1, false );   // sklep
    ui->tabWidget->setTabEnabled( 2, false );   // towar hurtownia
    ui->tabWidget->setTabEnabled( 6, false );   // zamowienie hurtownia

    if( button == QMessageBox::Yes ) {
        baza = "Sklep";
    } else {
        for( int i = 0; i < ui->tabWidget->count(); ++i )
            ui->tabWidget->setTabEnabled( i, !ui->tabWidget->isTabEnabled( i ) );

        // pozycja zamowienia jest w sklepie i hurtowni
        ui->tabWidget->setTabEnabled( 4, true );
    }



    db = new DBProxy( this, host, baza, login, haslo );

    connect( db, SIGNAL(log(QString)), ui->plainTextEdit, SLOT(appendPlainText(QString)));

    db->polacz();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
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

void MainWindow::on_pushButton_clicked()
{
    DBProxy::Hurtownia hurtownia( ui->lineEdit->text(),
                                  ui->lineEdit_2->text(),
                                  ui->lineEdit_3->text(),
                                  ui->lineEdit_4->text(),
                                  ui->lineEdit_5->text(),
                                  ui->lineEdit_6->text(),
                                  ui->lineEdit_7->text(),
                                  ui->lineEdit_8->text() );
    if( db->dodajHurtownie( hurtownia ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_3_clicked()
{
    DBProxy::Sklep sklep( ui->lineEdit_21->text(),
                          ui->lineEdit_22->text(),
                          ui->lineEdit_23->text(),
                          ui->lineEdit_24->text(),
                          ui->lineEdit_25->text(),
                          ui->lineEdit_26->text(),
                          ui->lineEdit_27->text(),
                          ui->lineEdit_28->text(),
                          ui->lineEdit_29->text(),
                          ui->lineEdit_30->text(),
                          ui->lineEdit_31->text().toFloat() );

    if( db->dodajSklep( sklep ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_2_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::wyczyscAktualnePola() {
    QObjectList children = ui->tabWidget->currentWidget()->children();

    foreach( QObject *object, children ) {
        QLineEdit *lineEdit = qobject_cast< QLineEdit* >( object );
        if( lineEdit )
            lineEdit->clear();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_5_clicked()
{
    DBProxy::TowarHurtownia towar( ui->lineEdit_32->text(),
                                   ui->lineEdit_33->text(),
                                   ui->lineEdit_34->text().toUInt(),
                                   ui->lineEdit_35->text().toFloat(),
                                   (DBProxy::StawkaVAT)ui->lineEdit_36->text().toInt() );

    if( db->dodajTowarHurtownia( towar ) ) {
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );

        QSqlQuery query = db->baza().exec( "SELECT * FROM Towar;" );
//        if( !query.is )
//            qDebug() <<  query.lastError().text();
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_7_clicked()
{
    DBProxy::TowarSklep towar( ui->lineEdit_37->text(),
                                   ui->lineEdit_38->text(),
                                   ui->lineEdit_39->text().toUInt(),
                                   ui->lineEdit_40->text().toFloat(),
                                   (DBProxy::StawkaVAT)ui->lineEdit_41->text().toInt(),
                                   ui->lineEdit_42->text().toFloat() );

    if( db->dodajTowarSklep( towar ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_9_clicked()
{
    DBProxy::PozycjaZamowienia pozycja( ui->lineEdit_43->text().toUInt(),
                                        ui->lineEdit_44->text().toUInt(),
                                        ui->lineEdit_45->text().toUInt() );

    if( db->dodajPozycjeZamowienia( pozycja ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_10_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_11_clicked()
{
    DBProxy::PozycjaSprzedazy pozycja( ui->lineEdit_46->text().toUInt(),
                                       ui->lineEdit_47->text().toUInt(),
                                       ui->lineEdit_48->text().toUInt(),
                                       ui->lineEdit_49->text().toFloat(),
                                       (DBProxy::StawkaVAT)ui->lineEdit_50->text().toInt() );

    if( db->dodajPozycjeSprzedazy( pozycja ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_12_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_15_clicked()
{
    DBProxy::ZamowienieHurtownia zamowienie( ui->lineEdit_56->text().toUInt(),
                                             QDate::fromString( ui->lineEdit_57->text() ),
                                             ui->lineEdit_58->text(),
                                             QDate::fromString( ui->lineEdit_59->text() ),
                                             ui->lineEdit_60->text().toFloat(),
                                             (DBProxy::StatusZamowienia)ui->lineEdit_61->text().toInt() );
    if( db->dodajZamowienieHurtownia( zamowienie ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_16_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_17_clicked()
{
    DBProxy::ZamowienieSklep zamowienie( ui->lineEdit_62->text().toUInt(),
                                             ui->lineEdit_63->text().toUInt(),
                                             QDate::fromString( ui->lineEdit_64->text() ),
                                             ui->lineEdit_65->text(),
                                             QDate::fromString( ui->lineEdit_66->text() ),
                                             ui->lineEdit_67->text().toFloat(),
                                             (DBProxy::StatusZamowienia)ui->lineEdit_68->text().toInt() );
    if( db->dodajZamowienieSklep( zamowienie ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_18_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_33_clicked()
{
    DBProxy::Sprzedaz sprzedaz( ui->lineEdit_105->text().toUInt(),
                                ui->lineEdit_106->text().toUInt(),
                                ui->lineEdit_107->text().toUInt(),
                                ui->lineEdit_108->text(),
                                (DBProxy::Potwierdzenie)ui->lineEdit_109->text().toInt(),
                                QDate::fromString( ui->lineEdit_110->text() ),
                                ui->lineEdit_111->text().toFloat(),
                                (DBProxy::StatusZamowienia)ui->lineEdit_112->text().toInt() );
    if( db->dodajSprzedaz( sprzedaz ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_35_clicked()
{
    DBProxy::Faktura faktura( ui->lineEdit_113->text() );

    if( db->dodajFakture( faktura ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_36_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_37_clicked()
{
    DBProxy::Kategoria kategoria( ui->lineEdit_114->text() );

    if( db->dodajKategorie( kategoria ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_38_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_39_clicked()
{
    DBProxy::Klient klient( ui->lineEdit_115->text(),
                            ui->lineEdit_116->text(),
                            ui->lineEdit_117->text(),
                            ui->lineEdit_118->text(),
                            ui->lineEdit_119->text(),
                            ui->lineEdit_120->text(),
                            ui->lineEdit_121->text() );
    if( db->dodajKlienta( klient ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}

void MainWindow::on_pushButton_40_clicked()
{
    wyczyscAktualnePola();
}

void MainWindow::on_pushButton_41_clicked()
{
    DBProxy::Pracownik pracownik( ui->lineEdit_122->text(),
                                  ui->lineEdit_123->text(),
                                  ui->lineEdit_124->text(),
                                  (DBProxy::Posada)ui->lineEdit_125->text().toInt(),
                                  QDate::fromString( ui->lineEdit_126->text() ),
                                  ui->lineEdit_127->text().toFloat(),
                                  ui->lineEdit_128->text(),
                                  ui->lineEdit_129->text(),
                                  ui->lineEdit_130->text(),
                                  ui->lineEdit_131->text(),
                                  ui->lineEdit_132->text(),
                                  ui->lineEdit_133->text(),
                                  ui->lineEdit_134->text() );
    if( db->dodajPracownika( pracownik ) )
        ui->plainTextEdit->appendPlainText( QDateTime::currentDateTime().toString() + "\tWpis dodany." );
}
