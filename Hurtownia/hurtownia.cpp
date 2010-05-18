#include "hurtownia.h"
#include "ui_hurtownia.h"

Hurtownia::Hurtownia(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hurtownia)
{
    ui->setupUi(this);
}

Hurtownia::~Hurtownia()
{
    delete ui;
}

void Hurtownia::changeEvent(QEvent *e)
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
