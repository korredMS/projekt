#include "kierownik.h"
#include "ui_kierownik.h"

Kierownik::Kierownik(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kierownik)
{
    ui->setupUi(this);
}

Kierownik::~Kierownik()
{
    delete ui;
}

void Kierownik::changeEvent(QEvent *e)
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
