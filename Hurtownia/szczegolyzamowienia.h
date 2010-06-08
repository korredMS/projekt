#ifndef SZCZEGOLYZAMOWIENIA_H
#define SZCZEGOLYZAMOWIENIA_H

#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include "../DBProxy/DBProxy.h"

namespace Ui {
    class SzczegolyZamowienia;
}

class SzczegolyZamowienia : public QDialog {
    Q_OBJECT
public:
    SzczegolyZamowienia(QWidget *parent, DBProxy &db, DBProxy::ZamowienieHurtownia * mZamowienie );
    ~SzczegolyZamowienia();

protected:
    void changeEvent(QEvent *e);

private:
    void pobierzSzczegoly();
    DBProxy &db;
    DBProxy::ZamowienieHurtownia *mZamowienie;
    Ui::SzczegolyZamowienia *ui;
    QStandardItemModel modelPozycjeZamowienia;

private slots:
    void on_szczegolyZamowienaWrocButton_clicked();
};

#endif // SZCZEGOLYZAMOWIENIA_H
