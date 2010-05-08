#include "zamawiajacy.h"
#include "ui_zamawiajacy.h"

Zamawiajacy::Zamawiajacy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zamawiajacy)
{
    ui->setupUi(this);
}

Zamawiajacy::~Zamawiajacy()
{
    delete ui;
}

void Zamawiajacy::changeEvent(QEvent *e)
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
