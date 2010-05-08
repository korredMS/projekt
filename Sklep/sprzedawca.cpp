#include "sprzedawca.h"
#include "ui_sprzedawca.h"

Sprzedawca::Sprzedawca(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sprzedawca)
{
    ui->setupUi(this);
}

Sprzedawca::~Sprzedawca()
{
    delete ui;
}

void Sprzedawca::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



void Sprzedawca::on_pushButton_clicked()
{
    QMessageBox::information(  this, "!", "dzia³a", QMessageBox::Ok );
}
