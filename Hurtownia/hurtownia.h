#ifndef HURTOWNIA_H
#define HURTOWNIA_H

#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTableView>
#include <QList>
#include <stdlib.h>

#include "../DBProxy/dbproxy.h"

class EdycjaSklep;
class EdycjaTowar;
class EdycjaKategoria;
class SzczegolyZamowienia;



namespace Ui {
    class Hurtownia;
}


class OknoHurtownia : public QMainWindow {
    Q_OBJECT
public:
    OknoHurtownia(QWidget *parent = 0);
    ~OknoHurtownia();

    QStandardItemModel modelSklepy,modelTowary, modelKategorie, modelZamowienia, modelPozycjeZamowienia;
    QList< DBProxy::Kategoria > kH;
    QList< DBProxy::PozycjaZamowienia > pozycjeZamowienia;
    QList< DBProxy::Sklep > sklep;
    QList< DBProxy::TowarHurtownia > towaryH;
    QList< DBProxy::ZamowienieHurtownia > zamowienieH;
    

    int idxSklepu;
    int idxZamowienia;
    int idxKategori;

protected:
    void changeEvent(QEvent *e);
private:
    Ui::Hurtownia *ui;
    EdycjaSklep *edycja;
    EdycjaTowar *towar;
    EdycjaKategoria *kategoria;
    SzczegolyZamowienia *szczegoly;


    DBProxy db;

private slots:

    void on_koniecButton_clicked();
    void on_odswiezButton_clicked();
    void on_szczegolyButton_clicked();
    void on_buttonModyfikujKat_clicked();
    void on_buttonUsunKat_clicked();
    void on_buttonModyfikujTowar_clicked();
    void on_tableListakategorii_clicked(QModelIndex index);
    void on_buttonDodajKat_clicked();
    void on_buttonAnulujZamowienie_clicked();
    void on_buttonRealizujZamowieni_clicked();
    void on_tableZamowienia_clicked(QModelIndex index);
    void on_buttonUsunTowar_clicked();
    void on_tableListaTowarow_clicked(QModelIndex index);
    void on_buttonDodajTowar_clicked();
    void on_modyfikujButton_clicked();
    void on_usunButton_clicked();
    void on_tableListaSklepow_clicked(QModelIndex index);
    void on_dodajButton_clicked();
    void pobierzSklepy();
    void pobierzTowary();
    void pobierzKategorie();
    void pobierzZamowienia();
    void pobierzSzczegoly();


};

#endif // HURTOWNIA_H

