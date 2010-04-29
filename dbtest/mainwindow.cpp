#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase( "QMYSQL" );
    db.setHostName( "localhost" );
    db.setDatabaseName( "Hurtownia" );
    db.setUserName( "root" );
    db.setPassword( "inutero" );
    if( !db.open() )
        qDebug() << db.lastError();

    QSqlQuery query( db );
    if( !query.exec( "INSERT INTO Towar (idTowaru, Nazwa, opis, cena, ilosc, stawkaVAT)"
                     "VALUES ('12344678', 'wyborowa 0,5l', 'opis', 25.0, 100, '21');" ) )
        qDebug() << query.lastError().databaseText();

    QSqlQuery selectQuery( db );
    selectQuery.exec( "SELECT * FROM Towar" );
    while( selectQuery.next() ) {
        qDebug() << "";
        for( int i = 0; i < 6; ++i )
            qDebug() << selectQuery.value( i ).toString();
    }
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
